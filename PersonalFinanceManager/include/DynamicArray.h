#ifndef PFM_DYNAMIC_ARRAY_H
#define PFM_DYNAMIC_ARRAY_H

// Owner D - W1-D-03 / W2-D-01.
// INCOMPLETE SCAFFOLD: implement ALL special members and methods before use.
// Store T items in manually allocated new T[] / delete[] memory.
// Do not use STL collection containers.
template <typename T>
class DynamicArray {
public:
    DynamicArray();
    DynamicArray(const DynamicArray& other);
    DynamicArray& operator=(const DynamicArray& other);
    ~DynamicArray();

    int size() const;
    int capacity() const;
    bool pushBack(const T& value);
    bool eraseAt(int index);
    T& at(int index);
    const T& at(int index) const;

private:
    T* data_ = nullptr;
    int size_ = 0;
    int capacity_ = 0;
    void grow();
};

// IMPORTANT: As a template, method definitions normally belong in this header.
// This file deliberately contains no method bodies; corresponding tests must fail
// until owner D implements the array. Do not claim it works as shipped.

template <typename T>
DynamicArray<T>::DynamicArray() : data_(nullptr), size_(0), capacity_(0) {
    
}
#endif
