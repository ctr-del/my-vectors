#include <iostream>
#include <string>
#include <utility>
#include <cassert>
#include <algorithm>

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

    template <typename T>
    void print_compare_vector(const Vector<T>& vector_a, const Vector<T> vector_b){
        const std::size_t loop_size = std::max(vector_a.size(), vector_b.size());
        std::cout << "[===VECTOR COMPARISON===]" << std::endl;
        for (std::size_t i = 0; i < loop_size; i++){
            try {
                std::cout << vector_a[i];
            } catch (const std::out_of_range& e){
                std::cout << "<empty>";
            }

            std::cout << " -> ";

            try {
                std::cout << vector_b[i];
            } catch (const std::out_of_range& e){
                std::cout << "<empty>";
            }
            std::cout << std::endl;
        }
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

    std::cout << "Testing resize()...";
    {
        vector.resize(86);
        assert(vector.capacity() == 86);
        assert(vector.size() == 86);
    }
    ok();

    std::cout << "Iterator testing" << std::endl;

    std::cout << "Iterating through the Vector we already have..." << std::endl;
    for (std::string element : vector){
        std::cout << element << " ";
    }
    std::cout << std::endl;
    ok();

    {
        std::cout << "Creating a const Vector to test const iterators...";
        const Vector<int> const_vector ({3, 5, 17, 4, 9, 12, 3, 2, 19, 92, 5, 2, 9});
        ok();

        std::cout << "Iterating through the const Vector list we have..." << std::endl;
        for (const auto element : const_vector) {
            std::cout << element << " ";
        }
        ok();
    }

    {
        std::cout << "Testing copy constructor and copy assignment..." << std::endl;
        Vector<int> original ({3, 7, 5, 8, 12});
        std::cout << "Trying to copy the original with a copy constructor..." << std::endl;
        Vector<int> copyA (original);
        std::cout << "Making a few changes to the copy to confirm it is indeed a copy..." << std::endl;
        copyA[1] = 9;
        copyA[3] = 2;
        std::cout << "Comparing..." << std::endl;
        debug::print_compare_vector(original, copyA);
        std::cout << "Testing copy assignment..." << std::endl;
        Vector<int> copyB ({102, 151, 522, 913});
        debug::print_compare_vector(copyB, original);
        copyB = original;
        debug::print_compare_vector(copyB, original);
        copyB = copyA;
        debug::print_compare_vector(copyB, original);
    }

    std::cout << "Looks like all tests have passed!" << std::endl;
}