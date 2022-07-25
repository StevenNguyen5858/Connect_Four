// base on the connect 4 of  Stratzilla, Stratzilla github: https://github.com/stratzilla/connect-four
#include <stdio.h>
#include <iostream>
#include <vector>
#include <limits.h>
#include <array>
#include <sstream>

#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

using namespace std;

// function define
int AI_move(int board[6][7], int color_index);
int find_opponent_color(int board[6][7], int AI);
array<int, 2> mini_max(int board[6][7], int depth, int alpha, int beta, int AI_player, int opponent, int minimax_player, int turn);
bool winning_move(int board[6][7], int player);
int check_four(int board[6][7], int row, int col, int moveX, int moveY, int player);
int tabScore(int board[6][7], int AI_player, int opponent, int p);
int scoreSet(vector< int> v, int AI_player, int opponent, int p);


// the one return column AI will play
int AI_move(int board[6][7], int color_index) {
	//variable
	//turn used in the min_max algorithm to find the best move
	// AI_player and opponent store the value of the token for AI and opponent, which is used to decide which token belong to
	//Ai_board make the copy of the board so it will not affect the board
	int turn = 0;
	int AI_player = color_index;
	int opponent = find_opponent_color(board, AI_player);
	int AI_board[6][7];
	//function
	// copy the board to AI_board, and count turn
	for (int r = 0; r < 6; r++) {
		for (int c = 0; c < 7; c++) {
			AI_board[r][c] = board[r][c];
			if (board[r][c] != -1) {
				turn++;
			}
		}
	}
	if (turn == 0) {
		return 3;
	}
	else {
		return mini_max(AI_board, 5, INT_MIN, INT_MAX, AI_player, opponent, AI_player, turn)[0];
	}
}

// find the color of the opponent
int find_opponent_color(int board[6][7], int AI_color) {
	for (int r = 0; r < 6; r++) {
		for (int c = 0; c < 7; c++) {
			if (board[r][c] != AI_color && board[r][c] != -1) {
				return board[r][c];
			}
		}
	}
	if (AI_color == 3) {
		return 0;
	}
	else {
		return AI_color + 1;
	}
}

// the minmax algorithm
/**
depth is the depth of the search,
alf is alpha
bet is beta
AI_player is the value of the token AI_play
opponent is the value of the opponent token
min_max_player decide who place the token
turn is the current turn atm.

*/

bool winning_move(int board[6][7], int player) {
	vector<int> x_vectors = { 0,1,1,1 };
	vector<int> y_vectors = { 1,0,1,-1 };
	for (int a = 0; a < x_vectors.size(); a++) {
		for (int row = 0; row < 6; row++) {
			for (int col = 0; col < 7; col++) {
				if (check_four(board, row, col, x_vectors[a], y_vectors[a], player) != -1) {
					return true;
				}
			}
		}
	}
	return false;
}

//check win function
int check_four(int board[6][7], int row, int col, int moveX, int moveY, int player) {
	//check if it will go outside the board or not, if outside, return -1 (no one win)
	if ((row + moveY * 3) < 0) {
		return -1;
	}
	if ((row + moveY * 3) >= 6) {
		return -1;
	}
	if ((col + moveX * 3) < 0) {
		return -1;
	}
	if ((row + moveX * 3) >= 7) {
		return -1;
	}
	//check if any four have the same color, if yes, return the color)
	// if all 4 has the same value, return the value.
	if (board[row][col] == board[row + moveY][col + moveX] && board[row][col] == board[row + 2 * moveY][col + 2 * moveX] && board[row][col] == board[row + 3 * moveY][col + 3 * moveX] && board[row][col] != -1) {
		return board[row][col];
	}
	else {
		return -1;
	}
}

