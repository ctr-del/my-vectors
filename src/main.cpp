#include <iostream>
#include <string>
#include <cassert>

#include "vectors.h"

void ok(){
    //std::cout << "Ok." << std::endl;
}

int main() {
    std::cout << "===[ Test Suite A for my Vector implementation. ]====================" << std::endl;

    std::cout << "Declaring our Vector variable...";
    Vector<std::string> vector;
    ok();

    std::cout << "Checking if the size is equal to zero...";
    assert(vector.size() == 0);
    ok();

    std::cout << "Checking if the capacity is equal to zero...";
    assert(vector.capacity() == 0);
    ok();

    std::cout << "Making sure that the vector is empty...";
    assert(vector.empty() == true);
    ok();


    std::cout << "===[ Test Suit B for my Vector implementation. ]=====================" << std::endl;

    std::cout << "Trying to add a few elements to the vector...";
    vector.push_back("Mayonaise");
    vector.push_back("Mustard");
    vector.push_back("Ketchup");
    vector.push_back("Brocolli");
    vector.push_back("Tomato");
    ok();

    std::cout << "Checking to see if the size is equal to 5...";
    assert(vector.size() == 5);
    ok();

    std::cout << "Checking to see if the capacity is equal to 8...";
    assert(vector.capacity() == 8);
    ok();

    std::cout << "Checking [] operators.";
    std::cout << "Element 0 is Mayonaise...";
    assert(vector[0] == "Mayonaise");
    ok();

    std::cout << "Element 4 is Brocolli...";
    assert(vector[4] == "Brocolli");
    ok();

    std::cout << "Looks like all tests have passed!" << std::endl;
}