#ifndef __Aspect_h_
#define __Aspect_h_

#include <OgreVector3.h>
//#include <Command.h>

class BaseEntity;    //Forward declaration of the Entity381 class
class Command;

class Aspect
{
public:
  Aspect(BaseEntity* ent);
  virtual ~Aspect();

  BaseEntity* entity;

  virtual void Tick(float dt);

  virtual void addCommand(Command *c);

  virtual void setCommand(Command *c);


protected:

};



class Renderable : Aspect
{
public:
	Renderable(BaseEntity* ent);
	~Renderable();



	void Tick(float dt);
};



#endif // #ifndef __Aspect_h_
