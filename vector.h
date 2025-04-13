#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

template <typename T>
class Vector {
private:
    T* arr;           // Pointer to store the array elements
    int capacity;       // Maximum capacity of the vector
    int current_size;   // Current number of elements

public:
    // Constructor
    Vector();

    // Destructor
    ~Vector();

    // Add an element at the end
    void push_back(T data);

    // Remove the last element
    void pop_back();

    // Get element at specific index
    T at(int index);

    // Get current size
    int size();

    // Check if vector is empty
    bool is_empty();

    // Clear all elements
    void clear();

    // Display all elements
    void display();

    // Overload [] for direct access 
    T& operator[](int index);      
    // Overload [] for direct access (const)
    const T& operator[](int index) const; 
};


#endif // VECTOR_H
