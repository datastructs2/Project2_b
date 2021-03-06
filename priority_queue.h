#include <vector>
#include <functional>

using namespace std;

template<typename Item_Type, typename Compare = std::less<Item_Type> >
class priority_queue{
public:
	priority_queue() {};

	void push(const Item_Type& item);
	void pop();
	const Item_Type& front() const { return the_data.front(); }
	const Item_Type& Index(int index) const{ return the_data[index]; }


	int size() const { return the_data.size(); }

	bool empty() const { return the_data.empty(); }

	void printItems(){
		int count = 0;
		while (count < size())
		{

			cout << "[" << the_data[count] << "]";
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
			cout << "[";
			(the_data[count])->print();
			cout << "]";
			
			count++;

			if (count < size()){
				cout << "<--";
			}
		}
		cout << "\n" << "\n";
	}

	//change priority based on index
	void change_priority(int index, Item_Type new_priority){

		the_data[index] = new_priority;
		//compare with parent
		int parent = (index - 1) / 2;
		int child = index;
		bool swap = false;

		while (parent >= 0
			&& comp(the_data[parent], the_data[child])) {
			std::swap(the_data[child], the_data[parent]);
			child = parent;
			parent = (child - 1) / 2;
			swap = true;
		}

		//if we made a swap we don't need to go down
		if (!swap){
			parent = index;

			while (true) {
				int left_child = 2 * parent + 1;
				if (left_child >= size()) break; // out of heap
				int right_child = left_child + 1;
				int max_child = left_child;
				if (right_child < size()
					&& comp(the_data[left_child], the_data[right_child]))
					max_child = right_child;
				if (comp(the_data[parent], the_data[max_child])) {
					std::swap(the_data[max_child], the_data[parent]);
					parent = max_child;
				}
				else break;
			}
		}
	}

private:
	Compare comp;
	vector<Item_Type> the_data;
};


template<typename Item_Type, typename Compare>
void priority_queue<Item_Type, Compare>::pop() {
	if (size() == 1) { 
		the_data.pop_back(); 
		return; 
	}
	std::swap(the_data[0], the_data[size() - 1]);
	the_data.pop_back();
	int parent = 0;
	while (true) {
		int left_child = 2 * parent + 1;
		if (left_child >= size()) break; // out of heap
		int right_child = left_child + 1;
		int max_child = left_child;
		if (right_child < size()
			&& comp(the_data[left_child], the_data[right_child]))
			max_child = right_child;
		if (comp(the_data[parent], the_data[max_child])) {
			std::swap(the_data[max_child], the_data[parent]);
			parent = max_child;
		}
		else break;
	}


}

template<typename Item_Type, typename Compare>
void priority_queue < Item_Type, Compare > ::push(const Item_Type& item) {
	the_data.push_back(item);
	int child = size() - 1;
	int parent = (child - 1) / 2;
	// Reheap
	while (parent >= 0
		&& comp(the_data[parent], the_data[child])) {
		std::swap(the_data[child], the_data[parent]);
		child = parent;
		parent = (child - 1) / 2;
	}
}


