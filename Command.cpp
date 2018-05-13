/*
 * Command.cpp
 *
 *  Created on: Apr 2, 2018
 *      Author: enzo
 */

#include "Command.h"
//#include <UnitAI.h>
#include <BaseEntity.h>
#include <math.h>
#include <EntityMgr.h>
#include <Engine.h>

Command::Command(BaseEntity* ent, COMMAND_TYPE ct) {
	// TODO Auto-generated constructor stub
	commandType = ct;
	entity = ent;
}
void Command::init(){

}

void Command::tick(float dt){

}

bool Command::done(){

	return false;
}

Command::~Command() {
	// TODO Auto-generated destructor stub
}

MoveTo::MoveTo(BaseEntity* ent, Ogre::Vector3 location)
:Command(ent, Move)
{
	MOVE_DISTANCE_THRESHOLD = 25;
	targetLocation = location;

}

MoveTo::~MoveTo() {
	// TODO Auto-generated destructor stub
}

void MoveTo::init(){

	std::cout << "MoveTo created" << std::endl;
}

void MoveTo::tick(float dt){
	//std::cout << "Executing command" << std::endl;
	Ogre::Vector3 diff = targetLocation - entity->position;
	entity->desiredHeading =( std::atan2(diff.z, diff.x)* 180/3.14);
	entity->desiredSpeed = entity->maxSpeed;
}

bool MoveTo::done(){

	if (entity->position.squaredDistance(targetLocation) <= MOVE_DISTANCE_THRESHOLD)
	{

		//entity->velocity = Ogre::Vector3::ZERO;
		entity->desiredSpeed = 0;
		//entity->desiredHeading = entity->heading;

		return true;
	}


	return false;
}

Intercept::Intercept(BaseEntity* ent, BaseEntity* targetEnt)
:Command(ent, Inter)
{
	MOVE_DISTANCE_THRESHOLD = 25 ;
	targetEntity = targetEnt;
	std::cout << "Intercept command created" << std::endl;

}

Intercept::~Intercept() {
	// TODO Auto-generated destructor stub
}

void Intercept::init(){

}

void Intercept::tick(float dt){

	//std::cout << "Executing command" << std::endl;
	Ogre::Vector3 diff = targetEntity->position - entity->position;
	Ogre::Vector3 relVel = targetEntity->velocity - entity->velocity;

	diff.x = abs(diff.x);
	diff.y = abs(diff.y);
	diff.z = abs(diff.z);

	relVel.x = abs(relVel.x);
	relVel.y = abs(relVel.y);
	relVel.z = abs(relVel.z);

	float t = diff.absDotProduct(relVel);

	predictedTargetPos = targetEntity->position + targetEntity->velocity * dt;

	entity->desiredHeading =std::atan2(predictedTargetPos.z, predictedTargetPos.x);
	entity->desiredSpeed = entity->maxSpeed;

}

bool Intercept::done(){
	if (entity->position.squaredDistance(predictedTargetPos) <= MOVE_DISTANCE_THRESHOLD)
	{
		entity->velocity = Ogre::Vector3::ZERO;
		entity->desiredSpeed = entity->speed = 0;
		entity->desiredHeading = entity->heading;

		return true;
	}
	return false;
}

Clear::Clear(BaseEntity* ent, Ogre::Vector3 location)
:Command(ent, Clean)
{


}

Clear::~Clear() {
	// TODO Auto-generated destructor stub
}

Escort::Escort(BaseEntity *ent, BaseEntity * targetEnt, Ogre::Vector3 offset)
:Command(ent, EscortType)
{
	target = targetEnt;
	targetOffset = target->sceneNode->createChildSceneNode(target->position+offset);
	//targetOffset->_getDerivedPosition()
}

void Escort::init()
{

}

void Escort::tick(float dt)
{

	Ogre::Vector3 diff = targetOffset->_getDerivedPosition() - entity->position;
	//std::cout << target->position << std::endl;
	entity->desiredHeading =( std::atan2(diff.z, diff.x)* 180/3.14);
	entity->desiredSpeed = entity->maxSpeed;
	//std::cout << entity->desiredHeading << "," << entity->heading << std::endl;
	if (entity->position.squaredDistance(targetOffset->_getDerivedPosition()) <= 25*25)
	{
		entity->velocity = target->velocity;
		entity->desiredSpeed = entity->speed = target->speed;
		entity->desiredHeading = target->heading;
	}
	for(int i =0; i< entity->engine->entityMgr->entities.size();i++)
	{
			if(entity->position.squaredDistance(entity->engine->entityMgr->entities[i]->position) <= 700*700)
			{
				if(entity->team != entity->engine->entityMgr->entities[i]->team &&  entity->engine->entityMgr->entities[i]->team != 0)
				{
					Command * fireo = new FireBarrage(entity, entity->engine->entityMgr->entities[i], entity->shellSpread);
					Command * escorto = new Escort(entity, entity->engine->entityMgr->playerEntity, Ogre::Vector3(-200, 0, 200));
					entity->desiredSpeed = 0;
					entity->aspects[3]->insertCommand(fireo);
					//entity->aspects[3]->addCommand(escorto);
					break;
				}
			}
	}

}

