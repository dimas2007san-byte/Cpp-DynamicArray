#pragma once

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>

template <typename T>
class DynamicArray {
private:
    T* data;
    int size;
    int capacity;

    void checkValue(const T& value) const {
        if constexpr (std::is_integral<T>::value) {
            if constexpr (std::is_signed<T>::value) {
                if (value < -100 || value > 100) {
                    throw std::invalid_argument("Integer value must be from -100 to 100");
                }
            } else {
                if (value > 100) {
                    throw std::invalid_argument("Integer value must be from 0 to 100");
                }
            }
        }
    }

public:
    class ElementProxy {
    private:
        DynamicArray& array;
        int index;

    public:
        ElementProxy(DynamicArray& source, int position)
            : array(source), index(position) {}

        ElementProxy& operator=(const T& value) {
            array.set(index, value);
            return *this;
        }

        operator T() const {
            return array.get(index);
        }
    };

    explicit DynamicArray(int initialSize)
        : data(nullptr), size(initialSize), capacity(initialSize) {
        if (initialSize < 0) {
            throw std::invalid_argument("Size cannot be negative");
        }

        data = new T[capacity]{};
    }

    DynamicArray(const DynamicArray& other)
        : data(new T[other.capacity]), size(other.size), capacity(other.capacity) {
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    ~DynamicArray() {
        delete[] data;
    }

    int getSize() const {
        return size;
    }

    void print() const {
        std::cout << '[';
        for (int i = 0; i < size; ++i) {
            if (i > 0) {
                std::cout << ", ";
            }
            std::cout << data[i];
        }
        std::cout << "]\n";
    }

    void set(int index, const T& value) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }

        checkValue(value);
        data[index] = value;
    }

    T get(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }

        return data[index];
    }

    ElementProxy operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return ElementProxy(*this, index);
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    void push_back(const T& value) {
        checkValue(value);

        if (size == capacity) {
            if (capacity == 0) {
                capacity = 1;
            } else {
                capacity = capacity * 2;
            }

            T* newData = new T[capacity];

            for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
            }

            delete[] data;
            data = newData;
        }

        data[size] = value;
        ++size;
    }

    void add(const DynamicArray& other) {
        if constexpr (std::is_arithmetic<T>::value) {
            for (int i = 0; i < size; ++i) {
                T otherValue = (i < other.size) ? other.data[i] : T{};
                set(i, data[i] + otherValue);
            }
        } else {
            throw std::bad_typeid();
        }
    }

    void sub(const DynamicArray& other) {
        if constexpr (std::is_arithmetic<T>::value) {
            for (int i = 0; i < size; ++i) {
                T otherValue = (i < other.size) ? other.data[i] : T{};
                set(i, data[i] - otherValue);
            }
        } else {
            throw std::bad_typeid();
        }
    }

    double distance(const DynamicArray& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Arrays must have the same size");
        }

        if constexpr (std::is_arithmetic<T>::value) {
            double sum = 0.0;

            for (int i = 0; i < size; ++i) {
                double difference = static_cast<double>(data[i])
                                  - static_cast<double>(other.data[i]);
                sum += difference * difference;
            }

            return std::sqrt(sum);
        } else {
            throw std::bad_typeid();
        }
    }

    bool operator==(const DynamicArray& other) const {
        if (size != other.size) {
            return false;
        }

        for (int i = 0; i < size; ++i) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const DynamicArray& other) const {
        return !(*this == other);
    }

    DynamicArray& operator+=(const DynamicArray& other) {
        if constexpr (std::is_arithmetic<T>::value) {
            for (int i = 0; i < size; ++i) {
                T otherValue = (i < other.size) ? other.data[i] : T{};
                set(i, data[i] + otherValue);
            }
        } else {
            throw std::bad_typeid();
        }
        return *this;
    }

    DynamicArray& operator-=(const DynamicArray& other) {
        if constexpr (std::is_arithmetic<T>::value) {
            for (int i = 0; i < size; ++i) {
                T otherValue = (i < other.size) ? other.data[i] : T{};
                set(i, data[i] - otherValue);
            }
        } else {
            throw std::bad_typeid();
        }
        return *this;
    }

    DynamicArray& operator+=(const T& value) {
        if constexpr (std::is_arithmetic<T>::value) {
            for (int i = 0; i < size; ++i) {
                set(i, data[i] + value);
            }
        } else {
            throw std::bad_typeid();
        }
        return *this;
    }

    DynamicArray& operator-=(const T& value) {
        if constexpr (std::is_arithmetic<T>::value) {
            for (int i = 0; i < size; ++i) {
                set(i, data[i] - value);
            }
        } else {
            throw std::bad_typeid();
        }
        return *this;
    }

    T* begin() {
        return data;
    }

    T* end() {
        return data + size;
    }

    const T* begin() const {
        return data;
    }

    const T* end() const {
        return data + size;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& output, const DynamicArray<T>& array) {
    output << '[';

    for (int i = 0; i < array.getSize(); ++i) {
        if (i > 0) {
            output << ", ";
        }
        output << array.get(i);
    }

    output << ']';
    return output;
}
