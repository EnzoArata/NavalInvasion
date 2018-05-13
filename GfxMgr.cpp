/*
 * GfxMgr.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */


#include <iostream>

#include <OgreEntity.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreException.h>
#include <OgrePlane.h>
#include <OgreMeshManager.h>

#include <Engine.h>
#include <GfxMgr.h>

GfxMgr::GfxMgr(Engine *engine): Mgr(engine) {

	mRoot = 0;
	mResourcesCfg = Ogre::StringUtil::BLANK;
	mPluginsCfg   = Ogre::StringUtil::BLANK;
	mWindow = 0;
	mSceneMgr = 0;
	mCamera = 0;
	mTerrainGroup = 0;
	mTerrainGlobals = 0;
	mTerrainsImported = 0;
	//oceanSurface(Ogre::Vector3::UNIT_Y, 0);
#ifdef _DEBUG
  mResourcesCfg = "resources_d.cfg";
  mPluginsCfg = "plugins_d.cfg";
#else
  mResourcesCfg = "resources.cfg";
  mPluginsCfg = "plugins.cfg";
#endif

  mRoot = new Ogre::Root(mPluginsCfg);

  Ogre::ConfigFile cf;
  cf.load(mResourcesCfg);

  Ogre::String name, locType;
  Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();

  while (secIt.hasMoreElements())
  {
    Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
    Ogre::ConfigFile::SettingsMultiMap::iterator it;

    for (it = settings->begin(); it != settings->end(); ++it)
    {
      locType = it->first;
      name = it->second;

      Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
    }
  }

  if (!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
	  std::cerr << "Could not find Config File and could not show Config Dialog" << std::endl;

  mWindow = mRoot->initialise(true, "CS381 Game Engine Version 1.0");



  mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

  mCamera = mSceneMgr->createCamera("MainCam");
  //mCamera->setPosition(0, 200, 80);
  //mCamera->lookAt(0, 150, -300);
  mCamera->setNearClipDistance(5);

  Ogre::Viewport* vp = mWindow->addViewport(mCamera);
  vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

  mCamera->setAspectRatio(
    Ogre::Real(vp->getActualWidth()) /
    Ogre::Real(vp->getActualHeight()));

  //-----------------------------------------------------------------------
  Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
}

GfxMgr::~GfxMgr() {

	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);
	delete mRoot;
}

void GfxMgr::Init(){

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
  //mRoot->addFrameListener(this);
  //mRoot->startRendering();


}


void GfxMgr::MakeSky(){
	engine->gfxMgr->mSceneMgr->setSkyBox(true, "Examples/StormySkyBox");
}

void GfxMgr::MakeGround(){

	//Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	//Ogre::Plane oceanSurface(Ogre::Vector3::UNIT_Y, 0);
	//oceanSurface = plane;
	oceanSurface.normal = oceanFloor.normal = Ogre::Vector3::UNIT_Y;
	oceanSurface.d = 0;
	oceanFloor.d = 300;
	Ogre::MeshManager::getSingleton().createPlane(
		"ocean",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		//plane,
		oceanSurface,
		15000, 15000, 20, 20,
		true,
		1, 5, 5,
		Ogre::Vector3::UNIT_Z);

	Ogre::Entity* OceanEntity = engine->gfxMgr->mSceneMgr->createEntity("ocean");
	engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(OceanEntity);
	OceanEntity->setCastShadows(false);
	//groundEntity->setMaterialName("Ocean2_HLSL_GLSL");
	//groundEntity->setMaterialName("OceanHLSL_GLSL");
	//groundEntity->setMaterialName("Ocean2_Cg");
	//groundEntity->setMaterialName("NavyCg");
	OceanEntity->setMaterialName("Examples/Water2");


	/*Ogre::MeshManager::getSingleton().createPlane(
		"floor",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		//plane,
		oceanFloor,
		15000, 15000, 20, 20,
		true,
		1, 5, 5,
		Ogre::Vector3::UNIT_Z);

	Ogre::Entity* groundEntity = engine->gfxMgr->mSceneMgr->createEntity("floor");
	engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	//groundEntity->setCastShadows(false);
	groundEntity->setMaterialName("Examples/Rocky");*/


	  mSceneMgr->setAmbientLight(Ogre::ColourValue(.2, .2, .2));

	  Ogre::Vector3 lightDir(.55, -.3, .75);
	  lightDir.normalise();

	  Ogre::Light* light = mSceneMgr->createLight("TestLight");
	  light->setType(Ogre::Light::LT_DIRECTIONAL);
	  light->setDirection(lightDir);
	  light->setDiffuseColour(Ogre::ColourValue::White);
	  light->setSpecularColour(Ogre::ColourValue(.4, .4, .4));

	// Fog
	  Ogre::ColourValue fadeColour(.8, .8, .9);
	  mWindow->getViewport(0)->setBackgroundColour(fadeColour);

	  mSceneMgr->setFog(Ogre::FOG_EXP2, fadeColour, 0.00007, 500 , 1000);

	  // Terrain
	  mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();

	  mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(
	    mSceneMgr,
	    Ogre::Terrain::ALIGN_X_Z,
	    513, 12000.0);
	  mTerrainGroup->setFilenameConvention(Ogre::String("terrain"), Ogre::String("dat"));
	  mTerrainGroup->setOrigin(Ogre::Vector3(0,-500,0));

	  configureTerrainDefaults(light);

	  for (long x = 0; x <= 0; ++x)
	    for (long y = 0; y <= 0; ++y)
	      defineTerrain(x, y);

	  mTerrainGroup->loadAllTerrains(true);

	  if (mTerrainsImported)
	  {
	    Ogre::TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();

	    while (ti.hasMoreElements())
	    {
	      Ogre::Terrain* t = ti.getNext()->instance;
	      initBlendMaps(t);
	    }
	  }

	  mTerrainGroup->freeTemporaryResources();

}


