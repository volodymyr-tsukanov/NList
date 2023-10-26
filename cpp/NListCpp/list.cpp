#include <iostream>
#include "list.h"

using namespace std;


List::endItem()
{
    if(listType == OneDirectional || listType == MultiDirectional) return nullptr;
    else return head;
}
