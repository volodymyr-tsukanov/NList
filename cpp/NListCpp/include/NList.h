#ifndef NLIST_H
#define NLIST_H

#include <iostream>
#include "List.h"


template<typename Type>
class NList
{
    protected:
    struct item{
        Type value;

        item* prev;
        item* next;
    };

    struct point{
        int position;

        item* current;
    };

private:
    item* head;
    item* tail;

    List<point, MultiDirectional> points;

    int size, pointStep;

    void recalculatePoints(){
        for(int i = points.getSize()-1; i > -1 ; i--)
        {
            if(points.get(i).position > size-1) points.removeEnd();
            else break;
        }

        float pos = (float)(size-2) / pointStep;
        if(pos > 0 && pos - (int)pos == 0)
        {
            points.add(point{size-2, tail->prev});
            //cout << "point: " << size-2 << endl;
        }
    }

    item* getItem(unsigned int position){
        item* temp = nullptr;

        if(points.isEmpty()){
            if(position-1 < (int)(size/2)){
                temp = head;

                for(int i = 0; i < position; i++) temp = temp->next;
            }
            else{
                temp = tail;

                for(int i = size-1; i > position; i--) temp = temp->prev;
            }
        }
        else{
            point s, e;

            if(position < pointStep){
                s = point{0, head};
                e = points.getStart();
            }
            else if(position == pointStep) return points.getStart().current;
            else if(position > size-pointStep){
                s = points.getEnd();
                e = point{size-1, tail};
            }
            else if(position == size-pointStep) return points.getEnd().current;
            else{
                int pos = position / pointStep;

                s = points.get(pos-1);
                e = points.get(pos);

                if(position == s.position) return s.current;
            }

            int diff = position - s.position - pointStep/2;
            //cout << "diff: " << diff << endl;

            if(diff <= 0){
                temp = s.current;

                for(int i = s.position; i < position; i++) temp = temp->next;
            }
            if(diff > 0){
                temp = e.current;

                for(int i = e.position; i > position; i--) temp = temp->prev;
            }
        }

        return temp;
    }

public:
    NList(){
        head = nullptr;
        tail = nullptr;

        size = 0;

        pointStep = 25000;
    }
    NList(unsigned int _pointStep):NList(){
        pointStep = _pointStep;
    }

    ~NList(){
        clear();

        delete head;
        delete tail;
    }

    void operator=(const NList& otr){
        head = otr.head;
        tail = otr.tail;
        points = otr.points;

        size = otr.size;
        pointStep = otr.pointsStep;
    }
    void operator+=(const NList& otr){
        item* temp = otr.head;
        for(int i = 0; i < otr.getSize(); i++){
            add(temp->value);

            temp = temp->next;
        }

        recalculatePoints();
    }
    bool operator==(const NList& otr){
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
    NList operator+(NList& otr){
        NList res = clone();

        item* temp = otr.head;
        for(int i = 0; i < otr.getSize(); i++){
            res.add(temp->value);

            temp = temp->next;
        }

        res.recalculatePoints();

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
        return size * (sizeof(Type) + 2*sizeof(item)) + points.getSize() *(sizeof(item) + sizeof(unsigned int));
    }

    void add(Type value){
        item* it = new item;
        it->value = value;
        it->next = nullptr;

        if(tail == nullptr){
            head = it;
        }
        else{
            tail->next = it;
            it->prev = tail;
        }

        tail = it;

        size++;

        recalculatePoints();
    }
    void addStart(Type value){
        item* it = new item;
        it->value = value;
        it->next = head;
        it->prev = nullptr;
        head = it;

        if(tail == nullptr) tail = it;

        size++;

        recalculatePoints();
    }
    void addPosition(Type value, unsigned int position){
        if(position < size-1){
            if(position == 0) addStart(value);
            else{
                item* temp = getItem(position-1);

                item* it = new item;
                it->value = value;

                it->next = temp->next;
                temp->next->prev = it;
                temp->next = it;
                it->prev = temp;

                size++;

                recalculatePoints();
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
                item* temp = getItem(position);

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

            delete del;

            size--;

            recalculatePoints();
        }
    }
    void removeEnd(){
        if(!isEmpty()){
            item* temp;
            item* del;

            del = tail;
            tail = tail->prev;

            delete del;

            size--;

            recalculatePoints();
        }
    }
    void remove(unsigned int position){
        if(!isEmpty()){
            if(position == 0) removeStart();
            else if(position == size-1) removeEnd();
            else{
                item* temp = getItem(position-1);

                item* del = temp->next;
                temp->next = del->next;

                delete del;

                size--;

                recalculatePoints();
            }
        }
    }

    void clear(){
        points.clear();

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

    NList clone(){
        NList _clone = NList();

        item* temp = head;
        while(temp != nullptr){
            _clone.add(temp->value);

            temp = temp->next;
        }

        _clone.points = points.clone();
        _clone.pointStep = pointStep;

        return _clone;
    }

    void print(char separator = ' '){
        item* temp = head;

        while(temp != nullptr){
            std::cout << temp->value << separator;

            temp = temp->next;
        }
        std::cout << std::endl;
    }
};

#endif // NLIST_H
