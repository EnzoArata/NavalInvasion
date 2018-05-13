/*
 * CollisionAspect.cpp
 *
 *  Created on: Apr 23, 2018
 *      Author: zmcilwain
 */

#include <CollisionAspect.h>
#include <Engine.h>
#include <EntityMgr.h>
#include <UiMgr.h>
#include <Types381.h>
#include <SoundMgr.h>

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
		if ( (entity->engine->entityMgr->entities[i] == entity) || (entity->engine->entityMgr->entities[i]->parent == Ship) )
			continue;
		if (Ship->position.squaredDistance(entity->engine->entityMgr->entities[i]->position) < Ship->collisionRadius*Ship->collisionRadius){

			if(entity->engine->entityMgr->entities[i]->entityType == ShellEnt)
			{
				if (Ship->team == entity->engine->entityMgr->entities[i]->parent->team){continue;}
			}
			if (Ship->team == entity->engine->entityMgr->entities[i]->team ) {continue;}
			std::cout << "collision detected with "<< entity->engine->entityMgr->entities[i]->name << std::endl;
			//entity->position = entity->engine->entityMgr->entities[i]->spawnLocation;
			//Ship->stopShip();
			//Ship->respawn();
			Ship->currentHealth -= entity->engine->entityMgr->entities[i]->damage;
			if(entity->engine->entityMgr->entities[i] == entity->engine->entityMgr->playerEntity){
				PlayerEntity* CurrentPlayer = (PlayerEntity*) entity->engine->entityMgr->entities[i];
				CurrentPlayer->currentHealth -= 10;
				entity->engine->uiMgr->UpdateHealth(CurrentPlayer->currentHealth);
				Ship->Destroy();
				//entity->engine->soundMgr->playExplosionSound(Ship);
			}
			if(Ship == entity->engine->entityMgr->playerEntity){
				if (entity->engine->entityMgr->entities[i]->entityType == RockEnt){
					Ship->respawn();
					Ship->currentHealth -= 20;
				}
				entity->engine->uiMgr->UpdateHealth(Ship->currentHealth);
			} else{
				if (entity->engine->entityMgr->entities[i]->entityType == RockEnt){

					Ship->Destroy();

				}
				else if(Ship->currentHealth <= 0)
				{
					Ship->Destroy();
				}

				//entity->engine->soundMgr->playExplosionSound(Ship);

			}
			if(entity->engine->entityMgr->entities[i]->entityType == ShellEnt )
			{
				entity->engine->entityMgr->entities[i]->Destroy();
				//entity->engine->soundMgr->playExplosionSound(entity);
			}


			//entity->engine->uiMgr->UpdateHealth(Ship->currentHealth);
			//pushBack(Player);
		}
	}
	if (entity->engine->entityMgr->playerEntity->currentHealth <= 0)
	{
			entity->engine->uiMgr->deathScreen();
	}
}

