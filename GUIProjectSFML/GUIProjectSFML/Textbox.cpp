#include "Textbox.h"

//asign the local variable i_label with the param iLabel etc...
Textbox::Textbox(float width, float height, string iLabel) : sizeX(width), sizeY(height), i_label(iLabel)
{
	//What is going on when we create the button this is your "Create() method"
	cout << "Creating Textbox..." << endl;
	if (false) {
		txboxFill.loadFromFile("btn_mask.png");
		txboxOutlR.loadFromFile("btn_outl_r.png");
		txboxOutlE.loadFromFile("btn_outl_e.png");
		txboxCursor.loadFromFile("txbox_cursor.png");
		Font.loadFromFile("arial.ttf");
	}
	else {
		txboxFill.loadFromFile("res/btn_mask.png");
		txboxOutlR.loadFromFile("res/btn_outl_r.png");
		txboxOutlE.loadFromFile("res/btn_outl_e.png");
		txboxCursor.loadFromFile("res/txbox_cursor.png");
		Font.loadFromFile("res/arial.ttf");
	}
	fSize = 24;
	labelRows = 0;
	Label.setFont(Font);
	Label.setCharacterSize(fSize);
	Label.setFillColor(sf::Color(102, 102, 102));

	/// i_label += static_cast<char>(0);
	/*
	i_label = "";
	for (int i = 32; i <= 64; i++) {
		i_label += static_cast<char>(i);
	}
	*/

	Label.setString(i_label);
	tmpLabel.setFont(Font);
	tmpLabel.setCharacterSize(fSize);
	tmpLabel.setFillColor(sf::Color(102, 102, 102));

	cLabel.setFont(Font);
	cLabel.setCharacterSize(fSize);
	cLabel.setFillColor(sf::Color(102, 102, 102));
	/// cout << Label.getLocalBounds().width << endl << Label.getLocalBounds().height << endl;

	OutlR1.setTexture(txboxOutlR);
	OutlR2.setTexture(txboxOutlR);
	OutlE1.setTexture(txboxOutlE);
	OutlE2.setTexture(txboxOutlE);
	Cursor.setTexture(txboxCursor);
	Fill.setTexture(txboxFill);

	Fill.setColor(sf::Color(255, 255, 255));
	OutlR1.setColor(sf::Color(153, 153, 153));
	OutlR2.setColor(sf::Color(153, 153, 153));
	OutlE1.setColor(sf::Color(153, 153, 153));
	OutlE2.setColor(sf::Color(153, 153, 153));
	Cursor.setColor(sf::Color::White);

	Fill.setScale(sf::Vector2f(sizeX / 48.f, sizeY / 48.f));
	OutlR1.setScale(sf::Vector2f(sizeX / 48.f, 1));
	OutlR2.setScale(sf::Vector2f(sizeX / 48.f, 1));
	OutlE1.setScale(sf::Vector2f(1, sizeY / 48.f));
	OutlE2.setScale(sf::Vector2f(1, sizeY / 48.f));

	/*
	if (Label.getLocalBounds().width * 1.25 >= sizeX) {
		for (int i = 1; i < t_label.getSize(); i++) {
			if (t_label[t_label.getSize() - i] == ' ') {
				t_label.replace(t_label.getSize() - i, 1, "\n");
				break;
			}
			else if (i == t_label.getSize()) {
				t_label += "\n";
			}
		}
	}
	*/

	e_mode = Mode::off;

	cout << "Width: " << Fill.getLocalBounds().width * Fill.getScale().x << endl;
	cout << "Scale X: " << Fill.getScale().x << endl;

	upt();
	Label.setOrigin(sf::Vector2f(-18.f , -8.f));
	tmpLabel.setOrigin(sf::Vector2f(-18.f, 30.f));
	cLabel.setOrigin(sf::Vector2f(-18.f, 30.f));
	Cursor.setOrigin(sf::Vector2f(-18.f, -8.f));
	Cursor.setPosition(sf::Vector2f(pos.x, pos.y));
}

