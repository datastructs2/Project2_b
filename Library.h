#include "Book.h"
#include "List.h"
using namespace std;

class Library{
private:
	list<Book> BookList;		// Books to be circulated to employees
	list<Book> ArchivedBooks;	// archived books; these are books already circulated

public:
	
	void add_book(Book somebook) {	// add book to BookList
		list<Book>::iterator iterator = ArchivedBooks.begin();
		bool found = false;
		while (found == false){
			while (iterator != ArchivedBooks.end()){
				if (iterator->get_title() == somebook.get_title()){
					cout << somebook.get_title() << " already circulated" << endl << endl;
					print_archived();
					found = true;
					return;
				}
				iterator++;

			}
			if (found == false){
				BookList.push_back(somebook);
				cout << somebook.get_title() << " added to library" << endl << endl;
			}

			print_BookList();
			//print_BookList();

			found = true;
			return;
		}
	}


	//void add_employee(Employee someone, Book somebook){
	void add_employee(Employee* someone, Book somebook){
		list<Book>::iterator iterator = ArchivedBooks.begin();
		
		bool found = false;
		while (found == false){
			cout << "adding employee" << endl;
			string title;
			
			cout << "checking archived books" << endl;

			while (iterator != ArchivedBooks.end()){
				title = iterator->get_title();
				if (title == somebook.get_title()){
					cout << somebook.get_title() << " found in Archived Books" << endl;
					print_archived();
					cout << "Can't add employees to Archived Books" << endl;
				
					found = true;
					return;
				}
				iterator++;
			}

			cout << "checking Books already checked out" << endl;

			iterator = BookList.begin();
			while (iterator != BookList.end()){
				title = iterator->get_title();
				if (title == somebook.get_title()){
					cout << somebook.get_title() << " found in Book List" << endl;
					
					iterator->add_employee(someone);


					if (iterator->get_size() != 0){
						//cout << "added " << someone.get_employee() << " to "
						cout << "added " << (*someone).get_employee() << " to "
							<< somebook.get_title() << " queue" << endl << endl;
					}
					
					found = true;
					return;
				}
				iterator++;
			}
			cout << "book not found" << endl << endl;
			found = true;
			return;
		}
	}

	void circulate_book(Book somebook, Date startdate){
		list<Book>::iterator iterator = BookList.begin();
		Date enddate;
		while (iterator != BookList.end()){
			if (iterator->get_title() == somebook.get_title()){
				cout << somebook.get_title() << " has begun circulation" << endl << endl;
				iterator->set_start(startdate);
				iterator->set_end(iterator->get_days_added()); 
				break;
			}
			iterator++;
		}
		enddate = iterator->get_end();
		cout << "Book circulation will begin : " << startdate.toString() << endl;
		print_BookList();
		cout << "\n";
		if (enddate == startdate)
			cout << "Book circulation should end : Can't determine currently" << endl << endl;
		else
		cout << "Book circulation should end: " << iterator->get_end() << endl << endl;
		
	}
	
	void pass_on(Book somebook , Date new_retaining_end){//, Date end_of_retaining){
		list<Book>::iterator iterator = BookList.begin();
		string title;
		bool found = false;
		while (iterator != BookList.end())  {
			title = iterator->get_title();
			if (title == somebook.get_title())  {
				found = true;
				if (iterator->get_size() > 1)  {// if this is not the only person in the waiting list
					
					iterator->set_top_retaining(new_retaining_end);
					cout << iterator->get_title() << " was passed on by: " << endl
						<< iterator->get_top() << endl;

					Employee current_employee = iterator->get_top();
					int days_held = iterator->get_top_retaining();
					
					iterator->pop_employee();
					if (current_employee.get_waiting() == 0){
						cout << "Book given to next in line:"<< endl << iterator->get_top() << endl;
					}
					else
					cout << "Book given to :" << endl<< iterator->get_top() << endl;
			
					// retaining times, and the start and end dates
					Date current_start = iterator->get_start_date();
					current_start.add_days(days_held);
					iterator->set_start(current_start);
					int days_left = iterator->get_days_added() - days_held;
					
					iterator->set_end(days_left);
					print_BookList();
					break;
				}

				else{
					iterator->set_top_retaining(new_retaining_end);

					int days_held = iterator->get_top_retaining();

					cout << iterator->get_title() << " was returned to the Library" << endl;
					cout << "Retaining was updated" << endl;
					cout << (*iterator).get_top() << endl;
						iterator->pop_employee();
						// update retaining times
						ArchivedBooks.push_back(iterator->get_title());
						BookList.erase(iterator);
						print_archived();
						break;
						
				}

			}
			iterator++;
		}

		if (found == false){
			cout << "book to pass on was not found" << endl << endl;
		}
			
		
	}
	

	void print_archived(){
		cout << "Showing Archived Books: " << endl << endl;
		if (ArchivedBooks.size() != 0){
			list<Book>::iterator iterator = ArchivedBooks.begin();
			while (iterator != ArchivedBooks.end()){
				iterator->print_waiting_list();
				iterator++;
			}
		}
		else{
			cout << "There are currently no archived books." << endl;
		}
		cout << "\n" << endl;
	}

	void print_BookList(){
		cout << "Showing Books currently checked out: " << endl << endl;
		if (BookList.size() != 0){
			list<Book>::iterator iterator = BookList.begin();
			while (iterator != BookList.end()){
				iterator->print_waiting_list();
				iterator++;
			}
		}
		else{
			cout << "There are currently no books checked out." << endl;
		}
		cout << "\n" << endl;
	}

};
