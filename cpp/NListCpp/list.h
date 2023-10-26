#ifndef LIST_H
#define LIST_H

#include <iostream>


enum ListType{ OneDirectional = 1, MultiDirectional = 6, CycledOneDirectional = 11, CycledMultiDirectional = 16 };

template<typename Type, ListType listType>
class List{
protected:
    struct item{
        Type value;

        item* prev;
        item* next;
    };

private:
    item* head;
    item* tail;

    int size;

    const item* endItem();

public:
    List();

    ~List();

    void operator=(const List& otr);
    void operator+=(const List& otr);
    bool operator==(const List& otr);
    List operator+(List& otr);
    Type operator[](unsigned int index);

    bool isEmpty();

    int getSize();

    int sizeOf();

    void add(Type value);
    void addStart(Type value);
    void addPosition(Type value, unsigned int position);

    Type getStart();
    Type getEnd();
    Type get(unsigned int position);

    void removeStart();
    void removeEnd();
    void remove(unsigned int position);

    void clear();

    List clone();

    void print(char separator = ' ');
};

#endif // LIST_H
