#include <iostream>
#include <fstream>
#include "Figura.h"
#include "Kolekcija.h"
#include "Kvadrat.h"
#include "Pravougaonik.h"

using namespace std;

int main()
{

	Figura* f1 = new Kvadrat(1.1, 2.2, 5);

	cout << *f1 << endl;

	Figura* f2 = new Pravougaonik(3.3, 5.5, 5, 6);

	cout << *f2 << endl;

	ifstream ulaz("ulaz.txt");
	if (ulaz.good())
	{
		int nmax, n;
		float x, y, visina, sirina;
		char tip;
		ulaz >> nmax;
		ulaz >> n;
		Kolekcija k(nmax);
		for (int i = 0; i < n; i++)
		{
			ulaz >> tip;
			if (tip == 'p')
			{
				ulaz >> x >> y >> visina >> sirina;
				k.Add(new Pravougaonik(visina, sirina, x, y));
			}
			else if (tip == 'k')
			{
				ulaz >> x >> y >> visina;
				k.Add(new Kvadrat(visina, x, y));
			}
		}

		k.Save("izlaz1.txt");

		Kvadrat* k1 = new Kvadrat();
		k1->upisi(ulaz);
		k.Add(k1);

		Pravougaonik* p1 = new Pravougaonik();
		p1->upisi(ulaz);
		k.Add(p1);

		Kvadrat* k2 = new Kvadrat();
		k2->upisi(ulaz);
		k.Add(k2);

		Kvadrat* k3 = new Kvadrat();
		k3->upisi(ulaz);
		k.Add(k3);

	}

}
