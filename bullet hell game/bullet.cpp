#include "bullet.h"
#include<iostream>

bullet::bullet() {
	xpos = 0;
	ypos = 0;
	alive = false;
}

bullet::~bullet() {}

bullet::bullet(int x, int y, sf::Sprite sprite, double a) {
	angle = angle * 3.14 / 180;
	xpos = x;
	ypos = y;
	radius = 10;
	alive = false;
	image = sprite;
}

bullet::bullet(int x, int y, double a) {
	xpos = x;
	ypos = y;
	angle = a;
	radius = 10;
	alive = false;
}

void bullet::move() {
	ypos += 5;
}

void bullet::move2() {
	radius = 10;
	angle += .1;
	if (angle > 6.28)//2 pir: means the bullet has done a full circle
		angle = 0;
	xpos = xpos + cos(angle) * (radius) / 2;
	ypos = ypos + sin(angle) * (radius) / 2 + 1;
}

void bullet::move3() {
	radius = 14;
	angle -= 0.1;
	if (angle < -6.28)
		angle = 0;
	xpos = xpos + sin(angle) * (radius) / 2;
	ypos = ypos + cos(angle) * (radius) / 2 - 1;
}

bool bullet::offScreen() {
	if (ypos < 0 || ypos > 800 || xpos < 0 || xpos > 800)
		return true;
	return false;
}

void bullet::draw(sf::RenderWindow& window) {
	sf::CircleShape shape(10);
	shape.setFillColor(sf::Color(100, 250, 50));
	//if (isALive()) {
		shape.setPosition(xpos, ypos);
		window.draw(shape);
	//}
}

bool bullet::isALive() {
	return alive;
}