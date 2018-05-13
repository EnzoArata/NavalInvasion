/*
 * ShellAspect.cpp
 *
 *  Created on: Apr 27, 2018
 *      Author: zmcilwain
 */
#include <ShellAspect.h>

ShellAspect::ShellAspect(BaseEntity *ent, Ogre::Vector3 target) : Aspect(ent)
{

	myTarget = entity->position - target;
	entity->position.y += 10;
	entity->speed = 500;
	originalPosition = entity->position;
	angle = 0.5*Ogre::Degree(Ogre::Math::ASin(30*target.distance(entity->position)/(entity->speed*entity->speed)));
	//std::cout<< "------------------" << std::endl << angle << std::endl;
	//std::cout<< target.distance(entity->position) << std::endl;
	//std::cout<< myTarget.x << std::endl;


	Ogre::Vector3 diff = target - entity->position;
	entity->heading =( std::atan2(diff.z, diff.x)* 180/3.14);
	time = 0;

}

ShellAspect::~ShellAspect()
{

}

void ShellAspect::Tick(float dt)
{
	if (entity->position.y < 0){entity->Destroy();}
	time += dt;
	entity->velocity.y = entity->speed * Ogre::Math::Sin(angle);
	entity->velocity.x = entity->speed * Ogre::Math::Cos(angle);
	//std::cout << "INitial X velocity" << entity->velocity.x << std::endl;
	//std::cout << "INitial Y velocity" << entity->velocity.y << std::endl;

	  //adjacent/hyp
	entity->velocity.z = Ogre::Math::Sin(Ogre::Degree(entity->heading)) * entity->velocity.x;
	entity->velocity.x = Ogre::Math::Cos(Ogre::Degree(entity->heading)) * entity->velocity.x;
	entity->position.x = entity->velocity.x * time + originalPosition.x;
	entity->position.z = entity->velocity.z * time + originalPosition.z;
	entity->position.y = entity->velocity.y * time - (0.5*(entity->engine->gameMgr->gravity)*time*time) + originalPosition.y;
	 // just to be safe, we do not want ships in the air.

	//std::cout << entity->velocity.x << "," << entity->velocity.z << std::endl;

	//This does not change!

}



