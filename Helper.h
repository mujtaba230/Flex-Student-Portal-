#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class Helper
{
public:
	static void initialize(int*& , const int& , ifstream&);
	static char* getNameFromBuffer(char*, char*);
	static int stringLength(char*);
	static void stringCopy(char*& , char*& );
	static int sum(int* , int* , const int& , const int& );
	static void printArray(int* , const int& );
	static void copyNames(char*&, char*&);
	static void copyArray(int*&, int*&, const int&);
	static void copyCharArray(char*, char*);
};
