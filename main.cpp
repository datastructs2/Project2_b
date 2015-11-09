#include "Library.h"
//#include "queue.h"
//#include <iostream>
using namespace std;

int main(){
	int days_to_wait = 10;
	Employee Employee1 = Employee("Bob");
	/*cout << "Name: " << Employee1.get_employee() << endl
		<< "Waiting time: " << Employee1.get_waiting() << endl
		<< "Time to have book: " << Employee1.get_retaining() << endl << endl;*/
	//cout << Employee1;
	

	/*string isArchived;
	Book NewBook = Book("Lion King", Date(2015, 3, 1, DateFormat::US));
	if (NewBook.get_archived() == true){
		isArchived = "true";
	}
	else{
		isArchived = "false";
	}
	*/
	/*cout << "Title: " << NewBook.get_title() << endl
		<< "Currently in Library: " << isArchived << endl
		<< "Will begin circulating: " << NewBook.get_start() << endl << endl;*/
	
	Employee Employee2 = Employee("Sarah");
	Employee Employee3 = Employee("Jake From State Farm");
	//queue<Employee> Employee_Queue;
	//Employee_Queue.push(Employee1);
	//Employee_Queue.push(Employee2);
	
	/*NewBook.add_employee(Employee1);
	NewBook.add_employee(Employee2);
	NewBook.add_employee(Employee3);*/
	//NewBook.print_waiting_list();

	Library library;

	//Book Book2 = Book ("Book2", Date(2015, 3, 1, DateFormat::US));
	//Book Book3 = Book("Book3", Date(2015, 3, 1, DateFormat::US));
	Book Book2 = Book("Book2");
	Book Book3 = Book("Book3");

	library.add_book(Book2);
	//library.add_book(Book2);
	//library.add_book(Book3);
	//library.print_archived();
	
	library.add_employee(Employee1, Book2);
	library.circulate_book(Book2, Date(2014, 3, 1, DateFormat::US));
	
	
	library.add_employee(Employee2, Book2);
	library.add_employee(Employee3, Book2);
	library.circulate_book(Book2, Date(2014, 10, 1, DateFormat::US));
	
	library.add_book(Book2);


	system("pause");
	//library.delete_all();
	return 0;
}
