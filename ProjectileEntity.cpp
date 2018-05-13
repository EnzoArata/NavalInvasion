/*
 * ProjectileEntity.cpp
 *
 *  Created on: Apr 27, 2018
 *      Author: zmcilwain
 */

#include <ProjectileEntity.h>

ProjectileEntity::ProjectileEntity(Engine *engine, Ogre::Vector3 pos, Ogre::Vector3 target, int identity)
	:BaseEntity(engine, pos, identity)	{
	name = "Projectile";
	// TODO Auto-generated constructor stub

}

ProjectileEntity::~ProjectileEntity() {
	// TODO Auto-generated destructor stub
}

void ProjectileEntity::Init(){
	BaseEntity::Init();
	Renderable * renderable = new Renderable(this);
	aspects.push_back((Aspect*)renderable);
	ShellAspect * ShellPhx = new ShellAspect(this, myTarget);
	aspects.push_back((Aspect*)ShellPhx);

	this->sceneNode->scale(0.1,0.1,0.1);


}





//-------------------------------------------------------------------------------------------------------
Shell::Shell(Engine *engine, Ogre::Vector3 pos, Ogre::Vector3 target, int ident):
	ProjectileEntity(engine, pos, target, ident){

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

