#ifndef CUSTOM_VECTOR_HPP
#define CUSTOM_VECTOR_HPP

#include <cstddef>
#include <stdexcept>

template <typename T>                                                           //Aw heck, here we go again, welcome back Mr.GPT.
class Vector {
    private:
        T* _data;
        std::size_t _size;                                                      //This is the size of the vector, i.e. the part of the vector that actually has data.
        std::size_t _capacity;                                                  //This is the capacity of the vector, i.e. all the memory allocated to the vector at this point in time.
    public:
        //Default vector constructor
        Vector();

        //Vector deconstructor
        ~Vector();

        //Lets disable copying for now, but Vector Copy Constructor and Copy Assignment
        Vector(const Vector&) = delete;
        Vector& operator=(const Vector&) = delete;

        //Move operations here for future implementation.
        Vector(const Vector&&);
        Vector&& operator=(const Vector&&);

        //Access operators and methods
        T& operator[](std::size_t index);
        const T& operator[](std::size_t index) const;
        T& at(std::size_t index);
        const T& at(std::size_t index) const;

        void push_back(const T& value);

        std::size_t size() const;
        std::size_t capacity() const;
        bool empty() const;

};

template <typename T>
Vector<T>::Vector() :
    _data(nullptr),
    _size(0),
    _capacity(0)
{

}

template <typename T>
Vector<T>::~Vector() {
    delete[] _data;
}

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
    if (index > _size) {
        throw std::out_of_range_exception("Error! Attempted to access vector beyond the vector size.");
    }
    return *this[index];
}

template <typename T>
const T& Vector<T>::at(std::size_t index) const {
    if (index > _size) {
        throw std::out_of_range_exception("Error! Attempted to access const vector boyond the vector size.");
    }
    return *this[index];
}

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