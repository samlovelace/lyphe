#pragma once

#include <iostream>

template<typename T>
class vec3
{
public:
    T x;
    T y;
    T z;

    // Default constructor
    vec3() : x(0), y(0), z(0) {}

    // Constructor with values
    vec3(T x, T y, T z) : x(x), y(y), z(z) {}

    // Copy constructor
    vec3(const vec3<T>& other) = default;

    // += operator
    vec3<T>& operator+=(const vec3<T>& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    // Optional: add + operator
    vec3<T> operator+(const vec3<T>& rhs) const
    {
        vec3<T> result(*this);
        result += rhs;
        return result;
    }

    vec3<T> operator*(const vec3<T>& rhs) const
    {
        vec3<T> result(*this); 
        result *= rhs; 
        return result; 
    }

    vec3<T> operator*=(const float scale) const 
    {
        vec3<T> result(*this); 
        result *= scale; 
        return result; 
    }

    // Print (for debugging)
    void print() const
    {
        std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
    }
};
