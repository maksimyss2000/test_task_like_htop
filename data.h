#pragma once

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
    Data(const int count_measurements) {
        size = count_measurements;
        data = new T[size];
    }

    T& operator[](const int index) {
        return data[index];
    }

    ~Data() {
        delete[] data;
        data = nullptr;
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

        Iterator& operator++(int) {
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



