#ifndef MONSTER_H
#define MONSTER_H

const int HEALTH = 50;
#include "GameObject.h"

class Monster : private GameObject
{
private:
	int healthPoints = HEALTH; // здоровье

public:
	
    Monster(uint posX=1, uint posY=1);
    virtual ~Monster(){}

	//----------------------------------

    uint getPosX();
    uint getPosY();
	int getHealthPoints();

    void setPosX(uint posX);
    void setPosY(uint PosY);
	void setHealthPoints(int monster_health);
    void move();

    bool isMoveUp = false;
    bool isMoveLeft = false;

	virtual void draw();
	int fight(int player_health, int damageFromPlayer);

    //-------------------------------------------------
	
};

#endif // !MONSTER_H



