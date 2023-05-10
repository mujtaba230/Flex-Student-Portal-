#include"Helper.h"

//Helper class functions

void Helper::initialize(int*& array, const int& size, ifstream& fin)
{
	//populates the array with data from file
	for (int i = 0; i < size; i++) 
	{
		fin >> array[i];
	}
}

char* Helper::getNameFromBuffer(char* fName, char* lName)
{
	char* name = new char[stringLength(fName) + stringLength(lName) + 2];
	int i;

	//Saves first name
	for (i = 0; i < stringLength(fName); i++) 
	{
		name[i] = fName[i];
	}
	name[i] = ' ';
	i++;

	//Saves last name
	for (int j = 0; i < (stringLength(fName) + stringLength(lName) + 1); j++, i++)
	{
		name[i] = lName[j];
	}

	name[i] = '\0';			//null character at last index

	return name;

}

int Helper::stringLength(char* str)
{
	int len;
	for (len = 0; str[len] != '\0'; len++);

	return len;
}

void Helper::stringCopy(char*& dest, char*& src)
{
	int i;
	for (i = 0; i < stringLength(src); i++) 
	{
		dest[i] = src[i];
	}

	dest[i] = '\0';
}

int Helper::sum(int* array1, int* array2, const int& size1, const int& size2)
{
	int total = 0;

	for (int i = 0; i < size1; i++) 
	{
		total += array1[i];
	}
	for (int i = 0; i < size2; i++) 
	{
		total += array2[i];
	}

	return total;

}

void Helper::printArray(int* array, const int& size)
{
	for (int i = 0; i < size; i++) 
	{
		cout << array[i] << "\t";
	}
}

void Helper::copyArray(int*& dest, int*& src, const int& size)
{
	dest = new int[size];
	for (int i = 0; i < size; i++) 
	{
		dest[i] = src[i];
	}

}

void Helper::copyCharArray(char* dest, char* src)
{
	int i;
	for (i = 0; i < stringLength(src); i++) 
	{
		dest[i] = src[i];
	}

	dest[i] = '\0';

}

void Helper::copyNames(char*& dest, char*& src)
{
	dest = new char[stringLength(src) + 1];

	stringCopy(dest, src);

}
