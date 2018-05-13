/*
 * PlayerEntity.cpp
 *
 *  Created on: Apr 21, 2018
 *      Author: zmcilwain
 */

#include <PlayerEntity.h>
#include <Physics2D.h>
#include <CollisionAspect.h>
#include <EntityMgr.h>
#include <GfxMgr.h>
#include "UnitAI.h"
#include <UiMgr.h>




PlayerEntity::PlayerEntity(Engine *engine, Ogre::Vector3 pos, int ident)
	:BaseEntity(engine, pos, ident)	{
	name = "PlayerEntity";//meshfname + IntToString(identity);
	collisionRadius = 20;
	currentHealth = 100;
	/*UnitAI * AI = new UnitAI(this);
	aspects.push_back((Aspect*)AI);*/


}


PlayerEntity::~PlayerEntity(){

}

void PlayerEntity::Init(){
	BaseEntity::Init();
	engine->entityMgr->playerEntity = this;
	Physics2D* phx = new Physics2D(this);
	aspects.push_back((Aspect*) phx);
	Renderable * renderable = new Renderable(this);
	aspects.push_back((Aspect*)renderable);
	CollisionAspect * collision = new CollisionAspect(this);
	aspects.push_back((Aspect*)collision);
	UnitAI * AI = new UnitAI(this);
	aspects.push_back((Aspect*)AI);



}

void PlayerEntity::stopShip(){
	Command * cleave = new Clear(this,Ogre::Vector3::ZERO);
	aspects[3]->setCommand(cleave);
	velocity = Ogre::Vector3::ZERO;
	desiredSpeed = speed = 0;
	desiredHeading = heading;
}

void PlayerEntity::respawn(){
	position = spawnLocation;
	desiredHeading = heading = 0;
	currentHealth =- 10;
	engine->uiMgr->pbar->setProgress(currentHealth);
}

/*void PlayerEntity::Tick(float dt)
{

}*/

//-------------------------------------------------------------------------------------------------------------------------------
Ship::Ship(Engine *engine, Ogre::Vector3 pos, int ident):
		PlayerEntity(engine, pos, ident){

	meshfilename = "ddg51.mesh";
	entityType = ShipEnt;
	isSelected = true;
	this->minSpeed = 0;
	this->maxSpeed = 64.0f;//meters per second...
	this->acceleration = 5.0f; // fast
	this->turnRate = 20.0f; //4 degrees per second
	std::cout << "Created: " << this->name << std::endl;
}

Ship::~Ship(){

}
