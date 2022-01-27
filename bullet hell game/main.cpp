//SFML C++ Bullet Hell
// Created by Dr. Mo Jan 2022
//dynamicsofanasteroid.com

#include<iostream>
#include<vector>
#include"missile.h"
#include"bullet.h"
#include "SFML/Graphics.hpp"
#include"globals.h"
using namespace std;

//enum DIRECTIONS { LEFT, RIGHT, UP, DOWN }; //left is 0, right is 1, up is 2, down is 3

int main() {
    //game set up (you'll need these lines in every game)
    sf::RenderWindow screen(sf::VideoMode(SCREEN_W, SCREEN_H), "Bullet Hell"); //set up screen
    sf::Event event; //set up event queue
    sf::Clock clock; //set up the clock (needed for game timing)
    const float FPS = 60.0f; //FPS
    screen.setFramerateLimit(FPS); //set FPS



    //player setup------------------------------------------------
    sf::Texture ship;
    ship.loadFromFile("ship.png");
    sf::IntRect playerImg(0, 0, 30, 30); //select portion of image to draw (our ship is 30x30)
    sf::Sprite player(ship, playerImg);
    // player.setTexture(ship); //use this instead of 2 lines above for static images
    int xpos = 400;
    int ypos = 700;
    int vx = 0;
    int vy = 0;
    int playerDir = -1;
    player.setPosition(xpos, ypos); //top left "corner" of circle (not center!)
    int ticker = 0;
    int frameNum = 0;
    bool keys[] = { false, false, false, false, false };

    //missile (the things the player shoots) setup----------
    int justShot = 0;
    //set up variables for missile image
    sf::Texture MissileImg;
    MissileImg.loadFromFile("missile.png");
    sf::Sprite MissilePic;
    MissilePic.setTexture(MissileImg);

    //bullet cariables
    double minBullets = 60; //speeds up object creation
    int counter = 0; //slow down object creation
    int moveTimer = 0;

    vector<bullet*> bullets;
    vector<bullet*>::iterator bulletIter;

    //vector to hold missiles
    vector<missile*> missiles;//creates vector of class missile POINTERS
    vector<missile*>::iterator iter2; //creates an iterator to walk through our missiles vector
    for (int i = 0; i < 5; i++) {
        missile* newMissile = new missile(xpos, ypos, MissilePic); //dynamically instantiates 5 missiles
        missiles.push_back(newMissile); //pushes a new missile into vector
    }

    //################### HOLD ONTO YOUR BUTTS, ITS THE GAME LOOP###############################################################
    while (screen.isOpen()) {//keep window open until user shuts it down

        while (screen.pollEvent(event)) { //look for events-----------------------

            //this checks if the user has clicked the little "x" button in the top right corner
            if (event.type == sf::Event::EventType::Closed)
                screen.close();

            //KEYBOARD INPUT 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                keys[LEFT] = true;
            }
            else keys[LEFT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                keys[RIGHT] = true;
            }
            else keys[RIGHT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                keys[UP] = true;
            }
            else keys[UP] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                keys[DOWN] = true;
            }
            else keys[DOWN] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                keys[SPACE] = true;
            }
            else keys[SPACE] = false;

        }//end event loop---------------------------------------------------------------

         //move ship
        if (keys[LEFT] == true) {
            vx = -5;
            playerDir = LEFT;
        }

        else if (keys[RIGHT] == true) {
            vx = 5;
            playerDir = RIGHT;
        }

        else { vx = 0; playerDir = -1; }

        if (keys[UP] == true)
            vy = -5;
        else if (keys[DOWN] == true)
            vy = 5;
        else vy = 0;

        xpos += vx;
        ypos += vy;
        player.setPosition(xpos, ypos);

        justShot++;//increment ticker
        if (keys[SPACE]) {
            for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {//walk through the vector, look at each thing
                if (((*iter2)->isALive()) == false && justShot > 5) {//only shoot dead missiles, add in pause
                    (*iter2)->shoot(xpos, ypos);
                    justShot = 0;//reset ticker
                }
            }
        }
        //move missiles
        for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
            if ((*iter2)->isALive())//only move live missiles
                (*iter2)->move();
        }
        //cull the missiles
        for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
            if ((*iter2)->offScreen())//if we move above the edge of the screen
                (*iter2)->kill();//set as dead
        }

        counter++; //variable to slow down object creating. initialize it to 0 above your gameloop
        minBullets -= 0.001; //variable initialized to 60. Subtracting here speeds up object creation over time
        if (counter > minBullets) {
            //create new bullets, push into vector
            bullet* newBullet = new bullet(500, 100, 0);
            bullets.push_back(newBullet);
            bullet* newBullet2 = new bullet(500, 100, 3.14);
            bullets.push_back(newBullet2);
            bullet* newBullet3 = new bullet(500, 100, 3.14 / 2);
            bullets.push_back(newBullet3);
            bullet* newBullet4 = new bullet(500, 100, 3 * 3.14 / 2);
            bullets.push_back(newBullet4);

            counter = 0;
        }
        //move the bullets
        moveTimer += 2; //movetimer slwos down MOVEMENT
        if (moveTimer > 2400)
            moveTimer = 0;

        for (bulletIter = bullets.begin(); bulletIter != bullets.end(); bulletIter++) {
            if (moveTimer < 600) {
                (*bulletIter)->move();
            }
            else if (moveTimer < 1200) {
                (*bulletIter)->move2();
            }
            else if (moveTimer < 1800) {
                (*bulletIter)->move();
            }
            else if (moveTimer < 2400) {
                (*bulletIter)->move3();
                
            }
        }

        for (bulletIter = bullets.begin(); bulletIter != bullets.end(); bulletIter++) {
            if ((*bulletIter)->offScreen()) {
                (*bulletIter)->~bullet(); // call the destructor (destroys the obejct, releases memory)
                bulletIter = bullets.erase(bulletIter); //take it out of the vector too
            }
        }
        for (bulletIter = bullets.begin(); bulletIter != bullets.end(); bulletIter++) {
            
                (*bulletIter)->draw(screen);
            
        }

        //render section-----------------------------------------
        screen.clear(); //wipes screen, without this things smear

        //player animation----------------------------------------------------------------------------------------------
        ticker += 1; //animation ticks every frame

        if (ticker % 4 == 0) //determines how often the game updates the sprite
            frameNum += 1;

        if (frameNum > 4)//reverts back to beginning of the sprite to avoid sprite flickering
            frameNum = 0;

        if (playerDir == -1)
            player.setTextureRect(sf::IntRect((frameNum) * 32, 0, 32, 32));//updates the part of the spritesheet that we draw

        else if (playerDir == LEFT)
            player.setTextureRect(sf::IntRect((frameNum + 6) * 32, 0, -32, 32));

        else if (playerDir == RIGHT)
            player.setTextureRect(sf::IntRect((frameNum + 5) * 32, 0, 32, 32));

        screen.draw(player); //draw player
        for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
            if ((*iter2)->isALive())//only move live missiles
                (*iter2)->draw(screen);
        }
        screen.display(); //flips memory drawings onto screen

    }//######################## end game loop ###################################################################################

        cout << "goodbye!" << endl;
} //end of main