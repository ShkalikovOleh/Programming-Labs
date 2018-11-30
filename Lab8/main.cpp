#include <iostream>
#include <fstream>
#include "LinkedText.h"

using namespace std;

int main() {
	std::fstream file;
	file.open("text.txt", std::fstream::in | std::fstream::out);

	LinkedText text;	
	text.AddLine("Linerg#rgfghgs 1");
	text.Write(cout);
	cout << endl;

	text.AddLine("Liine 2");
	text.Write(cout);
	cout << endl;

	text.AddLine("Liine 3");
	text.Write(cout);
	cout << endl;

	text.CopyLine(2, 1);
	text.Write(cout);
	cout << endl;

	text.CopyLine(2, 1);
	text.Write(cout);
	cout << endl;

	text.RemoveLine(3);
	text.Write(cout);
	cout << endl;

	text.SetName("Test text");	
	text.Write(file);

	cout << "Text name: " << text.GetName() << endl;
	text.Write(cout);

	LinkedText text2;	
	text2.Load(file);	
	cout << "Text2 name: " << text2.GetName() << endl;
	text2.Write(cout);	

	number i = 0, j = 0;
	text2.FindLetter('Z', i, j);
	cout << "First contains of letter Z" << endl << "Row " << i << " Column " << j << endl;
	
	cout << "Row which contains maximum count letter Z " << text2.GetLineWithMaxLetterContains('i') << endl;

	system("pause");
	return 0;
}