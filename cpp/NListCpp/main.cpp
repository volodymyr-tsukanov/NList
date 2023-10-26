#include <iostream>
#include <ctime>
#include "nlist.h"

using namespace std;


int main()
{
    unsigned int sz = 999999, cp = 25000;
    cout << "Size: ";
    cin >> sz;
    cout << "Capacity: ";
    cin >> cp;
    int tm, szHalf = (int)(sz/2), szQater = (int)(sz/4);

    tm = clock();
    NList<int> nl = NList<int>(cp);
    for(int i = 0; i < sz; i++) nl.add(i+1);
    cout << "Nl creation: " << clock() - tm << "ms\n\n";

    printf("Nl size: %.1fmb\n\n", nl.sizeOf() / 1024. / 1024);

    tm = clock();
    cout << nl[szQater];
    cout << "\nNl get 1/4: " << clock() - tm << "ms\n\n";

    tm = clock();
    cout << nl[szHalf];
    cout << "\nNl get 1/2: " << clock() - tm << "ms\n\n";

    tm = clock();
    cout << nl[szHalf + szQater];
    cout << "\nNl get 3/4: " << clock() - tm << "ms\n\n";

    int g = 1;
    while(g > 0){
        tm = clock();
        cout << nl[g];
        printf("\nNl get %d: %dms\n\n", g, clock() - tm);

        cout << "Get: ";
        cin >> g;
    }

    tm = clock();
    nl.clear();
    cout << "Nl clear: " << clock() - tm << "ms\n\n";
}
