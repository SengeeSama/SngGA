#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Vector2.h"

using namespace std;

class Switch {
private:
	sf::Texture swOutl;
	sf::Texture swFill;
	sf::Texture swBall;
	sf::Font Font;
	sf::Sprite Outl;
	sf::Sprite Ball;
	sf::Text Label;
	sf::Text InfoLabel;
	string i_label;
	enum Status { idle, hover, press, disabled, hidden } e_status;
	enum Mode { on, off } e_mode;
	enum Animation { aOn, aOff, none } e_anim;
	Vector2 pos, pos2; // pos: Top left corner of element. pos2: Bottom right corner of element
	int fineAdjust = 0;
	float bPos = 0.f; // Ball position
public:
	Switch(string iLabel = "", int s = 0);
	void animate();
	void upt();
	bool getDisabled();
	void setDisabled(bool);
	bool getHidden();
	void setHidden(bool);
	bool isOn();
	void setPosition(float newX, float newY);
	Vector2 getPosition();
	float getHeight();
	float getWidth();
	sf::Sprite getSprite(int x = 1);
	sf::Text getLabel(int x = 1);
	bool withinBounds(int coorX, int coorY);
	bool isPressed(int x = 1);
};