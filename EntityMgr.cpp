/*
 * EntityMgr.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include <EntityMgr.h>
#include <UiMgr.h>
#include <Engine.h>

EntityMgr::EntityMgr(Engine *eng): Mgr(eng){
	selectedEntity = 0;
	playerEntity = 0;
	count = 0;
	selectedEntityIndex = -1;
}

EntityMgr::~EntityMgr(){

}


void EntityMgr::SelectNextEntity(){
	if(selectedEntityIndex >= count - 1) {
		selectedEntityIndex = 0;
	} else {
		selectedEntityIndex++;
	}
	Select(selectedEntityIndex);
/*	if(selectedEntity != 0)
		selectedEntity->isSelected = false;
	selectedEntity = entities[selectedEntityIndex];
	selectedEntity->isSelected = true;
	SetSelectedFlyingEntity();*/
}

/*void EntityMgr::SetSelectedFlyingEntity(){
	FlyingEntity381 *tmp = dynamic_cast<FlyingEntity381 *>(selectedEntity);
	if(tmp != 0){
		selectedFlyingEntity = tmp;
	}	else {
		selectedFlyingEntity = 0;
	}
}*/


void EntityMgr::Select(int i){
	if(i >= 0 && i < count){
		if(selectedEntity != 0)
			selectedEntity->isSelected = false;
		selectedEntityIndex = i;
		selectedEntity = entities[i];
		selectedEntity->isSelected = true;
		//SetSelectedFlyingEntity();
	}
}




void EntityMgr::CreateEntityOfTypeAtPosition(EntityTypes entType, Ogre::Vector3 pos){

	BaseEntity * ent;
	switch(entType){

	case RockEnt:
		ent = (BaseEntity *) ( new Rock(engine, pos, count++));
		break;
	case ShipEnt:
		ent = (PlayerEntity *) ( new Ship(engine, pos, count++));
		break;
	case EnemyEnt:
		ent = (EnemyEntity *) ( new Enemy(engine, pos, count++));
		break;
	default:
		ent = (BaseEntity *) ( new Rock(engine, pos, count++));
		break;
	/*case DDG51Type:
		//CreateDDG51(pos);
		ent = (Entity381 *) ( new DDG51(engine, pos, count++));
		break;
	case CarrierType:
//		CreateCarrier(pos);
		ent = (Entity381 *) (new Carrier(engine, pos, count++));
		break;
	case SpeedBoatType:
		//CreateSpeedBoat(pos);
		ent =  (Entity381 *) (new SpeedBoat(engine, pos, count++));
		break;
	case FrigateType:
		//CreateFrigate(pos);
		ent = (Entity381 *) (new Frigate(engine, pos, count++));
		break;
	case AlienType:
		//CreateAlien(pos);
		ent = (Entity381 *) (new Alien(engine, pos, count++));
		break;
	case BansheeType:
		ent = (Entity381 *) ((FlyingEntity381*) (new Banshee(engine, pos, count++)));
		break;
	default:
		ent = (Entity381*) (new DDG51(engine, pos, count++));//CreateEntity("robot.mesh", pos);
		break;*/
	}
	ent->Init();
	entities.push_back(ent);

}

void EntityMgr::CreateEntityOfTypeAtPosition(EntityTypes entType, Ogre::Vector3 pos, Ogre::Vector3 target){
	BaseEntity * ent;
	switch(entType){

	case ShellEnt:
		ent = (ProjectileEntity *) ( new Shell(engine, pos, target, count++));
		break;
	default:
		ent = (BaseEntity *) ( new Rock(engine, pos, count++));
		break;
	}
	ent->Init();
	entities.push_back(ent);
}

void EntityMgr::Tick(float dt){
	for(int i = count - 1; i >= 0; i--){
		entities[i]->Tick(dt);
		if (entities[i]->isSelected){
			engine->uiMgr->UpdateInfo(entities[i]);

		}
		if(entities[i]->shouldKill)
		{
			delete entities[i];
			//entities.resize(entities.size()-1);
		}
	}
}
