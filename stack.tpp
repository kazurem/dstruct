//stack using linked list
template<typename T>
LStack<T>::LStack(): _list() {}

template<typename T>
bool LStack<T>::empty() const { return _list.empty(); }
template<typename T>
T LStack<T>::top() const { 
	if(empty()) throw std::underflow_error("Trying to get top value from empty stack!");
	return _list.front(); 
}
template<typename T>
void LStack<T>::display() const { _list.display(); }
template<typename T>

void LStack<T>::push(T val) { _list.insert(0, val); }
template<typename T>
T LStack<T>::pop() { 
	if(empty()) throw std::underflow_error("Trying to pop from empty stack!");
	return _list.pop(0); 
}


//stack using array
template<typename T>
AStack<T>::AStack(int stack_capacity): _stack_size(0), _stack_capacity(stack_capacity), _arr(new T[std::max(0, _stack_capacity)]) {}
template<typename T>
AStack<T>::~AStack() { delete[] _arr; }

template<typename T>
bool AStack<T>::empty() const { return _stack_size == 0; }
template<typename T>
T AStack<T>::top() const {
	if(empty()) throw std::underflow_error("Trying to get top value from empty stack!");
	return _arr[_stack_size-1];
}
template<typename T>
void AStack<T>::display() const {
	std::cout << "{";
	for(int i = _stack_size - 1; i >= 0; i--) {
		std::cout << _arr[i] << ",";
	}
	std::cout << "}";
}
template<typename T>
void AStack<T>::push(T val) {
	if(_stack_size == _stack_capacity) increase_capacity();
	_arr[_stack_size++] = val;
}
template<typename T>
T AStack<T>::pop() {
	if(empty()) throw std::underflow_error("Trying to pop from empty stack!");
	return _arr[--_stack_size];
}

template<typename T>
void AStack<T>::increase_capacity() {
	_stack_capacity = 2*_stack_capacity;
	T* new_arr = new T[_stack_capacity];
	for(int i = 0; i < _stack_size; i++) new_arr[i] = _arr[i];
	delete[] _arr;
	_arr = new_arr;
}

