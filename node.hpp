#pragma once
#include <iostream>
#include <stdexcept>

template<typename T>
class BaseNode {
	public:
		BaseNode(T val = T()): _val(val) {}

		//Accessors
		T val() const { return _val; }

		//Mutators
		void val(T val) { _val = val; }
		
	private:
		T _val;
};


template<typename T>
class SNode: public BaseNode<T> {
	public:
		SNode(T val = T(), SNode<T>* nptr = nullptr): BaseNode<T>(val), _nptr(nptr) {}

		//Accessors
		SNode<T>* nptr() { return _nptr; }

		//Mutators
		void nptr(SNode<T>* ptr) { _nptr = ptr; }

	private:
		SNode<T>* _nptr;
};


template<typename T>
class DNode: public BaseNode<T> {	
	public:
		DNode(T val = T(), DNode<T>* pptr = nullptr, DNode<T>* nptr= nullptr): BaseNode<T>(val), _pptr(pptr), _nptr(nptr) {}

		//Accessors
		DNode<T>* nptr() const { return _nptr; } 
		DNode<T>* pptr() const { return _pptr; }

		//Mutators
		void nptr(DNode<T>* ptr) { _nptr = ptr; }
		void pptr(DNode<T>* ptr) { _pptr = ptr; }

	private:
		DNode<T>* _pptr;
		DNode<T>* _nptr;
};