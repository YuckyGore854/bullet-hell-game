#include "missile.h"

//default constructor
missile::missile() {
	xpos = 0;
	ypos = 0;
	alive = false;
}

//destructor
missile::~missile() {}

//parameterized constructor with SFML image
missile::missile(int x, int y, sf::Sprite sprite) {
	xpos = x;
	ypos = y;
	alive = false;
	image = sprite;
}

//parameterized constructor without image (not used, code would need to be adjusted)
missile::missile(int x, int y) {
	xpos = x;
	ypos = y;
	alive = false;
}

void missile::move() {
	ypos -= 5;
}

//we pass a pointer to the SFML game screen here
//so the functiuon knows where to draw it!
void missile::draw(sf::RenderWindow& window) {
	if (alive) {//don't draw dead missiles
		image.setPosition(xpos, ypos);
		window.draw(image);//draw to gamescreen
	}
}

void missile::kill() {
	alive = false;
}

bool missile::offScreen() {
	return ypos < 0;
}

void missile::shoot(int x, int y) {
	alive = true;
	xpos = x;
	ypos = y;
}

bool missile::isALive() {
	return alive;
}

bool missile::collide(double x, double y) {
	if (sqrt((x - xpos) * (x - xpos) + (y - ypos) * (y - ypos)) < 32) {//circular collision (distance formula)
		return true;
	}
	return false;
}

int missile::getx() {
	return xpos;
}

int missile::gety() {
	return ypos;
}