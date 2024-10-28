// Zadatak 0: Klasa Complex i main
#include <iostream>
using namespace std;

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    friend ostream& operator<<(ostream& os, const Complex& c) {
        os << c.real << "+" << c.imag << "i";
        return os;
    }

    friend istream& operator>>(istream& is, Complex& c) {
        is >> c.real >> c.imag;
        return is;
    }
};

int main() {
    Complex c1, c2;
    cout << "Unesite prvi kompleksni broj (realni i imaginarni deo): ";
    cin >> c1;
    cout << "Unesite drugi kompleksni broj (realni i imaginarni deo): ";
    cin >> c2;

    Complex zbir = c1 + c2;
    Complex razlika = c1 - c2;

    cout << "Zbir: " << zbir << endl;
    cout << "Razlika: " << razlika << endl;
    return 0;
}

// Zadatak 1: Klasa Ispit i main
#include <iostream>
#include <cstring>
using namespace std;

class Ispit {
private:
    char* imeIspita;
    char datum[11];
    int ocena;

public:
    Ispit(const char* ime = "", const char* dat = "", int o = 0) : ocena(o) {
        imeIspita = new char[strlen(ime) + 1];
        strcpy(imeIspita, ime);
        strcpy(datum, dat);
    }

    ~Ispit() {
        delete[] imeIspita;
    }

    bool operator>(const Ispit& other) const {
        return ocena > other.ocena;
    }

    friend ostream& operator<<(ostream& os, const Ispit& i) {
        os << "Ispit: " << i.imeIspita << ", Datum: " << i.datum << ", Ocena: " << i.ocena;
        return os;
    }

    friend istream& operator>>(istream& is, Ispit& i) {
        char temp[100];
        cout << "Unesite ime ispita: ";
        is >> temp;
        i.imeIspita = new char[strlen(temp) + 1];
        strcpy(i.imeIspita, temp);
        cout << "Unesite datum (yyyy-MM-dd): ";
        is >> i.datum;
        cout << "Unesite ocenu: ";
        is >> i.ocena;
        return is;
    }
};

int main() {
    Ispit i1, i2;
    cin >> i1 >> i2;
    if (i1 > i2) {
        cout << "Ispit 1 ima bolju ocenu." << endl;
    } else {
        cout << "Ispit 2 ima bolju ocenu ili su ocene iste." << endl;
    }
    cout << "Podaci o ispitu 1: " << i1 << endl;
    cout << "Podaci o ispitu 2: " << i2 << endl;
    return 0;
}

// Zadatak 2: Klasa Poligon i main
#include <iostream>
using namespace std;

class Poligon {
private:
    int brojTemena;
    int* x;
    int* y;

public:
    Poligon(int n) : brojTemena(n) {
        x = new int[n];
        y = new int[n];
    }

    ~Poligon() {
        delete[] x;
        delete[] y;
    }

    void preslikajX() {
        for (int i = 0; i < brojTemena; ++i) {
            y[i] = -y[i];
        }
    }

    void preslikajY() {
        for (int i = 0; i < brojTemena; ++i) {
            x[i] = -x[i];
        }
    }

    friend ostream& operator<<(ostream& os, const Poligon& p) {
        os << "Temena poligona: ";
        for (int i = 0; i < p.brojTemena; ++i) {
            os << "(" << p.x[i] << ", " << p.y[i] << ") ";
        }
        return os;
    }

    friend istream& operator>>(istream& is, Poligon& p) {
        for (int i = 0; i < p.brojTemena; ++i) {
            cout << "Unesite koordinate temena " << i + 1 << " (x y): ";
            is >> p.x[i] >> p.y[i];
        }
        return is;
    }
};

int main() {
    Poligon p(4);
    cin >> p;
    cout << "Poligon pre preslikavanja: " << p << endl;
    p.preslikajX();
    cout << "Poligon nakon preslikavanja u odnosu na x osu: " << p << endl;
    p.preslikajY();
    cout << "Poligon nakon preslikavanja u odnosu na y osu: " << p << endl;
    return 0;
}

// Zadatak 3: Klasa Image i main
#include <iostream>
using namespace std;

