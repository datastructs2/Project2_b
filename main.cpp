#include "Library.h"
using namespace std;

int main(){


	Library library;
	
	Employee Ann = Employee("Ann");
	Employee Sam = Employee("Sam");
	Employee Adam = Employee("Adam");

	Employee* Employee_P;
	Employee_P = &Ann;

	Book SE = Book("Software Engineering");
	Book Chem = Book("Chemistry");

	library.add_book(SE);

	library.add_employee(Employee_P, SE);
	Employee_P = &Sam;
	library.add_employee(Employee_P, SE);
	Employee_P = &Adam;
	library.add_employee(Employee_P, SE);

	library.circulate_book(SE, Date(2015, 3, 1, DateFormat::US)); // begin circulation
	library.pass_on(SE, Date(2015, 3, 10, DateFormat::US));
	library.pass_on(SE, Date(2015, 3, 12, DateFormat::US));
	library.pass_on(SE, Date(2015, 3, 15, DateFormat::US));

	library.add_book(Chem);
	Employee_P = &Ann;
	library.add_employee(Employee_P, Chem);
	Employee_P = &Sam;
	library.add_employee(Employee_P, Chem);
	Employee_P = &Adam;
	library.add_employee(Employee_P, Chem);
	library.circulate_book(Chem, Date(2015, 3, 1, DateFormat::US)); // begin circulation
	library.pass_on(Chem, Date(2015, 3, 10, DateFormat::US));
	library.pass_on(Chem, Date(2015, 3, 12, DateFormat::US));
	library.pass_on(Chem, Date(2015, 3, 15, DateFormat::US));

	Employee_P = nullptr;
	delete Employee_P;

	system("pause");
	return 0;
}
