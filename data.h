#pragma once

template<typename T>
class Data {
private:
    T* data_core_cpu;
    int size;
public:
    /* TODO: change new[] to smart pointer */
    Data(){
        data_core_cpu = nullptr;
    }
    
    Data(const int count_measurements) {
        size = count_measurements;
        data_core_cpu = new T[size];
    }

    T& operator[](const int index) {
        return data_core_cpu[index];
    }

    ~Data() {
        delete[] data_core_cpu;
        data_core_cpu = nullptr;
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
        return Iterator(data_core_cpu);
    }

    Iterator end() {
        return Iterator(data_core_cpu + size);
    }
};



