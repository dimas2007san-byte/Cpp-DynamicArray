#include <iostream>
#include <stdexcept>
#include "../include/DynamicArray.h"


int main() {
    std::cout << "=== Part 2: Exceptions Demo ===\n\n";

    // 1. Проверка std::out_of_range
    try {
        DynamicArray arr(2);
        std::cout << "[Test 1] Trying to get element at index 5...\n";
        arr.get(5);
    } catch (const std::out_of_range& e) {
        std::cout << "Caught std::out_of_range: " << e.what() << "\n\n";
    }

    // 2. Проверка std::invalid_argument
    try {
        DynamicArray arr(2);
        std::cout << "[Test 2] Trying to set element at index 0 to 150...\n";
        arr.set(0, 150);
    } catch (const std::invalid_argument& e) {
        std::cout << "Caught std::invalid_argument: " << e.what() << "\n\n";
    }

    // 3. Проверка std::bad_alloc
    try {
        std::cout << "[Test 3] Trying to allocate an excessively large amount of memory...\n";
        DynamicArray hugeArr(2000000000); 
    } catch (const std::bad_alloc& e) {
        std::cout << "Caught std::bad_alloc: " << e.what() << "\n\n";
    }

    std::cout << "All exceptions caught successfully. Program finished.\n";
    return 0;
}