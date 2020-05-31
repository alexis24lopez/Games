/*********************************************************************************************************************
* Game: Tic Tac Toe (Gato)
* Programmer: Alexis Lopez
* Special Thanks to: https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-3-tic-tac-toe-ai-finding-optimal-move/
* One guy in cplusplus for their contributions of the cpu_medium algorithm.
* compile: $ g++ game.cpp
*		   $ a.exe (if compiing on windows)
*		   $ /a.out (if compiling on Linux)
* Updated: 05/29/2020
* Version: 3.0
*********************************************************************************************************************/
# include <iostream>
# include <cstdio>
# include <cstdlib>
# include <string>
# include <time.h>
# include <windows.h>
#include <fstream>

#define SIZE 3	// Size of the grid!
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

struct Move 
{ 
    int row, col; 
}; 

void header();
void instructions();
int multiplayer(char grid[SIZE][SIZE]);
int computer(char grid[SIZE][SIZE]);
void showGame(char grid[SIZE][SIZE]);
bool validate(short int position, char grid[SIZE][SIZE], bool player1_x);
bool full(char grid[SIZE][SIZE]);
void cpu_easy(char grid[SIZE][SIZE]);
bool gameOver(char symbol, char grid[SIZE][SIZE]);
void cpu_medium(char grid[SIZE][SIZE]);
void cpu_hard(char grid[SIZE][SIZE]);
bool isMovesLeft(char board[SIZE][SIZE]);
int evaluate(char b[SIZE][SIZE]);
int minimax(char board[SIZE][SIZE], int depth, bool isMax);
Move findBestMove(char board[SIZE][SIZE]);
bool score(int new_score, std::string load_name);
void view_score(std::string player, int score);

using namespace std;

int main()
{
	// Initializing variables;
	short int option, attempt = 0;
	char grid[SIZE][SIZE];
	int ranking = 0;
	string dummy_name = "as1s";
	
	while (true){
		header();
		
		cout << "[0] How to play\n[1] Multiplayer\n[2] Computer\n[3] Highest Score\n[4] Quit\n";
		cout << "Please select one: ";
		cin >> option;
		
		while (option > 4){
			header();
			attempt++;
			
			if (attempt == 9){
				cout << BOLDYELLOW << "\nOne attempt left!! :O " << RESET << endl;
				Sleep(1500);
			}
			if (attempt == 10){
				cout << BOLDRED << "\nToo many invalid attempts the program quited!! :(" << RESET << endl;
				return 0;
			}
			
			cout << BOLDRED << "Invalid number!" << RESET << endl;
			cout << "[0] How to play\n[1] Multiplayer\n[2] Computer\n[3] Higest Score\n[4] Quit\n";
			cout << "Please select one: ";
			cin >> option;
		}
		
		attempt = 0;	// Restart the attempt count
		
		// Initializing the grid
		for (int i = 0; i < SIZE; i++){
			for (int j = 0; j < SIZE; j++){
				grid[i][j] = '?';
			}
		}
		
		// Determining which function to call.
		if (option == 0){
			instructions();
		}else if (option == 1){
			multiplayer(grid);
		}else if (option == 2){
			computer(grid);
		}else if (option == 3){
			view_score(dummy_name, ranking);
			cout << "\nPress enter to continue: ";
			cin.ignore();
			cin.get();
		} else if (option == 4){
			cout << BOLDMAGENTA << "\n\nThanks for playing!! ;)\n" << RESET;
			Sleep(1500);
			break;
		}
	}
	
	system("CLS");
	
	return 0;
}

