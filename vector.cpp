#include "Vector.h"

template <typename T>
// Constructor
Vector<T>::Vector() {
    arr = new T[1];  // Start with capacity 1
    capacity = 1;
    current_size = 0;
}

template <typename T>
// Destructor
Vector<T>::~Vector() {
    delete[] arr;
}

template <typename T>
// Add an element at the end
void Vector<T>::push_back(T data) {
    // If vector is full, double its capacity
    if (current_size == capacity) {
        T* temp = new T[2 * capacity];

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

template <typename T>
// Remove the last element
void Vector<T>::pop_back() {
    if (current_size > 0) {
        current_size--;
    } else {
        std::cout << "Vector is empty!" << std::endl;
    }
}

template <typename T>
// Get element at specific index
T Vector<T>::at(int index) {
    if (index >= 0 && index < current_size) {
        return arr[index];
    } else {
        std::cout << "Index out of bounds!" << std::endl;
        return -1; // Return a default value
    }
}

template <typename T>
// Get current size
int Vector<T>::size () {
    return current_size;
}

template <typename T>
// Check if vector is empty
bool Vector<T>::is_empty() {
    return current_size == 0;
}

template <typename T>
// Clear all elements
void Vector<T>::clear() {
    current_size = 0;
}

template <typename T>
// Display all elements
void Vector<T>::display() {
    for (int i = 0; i < current_size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

}
// Overload [] for direct access 
template <typename T>
T& Vector<T>::operator[](int index) {
    if (index < 0 || index >= current_size) {
        std::cout << "Index out of bounds!" << std::endl;
    }
    return arr[index];
}

// Overload [] for direct access (const version)
template <typename T>
const T& Vector<T>::operator[](int index) const {
    if (index < 0 || index >= current_size) {
        throw std::out_of_range("Index out of bounds");
    }
    return arr[index];
}


