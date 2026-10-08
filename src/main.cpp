#include <iostream>
#include "../include/DynamicArray.h"

int main() {
    std::cout << "Task 1\n";
    DynamicArray arr1(3);
    arr1.set(0, 10);
    arr1.set(1, 20);
    arr1.set(2, 250); // должно выдать ошибку
    std::cout << "arr1: ";
    arr1.print();

    std::cout << "\nTask 2\n";
    DynamicArray arr2 = arr1;
    arr2.set(0, 99);
    std::cout << "original: "; arr1.print();
    std::cout << "copy:     "; arr2.print();

    std::cout << "\nTask 3\n";
    arr1.push_back(30);
    arr1.push_back(50);
    std::cout << "arr1 after push: ";
    arr1.print();

    std::cout << "\nTask 4\n";
    DynamicArray arr3(2);
    arr3.set(0, 5);
    arr3.set(1, 5);
    std::cout << "arr3: "; arr3.print();
    
    arr1.add(arr3);
    std::cout << "arr1 + arr3: ";
    arr1.print();

    return 0;
}