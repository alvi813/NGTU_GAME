#define _CRT_SECURE_NO_WARNINGS  //for fopen()

#include "GameBoard.h"
#include "Monster.h"
#include "task.h"
#include <cstdio>
#include <stdlib.h>
#include <cstring>
#include <cctype> // for (isdigit)
#include <conio.h>



GameBoard::GameBoard(uint maxX, uint maxY)
    :maxX(maxX),
      maxY(maxY)
{
    board = new char *[maxY];
    for (uint i = 0; i < maxY; i++)
    {
        board[i] = new char[maxX];
    }
}

//--------------------------------------------

GameBoard::GameBoard(const GameBoard& copyBoard)
{
    if(copyBoard.board != nullptr)
    {
        board = new char *[maxY];
        for (uint i = 0; i < maxY; i++)
        {
            board[i] = new char[maxX];
            //strcpy(board, copyBoard.board);
        }
    }
}

//-------------------------------------------------------------------

//-------------------------------------------

uint GameBoard::getMaxX()
{
    return maxX;
}

//-------------------------------------------

uint GameBoard::getMaxY()
{
    return maxY;
}

//------------------------------------------

uint GameBoard::getMinX()
{
    return minX;
}

//------------------------------------------

uint GameBoard::getMinY()
{
    return minY;
}

//------------------------------------------

char ** GameBoard::getBoard()
{
    return board;
}

//---------------------------------------------------

void GameBoard::readBoardFromFile()
{
    int rowNum = 0;
    const int strInLen = 40;  // maxX + 2 = 38+2 = 38 --->( /n + /0 );
    char strIn[strInLen] = {'\0'};
    FILE *fpIn = fopen("D:\\C++_NGTU\\Game\\Game\\textFiles\\gameBoard.txt", "r");
    if (fpIn == nullptr)
        puts("File error!");

    while (fgets(strIn, strInLen, fpIn) != nullptr)   // char * fgets( char * string, int num, FILE * filestream );
    {
        if (strIn[strlen(strIn) - 1] == '\n')
            strIn[strlen(strIn) - 1] = '\0';
        for (uint i = 0; i < maxX; i++)
            board[rowNum][i] = strIn[i];
        rowNum++;
    }
}

//-----------------------------------------------------------------------

void GameBoard::createClassInstances(vector<Monster*> * mMonsters, vector<Monster*> * qMonsters)
{
    //int m = 0;
    //int q = 0;
    for(uint y = 0; y < maxY; y++)
        for(uint x = 0; x < maxX; x++)
        {
            if(board[y][x] == Q_monster_symbol)
            {
                Monster *monster = new Monster(x, y);
                qMonsters->push_back(monster);
                //q++;
            }
            else if(board[y][x] == M_monster_symbol)
            {
                Monster *monster = new Monster(x, y);
                mMonsters->push_back(monster);
                //m++;
                //cout << y << " " << x<<endl;
            }
        }
    //cout << m <<" " << q;

    //Sleep(5000);
}

//-----------------------------------------------------------------------

bool GameBoard::accessBoard(uint X, uint Y)
{
    if(board[Y][X] == brick_symbol) return false;
    else if(board[Y][X] == red_door) return isRedKey;
    else if(board[Y][X] == green_door) return isGreenKey;
    else if(board[Y][X] == blue_door) return isBlueKey;
    else return true;
}



HANDLE GameBoard::GetConsoleHandle()
{
    return GetStdHandle(STD_OUTPUT_HANDLE);
}

//-------

void GameBoard::goToXY(uint x, uint y)
{
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetConsoleHandle(), coord);

    CONSOLE_CURSOR_INFO cci;

    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cci);
    cci.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cci);
}

//------------------------------------------------------------------------

void GameBoard::printGameObject(uint X, uint Y, int textColor, int backgroundColor)
{
    lock_guard<mutex> guard (mtx2);
    //mtx2.lock();
    //***
    CONSOLE_SCREEN_BUFFER_INFO start_attribute;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &start_attribute); // исходный цвет консоли / the original color of the console

    SetColor(textColor, backgroundColor); // изменяем цвет, функцию SetColor() пишем отдельно / change the color, SetColor() function write separately

    goToXY(X*3+2, Y+1); // because of format: X*3 is "%2c " of each step in X-axis; and +2 is "%2c" - the position of the player
    printf("%2c ",board[Y][X]);

    SetConsoleTextAttribute(hConsole, start_attribute.wAttributes); // возвращаем исходный цвет консоли / return the original color of the console
    //***
    //mtx2.unlock();
}

//----------------------------------------------------------------------------

void GameBoard::setPlayerStepInArray(uint X, uint Y) // отрисовка шага игрока в массиве
{
    board[Y][X] = player_symbol;
}

//---------

void GameBoard::printPlayerStep(uint X, uint Y) // отрисовка шага игрока на экране
{
    printGameObject(X, Y, Yellow, Black);
}

//--------

void GameBoard::setPlayerStep(uint X, uint Y) // ф-ция комбинирует отрисовку шага игрока в массиве и на экране
{
    setPlayerStepInArray(X, Y);
    printPlayerStep(X, Y);
}


