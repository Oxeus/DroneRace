//*****************************************************************************************
//Program by: Adam LaFleur
//Date: April 24, 2019
//Class: CS202 - Programming Systems
//Program: #1 - Drone Race
//File: control.h
//Purpose: The purpose of this program is to keep track of information pertaining to drones
//traveling through an obstacle course, it also handles collisions with object and other drones.
//Also keeps track of it there is a winner of the race also.
//control.h has the purpose of defining the classes and their functions that were used in the 
//program. Also defines the relationship between classes whether it is "is a" or "has a".
//*****************************************************************************************



class vertex;
class node;



//Base Class
//Name: Has the purpose of defining a name for the object or drone
class name {
	public:
		name();
		name(char * new_name);
		name(const name &to_copy);
		~name();

		void print_name();

	protected:	
		char * object_name;
};



//Drone Classes
//Location: Has the purpose of defining what a location is, can print, get, change, and compare locations
class location : public name
{
	public:
		location();
		location(char * new_name);
		location(const location &to_copy);

		void print_location();
		void change_location(vertex * start);
		vertex * get_location();
		bool compare_location(vertex * to_compare);

	protected:
		vertex * loc;
};



//Drone: Has the purpose of defining what a drone is, handles the movement and interaction of each drone.
class drone : public location
{
	public:
		drone();
		drone(char * new_name);
		drone(const drone &to_copy);
		
		drone *& go_prev();
		drone *& go_next();
		drone * copy_next() const;
		
		void change_marker(int num);
		bool compare_marker(int num);
		bool compare_position(const drone &to_compare);
		void print_position();
		int move();

	protected:
		void drone_interact(int num);

		int position;
		int held;
		int marker;

		drone * next;
		drone * prev;
};



//Dronelist Classes
//Doublylist: Has the purpose of defining what a doublylist is, can copy, create, print, and delete a doubly linked list.
class doublylist
{
	public:
		doublylist();
		doublylist(int number);
		doublylist(const doublylist &to_copy);
		~doublylist();

		void print_list();

	protected:
		void copy_list(drone *& head, const drone * source);
		void create_list(drone *& head, int number);
		void print_list(drone * head);
		void delete_list(drone *& head);

		drone * head;
};



//Sortlist: Has the purpose of sorting the drone list to keep track of current leader has functions to change list to array of
//drone pointers(without new allocations), sort, and change it back to a dll. 
class sortlist : public doublylist
{
	public:
		sortlist();
		sortlist(int number);
		sortlist(const sortlist &to_copy);

	protected:
		void dll2arr(drone *& head, drone ** arr, int num);
		void arr2dll(drone *& head, drone ** arr, int num);
		void largest(drone ** arr, int i, int j);
		void bubblesort(drone ** arr, int num);
		void sort_drones();

		int number_of_drones;
};



//Dronelist: Has the purpose of defining the functions that will be used control the initialization, movement, sorting, removal,
//and interaction of drones.
class dronelist : public sortlist
{
	public:
		dronelist();
		dronelist(int number);
		dronelist(const dronelist &to_copy);

		void move_drones();
		bool race_won();

	protected:
		void get_ready(vertex * new_start, vertex * new_finish);
		void get_ready(drone * head, vertex * updated);
		void move_drones(drone *& head);
		void sort_drones();
		void interact_drones(drone *& head);
		void mark_drones(drone *& head, vertex * location, int &count);
		void remove_drones(drone *& head);
		bool race_won(drone * head);

		vertex * start;
		vertex * finish;
};



//Control: Has the purpose of defining the functions that will create the graph, has access to protected members of parents
//so all functions in the dronelist can be accessed, the client can only access the public members. For testing purposes 
//display graph can be used to print the verteces and their adjacent verteces.
class control : public dronelist
{
	public:
		control();
		control(int number);
		control(const control &to_copy);
		~control();

		void display_graph();

	private:
		void create();
		void fill_table(vertex ** table, int num);
		void fill_empty(vertex ** table, int num);
		void display_graph(vertex ** table, int num);
		void delete_table(vertex ** table, int num);

		vertex ** table;
		int SIZE;
};



//Graph
//Vertex: Used to define what a vertex is for the graph, uses dynamic binding with virtual functions. Has
//functions to add, print, and delete vertices.
class vertex : public name
{
        public:
		vertex();
                vertex(char * object_name);
                virtual ~vertex();

		virtual void print()=0;
		virtual int interact()=0;

		void add_adjacent(vertex * to_add);
		void print_decisions();
		vertex * decide(int num);

        protected:
		void add_adjacent(node *& head, vertex * to_add);
		void print_decisions(node * head, int &num);
		void delete_adjacent(node *& head);	
		vertex * decide(node * head, int &num);

                node * head;
};



//Node: Used to define what a node is for the graph, has functions to get next node, get the vertex,
//print the vertex and the node, and print the adjacent vertex name.
class node
{
        public:
                node();
		node(vertex * new_adjacent);

		node *& get_next();
		vertex * get_adjacent();
		void print_node();
		void print_adjacent_name();

        protected:
                vertex * adjacent;
                node * next;
};



//Obstacles
//Defines a point. Derived from vertex. 
class point : public vertex
{
	public:
		point();
		void print();
		int interact();
};



//Defines an asteroid. Derived from vertex.
class asteroid : public vertex
{
	public:
		asteroid();
		void print();
		int interact();
};



//Defines a black_hole. Derived from vertex.
class black_hole : public vertex
{
	public:
		black_hole();
		void print();
		int interact();
};



//Defines a goal_post. Derived from vertex.
class goal_post : public vertex
{
	public:
		goal_post();
		void print();
		int interact();
};
