/*
 * ShellAspect.h
 *
 *  Created on: Apr 27, 2018
 *      Author: zmcilwain
 */

#ifndef INC_SHELLASPECT_H_
#define INC_SHELLASPECT_H_

#include <Aspect.h>
#include <BaseEntity.h>
#include <GameMgr.h>

class ShellAspect : public Aspect
{
public:
	ShellAspect(BaseEntity * ent, Ogre::Vector3 target);
	~ShellAspect();

	void Tick(float dt);
	Ogre::Vector3 myTarget;
	Ogre::Vector3 originalPosition;
	Ogre::Degree angle;
	float time;

};



#endif /* INC_SHELLASPECT_H_ */
