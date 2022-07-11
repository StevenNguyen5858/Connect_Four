#pragma once
#include "SNElement.h"

class player {
	// Access specifier:
public:
	string name;
	int color = 0; // 0(black), 1(red)
	bool isBot = false;
	
	// Default Constructor:
	player() {
	}
	// Parameterized Constructor:
	player(string name, int color, bool isBot) {
		this->name = name;
		this->color = color;
		this->isBot = isBot;
	}

};


class Game_Controller : public SNElement {
	// Access specifier:
private:
	int bot_difficulty = 0; // 0(easy), 1(medium), 2(hard)
	player player1;
	player player2;
	int starting_player = 1; // 1(player1), 2(player2)
	int board[6][7];
	void (*refresh)();
public:

	// Default Constructor:
	Game_Controller() {}
	// Parameterized Constructor:
	Game_Controller(string name, double x, double y, double w, double h, void (*refresh)())
	: SNElement(name, x, y, w, h){
		type = "Game Controller";
		this->refresh = refresh;
		player1.~player();
		new(&player1) player("Player 1", 0, false);
		player2.~player();
		new(&player2) player("Player 2", 1, false);
		
		
		for (int x = 0; x < 7; x++) {
			for (int y = 0; y < 6; y++) {
				board[y][x] = -1;
			}
		}
	}

	// Method
	void draw_element() {
		// Board outline
		stroke_weight(2);
		fill(220);
		stroke(255);
		rect(x, y, w, h, 25);
		// Tokens
		
		
		for (int x = 0; x < 7; x++) {
			for (int y = 0; y < 6; y++) {
				if (board[y][x] == 0) {
					fill(0);
				}
				else if (board[y][x] == 1) {
					fill(sf::Color(255, 0, 0));
				} else {
					fill(32);
				}
				circle(this->x+.5+(2*x), this->y+.5+(2*y), 1.5);
			}
		}
	}
	// (Board) Methods
	void place_token(int x) {
		int drop_col = (x - 9) / 2;
		if (drop_col > 6 || drop_col < 0) {
			return;
		}
		for (int r = 5; r >= 0; r--) {
			if (board[r][drop_col] == -1) {
				board[r][drop_col] = 1;
				break;
			}
			else {
			}
		}
		refresh();
	}
	void restart() {
		for (int x = 0; x < 7; x++) {
			for (int y = 0; y < 6; y++) {
				board[y][x] = -1;
			}
		}
		refresh();
	}

	// (Settings) Setter Methods
	void player1_toggle_color() {
		(player1.color == 0) ? (player1.color = 1) : (player1.color = 0);
		if (player1.color == player2.color) {
			player2_toggle_color();
		}
	}
	void player2_toggle_color() {
		(player2.color == 0) ? (player2.color = 1) : (player2.color = 0);
		if (player1.color == player2.color) {
			player1_toggle_color();
		}
	}
	void player1_toggle_type() {
		(player1.isBot) ? (player1.isBot = false) : (player1.isBot = true);
	}
	void player2_toggle_type() {
		(player2.isBot) ? (player2.isBot = false) : (player2.isBot = true);
	}
	void toggle_starting_player() {
		(starting_player == 1) ? starting_player = 2 : starting_player = 1;
	}
	void set_bot_difficulty(string difficulty) {
		if (difficulty == "Easy") {
			bot_difficulty = 0;
		}
		if (difficulty == "Medium") {
			bot_difficulty = 1;
		}
		if (difficulty == "Hard") {
			bot_difficulty = 2;
		}
	}

	// (Settings) Getter Methods:
	string player1_color() {
		string color;
		(player1.color == 0) ? (color = "Black") : (color = "Red");
		return color;
	}
	string player2_color() {
		string color;
		(player2.color == 0) ? (color = "Black") : (color = "Red");
		return color;
	}
	string player1_type() {
		(player1.isBot) ? player1.name = "Bot1" : player1.name = "Player1";
		return player1.name;
	}
	string player2_type() {
		(player2.isBot) ? player2.name = "Bot2" : player2.name = "Player2";
		return player2.name;
	}
	string starting_player_name() {
		string player_name;
		(starting_player == 1) ? player_name = player1.name : player_name = player2.name;
		return player_name;
	}
};