void Textbox::upt() {
	if (Label.getLocalBounds().width >= pos2.x - pos.x - 48) {
		if (fSize > 10) {
			fSize -= 2;
		}
	}
	else if (Label.getLocalBounds().width <= pos2.x - pos.x - (48 * 3)) {
		if (fSize < 24) {
			fSize += 2;
		}
	}
	tmpLabel.setCharacterSize(fSize);
	Label.setCharacterSize(fSize);
	Fill.setScale(sf::Vector2f(sizeX / 48.f, sizeY / 48.f));
	OutlR1.setScale(sf::Vector2f(sizeX / 48.f, 1));
	OutlR2.setScale(sf::Vector2f(sizeX / 48.f, 1));
	OutlE1.setScale(sf::Vector2f(1, sizeY / 48.f));
	OutlE2.setScale(sf::Vector2f(1, sizeY / 48.f));
	OutlR1.setPosition(sf::Vector2f(pos.x, pos.y));
	OutlR2.setPosition(sf::Vector2f(pos.x, pos.y + (Fill.getLocalBounds().height * Fill.getScale().y) - 3));
	OutlE1.setPosition(sf::Vector2f(pos.x, pos.y));
	OutlE2.setPosition(sf::Vector2f(pos.x + (Fill.getLocalBounds().width * Fill.getScale().x) - 3, pos.y));
	Cursor.setScale(sf::Vector2f(1, (fSize + fSize / 7.f) / 24));
	Cursor.setOrigin(sf::Vector2f(-18.f, -8.f - (15 * ((Cursor.getScale().y - 1) * (-1)))));
	Cursor.setPosition(sf::Vector2f(pos.x + tmpLabel.getLocalBounds().width, pos.y + ((fSize + fSize / 5.f) * labelRows)));
	setPosition(pos.x, pos.y);

	if (e_mode == Mode::off) {
		Label.setFillColor(sf::Color(102, 102, 102));
		Cursor.setColor(sf::Color::White);

		if (e_status == Status::idle) {
			OutlR1.setColor(sf::Color(153, 153, 153));
			OutlR2.setColor(sf::Color(153, 153, 153));
			OutlE1.setColor(sf::Color(153, 153, 153));
			OutlE2.setColor(sf::Color(153, 153, 153));
		}
		else if (e_status == Status::hover) {
			OutlR1.setColor(sf::Color(102, 102, 102));
			OutlR2.setColor(sf::Color(102, 102, 102));
			OutlE1.setColor(sf::Color(102, 102, 102));
			OutlE2.setColor(sf::Color(102, 102, 102));
		}
		else if (e_status == Status::press) {
			Label.setFillColor(sf::Color(153, 153, 153));
			OutlR1.setColor(sf::Color(0, 120, 215));
			OutlR2.setColor(sf::Color(0, 120, 215));
			OutlE1.setColor(sf::Color(0, 120, 215));
			OutlE2.setColor(sf::Color(0, 120, 215));
		}
	}
	else {
		if (Label.getString() == i_label) {
			Label.setFillColor(sf::Color(153, 153, 153));
		}
		else {
			Label.setFillColor(sf::Color::Black);
		}
		OutlR1.setColor(sf::Color(0, 120, 215));
		OutlR2.setColor(sf::Color(0, 120, 215));
		OutlE1.setColor(sf::Color(0, 120, 215));
		OutlE2.setColor(sf::Color(0, 120, 215));
		Cursor.setColor(sf::Color::Black);

		if (e_status == Status::idle) {
		}
		else if (e_status == Status::hover) {
		}
		else if (e_status == Status::press) {
		}
	}
}

