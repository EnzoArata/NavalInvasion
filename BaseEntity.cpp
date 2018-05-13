/*
 * BaseEntity.cpp
 *
 *  Created on: Apr 21, 2018
 *      Author: zmcilwain
 */

#include <BaseEntity.h>
#include <GfxMgr.h>
#include <BaseEntity.h>
#include <Utils.h>
//#include<Physics2D.h>
//#include<UnitAI.h>



BaseEntity::BaseEntity(Engine *engine, Ogre::Vector3 pos, int ident){

	this->engine = engine;

	entityType = None;
	meshfilename = std::string();
	position = spawnLocation = pos;
	velocity = Ogre::Vector3(0, 0, 0);
	identity = audioID = ident;
	isSelected = false;
	this->playSound = false;


	name = "BaseEntity";
	sceneNode = 0;
	ogreEntity = 0;
	collisionRadius = 0;

	this->desiredHeading = 0;
	this->acceleration = 0;
	this->heading = 0;
	this->turnRate = 0;
	this->desiredSpeed = this->speed = 0;
	this->minSpeed = this->maxSpeed = 0;

}

BaseEntity::~BaseEntity(){

}

void BaseEntity::Init(){

	name = meshfilename + IntToString(identity);
	ogreEntity = engine->gfxMgr->mSceneMgr->createEntity(meshfilename);
	sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(position);
	sceneNode->attachObject(ogreEntity);
	this->soundFile = "Boat-Sound.wav";

	//this->audioID = 0;
}

void BaseEntity::Tick(float dt){
	for(unsigned int i = 0; i < aspects.size(); i++){
		aspects[i]->Tick(dt);
	}
}

//-------------------------------------------------------------------------------------------------------------------------------
Rock::Rock(Engine *engine, Ogre::Vector3 pos, int ident):
		BaseEntity(engine, pos, ident){

	meshfilename = "sphere.mesh";
	entityType = RockEnt;
	collisionRadius = 100;
	//this->minSpeed = 0;
	//this->maxSpeed = 16.0f;//meters per second...
	//this->acceleration = 5.0f; // fast
	//this->turnRate = 20.0f; //4 degrees per second
	std::cout << "Created: " << this->name << std::endl;
}

Rock::~Rock(){

}





//-------------------------------------------------------------------------------------------------------------------------------
/*DDG51::DDG51(Engine *engine, Ogre::Vector3 pos, int ident):
		Entity381(engine, pos, ident){

	meshfilename = "ddg51.mesh";
	entityType = DDG51Type;
	this->minSpeed = 0;
	this->maxSpeed = 16.0f;//meters per second...
	this->acceleration = 5.0f; // fast
	this->turnRate = 20.0f; //4 degrees per second
	std::cout << "Created: " << this->name << std::endl;
}

DDG51::~DDG51(){

}

//-------------------------------------------------------------------------------------------------------------------------------
Carrier::Carrier(Engine *engine, Ogre::Vector3 pos, int ident):
		Entity381(engine, pos, ident){
	meshfilename = "cvn68.mesh";
	entityType = CarrierType;
	this->minSpeed = 0;
	this->maxSpeed = 20.0f;//meters per second...
	this->acceleration = 1.0f; // slow
	this->turnRate = 10.0f; //2 degrees per second
}

Carrier::~Carrier(){

}
//-------------------------------------------------------------------------------------------------------------------------------

SpeedBoat::SpeedBoat(Engine *engine, Ogre::Vector3 pos, int ident):
		Entity381(engine, pos, ident){
	meshfilename = "cigarette.mesh";
	entityType = SpeedBoatType;
	this->minSpeed = 0;
	this->maxSpeed = 30.0f;//meters per second...
	this->acceleration = 5.0f; // slow
	this->turnRate = 30.0f; //2 degrees per second
}

SpeedBoat::~SpeedBoat(){

}
//-------------------------------------------------------------------------------------------------------------------------------

Frigate::Frigate(Engine *engine, Ogre::Vector3 pos, int ident):
		Entity381(engine, pos, ident){
	meshfilename = "sleek.mesh";
	entityType = FrigateType;
	this->minSpeed = 0;
	this->maxSpeed = 15.0f;//meters per second...
	this->acceleration = 5.0f; // slow
	this->turnRate = 20.0f; //2 degrees per second
}

Frigate::~Frigate(){

}

//-------------------------------------------------------------------------------------------------------------------------------
Alien::Alien(Engine *engine, Ogre::Vector3 pos, int ident):
		Entity381(engine, pos, ident){
	meshfilename = "alienship.mesh";
	entityType = AlienType;
	this->minSpeed = 0;
	this->maxSpeed = 50.0f;//meters per second...
	this->acceleration = 10.0f; // slow
	this->turnRate = 40.0f; //2 degrees per second
}

Alien::~Alien(){

}*/
//-------------------------------------------------------------------------------------------------------------------------------

