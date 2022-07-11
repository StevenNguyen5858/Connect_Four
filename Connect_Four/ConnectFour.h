#pragma once
#include <SFML/Graphics.hpp>
#include "SNElement.h"
#include "Game_Controller.h"
#include "SNPage.h"


/*	Group1: SNElement declarations
*	Group2: SNPage declarations(SNElements are in pages)
*
*	Group3: SNElements' function initializations
*	Group4: SNEPages' function initializations */

// *******************************************************************************************************
// Group1: SNElement declarations. Pages: title_page, solo_setup_page, play_page
void temp() {}

// title_page elements:
void function_open_multiplayer();
void function_open_solo_play();
void function_open_options();
void function_refresh_title();

SNOption o_multiplayer("Multiplayer", 0, 0, 0, 0, &function_open_multiplayer);
SNOption o_solo_play("Solo Play", 0, 0, 0, 0, &function_open_solo_play);
SNOption o_options("Options", 0, 0, 0, 0, &function_open_options);
vector<SNOption*> title_menu_options = {
	&o_multiplayer,
	&o_solo_play,
	&o_options
};
SNMenu m_title("Connect IV Menu", 4, 10, 0, 1, title_menu_options, &function_refresh_title);
SNLabel l_connect4_title("Connect IV", false, 4, 5, 0, 2, 1.5);
vector<SNElement*> title_elements = {
	&l_connect4_title,
	&m_title,
};


// multiplayer_lobby_page elements:
void function_start_match();
void function_setup_game();
void function_lobby_to_home();
// void function_open_options() <- a duplicate use
void function_refresh_multiplayer_lobby();

SNOption o_start_match("Start Match", 0, 0, 0, 0, &function_open_multiplayer);
SNOption o_setup_game("Setup Game", 0, 0, 0, 0, &function_open_multiplayer);
SNOption o_spacer(" ", 0, 0, 0, 0, &temp);
SNOption o_m_options("Options", 0, 0, 0, 0, &function_open_multiplayer);
SNOption o_mlobby_to_home("Title Screen", 0, 0, 0, 0, &function_lobby_to_home);
vector<SNOption*> multiplayer_lobby_menu_options = {
	&o_start_match,
	&o_setup_game,
	&o_spacer,
	&o_m_options,
	&o_mlobby_to_home,
};
SNMenu m_multiplayer_lobby_menu("Multiplayer Menu", 4, 2, 0, 1,multiplayer_lobby_menu_options, &function_refresh_multiplayer_lobby);
SNLabel l_multiplayer_lobby_title("Multiplayer", false, 4, 0, 0, 2, 1.5);
vector<SNElement*> multiplayer_lobby_elements = {
	&m_multiplayer_lobby_menu,
	&l_multiplayer_lobby_title,
};


// solo_lobby_page elements:
// void function_start_match() <- a duplicate use
void function_setup_solo_game();
void function_refresh_solo_lobby();

SNOption o_s_start_match("Start Match", 0, 0, 0, 0, &function_refresh_solo_lobby);
SNOption o_s_setup_game("Setup Game", 0, 0, 0, 0, &function_setup_solo_game);
SNOption o_s_options("Options", 0, 0, 0, 0, &function_refresh_solo_lobby);
SNOption o_slobby_to_home("Title Screen", 0, 0, 0, 0, &function_lobby_to_home);
vector<SNOption*> solo_lobby_menu_options = {
	&o_s_start_match,
	&o_s_setup_game,
	&o_spacer,
	&o_s_options,
	&o_slobby_to_home,
};
SNMenu m_solo_lobby_menu("Solo Menu", 4, 2, 0, 1, solo_lobby_menu_options, &function_refresh_solo_lobby);
SNLabel l_solo_lobby_title("Solo Play", false, 4, 0, 0, 2, 1.5);
vector<SNElement*> solo_lobby_elements = {
	&m_solo_lobby_menu,
	&l_solo_lobby_title,
};


// solo_setup_page elements:
void function_refresh();
void function_difficulty();
void function_player1();
void function_color1();
void function_player2();
void function_color2();
void function_starting_player();
void function_open_play();

Game_Controller my_game = Game_Controller("My Game", 8.75, 4, 14.5, 12.5, &function_refresh);

SNRadio_Button* rb_difficulty;
SNRadio_Button rb_easy("Easy", 10, 4, 3, 1, &function_difficulty, &rb_difficulty);
SNRadio_Button rb_medium("Medium", 14, 4, 4, 1, &function_difficulty, &rb_difficulty);
SNRadio_Button rb_hard("Hard", 19, 4, 3, 1, &function_difficulty, &rb_difficulty);

SNLabel l_connect_four("Connect Four", true, 9, 0, 14, 2, 1.5);
SNLabel l_player1("Player1:", false, 10.2, 6, 4, 1, 0.6);
SNLabel l_color1("Color:", false, 10.2, 7.5, 4, 1, 0.6);
SNLabel l_player2("Player2:", false, 10.2, 9.5, 4, 1, 0.6);
SNLabel l_color2("Color:", false, 10.2, 11, 4, 1, 0.6);
SNLabel l_starting_player("Starting P:", false, 10.2, 12.5, 4, 1, 0.6);

