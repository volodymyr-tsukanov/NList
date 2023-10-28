#include <iostream>
#include <ctime>
#include "list.h"

using namespace std;


int main()
{
    List<int, OneDirectional> l1 = List<int, OneDirectional>();
    l1.add(42);
    l1.print();
    l1.clear();
    /*unsigned int sz = 999999, cp = 25000;
    cout << "Size: ";
    cin >> sz;
    cout << "Capacity: ";
    cin >> cp;
    int tm, szHalf = (int)(sz/2), szQater = (int)(sz/4);

    tm = clock();
    List<int, OneDirectional> l1 = List<int, OneDirectional>();
    l1.print();
    //l1ist<int> n1 = l1ist<int>(cp);
    for(int i = 0; i < sz; i++) l1.add(i+1);
    cout << "l1 creation: " << clock() - tm << "ms\n\n";

    printf("l1 size: %.1fmb\n\n", l1.sizeOf() / 1024. / 1024);

    tm = clock();
    cout << l1[szQater];
    cout << "\nl1 get 1/4: " << clock() - tm << "ms\n\n";

    tm = clock();
    cout << l1[szHalf];
    cout << "\nl1 get 1/2: " << clock() - tm << "ms\n\n";

    tm = clock();
    cout << l1[szHalf + szQater];
    cout << "\nl1 get 3/4: " << clock() - tm << "ms\n\n";

    int g = 1;
    while(g > 0){
        tm = clock();
        cout << l1[g];
        printf("\nl1 get %d: %dms\n\n", g, clock() - tm);

        cout << "Get: ";
        cin >> g;
    }

    tm = clock();
    l1.clear();
    cout << "l1 clear: " << clock() - tm << "ms\n\n";*/
}
