#pragma once
#include "SNElement.h"
#include "Game_Controller.h"


bool uses_dev_grid = false;

class SNPage {
	// Access specifier:
public:
	string name;
	SNMenu *page_menu;
	bool has_page_menu = false;
	vector<SNElement*> elements;
	vector<SNElement*> post_elements;
	void (*draw_func)();
	void (*page_setup)();

	// Default constructor:
	SNPage() {
	}
	// Parameterized Constructor:
	SNPage(string name, vector<SNElement*> elements, void (*page_setup)(), void (*draw_func)()) {
		this->name = name;
		this->elements = elements;
		this->page_setup = page_setup;
		this->draw_func = draw_func;
		for (int i = 0; i < elements.size(); i++) {
			if (elements[i]->type == "SNMenu") {
				SNMenu* menu_ptr = dynamic_cast<SNMenu*>(elements[i]);
				page_menu = menu_ptr;
				has_page_menu = true;
				break;
			}
		}
	}

	void draw_page() {
		cout << "Drawing " << name << endl;
		// Clear Window display
		main_window.clear(sf::Color(32,32,32));
		// Draw specialized function
		draw_func();
		// Draw plain background
		if (uses_dev_grid) {
			dev_grid();
		}
		// Draw page elements
		for (int i = 0; i < elements.size(); i++) {
			elements[i]->draw_element();
		}
		for (int i = 0; i < post_elements.size(); i++) {
			post_elements[i]->draw_element();
		}
		cout << endl;
		// Push buffer to Window display
		main_window.display();
	}

	void check_buttons(double mouse_x, double mouse_y) {
		double grid_x = mouse_x / sw;
		double grid_y = mouse_y / sh;
		for (int i = 0; i < elements.size(); i++) {
			SNElement* e = elements[i];
			if (e->isClickable) {
				if (e->x < grid_x && grid_x < e->x + e->w && e->y < grid_y && grid_y < e->y + e->h) {
					SNClickable* SNClickable_ptr = dynamic_cast<SNClickable*>(e);
					SNClickable_ptr->click_event("left", mouse_x, mouse_y);
					cout << e->name << " has been pressed." << endl;
				}
			}
			if (e->type == "SNButton_in_set") {
				if (e->x < grid_x && grid_x < e->x + e->w && e->y < grid_y && grid_y < e->y + e->h) {
					SNButton_in_set* button_ptr = dynamic_cast<SNButton_in_set*>(e);
					button_ptr->function(button_ptr->button_position);
				}
			}
		}
		for (int i = 0; i < post_elements.size(); i++) {
			SNElement* e = post_elements[i];
			if (e->isClickable) {
				if (e->x < grid_x && grid_x < e->x + e->w && e->y < grid_y && grid_y < e->y + e->h) {
					SNClickable* SNClickable_ptr = dynamic_cast<SNClickable*>(e);
					SNClickable_ptr->click_event("left", mouse_x, mouse_y);
					cout << e->name << " has been pressed." << endl;
				}
			}
			if (e->type == "SNButton_in_set") {
				if (e->x < grid_x && grid_x < e->x + e->w && e->y < grid_y && grid_y < e->y + e->h) {
					SNButton_in_set* button_ptr = dynamic_cast<SNButton_in_set*>(e);
					button_ptr->function(button_ptr->button_position);
				}
			}
		}
	}
	void mouse_move(double mouse_x, double mouse_y) {
		//"Hover_Pos"  "Mouse_Move"
		double grid_x = mouse_x / sw;
		double grid_y = mouse_y / sh;
		for (int i = 0; i < elements.size(); i++) {
			SNElement* e = elements[i];
			if (e->isHoverable) {
				if (e->x < grid_x && grid_x < e->x + e->w && e->y < grid_y && grid_y < e->y + e->h) {
					SNHoverable* SNHoverable_ptr = dynamic_cast<SNHoverable*>(e);
					SNHoverable_ptr->hover_event(mouse_x, mouse_y);
					cout << e->name << " is being hovered." << endl;
				}
			}
		}
	}
	void handle_keys(string key) {
		for (int i = 0; i < elements.size(); i++) {
			SNElement* e = elements[i];
			if (e->isTypeable) {
				SNTypeable* SNTypeable_ptr = dynamic_cast<SNTypeable*>(e);
				SNTypeable_ptr->keypress_event(key);
				cout << e->name << " is handling a keypress." << endl;
			}
		}
	}
};


