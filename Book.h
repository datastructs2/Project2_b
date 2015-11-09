#include <string>
#include "Date.h"
#include "Employee.h"
#include "queue.h"
#include <iostream>
using namespace std;

class Book {
private:
	string title;		// title of book
	Date start_date;	// date book starts circulating
	Date end_date;		// date book ends circulation and returns to archived books list
	bool archived;		// keeps track of whether the book is in library or not (true means it is)
	int size;			// number of employees in waiting list
	int days_added = 0;		// increments for every day addedd to end_date
	
	Employee* Employee_Pointer;//will point to the employees added to the queue

	//queue<Employee> Waiting_List;
	// This should be a priority queue of pointers to employees
	queue<Employee*> Waiting_List;	// the employees the book must circulate to

public:
	// CONSTRUCTOR
	//Book(string book, Date somedate) {
	Book(string book) {
		title = book;
		archived = true;	// will default to this for now
		set_dates(Date(2000, 1, 1, DateFormat::US));		// default for now
		
		Employee_Pointer = nullptr;

		size = 0;
	}


	void manual_delete(){
		if (Employee_Pointer != nullptr)
			delete Employee_Pointer;
	}

	//DESTRUCTOR
	~Book(){
		if (Employee_Pointer != nullptr)
			delete Employee_Pointer;
	}

	// GETTERS
	string get_title() {
		return title;
	}
	bool get_archived() {
		return archived;
	}
	string get_start() {
		string start = start_date.toString();
		return start;
	}
	string get_end() {
		string end = end_date.toString();
		return end;
	}

	int get_size(){
		return size;
	}

	int get_days_added(){
		return days_added;
	}

	// SETTERS
	void set_dates(Date somedate) {	// circulation starts on a given date
		// for now...
			start_date = somedate;	// circulation can begin immediately
			// LIBRARY.H will change the start date with the pass_on() function
			end_date = somedate;	// equals the start date

	}

	void set_start(Date somedate){
		start_date = somedate;
		end_date = somedate;//change end as well
	}

	void set_end(int days) {
		end_date.add_days(days);	//	this date will change as employees are added
	}

	void set_archived(bool status) {
		archived = status;
	}

	void added_to_queue(){
		size++;
	}

	void set_days_added( int days){
		days_added+=days;
	}

	// class based functions
	void add_employee(Employee someone) {

		Employee_Pointer = new Employee(someone.get_employee());
		
		if (archived == true){	// if the book is in the library(the line is empty)
			(*Employee_Pointer).set_waiting(0);		/* they are at the front of the line, so they can immediately
									    check out the book */
			set_end((*Employee_Pointer).get_retaining());	/* days are added to the end date each time an employee
												is added */

			set_days_added((*Employee_Pointer).get_retaining());

			//Waiting_List.push((*Employee_Pointer));	// add the employee to the queue
			Waiting_List.push((Employee_Pointer));		// add the employee to the queue
			
			added_to_queue();
			set_archived(false);
		}
		else{	// they will have to wait for the book
			int days_to_wait = 0;			// total days they will have to wait
			int size = Waiting_List.size();	// size of the queue is number of employees 
			
			int count = 0;			// a counter
			while (count < size)	// go through each employee
			{
				// add the days on that they'll have the book
				
				//days_to_wait += Waiting_List.front().get_retaining(); 
				days_to_wait += Waiting_List.front()->get_retaining();
				
				Waiting_List.push(Waiting_List.front());	// keep this employee in the queue
				Waiting_List.pop();	// switch to next employee
				count++;	// increment 
			}
			//once all employees have been accounted for
			(*Employee_Pointer).set_waiting(days_to_wait);	// set the waiting time for this employee
			set_end((*Employee_Pointer).get_retaining());	/* days are added to the end date each time an employee
												is added */
			set_days_added((*Employee_Pointer).get_retaining());
			
			//Waiting_List.push((*Employee_Pointer));	// push them onto the queue
			Waiting_List.push((Employee_Pointer));	// push them onto the queue
			
			added_to_queue();
		}
		
	}

	void pop_employee(){// always will remove from front
		Waiting_List.pop();
		//????????????? adjust times here?
	}

	void print_waiting_list()	{ // will print out the book data
		int count = 0;
		int size = Waiting_List.size();
			if (size != 0){
				cout << "Title: " << get_title() << endl
				 << "Book circulation will begin : " << get_start() << endl
					<< endl;
				while (count < size)
				{
					// THIS WAY RUNS (but doesn't print correct output)
					/*cout << "[" << Waiting_List.front()
						<< "]" << endl;*/
					
					// ??????????? But this doesn't run???
					cout << "[" << endl;
					Waiting_List.front()->print();
					cout << "]" << endl;
					
					Waiting_List.push(Waiting_List.front());

					Waiting_List.pop();
					count++;

					if (count < Waiting_List.size()){
						cout << "\t" << "|" << endl
							<< "\t" << "V" << endl;
					}
				}
				cout << "\n" << "Book circulation will end: " << get_end() << endl;
			}
			else{
				cout << "[ Title: " << get_title() << " ]" << endl;
			}
	}
};
