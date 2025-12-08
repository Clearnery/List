#pragma once
#include <istream>    
#include <ostream>    
#include <vector>     
#include <functional> 
#include <string>     
#include <iostream>

template<class T>
class TArrayList 
{
private:
    int* next;          
    T** data;          
    int root;           
    int size;           
    int capacity;       

public:
    
    class Iterator 
    {
    private:
        TArrayList<T>* list;  
        int current;          

    public:
        Iterator() : list(nullptr), current(-1) {}
        Iterator(TArrayList<T>* lst, int index) : list(lst), current(index) {}

        T& operator*() {
            return *(list->data[current]);
        }

        T* operator->() 
        {
            return list->data[current];
        }

        
        Iterator& operator++() 
        {
            if (current != -1) 
            {
                current = list->next[current];
            }
            return *this;
        }

        
        Iterator operator++(int) 
        {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const 
        {
            return list == other.list && current == other.current;
        }

        bool operator!=(const Iterator& other) const 
        {
            return !(*this == other);
        }

        explicit operator bool() const 
        {
            return current != -1;
        }

        int getIndex() const 
        {
            return current;
        }
    };

    
    TArrayList(int initialCapacity = 10);
    TArrayList(const TArrayList& other);
    TArrayList(TArrayList&& other) noexcept;
    ~TArrayList();

    
    int getSize() const;
    int getCapacity() const;
    int getRoot() const;
    bool isEmpty() const;
    bool isFull() const;

    
    void setRoot(int newRoot);
    void setSize(int newSize);
    void resize(int newCapacity);

    
    TArrayList& operator=(const TArrayList& other);
    TArrayList& operator=(TArrayList&& other) noexcept;
    bool operator==(const TArrayList& other) const;
    bool operator!=(const TArrayList& other) const;
    TArrayList operator+(const TArrayList& other) const;
    T& operator[](int index);
    const T& operator[](int index) const;

    
    friend std::istream& operator>>(std::istream& in, TArrayList<T>& list);
    friend std::ostream& operator<<(std::ostream& out, const TArrayList<T>& list);

    
    void pushFront(const T& value);
    void pushBack(const T& value);
    void insertAfter(int index, const T& value);
    T popFront();
    T popBack();
    void remove(int index);

    
    int count(const T& value) const;
    std::vector<int> findAll(const T& value) const;
    void forEach(std::function<void(T&)> func);
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);

    
    Iterator begin();
    Iterator end();

    void clear();

private:
    
    int allocateNode();
    void freeNode(int index);
    int findNodeByIndex(int position) const;
    int findNodeByValue(const T& value) const;
    void ensureCapacity(int requiredCapacity);
};