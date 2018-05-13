/*
 * Command.h
 *
 *  Created on: Mar 28, 2018
 *      Author: sushil
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include <BaseEntity.h>
#include <OgreVector3.h>
#include <Types381.h>

class BaseEntity;

class Command {

public:
	Command(BaseEntity* ent, COMMAND_TYPE ct);
	virtual ~Command();

	virtual void init();
	virtual void tick(float dt);
	virtual bool done();

	BaseEntity* entity;
	COMMAND_TYPE commandType;

};

class MoveTo: public Command {

public:
	MoveTo(BaseEntity* ent, Ogre::Vector3 location);
	~MoveTo();

	void init();
	void tick(float dt);
	bool done();

	Ogre::Vector3 targetLocation;
	float MOVE_DISTANCE_THRESHOLD;

};


class Intercept: public Command {

public:
	Intercept(BaseEntity* ent, BaseEntity* targetEnt);
	~Intercept();

	void init();
	void tick(float dt);
	bool done();

	BaseEntity* targetEntity;
	Ogre::Vector3 predictedTargetPos;
	float MOVE_DISTANCE_THRESHOLD;


};

class Clear: public Command {

public:
	Clear(BaseEntity* ent, Ogre::Vector3 location);
	~Clear();


};

class Escort: public Command {

public:
	Escort(BaseEntity* ent, BaseEntity* targetEnt, Ogre::Vector3 offset);
	void init();
	void tick(float dt);
	bool done();
	~Escort();

	BaseEntity *target;
	Ogre::SceneNode* targetOffset;


};






#endif /* COMMAND_H_ */
