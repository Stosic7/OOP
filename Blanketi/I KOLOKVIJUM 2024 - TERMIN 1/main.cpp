#include <iostream>
#include <fstream>
#include "Figura.h"
#include "Krug.h"
#include "Pravougaonik.h"
#include "Kanvas.h"
using namespace std;
void main()
{
	const char* boje[] = { "zelena", "plava", "crvena", "zuta", "roze" };
	// 2 poena
	Figura* p1 = new Krug(5.0, boje[0]);
	//p1.print();
	cout << "Prva Figura: \n" << *p1 << "\n----------------------------------" << endl;
	// 2 poena
	Figura* p2 = new Pravougaonik(399.99, 1, boje[1]);
	//p2.print();
	cout << "Druga Figura: \n" << *p2 << "\n----------------------------------" << endl;
	Kanvas p(4);
	Kanvas* pp = new Kanvas(4);
	// 2 poena
	for (int i = 0; i < p.BrojFigura() / 2; i++)
	{
		p.Add(new Krug(100 + i * 5, boje[(2 * i) % 5]));
		p.Add(new Pravougaonik(1000 + i * 20.37, (i + 1) * i, boje[(2 * i + 1) % 5]));
	}
	for (int i = 0; i < pp->BrojFigura() / 2; i++)
	{
		pp->Add(new Krug(100 + i * 5, boje[(2 * i) % 5]));
		pp->Add(new Pravougaonik(1000 + i * 20.37, (i + 1) * i, boje[(2 * i + 1) % 5]));
	}
	// 2 poena
	//p.print();
	cout << "Posle dodavanja: \n " << p << "\n----------------------------------" << endl;
	// 2 poena
	delete pp;
	// 2
	cout << "Ukupna Povrsina: \n " << p.UkupnaPovrsina() << "\n----------------------------------" << endl;
	// 2
	cout << "Ukupni Obim: \n " << p.UkupanObim() << "\n----------------------------------" << endl;
	// 3 poena
	Kanvas* ppp = p.PrebacitiPoBoji(boje[2]);
	//ppp->print();
	cout << "Prebacene boje: \n" << *ppp << "\n----------------------------------" << endl;
	// 3 poena
	Figura* pmax = nullptr;
	int ind;
	p.Max(&pmax, &ind);
	cout << "Max" << ind << " " << *pmax << "\n----------------------------------" << endl;
}
