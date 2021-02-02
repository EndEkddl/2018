#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

#define KEY_SPACE ' ' // not defined in ncurses.h
#define KEY_Enter 10
#define START_ROW 5
#define START_COL 5

int HEIGHT, WIDTH;

void saveGame(int **board, int row, int col, int turn, int players, int HEIGHT, int WIDTH){

	FILE* save;
	char ch[20] ;
	int state,  i = 0, j;
	mvprintw(row, col, "FILE NAME : ");
	echo();
	getstr(ch);
	save = fopen(ch, "w");
	fprintf(save, "%d %d %d %d %d %d\n", row, col, turn, players, HEIGHT, WIDTH);
	for(i=0; i<HEIGHT; i++) {
		for(j=0; j<WIDTH; j++) {
			fprintf(save, "%d ", board[i][j]);
		}
		fprintf(save, "\n");
	}
	state = fclose(save);

	if(state != 0){
		printf("file save error!\n");
	}
	return ;
	/*
		Save current game with given name 
	*/
	// TODO 
}

int** readSavedGame(int** board){
	
	FILE* read;
	char ch[20];
	int row, col, turn, players;
	int i = 0, j = 0;
	int BOARD;

	mvprintw(3,5,"FILE NAME : ");
	echo();
	getstr(ch);
	read = fopen(ch, "r");
	fscanf(read, "%d %d %d %d %d %d", &row, &col, &turn, &players, &HEIGHT, &WIDTH);
	board = (int**)malloc(sizeof(int*)*HEIGHT);
	for(int i=0; i<HEIGHT; i++) {
		board[i] = (int*)malloc(sizeof(int)*WIDTH);
	}

	for(i=0; i<HEIGHT; i++){
		for(; j<WIDTH; j++){
			fscanf(read, "%d ", &BOARD);
			board[i][j] = BOARD; 	
		}
		j=0;
	}
	
	return board;
	/*
		Read the existing game
	*/
	// TODO 
}

int** initBoard(int **board, int *row, int *col, int *turn, int load){
	board = (int**)malloc(sizeof(int*)*HEIGHT);
	for(int i=0; i<HEIGHT; i++){
		board[i] = (int*)malloc(sizeof(int)*WIDTH);
	}

	printf("%d %d\n", HEIGHT, WIDTH);
	board[0][0] = ACS_ULCORNER;//'┌'
	for (int i=1; i < WIDTH-1; i++)
		board[0][i] = ACS_TTEE;//'┬'
	board[0][WIDTH-1] = ACS_URCORNER; //'┐'

	for (int i=1; i<HEIGHT-1; i++){
		board[i][0] = ACS_LTEE; // '├'
		for (int j=1; j < WIDTH-1; j++)
			board[i][j] = ACS_PLUS; //'┼'
		board[i][WIDTH-1] = ACS_RTEE; //'┤'
	}

	board[HEIGHT-1][0] = ACS_LLCORNER; //'└'
	for (int i=1; i < WIDTH-1; i++)
		board[HEIGHT-1][i] = ACS_BTEE; //'┴'
	board[HEIGHT-1][WIDTH-1] = ACS_LRCORNER; // '┘'

	return board;
}

void paintBoard(int **board, WINDOW *win, int row, int col){
	
	for(int i=0; i < HEIGHT; i++)	 {
		for(int j=0; j < WIDTH; j++) {
			mvaddch(START_ROW+i, START_COL+j, board[i][j]); 
		}
	}
	/*
		Print the board to the given WINDOW 
		using functions of the ncurses library.
	*/
	// TODO
}

int stoneNumber_Horizontal(int **board, int row, int col, int stone[], int turn, int players){
	
	int i;
	int stoneNumber = 1;
	int STONE;
	if(players == 2) {
		if(turn == 1) STONE = stone[1];
		else STONE = stone[0];
	}
	else if(players == 3) {
		if(turn == 1) STONE = stone[2];
		else if(turn == 2) STONE = stone[0];
		else STONE = stone[1];
	}
	for(i=1 ; i<=4; i++) {
		if(col-5-i >= 0) {
			if(board[row-5][col-5-i] == STONE ) stoneNumber++;
			else break;
		}
		else continue;
	}
	for(i=1; i<= 4; i++) {
		if(col-5+i < WIDTH ) {
			if(board[row-5][col-5+i] == STONE ) stoneNumber++;
			else break;
		}
		else continue;
	}
	return stoneNumber;
}

