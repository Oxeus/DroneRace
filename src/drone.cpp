//*****************************************************************************************
//Program by: Adam LaFleur
//Date: April 24, 2019
//Class: CS202 - Programming Systems
//Program: #1 - Drone Race
//File: drone.cpp
//Purpose: The purpose of this program is to keep track of information pertaining to drones
//traveling through an obstacle course, it also handles collisions with object and other drones.
//Also keeps track of it there is a winner of the race also.
//drone.cpp has the purpose of implementing the functions pertaining to the drone class
//and its parents.
//*****************************************************************************************
#include <iostream>
#include <cstring>
#include "control.h"



using namespace std;



//Drone Class
//Constructor used to initialize a drone, sets data members
drone::drone() : location(), position(1), held(0), marker(0)
{
	prev = nullptr;
	next = nullptr;
}



//Constuctor used to initialize a drone with a name, sets data members. Takes a char pointer
//as an argument
drone::drone(char * new_name) : location(new_name), position(1), held(0), marker(0)
{
	prev = nullptr;
	next = nullptr;
}



//Constructor used to initialize a drone from another drone. Copy constructor. Sets data member.
//takes a pass by reference drone argument
drone::drone(const drone & to_copy) : location(to_copy.object_name), position(1), held(0), marker(0)
{

	prev = nullptr;
	next = nullptr;
}



//Function used to return a pass by reference pointer of the next drone
drone *& drone::go_prev()
{
	return prev;
}



//Function used to return a pass by reference pointer of the prev drone
drone *& drone::go_next()
{
	return next;
}



//Function used to return a const pointer of the next node for the copy list function.
drone * drone::copy_next() const
{
	return next;
}



//Function that changes the marker value from a integer argument
void drone::change_marker(int num)
{
	marker = num;
}



//Function that compares a marker value to the integer argument passed in, returns a true
//or false value based on whether the argument equals the marker.
bool drone::compare_marker(int num)
{
	if(num == marker)
	{
		return true;
	}
	else
	{
		return false;
	}
}



//Function that compares the position value to the pass by referenc drone position value.
//Returns a true or false value based on if they are equal.
bool drone::compare_position(const drone &to_compare)
{
	if(to_compare.position > position)
	{
		return true;
	}
	else
	{
		return false;
	}
}



//Function that prints the position of a drone
void drone::print_position()
{
	cout << position;
}



//Function that controls what happens to the drone based on whats passed in from the integer
//argument
void drone::drone_interact(int num)
{
	if(num == 2)
	{
		position = 1;
	}
	else if(num == 3)
	{
		held = 1;
	}
}



//Function used to control the movement of a single drone
int drone::move()
{
	int choice = 0, inter = 0;
	vertex * ptr = nullptr;
	print_name();
	cout << " is at a ";
	print_location();
	if(held == 0)
	{
		cout << ". The following choices may be chosen to move the drone: ";
		loc->print_decisions();
		cout << endl << endl << "Please enter a choice to make: ";
		cin >> choice;
		ptr = loc->decide(choice);
		if(ptr)
		{
			change_location(ptr);
			++position;
			cout << endl;
			loc->print();
			inter = loc->interact();
			drone_interact(inter);
		}
	}
	else
	{
		cout << ". The Drone still has to wait a turn to continue! " << endl;
		held = 0;
	}
	cout << endl;
	return inter;
}



//Location Class
//Constructor without arguments, initialize a name object without a name
location::location() : name(), loc(nullptr) {}



//Constructor with a char * argument, initializes a name object with a name.
location::location(char * new_name) : name(new_name), loc(nullptr) {}



//Constructor with a pass by reference location argument. Copy Constructor. 
location::location(const location & to_copy) : name(to_copy), loc(nullptr) {}



//Function used to print the location of a drone
void location::print_location()
{
	loc->print_name();
}



//Function used to change the location of a drone, takes a vertex pointer argument.
void location::change_location(vertex * ready)
{
	loc = ready;
}



//Function used to return a vertex pointer.
vertex * location::get_location()
{
	return loc;
}



//Function used to compare the location of a drone to the vertex pointer argument. Returns
//a bool value
bool location::compare_location(vertex * to_compare)
{
	if(to_compare == loc)
	{
		return true;
	}
	else
	{
		return false;
	}
}



//Name Class
//Constructor without arguments
name::name()
{
	object_name = nullptr;
}



//Constructor with a char * argument. Adds a name to a drone.
name::name(char * new_name)
{
	object_name = new char[strlen(new_name) + 1];
	strcpy(object_name, new_name);
}



//Constructor with a pass by reference name object. Copy Constructor, used
//to copy the name of one drone to another.
name::name(const name &to_copy)
{
	object_name = new char[strlen(to_copy.object_name) + 1];
	strcpy(object_name, to_copy.object_name);
}



//Destructor used to delete the name for a drone.
name::~name()
{
	if(object_name)
	{
		delete [] object_name;
	}
}



//Function used to print the name of a drone
void name::print_name()

{
	if(object_name)
	{
		cout << object_name;
	}
}
