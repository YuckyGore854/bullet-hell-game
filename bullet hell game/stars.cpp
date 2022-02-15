#include "stars.h"

stars::stars() {
	xpos = rand() % SCREEN_W;
	ypos = rand() % SCREEN_H;
	RG = rand() % 201;
	blue = rand() % 151 + 100;
	size = rand() % 2 + 1;
}

void stars::move(int x, int y) {
	ypos += 5;

}

void stars::reposition() {
	if (ypos > SCREEN_H) {
		ypos = 0;
		xpos = rand() % SCREEN_W;
		RG = rand() % 201;
		blue = rand() % 151 + 100;
	}
}

void stars::draw(sf::RenderWindow& window) {
	sf::CircleShape shape(size);
	shape.setFillColor(sf::Color(RG, RG, blue));
	shape.setPosition(xpos, ypos);
	window.draw(shape);//draw to gamescreen
}