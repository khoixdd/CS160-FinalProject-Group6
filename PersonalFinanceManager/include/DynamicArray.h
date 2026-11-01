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
DynamicArray<T>::DynamicArray() : data_(nullptr), size_(0), capacity_(0) {}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data_;
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray &other) 
    : data_(nullptr), size_(0), capacity_(0) {
    if (other.size() > 0) {
        data_ = new T[other.size_];
        size_ = other.size_;
        capacity_ = other.size_;

        for (int i = 0; i < size_; ++i)
            data_[i] = other.data_[i];
    }
} 

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other) {
    if (this != &other) {
        DynamicArray tmp(other);

        std::swap(data_, tmp.data_);
        std::swap(size_, tmp.size_);
        std::swap(capacity_, tmp.capacity_);
    }
}

template <typename T>
int DynamicArray<T>::size() const {
    return size_;
}

template <typename T>
int DynamicArray<T>::capacity() const {
    return capacity_;
}

template <typename T>
bool DynamicArray<T>::pushBack(const T& val) {
    try {
        T tmp = val;

        if (size_ == capacity_)
            grow();

        data_[size_] = std::move(tmp);

        size_++;

        return true;
    } catch (const std::exception&) {
        return false;
    }
}

template <typename T>
bool DynamicArray<T>::eraseAt(int id) {
    if (id < 0 || id >= size_)
        return false;

    for (int i = id; i + 1 < size_; ++i)
        data_[i] = std::move(data_[i + 1]);

    size_--;
    data_[size_] = T();
}

template <typename T>
T& DynamicArray<T>::at(int id) {
    if (id < 0 || id >= size_)
        throw std::out_of_range("DynamicArray:at index out of range");
    return data_[id];
}

template <typename T>
const T& DynamicArray<T>::at(int id) const {
    if (id < 0 || id >= size_)
        throw std::out_of_range("DynamicArray:at index out of range");
    return data_[id];
}

template <typename T>
void DynamicArray<T>::grow() {
    const int MAX_CAP = std::numeric_limits<int>::max() / 2;
    if (capacity_ >= MAX_CAP)
        throw std::length_error("DynamicArray capacity limit reached");
    int newCap = (capacity_ == 0) ? 2 : capacity_ * 2;

    T* newArr = new T[newCap];
    for (int i = 0; i < size_; ++i)
        newArr[i] = std::move(data_[i]);

    delete[] data_;
    data_ = newArr;
    capacity_ = newCap;
}
#endif
