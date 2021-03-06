/*
 * InputMgr.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */
#include<cfloat>

#include <Engine.h>
#include <GfxMgr.h>
#include <EntityMgr.h>
#include <InputMgr.h>
#include <EntityMgr.h>
#include <GameMgr.h>
#include <Command.h>
#include <UnitAI.h>
#include <UiMgr.h>

#include <Utils.h>

InputMgr::InputMgr(Engine *engine) : Mgr(engine), OIS::KeyListener(), OIS::MouseListener() {

	this->mInputMgr = 0;
	this->mKeyboard = 0;
	this->mMouse = 0;
	this->keyboardTimer = keyTime;
	deltaDesiredSpeed = 10.0f;
	deltaDesiredHeading = 10.0f;
	deltaDesiredAltitude = 20;
	MouseRotation = false;
	this->selectionDistanceSquaredThreshold = 10000;
}

InputMgr::~InputMgr() {

}

void InputMgr::Init(){

	  OIS::ParamList pl;
	  size_t windowHandle = 0;
	  std::ostringstream windowHandleStr;

	  engine->gfxMgr->mWindow->getCustomAttribute("WINDOW", &windowHandle);
	  windowHandleStr << windowHandle;
	  pl.insert(std::make_pair(std::string("WINDOW"), windowHandleStr.str()));
	  // insert the following lines right before calling mInputSystem = OIS::InputManager::createInputSystem( paramList );
		#if defined OIS_WIN32_PLATFORM
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
		#elif defined OIS_LINUX_PLATFORM
		pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
		pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
		//pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
		pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
		#endif

	  mInputMgr = OIS::InputManager::createInputSystem(pl);

	  mKeyboard = static_cast<OIS::Keyboard*>(
	    mInputMgr->createInputObject(OIS::OISKeyboard, true));
	  mMouse = static_cast<OIS::Mouse*>(
	    mInputMgr->createInputObject(OIS::OISMouse, true));

	  int left, top;
	  unsigned int width, height, depth;

	  engine->gfxMgr->mWindow->getMetrics(width, height, depth, left, top);
	  const OIS::MouseState &ms = mMouse->getMouseState();
	  ms.width = width;
	  ms.height = height;
	  mMouse->setEventCallback(this);
	  mKeyboard->setEventCallback(this);

}



void InputMgr::Stop(){
	if(mInputMgr){
		mInputMgr->destroyInputObject(mMouse);
		mInputMgr->destroyInputObject(mKeyboard);

		OIS::InputManager::destroyInputSystem(mInputMgr);
		mInputMgr = 0;
   	}
}

void InputMgr::Tick(float dt){

	mKeyboard->capture();
	if(mKeyboard->isKeyDown(OIS::KC_ESCAPE)){
		engine->keepRunning = false;
	}
	mMouse->capture();
//	mTrayMgr->frameRenderingQueued(fe);

	if (engine->gameMgr->levelSelect)
	{
		UpdateCamera(dt);
		UpdateVelocityAndSelection(dt);
	}
}

