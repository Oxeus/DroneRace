//*****************************************************************************************
//Program by: Adam LaFleur
//Date: April 24, 2019
//Class: CS202 - Programming Systems
//Program: #1 - Drone Race
//File: control.cpp
//Purpose: The purpose of this program is to keep track of information pertaining to drones
//traveling through an obstacle course, it also handles collisions with object and other drones.
//Also keeps track of it there is a winner of the race also.
//control.cpp has the purpose of implementing the dronelist and drone classes defined in control.h
//*****************************************************************************************
#include <iostream>
#include <cstring>
#include "control.h"



using namespace std;



//Control Class
//Constructor used to initialize the class object without arguments
control::control() : dronelist()
{
	SIZE = 0;
	table = nullptr;
}



//Constructor used to initialize the class object with an int argument
control::control(int number) : dronelist(number)
{
	SIZE = 21;
	table = nullptr;
	if(SIZE > 0 && number > 0)
	{
		table = new vertex*[SIZE];
		fill_empty(table, SIZE);
		create();
	}
}



//Constructor used to initialize the class object with a pass by reference
//control object, also a copy constructor
control::control(const control &to_copy) : dronelist(to_copy)
{
	SIZE = to_copy.SIZE;
	table = nullptr;
	if(SIZE > 0 && to_copy.number_of_drones > 0)
	{
		table = new vertex*[SIZE];
		fill_empty(table, SIZE);
		create();
	}
}



//Destructor used to destroy the vertex table, calls a recursive function.
control::~control()
{
	if(table)
	{
		delete_table(table, SIZE);
		delete [] table;
	}
}



//Function used to create a graph
void control::create()
{
	//Fill graph with obstacles
	*(table + 4) = new asteroid();
	*(table + 16) = new asteroid();
	*(table + 19) = new asteroid();
	*(table + 8) = new black_hole();
	*(table + 9) = new black_hole();
	*(table + 11) = new black_hole();
	*(table + 2) = new goal_post();
	*(table + 5) = new goal_post();
	*(table + 15) = new goal_post();

	//Fills Rest of Graph with points
	fill_table(table, SIZE);

	//Moves all rovers to the starting location
	get_ready(*(table + 0), *(table + (SIZE - 1)));

	//Sets Connections
	(*(table + 0))->add_adjacent(*(table + 1));
	(*(table + 0))->add_adjacent(*(table + 2));	
	(*(table + 0))->add_adjacent(*(table + 3));
	(*(table + 1))->add_adjacent(*(table + 5));
	(*(table + 1))->add_adjacent(*(table + 6));
	(*(table + 2))->add_adjacent(*(table + 6));
	(*(table + 3))->add_adjacent(*(table + 6));
	(*(table + 3))->add_adjacent(*(table + 7));
	(*(table + 3))->add_adjacent(*(table + 4));
	(*(table + 5))->add_adjacent(*(table + 8));
	(*(table + 5))->add_adjacent(*(table + 13));
	(*(table + 5))->add_adjacent(*(table + 10));
	(*(table + 6))->add_adjacent(*(table + 10));
	(*(table + 6))->add_adjacent(*(table + 11));
	(*(table + 6))->add_adjacent(*(table + 12));
	(*(table + 7))->add_adjacent(*(table + 12));
	(*(table + 7))->add_adjacent(*(table + 15));
	(*(table + 7))->add_adjacent(*(table + 9));
	(*(table + 10))->add_adjacent(*(table + 13));
	(*(table + 10))->add_adjacent(*(table + 14));
	(*(table + 12))->add_adjacent(*(table + 14));
	(*(table + 12))->add_adjacent(*(table + 15));
	(*(table + 13))->add_adjacent(*(table + 16));
	(*(table + 13))->add_adjacent(*(table + 17));
	(*(table + 14))->add_adjacent(*(table + 17));
	(*(table + 14))->add_adjacent(*(table + 18));
	(*(table + 15))->add_adjacent(*(table + 18));
	(*(table + 15))->add_adjacent(*(table + 19));	
	(*(table + 17))->add_adjacent(*(table + 20));
	(*(table + 18))->add_adjacent(*(table + 20));
}



//Function used to set the vertex table to nullptr. Takes 
//a vertex ** and integer as an argument
void control::fill_empty(vertex ** table, int num)
{
	if(num == 0) return;
	*(table + (num - 1)) = nullptr;
	fill_empty(table, --num);
}



//Function used to set the empty table indexes to points.
void control::fill_table(vertex ** table, int num)
{
	if(num == 0) return;
	if(*(table + (num - 1)) == nullptr)
	{
		*(table + (num - 1)) = new point();
	}
	fill_table(table, --num);
}



//Wrapper function used to print the graph for testing purposes
void control::display_graph()
{
	if(SIZE > 0)
	{
		display_graph(table, SIZE);
	}
}



