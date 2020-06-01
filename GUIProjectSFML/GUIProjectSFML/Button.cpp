#include "Button.h"

//asign the local variable i_label with the param iLabel etc...
Button::Button(string iLabel, string hLabel, string pLabel, bool minSize) : i_label(iLabel), h_label(hLabel), p_label(pLabel), min_size(minSize)
{
	//What is going on when we create the button this is your "Create() method"
	cout << "Creating Button..." << endl;
	if (false) {
		btnFill.loadFromFile("btn_mask.png");
		btnOutl.loadFromFile("btn_outl.png");
		btnOutlE.loadFromFile("btn_outl_e.png");
		Font.loadFromFile("arial.ttf");
	}
	else {
		btnFill.loadFromFile("res/btn_mask.png");
		btnOutl.loadFromFile("res/btn_outl.png");
		btnOutlE.loadFromFile("res/btn_outl_e.png");
		Font.loadFromFile("res/arial.ttf");
	}
	fSize = 24;
	Label.setFont(Font);
	Label.setCharacterSize(fSize);
	Label.setFillColor(sf::Color::Black);
	setLabel(i_label);
	/// cout << Label.getLocalBounds().width << endl << Label.getLocalBounds().height << endl;
	Outl.setTexture(btnOutl);
	OutlE1.setTexture(btnOutlE);
	OutlE2.setTexture(btnOutlE);
	Fill.setTexture(btnFill);
	Fill.setColor(sf::Color(204, 204, 204));
	Outl.setColor(sf::Color(122, 122, 122, 0));
	OutlE1.setColor(sf::Color(122, 122, 122, 0));
	OutlE2.setColor(sf::Color(122, 122, 122, 0));
	/// 
	cout << "Width: " << Fill.getLocalBounds().width * Outl.getScale().x << endl;
	cout << "Scale X: " << Outl.getScale().x << endl;
	upt();
}

void Button::setLabel(string iLabel) {
	i_label = iLabel;
	Label.setString(i_label);
	cout << "Label width: " << Label.getLocalBounds().width * 1.25 << endl;
	cout << (Label.getLocalBounds().width * 1.25 < 135.f && min_size) << endl;
	if (Label.getLocalBounds().width * 1.25 < 135.f && min_size) {
		Fill.setScale(sf::Vector2f(135.f / 48.f, 1));
		Outl.setScale(sf::Vector2f(135.f / 48.f, 1));
		cout << "Default width used: 135" << endl;
	}
	else {
		Fill.setScale(sf::Vector2f((Label.getLocalBounds().width + 40.f) / 48, 1));
		Outl.setScale(sf::Vector2f((Label.getLocalBounds().width + 40.f) / 48, 1));
		cout << "Label width used: " << Label.getLocalBounds().width * 1.25 << endl;
	}
	if (Label.getLocalBounds().height > fSize * 0.75) {
		fineAdjust = 0;
	}
	else {
		fineAdjust = fSize - (fSize * 0.75);
	}
	Label.setOrigin(sf::Vector2f(((Outl.getLocalBounds().width * Outl.getScale().x) / 2 - (Label.getLocalBounds().width) / 2) * (-1), ((Outl.getLocalBounds().height * Outl.getScale().y) / 2 - (Label.getLocalBounds().height + (fSize / 3) + fineAdjust) / 2) * (-1)));
}

