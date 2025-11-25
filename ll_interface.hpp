#include "node.hpp"

template<typename T>
class BaseLL {
	public:
	//Accessors
	virtual int size() const = 0;
	virtual int count(T val) const = 0;
	virtual bool empty() const = 0;
	virtual T front() const = 0;
	virtual T end() const = 0;
	virtual void display() const = 0;
	virtual void debug() const = 0;

	virtual void insert(int idx, T val) = 0;
	virtual T pop(int idx) = 0;
	virtual int erase(T val) = 0;
};

template<typename T>
class BaseSLL: public BaseLL<T> {
	public:
	bool empty() const override { return head() == nullptr; }
	T front() const override {
		if(!head()) throw std::underflow_error("Can't get front value. List is empty");
		return head()->val();
	}
	
	virtual SNode<T>* head() const = 0;
	virtual void head(SNode<T>* new_head) = 0;
};

template<typename T>
class BaseDLL: public BaseLL<T> {
	public:
	bool empty() const override { return head() == nullptr; }
	T front() const override {
		if(!head()) throw std::underflow_error("Can't get front value. List is empty");
		return head()->val();
	}
	
	virtual DNode<T>* head() const = 0;
	virtual void head(DNode<T>* new_head) = 0;
};