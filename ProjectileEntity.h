/*
 * ProjectileEntity.h
 *
 *  Created on: Apr 27, 2018
 *      Author: zmcilwain
 */

#ifndef INC_PROJECTILEENTITY_H_
#define INC_PROJECTILEENTITY_H_

#include <BaseEntity.h>
#include <Aspect.h>
#include <Types381.h>
#include <CollisionAspect.h>
#include <ShellAspect.h>

class ProjectileEntity : public BaseEntity{
public:
	ProjectileEntity(Engine *engine, PlayerEntity *dad, Ogre::Vector3 target, int identity);
	virtual ~ProjectileEntity();
	Ogre::Vector3 myTarget;
	virtual void Init();
	void Tick(float dt);
};

class Shell: public ProjectileEntity {
public:
	Shell(Engine *engine, PlayerEntity *dad ,  Ogre::Vector3 target, int identity);
	virtual ~Shell();





};


#endif /* INC_PROJECTILEENTITY_H_ */
