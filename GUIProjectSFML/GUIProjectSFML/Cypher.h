#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

class Cypher {
private:
	int pos;
	int out;
	int eOut;
	bool autoCode;
	int code[11];
	int wheel[11][101][2];
	string importText;
public:
	Cypher();
	int ZeroB2C(int i, int c, bool invert = false);
	void init(bool auto_code = true);
	int encode(int in);
	int getLast();
	void finish(string output, string fileName);
	string decode();
	void importFile(string fileName = "Encode_Output.txt");
};