void header()
{
	system ("CLS");
	cout << "---------------------------------\n";
	cout << "-     Welcome to Tic Tac Toe    -\n";
	cout << "---------------------------------\n\n";
}
void instructions()
{
	header();
	
	cout << "Programmer: Alexis Lopez\n";
	cout << "\nSelect the square you want by typing the corresponding number.\n";
	cout << "You are X and your friend or computer are O. Players take turns in\n";
	cout << "putting their mark on the remaining squares.\n";
	cout << "You cannot use a square that is already used. The first player to get 3\n";
	cout << "of her marks in a row(up, down, across, or diagonally) is the winner.\n";
	cout << "If all square are full and their is no apparent winner it is a tie.\n";
	cout << BOLDCYAN << "\nRemember to have fun!! :)\n" << RESET;
	cout << "Press Enter to return to main menu: ";
	cin.ignore();
	cin.get();
	
}
int multiplayer(char grid[SIZE][SIZE])
{
	// Initializing variables.
	string player1, player2;		//name of player.
	char play_again, change_name;		// want to play againg or change name.
	short int position1, position2 = 0;	// Position number of the grid from 1-9.
	bool player1_x = true;			// How to output the grid.
	char symbol_x = 'X';
	char symbol_o = 'O';
	int ranking_player1 = 0;		// Keeping score of players.
	int ranking_player2 = 0;
	
	header();
	cout << "Multiplayer mode!\n";
	cout << "Please enter the name of player 1 or [0] Main menu: ";
	cin >> player1;
	
	if(player1 == "0"){ return 0;}
	
	cout << "Please enter the name of player 2: ";
	cin >> player2;
	
	showGame(grid);
	
	while (true){
	
		// The game can be completed in a max of 5 moves for each player.
		for (int i = 0; i < 5; i++){
			cout << "Player 1: " << player1 << "\nnumber: ";
			cin >> position1;	// Getting the position of the player.
			
			// Validating his option, if position already taken choose a new one.
			while (!validate(position1, grid, player1_x)){ cin >> position1;}
			
			showGame(grid);	// Display the current game.
			
			if (gameOver(symbol_x, grid)){ // If is game over player one won and score will be recorded
				cout << "Player 1: " << player1 << BOLDGREEN << " won!!" << RESET << endl;
				ranking_player1++;
				Sleep(1500);
				
				if (score(ranking_player1, player1) == true){
					//If is a new record it will display it on green.
					view_score(player1, ranking_player1);
					cout << "\nPress any key to continue: ";
					cin.ignore();
					cin.get();
				}
				
				cout << endl << player1 << " score: " << ranking_player1 << endl;
				cout << player2 << " score: " << ranking_player2 << endl;
				break;
			}
			
			// If the grid is full meaning i = 5 the next player cannot move because there are no more
			// free spaces so the game is a tie!
			if(full(grid)){
				cout << BOLDMAGENTA << "Tied!" << RESET << endl;
				break;
			}
			
			// Same as player 1
			cout << "Player 2: " << player2 << "\nnumber: ";
			cin >> position2;
			
			while (!validate(position2, grid, !player1_x)){ cin >> position2;}
			
			showGame(grid);
			
			if (gameOver(symbol_o, grid)){
				cout << "Player 2: " << player2 << BOLDCYAN << " won!!" << RESET << endl;
				ranking_player2++;
				Sleep(1500);
				
				if (score(ranking_player2, player2) == true){
					view_score(player2, ranking_player2);
					cout << "\nPress any key to continue: ";
					cin.ignore();
					cin.get();
				}
				
				cout << endl << player1 << " score: " << ranking_player1 << endl;
				cout << player2 << " score: " << ranking_player2 << endl;
				break;
			}
		}
		
		// After the game is over it asks if they want to continue playing the multiplayer.
		cout << "\nDo you want to play again?[y/n]: ";
		cin >> play_again;
		
		if (play_again == 'y' || play_again == 'y'){
			// Restarting the grid
			for (int i = 0; i < SIZE; i++){
				for (int j = 0; j < SIZE; j++){
					grid[i][j] = '?';
				}
			}
			cout << "change name?[y/n]: ";
			cin >> change_name;
			
			if (change_name == 'Y' || change_name == 'y'){
				cout << "Please enter the name of player 1: ";
				cin >> player1;
				cout << "Please enter the name of player 2: ";
				cin >> player2;
				
				// Since names changed the scores are back to zero, for the new players.
				ranking_player1 = 0;
				ranking_player2 = 0;
			}
	
			showGame(grid);
			
		} else {
			break;
		}
	}
	
	return 0;
}
int computer(char grid[SIZE][SIZE])
{	
	// Initializing the variables.
	string player1;						// Name of single player.
	short int position, choice = 0;		// Selecting position on grid from 1-9. Level of dificulty of game.
	bool player1_x = true;
	char symbol_x = 'X';
	char symbol_o = 'O';
	bool tied = true;
	char play_again;
	int ranking_player1 = 0;			// Keeping score of single player and computer.
	int ranking_computer = 0;
	
	header();
	cout << "Computer mode!\n";
	cout << "[0] Main menu\n[1] Baby Easy\n[2] Medium\n[3] Invincible!\nSelect one: ";
	cin >> choice;
	
	// Check choice of level of difficulty is between the range.
	while (choice > 3){
		header();
		cout << BOLDRED << "Invalid number please try again!\n" << RESET;
		cout << "Computer mode!\n";
		cout << "[0] Main menu\n[1] Baby Easy\n[2] Medium\n[3] Invincible!\nSelect one: ";
		cin >> choice;
	}
	
	if (choice == 0) { return 0;}
	
	cout << "Please enter the name of player 1: ";
	cin >> player1;
	
	showGame(grid);
	
	while (true){
		// Same as multiplayer but now is vs the computer. The structure is the same. We don't keep score
		// on top five if computer wins or a tie.
		for (int i = 0; i < 5; i++){
			cout << "Player 1: " << player1 << "\nnumber: ";
			cin >> position;
			
			while (!validate(position, grid, player1_x)){ cin >> position;}
			
			showGame(grid);
			
			if (gameOver(symbol_x, grid)){
				cout << "Player: " << player1 << BOLDGREEN << " won!!" << RESET << endl;
				ranking_player1++;
				Sleep(1500);
				
				if (score(ranking_player1, player1) == true){
					//Display new score on green
					view_score(player1, ranking_player1);
					cout << "\nPress any key to continue: ";
					cin.ignore();
					cin.get();
				}
				
				cout << endl << player1 << " score: " << ranking_player1 << endl;
				cout << "Computer score: " << ranking_computer << endl;
				tied = false;
				break;
			}
			
			if(full(grid)){
				cout << BOLDMAGENTA << "Tied!" << RESET << endl;
				break;
			}
			
			if (choice == 1){
				cpu_easy(grid);
			}else if (choice == 2){
				cpu_medium(grid);
			}else{
				cpu_hard(grid);
			}
			
			showGame(grid);
			
			if (gameOver(symbol_o, grid)){
				cout << "Player: " << "Computer won!!\n";
				ranking_computer++;
				
				cout << endl << player1 << " score: " << ranking_player1 << endl;
				cout << "Computer score: " << ranking_computer << endl;
				
				tied = false;
				break;
			}
		}
		
		cout << "Do you want to play again?[y/n]: ";
		cin >> play_again;
		
		if (play_again == 'y' || play_again == 'y'){
			// Restarting the grid
			for (int i = 0; i < SIZE; i++){
				for (int j = 0; j < SIZE; j++){
					grid[i][j] = '?';
				}
			}
			
			showGame(grid);
			
		} else {
			break;
		}
	}
	
	return 0;
}
// Display the grid with the current moves and their respective symbols and colors.
void showGame(char grid[SIZE][SIZE])
{
	header();
	
	int count = 1;
    for (int i = 0; i < SIZE; i++)
    {
        cout << "                    ";
        for  (int j = 0; j < SIZE; j ++)
        {
            if (grid [i][j] == '?')
            {
                if (j == SIZE - 1){
					cout << "  " << count;
				} else {
					cout << "  " << count << "  |";
				}
            }
            else if (grid [i][j] == 'X')
            {
				if (j == SIZE - 1){
					cout << RED << "  X" << RESET;
				} else {
					cout << RED << "  X  " << RESET << '|';
				}
            }
            else{
                if (j == SIZE - 1){
					cout << CYAN << "  O" << RESET;
				} else {
					cout << CYAN << "  O  " << RESET << '|';;
				}
			}
            count ++;
        }
		if (i < SIZE - 1){
			cout <<"\n\t            -----+-----+-----\n";
		}
    }
    cout << endl;
	
}
bool validate(short int position, char grid[SIZE][SIZE], bool player1_x)
{
	// We check if current position is already taken. Returns false fi the position is taken.
	// if player is true we know that we need to set X else we set O. Same for other positions.
	if (position == 1){
		
		if (grid[0][0] != '?'){
			cout << YELLOW << "Position already taken. Choose another one: " << RESET;
			Sleep(1000);
			return false;
		} else {
			if (player1_x == true){
				grid[0][0] = 'X';
			} else {
				grid[0][0] = 'O';
			}
		}
		return true;
		
	} else if (position == 2){
		
		if (grid[0][1] != '?'){
			cout << YELLOW << "Position already taken. Choose another one: " << RESET;
			Sleep(1000);
			return false;
		} else {
			if (player1_x == true){
				grid[0][1] = 'X';
			} else {
				grid[0][1] = 'O';
			}
		}
		return true;
		
	} else if (position == 3){
		
		if (grid[0][2] != '?'){
			cout << YELLOW << "Position already taken. Choose another one: " << RESET;
			Sleep(1000);
			return false;
		} else {
			if (player1_x == true){
				grid[0][2] = 'X';
			} else {
				grid[0][2] = 'O';
			}
		}
		return true;
	
	} else if (position == 4){
		
		if (grid[1][0] != '?'){
			cout << YELLOW << "Position already taken. Choose another one: " << RESET;
			Sleep(1000);
			return false;
		} else {
			if (player1_x == true){
				grid[1][0] = 'X';
			} else {
				grid[1][0] = 'O';
			}
		}
		return true;
	
	} else if (position == 5){
		
		if (grid[1][1] != '?'){
			cout << YELLOW << "Position already taken. Choose another one: " << RESET;
			Sleep(1000);
			return false;
		} else {
			if (player1_x == true){
				grid[1][1] = 'X';
			} else {
				grid[1][1] = 'O';
			}
		}
		return true;
	
	} else if (position == 6){
		
		if (grid[1][2] != '?'){
			cout << YELLOW << "Position already taken. Choose another one: " << RESET;
			Sleep(1000);
			return false;
		} else {
			if (player1_x == true){
				grid[1][2] = 'X';
			} else {
				grid[1][2] = 'O';
			}
		}
		return true;
	
	} else if (position == 7){
		
		if (grid[2][0] != '?'){
			cout << YELLOW << "Position already taken. Choose another one: " << RESET;
			Sleep(1000);
			return false;
		} else {
			if (player1_x == true){
				grid[2][0] = 'X';
			} else {
				grid[2][0] = 'O';
			}
		}
		return true;
	
	} else if (position == 8){
		
		if (grid[2][1] != '?'){
			cout << YELLOW << "Position already taken. Choose another one: " << RESET;
			Sleep(1000);
			return false;
		} else {
			if (player1_x == true){
				grid[2][1] = 'X';
			} else {
				grid[2][1] = 'O';
			}
		}
		return true;
	
	} else if (position == 9){
		
		if (grid[2][2] != '?'){
			cout << YELLOW << "Position already taken. Choose another one: " << RESET;
			Sleep(1000);
			return false;
		} else {
			if (player1_x == true){
				grid[2][2] = 'X';
			} else {
				grid[2][2] = 'O';
			}
		}
		return true;
	
	} else {
		cout << "Invalid number! Please enter a number 1-9: ";
		return false;
	}
}
// Returns true if the grid is full. False if the grid is NOT full.
bool full(char grid[SIZE][SIZE])
{
	for (int i = 0; i < SIZE; i++){
		for (int j = 0; j < SIZE; j++){
			if (grid[i][j] == '?'){
				return false;
			}
		}
	}
	
	return true;
}
void cpu_easy(char grid[SIZE][SIZE])
{
    //initialize random seed:
    srand (time(NULL));

    int x,cont;
	int terminate = 0;
    bool found = false;
	
	// Looks into the grid until it finds an empty place. Validation is taking care here.
	// If it loops too many times there is no empty space so it quits.
    while(found == false)
    {
		if (terminate > 30){ break;}
		
        x = rand() % 9 + 1;
        cont = 1;
        for(int i = 0; i < SIZE; i++ ){
            for(int j = 0; j < SIZE; j++ ){
                if(cont == x){
                    if(grid[i][j] != 'X' && grid[i][j] != 'O'){
                        grid[i][j] = 'O';
                        found = true;
                    }
                }
                cont++;
            }
        }
		terminate++;
    }
}
// Checks if there are 3 consecutive X's or O's and return true if is true. False is there are no 3 consicutive symbols.
bool gameOver(char symbol, char grid[SIZE][SIZE])
{
	short int move_count = 0;
	
	// Check column
	for (int i = 0; i < SIZE; i++){
		if (grid[i][0] == symbol && grid[i][1] == symbol && grid[i][2] == symbol){ return true;}
		
		move_count++;
	}
	
	// Check row
	for (int j = 0; j < SIZE; j++){
		if (grid[0][j] == symbol && grid[1][j] == symbol && grid[2][j] == symbol){ return true;}
		
		move_count++;
	}
	
	// Check diagonal
	if (grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol){ return true;}
	
	move_count += 3;
	
	// Check anti-diagonal
	if (grid[2][0] == symbol && grid[1][1] == symbol && grid[0][2] == symbol){ return true;}
	
	// We tied
	//if (move_count == 9){}
	
	return false;
}
void cpu_medium(char grid[SIZE][SIZE])
{

    int d = SIZE-1 ;// auxiliary variable for secondary diagonal
    int contd = 0 ;// counter diagonal
    int contd2 = 0 ;// counter for secondary diagonal
    int contc ;// counter for column
    int contl ;// counter for line player 1

    int contd_Cpu = 0 ;// counter diagonal for cpu
    int contd2_Cpu = 0 ;// counter for secondary diagonal of cpu  
    int contc2;// counter for the column cpu
    int contl2;// counter for line cpu
    bool found = false;

    for (int i = 0; i < SIZE; i ++)
    {
        contc = 0;
        contl = 0;
        contc2 = 0;
        contl2 = 0;

        if (grid[i][i] == 'X'){ contd ++;}   
        if (grid[i][d] == 'X'){ contd2 ++;}
        if (grid[i][i] == 'O'){ contd_Cpu ++;}
        if (grid[i][d] == 'O'){ contd2_Cpu ++;}
            
        d--;
		
        for (int j = 0; j < SIZE; j ++){
            if (grid[i][j] == 'X'){ contl ++;}
            if (grid[j][i] == 'X'){ contc ++;}
            if (grid[i][j] == 'O'){ contl2 ++;}
            if (grid[j][i] == 'O'){ contc2 ++;} 
        }
        if(contd2_Cpu == 2 || contc2 == 2 || contd_Cpu == 2 || contl2 == 2){
            if (contl2 == 2){
                for (int z = 0; z < SIZE; z++){
                    if (grid[i][z] == '?'){
                        grid[i][z] = 'O';
                        found = true;
                    }
                }
            }else if(contd_Cpu == 2){
                for (int z = 0; z < SIZE; z++){
                    if (grid[z][z] == '?'){
                        grid[z][z] = 'O';
                        found = true;
                    }
                }
            }else if(contc2 == 2){
                for (int z = 0; z < SIZE; z++){
                    if (grid[z][i] == '?'){
                        grid[z][i] = 'O';
                        found = true;
                    }
                }
            }else if(contd2_Cpu == 2){
                int x = 0;
				
                for (int z = SIZE - 1; z >= 0; z--){
                    if (grid[x][z] == '?'){
                        grid[x][z] = 'O';
                        found = true;
                    }
                    x++;
                }
            }
        }else{
            if (contl == 2){
                for (int z = 0; z < SIZE; z++){
                    if (grid[i][z] == '?'){
                        grid[i][z] = 'O';
                        found = true;
                    }
                }
            }else if(contd == 2){
                for (int z = 0; z < SIZE; z++){
                    if (grid[z][z] == '?'){
                        grid[z][z] = 'O';
                        found = true;
                    }
                }
            }else if(contc == 2){
                for (int z = 0; z < SIZE; z++){
                    if (grid[z][i] == '?'){
                        grid[z][i] = 'O';
                        found = true;
                    }
                }
            }else if(contd2 == 2){
                int x = 0;
				
                for (int z = SIZE - 1; z >= 0; z--){
                    if (grid[x][z] == '?'){
                        grid[x][z] = 'O';
                        found = true;
                    }
                    x++;
                }
            }
        }
        if(found){ break;}
    }
    if(!found){ cpu_easy(grid);}
}
void cpu_hard(char grid[SIZE][SIZE])
{
	Move bestMove = findBestMove(grid); 
	grid[bestMove.row][bestMove.col] = 'O';
} 