void GfxMgr::windowClosed(Ogre::RenderWindow *rw){
	mRoot->shutdown();
	engine->keepRunning = false;
}

bool GfxMgr::frameRenderingQueued(const Ogre::FrameEvent& fe){
	if(mWindow->isClosed()) return false;
	return true;
}


void GfxMgr::LoadLevel(){

}

void GfxMgr::Stop(){
	mRoot->shutdown();
}

void GfxMgr::Tick(float dt){
//call ogre root render one frame method
	mRoot->renderOneFrame(dt);
	Ogre::WindowEventUtilities::messagePump();
}

void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img)
{
  img.load("terrain.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

  if (flipX)
    img.flipAroundY();
  if (flipY)
    img.flipAroundX();

}

void GfxMgr::defineTerrain(long x, long y)
{
  Ogre::String filename = mTerrainGroup->generateFilename(x, y);

  bool exists =
    Ogre::ResourceGroupManager::getSingleton().resourceExists(
      mTerrainGroup->getResourceGroup(),
      filename);

  if (exists)
    mTerrainGroup->defineTerrain(x, y);
  else
  {
    Ogre::Image img;
    getTerrainImage(x % 2 != 0, y % 2 != 0, img);
    mTerrainGroup->defineTerrain(x, y, &img);

    mTerrainsImported = true;
  }
}

void GfxMgr::initBlendMaps(Ogre::Terrain* terrain)
{
  Ogre::Real minHeight0 = 70;
  Ogre::Real fadeDist0 = 40;
  Ogre::Real minHeight1 = 70;
  Ogre::Real fadeDist1 = 15;

  Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
  Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);

  float* pBlend0 = blendMap0->getBlendPointer();
  float* pBlend1 = blendMap1->getBlendPointer();

  for (Ogre::uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y)
  {
    for (Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
    {
      Ogre::Real tx, ty;

      blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
      Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);
      Ogre::Real val = (height - minHeight0) / fadeDist0;
      val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
      *pBlend0++ = val;

      val = (height - minHeight1) / fadeDist1;
      val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
      *pBlend1++ = val;
    }
  }

  blendMap0->dirty();
  blendMap1->dirty();
  blendMap0->update();
  blendMap1->update();

}

void GfxMgr::configureTerrainDefaults(Ogre::Light* light)
{
  mTerrainGlobals->setMaxPixelError(8);
  mTerrainGlobals->setCompositeMapDistance(3000);

  mTerrainGlobals->setLightMapDirection(light->getDerivedDirection());
  mTerrainGlobals->setCompositeMapAmbient(mSceneMgr->getAmbientLight());
  mTerrainGlobals->setCompositeMapDiffuse(light->getDiffuseColour());

  Ogre::Terrain::ImportData& importData = mTerrainGroup->getDefaultImportSettings();
  importData.terrainSize = 513;
  importData.worldSize = 12000.0;
  importData.inputScale = 600;
  importData.minBatchSize = 33;
  importData.maxBatchSize = 65;

  importData.layerList.resize(3);
  importData.layerList[0].worldSize = 100;
  importData.layerList[0].textureNames.push_back(
    "dirt_grayrocky_diffusespecular.dds");
  importData.layerList[0].textureNames.push_back(
    "dirt_grayrocky_normalheight.dds");
  importData.layerList[1].worldSize = 30;
  importData.layerList[1].textureNames.push_back(
    "grass_green-01_diffusespecular.dds");
  importData.layerList[1].textureNames.push_back(
    "grass_green-01_normalheight.dds");
  importData.layerList[2].worldSize = 200;
  importData.layerList[2].textureNames.push_back(
    "growth_weirdfungus-03_diffusespecular.dds");
  importData.layerList[2].textureNames.push_back(
    "growth_weirdfungus-03_normalheight.dds");

}
