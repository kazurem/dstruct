#include "dlist.hpp"
	
int main() {
    DLList<int> dl;
    dl.insert(0, 1);
    dl.insert(0, 2);
    dl.insert(0, 3);

    dl.display();
}
