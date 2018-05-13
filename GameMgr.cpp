/*
 * GameMgr.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#include <Engine.h>

#include <EntityMgr.h>
#include <GameMgr.h>
#include <GfxMgr.h>

#include <iostream>
#include <Types381.h>

#include <OgreOverlay.h>
#include <OgreSceneNode.h>

#include <Command.h>
#include <UiMgr.h>


GameMgr::GameMgr(Engine *engine):
	Mgr(engine),
	cameraNode(0),
	cameraPitchNode(0)
{
	levelSelect = 0;
	gravity = 30;
}

GameMgr::~GameMgr() {
	// TODO Auto-generated destructor stub
}

void GameMgr::Init(){

}

void GameMgr::LoadLevel(){
		cameraNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
		cameraPitchNode = 	cameraNode->createChildSceneNode();
		cameraPitchNode->attachObject(engine->gfxMgr->mCamera);
		cameraNode->setPosition(0, 200, 500);
		//cameraNode->lookAt(Ogre::Vector3(0, 200, 0));

}

void GameMgr::LoadLevel1(){
		levelSelect = 1;
		//engine->uiMgr->mTrayMgr->hideAll();

	    engine->gfxMgr->mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	    engine->uiMgr->LoadLevel1();
		engine->gfxMgr->mCamera->lookAt(Ogre::Vector3(0, 0, 0));
		Ogre::Light* light = engine->gfxMgr->mSceneMgr->createLight("MainLight");
		light->setPosition(20.0, 80.0, 50.0);


		// a fixed point in the ocean so you can see relative motion

		/*Ogre::Entity* ogreEntityFixed = engine->gfxMgr->mSceneMgr->createEntity("robot.mesh");
		Ogre::SceneNode* sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 100, -200));
		sceneNode->attachObject(ogreEntityFixed);
		sceneNode->showBoundingBox(true);*/

		// A node to attach the camera to so we can move the camera node instead of the camera.


		engine->gfxMgr->MakeGround();
		engine->gfxMgr->MakeSky();
		MakeEntities();
}

void GameMgr::MakeEntities(){
	Ogre::Vector3 pos = Ogre::Vector3(-500, 0, 0);
	//engine->entityMgr->CreateEntityOfTypeAtPosition(RockEnt, pos);
		pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition(PlayerEnt, pos);
		pos.x += 500;
		//pos.z -= 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition(AllySmallEnt, Ogre::Vector3(500,0,0));
		pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition(AllySmallEnt, Ogre::Vector3(-100, 0, 200));
		pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition(AllySmallEnt, Ogre::Vector3(-100, 0, -100));
		pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition(AllySmallEnt, Ogre::Vector3(-200, 0, -200));
		pos.x += 2000;
	engine->entityMgr->CreateEntityOfTypeAtPosition(EnemyEnt, Ogre::Vector3(-2000, 0, 2000));
		pos.x += 2000;
		pos.z += 2000;
	engine->entityMgr->CreateEntityOfTypeAtPosition(EnemyEnt, Ogre::Vector3(-2000, 0, -2000));
		//pos.x += 2000;
		pos.z += 2000;
	engine->entityMgr->CreateEntityOfTypeAtPosition(EnemyEnt, Ogre::Vector3(2000, 0, -2000));
		pos.x -= 2000;
		pos.z += 2000;
	engine->entityMgr->CreateEntityOfTypeAtPosition(EnemyEnt, Ogre::Vector3(2000, 0, 2000));
		pos.z += 500;
	//engine->entityMgr->CreateEntityOfTypeAtPosition(AllyCarrierEnt, Ogre::Vector3(-400, 0, 0));
	//engine->entityMgr->CreateEntityOfTypeAtPosition(EnemyEnt, pos);
		pos.z += 500;
	//engine->entityMgr->CreateEntityOfTypeAtPosition(EnemyEnt, pos);
		pos.z += 500;
	//engine->entityMgr->CreateEntityOfTypeAtPosition(EnemyEnt, pos);
		pos.z += 500;

	Command * escorto = new Escort(engine->entityMgr->Allies[0], engine->entityMgr->playerEntity,Ogre::Vector3(-200, 0, 200));

	Command * patrolo = new Patrol(engine->entityMgr->Allies[0], Ogre::Vector3(1500,0,0), Ogre::Vector3(3000, 0, 0), 700);
	/*engine->entityMgr->Allies[0]->aspects[3]->setCommand(patrolo);
	escorto = new Escort(engine->entityMgr->Allies[1], engine->entityMgr->playerEntity,Ogre::Vector3(-100, 0, 100));
	engine->entityMgr->Allies[1]->aspects[3]->setCommand(escorto);
	escorto = new Escort(engine->entityMgr->Allies[2], engine->entityMgr->playerEntity,Ogre::Vector3(-100, 0, -100));
	engine->entityMgr->Allies[2]->aspects[3]->setCommand(escorto);
	escorto = new Escort(engine->entityMgr->Allies[3], engine->entityMgr->playerEntity,Ogre::Vector3(-200, 0, -200));
	engine->entityMgr->Allies[3]->aspects[3]->setCommand(escorto);*/
	patrolo = new Patrol(engine->entityMgr->Enemies[0], Ogre::Vector3(-2000,0,2000), Ogre::Vector3(-2000, 0, 0), 800);
	engine->entityMgr->Enemies[0]->aspects[3]->setCommand(patrolo);
	patrolo = new Patrol(engine->entityMgr->Enemies[1], Ogre::Vector3(-2000,0,-2000), Ogre::Vector3(0, 0, -2000), 800);
	engine->entityMgr->Enemies[1]->aspects[3]->setCommand(patrolo);
	patrolo = new Patrol(engine->entityMgr->Enemies[2], Ogre::Vector3(2000,0,-2000), Ogre::Vector3(2000, 0, 0), 800);
	engine->entityMgr->Enemies[2]->aspects[3]->setCommand(patrolo);
	patrolo = new Patrol(engine->entityMgr->Enemies[3], Ogre::Vector3(2000,0,2000), Ogre::Vector3(0, 0, 2000), 800);
	engine->entityMgr->Enemies[3]->aspects[3]->setCommand(patrolo);
	//fireo = new FireBarrage(engine->entityMgr->Enemies[1], engine->entityMgr->playerEntity);
	//engine->entityMgr->Enemies[1]->aspects[3]->setCommand(fireo);
	//fireo = new FireBarrage(engine->entityMgr->Enemies[2], engine->entityMgr->playerEntity);
	//engine->entityMgr->Enemies[2]->aspects[3]->setCommand(fireo);
	//fireo = new FireBarrage(engine->entityMgr->Enemies[3], engine->entityMgr->playerEntity);
	//engine->entityMgr->Enemies[3]->aspects[3]->setCommand(fireo);
	//engine->entityMgr->Enemies[3]->aspects[3]->setCommand(escorto);
	/*engine->entityMgr->CreateEntityOfTypeAtPosition(DDG51Type, pos);
	pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition(CarrierType, pos);
	pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition(SpeedBoatType, pos);
	pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition(FrigateType, pos);
	pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition(AlienType, pos);

	pos.x = 0;
	engine->entityMgr->CreateEntityOfTypeAtPosition(BansheeType, pos);

	engine->entityMgr->SelectNextEntity(); //sets selection*/
}

