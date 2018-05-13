#ifndef __EntityMgr_h_
#define __EntityMgr_h_

#include <vector>
#include <Mgr.h>
#include <BaseEntity.h>
#include <PlayerEntity.h>
#include <EnemyEntity.h>
//#include <FlyingEntity381.h>
//#include <Types381.h>

class EntityMgr: public Mgr {
public:
  EntityMgr(Engine *engine);
  virtual ~EntityMgr();

  //Engine *engine;

  std::vector<BaseEntity*> entities;
  BaseEntity* selectedEntity;
  PlayerEntity* playerEntity;
  std::vector<EnemyEntity*> Enemies;
  //FlyingEntity381* selectedFlyingEntity;
  int selectedEntityIndex;


  //Ogre::SceneManager *sceneMgr;

  void CreateEntityOfTypeAtPosition(EntityTypes type, Ogre::Vector3 pos);
  void SelectNextEntity();
  void SetSelectedFlyingEntity();
  void Select(int index);

  void Tick(float dt);

protected:

private:
  int count;

};

#endif // #ifndef __EntityMgr_h_
