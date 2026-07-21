#include <iostream>
#include <string>
#include <utility>
#include <cassert>

#include "vectors.h"

void ok(){
    std::cout << "Ok." << std::endl;
}

namespace debug {
    template <typename T>
    void print_vector(const Vector<T>& v){
        std::cout << "[=====VECTOR PRINT : =====]" << std::endl;
        for (std::size_t i = 0; i < v.size(); i++){
            std::cout << v[i] << std::endl;
        }
        std::cout << "[=========================]" << std::endl;
    }
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
    debug::print_vector(vector);

    std::cout << "Checking to see if the size is equal to 5...";
    assert(vector.size() == 5);
    ok();

    std::cout << "Checking to see if the capacity is equal to 8...";
    assert(vector.capacity() == 8);
    ok();

    std::cout << "Checking [] operators: " << std::endl;
    std::cout << "Element 0 is Mayonaise...";
    assert(vector[0] == "Mayonaise");
    ok();

    std::cout << "Element 3 is Brocolli...";
    assert(vector[3] == "Brocolli");
    ok();

    std::cout << "Testing popback()...";
    vector.pop_back();
    assert(vector.size() == 4);
    ok();
    debug::print_vector(vector);

    std::cout << "Testing clear()...";
    vector.clear();
    assert(vector.empty());
    ok();

    std::cout << "Populating the vector again...";
    vector.push_back("Pineapple");
    vector.push_back("Lemon");
    vector.push_back("Pear");
    vector.push_back("Seabear");
    vector.push_back("Tangerine");
    vector.push_back("Salmon");
    ok();
    debug::print_vector(vector);

    std::cout << "Testing reserve()...";
    {
        vector.reserve(64);
        assert(vector.capacity() == 64);
    }
    ok();


    std::cout << "Looks like all tests have passed!" << std::endl;
}