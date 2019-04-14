#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "GameObject.h"
#include "task.h"
#include "GameBoard.h"

using namespace std;

typedef unsigned int uint;

class Player : private GameObject
{
private:

	string name;

    uint beginPosX = 1;
    uint beginPosY = 1;

public:
    Player(string name = "Noname", uint posX = 0, uint posY = 0) ;
    virtual ~Player(){}

	//-----------------------
	
    uint getPosX(void);
    uint getPosY(void);
    uint getBeginPosX(void);
    uint getBeginPosY(void);
	
    void setPosX(uint posX);
    void setPosY(uint posY);
	
    virtual void draw(void);
	
};

#endif // !PLAYER_H
