#pragma once
#include <SFML/Graphics.hpp>
#include "SNElement.h"
#include "Game_Controller.h"


/*	Group1: SNElement declarations
*	Group2: SNPage declarations(SNElements are in pages)
*
*	Group3: SNElements' function initializations
*	Group4: SNEPages' function initializations */

// *******************************************************************************************************
// Group1: SNElement declarations
void temp() {}
void function_difficulty();
void function_open_play();
void function_open_home();

void function_player1();
void function_color1();
void function_player2();
void function_color2();
void function_starting_player();

SNRadio_Button* rb_difficulty;
SNRadio_Button rb_easy("Easy", 10, 4, 3, 1, &function_difficulty, &rb_difficulty);
SNRadio_Button rb_medium("Medium", 14, 4, 4, 1, &function_difficulty, &rb_difficulty);
SNRadio_Button rb_hard("Hard", 19, 4, 3, 1, &function_difficulty, &rb_difficulty);

SNLabel l_connect_four("Connect Four", true, 9, .5, 14, 1.5);
SNLabel l_player1("Player1:", false, 10.2, 6.1, 4, 0.6);
SNLabel l_color1("Color:", false, 10.2, 7.6, 4, 0.6);
SNLabel l_player2("Player2:", false, 10.2, 9.6, 4, 0.6);
SNLabel l_color2("Color:", false, 10.2, 11.1, 4, 0.6);
SNLabel l_starting_player("Starting P:", false, 10.2, 12.6, 4, 0.6);

SNButton b_player1(my_game.player1_type(), 16, 6, 6, 1, &function_player1);
SNButton b_color1(my_game.player1_color(), 16, 7.5, 6, 1, &function_color1);
SNButton b_player2(my_game.player2_type(), 16, 9.5, 6, 1, &function_player2);
SNButton b_color2(my_game.player2_color(), 16, 11, 6, 1, &function_color2);
SNButton b_starting_player(my_game.starting_player_name(), 16, 12.5, 6, 1, &function_starting_player);
SNButton b_play("Play", 14.5, 14, 3, 1, &function_open_play);
vector<SNElement*> main_elements = {
	&rb_easy,
	&rb_medium,
	&rb_hard,
	&l_connect_four,
	&l_player1,
	&l_color1,
	&l_player2,
	&l_color2,
	&l_starting_player,
	&b_player1,
	&b_color1,
	&b_player2,
	&b_color2,
	&b_starting_player,
	&b_play
};

SNLabel l_game_log("GAME LOG", true, .9, 4, 6, .8);
SNButton b_undo_move("Undo Move", 25, 4, 6, 1, &temp);
SNButton b_restart_game("Restart Game", 25, 6, 6, 1, &temp);
SNButton b_home_screen("Home Screen", 25, 8, 6, 1, &function_open_home);

vector<SNElement*> play_elements = {
	&l_connect_four,
	&l_game_log,
	&b_undo_move,
	&b_restart_game,
	&b_home_screen
};


// *******************************************************************************************************
// Group2 : SNPage declarations(SNElements are in pages)
void setup_main();
void draw_main();
void setup_play();
void draw_play();

SNPage main_page("Main Page", main_elements, &setup_main, &draw_main);
SNPage play_page("Play Page", play_elements, &setup_play, &draw_play);


// *******************************************************************************************************
// Group3 : SNElements' function initializations
void function_difficulty() {
	my_app.refresh_page();
	SNRadio_Button temp_rb = **(rb_easy.current_rb);
	my_game.set_bot_difficulty(temp_rb.name);
}
void function_open_play() {
	my_app.activate_page(&play_page);
}
void function_open_home() {
	my_app.activate_page(&main_page);
}

void function_player1() {
	my_game.player1_toggle_type();
	b_player1.name = my_game.player1_type();
	my_app.current_page->draw_page();
}
void function_player2() {
	my_game.player2_toggle_type();
	b_player2.name = my_game.player2_type();
	my_app.current_page->draw_page();
}
void function_color1() {
	my_game.player1_toggle_color();
	b_color1.name = my_game.player1_color();
	b_color2.name = my_game.player2_color();
	my_app.current_page->draw_page();
}
void function_color2() {
	my_game.player2_toggle_color();
	b_color2.name = my_game.player2_color();
	b_color1.name = my_game.player1_color();
	my_app.current_page->draw_page();
}
void function_starting_player() {
	my_game.toggle_starting_player();
	b_starting_player.name = my_game.starting_player_name();
	my_app.current_page->draw_page();
}

// *******************************************************************************************************
// Group4 : SNEPages' function initializations 
void setup_main() {

}
void draw_main() {
	stroke_weight(5);
	stroke(255);
	fill(220);
	rect(9, 3, 14, 13, 25);
}
void setup_play() {

}
void draw_play() {
	stroke_weight(5);
	fill(220);
	stroke(255);
	rect(9, 4, 14, 12.5, 25);
	rect(25, 10, 6, 6.5, 25);
	rect(1, 4, 6, 12.5, 25);
}