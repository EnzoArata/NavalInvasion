/*
 * CollisionAspect.h
 *
 *  Created on: Apr 23, 2018
 *      Author: zmcilwain
 */

#ifndef INC_COLLISIONASPECT_H_
#define INC_COLLISIONASPECT_H_


#include <Aspect.h>
#include <PlayerEntity.h>

class CollisionAspect : Aspect
{
public:
	CollisionAspect(PlayerEntity *ent);
	~CollisionAspect();

	PlayerEntity * Ship;


	void Tick(float dt);


};

#endif /* INC_COLLISIONASPECT_H_ */
