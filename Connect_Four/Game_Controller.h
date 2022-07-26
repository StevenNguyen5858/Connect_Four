#pragma once
#include <stack>
#include "SNElement.h"
#include "AI_bot.h"


class player {
	// Access specifier:
public:
	string name;
	bool isBot = false;
	int win_score = 0;

	int color_index = 0; // 0(green), 1(red), 2(yellow), 3(blue)
	sf::Color color = sf::Color::White;
	string color_name = "White";
	
	// Default Constructor:
	player() {
	}
	// Parameterized Constructor:
	player(string name, int color_index, bool isBot) {
		this->name = name;
		this->color_index = color_index;
		this->isBot = isBot;
		update_color();
	}

	// Methods:
	void update_color() {
		if (color_index == 0) {
			color = sf::Color(0, 120, 0);
			color_name = "Green";
		}
		if (color_index == 1) {
			color = sf::Color(255, 0, 0);
			color_name = "Red";
		}
		if (color_index == 2) {
			color = sf::Color(255, 174, 0);
			color_name = "Yellow";
		}
		if (color_index == 3) {
			color = sf::Color(0, 255, 255);
			color_name = "Blue";
		}
	}
	int get_move(int board[6][7]) {
		if (isBot) {
			return AI_move(board, color_index);
		}
	}
};


class Game_Log : public SNElement {
	// Access specifier:
public:
	void (*refresh)();
	string text_old;
	string text_new = "";
	vector<string> texts = {};
	stack<string> popped_texts = {};
	vector<pair<int, int>> game_turns = {};
	stack<pair<int, int>> popped_turns = {};
	

	// Default Constructor:
	Game_Log() {
	}
	// Parameterized Constructor:
	Game_Log(string name, double x, double y, double w, double h, void (*refresh)())
		: SNElement(name, x, y, w, h) {
		this->refresh = refresh;

	}

	// Helper Methods:
	void clear() {
		texts.clear();
	}
	void format_text(string new_line) {
		// Break text info into the various lines.
		string remaining_text = new_line;

		int char_per_line = 0;
		float char_w = text_width("M", 0.4);

		for (int I = 0; I < remaining_text.length(); I++) { // Count up until text_width is at max size.
			if ((0.4 + text_width(remaining_text.substr(0, I), 0.4)) > this->w - 0.4 - char_w) {
				for (int i = I; i > 0; i--) { // Count down until first space from the end.
					if (remaining_text.substr(i, 1) == " ") {
						texts.push_back(remaining_text.substr(0, i + 1));
						remaining_text = remaining_text.substr(i + 1);
						I = 0;
						break;
					}
				}
			}
			
		}
		texts.push_back(remaining_text);
	}
	void push_back(string new_line) {
		format_text(new_line);
		refresh();
	}
	void log_turn(pair<int, int> cord_pair) {
		game_turns.push_back(cord_pair);
	}
	pair<int, int> pop_previous_turn() {
		if (game_turns.empty() == false) {
			pair<int, int> previous_turn = game_turns.back();
			game_turns.pop_back();
			popped_turns.push(previous_turn);

			string text = texts.back();
			texts.pop_back();
			popped_texts.push(text);
			
			return previous_turn;
		}
		// If empty, cannot pop turn.
		return make_pair(-1, -1);
	}
	pair<int, int> redo_turn() {
		if (popped_turns.size() == 0) {
			return make_pair(-1, -1);
		}
		pair<int, int> last_undo_move = popped_turns.top();
		popped_turns.pop();
		game_turns.push_back(last_undo_move);

		string text = popped_texts.top();
		popped_texts.pop();
		texts.push_back(text);

		return last_undo_move;
	}
	// Virtual Methods:
	void draw_element() {
		// Full Backdrop
		stroke_weight(2);
		fill(220);
		stroke(255);
		rect(x, y, w, h, 25);
		// Title Backdrop
		stroke_weight(2);
		fill(220);
		stroke(255);
		rect(x, y, w, 1, 25);
		// Title
		fill(255);
		all_centered_text(name, x, y, w, 1, 0.8);

		// Draw textbox text
		int max_lines = (this->h - 1) / 0.8;
		int starting_i = (texts.size() > max_lines) ? texts.size() - max_lines : 0;
		for (int i = starting_i; i < texts.size(); i++) {
			int y_offset = i - starting_i;
			y_centered_text(texts[i], x + 0.2, y + (0.8 * y_offset) + 1, 0.8, 0.4);
		}
	}
};