char player = 'O', opponent = 'X'; // Hidden global variable!!
  
// This function returns true if there are moves 
// remaining on the board. It returns false if 
// there are no moves left to play. 
bool isMovesLeft(char board[SIZE][SIZE]) 
{ 
    for (int i = 0; i<SIZE; i++) 
        for (int j = 0; j<SIZE; j++) 
            if (board[i][j]=='?') 
                return true; 
    return false; 
} 
  
// This is the evaluation function as discussed 
// in the previous article ( http://goo.gl/sJgv68 ) 
int evaluate(char b[SIZE][SIZE]) 
{ 
    // Checking for Rows for X or O victory. 
    for (int row = 0; row<SIZE; row++) 
    { 
        if (b[row][0]==b[row][1] && 
            b[row][1]==b[row][2]) 
        { 
            if (b[row][0]==player) 
                return +10; 
            else if (b[row][0]==opponent) 
                return -10; 
        } 
    } 
  
    // Checking for Columns for X or O victory. 
    for (int col = 0; col<SIZE; col++) 
    { 
        if (b[0][col]==b[1][col] && 
            b[1][col]==b[2][col]) 
        { 
            if (b[0][col]==player) 
                return +10; 
  
            else if (b[0][col]==opponent) 
                return -10; 
        } 
    } 
  
    // Checking for Diagonals for X or O victory. 
    if (b[0][0]==b[1][1] && b[1][1]==b[2][2]) 
    { 
        if (b[0][0]==player) 
            return +10; 
        else if (b[0][0]==opponent) 
            return -10; 
    } 
  
    if (b[0][2]==b[1][1] && b[1][1]==b[2][0]) 
    { 
        if (b[0][2]==player) 
            return +10; 
        else if (b[0][2]==opponent) 
            return -10; 
    } 
  
    // Else if none of them have won then return 0 
    return 0; 
} 
  
