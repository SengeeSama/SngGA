#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include "Button.h"
#include "Switch.h"
#include "Checkbox.h"
#include "Textbox.h"
#include "Cypher.h"

using namespace std;
int State = 0;

int main() {
	// Create window
	sf::RenderWindow window;
	window.create(sf::VideoMode(600, 800), "Cypher", sf::Style::Titlebar | sf::Style::Close); // Unresizable window with titlebar
	window.setFramerateLimit(60);

	// Create icon
	sf::Image icon;
	icon.loadFromFile("res/icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	// Create element lists
	std::list<Button*> buttons;
	std::list<Switch*> switches;
	std::list<Checkbox*> checkboxes;	
	std::list<Textbox*> textboxes;

	// Create elements
	sf::Sprite Logo;
	sf::Texture LogoTex;
	LogoTex.create(icon.getSize().x, icon.getSize().y);
	LogoTex.update(icon);
	Logo.setTexture(LogoTex);
	Logo.scale(sf::Vector2f(250.f / Logo.getLocalBounds().width, 250.f / Logo.getLocalBounds().height));
	Logo.setPosition(sf::Vector2f(10, 10));

	Button* btn1 = new Button("Encode");
	btn1->setPosition(283.f, 135.f - (btn1->getHeight() / 2));
	buttons.push_back(btn1); // Add element to list

	Button* btn2 = new Button("Decode");
	btn2->setPosition(btn1->getWidth() + 25.5 + btn1->getPosition().x, btn1->getPosition().y);
	buttons.push_back(btn2);

	Switch* sw1 = new Switch("Automatic code generation", 1);
	sw1->setPosition(10.f, 300.f);
	switches.push_back(sw1);
	
	Checkbox* chbox1 = new Checkbox("This does nothing");
	chbox1->setPosition(10.f, 300.f);
	checkboxes.push_back(chbox1);

	Textbox* txbox1 = new Textbox(580.f, 490, "Type your message here...");
	txbox1->setPosition(10.f, 300.f);
	textboxes.push_back(txbox1);

	Cypher* cy = new Cypher();

	while (window.isOpen())
	{
		// Element changes
		if (State == 0) {
			btn1->setHidden(false);
			btn2->setHidden(false);
			sw1->setHidden(false);
			chbox1->setHidden(true);
			txbox1->setHidden(true);
		}
		else if (State == 1) {
			btn1->setHidden(false);
			btn2->setHidden(false);
			sw1->setHidden(true);
			chbox1->setHidden(true);
			txbox1->setHidden(false);
		}
		else if (State == 2) {
			btn1->setHidden(false);
			btn2->setHidden(false);
			sw1->setHidden(true);
			chbox1->setHidden(true);
			txbox1->setHidden(false);
		}

		// Take event
		sf::Event event;
		// Loop to handle event
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { // When close button is pressed
				window.close();
			}
			if (event.type == sf::Event::TextEntered) {
				txbox1->labelUpt(cy->encode(event.text.unicode));
				txbox1->labelUpt(cy->getLast(), event.text.unicode);
				/// txbox1->labelUpt(event.text.unicode);
				cout << event.text.unicode << endl;
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) { // When mouse button 1 is pressed
				// Handle elements
				for (Button* n : buttons) {
					if (!n->getHidden()) {
						n->isPressed();
					}
				}
				for (Switch* n : switches) {
					if (!n->getHidden()) {
						n->isPressed();
					}
				}
				for (Checkbox* n : checkboxes) {
					if (!n->getHidden()) {
						n->isPressed();
					}
				}
				for (Textbox* n : textboxes) {
					if (!n->getHidden()) {
						n->isPressed();
					}
				}

				cout << "Event: Mouse Button Pressed" << endl;
				cout << "X: " << event.mouseButton.x << "\t";
				cout << "Y: " << event.mouseButton.y << endl;
			}
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) { // When mouse button 1 is released
				// Handle elements
				for (Button* n : buttons) {
					if (!n->getHidden()) {
						if (n->isPressed(2)) {
							if (n->getLabel().getString() == "Finish") {
								if (State == 1) {
									cy->finish(txbox1->getLabel().getString(), "Encode_Output.txt");
									txbox1->reset();
								}
								else if (State == 2) {
									cy->finish(cy->decode(), "Decode_Output.txt");
								}
							}
							if (n->getLabel().getString() == "Encode") {
								n->setLabel("Finish");
								btn2->setLabel("Return");
								cy->init(sw1->isOn());
								State = 1;
							}
							else if (n->getLabel().getString() == "Decode") {
								n->setLabel("Return");
								btn1->setLabel("Finish");
								txbox1->reset();
								cy->importFile();
								txbox1->setLabel(cy->decode(), false);
								cout << cy->decode() << endl;
								State = 2;
							}
							else if (n->getLabel().getString() == "Return") {
								if (State == 1 || State == 2) {
									n->setLabel("Decode");
									btn1->setLabel("Encode");
									txbox1->reset();
									State = 0;
								}
							}
						}
					}
				}
				for (Switch* n : switches) {
					if (!n->getHidden()) {
						n->isPressed(2);
					}
				}
				for (Checkbox* n : checkboxes) {
					if (!n->getHidden()) {
						n->isPressed(2);
					}
				}
				for (Textbox* n : textboxes) {
					if (!n->getHidden()) {
						n->isPressed(2);
					}
				}

				cout << "Event: Mouse Button Released" << endl;
				cout << "X: " << event.mouseButton.x << "\t";
				cout << "Y: " << event.mouseButton.y << endl;
			}
			if (event.type == sf::Event::MouseMoved) { // When mouse is moved
				// Handle elements
				for (Button* n : buttons) {
					if (!n->getHidden()) {
						n->withinBounds(event.mouseMove.x, event.mouseMove.y);
					}
				}
				for (Switch* n : switches) {
					if (!n->getHidden()) {
						n->withinBounds(event.mouseMove.x, event.mouseMove.y);
					}
				}
				for (Checkbox* n : checkboxes) {
					if (!n->getHidden()) {
						n->withinBounds(event.mouseMove.x, event.mouseMove.y);
					}
				}
				for (Textbox* n : textboxes) {
					if (!n->getHidden()) {
						n->withinBounds(event.mouseMove.x, event.mouseMove.y);
					}
				}
			}

		}

		window.clear(sf::Color::White);

		// Update elements & Draw everything

		for (Button* n : buttons) {
			n->upt();
			if (!n->getHidden()) {
				for (int i = 1; i < 5; i++) {
					window.draw(n->getSprite(i));
				}
				window.draw(n->getLabel());
			}
		}
		for (Switch* n : switches) {
			n->upt();
			if (!n->getHidden()) {
				for (int i = 1; i < 3; i++) {
					window.draw(n->getSprite(i));
					window.draw(n->getLabel(i));
				}
			}
		}
		for (Checkbox* n : checkboxes) {
			n->upt();
			if (!n->getHidden()) {
				for (int i = 1; i < 4; i++) {
					window.draw(n->getSprite(i));
				}
				window.draw(n->getLabel());
			}
		}
		for (Textbox* n : textboxes) {
			n->upt();
			if (!n->getHidden()) {
				for (int i = 1; i < 7; i++) {
					window.draw(n->getSprite(i));
				}
				window.draw(n->getLabel());
				window.draw(n->getTmpLabel());
			}
		}
		window.draw(Logo);

		window.display();
	}

	//Reset the reserved ram and set the address pointer to NULL
	for (Button* n : buttons) {
		delete(n);
		n = NULL;
	}
	for (Switch* n : switches) {
		n = NULL;
	}
	for (Checkbox* n : checkboxes) {
		n = NULL;
	}
	for (Textbox* n : textboxes) {
		n = NULL;
	}

	return 0;
}