class Game_Controller : public SNElement {
	// Access specifier:
private:
	int bot_difficulty = 0; // 0(easy), 1(medium), 2(hard)
	player player1;
	player player2;
	int starting_player = 0; // 0(player1), 1(player2)

	
	int board[6][7];
	void (*refresh)();
	Game_Log* gl;
	double hover_p = 15.25;
public:
	bool game_paused = false;
	bool log_paused = false;
	bool player_has_won = false;
	vector<player*> players = { &player1, &player2 };
	int current_player;
	bool game_started = false;
	bool isMultiplayer = false;

	// Default Constructor:
	Game_Controller() {}
	// Parameterized Constructor:
	Game_Controller(string name, double x, double y, double w, double h, void (*refresh)(), Game_Log *gl)
	: SNElement(name, x, y, w, h){
		type = "Game Controller";
		this->refresh = refresh;
		this->gl = gl;

		player1.~player();
		new(&player1) player("Player 1", 0, false);
		player2.~player();
		new(&player2) player("Player 2", 1, false);
		this->current_player = starting_player;
		
		for (int x = 0; x < 7; x++) {
			for (int y = 0; y < 6; y++) {
				board[y][x] = -1;
			}
		}
	}

	// Methods
	void draw_element() {
		// Board outline
		stroke_weight(2);
		fill(220);
		stroke(255);
		rect(x, y, w, h, 25);
		// Tokens
		
		stroke(50);
		stroke_weight(2);
		for (int x = 0; x < 7; x++) {
			for (int y = 0; y < 6; y++) {
				if (board[y][x] == 0) {
					fill(player1.color);
				}
				else if (board[y][x] == 1) {
					fill(player2.color);
				} else {
					fill(32);
				}
				circle(this->x+.5+(2*x), this->y+.5+(2*y), 1.5);
			}
		}
		image(player_icons[players[current_player]->color_index], hover_p, 2.25, 1.5, 1.5);
	}

	// (Board) Win Handler
	int helper_win(int last_token_x, int last_token_y, int vx, int vy) {
		// Find a wall by following a vector <x,y>
		int curr_x = last_token_x;
		int curr_y = last_token_y;
		while (0 <= curr_y && curr_y <= 5 && 0 <= curr_x && curr_x <= 6) {
			curr_x += vx;
			curr_y += vy;
		}
		curr_x -= vx;
		curr_y -= vy;
		// Go backwards while counting for a win.
		int player1_count = 0;
		int player2_count = 0;
	
		while (0 <= curr_y && curr_y <= 5 && 0 <= curr_x && curr_x <= 6) {
			if (board[curr_y][curr_x] == 0) {
				player1_count += 1;
			}
			else {
				player1_count = 0;
			}
			if (board[curr_y][curr_x] == 1) {
				player2_count += 1;
			}
			else {
				player2_count = 0;
			}

			if (player1_count >= 4 && player2_count >= 4) {
				return -2;
			}
			if (player1_count >= 4) {
				return 0;
			}
			if (player2_count >= 4) {
				return 1;
			}
			curr_x = curr_x - vx;
			curr_y = curr_y - vy;
		}
		return -1;
		
	}
	int check_win(int last_token_x, int last_token_y) {
		vector<int> x_vectors = { 0, 1, 1, 1};
		vector<int> y_vectors = { 1, 0, 1, -1};
		int winner;
		for (int a = 0; a < x_vectors.size(); a++) {
			int winner = helper_win(last_token_x, last_token_y, x_vectors[a], y_vectors[a]);
			if (winner != -1) {
				return winner;
			}
		}
		return -1;
	}

