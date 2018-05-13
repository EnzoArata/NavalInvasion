/*
 * PlayerEntity.h
 *
 *  Created on: Apr 21, 2018
 *      Author: zmcilwain
 */

#ifndef INC_PLAYERENTITY_H_
#define INC_PLAYERENTITY_H_

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include <Aspect.h>
#include <Types381.h>
#include <BaseEntity.h>
#include <Engine.h>
#include <Utils.h>



class PlayerEntity: public BaseEntity{
public:
	PlayerEntity(Engine *engine, Ogre::Vector3 pos, int identity);
	virtual ~PlayerEntity();

	float currentHealth;

	Ogre::Node* CameraGimbal;
	//bool isSelected;
	//float desiredHeading, desiredSpeed;
	//float heading, speed;

	//EntityTypes entityType;

	//std::vector<Aspect* > aspects;



	virtual void Init();
	virtual void stopShip();
	virtual void respawn();

	//void Tick(float dt);

protected:


	//Ogre::MovablePlane* indicator;


};

class PlayerShip: public PlayerEntity {
public:
	PlayerShip(Engine *engine, Ogre::Vector3 pos, int identity);
	virtual ~PlayerShip();

};

class AllySmall: public PlayerEntity {
public:
	AllySmall(Engine *engine, Ogre::Vector3 pos, int identity);
	void Init();
	virtual ~AllySmall();

};

class AllyCarrier: public PlayerEntity {
public:
	AllyCarrier(Engine *engine, Ogre::Vector3 pos, int identity);
	void Init();
	virtual ~AllyCarrier();

};



#endif /* INC_PLAYERENTITY_H_ */
