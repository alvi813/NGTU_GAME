//#define _CRT_SECURE_NO_WARNINGS

#include "task.h"
#include <cstdlib>

#include "GameBoard.h"
#include "GameObject.h"
#include "Player.h"
#include "Game.h"
#include "Tree.h"
#include "Water.h"
#include "Earth.h"
#include <conio.h>
#include "Monster.h"
#include "Game.h"

#include "MonsterThread.h"
#include <QThread>
#include <QtCore/QCoreApplication>

#include <thread>
#include <chrono>
#include <QProcess>

using namespace std;


int main() {
    setlocale(LC_ALL, "ru");
    Game game;

    game.playMusic();

    const unsigned int boardX = 38;
    const unsigned int boardY = 28;
    string player_name;

    char input = 0;
    uint playerPosX = 1;
    uint playerPosY = 1;


    cout << endl;
    game.startGame();
    game.initializePlayer(player_name);

    GameBoard gameBoard(boardX, boardY);

    gameBoard.readBoardFromFile();


    Player player(player_name, playerPosX, playerPosY);

    vector<Monster*> MMonsters;
    vector<Monster*> QMonsters;

    gameBoard.createClassInstances(&MMonsters, &QMonsters);




    gameBoard.clearAndPrintBoard();
    gameBoard.setPlayerStep(playerPosX, playerPosY);
    gameBoard.informationMessages();



    //thread *MMonster_thread = new thread[MMonsters.size()];
    //uint *MMonsterPosX = new uint [MMonsters.size()];
    //uint *MMonsterPosY = new uint[MMonsters.size()];
    thread MMonsters_thread([&]()
    {

        uint MMonsterPosX;
        uint MMonsterPosY;
        while(input != 'q' || gameBoard.getPriceKey())
        {
            for (uint i = 0; i < MMonsters.size(); i++)

            {
                playerPosX = player.getPosX();
                playerPosY = player.getPosY();

                MMonsterPosX = MMonsters[i]->getPosX();
                MMonsterPosY = MMonsters[i]->getPosY();

                gameBoard.setMMonsterPosition(&MMonsterPosX, &MMonsterPosY, &MMonsters[i]->isMoveLeft);

                MMonsters[i]->setPosX(MMonsterPosX);
                MMonsters[i]->setPosY(MMonsterPosY);
                if (gameBoard.checkIsDanger(playerPosX, playerPosX))
                {
                    playerPosX = player.getBeginPosX();
                    playerPosX = player.getBeginPosX();

                    player.setPosX(playerPosX);
                    player.setPosY(playerPosY);
                }
            }
            timeDelay(5000);
        }
    });

    MMonsters_thread.detach();


    //--------------------------------------------------------

    thread QMonsters_thread([&]()
    {

        uint QMonsterPosX;
        uint QMonsterPosY;
        while(input != 'q' || gameBoard.getPriceKey())
        {
            for (uint i = 0; i < QMonsters.size(); i++)

            {
                playerPosX = player.getPosX();
                playerPosY = player.getPosY();

                QMonsterPosX = QMonsters[i]->getPosX();
                QMonsterPosY = QMonsters[i]->getPosY();

                gameBoard.setQMonsterPosition(&QMonsterPosX, &QMonsterPosY, &QMonsters[i]->isMoveUp);

                QMonsters[i]->setPosX(QMonsterPosX);
                QMonsters[i]->setPosY(QMonsterPosY);
                if (gameBoard.checkIsDanger(playerPosX, playerPosX))
                {
                    playerPosX = player.getBeginPosX();
                    playerPosX = player.getBeginPosX();

                    player.setPosX(playerPosX);
                    player.setPosY(playerPosY);
                }
            }
            timeDelay(3000);
        }
    });

    QMonsters_thread.detach();

    //--------------------------------------------------------------------

    do
    {
        playerPosX = player.getPosX();
        playerPosY = player.getPosY();

        gameBoard.setPlayerPosition(input, &playerPosX, &playerPosY, player.getBeginPosX(), player.getBeginPosY());

        if(gameBoard.getStepMistake())
        {
            mciSendString(L"play D:\\C++_NGTU\\Game\\Music\\impossibleToGo3.mp3", nullptr, 0, nullptr);
        }
        if(gameBoard.getStepDanger())
        {
            mciSendString(L"play D:\\C++_NGTU\\Game\\Music\\monster.mp3", nullptr, 0, nullptr);
        }
        player.setPosX(playerPosX);
        player.setPosY(playerPosY);

        //--------------------------
        userInput(&input);
    } while (input != 'q' || gameBoard.getPriceKey());

    //------------------------------------------------------
    system("cls");
    game.endGame();

    return 0;
}
