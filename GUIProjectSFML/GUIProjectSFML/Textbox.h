#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Vector2.h"

using namespace std;

class Textbox {
private:
	sf::Texture txboxFill;
	sf::Texture txboxOutlR;
	sf::Texture txboxOutlE;
	sf::Texture txboxCursor;
	sf::Sprite Fill;
	sf::Sprite OutlR1;
	sf::Sprite OutlR2;
	sf::Sprite OutlE1;
	sf::Sprite OutlE2;
	sf::Sprite Cursor;
	sf::Text Label;
	sf::Text tmpLabel;
	sf::Text cLabel;
	sf::String i_label;
	sf::String t_label;
	sf::String tmp_label;
	sf::String c_label;
	sf::String ct_label;
	enum Status { idle, hover, press, hidden } e_status;
	enum Mode { on, off } e_mode;
	Vector2 pos, pos2; // pos: Top left corner of element. pos2: Bottom right corner of element
	float sizeX, sizeY;
	int labelRows;
public:
	int fSize;
	sf::Font Font;
	Textbox(float width, float height, string iLabel = "");
	void upt();
	void labelUpt(int c, int c2 = -1);
	void Backspace(int c, int x = 1);
	void BackspaceC();
	bool isOn();
	bool getHidden();
	void setHidden(bool);
	void setPosition(float newX, float newY);
	Vector2 getPosition();
	float getHeight();
	float getWidth();
	sf::Sprite getSprite(int x = 1);
	sf::Text getLabel();
	sf::Text getTmpLabel();
	void setLabel(string newLabel, bool ghostText = true);
	void reset();
	bool withinBounds(int coorX, int coorY);
	bool isPressed(int x = 1);
};