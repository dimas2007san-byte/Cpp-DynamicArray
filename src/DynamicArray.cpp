#include "../include/DynamicArray.h"
#include <iostream>
#include <stdexcept>

DynamicArray::DynamicArray(int initialSize) {
    size = initialSize;
    capacity = initialSize;
    data = new int[capacity];
    
    for (int i = 0; i < size; i++) {
        data[i] = 0; // забиваем нулями
    }
}

DynamicArray::~DynamicArray() {
    delete[] data;
}

void DynamicArray::print() {
    std::cout << "[";
    for (int i = 0; i < size; i++) {
        std::cout << data[i];
        if (i < size - 1) std::cout << ", ";
    }
    std::cout << "]\n";
}

void DynamicArray::set(int index, int value) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    if (value < -100 || value > 100) {
        throw std::invalid_argument("Value must be in the range from -100 to 100");
    }
    data[index] = value;
}

int DynamicArray::get(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

DynamicArray::DynamicArray(const DynamicArray& other) {
    size = other.size;
    capacity = other.capacity;
    data = new int[capacity]; // новая независимая память
    
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

void DynamicArray::push_back(int value) {
    // Проверяем диапазон значений
    if (value < -100 || value > 100) {
        throw std::invalid_argument("Value must be between -100 and 100");
    }

    // Если массив заполнен — расширяем его в 2 раза
    if (size == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity = capacity * 2;
        }

        int* newData = new int[capacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

    data[size] = value;
    size++;
}

void DynamicArray::add(const DynamicArray& other) {
    for (int i = 0; i < size; i++) {
        int otherValue = (i < other.size) ? other.data[i] : 0;
        set(i, data[i] + otherValue); 
    }
}

void DynamicArray::sub(const DynamicArray& other) {
    for (int i = 0; i < size; i++) {
        int otherValue = (i < other.size) ? other.data[i] : 0;
        set(i, data[i] - otherValue);
    }
}