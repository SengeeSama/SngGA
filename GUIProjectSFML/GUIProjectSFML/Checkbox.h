#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Vector2.h"

using namespace std;

class Checkbox {
private:
	sf::Texture chboxFill;
	sf::Texture chboxOutl;
	sf::Texture chboxMark;
	sf::Texture chboxNone;
	sf::Font Font;
	sf::Sprite Outl;
	sf::Sprite Mark;
	sf::Sprite Fill;
	sf::Text Label;
	string i_label;
	enum Status { idle, hover, press, disabled, hidden } e_status;
	enum Mode { on, off } e_mode;
	Vector2 pos, pos2; // pos: Top left corner of element. pos2: Bottom right corner of element
	int fineAdjust = 0;
public:
	Checkbox(string iLabel, int s = 0);
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
	sf::Text getLabel();
	bool withinBounds(int coorX, int coorY);
	bool isPressed(int x = 1);
};