//------------------------------------------------------------------

void GameBoard::setQMonsterStepInArray(uint X, uint Y)
{
    board[Y][X] = Q_monster_symbol;
}

//---------

void GameBoard::printQMonsterStep(uint X, uint Y)
{
    printGameObject(X, Y, Blue, Black);
}

//---------

void GameBoard::setQMonsterStep(uint X, uint Y)
{
    setQMonsterStepInArray(X, Y);
    printQMonsterStep(X, Y);
}

//-----------------------------------------------------------------

void GameBoard::setMMonsterStepInArray(uint X, uint Y)
{
    board[Y][X] = M_monster_symbol;
}

//---------
void GameBoard::printMMonsterStep(uint X, uint Y)
{
    printGameObject(X, Y, LightRed, Black);
}

//---------

void GameBoard::setMMonsterStep(uint X, uint Y)
{
    setMMonsterStepInArray(X, Y);
    printMMonsterStep(X, Y);
}

//------------------------------------------------------------------

void GameBoard::erasePlayerStepInArray(uint X, uint Y) // стирание шага игрока в массиве
{
    isPlayerOnLadder ? board[Y][X]=ladder_symbol : board[Y][X]=empty_symbol;
}

//----------

void GameBoard::printEraseStep(uint X, uint Y) // отрисовка стирания шага на экране
{
    printGameObject(X, Y, DarkGray, Black);
}

//----------

void GameBoard::erasePlayerStep(uint X, uint Y) // ф-ция стирания шага (комбинирует массив и экран)
{
    erasePlayerStepInArray(X, Y);
    printEraseStep(X, Y);
}

//-----------------------------------------------------------------

void GameBoard::eraseMonsterStepInArray(uint X, uint Y)
{
    board[Y][X]=empty_symbol;
}
//------------------------------------

void GameBoard::eraseMonsterStep(uint X, uint Y)
{
    eraseMonsterStepInArray(X, Y);
    printEraseStep(X, Y);
}

//-------------------------------------

void GameBoard::SetColor(int text, int background)
{
    /*Получение дескриптора / Getting a descriptor*/
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD)((background << 4) | text));
}

//----------------------------------------------------------------------------


