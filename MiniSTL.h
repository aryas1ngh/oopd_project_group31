#ifndef MINISTL_H
#define MINISTL_H

// --- Custom String Class ---
class String {
private:
    char* data;
    unsigned long length;

public:
    String() : data(nullptr), length(0) {}
    
    String(const char* str) {
        unsigned long len = 0;
        while (str[len]) len++;
        length = len;
        data = new char[length + 1];
        for (unsigned long i = 0; i < length; i++) data[i] = str[i];
        data[length] = '\0';
    }

    String(const String& other) {
        length = other.length;
        if (other.data) {
            data = new char[length + 1];
            for (unsigned long i = 0; i < length; i++) data[i] = other.data[i];
            data[length] = '\0';
        } else {
            data = nullptr;
        }
    }

    ~String() { if (data) delete[] data; }

    String& operator=(const String& other) {
        if (this == &other) return *this;
        if (data) delete[] data;
        
        length = other.length;
        if (other.data) {
            data = new char[length + 1];
            for (unsigned long i = 0; i < length; i++) data[i] = other.data[i];
            data[length] = '\0';
        } else {
            data = nullptr;
            length = 0;
        }
        return *this;
    }

    const char* c_str() const { return data ? data : ""; }
};

// --- Custom Vector Template ---
template <typename T>
class Vector {
private:
    T* data;
    unsigned long capacity;
    unsigned long count;

public:
    Vector() : data(nullptr), capacity(0), count(0) {}

    ~Vector() { if (data) delete[] data; }

    void push_back(T element) {
        if (count == capacity) {
            unsigned long newCapacity = (capacity == 0) ? 1 : capacity * 2;
            T* newData = new T[newCapacity];
            
            for (unsigned long i = 0; i < count; i++) {
                newData[i] = data[i];
            }
            
            if (data) delete[] data;
            data = newData;
            capacity = newCapacity;
        }
        data[count] = element;
        count++;
    }

    void clear() {
        count = 0; 
        // We keep capacity to avoid reallocations
    }

    bool empty() const { return count == 0; }
    unsigned long size() const { return count; }

    T& operator[](unsigned long index) { return data[index]; }
    const T& operator[](unsigned long index) const { return data[index]; }

    // Iterators for range-based loops
    T* begin() { return data; }
    T* end() { return data + count; }
    const T* begin() const { return data; }
    const T* end() const { return data + count; }
};

#endif