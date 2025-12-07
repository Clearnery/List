#pragma once


template<class T>
class TArrayList {
private:
    int* next;          // Массив индексов следующих элементов
    T** data;           // Массив указателей на данные
    int root;           // Индекс корня (головы списка)
    int size;           // Текущее количество элементов
    int capacity;       // Вместимость массивов

public:
    // Класс итератора
    class Iterator 
    {
    private:
        TArrayList<T>* list;  // Указатель на список
        int current;          // Текущий индекс

    public:
        Iterator() : list(nullptr), current(-1) {}
        Iterator(TArrayList<T>* lst, int index) : list(lst), current(index) {}

        T& operator*() {
            return *(list->data[current]);
        }

        T* operator->() {
            return list->data[current];
        }

        // Префиксный инкремент
        Iterator& operator++() {
            if (current != -1) {
                current = list->next[current];
            }
            return *this;
        }

        // Постфиксный инкремент
        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return list == other.list && current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

        explicit operator bool() const {
            return current != -1;
        }

        int getIndex() const {
            return current;
        }
    };

    // Конструкторы и деструктор
    TArrayList(int initialCapacity = 10);
    TArrayList(const TArrayList& other);
    TArrayList(TArrayList&& other) noexcept;
    ~TArrayList();

    // Основные методы доступа
    int getSize() const;
    int getCapacity() const;
    int getRoot() const;
    bool isEmpty() const;
    bool isFull() const;

    // Изменение состояния
    void setRoot(int newRoot);
    void setSize(int newSize);
    void resize(int newCapacity);

    // Операторы
    TArrayList& operator=(const TArrayList& other);
    TArrayList& operator=(TArrayList&& other) noexcept;
    bool operator==(const TArrayList& other) const;
    bool operator!=(const TArrayList& other) const;
    TArrayList operator+(const TArrayList& other) const;
    T& operator[](int index);
    const T& operator[](int index) const;

    // Ввод/вывод
    friend std::istream& operator>>(std::istream& in, TArrayList<T>& list);
    friend std::ostream& operator<<(std::ostream& out, const TArrayList<T>& list);

    // Основные операции со списком
    void pushFront(const T& value);
    void pushBack(const T& value);
    void insertAfter(int index, const T& value);
    T popFront();
    T popBack();
    void remove(int index);

    // Поиск
    int count(const T& value) const;
    std::vector<int> findAll(const T& value) const;

    // Обработка элементов
    void forEach(std::function<void(T&)> func);
    void forEach(std::function<void(const T&)> func) const;

    // Работа с файлами
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);

    // Итераторы
    Iterator begin();
    Iterator end();

    // Вспомогательные методы
    void clear();
    void printDebug() const;  // Для отладки

private:
    // Приватные вспомогательные методы
    int allocateNode();
    void freeNode(int index);
    int findNodeByIndex(int position) const;
    int findNodeByValue(const T& value) const;
    void ensureCapacity(int requiredCapacity);
};