#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Vector2.h"

using namespace std;

class Button {
private:
	sf::Texture btnFill;
	sf::Texture btnOutl;
	sf::Texture btnOutlE;
	sf::Sprite Fill;
	sf::Sprite Outl;
	sf::Sprite OutlE1;
	sf::Sprite OutlE2;
	sf::Text Label;
	string i_label;
	string h_label;
	string p_label;
	bool min_size;
	enum Status { idle, hover, press, disabled, hidden } e_status;
	Vector2 pos, pos2; // pos: Top left corner of element. pos2: Bottom right corner of element
	int fSize;
	float fineAdjust;
public:
	sf::Font Font;
	Button(string iLabel, string hLabel = "", string pLabel = "", bool minSize = true);
	void setLabel(string iLabel);
	void upt();
	bool getDisabled();
	void setDisabled(bool);
	bool getHidden();
	void setHidden(bool);
	void setPosition(float newX, float newY);
	Vector2 getPosition();
	float getHeight();
	float getWidth();
	sf::Sprite getSprite(int x = 1);
	sf::Text getLabel();
	bool withinBounds(int coorX, int coorY);
	bool isPressed(int x = 1);
};