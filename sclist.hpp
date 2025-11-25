#pragma once
#include "node.hpp"

template<typename T>
class SCLList {
	public:
	SCLList(SNode<T>* head = nullptr);

	//Accessors
	int size() const;
	int count(T val) const;
	void display(bool debug = false) const;

	//Mutators
	void insert(int idx, T val);
	void pop(int idx);
	int erase(T val);

	private:
	SNode<T>* _head;
	SNode<T>* head() const;
	SNode<T>* tail() const;
	void head(SNode<T>* ptr);
};

#include "sclist.tpp"