// This is the minimax function. It considers all 
// the possible ways the game can go and returns 
// the value of the board 
int minimax(char board[SIZE][SIZE], int depth, bool isMax) 
{ 
    int score = evaluate(board); 
  
    // If Maximizer has won the game return his/her 
    // evaluated score 
    if (score == 10) 
        return score; 
  
    // If Minimizer has won the game return his/her 
    // evaluated score 
    if (score == -10) 
        return score; 
  
    // If there are no more moves and no winner then 
    // it is a tie 
    if (isMovesLeft(board)==false) 
        return 0; 
  
    // If this maximizer's move 
    if (isMax) 
    { 
        int best = -1000; 
  
        // Traverse all cells 
        for (int i = 0; i<SIZE; i++) 
        { 
            for (int j = 0; j<SIZE; j++) 
            { 
                // Check if cell is empty 
                if (board[i][j]=='?') 
                { 
                    // Make the move 
                    board[i][j] = player; 
  
                    // Call minimax recursively and choose 
                    // the maximum value 
                    best = max( best, 
                        minimax(board, depth+1, !isMax) ); 
  
                    // Undo the move 
                    board[i][j] = '?'; 
                } 
            } 
        } 
        return best; 
    } 
  
    // If this minimizer's move 
    else
    { 
        int best = 1000; 
  
        // Traverse all cells 
        for (int i = 0; i<SIZE; i++) 
        { 
            for (int j = 0; j<SIZE; j++) 
            { 
                // Check if cell is empty 
                if (board[i][j]=='?') 
                { 
                    // Make the move 
                    board[i][j] = opponent; 
  
                    // Call minimax recursively and choose 
                    // the minimum value 
                    best = min(best, 
                           minimax(board, depth+1, !isMax)); 
  
                    // Undo the move 
                    board[i][j] = '?'; 
                } 
            } 
        } 
        return best; 
    } 
} 
  
