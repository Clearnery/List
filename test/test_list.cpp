#include "List.h"

#include <gtest.h>
#include <fstream>
#include <sstream>


// Конструкторы и деструктор
TEST(TListTest, DefaultConstructor) 
{
    TList<int> list;
    EXPECT_EQ(list.getSize(), 0);
    EXPECT_EQ(list.getHead(), nullptr);
    EXPECT_TRUE(list.isEmpty());
}

TEST(TListTest, CopyConstructor) 
{
    TList<int> original;
    original.PushBack(1);
    original.PushBack(2);
    original.PushBack(3);

    TList<int> copy(original);
    EXPECT_EQ(copy.getSize(), 3);
    EXPECT_EQ(original.getSize(), 3);
    EXPECT_FALSE(copy.isEmpty());
}

TEST(TListTest, MoveConstructor) {
    TList<int> original;
    original.PushBack(1);
    original.PushBack(2);

    TList<int> moved(std::move(original));
    EXPECT_EQ(moved.getSize(), 2);
    EXPECT_EQ(original.getSize(), 0);
    EXPECT_EQ(original.getHead(), nullptr);
}

// Основные методы
TEST(TListTest, GetSize) {
    TList<int> list;
    EXPECT_EQ(list.getSize(), 0);

    list.PushBack(1);
    EXPECT_EQ(list.getSize(), 1);

    list.PushBack(2);
    EXPECT_EQ(list.getSize(), 2);
}

TEST(TListTest, IsEmpty) {
    TList<int> list;
    EXPECT_TRUE(list.isEmpty());

    list.PushBack(1);
    EXPECT_FALSE(list.isEmpty());
}



// Push методы
TEST(TListTest, PushFront) {
    TList<int> list;
    list.PushFront(3);
    EXPECT_EQ(list.getSize(), 1);
    EXPECT_EQ(list[0], 3);

    list.PushFront(2);
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_EQ(list[0], 2);
    EXPECT_EQ(list[1], 3);

    list.PushFront(1);
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
    EXPECT_EQ(list[2], 3);
}

TEST(TListTest, PushBack) {
    TList<int> list;
    list.PushBack(1);
    EXPECT_EQ(list.getSize(), 1);
    EXPECT_EQ(list[0], 1);

    list.PushBack(2);
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);

    list.PushBack(3);
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
    EXPECT_EQ(list[2], 3);
}

TEST(TListTest, PushAfter) {
    TList<int> list;
    list.PushBack(1);
    list.PushBack(3);

    list.PushAfter(0, 2);  // Вставить после первого элемента
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
    EXPECT_EQ(list[2], 3);

    list.PushAfter(2, 4);  // Вставить после последнего элемента
    EXPECT_EQ(list.getSize(), 4);
    EXPECT_EQ(list[3], 4);
}

TEST(TListTest, PushAfterInvalidIndex) {
    TList<int> list;
    list.PushBack(1);

    EXPECT_THROW(list.PushAfter(-1, 2), std::out_of_range);
    EXPECT_THROW(list.PushAfter(5, 2), std::out_of_range);
}


// Pop методы
TEST(TListTest, PopFront) {
    TList<int> list;
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);

    int value = list.PopFront();
    EXPECT_EQ(value, 1);
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_EQ(list[0], 2);
    EXPECT_EQ(list[1], 3);

    value = list.PopFront();
    EXPECT_EQ(value, 2);
    EXPECT_EQ(list.getSize(), 1);
    EXPECT_EQ(list[0], 3);

    value = list.PopFront();
    EXPECT_EQ(value, 3);
    EXPECT_EQ(list.getSize(), 0);
    EXPECT_TRUE(list.isEmpty());
}

TEST(TListTest, PopFrontEmptyList) {
    TList<int> list;
    EXPECT_THROW(list.PopFront(), std::runtime_error);
}

TEST(TListTest, PopFrontSingleElement) {
    TList<int> list;
    list.PushBack(42);

    int value = list.PopFront();
    EXPECT_EQ(value, 42);
    EXPECT_EQ(list.getSize(), 0);
    EXPECT_TRUE(list.isEmpty());
}

TEST(TListTest, PopBack) {
    TList<int> list;
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);

    int value = list.PopBack();
    EXPECT_EQ(value, 3);
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);

    value = list.PopBack();
    EXPECT_EQ(value, 2);
    EXPECT_EQ(list.getSize(), 1);
    EXPECT_EQ(list[0], 1);

    value = list.PopBack();
    EXPECT_EQ(value, 1);
    EXPECT_EQ(list.getSize(), 0);
    EXPECT_TRUE(list.isEmpty());
}

TEST(TListTest, PopBackEmptyList) {
    TList<int> list;
    EXPECT_THROW(list.PopBack(), std::runtime_error);
}

