#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Button.h"
#include "Switch.h"
#include "Checkbox.h"

using namespace std;

int main() {
	// Create window
	sf::RenderWindow window;
	window.create(sf::VideoMode(600, 800), "Test", sf::Style::Titlebar | sf::Style::Close); // Unresizable window with titlebar
	window.setFramerateLimit(60);

	// Create element lists
	std::list<Button*> buttons;
	std::list<Switch*> switches;
	std::list<Checkbox*> checkboxes;

	// Create elements
	// Set the pointer of the new Button in the ram
	Button* btn1 = new Button("Useless Fuck"); // Create and set label of element button/btn1 to "Actionless"

	// Position X explaination: 300 is center of window (x). Subtract 300 by button width divided by 2 for the center of button to match with center of window.
	// Position Y explaination: A Button is 48 pixels in height, A Switch with no label is 30, and the label itself is 40. (48 - 30) / 2 gives the radius difference between 2 circles, 1 with same diameter as height of switch and 1 as height of button. Subtracting this from 40 brings the button center to same height of switch center (subtract another 40 if switch has no label). Add 10 because switch draw position (y) is 10
	btn1->setPosition(300.f - (btn1->getWidth() / 2), 41.f);
	buttons.push_back(btn1); // Add element to list

	Button* btn2 = new Button("Unwork");
	btn2->setPosition(300.f - (btn2->getWidth() / 2), 141.f); // Adding 100 to y position gives a nice space between elements
	btn2->setDisabled(true); // Make this element uninterractable
	buttons.push_back(btn2);

	Switch* sw1 = new Switch("Do jack shit");
	sw1->setPosition(20.f, 10.f); // Switch element has a height of 70 pixels (30 with no label). 30 empty pixels underneeth before next element brings a nicer look. Total height per element adds up to 100 for easy head calculation
	switches.push_back(sw1);

	Switch* sw2 = new Switch("This bitch disabled");
	sw2->setPosition(20.f, 110.f); // 100 pixels below previous element to fullfill the criteria for 'a nicer look'
	sw2->setDisabled(true);
	switches.push_back(sw2);
	
	Checkbox* chbox1 = new Checkbox("This does fuck all");
	chbox1->setPosition(20.f, 250.f); // Add 40 to y position because checkbox element has no label on top as the switch does. Therefor keeping the space between the clickable elements themselves the same.
	checkboxes.push_back(chbox1);

	// Det är roligt med knappar
	Button* btnD = new Button("Det", "", "", false);
	btnD->setPosition(17.f, 783.f - btnD->getHeight());
	btnD->setHidden(true);
	buttons.push_back(btnD);

	Button* btnÄ = new Button("Är", "", "", false);
	btnÄ->setPosition(btnD->getWidth() + 25.f + btnD->getPosition().x, 783.f - btnÄ->getHeight());
	btnÄ->setHidden(true);
	buttons.push_back(btnÄ);

	Button* btnR = new Button("Roligt", "", "", false);
	btnR->setPosition(btnÄ->getWidth() + 25.f + btnÄ->getPosition().x, 783.f - btnR->getHeight());
	btnR->setHidden(true);
	buttons.push_back(btnR);

	Button* btnM = new Button("Med", "", "", false);
	btnM->setPosition(btnR->getWidth() + 25.f + btnR->getPosition().x, 783.f - btnM->getHeight());
	btnM->setHidden(true);
	buttons.push_back(btnM);

	Button* btnK = new Button("Knappar", "", "", false);
	btnK->setPosition(btnM->getWidth() + 25.f + btnM->getPosition().x, 783.f - btnK->getHeight());
	btnK->setHidden(true);
	buttons.push_back(btnK);

	while (window.isOpen())
	{
		// Element changes
		if (sw1->isOn()) {
			btn2->setDisabled(false);
			sw2->setDisabled(false);
		}
		else {
			btn2->setDisabled(true);
			sw2->setDisabled(true);
		}

		if (chbox1->isOn()) {
			btnD->setHidden(false);
			btnÄ->setHidden(false);
			btnR->setHidden(false);
			btnM->setHidden(false);
			btnK->setHidden(false);
		}
		else {
			btnD->setHidden(true);
			btnÄ->setHidden(true);
			btnR->setHidden(true);
			btnM->setHidden(true);
			btnK->setHidden(true);
		}

		// Take event
		sf::Event event;
		// Loop to handle event
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { // When close button is pressed
				window.close();
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

				cout << "Event: Mouse Button Pressed" << endl;
				cout << "X: " << event.mouseButton.x << "\t";
				cout << "Y: " << event.mouseButton.y << endl;
			}
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) { // When mouse button 1 is released
				// Handle elements
				for (Button* n : buttons) {
					if (!n->getHidden()) {
						n->isPressed(2);
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

				if (btn1->isPressed(2) == true) {
					// Code executed when this button has been pressed
					cout << "Button 1 was pressed" << endl;
				}
				if (btn2->isPressed(2) == true) {
					// Code executed when this button has been pressed
					cout << "Button 2 was pressed" << endl;
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
			}

		}

		// Update elements
		chbox1->upt();

		// Draw everything

		window.clear(sf::Color::White);

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

	return 0;
}