	// (Board) Events
	void start_game() {
		current_player = starting_player;
		game_started = true;
		cout << "GAME STARTED" << endl;
	}
	void event_parser(string event, vector<string>* keys, vector<string>* values) {
		string line;
		vector<string> lines = {};
		for (int i = 0; i < event.length(); i++) {
			if (event.substr(i, 1) == ",") {
				lines.push_back(line);
				line = "";
			}
			else {
				line += event.substr(i, 1);
			}
		}
		lines.push_back(line);

		string temp_key;
		string temp_value;
		int key_end_pos;
		for (int i = 0; i < lines.size(); i++) {
			if (lines[i].substr(0, 1) != "0") {
				key_end_pos = stoi(lines[i].substr(0, 1));
				temp_key = lines[i].substr(1, key_end_pos - 2);
				temp_value = lines[i].substr(key_end_pos, lines[i].length() - key_end_pos);
				keys->push_back(temp_key);
				values->push_back(temp_value);

				temp_key = "";
				temp_value = "";
			}
		}
	}
	void game_event(string event) {
		string event1;
		int from;
		int pos;
		
		//7Event:Mouse_Move,9Hover_P:" + to_string(grid_x)
		// Process game events first.
		vector<string> keys = {};
		vector<string> values = {};
		event_parser(event, &keys, &values);
		
		for (int i = 0; i < keys.size(); i++) {
			if (keys[i] == "Event") {
				event1 = values[i];
			}
			if (keys[i] == "From") {
				from = stoi(values[i]);
			}
			if (keys[i] == "Pos") {
				pos = stoi(values[i]);
			}
			if (keys[i] == "Hover_P") {
				double temp_hover_p = stoi(values[i]);
				if (x + 0.25 <= temp_hover_p && temp_hover_p < x + w - 0.25) {
					hover_p = temp_hover_p + 0.25;
				}
			}
		}
		// Then run through turn sequence.
		if (game_paused) {
			if (log_paused == false) {
				gl->push_back("Press Restart Game for new match.");
				log_paused = true;
			}
			return;
		}
		if (event1 == "Place_Token") {
			if (players[from]->isBot) {
				gl->push_back(place_token(players[from]->get_move(board), from));
			}
			else {
				gl->push_back(place_token(pos, from));
			}
		}
		if (event1 == "Mouse_Move") {
			placement_indicator(hover_p);
		}
	}
	void placement_indicator(double hover_pos) {
		refresh();
		/*
		cout << "TESTING MOUSE MOVE INDICATOR:" << hover_pos << endl;
		
		fill(255);
		stroke(0);
		stroke_weight(2);
		rect(1,1,10,10);
		refresh();
		*/
	}
	string place_token(int drop_col, int current_player) {
		string message = "";
		
		if (drop_col > 6 || drop_col < 0) {
			return "Click a column to make token placement.";
		}
		for (int r = 5; r >= 0; r--) {
			if (board[r][drop_col] == -1) {
				gl->log_turn(make_pair(r, drop_col));
				if (players[0]->isBot && players[1]->isBot) {
					hover_p = 9 + (drop_col * 2) + 0.25;
				}
				board[r][drop_col] = current_player;
				this->current_player = (current_player == 0) ? 1 : 0; // rotate turn
				int result = check_win(drop_col, r);
				if (result == 0 || result == 1) {
					players[result]->win_score += 100;
					message = players[result]->name + " has won this match.";
					game_paused = true;
					player_has_won = true;
				}
				else {
					message = players[current_player]->name + " (" + to_string(drop_col) + "," + to_string(r) + ").";
				}
				break;
			}
			else {
				message = players[current_player]->name + " attempted invalid move.";
			}
		}

		refresh();
		return message;
	}
	void undo() { // Undo move, and remove last message from log.
		if (game_paused || log_paused) {
			return;
		}
		pair<int,int> cord_pair = gl->pop_previous_turn();
		if (cord_pair.first == -1) {
			return;
		}
		board[cord_pair.first][cord_pair.second] = -1;
		this->current_player = (current_player == 0) ? 1 : 0; // rotate turn
		refresh();
	}
	void restart() {
		for (int x = 0; x < 7; x++) {
			for (int y = 0; y < 6; y++) {
				board[y][x] = -1;
			}
		}
		game_paused = false;
		log_paused = false;
		player_has_won = false;
		hover_p = 15.25;
		gl->clear();
		refresh();
	}

