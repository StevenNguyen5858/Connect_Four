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
void function_refresh();

SNOption o_multiplayer("Multiplayer", 0, 0, 0, 0, &function_open_multiplayer);
SNOption o_solo_play("Solo Play", 0, 0, 0, 0, &function_open_solo_play);
SNOption o_options("Options", 0, 0, 0, 0, &function_open_options);
vector<SNOption*> title_menu_options = {
	&o_multiplayer,
	&o_solo_play,
	&o_options
};
SNMenu m_title("Connect IV Menu", 4, 10, 0, 1, title_menu_options, &function_refresh);
SNLabel l_connect4_title("Connect IV", false, 4, 5, 0, 2, 1.5);
vector<SNElement*> title_elements = {
	&l_connect4_title,
	&m_title,
};


// multiplayer_lobby_page elements:
void function_start_multiplayer_match();
void function_setup_game();
void function_lobby_to_home();
void function_mlobby_to_options();

SNOption o_start_match("Start Match", 0, 0, 0, 0, &function_start_multiplayer_match);
SNOption o_setup_game("Setup Game", 0, 0, 0, 0, &function_setup_game);
SNOption o_spacer(" ", 0, 0, 0, 0, &temp);
SNOption o_m_options("Options", 0, 0, 0, 0, &function_mlobby_to_options);
SNOption o_mlobby_to_home("Title Screen", 0, 0, 0, 0, &function_lobby_to_home);
vector<SNOption*> multiplayer_lobby_menu_options = {
	&o_start_match,
	&o_setup_game,
	&o_spacer,
	&o_m_options,
	&o_mlobby_to_home,
};
SNMenu m_multiplayer_lobby_menu("Multiplayer Menu", 4, 2.5, 0, 1, multiplayer_lobby_menu_options, &function_refresh);
lobby lobby_multiplayer("2 Players (2Max)", 16, 2.5, 12, 1, my_game.players);
SNLabel l_multiplayer_lobby_title("Multiplayer", false, 4, 0.5, 0, 2, 1.5);
vector<SNElement*> multiplayer_lobby_elements = {
	&m_multiplayer_lobby_menu,
	&lobby_multiplayer,
	&l_multiplayer_lobby_title,
};


// solo_lobby_page elements:
// void function_start_match() <- a duplicate use
void function_setup_solo_game();
void function_start_solo_match();
void function_back();
void function_slobby_to_options();

SNOption o_s_start_match("Start Match", 0, 0, 0, 0, &function_start_solo_match);
SNOption o_s_setup_game("Setup Game", 0, 0, 0, 0, &function_setup_solo_game);
SNOption o_s_options("Options", 0, 0, 0, 0, &function_slobby_to_options);
SNOption o_slobby_to_home("Title Screen", 0, 0, 0, 0, &function_lobby_to_home);
vector<SNOption*> solo_lobby_menu_options = {
	&o_s_start_match,
	&o_s_setup_game,
	&o_spacer,
	&o_s_options,
	&o_slobby_to_home,
};
SNMenu m_solo_lobby_menu("Solo Menu", 4, 2.5, 0, 1, solo_lobby_menu_options, &function_refresh);
lobby lobby_solo("2 Players (2Max)", 16, 2.5, 12, 1, my_game.players);
SNLabel l_solo_lobby_title("Solo Play", false, 4, 0.5, 0, 2, 1.5);
vector<SNElement*> solo_lobby_elements = {
	&m_solo_lobby_menu,
	&l_solo_lobby_title,
	&lobby_solo,
};


// options_page elements:
void function_toggle_dev_grid();
void function_settings_to_title();
void function_toggle_backgrounds();

string str_uses_dev_grid = (uses_dev_grid) ? "true" : "false";
bool uses_backgrounds = true;
string str_uses_backgrounds = (uses_backgrounds) ? "true" : "false";
SNOption o_dev_grid("Enable-Developer-Tools:", 0, 0, 0, 0, str_uses_dev_grid, &function_toggle_dev_grid);
SNOption o_use_backgrounds("Use-Backgrounds:", 0, 0, 0, 0, str_uses_backgrounds, &function_toggle_backgrounds);
SNOption o_back("Back", 0, 0, 0, 0, &function_back);
vector<SNOption*> settings_menu_options = {
	&o_dev_grid,
	&o_use_backgrounds,
	&o_spacer,
	&o_spacer,
	&o_back,
};
SNMenu m_settings_menu("settings menu", 4, 3, 0, 1, settings_menu_options, &function_refresh);
SNLabel l_app_settings_title("App Settings", true, 9, 0.5, 14, 1.5, 1.5);
vector<SNElement*> settings_elements = {
	&m_settings_menu,
	&l_app_settings_title,
};