void Textbox::labelUpt(int c, int c2) {
	/*
	1 - 27		: Ctrl + Letter
	Ctrl + H	: Backspace (8)
	Ctrl + M	: Enter (13)
	Ctrl + J	: Ctrl + Enter (10)
	127			: Ctrl + Backspace
	*/

	if (Cursor.getPosition().x >= pos2.x - 48 && Cursor.getPosition().y < pos2.y - 48 && fSize <= 10) {
		for (int i = 1; i < tmp_label.getSize(); i++) {
			if (tmp_label[tmp_label.getSize() - i] == ' ') {
				t_label.replace(t_label.getSize() - i, 1, "\n");
				for (int l = 0; l <= t_label.getSize() - i; l++) {
					tmp_label.replace(tmp_label.getSize() - i, 1, "");
				}
				labelRows += 1;
				break;
			}
			else if (i == tmp_label.getSize() - 1 && c != 8 && c2 != 8) {
				t_label += "\n";
				tmp_label = "";
				ct_label += "\n";
				c_label = "";
				labelRows += 1;
				cout << "Insert Enter" << endl;
				break;
			}
		}
	}
	if (e_mode == Mode::on && c != -1) {
		if (c < 128 || c == 246 || c == 229 || c == 228 || c == 197 || c == 196 || c == 214) {
			if (c == 8) {
				Backspace(c);
			}
			else if (c == 127) {
				Backspace(c, 4);
			}
			else if (c == 13) {
				if (Cursor.getPosition().y < pos2.y - 48 && Cursor.getPosition().x < pos2.x - 48) {
					t_label += "\n";
					tmp_label = "";
					ct_label += "\n";
					c_label = "";
					labelRows += 1;
				}
			}
			else if (Cursor.getPosition().x < pos2.x - 48 || Cursor.getPosition().y < pos2.y - 48) {
				if (c != 31 && c != 29 && c != 10) {
					t_label += static_cast<char>(c);
					tmp_label += static_cast<char>(c);
				}
				if (c2 != -1) {
					c_label += static_cast<char>(c2);
					ct_label += static_cast<char>(c2);
				}
				else if (c == 31) {
					if (fSize > 4) {
						fSize -= 2;
					}
				}
				else if (c == 29) {
					if (fSize < 48) {
						fSize += 2;
					}
				}
			}
			Label.setString(t_label);
			tmpLabel.setString(tmp_label);
			cLabel.setString(c_label);
		}
	}
	else if (e_mode == Mode::on && c2 == 8) {
		if (ct_label.getSize() > 0) {
			if (ct_label[ct_label.getSize() - 1] != '\n') {
				Backspace(c);
			}
		}
		BackspaceC();
		cLabel.setString(c_label);
	}
	Cursor.setPosition(sf::Vector2f(pos.x + tmpLabel.getLocalBounds().width, pos.y + ((fSize + fSize / 7.f) * labelRows)));
	/// cout << "Label Rows: " << labelRows << endl;
	/// cout << c << endl << "tmp_label.size: " << tmp_label.getSize() << endl << "t_label.size: " << t_label.getSize() << endl;
}
void Textbox::Backspace(int c, int x) {
	for (int i = 1; i <= x; i++) {
		if (t_label.getSize() > 0) {
			if (tmp_label.getSize() > 0) {
				tmp_label.erase(tmp_label.getSize() - 1, 1);
			}
			else {
				tmp_label = t_label;
				for (int i = 2; i <= t_label.getSize(); i++) {
					if (t_label[t_label.getSize() - i] == '\n') {
						for (int l = 0; l <= t_label.getSize() - i; l++) {
							tmp_label.replace(tmp_label.getSize() - i, 1, "");
						}
						labelRows -= 1;
						tmp_label.erase(tmp_label.getSize() - 1, 1);
						break;
					}
					else if (i == t_label.getSize()) {
						labelRows -= 1;
						tmp_label.erase(tmp_label.getSize() - 1, 1);
						break;
					}
				}
				if (tmp_label.getSize() > 0) {
					if (tmp_label[tmp_label.getSize() - 1] == '\n' && t_label.getSize() < 2) {
						labelRows -= 1;
						tmp_label.erase(tmp_label.getSize() - 1, 1);
					}
				}
			}
			t_label.erase(t_label.getSize() - 1, 1);
		}
		Label.setString(t_label);
		tmpLabel.setString(tmp_label);
	}
}

