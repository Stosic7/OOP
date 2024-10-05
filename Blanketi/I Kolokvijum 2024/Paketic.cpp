#include <iostream>
#include <fstream>
#include "Paketic.h" 
#include "Cokolada.h"
#include "Igracka.h"
// sve heahdere implementiramo

using namespace std;

void Paketic::zauzmiMem(int _maxEl) // prvo funkcija za zauzimanje memorije
{

	top = 0; // vrh niza je na 0, nema elemente
	maxEl = _maxEl; // maxEl uzima prosledjeni broj iz arguemnta (to je sada najveci broj elemenata koje niza moze da ima)

	niz = new Poklon * [maxEl]; // niz uzima vrednost Poklon*[maxEl] to jest inicijalizuje se da niz moze da prima mazEl poklona
	for (int i = 0; i < maxEl; i++) // za sve elemente
		niz[i] = nullptr; // se vrednost postavlja na nullptr, nema elemenata

}

void Paketic::oslobodimem() // oslobdjanje memorije
{

	if (niz != nullptr) // ako niz ima elemente
		for (int i = 0; i < maxEl; i++)  // dok se ne dodje do maxEl
			if (niz[i] != nullptr) // ako na tom mestu u nizu ima element
				delete niz[i]; // brise se

	delete[] niz; // na kraju se dinamicki brise ceo niz, kad se na svim pozicijama odstrani element na pozicijama i

}

Paketic::Paketic() // default konsturktor
{

	niz = nullptr; // niz na null
	top = maxEl = 0; // ostalo na 0

}

Paketic::Paketic(int _maxEl)
{

	zauzmiMem(_maxEl); // za custom konstruktor se zauzme memorija

}

Paketic :: ~Paketic()
{

	oslobodimem(); // za destuktor se oslobodi memorija

}

void Paketic::Add(Poklon* p) // dodavanje
{

	if (top < maxEl) // ako nije doslo do prekoracenja
		niz[top++] = p; // dodaje se element

	/* moglo je i ovako ako vam je lakse tako
	if (top < maxEl)
		niz[top] = p;
		top++;
	*/

	// cesto moze da se zahteva u zadatku da se memorija prosiri ako dodje do prekoracenja, to vama dajem da sami eksperimentisete,
	// ali ja bih to uradio tako sto bih napravio funkciju prosiriMemoriju() i nju bih pozvao u funkciji Add ako je top == maxEl ili ako je top > maxEl
	// implementacija te funkcije je relativno laka, ako vam treba pomoc, pisite mi

}

Paketic::Paketic(const Paketic& og) // copy
{

	zauzmiMem(og.maxEl); // zauzmemo memoriju za og.maxEl
	for (int i = 0; i < og.top; i++) // ovo bi trebalo da je jasno
	{
		if (typeid(*og.niz[i]) == typeid(Cokolada)) // proverava se tip
			Add(new Cokolada(*dynamic_cast<Cokolada*>(og.niz[i]))); // dinamicki cast, mrzi me da ga objasnjavam, treba vam 5 minuta na yt da ga skontate, a mislim da se i ovde lepo vidi sta se desava
		else
			Add(new Igracka(*dynamic_cast<Igracka*>(og.niz[i])));
	}
} //OVO

Paketic Paketic :: operator+(const Paketic p) // operator+
{

	Paketic novi(maxEl + p.maxEl); //obejkat  novi koji ima kao argument konstuktora zbir maks elemenata

	for (int i = 0; i < maxEl; i++) // jedna for petlja za maxEl jedna za p.maxEl
	{
		if (typeid(*niz[i]) == typeid(Cokolada)) // isto se radi kao za copy
			novi.Add(new Cokolada(*dynamic_cast<Cokolada*>(niz[i])));
		else
			novi.Add(new Igracka(*dynamic_cast<Igracka*>(niz[i])));
	}

	for (int i = 0; i < p.maxEl; i++)
	{
		if (typeid(*p.niz[i]) == typeid(Cokolada))
			novi.Add(new Cokolada(*dynamic_cast<Cokolada*>(p.niz[i])));
		else
			novi.Add(new Igracka(*dynamic_cast<Igracka*>(p.niz[i])));
	}

	return novi; // ne zaboravite na return

} // OVO

void Paketic::Save(const char* filename) // cuvanje
{

	ofstream izlaz(filename); // pravi se objekat ofstreama.
	if (izlaz.good()) // self explained 
		izlaz << *this; // vraca se objekat *this, *this se uci na prvi termin vezbi, ako ste zaboravili pogledajte video
	izlaz.close(); // mora close

}

Poklon* Paketic::Max() const // max
{

	Poklon* max = niz[0]; // max se stavlja kao prvi el niza
	for (int i = 1; i < top; i++) // prolazi kroz sve elemente niza
		if (niz[i]->vratiBrojMasnica() > max->vratiBrojMasnica()) // uporedjuje ih
			max = niz[i];

	return max; // vraca max

}

void Paketic::RemoveMinimum(Poklon** p)
{

	if (top == 0) // granicni uslov
		return;

	int min = 0;
	for (int i = 1; i < top; i++)
		if (niz[i]->vratiBrojMasnica() < niz[i]->vratiBrojMasnica())
			min = i; // pamti se min

	*p = niz[min]; // u prvi *p se pamti min el niza

	for (int i = min; i < top - 1; i++) // brisemo ga
		niz[i] = niz[i + 1];

	niz[top - 1] = *p; // updatejujemo
	top--; // smanjujemo elemente niza

}

ostream& operator<<(ostream& izlaz, const Paketic& p) // operator<<
{
	for (int i = 0; i < p.maxEl; i++)
		if (p.niz[i] != nullptr)
			p.niz[i]->prikazi(izlaz); // poziva se prikazi
	return izlaz;
}
