#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#pragma comment (lib, "winmm.lib")
#include <thread>
#include <conio.h>

using namespace std;

class Game
{

public:
    const wchar_t * mainMusicAdressForPlay {L"play D:\\C++_NGTU\\Game\\Music\\mainMusic.mp3 repeat"};
    const wchar_t * mainMusicAdressForPause {L"pause D:\\C++_NGTU\\Game\\Music\\mainMusic.mp3"};
    const wchar_t * mainMusicAdressForResume {L"resume D:\\C++_NGTU\\Game\\Music\\mainMusic.mp3"};


    void initializePlayer(string & name)
    {
#ifdef EN
        cout << "Enter your name: ";
#endif // EN
#ifdef RU
        cout << "ƒл€ начала игры введи своЄ им€: ";
#endif // RU
        cin >> name;
    }

    //---------------------------------------------

    void initializeGameBoard(int *X, int *Y)
    {
        int scanf_result = 0;
        do
        {
#ifdef EN
            cout << "Enter the number of game-board columns (from 5 to 30): ";
#endif // EN
#ifdef RU
            cout << "¬веди количество столбцов игрового пол€ (от 5 до 30): ";
#endif // RU

            scanf_result = scanf("%d", X);
            stdin_clear();
        } while (!scanf_result || *X < 5 || *X > 30);

        //************************************

        scanf_result = 0;
        do
        {
#ifdef EN
            cout << "Enter the number of game-board rows (from 5 to 15): ";
#endif // EN
#ifdef RU
            cout << "¬веди количество строк игрового пол€ (от 5 до 15): ";
#endif // RU

            scanf_result = scanf("%d", Y);
            stdin_clear();
        } while (!scanf_result || *Y < 5 || *Y > 15);

    }

    //-------------------------------------------------------------

    void endGame()
    {
        cout << "The END.\nGAME OVER!!!" << endl;
        system("pause");
    }

    //----------------------------------------

    void stdin_clear(void)
    {
        char c;
        do {
            c = getchar();
        } while (c != '\n'  && c != EOF);
    }

    //-----------------------------------------

    void playMusic()
    {
        // clock_t now;
        //while (true)
        // {
        //PlaySound(TEXT("D:\\C++_NGTU\\Game\\Music\\mainMusic.wav"), nullptr, SND_ASYNC|SND_LOOP);

        mciSendString(mainMusicAdressForPlay, nullptr, 0, nullptr);
        //now = clock();
        //while (clock() <= now + 142*CLOCKS_PER_SEC);
        //Sleep(3000);
        //this_thread::sleep_for(chrono::seconds(142));
        // }
    }

    void pauseMusic()
    {
        mciSendString(mainMusicAdressForPause, nullptr, 0, nullptr);
    }

    void resumeMusic()
    {
        mciSendString(mainMusicAdressForResume, nullptr, 0, nullptr);
    }

    //--------------------------------------------

    void startGame()
    {
        cout<<"Please open the console window completely, to display the playing field correctly."<<endl
           <<"In this game you need to walk on the playing field, collecting keys of different colors"<<endl
          <<"and opening the corresponding doors."<<endl
         <<"To win you need to reach the lower right corner and get the prize (P)."<<endl
        <<"To move use the arrow keys or (W-A-S-D)."<<endl
        <<"When he reached the cell J, you can jump (key J)."<<endl
        <<"When they reached the cells JJ, you will be able to jump twice higher (press N)."<<endl
        <<"When you reach the < > icon, you can move horizontally several cells at once."<<endl
        <<"To move to the left, use Z."<<endl
        <<"To move to the right, use C."<<endl
        <<"To exit the game - key Q."<<endl
        <<"In the process of movement on the field avoid monsters!!!"<<endl
        <<"Faced with a monster, you will get to the beginning of the playing field!\n"<<endl
        <<"Good luck!!!\n"<<endl;
    }
};

#endif // !GAME_H
