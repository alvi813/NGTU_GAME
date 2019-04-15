#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream>
#include <ctime>
#include <Windows.h>

#include "Monster.h"

#include <thread>
#include <chrono>
#include <mutex>

#include <vector>

using namespace std;

typedef unsigned int uint;


class GameBoard
{
private:
    uint minX {0};
    uint minY {0};
    uint maxX {};
    uint maxY {};
    char **board = nullptr;

    bool isLadderSymbol = false;
    bool isPlayerOnLadder = false;

    bool isJumpKey = false;
    bool isDoubleJumpKey = false;
    bool isFastMove = false;
    bool fastMoveProcess = false;
    bool isRedKey = false;
    bool isGreenKey = false;
    bool isBlueKey = false;
    bool isPriceKey = false;
    uint beginTextMessagesXAxis = 3;
    uint beginTextMessagesYAxis = 30;

    enum ConsoleColor {
        Black = 0,
        Blue = 1,
        Green = 2,
        Cyan = 3,
        Red = 4,
        Magenta = 5,
        Brown = 6,
        LightGray = 7,
        DarkGray = 8,
        LightBlue = 9,
        LightGreen = 10,
        LightCyan = 11,
        LightRed = 12,
        LightMagenta = 13,
        Yellow = 14,
        White = 15
    };

    enum numStepPlayerAnswer
    {
        by_default = -1,
        move_forward = 0,
        move_backward,
        move_left,
        move_right,
        step_danger,
        step_mistake,
        step_jump,
        step_fallDown
    };

    enum doors
    {
        red_door = 'R',
        green_door = 'G',
        blue_door = 'B'
    };

    enum keys
    {
        jump_key = 'J',
        doubleJump_key = '%',
        fastMove_key = '>',
        red_key = 'r',
        green_key = 'g',
        blue_key = 'b',
        price_key = 'P'
    };

    enum boardSymbols
    {
        player_symbol = '#',
        ladder_symbol = '-',
        potion_symbol = '~',
        M_monster_symbol = 'M',
        Q_monster_symbol = 'Q',
        brick_symbol = 'x',
        door_symbol = '|',
        key_symbol = 'k',
        empty_symbol = ' '
    };

    int step_player_answer = by_default;

public:

    GameBoard(uint maxX, uint maxY);
    GameBoard(const GameBoard& copyBoard);

    mutex mtx;
    mutex mtx2;
    //-------------------------------------------
    //-------------------------------------------
    uint getMaxX();
    uint getMaxY();
    uint getMinX();
    uint getMinY();
    char **getBoard();

    void createClassInstances(vector<Monster*> * mMonsters, vector<Monster*> * qMonsters);

    void readBoardFromFile();

    bool accessBoard(uint X, uint Y);
    bool getStepMistake();
    bool getStepDanger();

    bool checkIsDanger(uint X, uint Y);

    //------------------------------------------

    HANDLE consoleColors();
    HANDLE GetConsoleHandle();
    void goToXY(uint x, uint y);

    //------------------------------------------

    void musicImpossibleToGo();

    //------------------------------------------

    void setPlayerPosition(char input, uint * playerX, uint * playerY, uint beginPosPlayerX, uint beginPosPlayerY);
    void movePlayerForward(uint * playerX, uint * playerY, uint beginPosPlayerX, uint beginPosPlayerY);
    void movePlayerBackward(uint * playerX, uint * playerY, uint beginPosPlayerX, uint beginPosPlayerY);
    void movePlayerLeft(uint * playerX, uint * playerY, uint beginPosPlayerX, uint beginPosPlayerY);
    void movePlayerRight(uint * playerX, uint * playerY, uint beginPosPlayerX, uint beginPosPlayerY);
    void jumpPlayer(uint * playerX, uint * playerY, uint beginPosPlayerX, uint beginPosPlayerY);
    void doubleJumpPlayer(uint * playerX, uint * playerY, uint beginPosPlayerX, uint beginPosPlayerY);
    void playerFallDown(uint * playerX, uint * playerY, uint beginPosPlayerX, uint beginPosPlayerY);
    void FastMovePlayerLeft(uint * playerX, uint * playerY, uint beginPosPlayerX, uint beginPosPlayerY);
    void FastMovePlayerRight(uint * playerX, uint * playerY, uint beginPosPlayerX, uint beginPosPlayerY);
    void moveError();

    //-----------------------------------------------
    //-----------------------------------------------
    //-----------------------------------------------

    void setMMonsterPosition(uint * monsterX, uint * monsterY, bool * isMoveLeft);
    void setQMonsterPosition(uint * monsterX, uint * monsterY, bool * isMoveUp);

    void moveMmonsterLeft(uint * monsterX, uint * monsterY);
    void moveMmonsterRight(uint * monsterX, uint * monsterY);

    void moveQmonsterForward(uint * monsterX, uint * monsterY);
    void moveQmonsterBackward(uint * monsterX, uint * monsterY);

    void setQMonsterStepInArray(uint X, uint Y);
    void printQMonsterStep(uint X, uint Y);
    void setQMonsterStep(uint X, uint Y);

    void setMMonsterStepInArray(uint X, uint Y);
    void printMMonsterStep(uint X, uint Y);
    void setMMonsterStep(uint X, uint Y);
    //--------------------------------------------------
    //--------------------------------------------------

    void stepPlayerAnswer();

    void SetColor(int text, int background);
    void printBoard();
    void clearAndPrintBoard();

    void printGameObject(uint X, uint Y, int textColor, int backgroundColor);

    void setPlayerStepInArray(uint X, uint Y); // отрисовка шага игрока в массиве
    void printPlayerStep(uint X, uint Y); // отрисовка шага игрока в консоли
    void setPlayerStep(uint X, uint Y);
    void erasePlayerStepInArray(uint X, uint Y); // стирание шага игрока в массиве
    void printEraseStep(uint X, uint Y);
    void erasePlayerStep(uint X, uint Y);

    void eraseMonsterStepInArray(uint X, uint Y); // стирание шага монстра в массиве
    void eraseMonsterStep(uint X, uint Y);

    bool isBrick(uint X, uint Y);
    bool isLadder(uint X, uint Y);
    bool isDoor(uint X, uint Y);
    void collectKeys(uint X, uint Y);
    void openDoors(uint X, uint Y);
    void informationMessages();
    void isPlayerGetPriceKey(uint X, uint Y);
    bool getPriceKey();

    //-------------------------------------------------------
    //------------------------------------------

    ~GameBoard();
};

#endif // !GAMEBOARD_H
