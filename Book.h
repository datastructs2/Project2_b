#include <string>
#include "Date.h"
//#include "Employee.h"
#include "EmpComp.h"
#include "queue.h"
#include "priority_queue.h"
#include <iostream>
using namespace std;

class Book {
private:
	string title;			// title of book
	Date start_date;		// date book starts circulating
	Date end_date;			// date book ends circulation and returns to archived books list
	bool archived;			// keeps track of whether the book is in library or not (true means it is)
	int days_added = 0;		// increments for every day addedd to end_date
	
	Employee* Employee_Pointer;//will point to the employees added to the queue

	//queue<Employee> Waiting_List;
	// This should be a priority queue of pointers to employees
	//queue<Employee*> Waiting_List;	// the employees the book must circulate to
	priority_queue<Employee*, EmpComp> Waiting_List;

public:
	// CONSTRUCTOR
	//Book(string book, Date somedate) {
	Book(string book) {
		title = book;
		archived = false;	// will default to false; when waiting list is empty this will be true
		set_dates(Date(2000, 1, 1, DateFormat::US));		// default for now
		
		Employee_Pointer = nullptr;
	}


	
	// GETTERS

	int get_top_retaining(){
		Employee_Pointer = Waiting_List.front();
		return Employee_Pointer->get_retaining();
	}

	Employee get_top(){
		Employee_Pointer = Waiting_List.front();
		return *Employee_Pointer;
	}
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
	Date get_start_date(){
		return start_date;
	}
	string get_end() {
		string end = end_date.toString();
		return end;
	}

	int get_size(){
		return Waiting_List.size();
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

	void set_start(Date somedate)  {
		start_date = somedate;
		end_date = somedate;//change end as well
	}

	void set_end(int days) {
		end_date.add_days(days);	//	this date will change as employees are added
	}

	void set_archived(bool status) {
		archived = status;
	}


	void set_days_added(int days)  {
		days_added=days;
	}

	void set_top_retaining(Date endDate){
		int days = endDate - start_date;
	 Waiting_List.front()->set_retaining(days);
		//Employee_Pointer->set_retaining(days);
	}
	

	// CLASS BASED FUNCTIONS
	//void add_employee(Employee someone) {
	void add_employee(Employee* Employee_Pointer) {

		//Employee_Pointer = nullptr;
		//Employee_Pointer = new Employee(someone.get_employee());
		//*Employee_Pointer = someone;	// have employee pointer point to someone


		if (archived == true){	// if the book is already circulated
			// do nothing
			cout << "book has already circulated" << endl;
		}
		else{	// they will have to wait for the book
			int days_to_wait = 0;			// total days they will have to wait
			int days_retained = 0;
			int size = Waiting_List.size();	// size of the queue is number of employees 
			if (size == 0){
				(*Employee_Pointer).set_waiting(0);		/* they are at the front of the line, so they can immediately
														check out the book */
				set_end((*Employee_Pointer).get_retaining());	/* days are added to the end date each time an employee
																is added */

				set_days_added((*Employee_Pointer).get_retaining());

				//Waiting_List.push((*Employee_Pointer));	// add the employee to the queue
				Waiting_List.push((Employee_Pointer));		// add the employee to the queue

				size++;
			}
			else{
				int count = 0;			// a counter
				while (count < size)	// go through each employee
				{
					// add the days on that they'll have the book

					//days_to_wait += Waiting_List.front()->get_retaining();
					days_to_wait += Waiting_List.Index(count)->get_retaining();
					
					//days_retained += Waiting_List.front()->get_retaining();
					days_retained += Waiting_List.Index(count)->get_retaining();
					
					//Waiting_List.push(Waiting_List.front());	// keep this employee in the queue
					//Waiting_List.pop();	// switch to next employee
					count++;	// increment 
				}
				//once all employees have been accounted for
				(*Employee_Pointer).set_waiting(days_to_wait);	// set the waiting time for this employee
				set_end((*Employee_Pointer).get_retaining());	/* days are added to the end date each time an employee
													is added */
				days_retained += (*Employee_Pointer).get_retaining();
				set_days_added(days_retained);

				//Waiting_List.push((*Employee_Pointer));	// push them onto the queue
				Waiting_List.push((Employee_Pointer));	// push them onto the queue

				size++;
			}
		}
		
	}

	

	void pop_employee()  {	// always will remove from front
		if (Waiting_List.size() == 1){
			Waiting_List.pop();
			set_archived(true);	// book has circulated completely since list now has size==0
		}

		else if (Waiting_List.size() > 1){
			Employee*second; Employee*prior;
			Employee_Pointer = Waiting_List.front();
			if (Employee_Pointer->get_waiting() == 0){
				second = Waiting_List.Index(1);
				(*second).set_waiting((*Employee_Pointer).get_retaining() + (*Employee_Pointer).get_waiting());
				Waiting_List.pop();
				return;
			}

			Waiting_List.pop();
			second = Waiting_List.front();
			//prior = new Employee(*second);

			//*this->waiting = prev->waiting + prev-> retaining
			(*second).set_waiting((*Employee_Pointer).get_retaining()+(*Employee_Pointer).get_waiting());
			
			
		
			second = nullptr; prior = nullptr;
			delete second; delete prior;
		}
		else{
			return; // if size == 0; do nothing
		}
		
	}

	void print_waiting_list()	{ // will print out the book data
		int count = 0;
		int size = Waiting_List.size();
			if (size != 0){
				cout << "Title: " << get_title() << endl;
				 /*<< "Book circulation will begin : " << get_start() << endl
					<< endl;*/
				while (count < size)
				{
					// THIS WAY RUNS (but doesn't print correct output)
					/*cout << "[" << Waiting_List.front()
						<< "]" << endl;*/
					
					cout << "[" << endl;
					//Waiting_List.front()->print();
					(Waiting_List.Index(count))->print();
					cout << "]" << endl;
					
					//Waiting_List.push(Waiting_List.front());

					//Waiting_List.pop();
					count++;

					if (count < Waiting_List.size()){
						cout << "\t" << "|" << endl
							<< "\t" << "V" << endl;
					}
				}
			//	cout << "\n" << "Book circulation should end: " << get_end() << endl;
			}
			else{
				cout << "[ Title: " << get_title() << " ]" << endl;
			}
	}
};
