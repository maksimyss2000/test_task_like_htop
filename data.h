#pragma once

#include <iostream>

template<typename T>
class Data {
private:
    T* data;
    int size;
public:
    Data(){
        data = nullptr;
    }

    /* TODO: change new[] to smart pointer */
    Data(const int size) {
        this->size = size;
        data = new T[size];
    }

    ~Data() {
        delete[] data;
    }
    
    T& operator[](const int index) {
        return data[index];
    }

    void operator=(Data<T>&& other) {
        delete[] this->data;
        this->data = other.data;
        this->size = other.size;
        other.data = nullptr;
        other.size = 0;
    } 

    int getSize() {
        return size;
    }

    class Iterator {
    private:
        T* ptr;
    public:
        Iterator(T* ptr) {
            this->ptr = ptr;
        }

        T& operator*() const {
            return *ptr;
        }

        Iterator operator++(int) {
            Iterator tmp = *this; 
            ++(*this);
            return tmp;
        }  

        Iterator& operator++() {
            ptr++;
            return *this; 
        }  

        bool operator!= (const Iterator& other) { 
            return this->ptr != other.ptr; 
        }  
    };

    Iterator begin() {
        return Iterator(data);
    }

    Iterator end() {
        return Iterator(data + size);
    }
};



