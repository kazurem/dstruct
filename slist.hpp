#pragma once
#include "node.hpp"
#include "ll_interface.hpp"

template<typename T>
class SLList: public BaseSLL<T> {
	public:
	SLList(SNode<T>* head = nullptr);
	~SLList() ;

	//Accessors
	int size() const override;
	int count(T val) const override;
	T end() const override;
	void display() const override;
	void debug() const override;
	SNode<T>* head() const override;
	void head(SNode<T>* new_head) override;

	//Mutators
	void insert(int idx, T val) override;
	T pop(int idx) override;
	int erase(T val) override;
	void reverse();

	private:
	SNode<T>* _head;

};

#include "slist.tpp"