bool Escort::done()
{
	return false;
}

Escort::~Escort()
{

}

FireBarrage::FireBarrage(BaseEntity* ent, BaseEntity* targetEnt, int count)
:Command(ent, BarrageType)
{
	target = targetEnt;
	timer = 5;
	bullets = count;
}

FireBarrage::~FireBarrage()
{

}

void FireBarrage::init()
{

}

void FireBarrage::tick(float dt)
{

	timer -= dt;
	float distance = entity->position.squaredDistance(target->position);
	Ogre::Vector3 diff = target->position - entity->position;
	entity->desiredHeading =( std::atan2(diff.z, diff.x)* 180/3.14);
	if (distance <= (500*500))
	{
		//std::cout << "enzo no" << std::endl;

		entity->desiredSpeed = 0;
		if (timer < 0)
		{

			//std::cout << "yo" << std::endl;
			Ogre::Vector3 offset;
			offset.x = Ogre::Math::RangeRandom(0, 150);
			offset.y = 0;
			offset.z = Ogre::Math::RangeRandom(0, 150);
			entity->engine->entityMgr->CreateEntityOfTypeAtPosition(ShellEnt, (PlayerEntity*)entity, target->position);
			for(int i=1; i<bullets; i++)
			{
				offset.x = Ogre::Math::RangeRandom(-150, 150);
				offset.z = Ogre::Math::RangeRandom(-150, 150);
				entity->engine->entityMgr->CreateEntityOfTypeAtPosition(ShellEnt, (PlayerEntity*)entity, target->position + offset);
			}
			timer = 5;
		}


	}
	else
	{
		//Ogre::Vector3 loc = entity->position;
		/*if (loc.x < target->position.x)
		{
			loc.x += 300;
		}
		else
		{
			loc.x -= 300;
		}
		if (loc.z < target->position.z)
		{
			loc.z += 300;
		}
		else
		{
			loc.z -= 300;
		}
		Command * newPos = new MoveTo(entity, loc);
		Command * newFire = new FireBarrage(entity, target);
		entity->aspects[3]->setCommand(newPos);
		entity->aspects[3]->addCommand(newFire);*/
		entity->desiredSpeed = entity->maxSpeed;
	}
	this->done();

}

bool FireBarrage::done()
{
	if(target->isAlive)
		return false;
	else
		return true;
}

Patrol::Patrol(BaseEntity* ent, Ogre::Vector3 location, Ogre::Vector3 location2, float range)
:Command(ent, PatrolType)
{
	pointA = location;
	pointB = location2;
	distance = range;
	MOVE_DISTANCE_THRESHOLD = 25;
	//targetOffset->_getDerivedPosition()

}
Patrol::~Patrol()
{

}

void Patrol::init(){


}
void Patrol::tick(float dt){

	Ogre::Vector3 diff = pointA - entity->position;
	std::cout << "MoveTo Ticking....." << std::endl;
	entity->desiredHeading =( std::atan2(diff.z, diff.x)* 180/3.14);
	entity->desiredSpeed = entity->maxSpeed/4;
	for(int i =0; i< entity->engine->entityMgr->entities.size();i++)
	{
		if(entity->position.squaredDistance(entity->engine->entityMgr->entities[i]->position) <= distance*distance)
		{
			if(entity->team != entity->engine->entityMgr->entities[i]->team &&  entity->engine->entityMgr->entities[i]->team != 0)
			{
				Command * fireo = new FireBarrage(entity, entity->engine->entityMgr->entities[i], entity->shellSpread);
				Command * patrolo = new Patrol(entity, pointA,pointB,500);
				entity->desiredSpeed = 0;
				entity->aspects[3]->setCommand(fireo);
				entity->aspects[3]->addCommand(patrolo);
				break;
			}
		}
	}
	this->done();

}
bool Patrol::done(){
	if (entity->position.squaredDistance(pointA) <= MOVE_DISTANCE_THRESHOLD*MOVE_DISTANCE_THRESHOLD)
	{
		Ogre::Vector3 temp = pointA;
		pointA = pointB;
		pointB = temp;
		entity->desiredSpeed = 0;
		//entity->speed = 0;
		return true;
	}

	return false;
}