// multiplayer_setup_page elements:
void function_o_color1();
void function_o_color2();
void function_o_starting();
void function_msetup_to_mlobby();

SNOption o_color1("Player1 Color:", 0, 0, 0, 0, my_game.player1_color(),&function_o_color1);
SNOption o_color2("Player2 Color:", 0, 0, 0, 0, my_game.player2_color(), &function_o_color2);
SNOption o_starting("Starting Player:", 0, 0, 0, 0, my_game.starting_player_name(), &function_o_starting);
SNOption o_apply("Apply", 0, 0, 0, 0, &function_msetup_to_mlobby);
vector<SNOption*> multiplayer_setup_menu_options = {
	&o_color1,
	&o_color2,
	&o_spacer,
	&o_starting,
	&o_spacer,
	&o_spacer,
	&o_apply,
};
SNMenu m_multiplayer_setup_menu("Multiplayer Menu", 4, 3, 0, 1, multiplayer_setup_menu_options, &function_refresh);
SNLabel l_multiplayer_setup_title("Setup Online Game", true, 9, 0.5, 14, 1.5, 1.5);
vector<SNElement*> multiplayer_setup_elements = {
	&m_multiplayer_setup_menu,
	&l_multiplayer_setup_title,
};


// solo_setup_page elements:
void function_difficulty();
void function_o_s_color1();
void function_o_s_color2();
void function_o_s_player1();
void function_o_s_player2();
void function_o_s_starting();
void function_open_play();
void function_ssetup_to_mlobby();

vector<string> difficulty_radios = { "Easy", "Medium", "Hard" };
SNRadio_Option ro_difficulty("Difficulty RO", 4, 2, 0, 1, &function_difficulty, difficulty_radios);
SNOption o_s_color1("Player1 Color:", 0, 0, 0, 0, my_game.player1_color(), &function_o_s_color1);
SNOption o_s_color2("Player2 Color:", 0, 0, 0, 0, my_game.player2_color(), &function_o_s_color2);
SNOption o_s_player1("Player1 Type:", 0, 0, 0, 0, my_game.player1_type(), &function_o_s_player1);
SNOption o_s_player2("Player2 Type:", 0, 0, 0, 0, my_game.player2_type(), &function_o_s_player2);
SNOption o_s_starting("Starting Player:", 0, 0, 0, 0, my_game.starting_player_name(), &function_o_s_starting);
SNOption o_s_apply("Apply", 0, 0, 0, 0, &function_ssetup_to_mlobby);
vector<SNOption*> solo_setup_menu_options = {
	&ro_difficulty,
	&o_spacer,
	&o_s_color1,
	&o_s_color2,
	&o_spacer,
	&o_s_player1,
	&o_s_player2,
	&o_spacer,
	&o_s_starting,
	&o_spacer,
	&o_spacer,
	&o_s_apply,
};
SNMenu m_solo_setup_menu("Solo Menu", 4, 3, 0, 1, solo_setup_menu_options, &function_refresh);
SNLabel l_solo_setup_title("Setup Solo Game", true, 9, 0.5, 14, 1.5, 1.5);
SNButton b_play("Play", 14.5, 14, 3, 1, &function_open_play);
vector<SNElement*> solo_setup_elements = {
	&l_solo_setup_title,
	&m_solo_setup_menu,
};


// play_page elements:
void function_open_home();
void function_undo();
void function_restart();


// 1 Game_Log and 1 Game_Controller Object initialized above setups. 
SNButton b_undo_move("Undo Move", 25, 4, 6, 1, &function_undo);
SNButton b_restart_game("Restart Game", 25, 6, 6, 1, &function_restart);
SNButton b_home_screen("Home Screen", 25, 8, 6, 1, &function_open_home);
SNLabel l_connect_four("Connect IV", true, 9, 0.5, 14, 1.5, 1.5);
lobby lobby_scoreboard("2 Players (2Max)", 25, 10, 6, 1, my_game.players);
vector<SNElement*> play_elements = {
	&l_connect_four,
	&gl_game_log,
	&my_game,
	&b_undo_move,
	&b_restart_game,
	&b_home_screen,
	&lobby_scoreboard,
};