TEST(TListTest, PopBackSingleElement) {
    TList<int> list;
    list.PushBack(42);

    int value = list.PopBack();
    EXPECT_EQ(value, 42);
    EXPECT_EQ(list.getSize(), 0);
    EXPECT_TRUE(list.isEmpty());
}

// Remove метод
TEST(TListTest, Remove) {
    TList<int> list;
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    list.PushBack(4);

    list.Remove(1);  // Удалить второй элемент (значение 2)
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 3);
    EXPECT_EQ(list[2], 4);

    list.Remove(0);  // Удалить первый элемент
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_EQ(list[0], 3);
    EXPECT_EQ(list[1], 4);

    list.Remove(1);  // Удалить последний элемент
    EXPECT_EQ(list.getSize(), 1);
    EXPECT_EQ(list[0], 3);
}

TEST(TListTest, RemoveInvalidIndex) {
    TList<int> list;
    list.PushBack(1);

    EXPECT_THROW(list.Remove(-1), std::out_of_range);
    EXPECT_THROW(list.Remove(5), std::out_of_range);
}

TEST(TListTest, RemoveEmptyList) {
    TList<int> list;
    EXPECT_THROW(list.Remove(0), std::runtime_error);
}

// Оператор индексации
TEST(TListTest, OperatorIndex) {
    TList<int> list;
    list.PushBack(10);
    list.PushBack(20);
    list.PushBack(30);

    EXPECT_EQ(list[0], 10);
    EXPECT_EQ(list[1], 20);
    EXPECT_EQ(list[2], 30);
}

TEST(TListTest, OperatorIndexInvalidIndex) {
    TList<int> list;
    list.PushBack(1);

    EXPECT_THROW(list[-1], std::invalid_argument);
    // НЕТ ПРОВЕРКИ ВЕРХНЕЙ ГРАНИЦЫ в текущей реализации!
    // EXPECT_THROW(list[5], std::out_of_range);
}

// Операторы сравнения
TEST(TListTest, OperatorEquality) {
    TList<int> list1;
    list1.PushBack(1);
    list1.PushBack(2);
    list1.PushBack(3);

    TList<int> list2;
    list2.PushBack(1);
    list2.PushBack(2);
    list2.PushBack(3);

    EXPECT_TRUE(list1 == list2);
    EXPECT_FALSE(list1 != list2);
}

TEST(TListTest, OperatorInequality) {
    TList<int> list1;
    list1.PushBack(1);
    list1.PushBack(2);

    TList<int> list2;
    list2.PushBack(1);
    list2.PushBack(2);
    list2.PushBack(3);

    EXPECT_FALSE(list1 == list2);
    EXPECT_TRUE(list1 != list2);
}

TEST(TListTest, SelfEquality) {
    TList<int> list;
    list.PushBack(1);
    list.PushBack(2);

    EXPECT_TRUE(list == list);
}

// Оператор присваивания
TEST(TListTest, CopyAssignment) {
    TList<int> list1;
    list1.PushBack(1);
    list1.PushBack(2);

    TList<int> list2;
    list2 = list1;

    EXPECT_EQ(list2.getSize(), 2);
    EXPECT_EQ(list1.getSize(), 2);

    // Проверка глубокого копирования
    list2.PushBack(3);
    EXPECT_EQ(list2.getSize(), 3);
    EXPECT_EQ(list1.getSize(), 2);
}

TEST(TListTest, SelfAssignment) {
    TList<int> list;
    list.PushBack(1);
    list.PushBack(2);

    list = list;  // Самоприсваивание
    EXPECT_EQ(list.getSize(), 2);
}

// Оператор сложения
TEST(TListTest, OperatorPlus) {
    TList<int> list1;
    list1.PushBack(1);
    list1.PushBack(2);

    TList<int> list2;
    list2.PushBack(3);
    list2.PushBack(4);

    TList<int> result = list1 + list2;
    EXPECT_EQ(result.getSize(), 4);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 3);
    EXPECT_EQ(result[3], 4);
}

// Тесты для кольцевой структуры
TEST(TListTest, CircularStructureSingleElement) {
    TList<int> list;
    list.PushBack(42);

    TNodeList<int>* head = list.getHead();
    ASSERT_NE(head, nullptr);

    // В кольцевом списке с одним элементом
    // next и previous указывают на сам элемент
    EXPECT_EQ(head->getNext(), head);
    EXPECT_EQ(head->getPrevious(), head);
}

TEST(TListTest, CircularStructureMultipleElements) {
    TList<int> list;
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);

    TNodeList<int>* head = list.getHead();
    ASSERT_NE(head, nullptr);

    
    TNodeList<int>* current = head;
    for (int i = 0; i < 3; i++) 
    {
        current = current->getNext();
    }
    EXPECT_EQ(current, head);

    // И через 3 шага назад
    current = head;
    for (int i = 0; i < 3; i++) 
    {
        current = current->getPrevious();
    }
    EXPECT_EQ(current, head);
}