class Image {
private:
    int dim;
    int** matrica;

public:
    Image(int d) : dim(d) {
        matrica = new int*[dim];
        for (int i = 0; i < dim; ++i) {
            matrica[i] = new int[dim];
        }
    }

    ~Image() {
        for (int i = 0; i < dim; ++i) {
            delete[] matrica[i];
        }
        delete[] matrica;
    }

    void invertuj() {
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                matrica[i][j] = 1 - matrica[i][j];
            }
        }
    }

    friend ostream& operator<<(ostream& os, const Image& img) {
        for (int i = 0; i < img.dim; ++i) {
            for (int j = 0; j < img.dim; ++j) {
                os << img.matrica[i][j] << " ";
            }
            os << endl;
        }
        return os;
    }

    friend istream& operator>>(istream& is, Image& img) {
        cout << "Unesite sadrzaj slike: \n";
        for (int i = 0; i < img.dim; ++i) {
            for (int j = 0; j < img.dim; ++j) {
                is >> img.matrica[i][j];
            }
        }
        return is;
    }
};

int main() {
    Image img(3);
    cin >> img;
    cout << "Originalna slika: \n" << img;
    img.invertuj();
    cout << "Inverz slika: \n" << img;
    return 0;
}

// Zadatak 4: Klasa Complex i main (ponovno)
#include <iostream>
#include <cmath>
using namespace std;

class Complex2 {
private:
    double real;
    double imag;

public:
    Complex2(double r = 0, double i = 0) : real(r), imag(i) {}

    double modul() const {
        return sqrt(real * real + imag * imag);
    }

    friend ostream& operator<<(ostream& os, const Complex2& c) {
        os << c.real << "+" << c.imag << "i";
        return os;
    }

    friend istream& operator>>(istream& is, Complex2& c) {
        is >> c.real >> c.imag;
        return is;
    }
};

int main() {
    Complex2 c;
    cout << "Unesite kompleksni broj (realni i imaginarni deo): ";
    cin >> c;
    cout << "Modul kompleksnog broja je: " << c.modul() << endl;
    return 0;
}

// Zadatak 5: Klasa Tacka i main
#include <iostream>
using namespace std;

class Tacka {
private:
    double x, y, z;

public:
    Tacka(double a = 0, double b = 0, double c = 0) : x(a), y(b), z(c) {}

    Tacka operator+(const Tacka& other) const {
        return Tacka(x + other.x, y + other.y, z + other.z);
    }

    friend ostream& operator<<(ostream& os, const Tacka& t) {
        os << "(" << t.x << ", " << t.y << ", " << t.z << ")";
        return os;
    }

    friend istream& operator>>(istream& is, Tacka& t) {
        is >> t.x >> t.y >> t.z;
        return is;
    }
};

int main() {
    Tacka t1, t2;
    cout << "Unesite prvu tacku (x y z): ";
    cin >> t1;
    cout << "Unesite drugu tacku (x y z): ";
    cin >> t2;
    Tacka suma = t1 + t2;
    cout << "Zbir tacaka je: " << suma << endl;
    return 0;
}

// Zadatak 6: Klasa Minesweeper i main
#include <iostream>
using namespace std;

class Minesweeper {
private:
    int dim;
    bool** polje;

public:
    Minesweeper(int d) : dim(d) {
        polje = new bool*[dim];
        for (int i = 0; i < dim; ++i) {
            polje[i] = new bool[dim]();
        }
    }

    ~Minesweeper() {
        for (int i = 0; i < dim; ++i) {
            delete[] polje[i];
        }
        delete[] polje;
    }

    void pomeriMineDesno() {
        for (int i = 0; i < dim; ++i) {
            bool last = polje[i][dim - 1];
            for (int j = dim - 1; j > 0; --j) {
                polje[i][j] = polje[i][j - 1];
            }
            polje[i][0] = last;
        }
    }

    friend ostream& operator<<(ostream& os, const Minesweeper& m) {
        for (int i = 0; i < m.dim; ++i) {
            for (int j = 0; j < m.dim; ++j) {
                os << m.polje[i][j] << " ";
            }
            os << endl;
        }
        return os;
    }