	void next_move() {
		if (!game_paused && !log_paused) {
			return;
		}
		pair<int, int> cord_pair = gl->redo_turn();
		if (cord_pair.first == -1) {
			return;
		}
		board[cord_pair.first][cord_pair.second] = players[current_player]->color_index;
		this->current_player = (current_player == 0) ? 1 : 0; // rotate turn
		refresh();
	}
	void previous_move() {
		if (!game_paused && !log_paused) {
			return;
		}
		pair<int, int> cord_pair = gl->pop_previous_turn();
		if (cord_pair.first == -1) {
			return;
		}
		board[cord_pair.first][cord_pair.second] = -1;
		this->current_player = (current_player == 0) ? 1 : 0; // rotate turn
		refresh();
	}
	void revert_review() {
		pair<int, int> cord_pair = gl->redo_turn();
		while (cord_pair.first != -1) {
			board[cord_pair.first][cord_pair.second] = players[current_player]->color_index;
			this->current_player = (current_player == 0) ? 1 : 0; // rotate turn
			cord_pair = gl->redo_turn();
			refresh();
		}
	}

	// (Settings) Setter Methods
	void player1_toggle_color() {
		(player1.color_index < 3) ? (player1.color_index += 1) : (player1.color_index = 0);
		player1.update_color();
		if (player1.color == player2.color) {
			player2_toggle_color();
		}
	}
	void player2_toggle_color() {
		(player2.color_index < 3) ? (player2.color_index += 1) : (player2.color_index = 0);
		player2.update_color();
		if (player2.color == player1.color) {
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
		(starting_player == 0) ? starting_player = 1 : starting_player = 0;
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
		return player1.color_name;
	}
	string player2_color() {
		return player2.color_name;
	}
	string player1_type() {
		(player1.isBot) ? player1.name = "Bot1" : player1.name = "Player1";
		return player1.name;
	}
	string player2_type() {
		(player2.isBot) ? player2.name = "Bot2" : player2.name = "Player2";
		return player2.name;
	}
	player active_player() {
		return *players[current_player];
	}
	string starting_player_name() {
		string player_name;
		(starting_player == 0) ? player_name = player1.name : player_name = player2.name;
		return player_name;
	}
};


class lobby : public SNElement {
	// Access specifier:
public:
	string name;
	vector<player*> players = {};
	double line_size = 0.8;
	double text_size = 0.6;

	// Default Constructor:
	lobby() {
	}
	// Parameterized Constructor:
	lobby(string name, double x, double y, double w, double h, vector<player*> players)
		: SNElement(name, x, y, w, h) {
		this->name = name;
		this->players = players;
	}

	// Methods:
	void draw_element() {
		fill(255);
		stroke_weight(1);
		y_centered_text(name, x+0.2, y, line_size, text_size);

		stroke(0);
		for (int i = 0; i < players.size(); i++) {
			fill(players[i]->color);
			rect(x, y + (line_size * (i + 1)), w, line_size,50);
		}
		
		fill(255);
		for (int i = 0; i < players.size(); i++) {
			y_centered_text(players[i]->name, x + line_size + 0.2, y + (line_size * (i + 1)), line_size, text_size);
			double score_xpos = x + w - text_width(to_string(players[i]->win_score), text_size) - 0.2;
			y_centered_text(to_string(players[i]->win_score), score_xpos, y + (line_size * (i + 1)), line_size, text_size);
		}

		for (int i = 0; i < players.size(); i++) {
			image(player_icons[players[i]->color_index], x + 0.2, y + (line_size * (i + 1)), line_size, line_size);
		}
	}
};