void InputMgr::UpdateCamera(float dt){
	float move = 400.0f;
	float rotate = 0.1f;
	float multiplier =1;

	if (mKeyboard->isKeyDown(OIS::KC_M)){
		CameraFollow = true;
	}

	 Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;
	 if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
		 multiplier = 2;
	  if (mKeyboard->isKeyDown(OIS::KC_W))
	    dirVec.z -= move * multiplier;

	  if (mKeyboard->isKeyDown(OIS::KC_S))
	    dirVec.z += move * multiplier;

	  if (mKeyboard->isKeyDown(OIS::KC_R))
	    dirVec.y += move * multiplier;

	  if (mKeyboard->isKeyDown(OIS::KC_F))
	    dirVec.y -= move * multiplier;

	  if (mKeyboard->isKeyDown(OIS::KC_A))
	  {

	      dirVec.x -= move * multiplier;
	  }

	  if (mKeyboard->isKeyDown(OIS::KC_D))
	  {

	      dirVec.x += move * multiplier;
	  }


	  if (!MouseRotation){
		  if (mKeyboard->isKeyDown(OIS::KC_Q))
			   engine->gameMgr->cameraNode->yaw(Ogre::Degree(5 * rotate * multiplier));

		  if (mKeyboard->isKeyDown(OIS::KC_E))
				   engine->gameMgr->cameraNode->yaw(Ogre::Degree(-5 * rotate * multiplier));

		  if (mKeyboard->isKeyDown(OIS::KC_Z))
				   engine->gameMgr->cameraPitchNode->pitch(Ogre::Degree(5 * rotate * multiplier));

		  if (mKeyboard->isKeyDown(OIS::KC_X))
				   engine->gameMgr->cameraPitchNode->pitch(Ogre::Degree(-5 * rotate * multiplier));

		  if ((engine->gameMgr->cameraNode->getPosition().y + dirVec.y * dt)< 5){
			  dirVec.y = 0;
		  }
	  } else {
		  engine->gameMgr->cameraNode->yaw(Ogre::Degree(-rotate*mRot.x * multiplier));
		  engine->gameMgr->cameraPitchNode->pitch(Ogre::Degree(-rotate*mRot.y * multiplier));
		  mRot.x = 0;
		  mRot.y = 0;
	  }
	  if (dirVec != Ogre::Vector3::ZERO){
		  CameraFollow = false;
	  }
	  if (CameraFollow){
			engine->gameMgr->cameraNode->setPosition(engine->entityMgr->playerEntity->CameraGimbal->_getDerivedPosition());
			engine->gameMgr->cameraNode->resetOrientation();
			engine->gameMgr->cameraNode->yaw(Ogre::Degree(-engine->entityMgr->playerEntity->heading-90));
	  }

	  engine->gameMgr->cameraNode->translate(dirVec * dt, Ogre::Node::TS_LOCAL);
}

void InputMgr::UpdateVelocityAndSelection(float dt){
	keyboardTimer -= dt;

	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD8)){
		keyboardTimer = keyTime;
		engine->entityMgr->playerEntity->desiredSpeed += deltaDesiredSpeed;
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD2)){
		keyboardTimer = keyTime;
		engine->entityMgr->playerEntity->desiredSpeed -= deltaDesiredSpeed;
	}


	/*if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD9)){
		keyboardTimer = keyTime;
		if(engine->entityMgr->selectedFlyingEntity != 0){
			engine->entityMgr->selectedFlyingEntity->desiredAltitude += deltaDesiredAltitude;
		}
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD3)){
		keyboardTimer = keyTime;
		if(engine->entityMgr->selectedFlyingEntity != 0)
			engine->entityMgr->selectedFlyingEntity->desiredAltitude -= deltaDesiredAltitude;
	}*/


	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD4)){
		keyboardTimer = keyTime;
		engine->entityMgr->playerEntity->desiredHeading -= deltaDesiredHeading;
	//turn left is decreasing degrees, turn right is increasing degrees because increasing degrees gives us the +ive Z axis
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_NUMPAD6)){
		keyboardTimer = keyTime;
		engine->entityMgr->playerEntity->desiredHeading += deltaDesiredHeading;
	}

	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_I)){
		keyboardTimer = keyTime;
		engine->entityMgr->playerEntity->desiredSpeed += deltaDesiredSpeed;
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_K)){
		keyboardTimer = keyTime;
		engine->entityMgr->playerEntity->desiredSpeed -= deltaDesiredSpeed;
	}


	/*if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_U)){
		keyboardTimer = keyTime;
		if(engine->entityMgr->selectedFlyingEntity != 0){
			engine->entityMgr->selectedFlyingEntity->desiredAltitude += deltaDesiredAltitude;
		}
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_O)){
		keyboardTimer = keyTime;
		if(engine->entityMgr->selectedFlyingEntity != 0)
			engine->entityMgr->selectedFlyingEntity->desiredAltitude -= deltaDesiredAltitude;
	}*/


	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_J)){
		keyboardTimer = keyTime;
		engine->entityMgr->playerEntity->desiredHeading -= deltaDesiredHeading;
	//turn left is decreasing degrees, turn right is increasing degrees because increasing degrees gives us the +ive Z axis
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_L)){
		keyboardTimer = keyTime;
		engine->entityMgr->playerEntity->desiredHeading += deltaDesiredHeading;
	}

	engine->entityMgr->playerEntity->desiredHeading = FixAngle(engine->entityMgr->playerEntity->desiredHeading);




	//Set velocity to zero....
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_SPACE)){
		keyboardTimer = keyTime;
		Command * cleave = new Clear(engine->entityMgr->playerEntity,Ogre::Vector3::ZERO);
		engine->entityMgr->playerEntity->aspects[3]->setCommand(cleave);
		engine->entityMgr->playerEntity->velocity = Ogre::Vector3::ZERO;
		engine->entityMgr->playerEntity->desiredSpeed = engine->entityMgr->playerEntity->speed = 0;
		engine->entityMgr->playerEntity->desiredHeading = engine->entityMgr->playerEntity->heading;
	}

	//tab handling
	/*if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_TAB)){
		keyboardTimer = keyTime;
		engine->entityMgr->SelectNextEntity();
	}*/
}