//Recursive function used to print the graph for testing 
//Purposes only
void control::display_graph(vertex ** table, int num)
{
	if(num == 0) return;
	vertex * curr = *(table + (num - 1));

	display_graph(table, --num);

	if(curr)
        {
                curr->print_name();
                cout << endl << "Adjacent: " << endl;
                curr->print_decisions();
                cout << endl << endl;
        }
}



//Function used by the destructor to delete the table,
//takes a vertex ** pointer as an argument and an
//integer argument
void control::delete_table(vertex ** table, int num)
{
	if(num == 0) return;
	delete *(table + (num - 1));
	delete_table(table, --num);
}



//Dronelist Class
//Constructor that initializes the object with no arguments
dronelist::dronelist() : sortlist()
{
	start = nullptr;
	finish = nullptr;
}



//Constructor that initializes the object with an integer argument
dronelist::dronelist(int number) : sortlist(number)
{
	start = nullptr;
	finish = nullptr;
}



//Constructor that initializes the object with a pass by reference
//dronelist argument.
dronelist::dronelist(const dronelist & to_copy) : sortlist(to_copy)
{
	start = nullptr;
	finish = nullptr;
}



//Wrapper Function used to set the locations of all drones to the start of
//the table. Takes two vertex pointers as imput arguments.
void dronelist::get_ready(vertex * new_start, vertex * new_finish)
{
        start = new_start;
        finish = new_finish;
        get_ready(head, new_start);
}



//Recursive Function used by its wrapper, takes a drone pointer
//and vertex pointer as arguments
void dronelist::get_ready(drone * head, vertex * updated)
{
        if(!head) return;
        head->change_location(updated);
        get_ready(head->go_next(), updated);
}



//Wrapper Function used to move the drones
void dronelist::move_drones()
{
	move_drones(head);
	sort_drones();
	interact_drones(head);
	remove_drones(head);
}



//Recursive Function used to move the drones, takes a pass by reference
//drone pointer as an argument
void dronelist::move_drones(drone *& head)
{
	int control = 0;
	if(!head) return;
	control = head->move();
	if(control == 2)
	{
		head->change_location(start);
	}
	move_drones(head->go_next());
	if(control == 1 && head)
	{
		head->print_name();
		cout << " hit an asteroid and was destroyed, it will be removed from the race! " << endl << endl;
		if(head->go_next())
		{
			head->go_next()->go_prev() = head->go_prev();
		}
		drone * ptr = head->go_next();
		delete head;
		head = ptr;
		--number_of_drones;
	}
}



//Function used to sort the drones in the list
void dronelist::sort_drones()
{
	int num = 0;
	drone ** arr = new drone*[number_of_drones];
	dll2arr(head, arr, num);
	head = nullptr;
	bubblesort(arr, num);
	arr2dll(head, arr, num);
	delete [] arr;
}



//Function used to mark drones for removal if they are at the same location.
//Takes a pass py refernce drone pointer, vertex pointer, and pass by reference
//int value as arguments;
void dronelist::mark_drones(drone *& head, vertex * location, int &count)
{
	if(!head) return;
	if(head->compare_location(location))
	{
		++count;
	}
	mark_drones(head->go_next(), location, count);
	if((count > 1) && head->compare_location(location))
	{
		head->change_marker(1);
	}
}



//Function used to recursively remove drones in the list if they are marked for removal.
//Takes a pass by reference drone pointer as an argument.
void dronelist::remove_drones(drone *& head)
{
	if(!head) return;
	remove_drones(head->go_next());
	if(head->compare_marker(1))
	{
		head->print_name();
		cout << " has crashed into another drone and will be removed from the race! " << endl << endl;
		if(head->go_next())
		{	
			head->go_next()->go_prev() = head->go_prev();
		}
		drone * ptr = head->go_next();
		--number_of_drones;
		delete head;
		head = ptr;
	}
}



//Function used to control the interaction of drones with each other, traverses the whole list
//to find drones and sees if their is another drone there. Takes a pass by reference drone 
//pointer as an argument
void dronelist::interact_drones(drone *& head)
{
	int count = 0;
	if(!head) return;
	mark_drones(head, head->get_location(), count);
	interact_drones(head->go_next());
}



//Wrapper function used to determine if a drone has reached the finish line or not. Returns a 
//bool argument.
bool dronelist::race_won()
{
	if(!head) 
	{
		cout << "No drones left in the race! " << endl;
		return true;
	}
	return race_won(head);
}



//Recursive function used to determine if a drone has reached the finish line, if so it prints
//out the winner. Takes a drone pointer as an argument.
bool dronelist::race_won(drone * head)
{
	if(!head) return false;
	if(head->compare_location(finish))
	{
		head->print_name();
		cout << " has reached the finish line. It won the race! " << endl;
		return true;
	}
	return race_won(head->go_next());
}



