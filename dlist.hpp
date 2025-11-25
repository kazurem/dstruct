#pragma once
#include "node.hpp"
#include "ll_interface.hpp"

template<typename T>
class DLList: public BaseDLL<T> {
	public:
	DLList(DNode<T>* head = nullptr);

	//Accessors
	int size() const override;
	T end() const override;
	int count(T val) const override;
	void display() const override;
	void debug() const override;

	//Mutators
	void insert(int idx, T val) override;
	T pop(int idx) override;
	int erase(T val) override;

	private:
	DNode<T>* _head;
	DNode<T>* head() const override;
	void head(DNode<T>* ptr) override;
};

#include "dlist.tpp"
