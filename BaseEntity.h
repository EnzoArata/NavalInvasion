/*
 * BaseEntity.h
 *
 *  Created on: Apr 21, 2018
 *      Author: zmcilwain
 */

#ifndef INC_BASEENTITY_H_
#define INC_BASEENTITY_H_

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include <Aspect.h>
#include <Types381.h>
#include <Engine.h>

class Aspect;

class BaseEntity
{
public:
	BaseEntity(Engine *engine, Ogre::Vector3 pos, int identity);
	virtual ~BaseEntity();

	Engine *engine;

	//static data
	int identity;
	std::string name;
	std::string meshfilename;
	Ogre::SceneNode* sceneNode;
	Ogre::Entity*    ogreEntity;
	float acceleration, turnRate;
	float minSpeed, maxSpeed;
	Ogre::Vector3 spawnLocation;

	float collisionRadius;

	//dynamic data
	Ogre::Vector3 position;
	Ogre::Vector3 velocity;
	bool isSelected;
	bool didSelectSoundPlay;

	//sound
	std::string soundFile;
	bool playSound;
	unsigned int audioID;

	float desiredHeading, desiredSpeed;
	float heading, speed;

	EntityTypes entityType;

	std::vector<Aspect* > aspects;

	virtual void Init();

	void Tick(float dt);

protected:


};


class Rock: public  BaseEntity{
public:
	Rock(Engine *engine, Ogre::Vector3 pos, int identity);
	virtual ~Rock();

};


/*class Carrier: public BaseEntity {
public:
	Carrier(Engine *engine, Ogre::Vector3 pos, int identity);
	virtual ~Carrier();

};

class DDG51: public BaseEntity {
public:
	DDG51(Engine *engine, Ogre::Vector3 pos, int identity);
	virtual ~DDG51();

};

class SpeedBoat: public BaseEntity {
public:
	SpeedBoat(Engine *engine, Ogre::Vector3 pos, int identity);
	virtual ~SpeedBoat();

};

class Frigate: public BaseEntity {
public:
	Frigate(Engine *engine, Ogre::Vector3 pos, int identity);
	virtual ~Frigate();

};

class Alien: public BaseEntity {
public:
	Alien(Engine *engine, Ogre::Vector3 pos, int identity);
	virtual ~Alien();

};*/

#endif /* INC_BASEENTITY_H_ */

