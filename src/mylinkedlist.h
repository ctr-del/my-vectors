#ifndef MYLINKEDLIST_H_INCLUDED
#define MYLINKEDLIST_H_INCLUDED
#include <initializer_list>
#include <stdexcept>

typedef unsigned int length_t;

template <typename T> class LinkedList {
    private:
        struct Node;
    public:
        //Iterator
        class Iterator {
            private:
                Node* current;
            public:
                Iterator(Node* node);

                T& operator*();
                Iterator& operator++();
                Iterator operator++(int);

                bool operator==(const Iterator& other) const;
                bool operator!=(const Iterator& other) const;
        };

        class ConstIterator {
            private:
                Node* current;
            public:
                Iterator(const Node* node);

                const T& operator*();
                Iterator&
        };
        Iterator begin();
        Iterator end();

        //Constructors
        LinkedList();
        LinkedList(std::initializer_list<T> values);
        ~LinkedList();

        //Copy and Move Operations
        //Copy Constructors and Copy Assignment
        LinkedList(const LinkedList&);
        LinkedList& operator=(const LinkedList&);

        //Move Constructors and Move Assignment
        LinkedList(LinkedList&& other) noexcept;
        LinkedList& operator=(LinkedList&& other) noexcept;

        //Operator Overloading
        LinkedList& operator+=(const T&);
        LinkedList& operator+=(const LinkedList&);
        LinkedList operator+(const T&) const;
        LinkedList operator+(const LinkedList&) const;

        //Capacity
        bool empty() const;
        length_t size() const;

        //Access
        T& at(length_t index);
        const T& at(length_t index) const;

        T& operator[](length_t index);
        const T& operator[](length_t index) const;

        T& front();
        const T& front() const;

        T& back();
        const T& back() const;



        //Modifiers
        void push_back(const T& element);
        void push_front(const T& element);
        void pop_front();
        void pop_back();
        void insert(const T& element, length_t index);
        void erase(length_t index);
        void clear();

    private:
        struct Node {
            T data;
            Node* next;
            Node(const T& value):
                data(value),
                next(nullptr)
            {
            }
        };

        //Helper functions
        length_t length;
        Node* first;
        Node* last;
        Node* at_node(length_t index);
        const Node* at_node(length_t index) const;
        void copy_from(const LinkedList<T>& other);
        void move_from(LinkedList<T>& other) noexcept;
};

//==============================================================//
//Constructors and Destructors                                  //
//==============================================================//

//Basic constructor, initializes the Linked List but does not include any elements.
template <typename T>
LinkedList<T>::LinkedList() :
    length (0),
    first (nullptr),
    last (nullptr)
{
}

//Basic constructor that initializes based on an initializer_list, i.e. support for Linked Lists to be
//defined using curley braces.
template <typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> values) :
    LinkedList()
{
    for(const T& value : values){
        push_back(value);
    }
}

//Basic destructor for our linked list that makes sure all elements of the linked list are deleted
//to avoid memory leaks.
template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

//==============================================================//
//Copy Move Operations                                          //
//==============================================================//

//Copy Constructor
template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other) :
    LinkedList()
{
    copy_from(other);
}

//Move Constructor
template <typename T>
LinkedList<T>::LinkedList(LinkedList&& other) noexcept :
    LinkedList()
{
    move_from(other);
}


//Copy Assignment
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other){
    if (this == &other){
        return *this;
    }

    clear();

    copy_from(other);

    return *this;
}


//Move Assignment
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) noexcept {
    if (this == &other){
        return *this;
    }

    clear();

    move_from(other);

    return *this;
}

//==============================================================//
//Operator Overloading                                          //
//==============================================================//

//Makes the += operator append to the back of the list if you add something that matches
//the type of the list.
template <typename T>
LinkedList<T>& LinkedList<T>::operator+=(const T& value){
    push_back(value);
    return *this;
}


//Makes the += operator append a list to another list if they match types
template <typename T>
LinkedList<T>& LinkedList<T>::operator+=(const LinkedList<T>& other) {
    if (this == &other){
        LinkedList copy(other);
        return *this += copy;
    }

    Node* cursor = other.first;

    while (cursor != nullptr) {
        push_back(cursor->data);
        cursor = cursor->next;
    }

    return *this;
}

//Makes the + operator append a value to the end of a linked list.
template <typename T>
LinkedList<T> LinkedList<T>::operator+(const T& value) const {
    LinkedList<T> result(*this);
    result += value;
    return result;
}

