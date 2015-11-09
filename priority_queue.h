#include <cstddef>

template<typename Item_Type>
class PriorityQueue {
private:
	// Insert implementation-specific data fields
	// Insert definition of Node here
#include "Node.h"
	// Data fields
	Node* front_of_queue;
	Node* back_of_queue;
	size_t num_items;
	bool is_empty;

public:

	PriorityQueue(Node* front_of_queue = NULL, Node* back_of_queue = NULL) :
		front_of_queue(front_of_queue), back_of_queue(back_of_queue), num_items(0) {}

	void push(const Item_Type& item) {
		if (front_of_queue == NULL) {
			back_of_queue = new Node(item, NULL);
			front_of_queue = back_of_queue;
			back_of_queue = new Node(item, NULL);
			front_of_queue = back_of_queue;
		}
		else {
			back_of_queue->next = new Node(item, NULL);
			back_of_queue = back_of_queue->next;
		}
		num_items++;
	}


	Item_Type& front() {
		return front_of_queue->data;

	}

	int size(){
		return num_items;
	}

	bool empty(){
		if (num_items == 0){
			return true;
		}
		else
			return false;
	}

	bool operator <(const PriorityQueue& other) const{
			return front_of_queue < other.front_of_queue;
	}

	void pop() {
		Node* old_front = front_of_queue;
		
		front_of_queue = front_of_queue->next;
		if (front_of_queue == NULL) {
			back_of_queue = NULL;
		}
		delete old_front;
		
		num_items--;
	}

	template <typename ItemType>
	void removeItem(const ItemType item, PriorityQueue<ItemType>& queue){
		int count = 0;
		while (count < queue.size()){
			if (queue.front() != item)
				queue.push(queue.front());

			queue.pop();
			count++;
		}
	}
	//template<typename ItemType>
	void printItems(){
		int count = 0;
		while (count < size())
		{

			cout << "[" << front() << "]";
			push(front());

			pop();
			count++;

			if (count < size()){
				cout << "<--";
			}
		}
		cout << "\n" << "\n";
	}

	void print_pointers(){
		int count = 0;
		while (count < size())
		{
			cout << "[" << endl;
			front()->print();// the object MUST have a print function for this to work
			cout << "]";
			push(front());

			pop();
			count++;

			if (count < size()){
				cout << "<--";
			}
		}
		cout << "\n" << "\n";
	}
};