int stoneNumber_Vertical(int **board, int row, int col, int stone[], int turn, int players){
	
	int i;
	int stoneNumber = 1;
	int STONE;

	if(players == 2) {
		if(turn == 1) STONE = stone[1];
		else STONE = stone[0];
	}
	else if(players == 3) {
		if(turn == 1) STONE = stone[2];
		else if(turn == 2) STONE = stone[0];
		else STONE = stone[1];
	}
	for(i=1 ; i<=4; i++) {
		if(row-5-i >= 0) {
			if(board[row-5-i][col-5] == STONE ) stoneNumber++;
			else break;
		}
		else continue;
	}
	for(i=1; i<= 4; i++) {
		if(row-5+i < HEIGHT ) {
			if(board[row-5+i][col-5] == STONE ) stoneNumber++;
			else break;
		}
		else continue;
	}
	
	
	return stoneNumber;
}

int stoneNumber_Diagonal1(int **board, int row, int col, int stone[], int turn, int players){

	int i;
	int stoneNumber = 1;
	int STONE;

	if(players == 2) {
		if(turn == 1) STONE = stone[1];
		else STONE = stone[0];
	}
	else if(players == 3) {
		if(turn == 1) STONE = stone[2];
		else if(turn == 2) STONE = stone[0];
		else STONE = stone[1];
	}
	for(i=1 ; i<=4; i++) {
		if(row-5-i >= 0 && col-5-i >= 0) {
			if(board[row-5-i][col-5-i] == STONE ) stoneNumber++;
			else break;
		}
		else continue;
	}
	for(i=1; i<= 4; i++) {
		if(row-5+i < HEIGHT && col-5+i < WIDTH) {
			if(board[row-5+i][col-5+i] == STONE ) stoneNumber++;
			else break;
		}
		else continue;
	}
	return stoneNumber;
}

int stoneNumber_Diagonal2(int **board, int row, int col, int stone[], int turn, int players){

	int i;	
	int stoneNumber = 1;
	int STONE;

	if(players == 2) {
		if(turn == 1) STONE = stone[1];
		else STONE = stone[0];
	}
	else if(players == 3) {
		if(turn == 1) STONE = stone[2];
		else if(turn == 2) STONE = stone[0];
		else STONE = stone[1];
	}
	for(i=1 ; i<=4; i++) {
		if(row-5-i >= 0 && col-5+i < WIDTH) {
			if(board[row-5-i][col-5+i] == STONE ) stoneNumber++;
			else break;
		}
		else continue;
	}
	for(i=1; i<= 4; i++) {
		if(row-5+i < HEIGHT && col-5-i >= 0) {
			if(board[row-5+i][col-5-i] == STONE ) stoneNumber++;
			else break;
		}
		else continue;
	}
	return stoneNumber;
}

int checkWin(int **board, int row, int col, int stone[], int turn, int players){ 

	int i = 1;
	int stoneNum1 = 1, stoneNum2 = 1, stoneNum3 = 1, stoneNum4 = 1;
	int STONE = stone[turn-1];
	
	
	stoneNum1 = stoneNumber_Horizontal(board, row, col, stone, turn, players);
	stoneNum2 = stoneNumber_Vertical(board, row, col, stone, turn, players);
	stoneNum3 = stoneNumber_Diagonal1(board, row, col, stone, turn, players);
	stoneNum4 = stoneNumber_Diagonal2(board, row, col, stone, turn, players);


	if(players == 2) {

		if(stoneNum1 >=5 || stoneNum2 >= 5 || stoneNum3 >= 5 || stoneNum4 >= 5) return 1;
		else return 0;
	}

	else if(players == 3) {

		if(stoneNum1 >=4 || stoneNum2 >= 4 || stoneNum3 >= 4 || stoneNum4 >= 4) return 1;
		else return 0;

	}
			

	// parameters and return type can be modified with any form. 
	/*
		Check if the game is over. 
	*/
	// TODO
}