class SNApp {
	// Access specifier:
public:
	vector<SNPage*> pages;
	SNPage* current_page;

	// Default constructor:
	SNApp() {
	}

	// Methods:
	void add_page(SNPage* new_page) {
		if (pages.size() == 0) {
			current_page = new_page;
		}
		pages.push_back(new_page);
	}
	void activate_page(SNPage* p) {
		p->page_setup();
		p->draw_page();
		current_page = p;
	}
	void refresh_page() {
		current_page->page_setup();
		current_page->draw_page();
	}
};


// ********************************************************************************************
// Group3: SNElement navigation page creation.
SNApp my_app;
/*	SUB Groups
*	GroupA: SNElement declarations
*	GroupB: SNPage declarations(SNElements are in pages)
*
*	GroupC: SNElements' function initializations
*	GroupD: SNEPages' function initializations */


// GroupA: SNElement declarations
void function_temp() {};
void function_open_page(int pos);
void function_rb_dev();
void function_rb_plain();

SNLabel l_SNEM_title("SNElements Main:", false, 1, 0, text_width("SNElements Main", 2), 2, 1.5);
SNLabel l_sidebar_title("View Options:", true, 25, 0, 7, 1, 0.6);
SNRadio_Button* SNEM_current_rb;
SNRadio_Button rb_dev("Developer Grid", 25, 2, 7, 1, &function_rb_dev, &SNEM_current_rb);
SNRadio_Button rb_plain("No Grid", 25, 3, 7, 1, &function_rb_plain, &SNEM_current_rb);

vector<SNElement*> SNEM_elements = {
	&l_SNEM_title,
	&l_sidebar_title,
	&rb_dev,
	&rb_plain
};


// GroupB: SNPage declarations(SNElements are in pages)
void setup_SNElement_main();
void draw_SNElement_main();

cache SNEM_page_cache = cache();
SNPage SNEM("SNElements Main", SNEM_elements, &setup_SNElement_main, &draw_SNElement_main);


// GroupC: SNElements' function initializations
void function_open_page(int pos) {
	if (my_app.pages.size() > pos) {
		my_app.activate_page(my_app.pages[pos]);
	}
}
void function_rb_dev() {
	uses_dev_grid = true;
	my_app.refresh_page();
}
void function_rb_plain() {
	uses_dev_grid = false;
	my_app.refresh_page();
}


// GroupD: SNEPages' function initializations */
void setup_SNElement_main() { // Creates new buttons to navigate pages added to my_app
	SNEM_page_cache.clear_all(&SNEM.post_elements);
	SNButton_in_set temp_button;
	for (int i = 0; i < my_app.pages.size(); i++) {
		temp_button.~SNButton_in_set();
		new(&temp_button) SNButton_in_set(my_app.pages[i]->name, 1, 2 + i * 2, text_width(my_app.pages[i]->name, 1 * 0.6) + 1, 1, &function_open_page, i);
		SNEM_page_cache.buttons_in_set.push_back(temp_button);
	}
	for (int i = 0; i < SNEM_page_cache.buttons_in_set.size(); i++) {
		SNEM.post_elements.push_back(&SNEM_page_cache.buttons_in_set[i]);
	}
}
void draw_SNElement_main() {
	fill(220);
	stroke(220);
	stroke_weight(2);
	int sidebar_width = 7;
	rect(gridW - sidebar_width, 0, sidebar_width + 1, gridH + 1, 25);
}