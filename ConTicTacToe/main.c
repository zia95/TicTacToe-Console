#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"../consolehelper/include/conhlpr.h"
#include"../consolehelper/include/hlpr.h"
#include "str.h"

#define PLAYER_ONE_MARK 'X'
#define PLAYER_TWO_MARK 'O'

#define CONSOLE_COLOR 31
#define PLAYER_ONE_CLR 26
#define PLAYER_TWO_CLR 20

#define CLEAR_CONSOLE() system("CLS")

typedef enum _PLAYER_
{
	Player1,
	Player2,
}PLAYER, *PPLAYER;

static char g_square[9];
static PLAYER g_playerturn;
static HANDLE g_hConOut;
static VECTOR2 g_start_pos;

/*********************************************
	FUNCTION TO draw ui
**********************************************/
void draw()
{
	SetTitle(STR_CON_TITLE);
	
	CLEAR_CONSOLE();

	printf(STR_TITLE);

	printf(STR_GAME_INFO, PLAYER_ONE_MARK, PLAYER_TWO_MARK);

	printf(STR_BOARD_ONE);
	GetConsolePosition(g_hConOut, &g_start_pos);//need start pos for changing marks
	g_start_pos.X += 10;//position of first char
	printf(STR_BOARD_TWO, g_square[0], g_square[1], g_square[2]);
	printf(STR_BOARD_THREE);

	printf(STR_BOARD_ONE);
	printf(STR_BOARD_TWO, g_square[3], g_square[4], g_square[5]);
	printf(STR_BOARD_THREE);

	printf(STR_BOARD_ONE);
	printf(STR_BOARD_TWO, g_square[6], g_square[7], g_square[8]);
	printf(STR_BOARD_ONE);

	printf(STR_CMD_LOG);
}


int check_input(char inp)
{
	inp = toupper(inp);//all square are in upper
	
	if (inp >= 'A' && inp <= 'I')
	{
		int i = inp - 'A';
		return inp == g_square[i] ? i : -1;
	}
	
	/*          OLD METHOD
	for (int i = 0; i < sizeof(g_square)/sizeof(char); i++)
	{
		if (inp != PLAYER_ONE_MARK && inp != PLAYER_TWO_MARK)
		{
			if (inp == g_square[i])
				return i;//return the index
		}
	}
	*/
	return -1;
}
void clear_in_buff()
{
	int c; 
	while ((c = getchar()) != '\n' && c != EOF) {}
}
/*********************************************
	FUNCTION TO get input
	return: Square array index
**********************************************/
int get_input()
{
	for(;;)
	{
		printf(STR_INPUT_MOVE, g_playerturn == Player1 ? PLAYER_ONE_MARK : PLAYER_TWO_MARK);
		int c = getchar();
		clear_in_buff();
		int ret = check_input(c);
		if (ret != -1)
		{
			return ret;
		}
		else
		{
			printf(STR_INPUT_ERR, c);
		}
	}

	return -1;
}
/*********************************************
	FUNCTION TO set marker
	nSquare: Square array index to set mark too
**********************************************/
void set_mark(int nSquare)
{
	g_square[nSquare] = g_playerturn == Player1 ? PLAYER_ONE_MARK : PLAYER_TWO_MARK;

	VECTOR2 _pos = g_start_pos;

	if (nSquare == 3 || nSquare == 4 || nSquare == 5)
		_pos.Y += 3;
	else if (nSquare == 6 || nSquare == 7 || nSquare == 8)
		_pos.Y += 6;

	if (nSquare == 1 || nSquare == 4 || nSquare == 7)
		_pos.X += 6;
	else if (nSquare == 2 || nSquare == 5 || nSquare == 8)
		_pos.X += 13;

	StoreState();

	SetConsolePosition(g_hConOut, _pos);
	SetConsoleColor(g_hConOut, g_playerturn ? PLAYER_ONE_CLR : PLAYER_TWO_CLR);
	
	putchar(g_square[nSquare]);

	RestoreState();
}
/*********************************************
	FUNCTION TO RETURN GAME STATUS
	1 FOR GAME IS OVER WITH RESULT
	-1 FOR GAME IS IN PROGRESS
	O GAME IS OVER AND NO RESULT
**********************************************/
int check_state()
{
	if (g_square[0] == g_square[1] && g_square[1] == g_square[2])
		return 1;
	else if (g_square[3] == g_square[4] && g_square[4] == g_square[5])
		return 1;
	else if (g_square[6] == g_square[7] && g_square[7] == g_square[8])
		return 1;
	else if (g_square[0] == g_square[3] && g_square[3] == g_square[6])
		return 1;
	else if (g_square[1] == g_square[4] && g_square[4] == g_square[7])
		return 1;
	else if (g_square[2] == g_square[5] && g_square[5] == g_square[8])
		return 1;
	else if (g_square[0] == g_square[4] && g_square[4] == g_square[8])
		return 1;
	else if (g_square[2] == g_square[4] && g_square[4] == g_square[6])
		return 1;
	else if (g_square[0] != 'A' && g_square[1] != 'B' && g_square[2] != 'C'
		&& g_square[3] != 'D' && g_square[4] != 'E' && g_square[5] != 'F'
		&& g_square[6] != 'G' && g_square[7] != 'H' && g_square[8] != 'I')
		return 0;
	else
		return -1;
}
int main(int argc, const char *argv[])
{
	g_hConOut = NULL;
	g_start_pos.X = 0;
	g_start_pos.Y = 0;
	SRECT win_rect = {0, 0, 60, 30};//left,top,right,bottom

	const char squ[9] = "ABCDEFGHI";

	g_hConOut = GetConsoleStdOutHandle();
	SetConsoleOutHandle(g_hConOut);
	SetConsoleColor(g_hConOut, CONSOLE_COLOR);

	SetConsoleWindowSize(g_hConOut, true, &win_rect);
	memcpy(g_square, squ, sizeof(g_square));
	draw();

	for (;;)
	{
		int squ_index = get_input();

		set_mark(squ_index);

		int state = check_state();
		if (state == -1)
		{
			g_playerturn = g_playerturn == Player1 ? Player2 : Player1;
		}
		else if (state == 1 || state == 0)
		{
			if (state == 1)
			{
				printf(STR_GAME_OVER, g_playerturn == Player1 ? PLAYER_ONE_MARK : PLAYER_TWO_MARK);
			}
			else
			{
				printf(STR_GAME_OVER_DRAW);
			}

			printf(STR_EXIT);//restart the game
			if (getchar() == '1')
			{
				clear_in_buff();

				//reset the game and start
				memcpy(g_square, squ, sizeof(g_square));
				draw();
				continue;
			}
			break;//exit the game if input is not '1'
		}
	}

	return 0;
}