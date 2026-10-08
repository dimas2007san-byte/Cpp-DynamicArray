#pragma once

class DynamicArray {
private:
    int* data;
    int size;
    int capacity; // память про запас

public:
    DynamicArray(int initialSize);
    ~DynamicArray();
    
    void print();
    void set(int index, int value);
    int get(int index);

    // конструктор копирования
    DynamicArray(const DynamicArray& other);
    
    void push_back(int value);
    
    void add(const DynamicArray& other);
    void sub(const DynamicArray& other);
};