#include"StudentPortal.h"

//studentReport class functions

studentReport::studentReport()
{
	name = 0;
	quizMarks = assignmentMarks = 0;
	total = 0;

	numberOfStudents++;			//each time constructor is called number of students rises

}

void studentReport::readDataFromFile(ifstream& fin)
{
	char temp1[80], temp2[80];

	quizMarks = new int[numberOfQuizes];

	assignmentMarks = new int[numberOfAssignments];


	fin >> rollNo;
	fin >> temp1;
	fin >> temp2;

	name = Helper::getNameFromBuffer(temp1, temp2);

	Helper::initialize(quizMarks, numberOfQuizes, fin);
	Helper::initialize(assignmentMarks, numberOfQuizes, fin);

	total = Helper::sum(quizMarks, assignmentMarks, numberOfQuizes, numberOfAssignments);
}

void studentReport::printList()
{
	cout << rollNo << "\t" << name << "\t\t";
	Helper::printArray(quizMarks, numberOfQuizes);
	Helper::printArray(assignmentMarks, numberOfAssignments);
	cout << total << endl;
}

int studentReport::getTotalStudents()
{
	return numberOfStudents;
}

int* studentReport::getTotalQuizMarks()
{
	return totalQuizMarks;
}

int* studentReport::getTotalAssignmentMarks()
{
	return totalAssignmentMarks;
}

void studentReport::setNumberOfQuizes(int n)
{
	numberOfQuizes = n;

}

void studentReport::setNumberOfAssignments(int n)
{
	numberOfAssignments = n;

}

void studentReport::setTotalQuizMarks(int* n, int size)
{
	totalQuizMarks = new int[size];

	for (int i = 0; i < size; i++) 
	{
		totalQuizMarks[i] = n[i];
	}

}

void studentReport::setTotalAssignmentMarks(int* n, int size)
{
	totalAssignmentMarks = new int[size];

	for (int i = 0; i < size; i++) 
	{
		totalAssignmentMarks[i] = n[i];
	}

}

void studentReport::setTotal(int n)
{
	maxTotal = n;

}

int studentReport::getTotal()
{
	return total;
}

char* studentReport::getRollNo()
{
	return rollNo;
}

int studentReport::getNumberOfQuizzes()
{
	return numberOfQuizes;
}

int studentReport::getNumberOfAssignments()
{
	return numberOfAssignments;
}

studentReport& studentReport::operator=(studentReport& student)
{
	//Assignment operator
	if (student.rollNo != this->rollNo)
	{
		Helper::copyCharArray(rollNo, student.rollNo);

		Helper::copyNames(name, student.name);

		Helper::copyArray(quizMarks, student.quizMarks, numberOfQuizes);

		Helper::copyArray(assignmentMarks, student.assignmentMarks, numberOfAssignments);

		total = student.total;
	}

	return *this;
}

studentReport::studentReport(studentReport& student)
{
	//Copy constructor

	Helper::copyCharArray(rollNo, student.rollNo);

	Helper::copyNames(name, student.name);

	Helper::copyArray(quizMarks, student.quizMarks, numberOfQuizes);

	Helper::copyArray(assignmentMarks, student.assignmentMarks, numberOfAssignments);

	total = student.total;
}

void studentReport::print()
{
	cout << rollNo << "\t" << name << "\t";
	Helper::printArray(quizMarks, numberOfQuizes);
	Helper::printArray(assignmentMarks, numberOfAssignments);
	cout << total << endl;
}

void studentReport::printDetail()
{
	cout << "Roll No:\t" << rollNo << endl;
	cout << "Name:\t\t" << name << endl;
	cout << "Quizzes Marks:\n";

	for (int i = 0; i < numberOfQuizes; i++) 
	{
		cout << "\t\tQ1:\t" << quizMarks[i] << "/" << totalQuizMarks[i] << endl;
	}

	cout << "Assignment Marks:\n";

	for (int i = 0; i < numberOfAssignments; i++) 
	{
		cout << "\t\tQ1:\t" << assignmentMarks[i] << "/" << totalAssignmentMarks[i] << endl;
	}

	cout << "Total: \t\t" << total << "/" << maxTotal;

}

studentReport::~studentReport()
{
	delete name;
	delete quizMarks;
	delete assignmentMarks;

	name = 0;
	quizMarks = assignmentMarks = 0;
	numberOfStudents--;
}

//Normal Fuctions

studentReport* getDataFromFile(const char* fileName)
{
	ifstream fin;
	fin.open(fileName);			//opens file gradesheet.txt
	if (fin.is_open()) 
	{
		int totalStudents;
		fin >> totalStudents;

		int totalQuizes, totalAssignments;
		fin >> totalQuizes;
		fin >> totalAssignments;

		studentReport::setNumberOfQuizes(totalQuizes);
		studentReport::setNumberOfAssignments(totalAssignments);

		int* totalMarksQuizes = new int[totalQuizes];
		int* totalMarksAssignments = new int[totalAssignments];

		Helper::initialize(totalMarksQuizes, totalQuizes, fin);
		Helper::initialize(totalMarksAssignments, totalAssignments, fin);

		studentReport::setTotalQuizMarks(totalMarksQuizes, totalQuizes);
		studentReport::setTotalAssignmentMarks(totalMarksAssignments, totalAssignments);

		int total = Helper::sum(totalMarksQuizes, totalMarksAssignments, totalQuizes, totalAssignments);
		studentReport::setTotal(total);

		studentReport* studentList = new studentReport[totalStudents];

		for (int i = 0; !fin.eof(); i++) 
		{
			studentList[i].readDataFromFile(fin);
		}

		deAllocate(totalMarksQuizes);
		deAllocate(totalMarksAssignments);

		fin.close();			// closes file gradesheet.txt
		return studentList;
	}
	else 
	{
		fin.close();
		return 0;
	}
}

