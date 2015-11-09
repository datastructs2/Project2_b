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
		retaining_time = 7; // for now all employees have equal times
		waiting_time = 0;

	}
	
	// GETTERS
	string get_employee()const{
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
	friend ostream& operator << (ostream& out, Employee& someone) {
		out << "Name: " << someone.get_employee() << endl;
		if (someone.get_waiting() == 0){
			out << "Waiting time: " << someone.get_waiting() << " (currently has book)" << endl
				<< "Time to have book: " << someone.get_retaining() << endl << endl;
		}
		else{
			out << "Waiting time: " << someone.get_waiting() << endl
			<< "Time to have book: " << someone.get_retaining() << endl << endl;
		}
		return out;
	}

	void print(){

	cout << "Name: " << get_employee() << endl;
	if (get_waiting() == 0){
	cout << "Waiting time: " << get_waiting() << " (currently has book)" << endl
	<< "Time to have book: " << get_retaining() << endl << endl;
	}
	else{
	cout << "Waiting time: " << get_waiting() << endl
	<< "Time to have book: " << get_retaining() << endl << endl;
	}
	}


};
