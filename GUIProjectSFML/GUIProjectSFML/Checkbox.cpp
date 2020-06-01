#include "Checkbox.h"

//asign the local variable i_label with the param iLabel etc...
Checkbox::Checkbox(string iLabel, int s) : i_label(iLabel)
{
	//What is going on when we create the button this is your "Create() method"
	cout << "Creating Checkbox..." << endl;
	// disblTex.loadFromFile("btn_disb;.png");
	if (false) {
		chboxFill.loadFromFile("chbox_fill.png");
		chboxOutl.loadFromFile("chbox_outl.png");
		chboxMark.loadFromFile("chbox_mark.png");
		chboxNone.loadFromFile("chbox_none.png");
		Font.loadFromFile("arial.ttf");
	}
	else {
		chboxFill.loadFromFile("res/chbox_fill.png");
		chboxOutl.loadFromFile("res/chbox_outl.png");
		chboxMark.loadFromFile("res/chbox_mark.png");
		chboxNone.loadFromFile("res/chbox_none.png");
		Font.loadFromFile("res/arial.ttf");
	}
	Label.setFont(Font);
	Label.setCharacterSize(24);
	Label.setFillColor(sf::Color::Black);
	Label.setString(i_label);
	if (s == 0) {
		e_mode = Mode::off;
	}
	else {
		e_mode = Mode::on;
	}
	e_status = Status::idle;
	Fill.setTexture(chboxNone);
	Outl.setTexture(chboxNone);
	Mark.setTexture(chboxNone);
	Mark.setOrigin(sf::Vector2f(0.f, 0.f));
	if (Label.getLocalBounds().height <= 18) { fineAdjust = 0; }
	if (Label.getLocalBounds().height >= 23) { fineAdjust = 5; }
	Label.setOrigin(sf::Vector2f(((Outl.getLocalBounds().width + 18)) * (-1), 0.f));
	upt();
}

void Checkbox::upt() {
	if (e_mode == Mode::off) {
		if (e_status == Status::idle) {
			Fill.setTexture(chboxFill);
			Outl.setTexture(chboxOutl);
			Mark.setTexture(chboxNone);
			Fill.setColor(sf::Color(255, 255, 255));
			Outl.setColor(sf::Color(51, 51, 51));
		}
		else if (e_status == Status::hover) {
			Fill.setTexture(chboxFill);
			Outl.setTexture(chboxOutl);
			Mark.setTexture(chboxNone);
			Fill.setColor(sf::Color(255, 255, 255));
			Outl.setColor(sf::Color(0, 0, 0));
		}
		else if (e_status == Status::press) {
			Fill.setTexture(chboxFill);
			Outl.setTexture(chboxNone);
			Mark.setTexture(chboxNone);
			Fill.setColor(sf::Color(102, 102, 102));
		}
	}
	else if (e_mode == Mode::on) {
		if (e_status == Status::idle) {
			Fill.setTexture(chboxFill);
			Outl.setTexture(chboxNone);
			Mark.setTexture(chboxMark);
			Fill.setColor(sf::Color(0, 120, 215));
			Mark.setColor(sf::Color(255, 255, 255));
		}
		else if (e_status == Status::hover) {
			Fill.setTexture(chboxFill);
			Outl.setTexture(chboxOutl);
			Mark.setTexture(chboxMark);
			Fill.setColor(sf::Color(0, 120, 215));
			Outl.setColor(sf::Color(0, 0, 0));
			Mark.setColor(sf::Color(255, 255, 255));
		}
		else if (e_status == Status::press) {
			Fill.setTexture(chboxFill);
			Outl.setTexture(chboxNone);
			Mark.setTexture(chboxMark);
			Fill.setColor(sf::Color(102, 102, 102));
			Mark.setColor(sf::Color(255, 255, 255));
		}
	}
}

bool Checkbox::getDisabled() {
	return e_status == Status::disabled;
}

void Checkbox::setDisabled(bool value) {
	if (value) {
		e_status = Status::disabled;
	}
	else if (e_status == Status::disabled) {
		e_status = Status::idle;
	}
}

bool Checkbox::getHidden() {
	return e_status == Status::hidden;
}

void Checkbox::setHidden(bool value) {
	if (value) {
		e_status = Status::hidden;
	}
	else if (e_status == Status::hidden) {
		e_status = Status::idle;
	}
}

bool Checkbox::isOn() {
	if (e_mode == Mode::on) {
		return true;
	}
	else if (e_mode == Mode::off) {
		return false;
	}
}

void Checkbox::setPosition(float newX, float newY) {
	pos.x = newX;
	pos.y = newY;
	pos2.x = newX + Outl.getLocalBounds().width;
	pos2.y = newY + Outl.getLocalBounds().height;
	Fill.setPosition(sf::Vector2f(newX, newY));
	Outl.setPosition(sf::Vector2f(newX, newY));
	Mark.setPosition(sf::Vector2f(newX, newY));
	Label.setPosition(sf::Vector2f(newX, newY));
}

Vector2 Checkbox::getPosition() {
	return pos;
}

float Checkbox::getHeight() {
	return Outl.getLocalBounds().height;
}

float Checkbox::getWidth() {
	return Outl.getLocalBounds().width;
}

sf::Sprite Checkbox::getSprite(int x) {
	if (x == 1) {
		return Fill;
	}
	else if (x == 2) {
		return Outl;
	}
	else if (x == 3) {
		return Mark;
	}
}

sf::Text Checkbox::getLabel() {
	return Label;
}

bool Checkbox::withinBounds(int coorX, int coorY) {
	if (coorX > pos.x && coorX < pos2.x && coorY > pos.y && coorY < pos2.y) {
		if (e_status != Status::press) {
			e_status = Status::hover;
		}
		return true;
	}
	else {
		if (e_status != Status::press) {
		}
		e_status = Status::idle;
		return false;
	}
}

bool Checkbox::isPressed(int x) {
	if (e_status == Status::hover && x == 1) {
		e_status = Status::press;
		return true;
	}
	else if (e_status == Status::press && x == 2) {
		e_status = Status::hover;
		if (e_mode == Mode::off) {
			e_mode = Mode::on;
		}
		else {
			e_mode = Mode::off;
		}
		return true;
	}
	else {
		return false;
	}
}