#include "../include/DynamicArray.h"

#include <new>
#include <string>

int main() {
    std::cout << "=== Numeric array ===\n";

    DynamicArray<int> first(2);
    first.set(0, 3);
    first.set(1, 4);

    DynamicArray<int> second(2);
    second.set(0, 6);
    second.set(1, 8);

    std::cout << "first:  " << first << '\n';
    std::cout << "second: " << second << '\n';
    std::cout << "distance: " << first.distance(second) << '\n';

    first.push_back(5);
    std::cout << "after push_back: " << first << '\n';

    first.add(second);
    std::cout << "after add: " << first << '\n';

    first.sub(second);
    std::cout << "after sub: " << first << '\n';

    std::cout << "\n=== Text array ===\n";

    DynamicArray<std::string> words(2);
    words.set(0, "cat");
    words.set(1, "dog");
    std::cout << "words: " << words << '\n';

    try {
        words.distance(words);
    } catch (const std::bad_typeid&) {
        std::cout << "Distance is available only for numeric arrays.\n";
    }

    std::cout << "\n=== Exceptions ===\n";

    try {
        first.get(20);
    } catch (const std::out_of_range& error) {
        std::cout << "Index error: " << error.what() << '\n';
    }

    try {
        first.set(0, 150);
    } catch (const std::invalid_argument& error) {
        std::cout << "Value error: " << error.what() << '\n';
    }

    try {
        throw std::bad_alloc(); // Пример обработки ошибки нехватки памяти.
    } catch (const std::bad_alloc&) {
        std::cout << "Memory error caught.\n";
    }

    return 0;
}
