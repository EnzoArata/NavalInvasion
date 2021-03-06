/*
 * UnitAI.h
 *
 *  Created on: Mar 28, 2018
 *      Author: sushil
 */

#ifndef UNITAI_H_
#define UNITAI_H_

#include <Aspect.h>
#include <Command.h>
#include <list>

class UnitAI: public Aspect {

public:

	std::list<Command*> commands;

	UnitAI(BaseEntity* ent);
	~UnitAI();

	void Tick(float dt);
	void setCommand(Command *c);
	void virtual addCommand(Command *c);
	void insertCommand(Command *c);

	BaseEntity* unit;

};





#endif /* UNITAI_H_ */