int Action(WINDOW *win, int **board, int keyin, int *row, int *col, int *turn, int players){
	int stone[3] = {79, 88, 89};
	int rowCopy, colCopy, turnCopy;
	char turnArr[3] = {1,2,3};
	int i = 0, j = 0;

	rowCopy = *row;
	colCopy = *col;
	turnCopy = *turn;
	
	switch (keyin)

	{
		case KEY_LEFT :
			if(*col < 6) *col = *col;
			else (*col)--;
			break;
		case KEY_RIGHT :
			if(*col >= WIDTH+4) *col = *col;
			else (*col)++;
			break;
		case KEY_UP :
			if(*row < 6) *row = *row;
			else (*row)--;
			break;
		case KEY_DOWN :
			if(*row >= HEIGHT+4) *row = *row;
			else (*row)++;
			break;
		case KEY_SPACE :
			board[*row-5][*col-5] = stone[*turn-1];
			if(players == 3) {	
				if(*turn == 3) {
					*turn = 1;
				}
				else *turn += 1; 
				if (checkWin(board, *row, *col, stone, *turn, players) == 1 )  {return 1;}
				else {return 0;}
				break;
			}

			else if(players == 2) {
				if(*turn == 1) {
					*turn = 2; 
				}
				else if(*turn == 2) {
					*turn = 1; 
				}
				if (checkWin(board, *row, *col, stone, *turn, players) == 1 )  {return 1;}
				else {return 0;}
				break;
			}
		case KEY_Enter :
			board[*row-5][*col-5] = stone[*turn - 1];
			if(players == 3) {	
				if(*turn == 3) {
					*turn = 1; 
				}
				else *turn += 1; 
				if (checkWin(board, *row, *col, stone, *turn, players) == 1 )  {return 1;}
				else {return 0;}
				break;
			}

			else if(players == 2) {
				if(*turn == 1) {
					*turn = 2; 
				}
				else if(*turn == 2) {
					*turn = 1; 
				}
				if (checkWin(board, *row, *col, stone, *turn, players) == 1 )  {return 1;}
				else {return 0;}
				break;
			}
		case '1' : saveGame(board, rowCopy, colCopy, turnCopy, players, HEIGHT, WIDTH); return 2; break;
		case '2' : return 2;
		default : break;
			
			 
	}

	/*
		following right after the keyboard input,
		perform a corresponding action. 
	*/
	// TODO 
}


void gameStart(WINDOW *win, int load, int players){

	int **board;
	int row = START_ROW;
	int col = START_COL;
	int keyin, endkey, winner;
	int turn = 1;
	int stone[3] = {79, 88, 89};
	if(load == 'y')	{ board = readSavedGame(board);}
	else if(load =='n')
	{board = initBoard(board, &row, &col, &turn, load);}

	while(1){
		paintBoard(board, win, row, col);
		mvprintw(30,5,"Current Turn : %c\n", stone[turn-1]);
		mvprintw(31,5,"1. Press 1 to save\n");
		mvprintw(32,5,"2. Exit without save\n");
		wmove(stdscr, row, col);
		keyin = getch();
	int exitCondition = Action(win, board, keyin, &row, &col, &turn, players);
		wmove(win,row, col);
		if ( exitCondition == 1 ) {
			refresh();
			wrefresh(win);
			if(players == 2) {
				if(turn == 1) winner = 2;
				else if(turn == 2) winner = 1;
			}
			else if(players == 3) {
				if(turn == 1) winner = 3;
				else if(turn == 2) winner = 1;
				else winner = 2;
			}
			mvprintw(28,5,"PLAYER%d WIN!! Press any button to terminate the program\n", winner);
			noecho();
			endkey = getch();
			break;
		}
		else if (exitCondition == 2) break;
		else {
			wrefresh(win);
		continue;
		}
			
	}	
	
	return ;

        	//  Prompts to ask options of the game
		/* 
			This While loop constantly loops in order to 
			draw every frame of the WINDOW.
		*/

		// TODO LIST
		  // PAINT THE BOARD
		  // PAINT MENU
		  // MOVE CURSOR TO THE LAST POINT 
		  // GET KEYBOARD INPUT
		  // DO ACTION ACCORDING TO THAT INPUT
		  // update WINDOW 
	
}

int main(void) {
	char load;
	int players;
	int** board;
	printf("Want to load the game?[y/n] : ");
	scanf("%c", &load);
	
	if(load == 'n')
	{
		printf("Enter the HEIGHT of the board :");
		scanf("%d", &HEIGHT);
		printf("Enter the WIDTH of the board : ");
		scanf("%d", &WIDTH);
		printf("Enter the number of players[2/3] : ");
		scanf("%d", &players);
		WINDOW *win = initscr();
		cbreak();
		noecho();
		keypad(stdscr, TRUE);
		gameStart(win, load, players); 
		endwin();
	}

	else if(load == 'y') {
		WINDOW *win = initscr();
		cbreak;
		noecho();
		keypad(stdscr, TRUE);
		board = readSavedGame(board);
		gameStart(win, load, players);	
		endwin();
	}
	else 
	{printf("You have to put 'y' or 'n' only.\n"); return 0;}

	return 0;

	// TODO 
	/*
		Prompts to ask options of the game
	*/

	// TODO LIST
	  // define a window
	  // terminate the window safely so that the terminal settings can be restored safely as well. 
//	WINDOW *win = initscr();
//	cbreak();
//	noecho();
//	keypad(stdscr, TRUE);
//	gameStart(win, load, players); 
	
}