// the minmax algorithm
/**
depth is the depth of the search,
alf is alpha
bet is beta
AI_player is the value of the token AI_play
opponent is the value of the opponent token
minimax_player decide who place the token
turn is the current turn atm.
*/
array<int, 2> mini_max(int board[6][7], int depth, int alpha, int beta, int AI_player, int opponent, int minimax_player, int turn) {
	// if the depth =0, or the game end with either 1 win or draw
	if (depth == 0 || turn == 42 || winning_move(board, opponent) || winning_move(board, AI_player)) {
		if (winning_move(board, AI_player)) {
			return array<int, 2>{-1, INT_MAX};
		}
		else if (winning_move(board, opponent)) {
			return array<int, 2>{-1, INT_MIN};
		}
		else if (turn == 42) {
			return array<int, 2>{-1, 0};
		}
		else {
			return array<int, 2>{-1, tabScore(board, AI_player, opponent, AI_player)};
		}

	}
	// if AI(max player)
	if (minimax_player == AI_player) {
		// value to compare, col to return
		int value = INT_MIN;
		int col = -1;
		for (int c = 0; c < 7; c++) {
			if (board[0][c] == -1) {
				//create a newboard and copy the board to the new one.
				int new_board[6][7];
				for (int r = 0; r < 6; r++) {
					for (int c = 0; c < 7; c++) {
						new_board[r][c] = board[r][c];  //just straight copy
					}
				}
				//drop the token
				for (int r = 5; r >= 0; r--) {
					if (new_board[r][c] == -1) {
						//first available spot
						new_board[r][c] = minimax_player;  //set piece
						break;
					}
				}
				int new_score = mini_max(new_board, depth - 1, alpha, beta, AI_player, opponent, opponent, turn + 1)[1];
				if (new_score > value) {
					value = new_score;
					col = c;
				}
				alpha = max(alpha, value);
				//reduce the search time
				if (alpha >= beta) { break; }
			}
		}
		return array<int, 2>{col, value};
	}
	// if opponent (min player)
	else {//if AI_player then
		// value to compare, col to return
		int value = INT_MAX;
		int col = -1;
		for (int c = 0; c < 7; c++) {
			if (board[0][c] == -1) {
				//create a newboard and copy the board to the new one.
				int new_board[6][7];
				for (int r = 0; r < 6; r++) {
					for (int c = 0; c < 7; c++) {
						new_board[r][c] = board[r][c];  //just straight copy
					}
				}
				//drop the token
				for (int r = 5; r >= 0; r--) {
					if (new_board[r][c] == -1) {
						//first available spot
						new_board[r][c] = minimax_player;  //set piece
						break;
					}
				}
				int new_score = mini_max(new_board, depth - 1, alpha, beta, AI_player, opponent, AI_player, turn + 1)[1];
				if (new_score < value) {
					value = new_score;
					col = c;
				}
				beta = min(beta, value);
				//reduce the search time
				if (alpha >= beta) { break; }
			}
		}
		return array<int, 2>{col, value};
	}
}

/**
function to tabulate current board "value"
b - the board to evaluate
p - the player to check score of
return - the board score
 */
int tabScore(int board[6][7], int AI_player, int opponent, int p) {
	int score = 0;
	//score in center column
	for (int r = 0; r < 6; r++) {
		if (board[r][3] == p) {
			score += 3;
		}
	}
	vector< int> set(4);
	/**
	 * horizontal checks, we're looking for sequences of 4
	 * containing any combination of AI, PLAYER, and empty pieces
	 */
	for (int r = 0; r < 6; r++) {
		for (int c = 0; c < 4; c++) {
			for (int i = 0; i < 4; i++) {
				set[i] = board[r][c + i];
			}
			score += scoreSet(set, AI_player, opponent, p); // find score
		}
	}
	// vertical
	for (int c = 0; c < 7; c++) {
		for (int r = 0; r < 3; r++) {
			for (int i = 0; i < 4; i++) {
				set[i] = board[r + i][c];
			}
			score += scoreSet(set, AI_player, opponent, p);
		}
	}
	// diagonals
	for (int r = 0; r < 6 - 3; r++) {
		for (int c = 0; c < 7 - 3; c++) {
			for (int i = 0; i < 4; i++) {
				set[i] = board[r + i][c + i];
			}
			score += scoreSet(set, AI_player, opponent, p);
		}
	}
	for (int r = 0; r < 6 - 3; r++) {
		for (int c = 0; c <= 7-3; c++) {
			for (int i = 0; i < 4; i++) {
				set[i] = board[r + 3 -i][c + i];
			}
			score += scoreSet(set, AI_player, opponent, p);
		}
	}
	return score;
}

/**
 * function to find the score of a set of 4 spots
 * @param v - the row/column to check
 * @param p - the player to check against
 * @return - the score of the row/column
 */
int scoreSet(vector< int> v, int AI_player, int opponent, int p) {
	int score = 0;
	int opp_piece = (p == AI_player) ? opponent : AI_player;
	int p_counter = 0;
	int empty = 0;
	int opp_counter = 0;
	for (int i = 0; i < 4; i++) {
		if (v[i] == p) {
			p_counter++;
		}
		else if (v[i] == opp_piece) {
			opp_counter++;
		}
		else {
			empty++;
		}
	}
	if (p_counter == 4) { score += 500001; } // preference to go for winning move vs. block
	else if (p_counter == 3 && empty == 1) { score += 5000; }
	else if (p_counter == 2 && empty == 2) { score += 500; }
	else if (opp_counter == 2 && empty == 2) { score -= 501; } // preference to block
	else if (opp_counter == 3 && empty == 1) { score -= 5001; } // preference to block
	else if (opp_counter == 4) { score -= 500000; }
	return score;
}
