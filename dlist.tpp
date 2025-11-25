#include "dlist.hpp"

template<typename T>
DLList<T>::DLList(DNode<T>* head): _head(head) {}

//Accessors
template<typename T>
int DLList<T>::size() const {
	DNode<T>* tptr = head();
	int size = 0;
	while(tptr) {
		size++;
		tptr = tptr->nptr();
	}
	return size;
};
template<typename T>
T DLList<T>::end() const {
	if(!head()) throw std::underflow_error("Can't get end value. List is empty!");
	DNode<T>* tptr = head();
	while(tptr->nptr()) tptr = tptr->nptr();
	return tptr->val();
}
template<typename T>
int DLList<T>::count(T val) const {
	DNode<T>* tptr = head();
	int count = 0;
	while(tptr) {
		if(tptr->val() == val) count++;
		tptr = tptr->nptr();
	}
	return count;
};
template<typename T>
void DLList<T>::display() const {
	std::cout << "{";
	DNode<T>* tmp_ptr = head();
	while(tmp_ptr) {
		std::cout << tmp_ptr->val() << ", ";
		tmp_ptr = tmp_ptr->nptr();
	}
	std::cout << "}";
}
template<typename T>
void DLList<T>::debug() const {
	std::cout << "{";
	DNode<T>* tptr = head();
	while(tptr) {
		std::cout << "\n" << tptr->pptr() << ",";
		std::cout << tptr->val() << "(" << tptr << "),";
		std::cout << tptr->nptr() << ",\n";
		tptr = tptr->nptr();
	}
	std::cout << "}";
}

//Mutators
template<typename T>
void DLList<T>::insert(int idx, T val) {
	if(idx < 0 || idx > size()) throw std::out_of_range("Index range out of range");
	DNode<T>* new_node = new DNode<T>(val);

	if(idx == 0 || !head()) {
		new_node->nptr(head());
		if(head()) head()->pptr(new_node); 
		head(new_node);
	}
	else if(idx > 0) {
		int idx_count = 0;
		DNode<T>* tmp_ptr = head();

		while(idx_count < idx - 1) {
			idx_count++;
			tmp_ptr = tmp_ptr->nptr();
		}

		new_node->nptr(tmp_ptr->nptr());
		new_node->pptr(tmp_ptr);
		tmp_ptr->nptr(new_node);
		if(new_node->nptr()) {
			new_node->nptr()->pptr(new_node);
		}
	}
}
template<typename T>
T DLList<T>::pop(int idx) {
	if(!head()) { throw std::underflow_error("Trying to delete from empty list"); }
	if(idx < 0 || idx >= size()) throw std::out_of_range("Index range out of range");

	DNode<T>* tmp_ptr = head();
	if(idx == 0) {
		T val = tmp_ptr->val();
		head(tmp_ptr->nptr());
		if(head()) head()->pptr(nullptr);
		delete tmp_ptr;
		tmp_ptr = nullptr;
		return val;
	} 
	else {
		int idx_count = 0;

		while(idx_count < idx - 1 && tmp_ptr) {
			idx_count++;
			tmp_ptr = tmp_ptr->nptr();
		}

		if(tmp_ptr) {
			DNode<T>* anthr_tmp_ptr = tmp_ptr->nptr();
			T val = anthr_tmp_ptr->val();
			tmp_ptr->nptr(anthr_tmp_ptr->nptr());
			if(tmp_ptr->nptr()) tmp_ptr->nptr()->pptr(tmp_ptr);
			delete anthr_tmp_ptr;
			anthr_tmp_ptr = nullptr;
			return val;
		}
	}
};
template<typename T>
int DLList<T>::erase(T val) {
	if(!head()) return 0;

	int count = 0;
	int idx_count = 0;
	DNode<T>* tmp_ptr = head();
	while(tmp_ptr) {
		if(tmp_ptr->val() == val) { 
			tmp_ptr = tmp_ptr->nptr();
			pop(idx_count);
			count++;
			idx_count--;
		}
		else {
			tmp_ptr = tmp_ptr->nptr();
		}
		idx_count++;
	}
	return count;
}


template<typename T>
DNode<T>* DLList<T>::head() const { return _head; }
template<typename T>
void DLList<T>::head(DNode<T>* ptr) { _head = ptr; }

