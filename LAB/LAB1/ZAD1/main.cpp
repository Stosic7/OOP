#include <iostream>
#include <fstream>
#include "Skup.h"

using namespace std;

int main() {
    Skup* skup1 = new Skup(10);

    cout << "Unesite prvo broj elemenata skupa, a nakon toga i elemente tog skupa: (maks 10)\n";
    cin >> *skup1;

    int broj1, broj2;
    cout << "Unesite dva broja za ispitivanje pripadnosti skupu:\n";
    cin >> broj1 >> broj2;
    cout << "Pripadnost broja " << broj1 << " skupu: " << skup1->pripadnostSkupa(broj1) << endl;
    cout << "Pripadnost broja " << broj2 << " skupu: " << skup1->pripadnostSkupa(broj2) << endl;

    Skup* skup2 = new Skup(*skup1);

    cout << "Originalni skup:\n";
    cout << *skup1 << endl;

    skup1->sortiraj();
    cout << "Sortiran skup:\n";
    cout << *skup1 << endl;

    skup1->izbaciDuplikate();
    cout << "Skup bez duplikata:\n";
    cout << *skup1 << endl;

    skup1->citaj(cin);
    skup1->prikazi(cout);

    delete skup1;
    delete skup2;

    return 0;
}
