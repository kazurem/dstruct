#include "slist.cpp"

//stack using linked list
template<typename T>
class LStack {
	public:
	LStack(): _list() {}

	bool empty() const { return _list.empty(); }
	T top() const { 
		if(empty()) throw std::underflow_error("Trying to get top value from empty stack!");
		return _list.front(); 
	}
	void push(T val) { _list.insert(0, val); }
	T pop() { 
		if(empty()) throw std::underflow_error("Trying to pop from empty stack!");
		return _list.pop(0); 
	}
	void display() const { _list.display(); }

	private:
	SLList<T> _list;
};

//stack using array
template<typename T>
class AStack {
	public:
	AStack(int stack_capacity = 100): _stack_size(0), _stack_capacity(stack_capacity), _arr(new T[std::max(0, _stack_capacity)]) {}
	~AStack() { delete[] _arr; }

	bool empty() { return _stack_size == 0; }
	T top() const {
		if(empty()) throw std::underflow_error("Trying to get top value from empty stack!");
		return _arr[_stack_size-1];
	}
	void push(T val) {
		if(_stack_size == _stack_capacity) increase_capacity();
		_arr[_stack_size++] = val;
	}
	T pop() {
		if(empty()) throw std::underflow_error("Trying to pop from empty stack!");
		return _arr[--_stack_size];
	}
	void display() const {
		std::cout << "{";
		for(int i = _stack_size - 1; i >= 0; i--) {
			std::cout << _arr[i] << ", ";
		}
		std::cout << "}";
	}

	private: 
	int _stack_size;
	int _stack_capacity;
	T* _arr;

	void increase_capacity() {
		_stack_capacity = 2*_stack_capacity;
		T* new_arr = new T[_stack_capacity];
		for(int i = 0; i < _stack_size; i++) new_arr[i] = _arr[i];
		delete[] _arr;
		_arr = new_arr;
	}
};
