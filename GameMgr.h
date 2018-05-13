/*
 * GameMgr.h
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#ifndef GAMEMGR_H_
#define GAMEMGR_H_

#include <Mgr.h>

class GameMgr: public Mgr {
public:
	GameMgr(Engine *engine);
	virtual ~GameMgr();

	void Init();
	void LoadLevel();
	void LoadLevel1();


	void MakeGround();
	void MakeSky();
	void MakeEntities();

	int levelSelect;
	Ogre::SceneNode *cameraNode;
	Ogre::SceneNode* cameraPitchNode;

};

#endif /* GAMEMGR_H_ */
