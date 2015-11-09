#include "Book.h"
#include "List.h"
using namespace std;

class Library{
private:
	list<Book> BookList;		// Books to be circulated to employees
	list<Book> ArchivedBooks;	// archived books

public:
	
	void add_book(Book somebook) {	// add book to archived Books
		list<Book>::iterator iterator = ArchivedBooks.begin();
		bool found = false;
		while (found == false){
			while (iterator != ArchivedBooks.end()){
				if (iterator->get_title() == somebook.get_title()){
					cout << somebook.get_title() << " already here" << endl << endl;
					found = true;
					return;
				}
				iterator++;

			}
			if (found == false){
				ArchivedBooks.push_back(somebook);
				cout << somebook.get_title() << " added to library" << endl << endl;
			}

			print_archived();
			//print_BookList();

			found = true;
			return;
		}
	}

	void add_employee(Employee someone, Book somebook){
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
					somebook.add_employee(someone);
					if (somebook.get_size() != 0){
						cout << "added " << someone.get_employee() << " to "
							<< somebook.get_title() << " queue" << endl;
					}
					BookList.push_back(somebook);
					ArchivedBooks.erase(iterator);
					cout << somebook.get_title() << " was removed from Archived." << endl << endl;
					print_archived();
					//print_BookList();
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
					///????? Are there other books with same title and less of a line?
					
					iterator->add_employee(someone);


					if (somebook.get_size() != 0){
						cout << "added " << someone.get_employee() << " to "
							<< somebook.get_title() << " queue" << endl << endl;
					}
					
					//print_BookList();
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
		while (iterator != BookList.end()){
			if (iterator->get_title() == somebook.get_title()){
				iterator->set_start(startdate);
				iterator->set_end(iterator->get_days_added());
			}
			iterator++;
		}

		print_BookList();
	}
	
	void pass_on(Book somebook, Date end_of_retaining){
		if (somebook.get_size() == 1){	// if this is the only person in the waiting list
			somebook.pop_employee();	// then empty the queue
			add_book(somebook);			// and return the book to archived books
		}
		else{
			// ?????????????????? book gets handed to the next person who has highest priority
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

	void delete_all(){
		if (BookList.size() != 0){
			list<Book>::iterator iterator = BookList.begin();
			while (iterator != BookList.end()){
				iterator->manual_delete();
				iterator++;
			}
		}
	}

};
