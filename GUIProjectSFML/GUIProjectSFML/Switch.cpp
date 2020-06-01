#include "Switch.h"

//asign the local variable i_label with the param iLabel etc...
Switch::Switch(string iLabel, int s) : i_label(iLabel)
{
	//What is going on when we create the button this is your "Create() method"
	cout << "Creating Switch..." << endl;
	// disblTex.loadFromFile("btn_disb;.png");
	if (false) {
		swOutl.loadFromFile("sw_outl.png");
		swFill.loadFromFile("sw_fill.png");
		swBall.loadFromFile("sw_ball.png");
		Font.loadFromFile("arial.ttf");
	}
	else {
		swOutl.loadFromFile("res/sw_outl.png");
		swFill.loadFromFile("res/sw_fill.png");
		swBall.loadFromFile("res/sw_ball.png");
		Font.loadFromFile("res/arial.ttf");
	}
	Label.setFont(Font);
	Label.setCharacterSize(24);
	Label.setFillColor(sf::Color::Black);
	Label.setString("Off");
	InfoLabel.setFont(Font);
	InfoLabel.setCharacterSize(24);
	InfoLabel.setFillColor(sf::Color::Black);
	InfoLabel.setString(i_label);
	if (s == 0) {
		e_mode = Mode::off;
		e_anim = Animation::none;
	}
	else {
		e_mode = Mode::on;
		e_anim = Animation::aOn;
	}
	e_status = Status::idle;
	Outl.setTexture(swOutl);
	Ball.setTexture(swBall);
	Ball.setOrigin(sf::Vector2f(0.f, 0.f));
	Label.setOrigin(sf::Vector2f(((Outl.getLocalBounds().width + 18)) * (-1), 0.f));
	InfoLabel.setOrigin(sf::Vector2f(0.f, Outl.getLocalBounds().height + 14));
	upt();
}

void Switch::upt() {
	if (e_mode == Mode::off) {
		Label.setString("Off");
		Outl.setTexture(swOutl);
		if (e_status == Status::disabled) {
			Outl.setColor(sf::Color(153, 153, 153));
			Ball.setColor(sf::Color(153, 153, 153));
			Label.setFillColor(sf::Color(122, 122, 122));
			InfoLabel.setFillColor(sf::Color(122, 122, 122));
		}
		else {
			Label.setFillColor(sf::Color::Black);
			InfoLabel.setFillColor(sf::Color::Black);
			animate();
			///Ball.setOrigin(sf::Vector2f(0.f, 0.f));
			if (e_status == Status::idle) {
				Outl.setColor(sf::Color(51, 51, 51));
				Ball.setColor(sf::Color(51, 51, 51));
			}
			else if (e_status == Status::hover) {
				Outl.setColor(sf::Color(0, 0, 0));
				Ball.setColor(sf::Color(0, 0, 0));
			}
			else if (e_status == Status::press) {
				Outl.setTexture(swFill);
				Outl.setColor(sf::Color(102, 102, 102));
				Ball.setColor(sf::Color(255, 255, 255));
			}
		}
	}
	else if (e_mode == Mode::on) {
		Label.setString("On");
		Outl.setTexture(swFill);
		if (e_status == Status::disabled) {
			Outl.setColor(sf::Color(204, 204, 204));
			Ball.setColor(sf::Color(163, 163, 163));
			Label.setFillColor(sf::Color(122, 122, 122));
			InfoLabel.setFillColor(sf::Color(122, 122, 122));
		}
		else {
			Label.setFillColor(sf::Color::Black);
			InfoLabel.setFillColor(sf::Color::Black);
			animate();
			//Ball.setOrigin(sf::Vector2f(-36.f, 0.f));
			if (e_status == Status::idle) {
				Outl.setColor(sf::Color(0, 120, 215));
				Ball.setColor(sf::Color(255, 255, 255));
			}
			else if (e_status == Status::hover) {
				Outl.setColor(sf::Color(77, 161, 227));
				Ball.setColor(sf::Color(255, 255, 255));
			}
			else if (e_status == Status::press) {
				Outl.setColor(sf::Color(102, 102, 102));
				Ball.setColor(sf::Color(255, 255, 255));
			}
		}
	}
}

void Switch::animate() {
	if (e_anim == Animation::aOn) {
		// On
		if (bPos > -36.f) {
			bPos -= 6;
			Ball.setOrigin(sf::Vector2f(bPos, 0.f));
			Ball.setPosition(sf::Vector2f(pos.x, pos.y));
			cout << "animate: " << bPos << endl;
		}
		else {
			e_anim = Animation::none;
		}
	}
	else if (e_anim == Animation::aOff) {
		// Off
		if (bPos < 0.f) {
			bPos += 6;
			Ball.setOrigin(sf::Vector2f(bPos, 0.f));
			Ball.setPosition(sf::Vector2f(pos.x, pos.y));
			cout << "animate: " << bPos << endl;
		}
		else {
			e_anim = Animation::none;
		}
	}
}

bool Switch::getDisabled() {
	return e_status == Status::disabled;
}

void Switch::setDisabled(bool value) {
	if (value) {
		e_status = Status::disabled;
	}
	else if (e_status == Status::disabled) {
		e_status = Status::idle;
	}
}

bool Switch::getHidden() {
	return e_status == Status::hidden;
}

void Switch::setHidden(bool value) {
	if (value) {
		e_status = Status::hidden;
	}
	else if (e_status == Status::hidden) {
		e_status = Status::idle;
	}
}

bool Switch::isOn() {
	if (e_mode == Mode::on) {
		return true;
	}
	else if (e_mode == Mode::off) {
		return false;
	}
}

void Switch::setPosition(float newX, float newY) {
	if (i_label != "") {
		newY = newY + 40;
	}
	pos.x = newX;
	pos.y = newY;
	pos2.x = newX + Outl.getLocalBounds().width;
	pos2.y = newY + Outl.getLocalBounds().height;

	Outl.setPosition(sf::Vector2f(newX, newY));
	Ball.setPosition(sf::Vector2f(newX, newY));
	Label.setPosition(sf::Vector2f(newX, newY));
	InfoLabel.setPosition(sf::Vector2f(newX, newY));
}

Vector2 Switch::getPosition() {
	return pos;
}

float Switch::getHeight() {
	return Outl.getLocalBounds().height;
}

float Switch::getWidth() {
	return Outl.getLocalBounds().width;
}

sf::Sprite Switch::getSprite(int x) {
	if (x == 1){
		return Outl;
	}
	else if (x == 2) {
		return Ball;
	}
}

sf::Text Switch::getLabel(int x) {
	if (x == 1) {
		return Label;
	}
	else if (x == 2) {
		return InfoLabel;
	}
}

bool Switch::withinBounds(int coorX, int coorY) {
	if (coorX > pos.x && coorX < pos2.x && coorY > pos.y && coorY < pos2.y && e_status != Status::disabled) {
		if (e_status != Status::press) {
			e_status = Status::hover;
		}
		return true;
	}
	else if (e_status != Status::disabled) {
		if (e_status != Status::press) {
		}
		e_status = Status::idle;
		return false;
	}
	else {
		return false;
	}
}

bool Switch::isPressed(int x) {
	if (e_status == Status::hover && x == 1) {
		e_status = Status::press;
		return true;
	}
	else if (e_status == Status::press && x == 2) {
		e_status = Status::hover;
		if (e_mode == Mode::off) {
			e_mode = Mode::on;
			e_anim = Animation::aOn;
		}
		else {
			e_mode = Mode::off;
			e_anim = Animation::aOff;
		}
		return true;
	}
	else {
		return false;
	}
}