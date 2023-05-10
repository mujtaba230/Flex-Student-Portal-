#include <iostream>
#include <fstream>
#include"Helper.h"
#include"StudentPortal.h"

using namespace std;


int main()
{
	const char* FILE_NAME = "gradesheet.txt";
	studentReport* studentList = getDataFromFile(FILE_NAME);

	int totalStudents = studentReport::getTotalStudents();

	cout << "----------------------- Data Read From File-------------------------\n\n";

	cout << "Roll No.\t Name\t\t\t Q1\t Q2\t Q3\t Q4\t A1\t A2\t A3\t A4\t Total\n";
	
	for (int i = 0; i < totalStudents; i++) 
	{
		studentList[i].printList();
	}

	cout << "\n\n----------------------- Sorted List-------------------------\n\n";

	cout << "Roll No.\t Name\t\t\t Q1\t Q2\t Q3\t Q4\t A1\t A2\t A3\t A4\t Total\n";

	for (int i = 0; i < totalStudents; i++) 
	{
		for (int j = 0; j < totalStudents - 1; j++) 
		{
			if (studentList[j].getTotal() > studentList[j + 1].getTotal()) 
			{
				studentReport temp = studentList[j];
				studentList[j] = studentList[j + 1];
				studentList[j + 1] = temp;
			}
		}
	}

	for (int i = 0; i < totalStudents; i++) 
	{
		studentList[i].printList();
	}

	cout << "\n\n----------------------- Student Information -------------------------\n\n";

	const char* find1 = new char[9];
	find1 = "15L-1234";

	int index = 0;
	bool found = findRollNo(find1, studentList, totalStudents, index);

	if (found) 
	{
		studentList[index].printDetail();
	}
	else 
	{
		cout << "Student Not Found\n";
	}

	cout << "\n\n----------------------- Student Information -------------------------\n\n";

	const char* find2 = new char[9];
	find2 = "15L-4023";

	index = 0;
	found = findRollNo(find2, studentList, totalStudents, index);

	if (found)
	{
		studentList[index].printDetail();
	}
	else
	{
		cout << "Student Not Found\n";
	}


	cout << "\n\n----------------------- Class Statistics -------------------------\n\n";

	cout << "\t\tQ1\t Q2\t Q3\t Q4\t A1\t A2\t A3\t A4";

	int quizzes = studentReport::getNumberOfQuizzes();
	int assignments = studentReport::getNumberOfAssignments();

	cout << "\nTotal:\t\t";

	int* totalQuizMarks = studentReport::getTotalQuizMarks();
	
	for (int i = 0; i < quizzes; i++) 
	{
		cout << totalQuizMarks[i] << "\t";
	}

	int* totalAssignmentMarks = studentReport::getTotalAssignmentMarks();
	
	for (int i = 0; i < assignments; i++) 
	{
		cout << totalAssignmentMarks[i] << "\t";
	}

	cout << "\nMaximum:\t";

	int* maxQuiz = maxQuizMarks(studentList, totalStudents);

	for (int i = 0; i < quizzes; i++)
	{
		cout << maxQuiz[i] << "\t";
	}

	int* maxAssignment = maxAssignmentMarks(studentList, totalStudents);

	for (int i = 0; i < assignments; i++)
	 {
		cout << maxAssignment[i] << "\t";
	}

	cout << "\nMinimun:\t";

	int* minQuiz = minQuizMarks(studentList, totalStudents);

	for (int i = 0; i < quizzes; i++)
	{
		cout << minQuiz[i] << "\t";
	}

	int* minAssignment = minAssignmentMarks(studentList, totalStudents);
	for (int i = 0; i < assignments; i++)
	{
		cout << minAssignment[i] << "\t";
	}

	cout << "\nAverage:\t";

	double* avgQuiz = avgQuizMarks(studentList, totalStudents);

	for (int i = 0; i < quizzes; i++)
	{
		cout << avgQuiz[i] << "\t";
	}

	double* avgAssignment = avgAssignmentMarks(studentList, totalStudents);
	for (int i = 0; i < assignments; i++) 
	{
		cout << avgAssignment[i] << "\t";
	}

	// Memory Deallocation

	deAllocate(maxQuiz);
	deAllocate(minQuiz);
	deAllocate(maxAssignment);
	deAllocate(minAssignment);
	deAllocate(avgQuiz);
	deAllocate(avgAssignment);

	if (studentList) 
	{
		delete[] studentList;
		studentList = 0;
	}

}

