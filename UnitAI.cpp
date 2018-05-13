/*
 * UnitAI.cpp
 *
 *  Created on: Apr 2, 2018
 *      Author: enzo
 */

#include "UnitAI.h"
#include <BaseEntity.h>
#include <iostream>

UnitAI::UnitAI(BaseEntity* ent) :Aspect(ent){
	// TODO Auto-generated constructor stub
	unit = ent;
}

UnitAI::~UnitAI() {
	// TODO Auto-generated destructor stub
}

void UnitAI::Tick(float dt){
	if (!commands.empty())
	{
		commands.front()->tick(dt);
		//std::cout << "Command received" << std::endl;
		if (commands.front()->done()){
			//std::cout << unit->identity << std::endl;
			commands.pop_front();
		}

	}


}

void UnitAI::setCommand(Command *c){
	commands.clear();
	if (c->commandType == Clean){return;}
	addCommand(c);

}

void UnitAI::addCommand(Command *c){
	std::cout << "here" << std::endl;
	commands.push_back(c);
}
