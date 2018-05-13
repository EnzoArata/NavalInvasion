/*
 * GfxMgr.h
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#ifndef GFXMGR_H_
#define GFXMGR_H_

#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>
#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>



#include <Mgr.h>


class GfxMgr:
		public Mgr,
		public Ogre::WindowEventListener,
		public Ogre::FrameListener {
public:
	GfxMgr(Engine *engine);
	virtual ~GfxMgr();

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);
	virtual void windowClosed(Ogre::RenderWindow* rw);
//---------------
	void Init();
	void LoadLevel();
	void Tick(float dt);
	void Stop();

	void MakeGround();
	Ogre::Plane oceanSurface;
	Ogre::Plane oceanFloor;
	void MakeSky();

	void defineTerrain(long x, long y);
	void initBlendMaps(Ogre::Terrain* terrain);
	void configureTerrainDefaults(Ogre::Light* light);

	bool mTerrainsImported;
	Ogre::TerrainGroup* mTerrainGroup;
	Ogre::TerrainGlobalOptions* mTerrainGlobals;

	//OgreBites::Label* mInfoLabel;

	//Ogre related stuff
	Ogre::Root* mRoot;
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;
	Ogre::RenderWindow* mWindow;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;

};

#endif /* GFXMGR_H_ */
