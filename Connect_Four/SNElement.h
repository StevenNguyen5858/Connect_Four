#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>


using namespace std;


/*	Group0: SNProcessing and SNElement tool explanation.
*
*	Group1: SNProcessing global variables and functions.
*
*	Group2: SNElement classes: SNElement, SNButton, SNLabel, SNContainer, SNCache,
*			SNPage and SNApp class.
*
*	Group3: SNElement navigation page creation. */


// ********************************************************************************************
// Group0: SNProcessing and SNElement tool explanation.

/*	Explanation for using this SNProcessing and SNElements tool:
*	-This file's purpose is to emmulate the Processing 3.5.4 IDE. Until further 
*	implementation, processing.org can be used as a close documentation reference.
*	Note that the main.cpp is setup similar to that IDE, main.cpp should 
*	only be modified by writing code in the following functions:
*	-void setup() Runs once at the initial instance before the application driver begins.
*	-void draw() Runs continously as apart of the application driver.
*	-The next functions are event handlers. They run prior to each draw() frame.
*	-void mouse_pressed() Runs on the event the mouse is pressed. 
*	-void mouse_released() Runs on the event the mouse is released.
*	Avoid modification of main(), unless planning to use unimplemented SFML features. */

/*	SNElements description: 
*	A Foundational project for future C++ application projects (GUI library extension). 
*	This project relies on the SFML low level Graphics library. SFML is a library which 
*	handles primitive objects such as geometric shapes, image sprites and application windows.
*	SNElements uses SFML to handle higher level objects such as pages and the elements
*	that may be within them: buttons, radio buttons, sliders, lables, etc.
*	
*	For those wishing to use unimplemented SFML features keep in mind, SNProcessing renders to 
*	a single application/RenderWindow. Multi-window applications will be supported in a 
*	different version. */


// ********************************************************************************************
// Group1: SNProcessing global variablesand functions.

// Single instance of Prcessing begins here. It includes global style values: 
sf::RenderWindow main_window;
sf::Color current_fill = sf::Color(255, 255, 255, 255);
sf::Color current_stroke = sf::Color(0, 0, 0, 255);
int current_stroke_weight = 2;
sf::Font font;

/* gridW and gridH represent the number of grid units will fit in the current screen.
*  Using the number of grid units, we determine the pixels per unit for the x and y axies.
*  We can use this value in our projections to keep elements at a scale.
*/
int gridW = 32;
int gridH = 18;
int sw;
int sh;
int displayW = sf::VideoMode::getDesktopMode().width;
int displayH = sf::VideoMode::getDesktopMode().height;

// Image icons:
sf::Image icon_image;
sf::Image icon_sound;
sf::Image icon_text;
sf::Image icon_video;

sf::Image radio_empty;
sf::Image radio_full;

// Sets up the basic screen dimentions, then on the front end use is setting grid units sw and sh.
void refresh_grid() {
	int screen_width = main_window.getSize().x;
	int screen_height = main_window.getSize().y;
	sw = screen_width / gridW;
	sh = screen_height / gridH;
}
void setup_window(int screen_width, int screen_height, string title) {
	font.loadFromFile("SNElement Resources/cour.ttf");
	icon_image.loadFromFile("SNElement Resources/ImageIcon.png");
	icon_sound.loadFromFile("SNElement Resources/SoundIcon.png");
	icon_text.loadFromFile("SNElement Resources/TextIcon.png");
	icon_video.loadFromFile("SNElement Resources/VideoIcon.png");

	radio_empty.loadFromFile("SNElement Resources/RadioButtonEmpty.png");
	radio_full.loadFromFile("SNElement Resources/RadioButtonFull.png");

	main_window.create(sf::VideoMode(screen_width, screen_height), title);
	refresh_grid();
}

// Processing modifiers for global style values:
void fill(sf::Color color) {
	current_fill = color;
}
void fill(int fill) {
	current_fill = sf::Color(fill, fill, fill, 255);
}
void no_fill() {
	current_fill = sf::Color::Transparent;
}
void stroke(sf::Color color) {
	current_stroke = color;
}
void stroke(int stroke) {
	current_stroke = sf::Color(stroke, stroke, stroke, 255);
}
void stroke_weight(int stroke_weight) {
	current_stroke_weight = stroke_weight;
}

