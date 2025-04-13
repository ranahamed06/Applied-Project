#include "Vector.h"

// Constructor
Vector::Vector() {
    arr = new int[1];  // Start with capacity 1
    capacity = 1;
    current_size = 0;
}

// Destructor
Vector::~Vector() {
    delete[] arr;
}

// Add an element at the end
void Vector::push_back(int data) {
    // If vector is full, double its capacity
    if (current_size == capacity) {
        int* temp = new int[2 * capacity];

        // Copy old elements to new array
        for (int i = 0; i < current_size; i++) {
            temp[i] = arr[i];
        }

        // Delete old array
        delete[] arr;

        // Update capacity and array pointer
        capacity *= 2;
        arr = temp;
    }

    // Insert the new element
    arr[current_size] = data;
    current_size++;
}

// Remove the last element
void Vector::pop_back() {
    if (current_size > 0) {
        current_size--;
    } else {
        std::cout << "Vector is empty!" << std::endl;
    }
}

// Get element at specific index
int Vector::at(int index) {
    if (index >= 0 && index < current_size) {
        return arr[index];
    } else {
        std::cout << "Index out of bounds!" << std::endl;
        return -1; // Return a default value
    }
}

// Get current size
int Vector::size() {
    return current_size;
}

// Check if vector is empty
bool Vector::is_empty() {
    return current_size == 0;
}

// Clear all elements
void Vector::clear() {
    current_size = 0;
}

// Display all elements
void Vector::display() {
    for (int i = 0; i < current_size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
