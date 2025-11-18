#include "node.h"

template<typename T>
class SLList {
	public:
	SLList(SNode<T>* head = nullptr): _head(head) {}
	~SLList() {
		while(head()) pop(0);
	}

	//Accessors
	int size() const {
		SNode<T>* tptr = head();
		int size = 0;
		while(tptr) {
			size++;
			tptr = tptr->nptr();
		}
		return size;
	}
	int count(T val) const {
		SNode<T>* tptr = head();
		int count = 0;
		while(tptr) {
			if(tptr->val() == val) count++;
			tptr = tptr->nptr();
		}
		return count;
	}
	bool empty() const { return head() == nullptr; }
	T front() const {
		if(head()) throw std::underflow_error("Can't get front value. List is empty");
		return head()->val();
	}
	T end() const {
		if(head()) throw std::underflow_error("Can't get end value. List is empty!");
		SNode<T>* tptr = head();
		while(tptr->nptr()) tptr->nptr(tptr->nptr);
		return tptr->val();
	}

	//Mutators
	void insert(int idx, T val) {
		SNode<T>* new_node = new SNode(val);

		if(idx == 0 || !head()) {
			new_node->nptr(head());
			head(new_node);
		}
		else if (idx > 0) {
			int idx_count = 0;
			SNode<T>* tptr = head();

			while(idx_count < idx - 1 && tptr) {
				idx_count++;
				tptr = tptr->nptr();
			}

			if(tptr) {
				new_node->nptr(tptr->nptr());
				tptr->nptr(new_node);
			}
			else {
				delete new_node;
			}
		}
	}
	T pop(int idx) {
		if(!head()) throw std::underflow_error("Trying to delete from empty list");
		if(idx < 0) throw std::invalid_argument("index value should be in range [0, size of list]");

		if(idx == 0) {
			SNode<T>* tptr = head();
			T val = tptr->val();
			head(tptr->nptr());
			delete tptr;
			tptr = nullptr;
			return val;
		} 

		int idx_count = 0;
		SNode<T>* tptr = head();

		while(idx_count < idx - 1 && tptr->nptr()) {
			idx_count++;
			tptr = tptr->nptr();
		}

		if(!tptr->nptr()) throw std::out_of_range("Index exceeds list size");

		SNode<T>* delptr = tptr->nptr();
		T val = delptr->val();
		tptr->nptr(delptr->nptr());
		delete delptr;
		delptr = nullptr;
		return val;
	}

	int erase(T val) {
		if(!head()) return 0;

		int count = 0;

		while (head() && head()->val() == val) {
			SNode<T>* tptr = head();
			head(head()->nptr());
			delete tptr;
			++count;
		}

		SNode<T>* tptr = head();
		while (tptr && tptr->nptr()) {
			if (tptr->nptr()->val() == val) {
				SNode<T>* temp = tptr->nptr();
				tptr->nptr(tptr->nptr()->nptr());
				delete temp;
				++count;
			} else {
				tptr = tptr->nptr();
			}
		}
		return count;
	}

	void reverse() {
		SNode<T>* prev = nullptr;
		SNode<T>* curr = head();
		SNode<T>* next = nullptr;

		while(curr) {
			next = curr->nptr();
			curr->nptr(prev);

			prev = curr;
			curr = next;
		}

		head(prev);
	}

	void display() const {
		std::cout << "{";
		SNode<T>* tptr = head();
		while(tptr) {
			std::cout << tptr->val() << ",";
			tptr = tptr->nptr();
		}
		std::cout << "}";
	}

	private:
	SNode<T>* _head;
	SNode<T>* head() const { return _head; }
	void head(SNode<T>* ptr) { _head = ptr; }

	void debug() const {
		std::cout << "{";
		SNode<T>* tptr = head();
		while(tptr) {
			std::cout << "\n" << tptr << ",";
			std::cout << tptr->val() << ",";
			std::cout << tptr->nptr() << ",\n";
			tptr = tptr->nptr();
		}
		std::cout << "}";
	}

};
