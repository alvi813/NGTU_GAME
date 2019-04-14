#include "Player.h"

Player::Player(string name , uint posX , uint posY ) : GameObject()
{
    this->name = name;
    this->posX = posX;
    this->posY = posY;
};


//--------------------------
uint Player::getPosX()
{
    return posX;
}

//---------------------------------------------------
uint Player::getPosY()
{
    return posY;
}
//-----------------------------------------------------------

uint Player::getBeginPosX()
{
    return beginPosX;
}

//---------------------------------------------------
uint Player::getBeginPosY()
{
    return beginPosY;
}
//-----------------------------------------------------------

void Player::setPosX(uint posX)
{
    this->posX = posX;
}
//-----------------
void Player::setPosY(uint posY)
{
    this->posY = posY;
}
//------------------------------------------------------------

//------------------------------------------------------------

void Player::draw()
{
#ifdef EN
    cout << "I'm a player " << name << " in position [" << posY << "][" << posX << "]" << endl;
#endif // EN
#ifdef RU
    cout << "Я игрок " << name << ", нахожусь в координатах [" << posY << "][" << posX << "]" << endl;
#endif // RU
}

//--------------------------------------------------------------------------------