void GameBoard::printBoard()
{
    CONSOLE_SCREEN_BUFFER_INFO start_attribute;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &start_attribute); // исходный цвет консоли / the original color of the console
    //*****************************************************************

    putchar('\n');

    // print coordinate axis X
    /*
 *   ---
 *  printf("%2c ", ' ');
 *  for (uint i = 0; i < maxX; i++)
 *  {
 *      printf("%2d ", i);
 *  }
 *  putchar('\n');
 *  ---
*/
    //*******************************

    int k = 0; // counter for coordinate axis Y
    for (uint i = 0; i < maxY; i++)
    {
        //---printf("%2d ", k); // for print coordinate axis Y
        printf("%c ", ' ');

        for (uint j = 0; j < maxX; j++)
            if (board[i][j] == brick_symbol)
            {
                //printf(" ");
                SetColor(Black, Brown); // изменяем цвет, функцию SetColor() пишем отдельно / change the color, SetColor() function write separately
                printf("%2c ", board[i][j]);
                SetConsoleTextAttribute(hConsole, start_attribute.wAttributes); // возвращаем исходный цвет консоли / return the original color of the console
                // printf(" ");
            }
            else if (board[i][j] == ladder_symbol)
            {
                SetColor(DarkGray, Black); // изменяем цвет, функцию SetColor() пишем отдельно / change the color, SetColor() function write separately
                printf("%2c ", board[i][j]);
                SetConsoleTextAttribute(hConsole, start_attribute.wAttributes); // возвращаем исходный цвет консоли / return the original color of the console
            }
            else if (board[i][j] == M_monster_symbol)
            {
                SetColor(LightRed, Black); // изменяем цвет, функцию SetColor() пишем отдельно / change the color, SetColor() function write separately
                printf("%2c ", board[i][j]);
                SetConsoleTextAttribute(hConsole, start_attribute.wAttributes); // возвращаем исходный цвет консоли / return the original color of the console
            }
            else if (board[i][j] == Q_monster_symbol)
            {
                SetColor(Blue, Black); // изменяем цвет, функцию SetColor() пишем отдельно / change the color, SetColor() function write separately
                printf("%2c ", board[i][j]);
                SetConsoleTextAttribute(hConsole, start_attribute.wAttributes); // возвращаем исходный цвет консоли / return the original color of the console
            }
            else if (board[i][j] == potion_symbol)
            {
                SetColor(LightGreen, Blue); // изменяем цвет, функцию SetColor() пишем отдельно / change the color, SetColor() function write separately
                printf("%2c ", board[i][j]);
                SetConsoleTextAttribute(hConsole, start_attribute.wAttributes); // возвращаем исходный цвет консоли / return the original color of the console
            }
            else if (board[i][j] == red_door)
            {
                printf(" ");
                SetColor(Black, Red); // изменяем цвет, функцию SetColor() пишем отдельно / change the color, SetColor() function write separately
                printf("%c", door_symbol);
                SetConsoleTextAttribute(hConsole, start_attribute.wAttributes); // возвращаем исходный цвет консоли / return the original color of the console
                printf(" ");
            }
            else if (board[i][j] == green_door)
            {
                printf(" ");
                SetColor(Black, Green); // изменяем цвет, функцию SetColor() пишем отдельно / change the color, SetColor() function write separately
                printf("%c", door_symbol);
                SetConsoleTextAttribute(hConsole, start_attribute.wAttributes); // возвращаем исходный цвет консоли / return the original color of the console
                printf(" ");
            }
            else if (board[i][j] == blue_door)
            {
                printf(" ");
                SetColor(Black, Blue); // изменяем цвет, функцию SetColor() пишем отдельно / change the color, SetColor() function write separately
                printf("%c", door_symbol);
                SetConsoleTextAttribute(hConsole, start_attribute.wAttributes); // возвращаем исходный цвет консоли / return the original color of the console
                printf(" ");
            }
            else if (board[i][j] == red_key)
            {
                SetColor(Black, Red); // изменяем цвет, функцию SetColor() пишем отдельно / change the color, SetColor() function write separately
                printf("%2c ", key_symbol);
                SetConsoleTextAttribute(hConsole, start_attribute.wAttributes); // возвращаем исходный цвет консоли / return the original color of the console
            }
            else if (board[i][j] == green_key)
            {
                SetColor(Black, Green); // изменяем цвет, функцию SetColor() пишем отдельно / change the color, SetColor() function write separately
                printf("%2c ", key_symbol);
                SetConsoleTextAttribute(hConsole, start_attribute.wAttributes); // возвращаем исходный цвет консоли / return the original color of the console
            }
            else if (board[i][j] == blue_key)
            {
                SetColor(Black, Blue); // изменяем цвет, функцию SetColor() пишем отдельно / change the color, SetColor() function write separately
                printf("%2c ", key_symbol);
                SetConsoleTextAttribute(hConsole, start_attribute.wAttributes); // возвращаем исходный цвет консоли / return the original color of the console
            }
            else if (board[i][j] == price_key)
            {
                SetColor(White, LightMagenta); // изменяем цвет, функцию SetColor() пишем отдельно / change the color, SetColor() function write separately
                printf("%2c ", price_key);
                SetConsoleTextAttribute(hConsole, start_attribute.wAttributes); // возвращаем исходный цвет консоли / return the original color of the console
            }
            else if (board[i][j] == jump_key)
            {
                SetColor(Black, Magenta); // изменяем цвет, функцию SetColor() пишем отдельно / change the color, SetColor() function write separately
                printf("%2c ", jump_key);
                SetConsoleTextAttribute(hConsole, start_attribute.wAttributes); // возвращаем исходный цвет консоли / return the original color of the console
            }
            else if (board[i][j] == doubleJump_key)
            {
                SetColor(Black, Magenta); // изменяем цвет, функцию SetColor() пишем отдельно / change the color, SetColor() function write separately
                printf("%2s ", "JJ");
                SetConsoleTextAttribute(hConsole, start_attribute.wAttributes); // возвращаем исходный цвет консоли / return the original color of the console
            }
            else if (board[i][j] == fastMove_key)
            {
                SetColor(Black, Magenta); // изменяем цвет, функцию SetColor() пишем отдельно / change the color, SetColor() function write separately
                printf("%2s ", "<>");
                SetConsoleTextAttribute(hConsole, start_attribute.wAttributes); // возвращаем исходный цвет консоли / return the original color of the console
            }
            else
                printf("%2c ", board[i][j]);
        putchar('\n');
        k++;
    }
    putchar('\n');
}

//-----------------------------------------------------------------------------
void GameBoard::clearAndPrintBoard()
{
    mtx.lock();
    system("cls");
    printBoard();
    mtx.unlock();
}

//--------------------------------------------------------------
//--------------------------------------------------------------

bool GameBoard::checkIsDanger(uint X, uint Y)
{
    return((board[Y][X] == M_monster_symbol ||
            board[Y][X] == Q_monster_symbol ||
            board[Y][X] == potion_symbol)? true : false);
}

//---------------------------------------------------------------

bool GameBoard::isBrick(uint X, uint Y)
{
    return(board[Y][X] == brick_symbol ? true : false);
}

//---------------------------------------------------------------

bool GameBoard::isLadder(uint X, uint Y)
{
    return (isLadderSymbol = (board[Y][X]==ladder_symbol ? true : false));
}

//---------------------------------------------------------------