void Textbox::BackspaceC() {
	if (ct_label.getSize() > 0) {
		if (c_label.getSize() > 0) {
			c_label.erase(c_label.getSize() - 1, 1);
		}
		else {
			c_label = ct_label;
			for (int i = 2; i <= ct_label.getSize(); i++) {
				if (ct_label[ct_label.getSize() - i] == '\n') {
					for (int l = 0; l <= ct_label.getSize() - i; l++) {
						c_label.replace(c_label.getSize() - i, 1, "");
					}
					c_label.erase(c_label.getSize() - 1, 1);
					break;
				}
				else if (i == ct_label.getSize()) {
					c_label.erase(c_label.getSize() - 1, 1);
					break;
				}
			}
			if (c_label.getSize() > 0) {
				if (c_label[c_label.getSize() - 1] == '\n' && ct_label.getSize() < 2) {
					c_label.erase(c_label.getSize() - 1, 1);
				}
			}
		}
		ct_label.erase(ct_label.getSize() - 1, 1);
	}
	cLabel.setString(c_label);
}

bool Textbox::isOn() {
	return e_mode == Mode::on;
}

bool Textbox::getHidden() {
	return e_status == Status::hidden;
}

void Textbox::setHidden(bool value) {
	if (value) {
		e_status = Status::hidden;
	}
	else if (e_status == Status::hidden) {
		e_status = Status::idle;
	}
}

void Textbox::setPosition(float newX, float newY) {
	pos.x = newX;
	pos.y = newY;
	pos2.x = newX + (Fill.getLocalBounds().width * Fill.getScale().x);
	pos2.y = newY + (Fill.getLocalBounds().height * Fill.getScale().y);
	Fill.setPosition(sf::Vector2f(newX, newY));
	Label.setPosition(sf::Vector2f(newX, newY));
	tmpLabel.setPosition(sf::Vector2f(newX, newY));
	cLabel.setPosition(sf::Vector2f(newX, newY));
}

Vector2 Textbox::getPosition() {
	return pos;
}

float Textbox::getHeight() {
	return Fill.getLocalBounds().height * Fill.getScale().y;
}

float Textbox::getWidth() {
	return Fill.getLocalBounds().width * Fill.getScale().x;
}

sf::Sprite Textbox::getSprite(int x) {
	if (x == 1) {
		return Fill;
	}
	else if (x == 2) {
		return OutlR1;
	}
	else if (x == 3) {
		return OutlR2;
	}
	else if (x == 4) {
		return OutlE1;
	}
	else if (x == 5) {
		return OutlE2;
	}
	else if (x == 6) {
		return Cursor;
	}
}

sf::Text Textbox::getLabel() {
	return Label;
}

sf::Text Textbox::getTmpLabel() {
	return cLabel;
}

void Textbox::setLabel(string newLabel, bool ghostText) {
	t_label = newLabel;
	tmp_label = newLabel;
	ct_label = newLabel;
	c_label = newLabel;
	Label.setString(t_label);
	tmpLabel.setString(tmp_label);
	if (ghostText) {
		cLabel.setString(c_label);
	}
	else {
		cLabel.setString("");
	}
	labelRows = 0;
}

void Textbox::reset() {
	setLabel("");
	isPressed();
	labelUpt(-1);
	fSize = 24;
}

bool Textbox::withinBounds(int coorX, int coorY) {
	if (coorX > pos.x && coorX < pos2.x && coorY > pos.y && coorY < pos2.y) {
		if (e_status != Status::press) {
			e_status = Status::hover;
		}
		return true;
	}
	else if (e_status != Status::press) {
		e_status = Status::idle;
		return false;
	}
	else {
		return false;
	}
}

bool Textbox::isPressed(int x) {
	if (e_status == Status::hover && x == 1) {
		if (t_label != "") {
			Label.setString(t_label);
		}
		else {
			Label.setString(i_label);
		}
		e_mode = Mode::on;
		e_status = Status::press;
		return true;
	}
	else if (e_status == Status::press && x == 2) {
		e_status = Status::hover;
		return true;
	}
	else {
		if (e_status != Status::hover && x == 1) {
			if (t_label != "") {
				Label.setString(t_label);
			}
			else {
				Label.setString(i_label);
			}
			if (e_mode != Mode::off) {
				e_mode = Mode::off;
			}
		}
		return false;
	}
}