SNButton b_player1(my_game.player1_type(), 16, 6, 6, 1, &function_player1);
SNButton b_color1(my_game.player1_color(), 16, 7.5, 6, 1, &function_color1);
SNButton b_player2(my_game.player2_type(), 16, 9.5, 6, 1, &function_player2);
SNButton b_color2(my_game.player2_color(), 16, 11, 6, 1, &function_color2);
SNButton b_starting_player(my_game.starting_player_name(), 16, 12.5, 6, 1, &function_starting_player);
SNButton b_play("Play", 14.5, 14, 3, 1, &function_open_play);
vector<SNElement*> solo_setup_elements = {
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


// play_page elements:
void function_open_home();
void function_restart();

SNLabel l_game_log("GAME LOG", true, .9, 4, 6, 1, 0.8);
SNButton b_undo_move("Undo Move", 25, 4, 6, 1, &temp);
SNButton b_restart_game("Restart Game", 25, 6, 6, 1, &function_restart);
SNButton b_home_screen("Home Screen", 25, 8, 6, 1, &function_open_home);
vector<SNElement*> play_elements = {
	&l_connect_four,
	&l_game_log,
	&my_game,
	&b_undo_move,
	&b_restart_game,
	&b_home_screen
};


// *******************************************************************************************************
// Group2 : SNPage declarations(SNElements are in pages). Pages: title_page, solo_setup_page, play_page

// title_page declarations
void setup_title();
void draw_title();
SNPage title_page("Title Page", title_elements, &setup_title, &draw_title);


// multiplayer_lobby_page declarations
void setup_multiplayer_lobby();
void draw_multiplayer_lobby();
SNPage multiplayer_lobby_page("Multiplayer Lobby Page", multiplayer_lobby_elements, &setup_multiplayer_lobby, &draw_multiplayer_lobby);


// solo_lobby_page declarations
void setup_solo_lobby();
void draw_solo_lobby();
SNPage solo_lobby_page("Solo Lobby Page", solo_lobby_elements, &setup_solo_lobby, &draw_solo_lobby);

// setup_solo_page declarations
void setup_solo_setup();
void draw_solo_setup();
SNPage solo_setup_page("Solo Setup Page", solo_setup_elements, &setup_solo_setup, &draw_solo_setup);


// play_page declarations
void setup_play();
void draw_play();
SNPage play_page("Play Page", play_elements, &setup_play, &draw_play);


// *******************************************************************************************************
// Group3 : SNElements' function initializations. Pages: title_page, solo_setup_page, play_page

// title_page element functions.
void function_open_multiplayer() {
	my_app.activate_page(&multiplayer_lobby_page);
}
void function_open_solo_play() {
	my_app.activate_page(&solo_lobby_page);
}
void function_open_options() {

}
void function_refresh_title() {
	my_app.current_page->draw_page();
}

// multiplayer_lobby_page element functions.
void function_start_match() {

}
void function_setup_game() {

}
void function_lobby_to_home() {
	my_app.activate_page(&title_page);
}
void function_refresh_multiplayer_lobby() {
	my_app.current_page->draw_page();
}


// solo_lobby_page element functions.
void function_setup_solo_game() {
	my_app.activate_page(&solo_setup_page);
}
void function_refresh_solo_lobby() {
	my_app.current_page->draw_page();
}


// solo_setup_page element functions.
void function_refresh() {
	my_app.current_page->draw_page();
}
void function_difficulty() {
	my_app.refresh_page();
	SNRadio_Button temp_rb = **(rb_easy.current_rb);
	my_game.set_bot_difficulty(temp_rb.name);
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
void function_open_play() {
	my_app.activate_page(&play_page);
}


// play_page element functions.
void function_restart() {
	my_game.restart();
}
void function_open_home() {
	my_game.restart();
	my_app.activate_page(&solo_setup_page);
}


// *******************************************************************************************************
// Group4 : SNEPages' function initializations. Pages: title_page, solo_setup_page, play_page

// title_page SNPage functions
void setup_title(){

}
void draw_title() {
	background2();
}


// multiplayer_lobby_page SNPage functions
void setup_multiplayer_lobby() {

}
void draw_multiplayer_lobby() {
	background4();
}


// solo_lobby_page declarations
void setup_solo_lobby() {

}
void draw_solo_lobby() {
	background2();
}


// solo_setup_page SNPage functions
void setup_solo_setup() {

}
void draw_solo_setup() {
	background2();
	stroke_weight(2);
	stroke(255);
	fill(220);
	rect(9, 3, 14, 13, 25);
}


// play_page SNPage functions
void setup_play() {

}
void draw_play() {
	background4();
	stroke_weight(2);
	fill(220);
	stroke(255);
	rect(25, 10, 6, 6.5, 25);
	rect(1, 4, 6, 12.5, 25);
}