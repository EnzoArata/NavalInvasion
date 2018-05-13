/*
 * Aspect.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include <Aspect.h>
#include <BaseEntity.h>  //Aspect includes Entity381.h



Aspect::Aspect(BaseEntity *ent){
	entity = ent;
}

Aspect::~Aspect(){
	delete entity;
}

void Aspect::addCommand(Command *c){

}

void Aspect::setCommand(Command *c){

}

void Aspect::insertCommand(Command * c)
{

}

void Aspect::Tick(float dt){

}






Renderable::Renderable(BaseEntity* ent): Aspect(ent){

}

Renderable::~Renderable(){

}

void Renderable::Tick(float dt){
//do something;
	entity->sceneNode->setPosition(entity->position); //now ogre should render the sceneNode at the new position...
	entity->sceneNode->resetOrientation(); // yaw is cumulative, so set current y-rotation to 0
	entity->sceneNode->yaw(Ogre::Degree(-entity->heading)); //ogre's yaw is in the direction of -z
	//bounding boxes are rendered so...
	if(entity->isSelected)
		entity->sceneNode->showBoundingBox(true);
	else
		entity->sceneNode->showBoundingBox(false); //or we could do this in the entity mgr every time tab is pressed....

}


