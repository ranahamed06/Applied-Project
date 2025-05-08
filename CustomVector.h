
#ifndef CUSTOMVECTOR_H
#define CUSTOMVECTOR_H

// Custom implementation of vector since STL is not allowed
template <typename T>
class CustomVector {
private:
    T* data;
    int capacity;
    int size_;

    void resize() {
        int newCapacity = capacity * 2;
        T* newData = new T[newCapacity];

        for (int i = 0; i < size_; i++) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    CustomVector() : capacity(10), size_(0) {
        data = new T[capacity];
    }

    explicit CustomVector(int initialCapacity) : capacity(initialCapacity), size_(0) {
        data = new T[capacity];
    }

    CustomVector(const CustomVector& other) : capacity(other.capacity), size_(other.size_) {
        data = new T[capacity];
        for (int i = 0; i < size_; i++) {
            data[i] = other.data[i];
        }
    }

    ~CustomVector() {
        delete[] data;
    }

    CustomVector& operator=(const CustomVector& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            size_ = other.size_;
            data = new T[capacity];
            for (int i = 0; i < size_; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    void push_back(const T& value) {
        if (size_ >= capacity) {
            resize();
        }
        data[size_++] = value;
    }

    void pop_back() {
        if (size_ > 0) {
            size_--;
        }
    }

    T& operator[](int index) {
        return data[index];
    }

    const T& operator[](int index) const {
        return data[index];
    }

    int size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    void clear() {
        size_ = 0;
    }

    T& at(int index) {
        if (index < 0 || index >= size_) {
            throw "Index out of bounds";
        }
        return data[index];
    }

    void remove(int index) {
        if (index < 0 || index >= size_) {
            return;
        }

        for (int i = index; i < size_ - 1; i++) {
            data[i] = data[i + 1];
        }
        size_--;
    }
};

#endif //CUSTOMVECTOR_H
