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

sf::Image bg2;
sf::Image bg4;

sf::Image blue_icon;
sf::Image green_icon;
sf::Image red_icon;
sf::Image yellow_icon;
vector<sf::Image*> player_icons = { &green_icon, &red_icon, &yellow_icon, &blue_icon };

// Sets up the basic screen dimentions, then on the front end use is setting grid units sw and sh.
void refresh_grid() {
	int screen_width = main_window.getSize().x;
	int screen_height = main_window.getSize().y;
	sw = screen_width / gridW;
	sh = screen_height / gridH;
}
void setup_window(int screen_width, int screen_height, string title) {
	bool couldnt_load = false;
	if (!bg2.loadFromFile("SNElement Resources/BG2.png")) {
		sf::err() << "Couldn't load BG2\n";
		bool couldnt_load = true;
	}
	if (!bg4.loadFromFile("SNElement Resources/BG4.jpg")) {
		sf::err() << "Couldn't load BG4\n";
		bool couldnt_load = true;
	}
	if (!font.loadFromFile("SNElement Resources/cour.ttf")) {
		sf::err() << "Couldn't load cour font\n";
		bool couldnt_load = true;
	}
	if (!icon_image.loadFromFile("SNElement Resources/ImageIcon.png")) {
		sf::err() << "Couldn't load ImageIcon\n";
		bool couldnt_load = true;
	}
	if (!icon_sound.loadFromFile("SNElement Resources/SoundIcon.png")) {
		sf::err() << "Couldn't load SoundIcon\n";
		bool couldnt_load = true;
	}
	if (!icon_text.loadFromFile("SNElement Resources/TextIcon.png")) {
		sf::err() << "Couldn't load TextIcon\n";
		bool couldnt_load = true;
	}
	if (!icon_video.loadFromFile("SNElement Resources/VideoIcon.png")) {
		sf::err() << "Couldn't load VideoIcon\n";
		bool couldnt_load = true;
	}

	if (!blue_icon.loadFromFile("SNElement Resources/Blue Frames/tile000.png")) {
		sf::err() << "Couldn't load blue icon\n";
		bool couldnt_load = true;
	}
	if (!green_icon.loadFromFile("SNElement Resources/Green Frames/tile000.png")) {
		sf::err() << "Couldn't load blue icon\n";
		bool couldnt_load = true;
	}
	if (!red_icon.loadFromFile("SNElement Resources/Red Frames/tile000.png")) {
		sf::err() << "Couldn't load blue icon\n";
		bool couldnt_load = true;
	}
	if (!yellow_icon.loadFromFile("SNElement Resources/Yellow Frames/tile000.png")) {
		sf::err() << "Couldn't load blue icon\n";
		bool couldnt_load = true;
	}

	if (!radio_empty.loadFromFile("SNElement Resources/RadioButtonEmpty.png")) {
		sf::err() << "Couldn't load RadioEmptyIcon\n";
		bool couldnt_load = true;
	}
	if (!radio_full.loadFromFile("SNElement Resources/RadioButtonFull.png")) {
		sf::err() << "Couldn't load RadioFullIcon\n";
		bool couldnt_load = true;
	}
	
	if (couldnt_load) {
		sf::err() << "Application resources were not all loaded. Try repairing or reinstalling your application.\n";
	}
	
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
// Draws line using vertex shape to buffer.
class sfLine : public sf::Drawable {
public:
	sfLine(const sf::Vector2f& point1, const sf::Vector2f& point2)
	: fill(sf::Color::Yellow), thickness(1.f) {
		sf::Vector2f direction = point2 - point1;
		sf::Vector2f unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
		sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

		sf::Vector2f offset = (thickness / 2.f) * unitPerpendicular;

		vertices[0].position = point1 + offset;
		vertices[1].position = point2 + offset;
		vertices[2].position = point2 - offset;
		vertices[3].position = point1 - offset;

		for (int i = 0; i < 4; ++i) {
			vertices[i].color = fill;
		}
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(vertices, 4, sf::Quads);
	}
	void setFillColor(sf::Color fill) {
		for (int i = 0; i < 4; ++i) {
			vertices[i].color = fill;
		}
	}

public:
	sf::Vertex vertices[4];
	float thickness;
	sf::Color fill;
};
void line(double x1, double y1, double x2, double y2) {
	sfLine line(sf::Vector2f(x1*sw, y1*sh), sf::Vector2f(x2*sw, y2*sh));
	line.setFillColor(current_fill);
	line.thickness = current_stroke_weight;
	main_window.draw(line);
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
// Draws text to buffer.
void text(string str, double x, double y, double h) {
	sf::Text text;
	// Text Style:
	text.setFont(font);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(current_fill);
	text.setString(str);
	text.setCharacterSize(h * sh);
	// Text Positioning:
	text.setPosition(sf::Vector2f(x * sw, y * sh));

	main_window.draw(text);
}
// Draws y centered text within a given x, y, h and text_h to buffer.
void y_centered_text(string str, double x, double y, double h, double text_h) {
	sf::Text text;
	// Text Style:
	text.setFont(font);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(current_fill);
	text.setString("l"); // Set string to l for consistent text height regardless of entered str
	text.setCharacterSize(text_h * sh);
	// Text Positioning:
	double centered_offset_y = ((h * sh) - text.getGlobalBounds().height) / 2;
	int centered_y = (y * sh) + centered_offset_y;
	text.setString(str);
	text.setOrigin(text.getGlobalBounds().left, text.getGlobalBounds().top);
	text.setPosition(sf::Vector2f(int(x * sw), centered_y));

	main_window.draw(text);
}
// Draws x and y centered text within a given x, y, w, h and text_h to buffer.
void all_centered_text(string str, double x, double y, double w, double h, double text_h) { 
	sf::Text text;
	// Text Style:
	text.setFont(font);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(current_fill);
	text.setString("l"); // Set string to l for consistent text height regardless of entered strtext.setString(str);
	text.setCharacterSize(text_h * sh);
	// Text Positioning:
	double centered_offset_y = ((h * sh) - text.getGlobalBounds().height) / 2;
	int centered_y = (y * sh) + centered_offset_y;
	text.setString(str);
	double centered_offset_x = ((w * sw) - (text.getGlobalBounds().width)) / 2;
	int centered_x = (x * sw) + centered_offset_x;
	text.setOrigin(text.getGlobalBounds().left, text.getGlobalBounds().top);
	text.setPosition(sf::Vector2f(centered_x, centered_y));

	main_window.draw(text);
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
void image(sf::Image* img, double x, double y) { 
	sf::Texture temp;
	sf::Sprite sprit;
	sprit.setPosition(sf::Vector2f(int(x * sw), int(y * sh)));
	temp.loadFromImage(*img);
	sprit.setTexture(temp);
	main_window.draw(sprit);
}
// Draws an sf::image object to buffer with given width and height.
// Images scale best by factors of two.
void image(sf::Image* img, double x, double y, double new_width, double new_height) { 
	double scale_w = (float)(new_width * sw) / img->getSize().x;
	double scale_h = (float)(new_height * sh) / img->getSize().y;
	sf::Texture temp;
	sf::Sprite sprit;
	sprit.setPosition(sf::Vector2f(int(x * sw), int(y * sh)));
	temp.loadFromImage(*img);
	sprit.setTexture(temp);
	sprit.setScale(sf::Vector2f(scale_w, scale_h));
	main_window.draw(sprit);
}

// Displays the grid which processing functions are based on.
void dev_grid() {
	stroke(120);
	stroke_weight(1);
	no_fill();
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
// Image background.
void background2() {
	main_window.clear(sf::Color(32, 32, 32));
	image(&bg2, 0, 0, 32, 18);
}
void background4() {
	main_window.clear(sf::Color(32, 32, 32));
	image(&bg4, 0, -2, 32, 24);
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
	double text_h;
	bool isCentered;

	// Default Constructor:
	SNLabel() {
	}
	// Parameterized
	SNLabel(string str, bool isCentered, double x, double y, double w, double h, double text_h)
		: SNElement(name, x, y, w, h) {
		this->type = "SNLabel";
		this->text_h = text_h;
		this->str = str;
		this->isCentered = isCentered;
	}

	void draw_element() { // Overloading virtual parent func.
		cout << " " << name << " (overloaded draw func)." << x << endl;
		fill(255);
		stroke(255);
		if (isCentered) {
			all_centered_text(str, x, y, w, h, text_h);
		}
		else {
			y_centered_text(str, x, y, h, text_h);
		}
	}
};


class SNButton : public SNElement {
	// Access specifier:
public:
	bool is_selected = false;
	bool is_centered = false;
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
	SNButton(string name, double x, double y, double w, double h, bool is_centered, void (*function)())
		: SNElement(name, x, y, w, h) {
		this->type = "SNButton";
		this->function = function;
		this->is_centered = is_centered;
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
		if (is_centered) {
			all_centered_text(name, x, y, w, h, h * .6);
		}
		else {
			y_centered_text(name, x + 0.2, y, h, h * .6);
		}
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
		y_centered_text(name, x + 0.2, y, h, h * 0.6);
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
		y_centered_text(name, x + 1.2, y, h, 0.6);
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
		all_centered_text(title, x, y, title_w, 1, 0.6);
		for (int i = 0; i < elements.size(); i++) {
			elements[i]->draw_element();
		}
	}
};


class SNOption : public SNButton {
	// Access specifier:
public:
	double x2 = 0;
	double option_width = 0;
	double data_width = 0;
	string option_data = "";

	// Default Constructor:
	SNOption() {}
	// Parameterized Constructor:
	SNOption(string name, double x, double y, double w, double h, void (*function)())
		: SNButton(name, x, y, w, h, function) {
		this->type = "SNOption";
	}
	SNOption(string name, double x, double y, double w, double h, string option_data, void (*function)())
		: SNButton(name, x, y, w, h, function) {
		this->type = "SNOption";
		this->option_data = option_data;
	}

	// Methods:
	void set_box_part1(double x, double y, double h) {
		//SNOptions are intended to be sized post object initialization as apart of a SNMenu object.
		this->x = x;
		this->y = y;
		this->h = h;
	}

	virtual double basic_width() {
		option_width = (option_data == "") ? text_width(name, 0.8) + 0.4 : text_width(name, 0.8) + 0.4 + 2;
		return option_width;
	}
	virtual double complex_width() {
		x2 = this->x + this->option_width;
		
		data_width = (option_data != "") ? text_width(option_data, 0.8) + 0.4 : 0;
		this->w = option_width + data_width;
		return this->w;
	}
	virtual void final_update(double menu_width) {}
	void draw_element() {
		// Coloring and styling is intended to occur from SNMenu object.
		y_centered_text(name, x + 0.2, y, h, 0.8);
		if (option_data != "") {
			y_centered_text(option_data, x2 + 0.2, y, h, 0.8);
		}
	}
};


class SNRadio_Option : public SNOption {
	// Access specifier:
public:
	int radio_pos;
	vector<string> radios;
	double spacer = 1.5;
	double sum_radio_widths = 0;

	// Default Constructor:
	SNRadio_Option() {
	}
	// Parameterized Constructor:
	SNRadio_Option(string name, double x, double y, double w, double h, void (*function)(), vector<string> radios)
	: SNOption(name, x, y, w, h, function) {
		this->type = "SNRadio_Option";
		this->radios = radios;
	}

	// Methods
	double basic_width() {
		return 0;
	}
	double complex_width() {
		int current_x = this->x;
		for (int i = 0; i < radios.size(); i++) {
			current_x = current_x + 1.2 + text_width(radios[i], 0.8) + spacer;
		}
		this->w = current_x - x;
		return w;
	}
	void final_update(double menu_width) {
		if (this->w < menu_width) {
			for (int i = 0; i < radios.size(); i++) {
				sum_radio_widths += text_width(radios[i], 0.8);
			}

			double taken_space = sum_radio_widths + (radios.size()) * (1.2) + .2;
			double space_left = menu_width - taken_space;
			this->spacer = space_left/(radios.size()-1);
		}
	}
	void draw_element() {
		cout << " " << name << " (overloaded draw func)." << x << "." << y << endl;
		double current_x = this->x;
		for (int i = 0; i < radios.size(); i++) {
			if (radio_pos == i) {
				image(&radio_full, current_x, y, 1, 1);
			}
			else {
				image(&radio_empty, current_x, y, 1, 1);
			}
			// Coloring and styling is intended to occur from SNMenu object.
			y_centered_text(radios[i], current_x + 1.2, y, h, 0.8);
			current_x = current_x + 1.2 + text_width(radios[i], 0.8) + spacer;
		}
	}
	string radio_switch() {
		radio_pos = (radio_pos == radios.size() - 1) ? 0 : radio_pos + 1;
		return radios[radio_pos];
	}
};


bool uses_menu_outline = false;
class SNMenu : public SNElement {
	// Access specifier:
public:
	vector<SNOption*> options;
	int selected_option_pos = 0;
	int num_options = 0;
	double option_h = 0;
	void (*refresh)();


	// Default Constructor:
	SNMenu() {}
	// Parameterized Constructor:
	SNMenu(string name, double x, double y, double w, double option_h, vector<SNOption*> options, void (*refresh)()) {
		this->type = "SNMenu";
		this->name = name;
		this->x = x;
		this->y = y;
		this->w = w;
		this->option_h = option_h;
		this->h = options.size() * option_h;
		this->options = options;
		this->refresh = refresh;
		for (int i = 0; i < options.size(); i++) {
			if (options[i]->name != " " || options[i]->name != "") {
				num_options++;
			}
		}
	}

	bool updated_once = false;
	void resize_update() {
		// Set proper rect for options.
		double max_option_w = 0;
		// Set X Y H + Find largest basic width
		for (int i = 0; i < options.size(); i++) {
			options[i]->set_box_part1(x, y + i, option_h);
			double option_width = options[i]->basic_width();
			if (max_option_w < option_width) {
				max_option_w = option_width;
			}			
		}

		double total_width = 0;
		for (int i = 0; i < options.size(); i++) {
			options[i]->option_width = max_option_w;
			if (total_width < options[i]->complex_width()) {
				total_width = options[i]->complex_width();
			}
		}

		double max_total_w = 0;
		for (int i = 0; i < options.size(); i++) {
			if (max_total_w < options[i]->w) {
				max_total_w = options[i]->w;
			}
		}

		for (int i = 0; i < options.size(); i++) {
			options[i]->final_update(max_total_w);
		}

		this->w = max_total_w;
		updated_once = true;
	}
	void draw_element() {
		if (updated_once == false) {
			resize_update();
		}
		if (uses_menu_outline) {
			stroke(255);
			no_fill();
			rect(x, y, w, h);
		}
		for (int i = 0; i < options.size(); i++) {
			if (options[i]->name == " " || options[i]->name == "") {
				continue;
			}
			if (i == selected_option_pos) {
				fill(sf::Color(218, 119, 48));
			}
			else {
				fill(255);
			}
			options[i]->draw_element();
		}
	}
	void find_option(double grid_x, double grid_y) {
		for (int i = 0; i < options.size(); i++) {
			SNOption* e = options[i];
			if (e->x < grid_x && grid_x < e->x + e->w && e->y < grid_y && grid_y < e->y + e->h) {
				e->function();
			}
		}
	}
	void navigate(string key) {
		if (key == "w" && selected_option_pos > 0) {
			selected_option_pos--;
			for (int x = selected_option_pos; x > 0; x--) {
				if (options[x]->name != " " && options[x]->name != "") {
					break;
				}
				selected_option_pos--;
			}

		}
		if (key == "s" && selected_option_pos < num_options - 1) {
			selected_option_pos++;
			for (int x = selected_option_pos; x < options.size() - 1; x++) {
				if (options[x]->name != " " && options[x]->name != "") {
					break;
				}
				selected_option_pos++;
			}
		}
		if (key == "ENTER") {
			options[selected_option_pos]->function();
			cout << "ENTER " << options[selected_option_pos]->name << " Selected." << endl;
		}
		refresh();
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