void InputMgr::LoadLevel(){

}

bool InputMgr::keyPressed(const OIS::KeyEvent& ke){
	return true;
}

bool InputMgr::keyReleased(const OIS::KeyEvent& ke){
	return true;
}

bool InputMgr::mouseMoved(const OIS::MouseEvent& me){
	if (engine->uiMgr->mTrayMgr->injectMouseMove(me)) return true;
	mRot.x = me.state.X.rel;
	mRot.y = me.state.Y.rel;
	return true;
}

bool InputMgr::mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID mid){
	std::cout << "Mouse pressed" << std::endl;
	if (engine->uiMgr->mTrayMgr->injectMouseDown(me, mid)) return true;
	if(OIS::MB_Left == mid){
		std::cout << "Left mouse press" << std::endl;
		fireAt(me);
	}
	if(OIS::MB_Right == mid){

		std::cout << "Right mouse press" << std::endl;
		positionSelection(me);
	}
	if(OIS::MB_Middle == mid){

		std::cout << "Middle mouse press" << std::endl;
		MouseRotation = true;
	}

	return true;
}

bool InputMgr::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID mid){
	if(OIS::MB_Middle == mid){

		std::cout << "Middle mouse released" << std::endl;
		MouseRotation = false;
	}
	if (engine->uiMgr->mTrayMgr->injectMouseUp(me, mid)) return true;

	return true;
}

void InputMgr::positionSelection(const OIS::MouseEvent& me) {
	const OIS::MouseState &ms = mMouse->getMouseState();
	Ogre::Ray mouseRay = engine->gfxMgr->mCamera->getCameraToViewportRay(ms.X.abs/(float) ms.width, ms.Y.abs/(float)ms.height);
	std::pair<bool, float> result = mouseRay.intersects(engine->gfxMgr->oceanSurface);
	std::cout << "Mouse pressed wow" << std::endl;
	if(result.first){

		Ogre::Vector3 posUnderMouse = mouseRay.getPoint(result.second);

		Command * Move = new MoveTo(engine->entityMgr->playerEntity,posUnderMouse);
		if(mKeyboard->isKeyDown(OIS::KC_LSHIFT))
		{
			engine->entityMgr->playerEntity->aspects[3]->addCommand(Move);
			std::cout << "Move to " << posUnderMouse << " added" << std::endl;
		}
		else
		{
			engine->entityMgr->playerEntity->aspects[3]->setCommand(Move);
			std::cout << "Move to " << posUnderMouse << " set" << std::endl;
		}


	}


}

//check if ms.width and ms.height need to be adjusted when things change
void InputMgr::fireAt(const OIS::MouseEvent &me){
	const OIS::MouseState &ms = mMouse->getMouseState();
	int index = -1;
	Ogre::Vector3 posUnderMouse;
	Ogre::Ray mouseRay = engine->gfxMgr->mCamera->getCameraToViewportRay(ms.X.abs/(float) ms.width, ms.Y.abs/(float)ms.height);
	std::pair<bool, float> result = mouseRay.intersects(engine->gfxMgr->oceanSurface);
	std::cout << mouseRay.getPoint(result.second) << std::endl;
	if(result.first){
		posUnderMouse = mouseRay.getPoint(result.second);
		float dist = posUnderMouse.distance(engine->entityMgr->playerEntity->position);
		std::cout << dist << std::endl;
		if(dist < (300*300/engine->gameMgr->gravity))
		{
			engine->entityMgr->CreateEntityOfTypeAtPosition(ShellEnt, engine->entityMgr->playerEntity, posUnderMouse);
		}

	}

}




