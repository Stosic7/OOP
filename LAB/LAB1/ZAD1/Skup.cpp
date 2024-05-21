#include <iostream>
#include <fstream>
#include "Skup.h"

using namespace std;

Skup::Skup()
{

	brojelemenata = 0;
	niz = 0;

}

Skup::Skup(int _brojelemenata)
{

	brojelemenata = _brojelemenata;

}

Skup :: ~Skup()
{

	delete[] niz;

}

Skup::Skup(const Skup& og)
{

	brojelemenata = og.brojelemenata;

	niz = new int[og.brojelemenata];
	for (int i = 0; i < og.brojelemenata; i++)
	{

		niz[i] = og.niz[i];

	}

	if (og.brojelemenata < 0)
		niz = nullptr;

}

void Skup::izbaciDuplikate()
{

	if (brojelemenata < 2)
		return;

	for (int i = 0; i < brojelemenata - 1; i++)
	{

		for (int j = i + 1; j < brojelemenata; j++)
		{

			if (niz[j] > niz[j + 1])
			{
				int temp = niz[j];
				niz[j] = niz[j + 1];
				niz[j + 1] = temp;
			}
		}

	}

	int pomocna = 1;
	for (int i = 1; i < brojelemenata; i++)
	{

		if (niz[i] != niz[i - 1])
		{

			niz[pomocna] = niz[i];
			pomocna++;

		}

	}

	brojelemenata = pomocna;

}

bool Skup::pripadnostSkupa(int el)
{

	for (int i = 0; i < brojelemenata; i++)
	{

		if (niz[i] == el)
		{

			return true;

		}

	}

	return false;

}

void Skup:: sortiraj() {
	for (int i = 0; i < brojelemenata - 1; ++i) {
		for (int j = 0; j < brojelemenata - i - 1; ++j) {
			if (niz[j] < niz[j + 1]) {
				int temp = niz[j];
				niz[j] = niz[j + 1];
				niz[j + 1] = temp;
			}
		}
	}
}

void Skup::citaj(istream& ulaz) {
	ulaz >> brojelemenata;
	delete[] niz;
	niz = new int[brojelemenata];
	for (int i = 0; i < brojelemenata; ++i) {
		ulaz >> niz[i];
	}
}

void Skup::prikazi(ostream& izlaz) const {
	for (int i = 0; i < brojelemenata; ++i) {
		izlaz << niz[i] << " ";
	}
	izlaz << std::endl;
}

ostream& operator<<(ostream& izlaz, const Skup& s) {
	izlaz << "{ ";
	for (int i = 0; i < s.brojelemenata; ++i) {
		izlaz << s.niz[i];
		if (i < s.brojelemenata - 1) {
			izlaz << ", ";
		}
	}
	izlaz << " }";
	return izlaz;
}

istream& operator>>(istream& ulaz, Skup& s) {
	ulaz >> s.brojelemenata;
	delete[] s.niz;
	s.niz = new int[s.brojelemenata];
	for (int i = 0; i < s.brojelemenata; ++i) {
		ulaz >> s.niz[i];
	}
	return ulaz;
}