void Button::upt() {
	if (Label.getLocalBounds().width > ((Outl.getLocalBounds().width * Outl.getScale().x) * 0.9)) {
		/*
		fSize -= 3;
		Label.setCharacterSize(fSize);
		Label.setString(i_label);
		Label.setOrigin(sf::Vector2f(((Outl.getLocalBounds().width) / 2 - (Label.getLocalBounds().width) / 2) * (-1), ((Outl.getLocalBounds().height) / 2 - (Label.getLocalBounds().height + (fSize / 3) + fineAdjust) / 2) * (-1)));
		if (Label.getLocalBounds().width > (Outl.getLocalBounds().width * 0.9)) {
			upt();
		}
		*/
	}
	else {
		if (Label.getLocalBounds().width * 1.25 < 135 && min_size) {
			Fill.setScale(sf::Vector2f(135.f / 48.f, 1));
			Outl.setScale(sf::Vector2f(135.f / 48.f, 1));
		}
		else {
			Fill.setScale(sf::Vector2f((Label.getLocalBounds().width + 40.f) / 48, 1));
			Outl.setScale(sf::Vector2f((Label.getLocalBounds().width + 40.f) / 48, 1));
		}
		Label.setScale(sf::Vector2f(1, 1));
		Fill.setColor(sf::Color(204, 204, 204));
		Outl.setColor(sf::Color(122, 122, 122, 0));
		OutlE1.setColor(sf::Color(122, 122, 122, 0));
		OutlE2.setColor(sf::Color(122, 122, 122, 0));
		Fill.setOrigin(0.f, 0.f);
		Label.setOrigin(sf::Vector2f(((Outl.getLocalBounds().width * Outl.getScale().x) / 2 - (Label.getLocalBounds().width) / 2) * (-1), ((Outl.getLocalBounds().height * Outl.getScale().y) / 2 - (Label.getLocalBounds().height + (fSize / 3) + fineAdjust) / 2) * (-1)));
		OutlE1.setPosition(sf::Vector2f(pos.x, pos.y));
		OutlE2.setPosition(sf::Vector2f(pos.x + (Outl.getLocalBounds().width * Outl.getScale().x) - 3, pos.y));
		setPosition(pos.x, pos.y);

		if (e_status == Status::disabled) {
			Label.setFillColor(sf::Color(122, 122, 122));
		}
		else {
			Label.setFillColor(sf::Color::Black);
			if (e_status == Status::idle) {
			}
			else if (e_status == Status::hover) {
				Outl.setColor(sf::Color(122, 122, 122));
				OutlE1.setColor(sf::Color(122, 122, 122));
				OutlE2.setColor(sf::Color(122, 122, 122));
			}
			else if (e_status == Status::press) {
				Fill.setColor(sf::Color(153, 153, 153));
				pos.x = pos.x + ((Outl.getLocalBounds().width * Outl.getScale().x) - ((Outl.getLocalBounds().width * Outl.getScale().x) * 0.96)) / 2;
				pos.y = pos.y + ((Outl.getLocalBounds().height * Outl.getScale().y) - ((Outl.getLocalBounds().height * Outl.getScale().y) * 0.96)) / 2;
				Fill.scale(sf::Vector2f(0.96, 0.96));
				Label.scale(sf::Vector2f(0.96, 0.96));
				setPosition(pos.x, pos.y);
				pos.x = pos.x - ((Outl.getLocalBounds().width * Outl.getScale().x) - ((Outl.getLocalBounds().width * Outl.getScale().x) * 0.96)) / 2;
				pos.y = pos.y - ((Outl.getLocalBounds().height * Outl.getScale().y) - ((Outl.getLocalBounds().height * Outl.getScale().y) * 0.96)) / 2;
			}
		}
	}
}

bool Button::getDisabled() {
	return e_status == Status::disabled;
}

void Button::setDisabled(bool value) {
	if (value) {
		e_status = Status::disabled;
	}
	else if (e_status == Status::disabled) {
		e_status = Status::idle;
	}
}

bool Button::getHidden() {
	return e_status == Status::hidden;
}

void Button::setHidden(bool value) {
	if (value) {
		e_status = Status::hidden;
	}
	else if (e_status == Status::hidden) {
		e_status = Status::idle;
	}
}

void Button::setPosition(float newX, float newY) {
	pos.x = newX;
	pos.y = newY;
	pos2.x = newX + (Outl.getLocalBounds().width * Outl.getScale().x);
	pos2.y = newY + (Outl.getLocalBounds().height * Outl.getScale().y);
	Outl.setPosition(sf::Vector2f(newX, newY));
	Fill.setPosition(sf::Vector2f(newX, newY));
	Label.setPosition(sf::Vector2f(newX, newY));
}

Vector2 Button::getPosition(){
	return pos;
}

float Button::getHeight() {
	return Outl.getLocalBounds().height * Outl.getScale().y;
}

float Button::getWidth() {
	return Outl.getLocalBounds().width * Outl.getScale().x;
}

sf::Sprite Button::getSprite(int x) {
	if (x == 1) {
		return Fill;
	}
	else if (x == 2) {
		return Outl;
	}
	else if (x == 3) {
		return OutlE1;
	}
	else if (x == 4) {
		return OutlE2;
	}
}

sf::Text Button::getLabel() {
	return Label;
}

bool Button::withinBounds(int coorX, int coorY) {
	if (coorX > pos.x && coorX < pos2.x && coorY > pos.y && coorY < pos2.y && e_status != Status::disabled) {
		if (e_status != Status::press) {
			if (h_label != "") {
				Label.setString(h_label);
			}
			e_status = Status::hover;
		}
		return true;
	}
	else if (e_status != Status::disabled) {
		if (e_status != Status::press) {
			if (i_label != "") {
				Label.setString(i_label);
			}
		}
		e_status = Status::idle;
		return false;
	}
	else {
		return false;
	}
}

bool Button::isPressed(int x) {
	if (e_status == Status::hover && x == 1) {
		if (p_label != "") {
			Label.setString(p_label);
		}
		e_status = Status::press;
		return true;
	}
	else if (e_status == Status::press && x == 2) {
		if (h_label != "") {
			Label.setString(h_label);
		}
		e_status = Status::hover;
		return true;
	}
	else {
		return false;
	}
}