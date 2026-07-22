#ifndef CUSTOM_VECTOR_HPP
#define CUSTOM_VECTOR_HPP

#include <cstddef>
#include <utility>
#include <stdexcept>
#include <iostream>
#include <initializer_list>

template <typename T>                                                           //Aw heck, here we go again, welcome back Mr.GPT.
class Vector {
    private:
        T* _data;
        std::size_t _size;                                                      //This is the size of the vector, i.e. the part of the vector that actually has data.
        std::size_t _capacity;                                                  //This is the capacity of the vector, i.e. all the memory allocated to the vector at this point in time.
        void expand();
        void swap();

    public:
        //Default vector constructor
        Vector();

        //Initializer list vector constructor
        Vector(std::initializer_list<T>);

        //Vector deconstructor
        ~Vector();

        //Lets disable copying for now, but Vector Copy Constructor and Copy Assignment
        Vector(const Vector& other);
        Vector& operator=(const Vector& other);

        //Move operations here for future implementation.
        Vector(Vector&& other) = delete;
        Vector& operator=(Vector&& other) = delete;

        //Iterator Nonsense
        using iterator = T*;
        using const_iterator = const T*;

        iterator begin();
        iterator end();

        const_iterator begin() const;
        const_iterator end() const;

        const_iterator cbegin() const;
        const_iterator cend() const;

        //Access operators and methods
        T& operator[](std::size_t index);
        const T& operator[](std::size_t index) const;
        T& at(std::size_t index);
        const T& at(std::size_t index) const;

        void push_back(const T& value);
        void pop_back();
        void clear();

        void reserve(std::size_t amount);
        void resize(std::size_t new_capacity);

        std::size_t size() const;
        std::size_t capacity() const;
        bool empty() const;

};

//
// ===[ CONSTRUCTORS AND DESTRUCTORS ]===
//
template <typename T>
Vector<T>::Vector() :
    _data(nullptr),
    _size(0),
    _capacity(0)
{

}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> initial_array):
    Vector()
{
    for(T item : initial_array){
        push_back(item);
    }
}

template <typename T>
Vector<T>::~Vector() {
    delete[] _data;
}

//
// ===[COPY ASSIGNMENT AND COPY CONSTRUCTOR]===
//

//Copy Constructor
template <typename T>
Vector<T>::Vector(const Vector& other):
    Vector()
{
    reserve(other._capacity);

    for (const auto& element : other){
        push_back(element);
    }
}

//Copy Assignment
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other ){
    //Return early if we are trying to assign to ourselves...
    if(this == &other){
        return *this;
    }

    reserve(other.capacity());

    //Clear the vector before we add anything to it.
    clear();

    //
    for (auto element : other){
        push_back(element);
    }

    return *this;
}

//
// ===[ ITERATOR OPERATIONS ]===
//

template <typename T>
auto Vector<T>::begin() -> iterator {
    return _data;
}

template <typename T>
auto Vector<T>::end() -> iterator {
    return _data + _size;
}

template <typename T>
auto Vector<T>::begin() const -> const_iterator {
    return _data;
}

template <typename T>
auto Vector<T>::end() const -> const_iterator {
    return _data + _size;
}

template <typename T>
auto Vector<T>::cbegin() const -> const_iterator {
    return begin();
}

template <typename T>
auto Vector<T>::cend() const -> const_iterator {
    return end();
}

//
// ===[ ACCESS OPERATORS AND METHODS ]===
//

template <typename T>
T& Vector<T>::operator[](std::size_t index) {
    return _data[index];
}

template <typename T>
const T& Vector<T>::operator[](std::size_t index) const{
    return _data[index];
}

template <typename T>
T& Vector<T>::at(std::size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Error! Attempted to access vector beyond the vector size.");
    }
    return (*this)[index];
}

template <typename T>
const T& Vector<T>::at(std::size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Error! Attempted to access const vector boyond the vector size.");
    }
    return (*this)[index];
}

//
// ===[ MODIFIER OPERATORS AND METHODS ]===
//
template <typename T>
void Vector<T>::push_back(const T& value) {
    //First of all, let's compare the size and capacity of the vector, if it is the same, lets extend the capacity before we add any elements...
    if (_size == _capacity){
        expand();
    }
    _data[_size] = value;
    ++_size;
}

template <typename T>
void Vector<T>::pop_back() {
    --_size;
}

template <typename T>
void Vector<T>::clear() {
    _size = 0;
}

//LEGACY VERSION
/*
template <typename T>
void Vector<T>::expand() {
    std::size_t new_capacity = (_capacity == 0) ? 1 : _capacity * 2;

    T* new_data = new T[new_capacity];

    for (std::size_t i = 0; i < _size; i++){
        new_data[i] = std::move(_data[i]);
    }

    delete[] _data;

    _data = new_data;
    _capacity = new_capacity;
}
*/
template <typename T>
void Vector<T>::expand() {
    reserve((_capacity == 0 ? 1 : _capacity * 2));
}


template <typename T>
void Vector<T>::reserve(std::size_t amount) {
    if (amount > _capacity){
        T* new_data = new T[amount];

        for (std::size_t i = 0; i < _size; i++){
            new_data[i] = std::move(_data[i]);
        }

        delete[] _data;

        _data = new_data;
        _capacity = amount;
    }
}

template <typename T>
void Vector<T>::resize(std::size_t new_size) {
    if(new_size > _capacity){
        reserve(new_size);
    }

    _size = new_size;
}

//
// ===[ DATA METHODS ]===
//
template <typename T>
std::size_t Vector<T>::size() const {
    return _size;
}

template <typename T>
std::size_t Vector<T>::capacity() const {
    return _capacity;
}

template <typename T>
bool Vector<T>::empty() const {
    return _size == 0;
}

#endif