// *******************************************************************************************************
// Group2 : SNPage declarations(SNElements are in pages). Pages: title_page, solo_setup_page, play_page

// title_page declarations
void setup_title();
void draw_title();
SNPage title_page("Title Page", title_elements, &setup_title, &draw_title);


// settings_page declarations
void setup_settings();
void draw_settings();
SNPage settings_page("Settings Page", settings_elements, &setup_settings, &draw_settings);


// multiplayer_lobby_page declarations
void setup_multiplayer_lobby();
void draw_multiplayer_lobby();
SNPage multiplayer_lobby_page("Multiplayer Lobby Page", multiplayer_lobby_elements, &setup_multiplayer_lobby, &draw_multiplayer_lobby);


// solo_lobby_page declarations
void setup_solo_lobby();
void draw_solo_lobby();
SNPage solo_lobby_page("Solo Lobby Page", solo_lobby_elements, &setup_solo_lobby, &draw_solo_lobby);


// multiplayer_setup_page declarations;
void setup_multiplayer_setup();
void draw_multiplayer_setup();
SNPage multiplayer_setup_page("Multiplayer Setup Page", multiplayer_setup_elements, &setup_multiplayer_setup, &draw_multiplayer_setup);


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
SNPage* previous_page = &title_page;
void function_back() {
	my_app.activate_page(previous_page);
}
void function_open_options() {
	previous_page = &title_page;
	my_app.activate_page(&settings_page);
}
void function_refresh() {
	my_app.current_page->draw_page();
}


// options_page element functions:
void function_toggle_dev_grid() {
	uses_dev_grid = (uses_dev_grid) ? false : true;
	uses_menu_outline = uses_dev_grid;
	str_uses_dev_grid = (uses_dev_grid) ? "true" : "false";
	o_dev_grid.option_data = str_uses_dev_grid;
}
void function_toggle_backgrounds() {
	uses_backgrounds = (uses_backgrounds) ? false : true;
	str_uses_backgrounds = (uses_backgrounds) ? "true" : "false";
	o_use_backgrounds.option_data = str_uses_backgrounds;
}
void function_settings_to_title() {
	my_app.activate_page(&title_page);
}


// multiplayer_lobby_page element functions.
void function_start_multiplayer_match() {
	my_game.isMultiplayer = true;
	my_game.start_game();
	my_app.activate_page(&play_page);
}
void function_setup_game() {
	my_app.activate_page(&multiplayer_setup_page);
}
void function_mlobby_to_options() {
	previous_page = &multiplayer_lobby_page;
	my_app.activate_page(&settings_page);
}
void function_lobby_to_home() {
	my_app.activate_page(&title_page);
}


// solo_lobby_page element functions.
void function_start_solo_match() {
	my_game.isMultiplayer = false;
	my_game.start_game();
	my_app.activate_page(&play_page);
}
void function_setup_solo_game() {
	my_app.activate_page(&solo_setup_page);
}
void function_slobby_to_options() {
	previous_page = &solo_lobby_page;
	my_app.activate_page(&settings_page);
}



// multiplayer_setup_page element functions.
void function_o_color1() {
	my_game.player1_toggle_color();
	o_color1.option_data = my_game.player1_color();
	o_color2.option_data = my_game.player2_color();	
}
void function_o_color2() {
	my_game.player2_toggle_color();
	o_color2.option_data = my_game.player2_color();
	o_color1.option_data = my_game.player1_color();
}
void function_o_starting() {
	my_game.toggle_starting_player();
	o_starting.option_data = my_game.starting_player_name();	
}
void function_msetup_to_mlobby() {
	my_app.activate_page(&multiplayer_lobby_page);
}


