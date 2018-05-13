/*
 * EnemyEntity.cpp
 *
 *  Created on: Apr 22, 2018
 *      Author: zmcilwain
 */

#include <EnemyEntity.h>
#include <Physics2D.h>
#include <CollisionAspect.h>
#include <EntityMgr.h>
#include <GfxMgr.h>
#include <Utils.h>
#include <UnitAI.h>


EnemyEntity::EnemyEntity(Engine *engine, Ogre::Vector3 pos, int ident)
:PlayerEntity(engine, pos, ident)	{

name = "EnemyEntity";//meshfname + IntToString(identity);
collisionRadius = 20;
team = 2;
shellSpread =4;



/*UnitAI * AI = new UnitAI(this);
aspects.push_back((Aspect*)AI);*/


}

EnemyEntity::~EnemyEntity(){
	//BaseEntity::~BaseEntity();
}

void EnemyEntity::Init(){
	BaseEntity::Init();
	engine->entityMgr->Enemies.push_back(this);
	Physics2D* phx = new Physics2D(this);
	aspects.push_back((Aspect*) phx);
	Renderable * renderable = new Renderable(this);
	aspects.push_back((Aspect*)renderable);
	CollisionAspect * collision = new CollisionAspect(this);
	aspects.push_back((Aspect*)collision);
	UnitAI * AI = new UnitAI(this);
	aspects.push_back((Aspect*)AI);

}

Enemy::Enemy(Engine *engine, Ogre::Vector3 pos, int ident):
		EnemyEntity(engine, pos, ident){

	meshfilename = "sleek.mesh";
	entityType = EnemyEnt;
	this->minSpeed = 0;
	this->maxSpeed = 300.0f;//meters per second...
	this->acceleration = 35.0f; // fast
	this->turnRate = 50.0f;
	damage = 20;
	currentHealth = 60;
	//this->sceneNode->scale(2,2,2);

	std::cout << "Created: " << this->name << std::endl;
}

Enemy::~Enemy(){

}
