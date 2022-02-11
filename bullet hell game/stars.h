#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include"globals.h"
class stars{
private:
	double xpos;
	double ypos;
	int RG;
	int blue;
	int size;
public:
	stars();
	~stars(){ }
	void move();
	void reposition();
	void draw(sf::RenderWindow& window);
};

