/*
 * CollisionAspect.cpp
 *
 *  Created on: Apr 23, 2018
 *      Author: zmcilwain
 */

#include <CollisionAspect.h>
#include <Engine.h>
#include <EntityMgr.h>

CollisionAspect::CollisionAspect(PlayerEntity *ent)
	:Aspect(ent),
	 Ship(ent){
	// TODO Auto-generated constructor stub

}

CollisionAspect::~CollisionAspect() {
	// TODO Auto-generated destructor stub
}

void CollisionAspect::Tick(float dt){
	for (unsigned int i=0; i<entity->engine->entityMgr->entities.size();i++){
		if (entity->engine->entityMgr->entities[i] == entity)
			continue;
		if (entity->position.squaredDistance(entity->engine->entityMgr->entities[i]->position)
				< entity->engine->entityMgr->entities[i]->collisionRadius*entity->engine->entityMgr->entities[i]->collisionRadius){
			std::cout << "collision detected with "<< entity->engine->entityMgr->entities[i]->name << std::endl;
			//entity->position = entity->engine->entityMgr->entities[i]->spawnLocation;
			Ship->stopShip();
			Ship->respawn();
			//pushBack(Player);
		}
	}
}

