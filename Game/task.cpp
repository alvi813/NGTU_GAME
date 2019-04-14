#ifndef H_TASK
#include "task.h"
#include "ctime"
#include <conio.h>
#endif // !H_TASK

//---------------------------

void userInput(char *input)
{
	//cin >> (*input);


    *input = (char)_getch(); // code 224
    //(Для управляющий клавиши передается 2 байта. Первый код, который читается, равен 224)
	//(For the control key, 2 bytes are sent. The first code that is read is 224)
	
	if (*input == (char)224)
		*input = (char)_getch();
    else
       _getch();
	//*input = (char)toupper(*input);
}

void enterMovementData()
{
#ifdef EN
	cout << "Select the direction of your movement by pressing the arrows or the buttons: 'w', 'a', 's', 'd' ('x' - for exit)";
#endif // EN
#ifdef RU
	cout << "\nВыбери направление движения нажатием стрелок или клавиш: 'w', 'a', 's', 'd' ('x' - для выхода)";
#endif // RU
}

void timeDelay(int delay)
{
	clock_t now;
	now = clock();
    while (clock() <= now + delay * CLOCKS_PER_SEC / 1000)
		;
}
