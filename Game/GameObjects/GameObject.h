#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

typedef unsigned int uint;

class GameObject
{
	
public:
    uint posX;
    uint posY;

	GameObject()
	{}

	virtual void draw() = 0;
    virtual ~GameObject(){}
};
#endif // !GAMEOBJECT_H



