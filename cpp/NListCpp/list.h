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
    List(){
        head = nullptr;
        tail = nullptr;

        size = 0;
    }

    ~List(){
        clear();

        delete head;
        delete tail;
    }

    void operator=(const List& otr){
        head = otr.head;
        tail = otr.tail;

        size = otr.size;
    }
    void operator+=(const List& otr){
        item* temp = otr.head;
        for(int i = 0; i < otr.size; i++){
            add(temp->value);

            temp = temp->next;
        }
    }
    bool operator==(const List& otr){
        if(size == otr.size){
            item* temp = head;
            item* temp2 = otr.head;

            for(int i = 0; i < size; i++){
                if(temp == temp2){
                    temp = temp->next;
                    temp2 = temp2->next;
                }
                else return false;
            }

            return true;
        }
        else return false;
    }
    List operator+(List& otr){
        List res = clone();

        item* temp = otr.head;
        for(int i = 0; i < otr.getSize(); i++){
            res.add(temp->value);

            temp = temp->next;
        }

        return res;
    }
    Type operator[](unsigned int index){
        return get(index);
    }

    bool isEmpty(){
        return head == nullptr && tail == nullptr;
    }

    int getSize(){
        return size;
    }

    int sizeOf(){
        if(listType == OneDirectional || listType == CycledOneDirectional)
            return size * (sizeof(Type) + sizeof(item));

        if(listType == MultiDirectional || listType == CycledMultiDirectional)
            return size * (sizeof(Type) + 2*sizeof(item));
    }

    void add(Type value){
        item* it = new item;
        it->value = value;
        it->next = nullptr;
        if(listType == CycledOneDirectional || listType == CycledMultiDirectional) it->next = head;

        if(tail == nullptr){
            head = it;
        }
        else{
            tail->next = it;
            if(listType == MultiDirectional || listType == CycledMultiDirectional) it->prev = tail;
        }

        tail = it;

        size++;
    }
    void addStart(Type value){
        item* it = new item;
        it->value = value;
        it->next = head;
        if(listType == MultiDirectional) it->prev = nullptr;
        if(listType == CycledMultiDirectional) it->prev = tail;
        head = it;

        if(tail == nullptr) tail = it;

        size++;
    }
    void addPosition(Type value, unsigned int position){
        if(position < size-1){
            if(position == 0) addStart(value);
            else{
                item* temp = head;

                for(int i = 0; i < position-1; i++){
                    temp = temp->next;
                }

                item* it = new item;
                it->value = value;
                it->next = temp->next;

                if(listType == MultiDirectional || listType == CycledMultiDirectional){
                    it->prev = temp;
                    it->next->prev = it;
                }
                temp->next = it;

                size++;
            }
        }
        else add(value);
    }

    Type getStart(){
        Type value;

        if(!isEmpty()){
            value = head->value;
        }

        return value;
    }
    Type getEnd(){
        Type value;

        if(!isEmpty()){
            value = tail->value;
        }

        return value;
    }
    Type get(unsigned int position){
        Type value;

        if(!isEmpty()){
            if(position == 0) return getStart();
            if(position == size-1) return getEnd();
            else{
                item* temp = head;

                for(int i = 0; i < position; i++){
                    temp = temp->next;
                }

                value = temp->value;
            }
        }

        return value;
    }

    void removeStart(){
        if(!isEmpty()){
            item* del = head;

            if(head == tail){
                head = nullptr;
                tail = nullptr;
            }
            else{
                head = del->next;
            }

            if(listType == CycledOneDirectional) tail->next = head;
            if(listType == CycledMultiDirectional){
                head->prev = tail;
                tail->next = head;
            }

            delete del;

            size--;
        }
    }
    void removeEnd(){
        if(!isEmpty()){
            item* temp;
            item* del;

            if(listType == OneDirectional || listType == CycledOneDirectional){
                temp = head;

                for(int i = 0; i < size-1-1; i++){
                    temp = temp->next;
                }

                del = temp->next;
                temp->next = nullptr;
                if(listType == CycledOneDirectional) temp->next = head;
                tail = temp;
            }

            if(listType == MultiDirectional || listType == CycledMultiDirectional){
                del = tail;
                tail = tail->prev;
                tail->next = nullptr;
                if(listType == CycledMultiDirectional) tail->next = head;
            }

            delete del;

            size--;
        }
    }
    void remove(unsigned int position){
        if(!isEmpty()){
            if(position == 0) removeStart();
            else if(position == size-1) removeEnd();
            else{
                item* temp = head;

                for(int i = 0; i < position-1; i++){
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

    void clear(){
        while(!isEmpty()){
            item* del = head;

            if(head == tail){
                head = nullptr;
                tail = nullptr;
            }
            else{
                head = del->next;
            }

            delete del;
        }

        size = 0;
    }

    List clone(){
        List _clone = List();

        item* temp = head;
        while(temp != endItem()){
            _clone.add(temp->value);

            temp = temp->next;
        }

        return _clone;
    }

    void print(char separator = ' '){
        item* temp = head;

        if(isEmpty())return;

        cout << temp->value;
        temp = temp->next;
        while(temp != endItem()){
            cout << separator << temp->value;

            temp = temp->next;
        }
        cout << endl;
    }
};

#endif // LIST_H
