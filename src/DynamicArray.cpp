#include "../include/DynamicArray.h"
#include <iostream>

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
        std::cout << "Error: invalid index\n";
        return;
    }
    // по условию от -100 до 100
    if (value < -100 || value > 100) {
        std::cout << "Error: bad value\n";
        return;
    }
    data[index] = value;
}

int DynamicArray::get(int index) {
    if (index < 0 || index >= size) {
        std::cout << "Error: invalid index\n";
        return 0;
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
    if (value < -100 || value > 100) {
        std::cout << "Error: bad value\n";
        return;
    }

    // расширяем массив если места больше нет
    if (size == capacity) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        int* newData = new int[newCapacity];
        
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        
        delete[] data;
        data = newData;
        capacity = newCapacity;
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