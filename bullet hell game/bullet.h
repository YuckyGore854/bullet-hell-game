#pragma once
#include"globals.h"
#include"SFML/Graphics.hpp"
#include<math.h>
class bullet{
private:
	int xpos;
	int ypos;
	double xVel;
	double yVel;
	bool alive;
	double angle;
	double radius;
	sf::Sprite image;
public:
	bullet();
	~bullet();
	bullet(int x, int y, sf::Sprite sprite, double angle);
	bullet(int x, int y, double a);
	void draw(sf::RenderWindow& window);
	void kill();
	bool offScreen();
	bool isALive();
	bool collide(double x, double y);
	int getx();
	int gety();
	void move();
	void move2();
	void move3();
};