//sortlist
//Constructor without arguments
sortlist::sortlist() : doublylist(), number_of_drones(0) {}



//Constructor with arguments that passes data to parent.
sortlist::sortlist(int number) : doublylist(number), number_of_drones(number) {}



//Constructor with a pass by reference sortlist as an argument. Copy Constructor.
sortlist::sortlist(const sortlist & to_copy) : doublylist(to_copy), number_of_drones(to_copy.number_of_drones) {}



//Recursive Function used to change a dll into an arr without new allocations. Takes a pass by reference
//drone pointer, a drone **, and an int as an argument.
void sortlist::dll2arr(drone *& head, drone ** arr, int num)
{
	if(!head) return;
	*(arr + num) = head;
	dll2arr(head->go_next(), arr, ++num);
	if(head)
	{
		head->go_next() = nullptr;
		head->go_prev() = nullptr;
	}
}



//Recursive Function used to change a arr into a dll without new allocations. Takes a pass by reference
//drone pointer, a drone **, and an int as an argument.
void sortlist::arr2dll(drone *& head, drone ** arr, int num)
{
	if(num == number_of_drones) return;
	head = *(arr + num);
	*(arr + num) = nullptr;
	arr2dll(head->go_next(), arr, ++num);
	if(head->go_next())
	{
		head->go_next()->go_prev() = head;
	}
}



//Part of the recursive function used to bubble sort the list. takes a drone **, and an two integers as
//arguments.
void sortlist::largest(drone ** arr, int i, int j)
{
	drone * temp = nullptr;
	if(j == (number_of_drones - i)) return; //one the smallest item is at the end of the array, then it reduces size
	{
		if(arr[j - 1]->compare_position(*arr[j]))
		{
			temp = arr[j - 1];
			arr[j - 1] = arr[j];
			arr[j] = temp;
		}
	}
	largest(arr, i, ++j);
}



//Recursive Function used to bubble sort the list. Takes a drone ** and an int as an argument.
void sortlist::bubblesort(drone ** arr, int num)
{
	if(num == number_of_drones) return;
	largest(arr, num, 1);
	bubblesort(arr, ++num);
}



//doublelist
//Constructor without arguments, sets head to nullptr. 
doublylist::doublylist()
{
	head = nullptr;
}



//Constructor with an integer argument, creates an drone list with a length of that integer. 
//Tekas an integer argument.
doublylist::doublylist(int num)
{
	head = nullptr;
	create_list(head, num);
	head->print_name();
	head->go_next()->print_name();
	head->go_next()->go_prev()->print_name();
}



//Constructor with an doublylist argument, copies the list from to_copy. Takes a pass by 
//reference argument.
doublylist::doublylist(const doublylist & to_copy)
{
	head = nullptr;
	copy_list(head, to_copy.head);
}



//Destructor used to delete the drone list
doublylist::~doublylist()
{
	delete_list(head);
}



//Function used to copy the list, called by copy constructor. Takes a pass by reference drone
//pointer and a const drone pointer as an argument.
void doublylist::copy_list(drone *& head, const drone * source)
{
	if(!source)
	{
	       	head = nullptr;	
		return;
	}
	head = new drone(*source);
	copy_list(head->go_next(), source->copy_next());
	if(head->go_next())
	{
		head->go_next()->go_prev() = head;
	}
}



//Function used to creat the list, called by constructor. Takes a pass by reference drone pointer
//and an integer as an argument.
void doublylist::create_list(drone *& head, int number)
{
	if(number == 0)
	{
		head = nullptr;
		return;
	}
	else
	{
		char temp[10] = {"Drone "}, temp2[5];
		sprintf(temp2,"%d",number);
		strcat(temp, temp2);
		head = new drone(temp);
	}
	create_list(head->go_next(), --number);
	if(head->go_next())
	{
		head->go_next()->go_prev() = head;
	}
}



//Wrapper function used to print the list of drones
void doublylist::print_list()
{
	print_list(head);
}



//Recursive function used to print the list of drones. Takes a drone pointer as an argument.
void doublylist::print_list(drone * head)
{
	if(!head) return;
	cout << "Name: ";
	head->print_name();
	cout << endl;
	cout << "Location: ";
	head->print_location();
	cout << endl;
	cout << "Position: ";
	head->print_position();
	cout << endl << endl;
	print_list(head->go_next());
}



//Recursive Function used by destructor to delete the drone list. Takes a pass by reference drone
//pointer as an argument.
void doublylist::delete_list(drone *& head)
{
	if(!head) return;
	delete_list(head->go_next());
	if(head)
	{
		delete head;
		head = nullptr;
	}
}