//Makes the + operator append a linked list to another linked list.
template <typename T>
LinkedList<T> LinkedList<T>::operator+(const LinkedList<T>& other) const {
    LinkedList<T> result (*this);
    result += other;
    return result;
}

//==============================================================//
//Capacity                                                      //
//==============================================================//

//Checks to see if the container is empty and if it is, return true
template <typename T>
bool LinkedList<T>::empty() const {
    return first == nullptr;
}

//Retrieves the size of the container
template <typename T>
length_t LinkedList<T>::size() const {
    return length;
}

//==============================================================//
//Access                                                        //
//==============================================================//

//Get the value at a specific index. O(n) complexity, it takes longer the longer the
//list is.
template <typename T>
T& LinkedList<T>::at(const length_t index) {
    Node* indexed_node = at_node(index);
    if(indexed_node == nullptr) {
        throw std::out_of_range("Cannot access element that is out of range...");
    }
    return indexed_node->data;
}

//Const version
template <typename T>
const T& LinkedList<T>::at(const length_t index) const {
    const Node* indexed_node = at_node(index);
    if(indexed_node == nullptr) {
        throw std::out_of_range("Cannot access element that is out of range...");
    }
    return indexed_node->data;
}

//Get the value at a specific index. O(n) complexity, it takes longer the longer the
//list is. NO BOUNDS CHECKING so use at own risk.
template <typename T>
T& LinkedList<T>::operator[](length_t index){
    return at_node(index)->data;
}

//Same as above but const version
template <typename T>
const T& LinkedList<T>::operator[](length_t index) const{
    return at_node(index)->data;
}

//Get the first value in the linked list.
template <typename T>
T& LinkedList<T>::front(){
    if(first==nullptr){
        throw std::out_of_range("Cannot access the first element of an empty list!");
    }
    return first->data;
}

//Again, same as above except contains the mythical power of const.
template <typename T>
const T& LinkedList<T>::front() const {
    if(first==nullptr){
        throw std::out_of_range("Cannot access the first element of an empty list!");
    }
    return first->data;
}

//Get the last value in the linked list.
template <typename T>
T& LinkedList<T>::back(){
    if(last==nullptr){
        throw std::out_of_range("Cannot access the last element of an empty list!");
    }
    return last->data;
}

//Another super unique... JUST KIDDING MORE CONST COMPATIBILITY
template <typename T>
const T& LinkedList<T>::back() const {
    if(last==nullptr){
        throw std::out_of_range("Cannot access the last element of an empty list!");
    }
    return last->data;
}

//==============================================================//
//Container Manipulation Methods                                //
//==============================================================//

//Empties the list, deleting all the created nodes in the process. O(n) time due
//having to walk the entire list.
template <typename T>
void LinkedList<T>::clear(){
    while(!empty()){
        pop_front();
    }
}


//Adds an element to the back of the list. O(1) time since we know where the end of the list is.
template <typename T>
void LinkedList<T>::push_back(const T& element) {
    Node* new_node = new Node(element);

    //If the linked list 'first' value is a null pointer, let's give it the value of this node.
    //Else, lets see if we can find where the next null pointer is to insert our element at the end.
    if (last == nullptr) {
        first = new_node;
        last = new_node;
    }else{
        last->next = new_node;
        last = new_node;
    }
    ++length;
}

//Adds an element to the front of the list. O(1) time since we know where the start of the list is.
template <typename T>
void LinkedList<T>::push_front(const T& element) {
    Node* new_node = new Node(element);

    if (first == nullptr) {
        first = new_node;
        last = new_node;
    }else{
        new_node->next = first;
        first = new_node;
    }
    ++length;
}

//Removes the element from the front of the list. O(1) time since we know where the start of the list is.
template <typename T>
void LinkedList<T>::pop_front() {
    if (first == nullptr) {
        return;
    }

    Node* old_node = first;
    first = first->next;
    delete old_node;

    //If removing the first node sets first to a null pointer, we want to make sure that the last node is
    //also a null pointer too so we can avoid dangling pointers.
    if (first == nullptr) {
        last = nullptr;
    }

    --length;
}


//Removes an item from the back of the list. O(n) time due to having to walk the list at least once in order
//to get the position of the second to last node.
template <typename T>
void LinkedList<T>::pop_back() {
    //Let's first check to see if last even exists, if not we can go ahead and return.
    if (last == nullptr){
        return;
    }

    Node* old_node = last;

    //If the length of the list is 1, lets go ahead and wipe it and then return.
    if (length == 1){
        first = nullptr;
        last = nullptr;
    }else{
        last = at_node(length - 2);
        last->next = nullptr;
    }

    delete old_node;

    --length;
}

