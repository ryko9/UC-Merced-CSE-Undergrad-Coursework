#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <assert.h>
using namespace std;


struct Time
{
	int hour;
	int minutes;
	int seconds;
};

struct Course
{
	string name;
	int credits;
	bool majorRequirement;
	double avgGrade;
	string days;
	Time startTime;
	Time endTime;
};

void getTimeFromUser(Time &time, string input) //passes time struct by reference and takes in second parameter of type string to convert into proper time format
{

                //indexes of semicolons in int variables

                int semi1 = input.find(":", 0); //represents index of first semicolon found starting from index 0
                int semi2 = input.find(":", semi1 + 1); //to find the second semicolon AFTER index "first", we start from first + 1

                //strings that contain hour, seconds, and minutes extracted from user input

                //to get substring from index x to index y, substr(x, y - x)

                string strhour = input.substr(0, semi1); //hour is string from index 0 to the index BEFORE the semicolon.
                string strminutes = input.substr(semi1 + 1, semi2 - semi1 + 1); //minutes is between first semi and second semi
                string strseconds = input.substr(semi2 + 1, input.length() - semi2 + 1); //seconds is in between second and third semi

                //we start from index semi1 + 1 since we don't want to reinclude the semicolon. Then we go up a length of
                // semi2 - (semi1 + 1) in order to go from (semi1 + 1) to the index BEFORE semi2

                //converting hour, seconds, and minutes to integers.

                int hour = atoi(strhour.c_str());
                int minutes = atoi(strminutes.c_str());
                int seconds = atoi(strseconds.c_str());

                //checking if hour, minutes, and seconds are valid

		if(hour > 12)
		{
			hour -= 12;
		}

                time.hour = hour;        //sets structure values and returns true if valid
                time.minutes = minutes;
                time.seconds = seconds;



}

void print24Hour(Time &time) //prints time out
{

        //setfill(0) << setw(2) puts 2 spaces filled with '0'. When you input time, hour, and minutes, they fit into the spaces

        cout << setfill('0') << setw(2) << time.hour << ":"; // hour, followed by semicolon
        cout << setfill('0') << setw(2) << time.minutes << ":"; // minutes followed by semi
        cout << setfill('0') << setw(2) << time.seconds;  //seconds followed by semi

}

void printCourse(struct Course A[], int size) //prints out course elements
{
	//heading
	cout << setfill('-') << setw(20) << " " << endl;
	cout << "SCHEDULE OF STUDENT "<< endl;
	cout << setfill('-') << setw(20) << " " << endl;

	//courses
	for(int i = 0; i < size; i++)
	{
		cout << "COURSE " << i + 1 << " : " << A[i].name << endl;
		if(A[i].majorRequirement == 1)
		{
			cout << "Note: this course is a major requirement!" << endl;
		}
		else
		{
			cout << "Note: this course is not a major requirement... " << endl;
		}
		cout << "Number of Credits: " << A[i].credits << endl;

		cout << "Days of Lectures: " <<  A[i].days << endl;

		cout << "Lecture time: ";
		print24Hour(A[i].startTime);
		cout << "pm -";
		print24Hour(A[i].endTime);
		cout << "pm" << endl;

		cout << "Stat: on average students get " << A[i].avgGrade << "% in this course." << endl;
		cout << setfill('-') << setw(20) << " " << endl;
	}
}

int main()
{

	int size = 0; //size of string array
        int j = 0; //used later to go through string array
        string line; //arbitrary string to go through first line of file.

        //go through file contents
        ifstream input;

        input.open("words_in.txt"); //file name
        assert(!input.fail()); //address validation

        string firstLine; //getting first line of file
        getline(input, firstLine);
        int numCourses = atoi(firstLine.c_str()); //converting first line into int that represents number of courses

        while(!input.eof())
        {
                getline(input,line);
                size++;
        }

        string lines[size]; //string array to store each line of the array.

        input.close(); //reopening file
        input.open("words_in.txt");
        getline(input, line); //going past first line of file since we already know the number of courses. the other elements are what we need to store now

        for(int i = 0; i < size; i++) //inputting lines from file into array
        {
                getline(input, lines[i]); //inputting line (0+i) into element i of array
        }


        input.close(); //close input
        Course* courses = new Course[numCourses]; //creates time array with number of elements based on FIRST line in text which should represent # of courses

        for(int i = 0; i < numCourses; i++) //assigning values to elements in course array
        {
                //j represents index of string array. every time we want the next line, we will just increment j by 1 without resetting its value

                courses[i].name = lines[j];
                j++;
                courses[i].credits = atoi(lines[j].c_str());
                j++;
                if(atoi(lines[j].c_str()) == 1)
                {
                        courses[i].majorRequirement = true;
                }
                else
                {
                        courses[i].majorRequirement = false;
                }
                j++;
                courses[i].avgGrade = atof(lines[j].c_str());
                j++;
                courses[i].days = lines[j];
                j++;
                getTimeFromUser(courses[i].startTime, lines[j]);
                j++;
		getTimeFromUser(courses[i].endTime, lines[j]);
		j++;
        }

        printCourse(courses, numCourses);

	return 0;
}