// This will return the best possible move for the player 
Move findBestMove(char board[SIZE][SIZE]) 
{ 
    int bestVal = -1000; 
    Move bestMove; 
    bestMove.row = -1; 
    bestMove.col = -1; 
  
    // Traverse all cells, evaluate minimax function for 
    // all empty cells. And return the cell with optimal 
    // value. 
    for (int i = 0; i<SIZE; i++) 
    { 
        for (int j = 0; j<SIZE; j++) 
        { 
            // Check if cell is empty 
            if (board[i][j]=='?') 
            { 
                // Make the move 
                board[i][j] = player; 
  
                // compute evaluation function for this 
                // move. 
                int moveVal = minimax(board, 0, false); 
  
                // Undo the move 
                board[i][j] = '?'; 
  
                // If the value of the current move is 
                // more than the best value, then update 
                // best/ 
                if (moveVal > bestVal) 
                { 
                    bestMove.row = i; 
                    bestMove.col = j; 
                    bestVal = moveVal; 
                } 
            } 
        } 
    } 
  
    printf("The value of the best Move is : %d\n\n", 
            bestVal); 
  
    return bestMove; 
} 
bool score(int new_score, std::string load_name) // Keep track of best five scores.
{
	// Initializing variables.
	bool exists, high_score = false;
	string top_five[9];
	
	header();
	
	fstream myfile;
	myfile.open("ranking_gato.txt", ios::app);
	
	if (!myfile){
		cout << "Unable to open file";
		exit(1); //terminate with error
	}
	
	// Checking if file is empty. If it is initialize the file.
	myfile.seekg(0, ios::end);
	if (myfile.tellg() == 0){
		for (int i = 0; i <= 4; i++){
			myfile << "Player: 0\n";
		}
	}
	myfile.close();
	
	// Open the file and load values to array
	ifstream inFile;
	inFile.open("ranking_gato.txt");
		
	string data;
		
	// Odd indexes contain numbers and even contain names.
	for (int i = 0; inFile >> data; i++){
		top_five[i] = data;
	}
		
	inFile.close();
	
	load_name += ":";	// To format the name to the corresponding format.
	
	// If name already exists it will swap them to move up on the list.
	for (int i = 0; i <= 4; i++){
		if (load_name == top_five[2 * i]){ // names are located on the even indexes.
			if (new_score > stoi(top_five[2 * i + 1])){ // If new score of existing name is bigger record it, else dont.
				top_five[2 * i + 1] = to_string(new_score);	// Setting new high score.
				
				if (i > 0){	// The high score is not the top one so swap the score to its corresponding place on the list.
					while (stoi(top_five[2 * i - 1]) < new_score){
						string temp;
						//cout << "Swapping!\n";
						// Swap value
						temp = top_five[2 * i - 1];
						top_five[2 * i + 1] = temp;
						top_five[2 * i - 1] = to_string(new_score);
						
						// Swap names
						temp = top_five[2 * i - 2];
						top_five[2 * i] = temp;
						top_five[2 * i - 2] = load_name;
						i--;
						if (i == 0){ break;}
					}
				}
				high_score = true;	// We have a new high score and it will show on green!
			}
			exists = true;	// The name already existed on the list and no new name is added.
			break;
		}
	}

	if (exists == false){	// The new high score does not exist on the list so we are going to added it
							// if is on the top five scores.
		
		// Name does not exist so check if is on top 5
		for (int i = 4; i >= 0; i--){
			
			//cout << "loop\n";
			//cout << top_five[2 * i + 1] << endl;
			
			if (new_score < stoi(top_five[2 * i + 1])){ // It will check if the new score is bw 5-2.

				// If score is not the top one then added it and eliminate the lowes score on the list.
				// This works only if the best score is at most the second best.
				for (int j = 9; j >= 2 * i + 2; j--){
					top_five[j] = top_five[j - 2];
				}

				// Setting new high score!
				top_five[2 * i + 2] = load_name;
				top_five[2 * i + 3] = to_string(new_score);
				high_score = true;
				
			}
			if (i == 0){ //Right here if true means the second on the list is the new number one.
				// If the second score is higher than number one swap them.
				if (new_score > stoi(top_five[1])){
				
					// Swapping 1st and 2nd place. To be in correct order.
					for (int j = 9; j >= 2 * i + 2; j--){
						top_five[j] = top_five[j - 2];
					}

					top_five[2 * i + 2] = load_name;
					top_five[2 * i + 3] = to_string(new_score);
					
					string temp;
					// Swap value
					temp = top_five[1];
					top_five[3] = temp;
					top_five[1] = to_string(new_score);
					
					// Swap names
					temp = top_five[0];
					top_five[2] = temp;
					top_five[0] = load_name;
					
					high_score = true; // We have a new high score and it will show in green.
				}
			}
			
		}
	}
	
	// opening the file to write new high scores.
	ofstream oFile;
	oFile.open("ranking_gato.txt");
	
	if (!oFile){
		
		cout << "Unable to open file";
		exit(2); //terminate with error
	}
	
	for (int i = 0; i < 10; i++){
		if (i % 2 == 0){
			oFile << top_five[i] << " ";
		} else{
			oFile << top_five[i] << endl;
		}
	}
	
	return high_score;	// If this is false no new high score was recorded.
}
void view_score(std::string player, int score)
{
	header();
	
	fstream myfile;
	myfile.open("ranking_gato.txt", ios::app);
	
	if (!myfile){
		
		cout << "Unable to open file";
		exit(1); //terminate with error
	}
	
	// Checking if file is empty
	myfile.seekg(0, ios::end);
	if (myfile.tellg() == 0){
		for (int i = 0; i <= 4; i++){
			myfile << "Player: 0\n";
		}
	}
	myfile.close();
	
	// Open the file and load values to array
	ifstream inFile;
	inFile.open("ranking_gato.txt");
	
	player += ":";

	string data;
	
	// Odd indexes contain numbers and even contain names. Displaying the scores!
	for (int i = 0; inFile >> data; i++){
		if (i % 2 == 0){
			if (player == data){
				cout << BOLDGREEN << data << RESET << " ";
			}else{			
				cout << data << " ";
			}
		}else{
			cout << data << endl;
		}
	}
		
	inFile.close();
}