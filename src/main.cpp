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
            std::cout << std::endl << "[=======================]" << std::endl;
        }
    }
}

int main() {
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
        //Variable initialization...
        Vector<int> vector_a ({
            4,
            7,
            9,
            4,
            3,
            2
        });

        Vector<int> vector_b (vector_a);

        //Check to if the size and capacity carried over properly and if it didn't return a failed TestResult.
        if(
            vector_a.size() != vector_b.size() ||
            vector_a.capacity() != vector_b.capacity()
        ){
            return TestResult(T_COPY_CONSTRUCT_MISMATCH,"Vector size or capacity mismatch indicated vector was not copied correctly.");
        }
        //Check to see if all the contents copied properly and if it didn't return a failed TestResult.
        for(std::size_t i = 0; i < vector_a.size(); i++){
            if(vector_a[i] != vector_b[i]){
                return TestResult(T_COPY_CONSTRUCT_MISMATCH, std::format("Vector copy constructor failed. Vector a mismatch at index {}.", i));
            }
        }

        //Change a value in vector_b
        vector_b[2] = 5;

        //Make sure the value in vector_a didn't change as well because that means we have a shallow copy.
        if(vector_a[2] == vector_b[2]){
            return TestResult(T_COPY_CONSTRUCT_MISMATCH, "Vector copy constructor failed. Vector b is a shallow copy of vector b instead of a deep copy.");
        }

        //Test is OK.
        return TestResult(T_SUCCESS);
    });

    Test tVectorCopyAssignment("tVectorCopyAssignment", []() -> TestResult {
        //Initialize the vectors
        Vector<std::string> vector_a ({
            "gameboy",
            "gameboy advance",
            "gamegear",
            "neogeo pocket"
        });

        Vector<std::string> vector_b = {};

        //Copy 'vector_a' to 'vector_b' overwriting it's previous values.
        vector_b = vector_a;

        //Check to if the size and capacity carried over properly and if it didn't return a failed TestResult.
        if(
            vector_a.size() != vector_b.size() ||
            vector_a.capacity() != vector_b.capacity()
        ){
            return TestResult(T_COPY_ASSIGNMENT_MISMATCH,"Vector size or capacity mismatch indicated vector was not copied correctly.");
        }

        //Check to see if all the contents copied properly and if it didn't return a failed TEST_RESULT.
        for(std::size_t i = 0; i < vector_a.size(); i++){
            if(vector_a[i] != vector_b[i]){
                return TestResult(T_COPY_ASSIGNMENT_MISMATCH, std::format("Vector copy constructor failed. Vector a mismatch at index {}.", i));
            }
        }

        //Lets change one of the elements in vector_b.
        vector_b[3] = "nintendo ds";

        //And make sure it didn't effect vector_a as well and if it did, return an error.
        if(vector_b[3] == vector_a[3]){
            return TestResult(T_COPY_CONSTRUCT_MISMATCH, "Vector copy constructor failed. Vector b is a shallow copy of vector b instead of a deep copy.");
        }

        return TestResult(0);
    });

    Test tVectorMoveConstructor("tVectorMoveConstructor", []() -> TestResult {
        Vector<int> vector_a ({3, 7, 5, 9 ,4});
        Vector<int> vector_b (std::move(vector_a));

        //Check to see if Vector A is empty.
        if(!vector_a.empty()) {
            return TestResult(T_MOVE_CONSTRUCT_MISMATCH, "Vector A didn't get cleared. Move operation failed.");
        }

        //Check to see if Vector B is the appropriate size.
        if(vector_b.size() != 5) {
            return TestResult(T_MOVE_CONSTRUCT_MISMATCH, std::format("vector_b was supposed have a size of 5, but has a size of {}.", vector_b.size()));
        }

        //Check to make sure all the items made it over in the right order.
        if(
            vector_b[0] == 3 &&
            vector_b[1] == 7 &&
            vector_b[2] == 5 &&
            vector_b[3] == 9 &&
            vector_b[4] == 4
        ){
            //Test OK.
            return TestResult(0);
        }
        
        return TestResult(T_MOVE_CONSTRUCT_MISMATCH, "vector_b didn't match vector_a's elements after it was moved. Something went very wrong.");
    });

    Test tVectorMoveAssignment("tVectorMoveAssignment", []() -> TestResult {
        //Vector initialization...
        Vector<int> vector_a = {1, 2, 3, 4};
        Vector<int> vector_b = {5, 6, 7, 8};

        vector_a = std::move(vector_b);

        if(!vector_b.empty()){
            return TestResult(T_MOVE_ASSIGNMENT_MISMATCH, std::format("vector_b was supposed to be empty, but has a size of {}.", vector_b.size()));
        }
        if(
            vector_a[0] == 5 &&
            vector_a[1] == 6 &&
            vector_a[2] == 7 &&
            vector_a[3] == 8
        ){
            //Test OK.
            return TestResult(0);
        }

        return TestResult(T_MOVE_ASSIGNMENT_MISMATCH, "vector_b didn't match vector_a's elements after it was moved. Something went very wrong.");
    });



    Test::run_all();
}