void GameBoard::collectKeys(uint X, uint Y)
{
    if(board[Y][X] == jump_key)
    {    isJumpKey = true;
        numberOfHelpMessages++;
        goToXY(beginTextMessagesXAxis, beginTextMessagesYAxis + numberOfHelpMessages); // 3 Y-axis; 30 X-axis
        printf("%s", "J - jump;");
    }
    else if(board[Y][X] == doubleJump_key)
    {
        isDoubleJumpKey = true;
        numberOfHelpMessages++;
        goToXY(beginTextMessagesXAxis, beginTextMessagesYAxis + numberOfHelpMessages);
        printf("%s", "N - double jump;");
    }
    else if(board[Y][X] == fastMove_key)
    {
        isFastMove = true;
        numberOfHelpMessages++;
        goToXY(beginTextMessagesXAxis, beginTextMessagesYAxis + numberOfHelpMessages);
        printf("%s", "Z - fast move left;");
        numberOfHelpMessages++;
        goToXY(beginTextMessagesXAxis, beginTextMessagesYAxis + numberOfHelpMessages);
        printf("%s", "C - fast move right.");
    }
    else if(board[Y][X] == red_key)
    {
        isRedKey = true;
        numberOfHelpMessages++;
        goToXY(beginTextMessagesXAxis, beginTextMessagesYAxis + numberOfHelpMessages);
        printf("%s", "Now you can open the red door.         ");
    }
    else if(board[Y][X] == green_key)
    {
        isGreenKey = true;
        numberOfHelpMessages++;
        goToXY(beginTextMessagesXAxis, beginTextMessagesYAxis + numberOfHelpMessages);
        printf("%s", "Now you can open the green door.       ");
    }
    else if(board[Y][X] == blue_key)
    {
        isBlueKey = true;
        numberOfHelpMessages++;
        goToXY(beginTextMessagesXAxis, beginTextMessagesYAxis + numberOfHelpMessages);
        printf("%s", "Now you can open the blue door.        ");
    }
    else if(board[Y][X] == price_key)
        isPriceKey = true;
}

//------------------------------------------------

void GameBoard::openDoors(uint X, uint Y)
{
    if(board[Y][X] == red_door)
    {
        numberOfHelpMessages++;
        goToXY(beginTextMessagesXAxis, beginTextMessagesYAxis + numberOfHelpMessages);
        printf("%s", "You open the red door!!!                ");
    }
    if(board[Y][X] == green_door)
    {
        numberOfHelpMessages++;
        goToXY(beginTextMessagesXAxis, beginTextMessagesYAxis + numberOfHelpMessages);
        printf("%s", "You open the green door!!!              ");
    }
    if(board[Y][X] == blue_door)
    {
        numberOfHelpMessages++;
        goToXY(beginTextMessagesXAxis, beginTextMessagesYAxis + numberOfHelpMessages);
        printf("%s", "You open the blue door!!!               ");
    }
}

//------------------------------------------------

void GameBoard::informationMessages()
{
    goToXY(beginTextMessagesXAxis, beginTextMessagesYAxis);
    printf("%s", "Q - to exit the game;                ");
}

bool GameBoard::isDoor(uint X, uint Y)
{
    return ((board[Y][X] == red_door ||
             board[Y][X] == green_door ||
             board[Y][X] == blue_door) ? true : false);
}

void GameBoard::isPlayerGetPriceKey(uint X, uint Y)
{
    if(board[Y][X] == price_key)
        isPriceKey = true;
}

bool GameBoard::getPriceKey()
{
    return isPriceKey;
}

void GameBoard::musicImpossibleToGo()
{
    PlaySound(TEXT("D:\\C++_NGTU\\Game\\Music\\impossibleToGo.wav"), nullptr, SND_FILENAME | SND_ASYNC);
    Sleep(200);
}

