#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "Akvarijum.h"
#include "Valjak.h"
#include "Kvadar.h"
#include "Polica.h"
using namespace std;
void main(){
	const char* tip_akvarijuma[] = { "akvarijum slatke vode", "akvarijum slane vode", "bez vode - terarijum" };
	// 2 poena
	Akvarijum* p1 = new Valjak(5.0, 10.1, tip_akvarijuma[0], false);
	//p1.print();
	cout << "Prvi Akvarijum: \n" << *p1 << "\n----------------------------------" << endl;
	// 2 poena
	Akvarijum* p2 = new Kvadar(200, 40, 55, tip_akvarijuma[1], true);
	//p2.print();
	cout << "Drugi Akvarijum: \n" << *p2 << "\n----------------------------------" << endl;
	Polica p(4);
	Polica* pp = new Polica(4);
	// 2 poena
	for (int i = 0; i < p.BrojAkvarijuma() / 2; i++)	{
		p.Add(new Valjak(100 + i * 5, i * 3, tip_akvarijuma[(2 * i) % 3], i % 2));
		p.Add(new Kvadar(1000 + i * 20.37, (i + 1) * i, i * 3, tip_akvarijuma[(2 * i + 1) % 3], (i + 1) % 2));
	}
	for (int i = 0; i < pp->BrojAkvarijuma() / 2; i++)	{
		pp->Add(new Valjak(100 + i * 5, i * 3, tip_akvarijuma[(2 * i) % 3], i % 2));
		pp->Add(new Kvadar(1000 + i * 20.37, (i + 1) * i, i * 3, tip_akvarijuma[(2 * i + 1) % 3], (i + 1) % 2));	}
	// 2 poena	//p.print();
	cout << "Posle dodavanja: \n " << p << "\n----------------------------------" << endl;
	// 2 poena
	delete pp;
	// 2
	cout << "Ukupna Povrsina: \n " << p.UkupnaPovrsinaStakla() << "\n----------------------------------" << endl;
	// 2
	cout << "Ukupni Obim: \n " << p.UkupnaZapremina() << "\n----------------------------------" << endl;
	// 3 poena
	Polica* ppp = p.PrebacitiAkvarijume(tip_akvarijuma[2]);
	//ppp->print();
	cout << "Prebaceni Akvarijumi: \n" << *ppp << "\n----------------------------------" << endl;
	// 3 poena
	Akvarijum* pmin = nullptr;	int ind;
	p.Min(&ind, &pmin);
	cout << "Min" << ind << " " << *pmin << "\n----------------------------------" << endl;}