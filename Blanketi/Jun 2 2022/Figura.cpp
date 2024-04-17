#include <iostream>
#include <fstream>
#include "Figura.h"

using namespace std;

Figura::Figura()
{

	x = y = 0;

}

Figura::Figura(double _x, double _y)
{

	x = _x;
	y = _y;

}

Figura::Figura(const Figura& og)
{

	x = og.x;
	y = og.y;

}

ostream& operator<<(ostream& os, const Figura& f)
{

	f.ispisi(os);

	return os;

}
