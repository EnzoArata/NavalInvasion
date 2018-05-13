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

}

bool Escort::done()
{
	return false;
}

Escort::~Escort()
{

}