void GameBoard::setPlayerPosition(char input, uint * playerX, uint * playerY, uint beginPosPlayerX, uint beginPosPlayerY)
{
    switch (input)
    {
    case 72: // '72' - code of the up arrow ('H')
    case 'w':
    case 'W':
    case (char)150: //Ц
    case (char)230: //ц
        if(isLadder(*playerX, *playerY - 1) || isPlayerOnLadder)
        {
            erasePlayerStep(*playerX, *playerY);
            movePlayerForward(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
            setPlayerStep(*playerX, *playerY);
        }
        break;

    case 80: // '80' - code of the down arrow ('P')
    case 's':
    case 'S':
    case (char)155: //Ы
    case (char)235: //ы
        if(isLadder(*playerX, *playerY + 1))
        {
            erasePlayerStep(*playerX, *playerY);
            movePlayerBackward(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
            setPlayerStep(*playerX, *playerY);
        }
        else
        {
            playerFallDown(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
        }
        break;

    case 75: // '75' - code of the left arrow ('K')
    case 'a':
    case 'A':
    case (char)148: //Ф
    case (char)228: //ф
        erasePlayerStep(*playerX, *playerY);
        movePlayerLeft(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
        setPlayerStep(*playerX, *playerY);
        break;

    case 77: // '77' - code of the right arrow ('M')
    case 'd':
    case 'D':
    case (char)130: //В
    case (char)162: //в
        erasePlayerStep(*playerX, *playerY);
        movePlayerRight(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
        setPlayerStep(*playerX, *playerY);
        break;

    case 'J':
    case 'j':
    case (char)142: //О
    case (char)174: //о
        if(isJumpKey)
        {
            erasePlayerStep(*playerX, *playerY);
            jumpPlayer(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
            setPlayerStep(*playerX, *playerY);
        }
        break;

    case 'N':
    case 'n':
    case (char)146: //О
    case (char)226: //о
        if(isDoubleJumpKey)
        {
            erasePlayerStep(*playerX, *playerY);
            doubleJumpPlayer(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
            setPlayerStep(*playerX, *playerY);
        }
        break;


    case 'Z':
    case 'z':
    case (char)159: //Я
    case (char)239: //я
        if(isFastMove)
        {
            erasePlayerStep(*playerX, *playerY);
            FastMovePlayerLeft(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
            setPlayerStep(*playerX, *playerY);
        }
        break;

    case 'C':
    case 'c':
    case (char)145: //Я
    case (char)225: //я
        if(isFastMove)
        {
            erasePlayerStep(*playerX, *playerY);
            FastMovePlayerRight(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
            setPlayerStep(*playerX, *playerY);
        }
        break;


    default:
        moveError();
        break;
    }
}

//-------------------------------------------------------------

void GameBoard::jumpPlayer(uint * playerX, uint * playerY, uint beginPosPlayerX, uint beginPosPlayerY)
{
    int isEnterAnything = 0;
    char symb;
    step_player_answer = by_default;
    int i = 0;

    while(i < 2)
    {
        if(isLadder(*playerX, *playerY - 1))
        {
            erasePlayerStep(*playerX, *playerY);
            movePlayerForward(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
            setPlayerStep(*playerX, *playerY);
            break;
        }
        else
        {
            erasePlayerStep(*playerX, *playerY);
            movePlayerForward(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
            setPlayerStep(*playerX, *playerY);
            i++;
            timeDelay(50);
        }
    }

    timeDelay(90);

    isEnterAnything = _kbhit();

    if (isEnterAnything)
    {
        symb = (char)_getch(); // code 224
        //(Для управляющий клавиши передается 2 байта. Первый код, который читается, равен 224)
        //(For the control key, 2 bytes are sent. The first code that is read is 224)

        if (symb == (char)224)
            symb = (char)_getch();
        else
            (char)_getch();


        if((symb == 'a') ||
                (symb == 'A') ||
                (symb == 75) ||         // '75' - code of the left arrow ('K')
                (symb == (char)148) ||  //Ф
                (symb == (char)228))    //ф
        {
            timeDelay(50);
            erasePlayerStep(*playerX, *playerY);
            movePlayerLeft(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
            setPlayerStep(*playerX, *playerY);
        }
        else if((symb == 'd') ||
                (symb == 'D') ||
                (symb == 77) ||         // '77' - code of the right arrow ('M')
                (symb == (char)130) ||  //В
                (symb == (char)162))    //в
        {
            timeDelay(50);
            erasePlayerStep(*playerX, *playerY);
            movePlayerRight(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
            setPlayerStep(*playerX, *playerY);
        }
        else if((symb == 'Z') ||
                (symb == 'z') ||
                (symb == (char)159) || //Я
                (symb == (char)239))   //я
        {
            if(isFastMove)
            {
                timeDelay(50);
                erasePlayerStep(*playerX, *playerY);
                FastMovePlayerLeft(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
                setPlayerStep(*playerX, *playerY);
            }
        }

        else if((symb == 'c') ||
                (symb == 'C') ||
                (symb == (char)145) ||  //В
                (symb == (char)225))    //в
        {
            if(isFastMove)
            {
                timeDelay(70);
                erasePlayerStep(*playerX, *playerY);
                FastMovePlayerRight(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
                setPlayerStep(*playerX, *playerY);
            }
        }
    }

    if(step_player_answer == step_mistake)
    {
        step_player_answer = by_default;
        playerFallDown(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
    }


    if(!isPlayerOnLadder) playerFallDown(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
}
//-------------------------------------------------------------

void GameBoard::doubleJumpPlayer(uint * playerX, uint * playerY, uint beginPosPlayerX, uint beginPosPlayerY)
{
    int isEnterAnything = 0;
    char symb;
    step_player_answer = by_default;
    int i = 0;

    while(i < 4)
    {
        if(isLadder(*playerX, *playerY - 1))
        {
            erasePlayerStep(*playerX, *playerY);
            movePlayerForward(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
            setPlayerStep(*playerX, *playerY);
            break;
        }
        else
        {
            erasePlayerStep(*playerX, *playerY);
            movePlayerForward(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
            setPlayerStep(*playerX, *playerY);
            i++;
            timeDelay(50);
        }
    }

    timeDelay(130);

    isEnterAnything = _kbhit();

    if (isEnterAnything)
    {
        symb = (char)_getch(); // code 224
        //(Для управляющий клавиши передается 2 байта. Первый код, который читается, равен 224)
        //(For the control key, 2 bytes are sent. The first code that is read is 224)

        if (symb == (char)224)
            symb = (char)_getch();
        else
            (char)_getch();


        if((symb == 'a') ||
                (symb == 'A') ||
                (symb == 75) ||         // '75' - code of the left arrow ('K')
                (symb == (char)148) ||  //Ф
                (symb == (char)228))    //ф
        {
            timeDelay(50);
            erasePlayerStep(*playerX, *playerY);
            movePlayerLeft(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
            setPlayerStep(*playerX, *playerY);
        }
        else if((symb == 'd') ||
                (symb == 'D') ||
                (symb == 77) ||         // '77' - code of the right arrow ('M')
                (symb == (char)130) ||  //В
                (symb == (char)162))    //в
        {
            timeDelay(50);
            erasePlayerStep(*playerX, *playerY);
            movePlayerRight(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
            setPlayerStep(*playerX, *playerY);
        }
        else if((symb == 'Z') ||
                (symb == 'z') ||
                (symb == (char)159) || //Я
                (symb == (char)239))   //я
        {
            if(isFastMove)
            {
                timeDelay(50);
                erasePlayerStep(*playerX, *playerY);
                FastMovePlayerLeft(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
                setPlayerStep(*playerX, *playerY);
            }
        }

        else if((symb == 'c') ||
                (symb == 'C') ||
                (symb == (char)145) ||  //В
                (symb == (char)225))    //в
        {
            if(isFastMove)
            {
                timeDelay(50);
                erasePlayerStep(*playerX, *playerY);
                FastMovePlayerRight(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
                setPlayerStep(*playerX, *playerY);
            }
        }
    }

    if(step_player_answer == step_mistake)
    {
        step_player_answer = by_default;
        playerFallDown(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
    }


    if(!isPlayerOnLadder) playerFallDown(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
}

//-------------------------------------------------------------

void GameBoard::FastMovePlayerLeft(uint * playerX, uint * playerY, uint beginPosPlayerX, uint beginPosPlayerY)
{
    fastMoveProcess = true;

    for(int i = 0; i < 4 && step_player_answer != step_mistake; i++)
    {
        if(isLadder(*playerX - 1, *playerY))
        {
            erasePlayerStep(*playerX, *playerY);
            movePlayerLeft(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
            setPlayerStep(*playerX, *playerY);
            break;
        }
        else
        {
            erasePlayerStep(*playerX, *playerY);
            movePlayerLeft(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
            setPlayerStep(*playerX, *playerY);
            timeDelay(70);
        }
    }

    if(!isBrick(*playerX, *playerY))
    {
        step_player_answer = by_default;
        setPlayerStep(*playerX, *playerY);
        timeDelay(70);
        playerFallDown(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
        step_player_answer = step_fallDown;
    }

    fastMoveProcess = false;
}

//-------------------------------------------------------------

void GameBoard::FastMovePlayerRight(uint * playerX, uint * playerY, uint beginPosPlayerX, uint beginPosPlayerY)
{
    fastMoveProcess = true;

    for(int i = 0; i < 4 && step_player_answer != step_mistake; i++)
    {
        if(isLadder(*playerX + 1, *playerY))
        {
            erasePlayerStep(*playerX, *playerY);
            movePlayerRight(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
            setPlayerStep(*playerX, *playerY);
            break;
        }
        else
        {
            erasePlayerStep(*playerX, *playerY);
            movePlayerRight(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
            setPlayerStep(*playerX, *playerY);
            timeDelay(70);
        }
    }

    if(!isBrick(*playerX, *playerY))
    {
        step_player_answer = by_default;
        setPlayerStep(*playerX, *playerY);
        timeDelay(70);
        playerFallDown(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
        step_player_answer = step_fallDown;
    }

    fastMoveProcess = false;
}

//-------------------------------------------------------------

void GameBoard::playerFallDown(uint * playerX, uint * playerY, uint beginPosPlayerX, uint beginPosPlayerY)
{
    while(step_player_answer != step_mistake &&
          step_player_answer != step_danger &&
          !isLadder(*playerX, *playerY + 1))
    {
        if (checkIsDanger(*playerX, *playerY + 1))
        {
            erasePlayerStep(*playerX, *playerY);
            *playerX = beginPosPlayerX;
            *playerY = beginPosPlayerY;
            setPlayerStep(*playerX, *playerY);
            step_player_answer = step_danger;
        }
        else
        {
            erasePlayerStep(*playerX, *playerY);
            movePlayerBackward(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
            setPlayerStep(*playerX, *playerY);
            timeDelay(70);
        }
    }
    step_player_answer = step_fallDown;
}

//--------------------------------------------------------------

void GameBoard::movePlayerForward(uint * playerX, uint * playerY, uint beginPosPlayerX, uint beginPosPlayerY)
{
    if (accessBoard(*playerX, *playerY - 1))
    {
        if (checkIsDanger(*playerX, *playerY - 1))
        {
            *playerX = beginPosPlayerX;
            *playerY = beginPosPlayerY;
            step_player_answer = step_danger;
        }
        else
        {
            isLadder(*playerX, *playerY - 1);
            (*playerY)--;
            isLadderSymbol ? isPlayerOnLadder=true : isPlayerOnLadder=false;
            step_player_answer = move_forward;
        }
    }
    else
    {
        step_player_answer = step_mistake;
    }
}

//----------------------------------------------------------------------------

void GameBoard::movePlayerBackward(uint * playerX, uint * playerY, uint beginPosPlayerX, uint beginPosPlayerY)
{
    if (accessBoard(*playerX, *playerY + 1))
    {
        if (checkIsDanger(*playerX, *playerY + 1))
        {
            *playerX = beginPosPlayerX;
            *playerY = beginPosPlayerY;
            step_player_answer = step_danger;
        }
        else
        {
            isLadder(*playerX, *playerY + 1);
            (*playerY)++;
            isLadderSymbol ? isPlayerOnLadder=true : isPlayerOnLadder=false;
            step_player_answer = move_backward;
        }
    }
    else
    {
        step_player_answer = step_mistake;
    }
}

//----------------------------------------------------------------------------

void GameBoard::movePlayerLeft(uint * playerX, uint * playerY, uint beginPosPlayerX, uint beginPosPlayerY)
{
    if (accessBoard(*playerX - 1, *playerY))
    {
        if (checkIsDanger(*playerX - 1, *playerY))
        {
            *playerX = beginPosPlayerX;
            *playerY = beginPosPlayerY;
            step_player_answer = step_danger;
        }
        else
        {
            isLadder(*playerX - 1, *playerY);
            collectKeys(*playerX - 1, *playerY);
            openDoors(*playerX - 1, *playerY);
            isPlayerGetPriceKey(*playerX - 1, *playerY);
            (*playerX)--;
            isLadderSymbol ? isPlayerOnLadder=true : isPlayerOnLadder=false;
            step_player_answer = move_left;

            if(!isBrick(*playerX, *playerY) && !fastMoveProcess)
            {
                setPlayerStep(*playerX, *playerY);
                timeDelay(70);
                playerFallDown(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
            }
        }
    }
    else
    {
        step_player_answer = step_mistake;
    }
}

//------------------------------------------------------------------------------

void GameBoard::movePlayerRight(uint * playerX, uint * playerY, uint beginPosPlayerX, uint beginPosPlayerY)
{
    if (accessBoard(*playerX + 1, *playerY))
    {
        if (checkIsDanger(*playerX + 1, *playerY))
        {
            *playerX = beginPosPlayerX;
            *playerY = beginPosPlayerY;
            step_player_answer = step_danger;
        }
        else
        {
            isLadder(*playerX + 1, *playerY);
            collectKeys(*playerX + 1, *playerY);
            openDoors(*playerX + 1, *playerY);
            isPlayerGetPriceKey(*playerX + 1, *playerY);
            (*playerX)++;
            isLadderSymbol ? isPlayerOnLadder=true : isPlayerOnLadder=false;
            step_player_answer = move_right;

            if(!isBrick(*playerX, *playerY) && !fastMoveProcess)
            {
                setPlayerStep(*playerX, *playerY);
                timeDelay(70);
                playerFallDown(playerX, playerY, beginPosPlayerX, beginPosPlayerY);
            }
        }
    }
    else
    {
        step_player_answer = step_mistake;
    }
}

//--------------------------------------------------------------------------------

void GameBoard::moveError()
{
    step_player_answer = by_default;
}

//--------------------------------------------------------------------------------

bool GameBoard::getStepMistake()
{
    return((step_player_answer == step_mistake) ? true : false);
}

//--------------------------------------------------------------------------------

bool GameBoard::getStepDanger()
{
    return((step_player_answer == step_danger) ? true : false);
}

//--------------------------------------------------------------------------------

void GameBoard::stepPlayerAnswer()
{
    switch (step_player_answer)
    {
    //*********************************************************************
    case step_mistake:
#ifdef EN
        cout << "\aCAN'T GO THERE!!!" << endl;
#endif // EN
#ifdef RU
        cout << "\aНЕ МОГУ ПОЙТИ ТУДА!!!" << endl;
#endif // RU
        break;
        //*********************************************************************
    case move_forward:
#ifdef EN
        cout << "I've done a step up" << endl; // move forward
#endif // EN
#ifdef RU
        cout << "Я сделал шаг вверх" << endl;
#endif // RU
        break;
        //*********************************************************************
    case move_backward:
#ifdef EN
        cout << "I've done a step down" << endl; // move forward
#endif // EN
#ifdef RU
        cout << "Я сделал шаг вниз" << endl;
#endif // RU
        break;
        //*********************************************************************
    case move_left:
#ifdef EN
        cout << "I've done a step left" << endl; // move forward
#endif // EN
#ifdef RU
        cout << "Я сделал шаг влево" << endl;
#endif // RU
        break;
        //*********************************************************************
    case move_right:
#ifdef EN
        cout << "I've done a step right" << endl; // move forward
#endif // EN
#ifdef RU
        cout << "Я сделал шаг вправо" << endl;
#endif // RU
        break;
        //*********************************************************************
    case step_danger:
#ifdef EN
        cout << "\aI'm faced with danger!" << endl; // move forward
#endif // EN
#ifdef RU
        cout << "\aЯ столкнулся с опасностью!" << endl;
#endif // RU
        break;
        //*********************************************************************
    case step_fallDown:
#ifdef EN
        cout << "\aI'm jump down!" << endl; // move forward
#endif // EN
#ifdef RU
        cout << "\aЯ спрыгнул вниз!" << endl;
#endif // RU
        break;
    }
}



//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

void GameBoard::setMMonsterPosition(uint *monsterX, uint *monsterY, bool * isMoveLeft)
{
    /*srand((uint)(time(nullptr)));
    int var = rand() % 2;
    switch (var)
    {
    case 0:
        //while(true)
       // {
            moveMmonsterLeft(monsterX, monsterY);
           // moveMmonsterRight(monsterX, monsterY, playerX, playerY, beginPosPlayerX, beginPosPlayerY);
        //}
        break;

    case 1:
       // while(true)
       // {
            moveMmonsterRight(monsterX, monsterY);
           // moveMmonsterLeft(monsterX, monsterY, playerX, playerY, beginPosPlayerX, beginPosPlayerY);
      //  }
        break;
    }*/

    if(*isMoveLeft)
    {
        if (board[*monsterY][*monsterX - 1] != brick_symbol &&
                isBrick(*monsterX - 1, *monsterY + 1) &&
                !isDoor(*monsterX - 1, *monsterY))
            moveMmonsterLeft(monsterX, monsterY);
        else
        {
            *isMoveLeft=false;
            moveMmonsterRight(monsterX, monsterY);
        }
    }
    else
    {
        if (board[*monsterY][*monsterX + 1] != brick_symbol &&
                isBrick(*monsterX + 1, *monsterY + 1) &&
                !isDoor(*monsterX + 1, *monsterY))
        {
            moveMmonsterRight(monsterX, monsterY);
        }
        else
        {
            *isMoveLeft=true;
            moveMmonsterLeft(monsterX, monsterY);
        }
    }
}

//--------------------------------------------------------------

void GameBoard::setQMonsterPosition(uint * monsterX, uint * monsterY, bool * isMoveUp)
{
    /*
     * srand((uint)(time(nullptr)));
    int var = rand() % 2;
    switch (var)
    {
    case 0:
        //while(true)
    {
        moveQmonsterForward(monsterX, monsterY);
        //moveQmonsterBackward(monsterX, monsterY);
    }
        break;

    case 1:
        // while(true)
    {
        moveQmonsterBackward(monsterX, monsterY);
        //moveQmonsterForward(monsterX, monsterY);
    }
        break;
    }
    */

    if(*isMoveUp)
    {
        if (board[*monsterY - 1][*monsterX] != brick_symbol &&
                board[*monsterY - 1][*monsterX] != potion_symbol)
            moveQmonsterForward(monsterX, monsterY);
        else
        {
            *isMoveUp=false;
            moveQmonsterBackward(monsterX, monsterY);
        }
    }
    else {
        if (board[*monsterY + 1][*monsterX] != brick_symbol &&
                board[*monsterY + 1][*monsterX] != potion_symbol)
        {
            moveQmonsterBackward(monsterX, monsterY);
        }
        else
        {
            *isMoveUp=true;
            moveQmonsterForward(monsterX, monsterY);
        }
    }

}

//-----------------------------------------------------------------

void GameBoard::moveMmonsterLeft(uint * monsterX, uint * monsterY)
{
    /*if (board[*monsterY][*monsterX - 1] != brick_symbol &&
           isBrick(*monsterX - 1, *monsterY + 1))*/
    {
        eraseMonsterStep(*monsterX, *monsterY);
        (*monsterX)--;
        setMMonsterStep(*monsterX, *monsterY);

    }
}

//------------------------------------------------------------------

void GameBoard::moveMmonsterRight(uint * monsterX, uint * monsterY)
{
    /*if (board[*monsterY][*monsterX + 1] != brick_symbol &&
           isBrick(*monsterX + 1, *monsterY + 1))*/
    {
        eraseMonsterStep(*monsterX, *monsterY);
        (*monsterX)++;
        setMMonsterStep(*monsterX, *monsterY);
    }
}

//-----------------------------------------------------------------------

void GameBoard::moveQmonsterForward(uint * monsterX, uint * monsterY)
{
    /* while (board[*monsterY - 1][*monsterX] != brick_symbol) */
    {
        eraseMonsterStep(*monsterX, *monsterY);
        (*monsterY)--;
        setQMonsterStep(*monsterX, *monsterY);
    }
}

void GameBoard::moveQmonsterBackward(uint * monsterX, uint * monsterY)
{
    /* while (board[*monsterY + 1][*monsterX] != brick_symbol) */
    {
        eraseMonsterStep(*monsterX, *monsterY);
        (*monsterY)++;
        setQMonsterStep(*monsterX, *monsterY);
    }
}

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------

GameBoard::~GameBoard()
{
    if (board != nullptr)
    {
        for (uint i = 0; i < maxY; i++)
        {
            delete[] board[i];
        }
        delete[] board;
    }
}


