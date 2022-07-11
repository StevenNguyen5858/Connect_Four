#include <SFML/Graphics.hpp>
#include "SNElement.h"
#include "ConnectFour.h"
// Testing push from Steven.


/*	Explanation for using this SNProcessing and SNElements tool:
*	-This file's purpose is to emmulate the Processing 3.5.4 IDE. Until further
*	implementation, processing.org can be used as a close documentation reference.
*	Note that the main.cpp is setup similar to that IDE, main.cpp should
*	only be modified by writing code in the following functions:
*	- void setup() Runs once at the initial instance before the application driver begins.
*	- void draw() Runs continously as apart of the application driver.
*	- The next functions are event handlers. They run prior to each draw() frame.
*	- void mouse_pressed() Runs on the event the mouse is pressed.
*	- void mouse_released() Runs on the event the mouse is released.
*	Avoid modification of main(), unless planning to use unimplemented SFML features. */

/*	SNElements description:
*	A Foundational project for future C++ application projects (GUI library extension).
*	This project relies on the SFML low level Graphics library. SFML is a library which
*	handles primitive objects such as geometric shapes, image sprites and application windows.
*	SNElements uses SFML to handle higher level objects such as pages and the elements
*	that may be within them: buttons, radio buttons, sliders, lables, etc.
*
*	Drawing onto the application is done through SNElements and/or SNProcessing. SNProcessing
*	provides the draw() for continously updating display. 
*	SNElement offers a staticaly drawn page based display. To get started:
*	- Create your own SNPage object with its various elements.
*	- Add this page object the default SNApp "my_app.add_page(*YOUR_PAGE)" 
*	- To change the starting page from the SNElements navigator, "my_app.current_page = YOUR_PAGE".
* 
*	For those wishing to use unimplemented SFML features keep in mind, SNProcessing renders to
*	a single application/RenderWindow. Multi-window applications will be supported in a
*	different version. */


// Runs once at start of program.
void setup() {
	my_app.add_page(&title_page);
	my_app.add_page(&multiplayer_lobby_page);
	my_app.add_page(&solo_lobby_page);
	my_app.add_page(&solo_setup_page);
	my_app.add_page(&play_page);
	my_app.current_page = &title_page;
	rb_difficulty = &rb_easy;
	rb_easy.is_selected = true;
}

// Loops for application drawing.
void draw() {

}

// Runs when mouse is pressed.
void mouse_pressed(double mouse_x, double mouse_y) {
	cout << "Mouse X: " << int(mouse_x / sw) << " Mouse Y: " << int(mouse_y / sh) << endl;
	my_app.current_page->check_buttons(mouse_x, mouse_y);
}

// Runs when mouse is released.
void mouse_released(double mouse_x, double mouse_y) {

}

void keypressed(string key) {
	my_app.current_page->handle_keys(key);
}


// Main() driver should be left in background. 
// Use the above space and functions to create your program.
int main() {
	my_app.add_page(&SNEM);
	cout << "W: " << sf::VideoMode::getDesktopMode().width * .75 << " H: " << sf::VideoMode::getDesktopMode().height * .75 << endl;
	setup_window(sf::VideoMode::getDesktopMode().width*.75, sf::VideoMode::getDesktopMode().height*.75, "SNElement Application");
	bool drawOnce = true;
	SNEM_current_rb = &rb_dev;
	rb_dev.is_selected = true;

	setup();

	// Draw Loop:
	while (main_window.isOpen()) {
		// First page is draw here.
		if (drawOnce) {
			my_app.refresh_page();
			drawOnce = false;
		}

		sf::Event event;
		// Event Handler:
		while (main_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				main_window.close();
			}
			if (event.type == sf::Event::Resized) {
				refresh_grid();
				main_window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
				drawOnce = true;
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				double mouse_x = sf::Mouse::getPosition(main_window).x;
				double mouse_y = sf::Mouse::getPosition(main_window).y;
				mouse_pressed(mouse_x, mouse_y);
				
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				double mouse_x = sf::Mouse::getPosition(main_window).x;
				double mouse_y = sf::Mouse::getPosition(main_window).y;
				mouse_released(mouse_x, mouse_y);
			}
			if (event.type == sf::Event::KeyPressed) {
				string key = " ";
				if (event.key.code == sf::Keyboard::Escape) {
					main_window.close();
				}
				if (event.key.code == 22 || event.key.code == 73 ) {
					key = "w";
				}
				if (event.key.code == 0 || event.key.code == 71) {
					key = "a";
				}
				if (event.key.code == 18 || event.key.code == 74) {
					key = "s";
				}
				if (event.key.code == 3 || event.key.code == 72) {
					key = "d";
				}
				if (event.key.code == 58) {
					key = "ENTER";
				}
				keypressed(key);
			}
		}
		draw();
	}
}
