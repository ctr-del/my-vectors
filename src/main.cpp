#include <iostream>
#include <string>
#include <utility>
#include <cassert>
#include <algorithm>
#include <format>

#include "vectors.h"
#include "test.h"
#include "test_failure_codes.h"

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
                std::cout << vector_a.at(i);
            } catch (const std::out_of_range& e){
                std::cout << "<empty>";
            }

            std::cout << " -> ";

            try {
                std::cout << vector_b.at(i);
            } catch (const std::out_of_range& e){
                std::cout << "<empty>";
            }
            std::cout << std::endl;
        }
    }
}

void ok(){
    std::cout << "Ok." << std::endl;
}

int main() {
    #ifndef NDEBUG
    std::cout << "Vector Test Suite 2.0" << std::endl;

    //Vector Construction Tests...
    Test tVectorBlankInitTest("tVectorBlankInitTest", []() -> TestResult {
        //Initialize the empty vector
        Vector<int> vector;
        if(vector.size() != 0) {
            return TestResult(T_FAILURE_TO_INITIALIZE_BLANK, std::format("Broken blank initialization. Was expecting a size of 0 but got {} instead.", vector.size()));
        }

        if(vector.capacity() != 0) {
            return TestResult(T_FAILURE_TO_INITIALIZE_BLANK, std::format("Broken blank initialization. Was expecting 0 capacity of 0 but got {} instead.", vector.capacity()));
        }

        return TestResult(T_SUCCESS);
    });

    Test tVectorInitializerListConstructor("tVectorInitializerListConstructor", []() -> TestResult {
        std::initializer_list<std::string> init_list = {
            "banana",
            "orange",
            "pineapple",
            "cherry",
            "pear"
        };
        Vector<std::string> vector (init_list);

        //Is the size correct?
        if(vector.size() != 5) {
            return TestResult(T_FAILURE_TO_INITIALIZE_INIT_LIST, std::format("Vector initiliazer list constructor failed. Vector size was expected to be 5 but it's {}.", vector.size()));
        }

        //Is the capacity correct?
        if(vector.capacity() != 8) {
            return TestResult(T_FAILURE_TO_INITIALIZE_INIT_LIST, std::format("Vector initiliazer list constructor failed. Vector capacity was expected to be 8 but it's {}.", vector.capacity()));
        }

        return TestResult(T_SUCCESS);
    });

    Test tVectorCopyConstructor("tVectorCopyConstructor", []() -> TestResult {
        Vector<int> vector_a ({
            4,
            7,
            9,
            4,
            3,
            2
        });

        Vector<int> vector_b (vector_a);

        for(std::size_t i = 0; i < vector_a.size(); i++){
            if(vector_a[i] != vector_b[i]){
                return TestResult(T_COPY_CONSTRUCT_MISMATCH, "Vector copy constructor failed. Vector a does not have the same elements as vector b.");
            }
        }

        vector_b[2] = 5;

        if(vector_a[2] == vector_b[2]){
            debug::print_compare_vector(vector_a, vector_b);
            return TestResult(T_COPY_CONSTRUCT_MISMATCH, "Vector copy constructor failed. Vector b is a shallow copy of vector b instead of a deep copy.");
        }

        return TestResult(T_SUCCESS);
    });

    Test::run_all();
    #else
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
        Vector<int> copyB ({102, 151, 522, 913, 210, 513, 512});
        debug::print_compare_vector(copyB, original);
        copyB = original;
        debug::print_compare_vector(copyB, original);
        copyB = copyA;
        debug::print_compare_vector(copyB, original);
    }

    {
        std::cout << "Testing move constructor and move assignment..." << std::endl;
        Vector<int> original ({13, 57, 82, 13, 52});
        debug::print_vector(original);
        Vector<int> moved_vector (std::move(original));
        debug::print_compare_vector(original, moved_vector);
        std::cout << "Repopulating original list..." << std::endl;
        original.push_back(12);
        original.push_back(34);
        original.push_back(26);
        original.push_back(9);
        debug::print_compare_vector(original, moved_vector);
        std::cout << "Testing move assignment operator..." << std::endl;
        moved_vector = std::move(original);
        debug::print_compare_vector(original, moved_vector);
    }

    std::cout << "Looks like all tests have passed!" << std::endl;
    #endif
}