// Changes the title of the application.
void set_title(string str) {
	setup_window(displayW, displayH, str);
}
// Draws rectangle to buffer.
void rect(double x, double y, double w, double h) { 
	sf::RectangleShape r(sf::Vector2f(w * sw, h * sh));
	r.setPosition(x * sw, y * sh);
	r.setFillColor(current_fill);
	r.setOutlineThickness(current_stroke_weight);
	r.setOutlineColor(current_stroke);
	main_window.draw(r);
}
// Draws rectangle with an alpha fill to buffer.
void rect(double x, double y, double w, double h, int alpha) {
	sf::RectangleShape r(sf::Vector2f(w * sw, h * sh));
	r.setPosition(x * sw, y * sh);
	r.setFillColor(sf::Color(current_fill.r, current_fill.g, current_fill.b, alpha));
	r.setOutlineThickness(current_stroke_weight);
	r.setOutlineColor(current_stroke);
	main_window.draw(r);
}
// Draws circle to buffer.
void circle(double x, double y, double d) {
	sf::CircleShape c(d / 2 * sw);
	c.setPosition(x * sw, y * sh);
	c.setFillColor(current_fill);
	c.setOutlineThickness(current_stroke_weight);
	c.setOutlineColor(current_stroke);
	main_window.draw(c);
}
// Draws circle with an alpha fill to buffer.
void circle(double x, double y, double d, int alpha) {
	sf::CircleShape c(d / 2 * sw);
	c.setPosition(x * sw, y * sh);
	c.setFillColor(sf::Color(current_fill.r, current_fill.g, current_fill.b, alpha));
	c.setOutlineThickness(current_stroke_weight);
	c.setOutlineColor(current_stroke);
	main_window.draw(c);
}
// Draws text to buffer.
void text(string str, double x, double y, double h) { 
	sf::Text text;

	text.setFont(font);
	text.setStyle(sf::Text::Bold);
	text.setString(str);
	text.setCharacterSize(h * sh);
	text.setPosition(sf::Vector2f(x * sw, y * sh - (h * sh * .1)));
	text.setFillColor(current_fill);
	main_window.draw(text);
}
// Draws centered text within a given x, y, w and h to buffer.
void centered_text(string str, double x, double y, double w, double h) { 
	sf::Text text;

	text.setFont(font);
	text.setStyle(sf::Text::Bold);
	text.setString(str);
	text.setCharacterSize(h * sh);
	int text_w = text.getGlobalBounds().width;
	int centered_x = (x * sw) + ((w * sw) - text_w) / 2;
	text.setPosition(sf::Vector2f(centered_x, y*sh));
	text.setFillColor(current_fill);
	main_window.draw(text);
}
// Returns grid based text width.
double text_width(string str, double h) {
	sf::Text text;

	text.setFont(font);
	text.setStyle(sf::Text::Bold);
	text.setString(str);
	text.setCharacterSize(h * sh);
	double text_w = text.getGlobalBounds().width / sw;
	return text_w;
}
// Fills buffer with sf::Color.
void background(sf::Color color) {
	main_window.clear(color);
}
// Fills buffer with rgb(255-0).
void background(int color) {
	main_window.clear(sf::Color(color, color, color, 255));
}
// Draws an sf::image object to buffer at default image size.
void image(sf::Image* img, int x, int y) { 
	sf::Texture temp;
	sf::Sprite sprit;
	sprit.setPosition(sf::Vector2f(x * sw, y * sh));
	temp.loadFromImage(*img);
	sprit.setTexture(temp);
	main_window.draw(sprit);
}
// Draws an sf::image object to buffer with given width and height.
// Images scale best by factors of two.
void image(sf::Image* img, int x, int y, int new_width, int new_height) { 
	double scale_w = (float)(new_width * sw) / img->getSize().x;
	double scale_h = (float)(new_height * sh) / img->getSize().y;
	sf::Texture temp;
	sf::Sprite sprit;
	sprit.setPosition(sf::Vector2f(x * sw, y * sh));
	temp.loadFromImage(*img);
	sprit.setTexture(temp);
	sprit.setScale(sf::Vector2f(scale_w, scale_h));
	main_window.draw(sprit);
}

// Displays the grid which processing functions are based on.
void dev_grid() {
	stroke(120);
	stroke_weight(1);
	fill(32);
	for (int x = 0; x < gridW + 1; x++) { // Note gridW is main display, the +1 is for partially displaying border
		for (int y = 0; y < gridH + 1; y++) {
			rect(x, y, 1, 1);
		}
	}
	stroke_weight(2);
}
// Plain background.
void gridless() {
	main_window.clear(sf::Color(32, 32, 32));
}


// ********************************************************************************************
// Group2: SNElement classes : SNElement, SNButton, SNLabel, SNContainer, SNCache, SNPageand SNApp class.

class SNElement {
	// Access specifier:
public:
	string type = "SNElement";
	string name;
	double x, y, w, h;
	void (*function)();

	// Default Constructor:
	SNElement() {
	}
	// Parameterized Constructor:
	SNElement(string name, double x, double y, double w, double h) {
		this->name = name;
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}

	// Methods:
	virtual void draw_element() {
		cout << " " << name << " (virtual draw func)." << x << "." << y << endl;
		fill(220);
		stroke(255);
		stroke_weight(2);
		rect(x, y, w, h, 25);
	}
};


class SNLabel : public SNElement {
	// Access specifier:
public:
	string str;
	int height;
	bool isCentered;

