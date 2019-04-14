#include "Monster.h"
#include <iostream>
#include "task.h"

using namespace std;

Monster::Monster(uint posX, uint posY) : GameObject()
{
	this->posX = posX;
	this->posY = posY;
}

uint Monster::getPosX()
{
	return posX;
}

//-----------------------------------

uint Monster::getPosY()
{
	return posY;
}

//------------------------------------

void Monster::setPosX(uint posX)
{
    this->posX = posX;
}

//-----------------------------------

void Monster::setPosY(uint posY)
{
    this->posY = posY;
}

//-----------------------------------------

int Monster::getHealthPoints()
{
	return healthPoints;
}

//------------------------------------------------------------

void Monster::setHealthPoints(int monster_health)
{
	healthPoints = monster_health;
}

//------------------------------------------------------------
//------------------------------------------------------------

void Monster::draw()
{
#ifdef EN
    cout << posX << " " << posY << " - Monster." << endl;
#endif // EN
#ifdef RU
    cout << posX << " " << posY << " - Монстр." << endl;
#endif // RU
}


//---------------------------------------------------------------------
