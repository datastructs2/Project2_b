#include <string>
#include <iostream>
using namespace std;

class Employee{
private:
	string name;		// name of employee
	int waiting_time;	// time employee waits to recieve book
	int retaining_time;	// time employee gets to have book
	
public:
	
	// CONSTRUCTOR
	Employee(string employee){
		name = employee;
		
		//default these to zero since we don't know them yet
		retaining_time = 0; 
		waiting_time = 0; 

	}
	

	//COPY CONSTRUCTOR
	Employee(const Employee& other){
		*this = other;
	}
	//OVERLOAD ASSIGNMENT
	const Employee& operator=(const Employee& rhs){
		if (this != &rhs){
			name = rhs.name;
			waiting_time = rhs.waiting_time;
			retaining_time = rhs.retaining_time;
		}
		return *this;
	}

	// GETTERS
	string get_employee(){
		return name;
	}

	int get_waiting(){
		return waiting_time;
	}
	int get_retaining(){
		return retaining_time;
	}

	// SETTERS
	void set_waiting(int days_to_wait){
		waiting_time = days_to_wait;
	}

	void set_retaining(int days_held){
		retaining_time = days_held;
	}

	// CLASS BASED FUNCTIONS

	//for retaining
	friend ostream& operator << (ostream& out, Employee& someone) {
		out << "Name: " << someone.get_employee() << endl;
		if (someone.get_waiting() == 0){
			out << "Days Employee had book: " << someone.get_retaining() << endl << endl;
		}
		else{
			out << "Waiting time: " << someone.get_waiting() << endl
			<< "Days retained: " << someone.get_retaining() << endl << endl;
		}
		return out;
	}

	

	void print(){

	cout << "Name: " << get_employee() << endl;
	if (get_retaining() == 0){
	cout << "Waiting time: " << get_waiting() << endl
	<< "Days retained last: " << get_retaining() << " (unknown)" << endl << endl;
	}
	else{
	cout << "Waiting time: " << get_waiting() << endl
	<< "Days retained last: " << get_retaining() << endl << endl;
	}
	}


};
