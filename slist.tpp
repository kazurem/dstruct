template<typename T>
SLList<T>::SLList(SNode<T>* head): _head(head) {}
template<typename T>
SLList<T>::~SLList() {
	while(head()) pop(0);
}

//Accessors
template<typename T>
int SLList<T>::size() const {
	SNode<T>* tptr = head();
	int size = 0;
	while(tptr) {
		size++;
		tptr = tptr->nptr();
	}
	return size;
}
template<typename T>
int SLList<T>::count(T val) const {
	SNode<T>* tptr = head();
	int count = 0;
	while(tptr) {
		if(tptr->val() == val) count++;
		tptr = tptr->nptr();
	}
	return count;
}
template<typename T>
T SLList<T>::end() const {
	if(!head()) throw std::underflow_error("Can't get end value. List is empty!");
	SNode<T>* tptr = head();
	while(tptr->nptr()) tptr = tptr->nptr();
	return tptr->val();
}
template<typename T>
SNode<T>* SLList<T>::head() const { return _head; }
template<typename T>
void SLList<T>::head(SNode<T>* new_head) { _head = new_head; } 
template<typename T>
void SLList<T>::display() const {
	std::cout << "{";
	SNode<T>* tptr = head();
	while(tptr) {
		std::cout << tptr->val() << ",";
		tptr = tptr->nptr();
	}
	std::cout << "}";
}
template<typename T>
void SLList<T>::debug() const {
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

//Mutators
template<typename T>
void SLList<T>::insert(int idx, T val) {
	if(idx < 0 || idx > size()) throw std::out_of_range("Index out of range");
	SNode<T>* new_node = new SNode<T>(val);

	if(idx == 0 || !head()) {
		new_node->nptr(head());
		head(new_node);
	}
	else {
		int idx_count = 0;
		SNode<T>* tptr = head();

		while(idx_count < idx - 1) {
			idx_count++;
			tptr = tptr->nptr();
		}

		new_node->nptr(tptr->nptr());
		tptr->nptr(new_node);
	}
}
template<typename T>
T SLList<T>::pop(int idx) {
	if(!head()) throw std::underflow_error("Trying to delete from empty list");
	if(idx < 0 || idx >= size()) throw std::out_of_range("index value out of range");

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

	while(idx_count < idx - 1) {
		idx_count++;
		tptr = tptr->nptr();
	}

	SNode<T>* delptr = tptr->nptr();
	T val = delptr->val();
	tptr->nptr(delptr->nptr());
	delete delptr;
	delptr = nullptr;
	return val;
}
template<typename T>
int SLList<T>::erase(T val) {
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
template<typename T>
void SLList<T>::reverse() {
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
