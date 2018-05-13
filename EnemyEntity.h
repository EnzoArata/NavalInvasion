/*
 * EnemyEntity.h
 *
 *  Created on: Apr 22, 2018
 *      Author: zmcilwain
 */

#ifndef INC_ENEMYENTITY_H_
#define INC_ENEMYENTITY_H_

#include <BaseEntity.h>
#include <PlayerEntity.h>
#include <BaseEntity.h>


class EnemyEntity : public PlayerEntity{

public:
	EnemyEntity(Engine *engine, Ogre::Vector3 pos, int identity);
	virtual ~EnemyEntity();

	virtual void Init();

	//void Tick(float dt);
};

class Enemy: public EnemyEntity{
public:
	Enemy(Engine *engine, Ogre::Vector3 pos, int identity);
	virtual ~Enemy();


};

#endif /* INC_ENEMYENTITY_H_ */