//Insert an element into the list. O(n) time since you have to walk through the list until you
//get to the index where you want to insert.
template <typename T>
void LinkedList<T>::insert(const T& value, const length_t index){
    //If the index is greater than the length, let's just go ahead append to the end of the list.
    if (index >= length) {
        push_back(value);
        return;
    }

    if (index == 0) {
        push_front(value);
        return;
    }

    //Let's declare some variables to make things easier to follow.
    Node* previous_node = at_node(index - 1);
    Node* next_node = previous_node->next;
    Node* new_node = new Node(value);

    //First we need to make sure the previous node points to our new one...
    previous_node->next = new_node;

    //Now we have to make sure our new node points to the next node...
    new_node->next = next_node;

    //Don't forget to increment the length again!
    ++length;
}

//Removes and deletes an element from a specific index in the linked list. O(n) time
//complexity from where you have to walk the list.
template <typename T>
void LinkedList<T>::erase(const length_t index){
    //If the index is greater than the length, let's return early...
    if (index >= length) {
        return;
    }

    if (index == 0) {
        pop_front();
        return;
    }

    Node* previous_node = at_node(index - 1);
    Node* current_node = previous_node->next;
    Node* next_node = current_node->next;

    if (current_node == last){
        last = previous_node;
    }
    previous_node->next = next_node;

    delete current_node;

    --length;
}

//==============================================================//
//Iterator Junk                                                 //
//==============================================================//

//Basic Iterator Constructor
template <typename T>
LinkedList<T>::Iterator::Iterator(Node* node):
    current(node)
{
}

//Iterator * Unary operator overload, so we can dereference our lovely
//node pointer.
template <typename T>
T& LinkedList<T>::Iterator::operator*(){
    return current->data;
}

template <typename T>
auto LinkedList<T>::Iterator::operator++() -> Iterator& {
    current = current->next;
    return *this;
}

template <typename T>
auto LinkedList<T>::Iterator::operator++(int) -> Iterator {
    Iterator temp (*this);

    ++(*this);

    return temp;
}

template <typename T>
bool LinkedList<T>::Iterator::operator==(const Iterator& other) const{
    return current==other.current;
}

template <typename T>
bool LinkedList<T>::Iterator::operator!=(const Iterator& other) const{
    return current!=other.current;
}

template <typename T>
auto LinkedList<T>::begin() -> Iterator {
    return Iterator(first);
}

template <typename T>
auto LinkedList<T>::end() -> Iterator {
    return Iterator(nullptr);
}

//==============================================================//
//Helper Functions                                              //
//==============================================================//

template <typename T>
auto LinkedList<T>::at_node(const length_t index) -> Node*{
    //First, lets check to see if the index is greater than the length and if it is, lets go ahead and return
    //a nullptr because an index bigger than the length isn't possible. This should also cover if the list is
    //empty as an empty list should have a length of zero.
    if (index >= length) {
        return nullptr;
    }

    if (index == 0){
        return first;
    }

    //Next, if the index is the length of the linked list, just return the last element. There is no point in
    //walking the list if we already know how where the last element is.
    if (index == length - 1) {
        return last;
    }

    Node* cursor = first;            //This is a cursor pointer to keep track of nodes as we walk through them.

    //Finally lets walk the list then return when we arrive at the proper index.
    for(length_t i = 0; i < index; ++i){
        cursor = cursor->next;
    }

    return cursor;
}

template <typename T>
auto LinkedList<T>::at_node(const length_t index) const -> const Node* {
    if (index >= length){
            return nullptr;
        }
    if (index == 0){
        return first;
    }
    if (index == length - 1){
        return last;
    }
    const Node* cursor = first;

    for(length_t i = 0; i < index; ++i){
        cursor = cursor->next;
    }

    return cursor;
}

template <typename T>
void LinkedList<T>::copy_from(const LinkedList<T>& other){
    const Node* cursor = other.first;

    while(cursor != nullptr){
        push_back(cursor->data);
        cursor = cursor->next;
    }
}

template <typename T>
void LinkedList<T>::move_from(LinkedList<T>& other) noexcept {
    length = other.length;
    first = other.first;
    last = other.last;

    other.length = 0;
    other.first = nullptr;
    other.last = nullptr;
}


#endif // MYLINKEDLIST_H_INCLUDED
