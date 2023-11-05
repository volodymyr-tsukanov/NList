#include <iostream>
#include <ctime>
#include <List>
#include "DNArray.h"

using namespace std;


int main()
{
    bool b; int i; float f; double d; char c; string s; long int li; long long int lli;

    cout << "bool: " << typeid(b).hash_code() << endl;
    cout << "int: " << typeid(i).hash_code() << endl;
    cout << "float: " << typeid(f).hash_code() << endl;
    cout << "double: " << typeid(d).hash_code() << endl;
    cout << "char: " << typeid(c).hash_code() << endl;
    cout << "string: " << typeid(s).hash_code() << endl;
    cout << "long int: " << typeid(li).hash_code() << endl;
    cout << "long long int: " << typeid(lli).hash_code() << endl;
}
