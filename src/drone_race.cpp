//*****************************************************************************************
//Program by: Adam LaFleur
//Date: April 24, 2019
//Class: CS202 - Programming Systems
//Program: #1 - Drone Race
//File: assignment01.cpp
//Purpose: The purpose of this program is to keep track of information pertaining to drones 
//traveling through an obstacle course, it also handles collisions with object and other drones.
//Also keeps track of it there is a winner of the race also.
//assignment01.cpp has the purpose of controlling the program and sending the number of drones to the classes
//*****************************************************************************************
#include <iostream>
#include "control.h"



using namespace std;



//Client program, can take an argument at run time to specify the number of rovers in the program. Ex: ./a.out 5.
//Creates a control mission object and used public functions from control to run and control the program.
int main(int argc, char ** argv)
{
	int drones = 3;
	bool loop = true;

	if(argc > 1) 
	{
		drones = atoi(argv[1]);
	}

	control mission(drones);
	cout << "----------------------------------------------" << endl;
        cout << "********* Assignment 01: Drone Race **********" << endl;
        cout << "----------------------------------------------" << endl;
	//mission.display_graph(); //For Testing Map
	while(loop)
	{
		cout << endl <<  "The current standing of the race is: " << endl;
		cout << "----------------------------------------------" << endl;
		mission.print_list();
		mission.move_drones();
		if(mission.race_won())
		{
			loop = false;
			if(drones == 0)
			{
				cout << "There was no drone applications for the race. " << endl;
			}
		}
	}
	cout << endl << "Quitting Drone Race! " << endl;
	return 0;
}