bool findRollNo(const char* RollNo, studentReport* list, int totalStudents, int& index)
{
	bool found = false;

	for (int i = 0; i < totalStudents; i++) 
	{
		if (!found) 
		{
			for (int j = 0; j < 9; j++) 
			{
				char* temp = list[i].getRollNo();		//saves roll no in an array
				if (RollNo[j] == temp[j]) 
				{			//compares the roll no to be found with every roll no
					found = true;
				}
				else 
				{
					found = false;
					break;
				}
			}
		}
		else 
		{
			break;
		}
		index = i;				// saves the index of roll no where it is found
	}

	return found;
}

int* maxQuizMarks(studentReport* list, int totalStudents)
{
	int quizes = list[0].numberOfQuizes;
	int* max = new int[quizes];

	for (int i = 0; i < quizes; i++) 
	{
		max[i] = 0;
	}

	for (int i = 0; i < quizes; i++) 
	{
		for (int j = 0; j < totalStudents - 1; j++) 
		{
			if (list[j].quizMarks[i] > max[i]) 			//compares max with every index of each quiz
			{											
				max[i] = list[j].quizMarks[i];			//saves if marks are greater than max
			}
		}
	}

	return max;

}

int* maxAssignmentMarks(studentReport* list, int totalStudents)
{
	int assignments = list[0].numberOfAssignments;
	int* max = new int[assignments];

	for (int i = 0; i < assignments; i++) 
	{
		max[i] = 0;
	}

	for (int i = 0; i < assignments; i++) 
	{
		for (int j = 0; j < totalStudents; j++) 
		{
			if (list[j].assignmentMarks[i] > max[i])		//compares max with every index of assignment marks 
			{		
				max[i] = list[j].assignmentMarks[i];		//saves markss in max if they are greater	
			}
		}
	}

	return max;

}

int* minQuizMarks(studentReport* list, int totalStudents)
{
	int quizes = list[0].numberOfQuizes;
	int* min = new int[quizes];

	for (int i = 0; i < quizes; i++) 
	{
		min[i] = 0;
	}

	for (int i = 0; i < quizes; i++) 
	{
		for (int j = 0; j < totalStudents - 1; j++) 
		{
			if (list[j].quizMarks[i] < min[i]) 		//compares min with every index of quiz marks
			{
				min[i] = list[j].quizMarks[i];			//saves marks in min if they are less
			}
		}
	}

	return min;

}

int* minAssignmentMarks(studentReport* list, int totalStudents)
{
	int assignments = list[0].numberOfAssignments;
	int* min = new int[assignments];

	for (int i = 0; i < assignments; i++) 
	{
		min[i] = 0;
	}

	for (int i = 0; i < assignments; i++) 
	{
		for (int j = 0; j < totalStudents; j++) 
		{
			if (list[j].assignmentMarks[i] < min[i]) 
			{												//compares min with every index of assignment marks
				min[i] = list[j].assignmentMarks[i];		//saves marks in min if they are less
			}
		}
	}

	return min;

}

double* avgQuizMarks(studentReport* list, int totalStudents)
{
	int quizzes = list[0].numberOfQuizes;
	double* avg = new double[quizzes];

	for (int i = 0; i < quizzes; i++) 
	{
		avg[i] = 0;
	}

	for (int i = 0; i < quizzes; i++) 
	{
		for (int j = 0; j < totalStudents; j++) 
		{
			avg[i] = avg[i] + list[j].quizMarks[i];			//add all the marks
		}
		avg[i] = ceil(avg[i] / totalStudents);			//rounds up to the next integer after deviding
	}

	return avg;

}

double* avgAssignmentMarks(studentReport* list, int totalStudents)
{
	int assignments = list[0].numberOfAssignments;
	double* avg = new double[assignments];

	for (int i = 0; i < assignments; i++) 
	{
		avg[i] = 0;
	}

	for (int i = 0; i < assignments; i++) 
	{
		for (int j = 0; j < totalStudents; j++) 
		{
			avg[i] = avg[i] + list[j].assignmentMarks[i];		//add all the marks
		}
		avg[i] = ceil(avg[i] / totalStudents);				//rounds to the next integer
	}

	return avg;

}

void deAllocate(int*& array)
{
	if (array)
	{
		delete[] array;
		array = 0;
	}

}

void deAllocate(double*& array)
{
	if (array)
	{
		delete[] array;
		array = 0;
	}

}

static void DeleteStaticData()
{
	delete[] studentReport::totalQuizMarks;
	delete[] studentReport::totalAssignmentMarks;

}