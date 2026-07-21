#include <iostream>
#include <cassert>

#include "vectors.h"

int main() {
    std::cout << "===[ Test Suite A for my Vector implementation. ]====================" << std::endl;

    //Let's declare a Vector right here...
    std::cout << "Declaring our Vector variable..." << std::endl;
    Vector<int> vector;
    std::cout << "Checking if the size is equal to zero..." << std::endl;
    assert(vector.size() == 0);
    std::cout << "Checking if the capacity is equal to zero..." << std::endl;
    assert(vector.capacity() == 0);
    std::cout << "Making sure that the vector is empty..." << std::endl;
    assert(vector.empty() == true);

    std::cout << "Looks like all tests have passed!" << std::endl;
}