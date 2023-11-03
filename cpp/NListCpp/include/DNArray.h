#ifndef DNARRAY_H
#define DNARRAY_H

#include <iostream>
#include <string>


class DNArray{
public:
    enum ElementTypes {Boolean = 3, Char = 21, Integer = 11, Float = 13 , Double = 15, String = 31};


    class ArrayElement{
    public:
        ArrayElement(){
        }

        ~ArrayElement(){
        }


        void operator=(const ArrayElement& otr){
            status = otr.status;
            type = otr.type;
            set(otr.type, otr.get());
        }

    private:
        enum Statuses {none = 0, active = 1, inactive = -1};

        union Data{
            bool _boolean;
            char _char;
            int _integer;
            float _float;
            double _double;
            std::string _string;
        };

        Statuses status;
        ElementTypes type;

    public:
        template <typename T>
        T get(ElementTypes et){
            switch(et){
                case Boolean:
                    return static_cast<T>(Data._boolean);
                case Char:
                    return static_cast<T>(Data._char);
                case Integer:
                    return static_cast<T>(Data._integer);
                case Float:
                    return static_cast<T>(Data._float);
                case Double:
                    return static_cast<T>(Data._double);
                case String:
                    return static_cast<T>(Data._string);
                case default:
                    return nullptr;
            }
        }

        template<typename T>
        void set(T value){
            switch(_type){
                case Boolean:
                    data._boolean = valueAdress;
                    break;
                case Char:
                    return &data._char;
                    break;
                case Integer:
                    return &data._integer;
                    break;
                case Float:
                    return &data._float;
                    break;
                case Double:
                    return &data._double;
                    break;
                case String:
                    return &data._string;
                    break;
            }
        }
    };


    const long int capacityDefault = 10;
    long int _size, _inactiveSize, _capacity, _capacityMax = 9999999999;

    ArrayElement* _array;


    void initialize(){
        _array = new ArrayElement[_capacity];

        _size = 0;
        _inactiveSize = 0;
    }

    void organize(int fromIndex, int toIndex, int order){
        for(int i = 0; i < abs(toIndex - fromIndex); i++){
            _array[fromIndex + i] = _array[fromIndex+order + i];
        }
    }

    void expand(int expandCapacity){
        if(_capacity + expandCapacity > _capacityMax) return;
        _capacity += expandCapacity;

        _array = (ArrayElement*) realloc(_array, _capacity * sizeof(ArrayElement));
    }
    void expand(){
        int expandCapacity = 1;

        for(int p = 50; p > 0; p--){
            if(int(_capacity+_size*p/100) < _capacityMax){
                expandCapacity = _size*p/100;

                break;
            }
        }

        expand(expandCapacity);
    }

public:
    DNArray(){
        _capacity = capacityDefault;

        initialize();
    }
    DNArray(int capacity){
        capacity < _capacityMax ? _capacity = capacity : _capacity = _capacityMax;

        initialize();
    }

    ~DNArray(){
        clear();
    }


    int size(){
        return _size;
    }

    int sizeInBytes(){
        return sizeof(_array);
    }

    std::string toString(int fromIndex, int toIndex){
        std::string output = "[";
        if(fromIndex > -1 && toIndex < _capacity){
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
        return toString(0, _capacity-1);
    }


    template <typename T> T get(int index){
        if(index > -1 && index < _size){
            ArrayElement element = _array[index];

            return element.value;
        }

        return NULL;
    }

    template <typename T> void add(T _element){
        if(_capacity > _size*5) expand(-_size);

        if(_size < _capacity){
            ArrayElement element;
            element.status = ArrayElement::active;
            element.value = _element;

            _array[_size] = element;
            _size++;
        }
        else if(_capacity < _capacityMax){
            expand();

            add(_element);
        }
    }

    void remove(int index){
        if(index > -1 && index < _size){
            ArrayElement element = _array[index];
            element.status = element.inactive;
            _size--;

            if(_inactiveSize < _capacity/5){
                _array[_capacity - _inactiveSize - 1] = element;
                _inactiveSize++;
            }

            organize(index, _size, 1);
        }
    }

    void clear(){
        delete [] _array;

        initialize();
    }
};

#endif // DNARRAY_H
