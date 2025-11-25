#include "slist.hpp"

template<typename T>
class QueueInterface {
	public:
	// Accessors
	virtual bool empty() const = 0;
	virtual T front() const = 0;
	virtual void display() const = 0;

	// Mutators
	virtual void enqueue(T val) = 0;
	virtual T dequeue() = 0;
};

template <typename T>
class LQueue: public QueueInterface<T> {
public:
	LQueue();

	bool empty() const override;
	T front() const override;
	void display() const override;

	void enqueue(T val) override;
	T dequeue() override;

private:
	SLList<T> _list;
};

template <typename T>
class AQueue: public QueueInterface<T> {
public:
	AQueue(int queue_capacity = 100);

	bool empty() const override;
	T front() const override;
	void display() const override;

	// Mutators
	void enqueue(T val) override;
	T dequeue() override;

private:
	int _queue_capacity;
	int _queue_size;
	int _head;
	int _tail;
	T *_arr;

	void increase_capacity();
};

#include "queue.tpp"