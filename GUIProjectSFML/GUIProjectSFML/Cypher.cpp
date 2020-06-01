#include "Cypher.h"

Cypher::Cypher()
{
	/*
	32 - 47		: Special characters
	48 - 57		: Numbers
	58 - 64		: Special characters
	65 - 90		: Uppercase letters
	91 - 96		: Special Characters
	97 - 122	: Lowercase letters
	123 - 126	: Special characters
	196			: Ä
	197			: Å
	214			: Ö
	228			: ä
	229			: å
	246			: ö
	101

	1 - 27		: Ctrl + Letter
	Ctrl + H	: Backspace (8)
	Ctrl + M	: Enter (13)
	Ctrl + J	: Ctrl + Enter (10)
	*/
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j <= 100; j++) {
			wheel[i][j][0] = ZeroB2C(j + (i * 101), 0);
			wheel[i][j][1] = ZeroB2C(j + (i * 101), 1);
			/// cout << static_cast<char>(wheel[i][j][0]) << static_cast<char>(wheel[i][j][1]) << " : " << wheel[i][j][0] << wheel[i][j][1] << "\t" << ZeroB2C(j + (i * 101), 0) << ZeroB2C(j + (i * 101), 1) << " : " << j << " : " << i << endl;
		}
	}
}

void Cypher::init(bool autoCode) {
	if (autoCode) {
		for (int i = 0; i < 11; i++) {
			code[i] = rand() % 101;
		}
	}
	else {
		for (int i = 0; i < 11; i++) {
			code[i] = 0;
		}
	}
}

int Cypher::ZeroB2C(int i, int c, bool invert) {	// converts an int to it's eqivalent in my character table.
	int j;
	int x;
	int y;
	if (invert) {
		x = c;
		y = i;
	}
	else {
		j = (double)i / 36;
		x = i + 48;
		y = j + 48;
	}
	while (true) {
		if (x <= 57) {
			if (y <= 57) {
				if (invert) {
					x -= 48;
					y -= 48;
					return x + (36 * y);
				}
				else if (c == 0) {
					return y;
				}
				else if (c == 1) {
					return x;
				}
			}
			else {
				if (invert) {
					x -= 48;
					y -= (48 + 7);
					return x + (36 * y);
				}
				else {
					y += 7;
				}
				if (y <= 90) {
					if (c == 0) {
						return y;
					}
					else if (c == 1) {
						return x;
					}
				}
				else {
					cout << "WHEEL OUT OF RANGE" << endl;
					return 48;
				}
			}
		}
		else {
			if (!invert) {
				x += 7;
			}
			if (x <= 90) {
				if (y <= 57) {
					if (invert) {
						x -= (48 + 7);
						y -= 48;
						return x + (36 * y);
					}
					else if (c == 0) {
						return y;
					}
					else if (c == 1) {
						return x;
					}
				}
				else {
					if (!invert) {
						y += 7;
					}
					if (y <= 90) {
						if (invert) {
							x -= (48 + 7);
							y -= (48 + 7);
							return x + (36 * y);
						}
						else if (c == 0) {
							return y;
						}
						else if (c == 1) {
							return x;
						}
					}
					else {
						cout << "WHEEL OUT OF RANGE" << endl;
						return 48;
					}
				}
			}
			else {
				x -= 43;
			}
		}
	}
}

int Cypher::encode(int in) {
	int R = rand() % 11;
	pos = code[R];
	cout << R << " : ";
	if (in >= 32) {
		if (in <= 126) {
			pos += in - 32;
			while (pos > 100) {
				pos -= 101;
			}
			out = wheel[R][pos][0];
			eOut = wheel[R][pos][1];
			cout << pos << endl;
		}
		else if (in == 196 || in == 197) {
			pos += in - 101;
			while (pos > 100) {
				pos -= 101;
			}
			out = wheel[R][pos][0];
			eOut = wheel[R][pos][1];
			cout << pos << endl;

		}
		else if (in == 214) {
			pos += in - 117;
			while (pos > 100) {
				pos -= 101;
			}
			out = wheel[R][pos][0];
			eOut = wheel[R][pos][1];
			cout << pos << endl;

		}
		else if (in == 228 || in == 229) {
			pos += in - 130;
			while (pos > 100) {
				pos -= 101;
			}
			out = wheel[R][pos][0];
			eOut = wheel[R][pos][1];
			cout << pos << endl;

		}
		else if (in == 246) {
			pos += in - 146;
			while (pos > 100) {
				pos -= 101;
			}
			out = wheel[R][pos][0];
			eOut = wheel[R][pos][1];
			cout << pos << endl;

		}
		else {
			out = -1;
			eOut = -1;
		}
	}
	else if (in == 8 || in == 10 || in == 13 || in == 31 || in == 29) {
		out = in;
		eOut = -1;
	}
	else {
		out = -1;
		eOut = -1;
	}
	return out;
}

int Cypher::getLast() {
	return eOut;
}

void Cypher::finish(string output, string fileName) {
	ofstream outFile;
	outFile.open(fileName, ios::out | ios::trunc);
	if (outFile.is_open()) {
		for (int i = 0; i < 11; i++) {
			outFile << code[i];
			if (i < 10) {
				outFile << " : ";
			}
		}
		outFile << endl << output;
		outFile.close();
	}
	else {
		cout << "Failed to open output file" << endl;
	}
}

string Cypher::decode() {
	std::list<int> decoded;
	if (importText != "") {
		int j;
		int k;
		for (int i = 0; i < importText.length(); i++) {
			/// cout << static_cast<char>(importText[i]) << static_cast<char>(importText[i + 1]) << endl;
			if (importText[i] == '\n') {
				decoded.push_back((int)'\n');
			}
			else {
				j = 0;
				k = ZeroB2C((int)importText[i], (int)importText[i + 1], true);
				while (k > 100) {
					k -= 101;
					j++;
				}
				k -= code[j];
				while (k < 0) {
					k += 101;
				}
				k += 32;
				if (k > 126) {
					k += 69;
					if (k > 197) {
						k += 16;
						if (k > 214) {
							k += 13;
							if (k > 229) {
								k += 16;
							}
						}
					}
				}
				decoded.push_back(k);
				cout << static_cast<char>(k) << " : " << code[j] << " : " << j << " : " << static_cast<char>(importText[i]) << static_cast<char>(importText[i + 1]) << endl;
				i++;
			}
		}
		string output;
		for (int n : decoded) {
			output += static_cast<char>(n);
		}
		return output;
	}
}

void Cypher::importFile(string fileName) {
	string line;
	string c;
	importText = "";
	ifstream inFile(fileName);
	if (inFile.is_open()) {
		int i = 1;
		while (getline(inFile, line)) {
			if (i == 1) {
				int k = 0;
				for (int j = 0; j < line.length(); j++) {
					if (line[j] != ':' && line[j] != ' ') {
						c += line[j];
					}
					else if (line[j] != ' ') {
						cout << c << " : " << stoi(c) << endl;
						code[k] = stoi(c);
						c = "";
						k++;
					}
				}
				code[k] = stoi(c);
			}
			else {
				importText += line + '\n';
			}
			i++;
		}
		inFile.close();
	}
	else {
		cout << "Failed to open input file" << endl;
	}
}