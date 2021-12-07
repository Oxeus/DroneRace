//*****************************************************************************************
//Program by: Adam LaFleur
//Date: April 24, 2019
//Class: CS202 - Programming Systems
//Program: #1 - Drone Race
//File: graph.cpp
//Purpose: The purpose of this program is to keep track of information pertaining to drones
//traveling through an obstacle course, it also handles collisions with object and other drones.
//Also keeps track of it there is a winner of the race also.
//graph.cpp has the purpose of implementing the graph functions defined in control.h
//*****************************************************************************************
#include "control.h"
#include <iostream>



using namespace std;



//Object Vertex
//Constructor without arguments
vertex::vertex() : name()
{
	head = nullptr;
}



//Constructor to create a vertex with a name
vertex::vertex(char * object_name) : name(object_name)
{
	head = nullptr;
}



//Destructor to delete a list at a vertex
vertex::~vertex()
{
	delete_adjacent(head);
}




//Function to delete the adjacency list, takes a pass by reference
//node pointer as an input 
void vertex::delete_adjacent(node *& head)
{
        if(!head) return;
        delete_adjacent(head->get_next());
        if(head)
        {
                delete head;
                head = nullptr;
        }
}



//Wrapper function used to add to the adjacency list, takes a pointer 
//to a vertex as an argument.
void vertex::add_adjacent(vertex * to_add)
{
	add_adjacent(head, to_add);
}



//Function used to recursively add a vertex to the adjacency list, takes a 
//pass by reference node pointer and a vertex pointer.
void vertex::add_adjacent(node *& head, vertex * to_add)
{
	if(!head)
	{
		head = new node(to_add);
		return;
	}
	add_adjacent(head->get_next(), to_add);
}



//Wrapper function used to print the decisions that the drone can make.
void vertex::print_decisions()
{
	int num = 0;
	print_decisions(head, num);
}



//Function used to recursively print the verteces in the adjacency list
//takes a node pointer and a pass by reference int as arguments.
void vertex::print_decisions(node * head, int &num)
{
	if(!head) return;
	cout << num << ": ";
	head->print_adjacent_name();
	cout << " ";
	print_decisions(head->get_next(), ++num);
}



//Wrapper function used to select which vertex to go to based on a integer
//imput passed to it. Returns a vertex pointer.
vertex * vertex::decide(int num)
{
	int temp = num;
	return decide(head, temp);
}



//Function to recursively select which node to go to, takes a pass by reference 
//integer and a node pointer as arguments. Returns a vertex pointer.
vertex * vertex::decide(node * head, int &num)
{
	if(!head || num < 0) return nullptr;
	if(num == 0)
	{
		return head->get_adjacent();
	}
	return decide(head->get_next(), --num);
}



//Node Object
//Constructor without arguments, sets data members to nullptr
node::node() : adjacent(nullptr), next(nullptr) {}



//Constructor that creates a node using a vertex pointer as an argument.
node::node(vertex * new_adjacent) : adjacent(new_adjacent), next(nullptr) {}



//Function used to get the next node pointer, returns a pass by reference node pointer.
node *& node::get_next()
{
	return next;
}



//Function used to get the adjacent vertex, returns a vertex pointer
vertex * node::get_adjacent()
{
	return adjacent;
}



//Funtion used to print the vertex located in the node.
void node::print_adjacent_name()
{
	if(adjacent)
	{
		adjacent->print_name();
	}
}



//Point Object
//Constructor that creates a point and sets the name to Point.
point::point() : vertex((char*)"Point") {};



//Function used to print what happens when a drone interacts with it
void point::print() 
{
	cout << "A Point in the course has been reached! " << endl;
}



//Function used to interact with a drone, returns a 0.
int point::interact()
{
	return 0;
}



//Asteroid Object
//Constructor that creates an asteroid and sets the name to Asteroid
asteroid::asteroid() : vertex((char*)"Asteroid") {}



//Function used to print what happens when a drone interacts with it
void asteroid::print() 
{
	cout << "An Asteroid in the course has been reached! The asteroid collides with the drone! Oh No! " << endl;
}



//Function used to interact with a drone, returns a 1.
int asteroid::interact()
{
	return 1;
}



//Black Hole Object
//Constructor that creates a black_hole and sets the name to Black Hole
black_hole::black_hole() : vertex((char*)"Black Hole") {}



//Function used to print what happens when a drone interacts with it
void black_hole::print() 
{
	cout << "A Black Hole in the course has been reached! Drone warped back to start! " << endl;
}



//Function used to interact with a drone, returns a 2.
int black_hole::interact()
{
	return 2;
}



//Goal Post Object
//Constructor that creates a goal_post and sets the name to Goal Post
goal_post::goal_post() : vertex((char*)"Goal Post") {}



//Function used to print what happens when a drone interacts with it
void goal_post::print() 
{
	cout << "A Goal Post in the course has been reached! Drone has to wait a turn and fly over or under to continue! " << endl;
}



//Function used to interact with a drone, returns a 3;
int goal_post::interact()
{
	return 3;
}