    friend istream& operator>>(istream& is, Minesweeper& m) {
        cout << "Unesite polje (0 ili 1 za svaku celiju):\n";
        for (int i = 0; i < m.dim; ++i) {
            for (int j = 0; j < m.dim; ++j) {
                is >> m.polje[i][j];
            }
        }
        return is;
    }
};

int main() {
    Minesweeper m(3);
    cin >> m;
    cout << "Originalno polje:\n" << m;
    m.pomeriMineDesno();
    cout << "Polje nakon pomeranja mina udesno:\n" << m;
    return 0;
}

// Zadatak 7: Klasa Matrica i main
#include <iostream>
using namespace std;

class Matrica {
private:
    int redovi;
    int kolone;
    double** matrica;

public:
    Matrica(int r, int k) : redovi(r), kolone(k) {
        matrica = new double*[redovi];
        for (int i = 0; i < redovi; ++i) {
            matrica[i] = new double[kolone];
        }
    }

    ~Matrica() {
        for (int i = 0; i < redovi; ++i) {
            delete[] matrica[i];
        }
        delete[] matrica;
    }

    friend ostream& operator<<(ostream& os, const Matrica& m) {
        for (int i = 0; i < m.redovi; ++i) {
            for (int j = 0; j < m.kolone; ++j) {
                os << m.matrica[i][j] << " ";
            }
            os << endl;
        }
        return os;
    }

    friend istream& operator>>(istream& is, Matrica& m) {
        cout << "Unesite elemente matrice:\n";
        for (int i = 0; i < m.redovi; ++i) {
            for (int j = 0; j < m.kolone; ++j) {
                is >> m.matrica[i][j];
            }
        }
        return is;
    }
};

int main() {
    Matrica m(3, 3);
    cin >> m;
    cout << "Matrica:\n" << m;
    return 0;
}

// Zadatak 8: Klasa String i main
#include <iostream>
#include <cstring>
using namespace std;

class String {
private:
    char* niz;
    int duzina;

public:
    String(const char* str = "") {
        duzina = strlen(str);
        niz = new char[duzina + 1];
        strcpy(niz, str);
    }

    ~String() {
        delete[] niz;
    }

    void toUpperCase() {
        for (int i = 0; i < duzina; ++i) {
            niz[i] = toupper(niz[i]);
        }
    }

    friend ostream& operator<<(ostream& os, const String& s) {
        os << s.niz;
        return os;
    }

    friend istream& operator>>(istream& is, String& s) {
        char temp[100];
        is >> temp;
        s.duzina = strlen(temp);
        delete[] s.niz;
        s.niz = new char[s.duzina + 1];
        strcpy(s.niz, temp);
        return is;
    }
};

int main() {
    String s;
    cout << "Unesite string: ";
    cin >> s;
    cout << "Originalni string: " << s << endl;
    s.toUpperCase();
    cout << "String velikim slovima: " << s << endl;
    return 0;
}

// Zadatak 9: Klasa Picture i main
#include <iostream>
using namespace std;

class Picture {
private:
    int dim;
    int** matrica;

public:
    Picture(int d) : dim(d) {
        matrica = new int*[dim];
        for (int i = 0; i < dim; ++i) {
            matrica[i] = new int[dim];
        }
    }

    ~Picture() {
        for (int i = 0; i < dim; ++i) {
            delete[] matrica[i];
        }
        delete[] matrica;
    }

    friend ostream& operator<<(ostream& os, const Picture& p) {
        for (int i = 0; i < p.dim; ++i) {
            for (int j = 0; j < p.dim; ++j) {
                os << p.matrica[i][j] << " ";
            }
            os << endl;
        }
        return os;
    }

    friend istream& operator>>(istream& is, Picture& p) {
        cout << "Unesite sadrzaj slike:\n";
        for (int i = 0; i < p.dim; ++i) {
            for (int j = 0; j < p.dim; ++j) {
                is >> p.matrica[i][j];
            }
        }
        return is;
    }
};

int main() {
    Picture p(3);
    cin >> p;
    cout << "Slika:\n" << p;
    return 0;
}
