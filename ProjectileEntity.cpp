/*
 * ProjectileEntity.cpp
 *
 *  Created on: Apr 27, 2018
 *      Author: zmcilwain
 */

#include <ProjectileEntity.h>

ProjectileEntity::ProjectileEntity(Engine *engine, PlayerEntity *dad, Ogre::Vector3 target, int identity)
	:BaseEntity(engine, dad->position, identity)	{
	name = "Projectile";
	parent = dad;
	team = 0;
	damage = parent->damage;
	// TODO Auto-generated constructor stub

}

ProjectileEntity::~ProjectileEntity() {

}

void ProjectileEntity::Init(){
	BaseEntity::Init();
	Renderable * renderable = new Renderable(this);
	aspects.push_back((Aspect*)renderable);
	ShellAspect * ShellPhx = new ShellAspect(this, myTarget);
	aspects.push_back((Aspect*)ShellPhx);

	//this->soundFile = "data/watercraft/sounds/explosion.wav";

	this->sceneNode->scale(0.02,0.02,0.02);


}





//-------------------------------------------------------------------------------------------------------
Shell::Shell(Engine *engine, PlayerEntity *dad, Ogre::Vector3 target, int ident):
	ProjectileEntity(engine, dad, target, ident){

	myTarget = target;
	meshfilename = "sphere.mesh";
	entityType = ShellEnt;
	isSelected = true;
	this->minSpeed = 0;
	this->maxSpeed = 500.0f;//meters per second...
	this->acceleration = 500.0f; // fast
	this->turnRate = 0; //
	std::cout << "Created: " << this->name << std::endl;
}

Shell::~Shell(){

}

