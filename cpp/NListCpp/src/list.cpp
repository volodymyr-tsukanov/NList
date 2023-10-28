#include "list.h"

using namespace std;


template<typename Type, ListType listType>
List<Type, listType>::List(){
    head = nullptr;
    tail = nullptr;

    size = 0;
}

template<typename Type, ListType listType>
List<Type, listType>::~List()
{
    clear();

    delete head;
    delete tail;
}

template<typename Type, ListType listType>
void List<Type, listType>::operator=(const List& otr)
{
    head = otr.head;
    tail = otr.tail;

    size = otr.size;
}
template<typename Type, ListType listType>
void List<Type, listType>::operator+=(const List& otr)
{
    item* temp = otr.head;
    for(int i = 0; i < otr.size; i++)
    {
        add(temp->value);

        temp = temp->next;
    }
}
template<typename Type, ListType listType>
bool List<Type, listType>::operator==(const List& otr)
{
    if(size == otr.size)
    {
        item* temp = head;
        item* temp2 = otr.head;

        for(int i = 0; i < size; i++)
        {
            if(temp == temp2)
            {
                temp = temp->next;
                temp2 = temp2->next;
            }
            else return false;
        }

        return true;
    }
    else return false;
}
template<typename Type, ListType listType>
typename List<Type, listType>::List List<Type, listType>::operator+(List& otr)
{
    List res = clone();

    item* temp = otr.head;
    for(int i = 0; i < otr.getSize(); i++)
    {
        res.add(temp->value);

        temp = temp->next;
    }

    return res;
}
template<typename Type, ListType listType>
Type List<Type, listType>::operator[](unsigned int index)
{
    return get(index);
}

template<typename Type, ListType listType>
bool List<Type, listType>::isEmpty()
{
    return head == nullptr && tail == nullptr;
}

template<typename Type, ListType listType>
int List<Type, listType>::getSize()
{
    return size;
}

template<typename Type, ListType listType>
int List<Type, listType>::sizeOf()
{
    if(listType == OneDirectional || listType == CycledOneDirectional)
        return size * (sizeof(Type) + sizeof(item));

    if(listType == MultiDirectional || listType == CycledMultiDirectional)
        return size * (sizeof(Type) + 2*sizeof(item));
}

template<typename Type, ListType listType>
void List<Type, listType>::add(Type value)
{
    item* it = new item;
    it->value = value;
    it->next = nullptr;
    if(listType == CycledOneDirectional || listType == CycledMultiDirectional) it->next = head;

    if(tail == nullptr)
    {
        head = it;
    }
    else
    {
        tail->next = it;
        if(listType == MultiDirectional || listType == CycledMultiDirectional) it->prev = tail;
    }

    tail = it;

    size++;
}
template<typename Type, ListType listType>
void List<Type, listType>::addStart(Type value)
{
    item* it = new item;
    it->value = value;
    it->next = head;
    if(listType == MultiDirectional) it->prev = nullptr;
    if(listType == CycledMultiDirectional) it->prev = tail;
    head = it;

    if(tail == nullptr) tail = it;

    size++;
}
template<typename Type, ListType listType>
void List<Type, listType>::addPosition(Type value, unsigned int position)
{
    if(position < size-1)
    {
        if(position == 0) addStart(value);
        else
        {
            item* temp = head;

            for(int i = 0; i < position-1; i++)
            {
                temp = temp->next;
            }

            item* it = new item;
            it->value = value;
            it->next = temp->next;

            if(listType == MultiDirectional || listType == CycledMultiDirectional)
            {
                it->prev = temp;
                it->next->prev = it;
            }
            temp->next = it;

            size++;
        }
    }
    else add(value);
}

template<typename Type, ListType listType>
Type List<Type, listType>::getStart()
{
    Type value;

    if(!isEmpty())
    {
        value = head->value;
    }

    return value;
}
template<typename Type, ListType listType>
Type List<Type, listType>::getEnd()
{
    Type value;

    if(!isEmpty())
    {
        value = tail->value;
    }

    return value;
}
template<typename Type, ListType listType>
Type List<Type, listType>::get(unsigned int position)
{
    Type value;

    if(!isEmpty())
    {
        if(position == 0) return getStart();
        if(position == size-1) return getEnd();
        else
        {
            item* temp = head;

            for(int i = 0; i < position; i++)
            {
                temp = temp->next;
            }

            value = temp->value;
        }
    }

    return value;
}

template<typename Type, ListType listType>
void List<Type, listType>::removeStart()
{
    if(!isEmpty())
    {
        item* del = head;

        if(head == tail)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            head = del->next;
        }

        if(listType == CycledOneDirectional) tail->next = head;
        if(listType == CycledMultiDirectional)
        {
            head->prev = tail;
            tail->next = head;
        }

        delete del;

        size--;
    }
}
template<typename Type, ListType listType>
void List<Type, listType>::removeEnd()
{
    if(!isEmpty())
    {
        item* temp;
        item* del;

        if(listType == OneDirectional || listType == CycledOneDirectional)
        {
            temp = head;

            for(int i = 0; i < size-1-1; i++)
            {
                temp = temp->next;
            }

            del = temp->next;
            temp->next = nullptr;
            if(listType == CycledOneDirectional) temp->next = head;
            tail = temp;
        }

        if(listType == MultiDirectional || listType == CycledMultiDirectional)
        {
            del = tail;
            tail = tail->prev;
            tail->next = nullptr;
            if(listType == CycledMultiDirectional) tail->next = head;
        }

        delete del;

        size--;
    }
}
template<typename Type, ListType listType>
void List<Type, listType>::remove(unsigned int position)
{
    if(!isEmpty())
    {
        if(position == 0) removeStart();
        else if(position == size-1) removeEnd();
        else
        {
            item* temp = head;

            for(int i = 0; i < position-1; i++)
            {
                temp = temp->next;
            }

            item* del = temp->next;
            temp->next = del->next;
            if(listType == MultiDirectional || listType == CycledMultiDirectional)
                temp->next->prev = temp;

            delete del;

            size--;
        }
    }
}

template<typename Type, ListType listType>
void List<Type, listType>::clear()
{
    while(!isEmpty())
    {
        item* del = head;

        if(head == tail)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            head = del->next;
        }

        delete del;
    }

    size = 0;
}

template<typename Type, ListType listType>
typename List<Type, listType>::List List<Type, listType>::clone()
{
    List _clone = List();

    item* temp = head;
    while(temp != endItem())
    {
        _clone.add(temp->value);

        temp = temp->next;
    }

    return _clone;
}

template<typename Type, ListType listType>
void List<Type, listType>::print(char separator)
{
    item* temp = head;

    if(isEmpty())return;

    cout << temp->value;
    temp = temp->next;
    while(temp != endItem())
    {
        cout << separator << temp->value;

        temp = temp->next;
    }
    cout << endl;
}
