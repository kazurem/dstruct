#include <iostream>
#include <vector>
#include <list>


//requires expression to check indexibility
template<template<typename ...> class Container>
static auto is_indexible() -> bool { return requires (Container<> cont) { cont[0]; }; }

//requires expression to check if std::advance works
template<template<typename ...> class Container>
static auto is_advanceable() -> bool { 
	return requires (Container<> cont) { 
		std::advance(cont.begin(), 1); 
	}; 
}


int main() {
	
}
