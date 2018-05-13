/*
 * UiMgr.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: chad
 */

#include <UiMgr.h>
#include <Engine.h>
#include <GfxMgr.h>
#include <InputMgr.h>
#include <EntityMgr.h>
#include <Types381.h>
#include <GameMgr.h>
#include <Utils.h>

UiMgr::UiMgr(Engine* eng): Mgr(eng){
	// Initialize the OverlaySystem (changed for Ogre 1.9)
	    mOverlaySystem = new Ogre::OverlaySystem();
	    engine->gfxMgr->mSceneMgr->addRenderQueueListener(mOverlaySystem);

	    //Ogre::WindowEventUtilities::addWindowEventListener(engine->gfxMgr->ogreRenderWindow, this);
}

UiMgr::~UiMgr(){ // before gfxMgr destructor

}

void UiMgr::Init(){
	//init sdktrays

    mInputContext.mKeyboard = engine->inputMgr->mKeyboard;
    mInputContext.mMouse = engine->inputMgr->mMouse;
    mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", engine->gfxMgr->mWindow, mInputContext, this);
    //mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    //mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    //mTrayMgr->hideCursor();
}

void UiMgr::stop(){

}

void UiMgr::UpdateInfo(BaseEntity* ent){
	LabelName->setCaption(ent->name);
	LabelSpeed->setCaption(IntToString(ent->speed));
	LabelHeading->setCaption(IntToString(ent->heading));
	//mTrayMgr->
}

void UiMgr::LoadLevel(){

	mTrayMgr->showBackdrop("NAVALSTARTMENU");
	mTrayMgr->createLabel(OgreBites::TL_CENTER, "MenuText", "PreAlpha_0.03 ", 300);
	mTrayMgr->createButton(OgreBites::TL_CENTER, "startButton", "Start Game!");
	mTrayMgr->createButton(OgreBites::TL_CENTER, "quitButton", "Quit Game");



	/*
	 *
	*/
}
void UiMgr::LoadLevel1(){
	mTrayMgr->createButton(OgreBites::TL_TOPLEFT, "MyButton", "Spawn Boat!");

	Ogre::StringVector options;
	options.push_back("Select Ship");
	options.push_back("Spawn Rock");
	options.push_back("Spawn Another Ship");
	options.push_back("Spawn Enemy");
	mTrayMgr->createLongSelectMenu(OgreBites::TL_TOPRIGHT, "MyMenu", "Menu", 300, 4,options);

	mTrayMgr->showBackdrop("ECSLENT/UI");

	LabelName = mTrayMgr->createLabel(OgreBites::TL_BOTTOMLEFT,"MyName","",250);
	LabelSpeed = mTrayMgr->createLabel(OgreBites::TL_BOTTOMLEFT,"MySpeed","",250);
	LabelHeading = mTrayMgr->createLabel(OgreBites::TL_BOTTOMLEFT,"MyHeading","",250);
	LabelPosition = mTrayMgr->createLabel(OgreBites::TL_BOTTOMLEFT,"MyPosition","",250);

	//OgreBites::ProgressBar * pbar;
	pbar = mTrayMgr->createProgressBar(OgreBites::TL_TOP,"HealthBar", "Health", 300, 200);
	pbar->setProgress(100);
}

void UiMgr::Tick(float dt){
	mTrayMgr->refreshCursor();
}

void UiMgr::windowResized(Ogre::RenderWindow* rw){
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = engine->inputMgr->mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void UiMgr::windowClosed(Ogre::RenderWindow* rw){

}

bool UiMgr::keyPressed(const OIS::KeyEvent &arg) {
	std::cout << "Key Pressed: " << arg.key << std::endl;
	return true;
}
bool UiMgr::keyReleased(const OIS::KeyEvent &arg){
	return true;
}
bool UiMgr::mouseMoved(const OIS::MouseEvent &arg){
    if (mTrayMgr->injectMouseMove(arg)) return true;
	return false;
}
bool UiMgr::mousePressed(const OIS::MouseEvent &me, OIS::MouseButtonID mid) {
	std::cout << "mouse clicked" << std::endl;
	if (mTrayMgr->injectMouseDown(me, mid)) return true;
	return false;
}
bool UiMgr::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
    if (mTrayMgr->injectMouseUp(arg, id)) return true;
    /* normal mouse processing here... */
	return false;
}

void UiMgr::buttonHit(OgreBites::Button *b){

    if(b->getName()=="MyButton")
    {
        std::cout <<"Boat Spawned!" << std::endl;
        Ogre::Vector3 pos;
        pos.x = 0;
        pos.y = 0;
        pos.z = -100;
        engine->entityMgr->CreateEntityOfTypeAtPosition(ShipEnt,pos);
        return;
    }
    if(b->getName()=="startButton")
    {
		//mTrayMgr->removeWidgetFromTray("quitButton");
		mTrayMgr->clearTray(OgreBites::TL_CENTER);
		//mTrayMgr->removeWidgetFromTray("startButton");
		//mTrayMgr->clearTray(OgreBites::TL_BOTTOM);
		mTrayMgr->destroyWidget("startButton");
		mTrayMgr->destroyWidget("quitButton");
		mTrayMgr->destroyWidget("MenuText");
    	engine->gameMgr->LoadLevel1();
    	std::cout << "start button pressed" << std::endl;
    	return;
    }
    if(b->getName()=="quitButton")
   {
    	std::cout << "quit button pressed" << std::endl;
    	engine->keepRunning = false;
    	return;
   }

}

void UiMgr::itemSelected(OgreBites::SelectMenu *m){
    Ogre::Vector3 pos;
    pos.x = 0;
    pos.y = 0;
    pos.z = 100;
    switch(m->getSelectionIndex()){
    case 1:
    	engine->entityMgr->CreateEntityOfTypeAtPosition(RockEnt,pos);
    	break;
    case 2:
    	engine->entityMgr->CreateEntityOfTypeAtPosition(ShipEnt,pos);
    	break;
    case 3:
    	engine->entityMgr->CreateEntityOfTypeAtPosition(EnemyEnt,pos);
    	break;
    default:
    	break;
    }

}