// solo_setup_page element functions.
void function_difficulty() {
	my_app.refresh_page();
	my_game.set_bot_difficulty(ro_difficulty.radio_switch());
}
void function_o_s_player1() {
	my_game.player1_toggle_type();
	o_s_player1.option_data= my_game.player1_type();
}
void function_o_s_player2() {
	my_game.player2_toggle_type();
	o_s_player2.option_data = my_game.player2_type();
}
void function_o_s_color1() {
	my_game.player1_toggle_color();
	o_s_color1.option_data = my_game.player1_color();
	o_s_color2.option_data = my_game.player2_color();
}
void function_o_s_color2() {
	my_game.player2_toggle_color();
	o_s_color2.option_data = my_game.player2_color();
	o_s_color1.option_data = my_game.player1_color();
}
void function_o_s_starting() {
	my_game.toggle_starting_player();
	o_s_starting.option_data = my_game.starting_player_name();
}
void function_ssetup_to_mlobby() {
	my_app.activate_page(&solo_lobby_page);
}
void function_open_play() {
	my_game.start_game();
	my_app.activate_page(&play_page);
}


// play_page element functions.
void function_undo() {
	my_game.undo();
}
void function_restart() {
	my_game.restart();
}
void function_open_home() {
	my_game.game_started = false;
	my_game.restart();
	if (my_game.isMultiplayer) {
		my_app.activate_page(&multiplayer_lobby_page);
	}
	else {
		my_app.activate_page(&solo_lobby_page);
	}
}


// *******************************************************************************************************
// Group4 : SNEPages' function initializations. Pages: title_page, solo_setup_page, play_page

// Menu draw helper functions
void menu_nav_explainers() {
	// Navigation explainers
	fill(0);
	stroke(255);
	stroke_weight(1);
	// KeyBoxes: Enter, Esc
	rect(4.2, 16.2, 1.8, 0.6, 100);
	rect(8.8, 16.2, 1.2, 0.6, 100);

	fill(255);
	// Enter
	all_centered_text("Enter", 4.2, 16.2, 1.8, 0.6, 0.4);
	y_centered_text("Select", 6.2, 16.1, 0.8, 0.5);
	// Esc
	all_centered_text("Esc", 8.8, 16.2, 1.2, 0.6, 0.4);
	y_centered_text("Exit", 10.2, 16.1, 0.8, 0.5);
}


// title_page SNPage functions
void helper_line_accent() {
	fill(255);
	stroke_weight(2);
	line(0, 0.75, 4, 0.75);
	line(4, 0.75, 4.5, 0.25);
	line(4.5, 0.25, 27.5, 0.25);
	line(27.5, 0.25, 28, 0.75);
	line(28, 0.75, 32, 0.75);
	line(0, gridH - 0.75, 4, gridH - 0.75);
	line(4, gridH - 0.75, 4.5, gridH - 0.25);
	line(4.5, gridH - 0.25, 27.5, gridH - 0.25);
	line(27.5, gridH - 0.25, 28, gridH - 0.75);
	line(28, gridH - 0.75, 32, gridH - 0.75);
}
void setup_title(){

}
void draw_title() {
	if (uses_backgrounds) {
		background2();
	}
	menu_nav_explainers();
}


// settings_page SNPage functions
void setup_settings() {

}
void draw_settings() {
	if (uses_backgrounds) {
		background2();
	}
	// Accent lines
	helper_line_accent();
	menu_nav_explainers();
}


// multiplayer_lobby_page SNPage functions
void setup_multiplayer_lobby() {

}
void draw_multiplayer_lobby() {
	if (uses_backgrounds) {
		background4();
	}
	menu_nav_explainers();
}


// solo_lobby_page declarations
void setup_solo_lobby() {

}
void draw_solo_lobby() {
	if (uses_backgrounds) {
		background2();
	}
	menu_nav_explainers();
}


// multiplayer_setup_page SNPage functions
void setup_multiplayer_setup() {

}
void draw_multiplayer_setup() {
	if (uses_backgrounds) {
		background4();
	}
	menu_nav_explainers();
	// Accent lines
	helper_line_accent();
}


// solo_setup_page SNPage functions
void setup_solo_setup() {

}
void draw_solo_setup() {
	if (uses_backgrounds) {
		background2();
	}
	menu_nav_explainers();
	// Accent lines
	helper_line_accent();
}


// play_page SNPage functions
void setup_play() {

}
void draw_play() {
	if (uses_backgrounds) {
		background4();
	}
	stroke_weight(2);
	//fill(220);
	fill(sf::Color::Magenta);
	stroke(255);
	//rect(25, 10, 6, 6.5, 25);
}