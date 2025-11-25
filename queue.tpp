template <typename T>
LQueue<T>::LQueue() : _list() {}

template <typename T>
bool LQueue<T>::empty() const { return _list.empty(); }
template <typename T>
T LQueue<T>::front() const {
	if (empty())
		throw std::underflow_error("Trying to get front value from empty Queue!");
	return _list.front();
}
template <typename T>
void LQueue<T>::display() const { _list.display(); }

template <typename T>
void LQueue<T>::enqueue(T val) { _list.insert(_list.size(), val); }
template <typename T>
T LQueue<T>::dequeue() {
	if (empty())
		throw std::underflow_error("Trying to pop from empty Queue!");
	return _list.pop(0);
}


template <typename T>
AQueue<T>::AQueue(int queue_capacity) : _queue_capacity(queue_capacity), _queue_size(0), _head(0), _tail(0), _arr(new T[std::max(0, queue_capacity)]) {}

template <typename T>
bool AQueue<T>::empty() const { return _queue_size == 0; }
template <typename T>
T AQueue<T>::front() const {
	if (empty())
		throw std::underflow_error("Trying to get front value from empty array");
	return _arr[_head];
}
template <typename T>
void AQueue<T>::display() const {
	std::cout << "{";
	for(int i = 0; i < _queue_size; i++) {
		std::cout << _arr[(_head + i) % _queue_capacity] << ",";
	}
	std::cout << "}";
}

template <typename T>
void AQueue<T>::enqueue(T val) {
	if (_queue_size == _queue_capacity)
		increase_capacity();
    _arr[_tail] = val; 
    _tail = (_tail + 1) % _queue_capacity;
    _queue_size++;
}
template <typename T>
T AQueue<T>::dequeue() {
	if (empty()) throw std::underflow_error("Trying to pop from empty Queue!");
	T val = _arr[_head];
	_head = (_head + 1) % _queue_capacity;
	_queue_size--;
	return val;
}

template <typename T>
void AQueue<T>::increase_capacity() {
	int old_capacity = _queue_capacity;
	_queue_capacity *= 2;
	T *new_arr = new T[_queue_capacity];

	for (int i = 0; i < _queue_size; i++) {
        int old_index = (_head + i) % old_capacity; 
        new_arr[i] = _arr[old_index];
    }
    delete[] _arr;
    _arr = new_arr;
    _head = 0;
    _tail = _queue_size;
}

