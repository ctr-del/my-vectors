#include <iostream>
#include <cassert>

#include "vectors.h"

int main() {
    std::cout << "Test Suite A for my Vector implementation." << std::endl;

    //Let's declare a Vector right here...
    Vector<int> vector;
    assert(vector.size() == 0);
    assert(vector.capacity() == 0);
}