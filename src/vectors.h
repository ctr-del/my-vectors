#ifndef CUSTOM_VECTOR_HPP
#define CUSTOM_VECTOR_HPP

#include <cstddef>

template <typename T>                                                           //Aw heck, here we go again, welcome back Mr.GPT.
class Vector {
    private:
        T* _data;
        std::size_t _size;                                                      //This is the size of the vector, i.e. the part of the vector that actually has data.
        std::size_t _capacity;                                                  //This is the capacity of the vector, i.e. all the memory allocated to the vector at this point in time.
    public:
        Vector();
        ~Vector();

        void push_back(const T& value);

        T& operator[](std::size_t index);
        const T& operator[](std::size_t index) const;

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
std::size_t Vector<T>::size() const {
    return _size;
}

template <typename T>
std::size_t Vector<T>::capacity() const {
    return _capacity;
}

template <typename T>
bool Vector<T>::empty() const {
    return _data == nullptr;
}

#endif