	// Default Constructor:
	SNLabel() {
	}
	// Parameterized
	SNLabel(string str, bool isCentered, double x, double y, double w, double h)
		: SNElement(name, x, y, w, h) {
		this->str = str;
		this->isCentered = isCentered;
		this->height = h;
		this->type = "SNLabel";
	}

	void draw_element() { // Overloading virtual parent func.
		cout << " " << name << " (overloaded draw func)." << x << endl;
		fill(255);
		stroke(255);
		if (isCentered) {
			centered_text(str, x, y, w, h);
		}
		else {
			text(str, x, y, h);
		}
	}
};


class SNButton : public SNElement {
	// Access specifier:
public:
	bool is_selected = false;
	void (*function)();

	// Default Constructor:
	SNButton() {
		this->type = "SNButton";
	}
	// Parameterized Constructor:
	SNButton(string name, double x, double y, double w, double h, void (*function)())
		: SNElement(name, x, y, w, h) {
		this->type = "SNButton";
		this->function = function;
	}

	// Methods:
	void draw_element() {
		cout << " " << name << " (overloaded draw func)." << x << "." << y << endl;
		fill(220);
		if (is_selected) {
			stroke(sf::Color(20, 140, 150));
		}
		else {
			stroke(255);
		}
		stroke_weight(2);
		rect(x, y, w, h, 25);
		fill(255);
		text(name, x+0.2, y+(h*0.15), h*.6);
	}
};


class SNButton_in_set : public SNElement { // Useful for when button position in a set is relevant.
	// Access specifier:
public:
	bool is_selected = false;
	int button_position;
	void (*function)(int);

	// Default Constructor:
	SNButton_in_set() {
		this->type = "SNButton_in_set";
	}
	// Parameterized Constructor:
	SNButton_in_set(string name, double x, double y, double w, double h, void (*function)(int), int button_position)
		: SNElement(name, x, y, w, h) {
		this->type = "SNButton_in_set";
		this->function = function;
		this->button_position = button_position;
	}

	void draw_element() {
		cout << " " << name << " (overloaded draw func)." << x << "." << y << endl;
		fill(220);
		if (is_selected) {
			stroke(sf::Color(20, 140, 150));
		}
		else {
			stroke(255);
		}
		stroke_weight(2);
		rect(x, y, w, h, 25);
		fill(255);
		text(name, x + 0.2, y + (h * 0.15), h * .6);
	}
};


class SNRadio_Button : public SNButton {
	// Access specififer:
public:
	bool is_selected = false;
	SNRadio_Button **current_rb;

	// Deafult Constructor:
	SNRadio_Button() {
	}
	// Parametereized Constructor:
	SNRadio_Button(string name, double x, double y, double w, double h, void (*function)(), SNRadio_Button **current_rb)
		: SNButton(name, x, y, w, h, function) {
		this->type = "SNRadio_Button";
		this->current_rb = current_rb;
	}

	// Methods:
	void draw_element() {
		cout << " " << name << " (overloaded draw func)." << x << "." << y << endl;
		if (is_selected) {
			image(&radio_full, x, y, 1, 1);
		}
		else {
			image(&radio_empty, x, y, 1, 1);
		}
		fill(255);
		stroke_weight(2);
		text(name, x + 1.2, y + .08, 0.6);
	}
	void radio_switch() {
		SNRadio_Button* t = *current_rb;
		if (t != NULL) {
			t->is_selected = false;
			this->is_selected = true;
			*current_rb = this;
		}
		else {
			cout << "No initial radio button set" << endl;
		}
		function();
	}
};


class SNContainer : public SNElement {
	// Access specifier:
public:
	vector<SNElement*> elements;
	string title;

	// Default Constructor:
	SNContainer() {
	}
	// Parameterized Constructor:
	SNContainer(string name, double x, double y, double w, double h, vector<SNElement*> elements, string title)
		: SNElement(name, x, y, w, h) {
		this->elements = elements;
		this->title = title;
	}

	void draw_element() { // Overloading virtual parent func.
		cout << " " << name << " (container draw func)." << x << "." << y << endl;
		no_fill();
		stroke(220);
		stroke_weight(2);
		double title_w = ceil(text_width(title, 0.7)); // title
		rect(x + title_w, y + .5, w - title_w, 0); // title line -----------------------------
		fill(255);
		centered_text(title, x, y, title_w, 0.6);
		for (int i = 0; i < elements.size(); i++) {
			elements[i]->draw_element();
		}
	}
};


class cache { // For storing loop created objects.
// Access specifier:
public:
	vector<SNButton> buttons = {};
	vector<SNButton_in_set> buttons_in_set = {};
	vector<SNElement> elements = {};
	vector<SNContainer> containers = {};

	// Default constructor:
	cache() {
	}

	// Methods:
	void clear_all(vector<SNElement*>* page_elements) {
		page_elements->clear();
		buttons.clear();
		buttons_in_set.clear();
		elements.clear();
		containers.clear();
	}
};

