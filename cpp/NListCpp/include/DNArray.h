#ifndef DNARRAY_H
#define DNARRAY_H

#include <iostream>
#include <string>
#include <typeindex>


class DNArray{
protected:
    class Item{
    public:
        enum Statuses {NONE = 0, ACTIVE = 1, INACTIVE = -1};

    protected:
        Statuses status;
        size_t type;
        void* data;

    public:
        Item(){
            status = NONE;
            type = 0;
            data = nullptr;
        }

        ~Item(){
            delete data;
        }


        void operator=(const Item& otr){
            status = otr.status;
            type = otr.type;
            data = otr.data;
        }


        size_t getTypeHash(){
            return type;
        }

        template<typename T>
        T get(){
            switch(status)
            {
            case ACTIVE:
                if(typeid(T).hash_code() != type){}

                return *static_cast<T*>(data);
            case INACTIVE:
                break;
            default:
                break;
            }
        }

        template<typename T>
        void set(T value){
            type = typeid(value).hash_code();
            data = &value;
        }

        void deactivate(){
            status = INACTIVE;
        }
    };


    const long long int capacityDefault = 10;
    long long int _size, inactiveSize, capacity, capacityMax = 9999999999;

    Item* items;


    void initialize(){
        items = new Item[capacity];

        _size = 0;
        inactiveSize = 0;
    }

    void organize(int fromIndex, int toIndex, int order){
        for(int i = 0; i < abs(toIndex - fromIndex); i++){
            items[fromIndex + i] = items[fromIndex+order + i];
        }
    }

    void expand(int expandCapacity){
        if(capacity + expandCapacity > capacityMax) return;
        capacity += expandCapacity;

        items = (Item*) realloc(items, capacity * sizeof(Item));
    }
    void expand(){
        int expandCapacity = 1;

        for(int p = 50; p > 0; p--){
            if(int(capacity+_size*p/100) < capacityMax){
                expandCapacity = _size*p/100;

                break;
            }
        }

        expand(expandCapacity);
    }

public:
    DNArray(){
        capacity = capacityDefault;

        initialize();
    }
    DNArray(int capacity){
        capacity < capacityMax ? capacity = capacity : capacity = capacityMax;

        initialize();
    }

    ~DNArray(){
        clear();
    }


    void operator=(const DNArray& otr){
        _size = otr._size;
        capacity = otr.capacity;
        capacityMax = otr.capacityMax;
        items = otr.items;
    }
    Item operator[](const int index){
        return get(index);
    }


    int size(){
        return _size;
    }

    int sizeInBytes(){
        return sizeof(items);
    }

    std::string toString(int fromIndex, int toIndex){
        std::string output = "[";
        if(fromIndex > -1 && toIndex < capacity){
            //output += to_string(_array[fromIndex].get());
            for(int i = fromIndex+1; i <= toIndex; i++){
                //output += ", " + to_string(_array[i].value);
            }
        }
        output += "]";

        return output;
    }
    std::string toString(){
        return toString(0, _size-1);
    }
    std::string toString(bool all){
        return toString(0, capacity-1);
    }


    Item get(int index){
        if(index > -1 && index < _size){
            Item item = items[index];

            return item;
        }

        return Item();
    }

    template<typename T>
    void add(T value){
        if(capacity > _size*5) expand(-_size);

        if(_size < capacity){
            Item item;
            item.set(value);

            items[_size] = item;
            _size++;
        }
        else if(capacity < capacityMax){
            expand();

            add(value);
        }
    }

    void remove(int index){
        if(index > -1 && index < _size){
            Item item = items[index];
            item.deactivate();
            _size--;

            if(inactiveSize < capacity/5){
                items[capacity - inactiveSize - 1] = item;
                inactiveSize++;
            }

            organize(index, _size, 1);
        }
    }

    void clear(){
        delete [] items;

        initialize();
    }
};

#endif // DNARRAY_H
