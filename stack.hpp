#include "slist.hpp"

template<typename T>
class StackInterface {
	public:
	//Accessors
	virtual bool empty() const = 0;
	virtual T top() const = 0;
	virtual void display() const = 0;

	//Mutators
	virtual void push(T val) = 0;
	virtual T pop() = 0;
};

//stack using linked list
template<typename T>
class LStack: public StackInterface<T> {
	public:
	LStack();

	bool empty() const override;
	T top() const override;
	void display() const override;
	
	void push(T val) override;
	T pop() override;

	private:
	SLList<T> _list;
};

//stack using array
template<typename T>
class AStack: public StackInterface<T> {
	public:
	AStack(int stack_capacity = 100);
	~AStack();

	bool empty() const override;
	T top() const override;
	void display() const override;

	void push(T val) override;
	T pop() override;

	private: 
	int _stack_size;
	int _stack_capacity;
	T* _arr;

	void increase_capacity();
};

#include "stack.tpp"