#ifndef VECTOR_CPP
#define VECTOR_CPP

#include <iostream>
using namespace std;

template <typename T>
class Vector {
private:
    T* V;         
    int cap;      
    int num;       

    void resize() {
        cap *= 2;  
        T* temp = new T[cap];
        for(int i = 0; i < num; i++) {
            temp[i] = V[i];
        }
        delete[] V;
        V = temp;
    }

public:
    Vector() {
        cap = 1;
        num = 0;
        V = new T[cap];
    }

    Vector(int size, T value) {
        cap = size;
        num = size;
        V = new T[size];
        for(int i = 0; i < size; i++) {
            V[i] = value;
        }
    }

    Vector(const Vector& other) {
        cap = other.cap;
        num = other.num;
        V = new T[cap];
        for(int i = 0; i < num; i++) {
            V[i] = other.V[i];
        }
    }

    ~Vector() {
        delete[] V;
    }

    Vector& operator=(const Vector& other) {
        if(this != &other) {
            delete[] V;
            cap = other.cap;
            num = other.num;
            V = new T[cap];
            for(int i = 0; i < num; i++) {
                V[i] = other.V[i];
            }
        }
        return *this;
    }

    void push_back(T value) {
        if(num == cap) {
            resize();
        }
        V[num++] = value;
    }

    void pop_back() {
        if(num > 0) {
            num--;
        }
    }

    T& operator[](int index) {
        return V[index];
    }

    const T& operator[](int index) const {
        return V[index];
    }

    int size() const {
        return num;
    }

    T back() const {
        if(num > 0) {
            return V[num - 1];
        }
        return T();
    }
};

#endif