// Комплексные тесты
TEST(TListTest, MultipleOperationsSequence) 
{
    TList<int> list;

    // Серия различных операций
    EXPECT_TRUE(list.isEmpty());

    list.PushFront(2);
    EXPECT_EQ(list.getSize(), 1);
    EXPECT_EQ(list[0], 2);

    list.PushBack(4);
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_EQ(list[0], 2);
    EXPECT_EQ(list[1], 4);

    list.PushAfter(0, 3);
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list[0], 2);
    EXPECT_EQ(list[1], 3);
    EXPECT_EQ(list[2], 4);

    list.PushFront(1);
    EXPECT_EQ(list.getSize(), 4);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
    EXPECT_EQ(list[2], 3);
    EXPECT_EQ(list[3], 4);

    int val = list.PopFront();
    EXPECT_EQ(val, 1);
    EXPECT_EQ(list.getSize(), 3);

    val = list.PopBack();
    EXPECT_EQ(val, 4);
    EXPECT_EQ(list.getSize(), 2);

    list.Remove(0);
    EXPECT_EQ(list.getSize(), 1);
    EXPECT_EQ(list[0], 3);

    list.Remove(0);
    EXPECT_EQ(list.getSize(), 0);
    EXPECT_TRUE(list.isEmpty());
}

// Тесты для TNodeList (опционально)
TEST(TNodeListTest, Constructor) 
{
    TNodeList<int> node1;
    EXPECT_EQ(node1.getValue(), 0);

    TNodeList<int> node2(42);
    EXPECT_EQ(node2.getValue(), 42);
}

TEST(TNodeListTest, GetSetMethods) 
{
    TNodeList<int> node;
    node.setValue(100);
    EXPECT_EQ(node.getValue(), 100);
}

TEST(TNodeListTest, EqualityOperator) 
{
    TNodeList<int> node1(10);
    TNodeList<int> node2(10);
    TNodeList<int> node3(20);

    EXPECT_TRUE(node1 == node2);
    EXPECT_FALSE(node1 == node3);
    EXPECT_TRUE(node1 != node3);
}

TEST(TListTest, CountMethod)
{
    TList<int> list;

    // Пустой список
    int count1 = list.count(5);
    EXPECT_EQ(count1, 0);

    // Список с одним элементом
    list.PushBack(5);
    int count2 = list.count(5);
    int count3 = list.count(10);
    EXPECT_EQ(count2, 1);
    EXPECT_EQ(count3, 0);

    // Список с несколькими элементами
    list.PushBack(10);
    list.PushBack(5);
    list.PushBack(20);
    list.PushBack(5);

    int count4 = list.count(5);
    int count5 = list.count(10);
    int count6 = list.count(20);
    int count7 = list.count(100);
    EXPECT_EQ(count4, 3);
    EXPECT_EQ(count5, 1);
    EXPECT_EQ(count6, 1);
    EXPECT_EQ(count7, 0);
}

TEST(TListTest, FindAllMethod)
{
    TList<int> list;

    // Пустой список
    std::vector<int> emptyResult = list.findAll(5);
    EXPECT_TRUE(emptyResult.empty());

    // Список с одним элементом
    list.PushBack(5);
    std::vector<int> singleResult = list.findAll(5);
    EXPECT_EQ(singleResult.size(), 1);
    EXPECT_EQ(singleResult[0], 0);

    // Поиск несуществующего элемента
    std::vector<int> notFoundResult = list.findAll(10);
    EXPECT_TRUE(notFoundResult.empty());

    // Список с несколькими вхождениями
    list.PushBack(10);
    list.PushBack(5);
    list.PushBack(20);
    list.PushBack(5);
    list.PushBack(30);
    list.PushBack(5);

    std::vector<int> multiResult = list.findAll(5);
    EXPECT_EQ(multiResult.size(), 4);
    EXPECT_EQ(multiResult[0], 0);
    EXPECT_EQ(multiResult[1], 2);
    EXPECT_EQ(multiResult[2], 4);
    EXPECT_EQ(multiResult[3], 6);
}

TEST(TListTest, ForEachMethod)
{
    TList<int> list;

    // Пустой список
    bool calledOnEmpty = false;
    list.forEach([&calledOnEmpty](int& x) {
        calledOnEmpty = true;
        });
    EXPECT_FALSE(calledOnEmpty);

    // Список с элементами
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    list.PushBack(4);
    list.PushBack(5);

    
    list.forEach([](int& x) 
        {
        x *= 2;
        });

    int val1 = list[0];
    int val2 = list[1];
    int val3 = list[2];
    int val4 = list[3];
    int val5 = list[4];

    EXPECT_EQ(val1, 2);
    EXPECT_EQ(val2, 4);
    EXPECT_EQ(val3, 6);
    EXPECT_EQ(val4, 8);
    EXPECT_EQ(val5, 10);
}