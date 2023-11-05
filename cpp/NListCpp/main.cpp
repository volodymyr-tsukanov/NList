#include <iostream>
#include <ctime>
#include <List>
#include "DNArray.h"

using namespace std;


int main()
{
    DNArray dna = DNArray(100);
    dna.add<int>(12);
    dna.add<bool>(true);
    dna.add<float>(2.7);
    dna.add<char>('O');

    cout << dna[0].getTypeHash() << ": " << dna[0].get<int>() << endl;
}
