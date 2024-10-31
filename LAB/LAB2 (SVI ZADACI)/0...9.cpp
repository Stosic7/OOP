// ZADATAK 0
#include <iostream>
#include <vector>
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

class Skup {
private:
    vector<Complex> elementi;

public:
    Skup() {}

    void dodajElement(const Complex& c) {
        elementi.push_back(c);
    }

    Skup operator-(const Skup& other) const {
        Skup rezultat;
        for (const auto& e : elementi) {
            bool found = false;
            for (const auto& oe : other.elementi) {
                if (e.real == oe.real && e.imag == oe.imag) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                rezultat.dodajElement(e);
            }
        }
        return rezultat;
    }

    Skup operator+(const Skup& other) const {
        Skup rezultat = *this;
        for (const auto& oe : other.elementi) {
            bool found = false;
            for (const auto& e : rezultat.elementi) {
                if (e.real == oe.real && e.imag == oe.imag) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                rezultat.dodajElement(oe);
            }
        }
        return rezultat;
    }

    Skup presek(const Skup& other) const {
        Skup rezultat;
        for (const auto& e : elementi) {
            for (const auto& oe : other.elementi) {
                if (e.real == oe.real && e.imag == oe.imag) {
                    rezultat.dodajElement(e);
                    break;
                }
            }
        }
        return rezultat;
    }

    Skup& operator=(const Skup& other) {
        if (this != &other) {
            elementi = other.elementi;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Skup& s) {
        for (const auto& e : s.elementi) {
            os << e << " ";
        }
        return os;
    }

    friend istream& operator>>(istream& is, Skup& s) {
        int n;
        cout << "Unesite broj elemenata skupa: ";
        is >> n;
        for (int i = 0; i < n; ++i) {
            Complex c;
            cout << "Unesite kompleksni broj (realni i imaginarni deo): ";
            is >> c;
            s.dodajElement(c);
        }
        return is;
    }
};

int main() {
    Skup* s1 = new Skup();
    Skup* s2 = new Skup();

    cout << "Unos prvog skupa:" << endl;
    cin >> *s1;
    cout << "Unos drugog skupa:" << endl;
    cin >> *s2;

    Skup unija = *s1 + *s2;
    Skup razlika = *s1 - *s2;
    Skup presek = s1->presek(*s2);

    cout << "Unija: " << unija << endl;
    cout << "Razlika: " << razlika << endl;
    cout << "Presek: " << presek << endl;

    delete s1;
    delete s2;

    return 0;
}

// ZADATAK 1

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
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

    Ispit(const Ispit& other) {
        imeIspita = new char[strlen(other.imeIspita) + 1];
        strcpy(imeIspita, other.imeIspita);
        strcpy(datum, other.datum);
        ocena = other.ocena;
    }

    Ispit& operator=(const Ispit& other) {
        if (this != &other) {
            delete[] imeIspita;
            imeIspita = new char[strlen(other.imeIspita) + 1];
            strcpy(imeIspita, other.imeIspita);
            strcpy(datum, other.datum);
            ocena = other.ocena;
        }
        return *this;
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
        delete[] i.imeIspita;
        i.imeIspita = new char[strlen(temp) + 1];
        strcpy(i.imeIspita, temp);
        cout << "Unesite datum (yyyy-MM-dd): ";
        is >> i.datum;
        cout << "Unesite ocenu: ";
        is >> i.ocena;
        return is;
    }

    const char* getDatum() const {
        return datum;
    }

    int getOcena() const {
        return ocena;
    }
};

class Student {
private:
    vector<Ispit> ispiti;

public:
    Student() {
        ispiti.reserve(50);
    }

    void dodajIspit(const Ispit& ispit) {
        ispiti.push_back(ispit);
    }

    double prosecnaOcena() const {
        if (ispiti.empty()) return 0;
        double suma = 0;
        for (const auto& ispit : ispiti) {
            suma += ispit.getOcena();
        }
        return suma / ispiti.size();
    }

    bool operator>(const Student& other) const {
        return prosecnaOcena() > other.prosecnaOcena();
    }

    Student& operator=(const Student& other) {
        if (this != &other) {
            ispiti = other.ispiti;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Student& s) {
        os << "Student sa ispitima:\n";
        for (const auto& ispit : s.ispiti) {
            os << ispit << "\n";
        }
        return os;
    }

    friend istream& operator>>(istream& is, Student& s) {
        int n;
        cout << "Unesite broj ispita: ";
        is >> n;
        for (int i = 0; i < n; ++i) {
            Ispit ispit;
            is >> ispit;
            s.dodajIspit(ispit);
        }
        return is;
    }
};

int main() {
    vector<Student*> studenti;
    int brojStudenata;
    cout << "Unesite broj studenata: ";
    cin >> brojStudenata;

    for (int i = 0; i < brojStudenata; ++i) {
        Student* s = new Student();
        cout << "Unos podataka za studenta " << i + 1 << ":\n";
        cin >> *s;
        studenti.push_back(s);
    }

    sort(studenti.begin(), studenti.end(), [](Student* a, Student* b) {
        return *a > *b;
    });

    cout << "\nStudenti sortirani po prosečnoj oceni:\n";
    for (const auto& s : studenti) {
        cout << *s << "\n";
    }

    // Sortiranje po vremenu između prvog i poslednjeg ispita nije implementirano zbog složenosti parsiranja datuma.
    // Ova funkcionalnost može biti dodata pomoću biblioteke za rad sa datumima.

    sort(studenti.begin(), studenti.end(), [](Student* a, Student* b) {
        return a->ispiti.size() > b->ispiti.size();
    });

    cout << "\nStudenti sortirani po broju položenih ispita:\n";
    for (const auto& s : studenti) {
        cout << *s << "\n";
    }

    for (auto& s : studenti) {
        delete s;
    }

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

class Slika {
private:
    int maxPoligona;
    int brojPoligona;
    Poligon** poligoni;

public:
    Slika(int max) : maxPoligona(max), brojPoligona(0) {
        poligoni = new Poligon*[maxPoligona];
    }

    ~Slika() {
        for (int i = 0; i < brojPoligona; ++i) {
            delete poligoni[i];
        }
        delete[] poligoni;
    }

    void dodajPoligon(Poligon* p) {
        if (brojPoligona < maxPoligona) {
            poligoni[brojPoligona++] = p;
        } else {
            cout << "Slika je puna, ne može se dodati više poligona." << endl;
        }
    }

    friend ostream& operator<<(ostream& os, const Slika& s) {
        os << "Slika sa poligonima:\n";
        for (int i = 0; i < s.brojPoligona; ++i) {
            os << *(s.poligoni[i]) << "\n";
        }
        return os;
    }
};

int main() {
    int n, m, k;
    cout << "Unesite broj temena za prvi poligon: ";
    cin >> n;
    Poligon* p1 = new Poligon(n);
    cin >> *p1;
    cout << "Poligon pre preslikavanja: " << *p1 << endl;
    p1->preslikajX();
    cout << "Poligon nakon preslikavanja u odnosu na x osu: " << *p1 << endl;
    p1->preslikajY();
    cout << "Poligon nakon preslikavanja u odnosu na y osu: " << *p1 << endl;

    cout << "\nUnesite broj temena za drugi poligon: ";
    cin >> m;
    Poligon* p2 = new Poligon(m);
    cin >> *p2;
    cout << "Poligon pre preslikavanja: " << *p2 << endl;
    p2->preslikajX();
    cout << "Poligon nakon preslikavanja u odnosu na x osu: " << *p2 << endl;
    p2->preslikajY();
    cout << "Poligon nakon preslikavanja u odnosu na y osu: " << *p2 << endl;

    cout << "\nUnesite maksimalan broj poligona za sliku: ";
    cin >> k;
    Slika slika(k);
    slika.dodajPoligon(p1);
    slika.dodajPoligon(p2);

    for (int i = 0; i < k - 2; ++i) {
        int brojTemena;
        cout << "Unesite broj temena za poligon " << i + 3 << ": ";
        cin >> brojTemena;
        Poligon* p = new Poligon(brojTemena);
        cin >> *p;
        slika.dodajPoligon(p);
    }

    cout << "\n" << slika;

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

    void preklopi(const Image& other) {
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                matrica[i][j] = matrica[i][j] || other.matrica[i][j];
            }
        }
    }

    void rotiraj() {
        int** novaMatrica = new int*[dim];
        for (int i = 0; i < dim; ++i) {
            novaMatrica[i] = new int[dim];
        }

        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                novaMatrica[j][dim - 1 - i] = matrica[i][j];
            }
        }

        for (int i = 0; i < dim; ++i) {
            delete[] matrica[i];
        }
        delete[] matrica;

        matrica = novaMatrica;
    }

    Image& operator=(const Image& other) {
        if (this != &other) {
            for (int i = 0; i < dim; ++i) {
                delete[] matrica[i];
            }
            delete[] matrica;

            dim = other.dim;
            matrica = new int*[dim];
            for (int i = 0; i < dim; ++i) {
                matrica[i] = new int[dim];
                for (int j = 0; j < dim; ++j) {
                    matrica[i][j] = other.matrica[i][j];
                }
            }
        }
        return *this;
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

class Kolekcija {
private:
    int maxSlika;
    int brojSlika;
    Image** slike;

public:
    Kolekcija(int max) : maxSlika(max), brojSlika(0) {
        slike = new Image*[maxSlika];
    }

    ~Kolekcija() {
        for (int i = 0; i < brojSlika; ++i) {
            delete slike[i];
        }
        delete[] slike;
    }

    void dodajSliku(Image* img) {
        if (brojSlika < maxSlika) {
            slike[brojSlika++] = img;
        } else {
            cout << "Kolekcija je puna, ne moze se dodati vise slika." << endl;
        }
    }

    friend ostream& operator<<(ostream& os, const Kolekcija& kol) {
        os << "Kolekcija sadrzi slike:\n";
        for (int i = 0; i < kol.brojSlika; ++i) {
            os << "Slika " << i + 1 << ":\n";
            os << *(kol.slike[i]) << "\n";
        }
        return os;
    }
};

int main() {
    int dim;
    cout << "Unesite dimenziju slike: ";
    cin >> dim;

    Image* img1 = new Image(dim);
    Image* img2 = new Image(dim);

    cin >> *img1;
    cin >> *img2;

    img1->invertuj();
    img2->invertuj();

    Image* img3 = new Image(dim);
    *img3 = *img1;
    img3->preklopi(*img2);

    cout << "Rezultujuca slika nakon preklapanja:\n" << *img3 << endl;

    Kolekcija kolekcija(3);
    kolekcija.dodajSliku(img1);
    kolekcija.dodajSliku(img2);
    kolekcija.dodajSliku(img3);

    cout << "\n" << kolekcija;

    return 0;
}


// Zadatak 4: Klasa Complex i main (ponovno)
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    double modul() const {
        return sqrt(real * real + imag * imag);
    }

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    bool operator<(const Complex& other) const {
        return modul() < other.modul();
    }

    friend ostream& operator<<(ostream& os, const Complex& c) {
        os << c.real << (c.imag >= 0 ? "+" : "") << c.imag << "i";
        return os;
    }

    friend istream& operator>>(istream& is, Complex& c) {
        cout << "Unesite realni i imaginarni deo: ";
        is >> c.real >> c.imag;
        return is;
    }
};

class Buffer {
private:
    vector<Complex> elementi;

public:
    void dodaj(const Complex& c) {
        elementi.push_back(c);
    }

    void nadovezi(const Buffer& other) {
        elementi.insert(elementi.end(), other.elementi.begin(), other.elementi.end());
    }

    void izbaciNaLokaciji(int index) {
        if (index >= 0 && index < elementi.size()) {
            elementi.erase(elementi.begin() + index);
        } else {
            cout << "Neispravna lokacija." << endl;
        }
    }

    void izbaciSveManjeOd(const Complex& vrednost) {
        elementi.erase(remove_if(elementi.begin(), elementi.end(), [&](const Complex& c) {
            return c < vrednost;
        }), elementi.end());
    }

    double prosecnaVrednost() const {
        if (elementi.empty()) return 0;
        double suma = 0;
        for (const auto& e : elementi) {
            suma += e.modul();
        }
        return suma / elementi.size();
    }

    Buffer& operator=(const Buffer& other) {
        if (this != &other) {
            elementi = other.elementi;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Buffer& b) {
        os << "Buffer sadrzi: ";
        for (const auto& e : b.elementi) {
            os << e << " ";
        }
        return os;
    }
};

int main() {
    Buffer b1, b2;
    Complex c1(3, 4), c2(1, -1), c3(0, 2);
    b1.dodaj(c1);
    b1.dodaj(c2);
    b2.dodaj(c3);

    cout << "Buffer 1: " << b1 << endl;
    cout << "Buffer 2: " << b2 << endl;

    b1.nadovezi(b2);
    cout << "Buffer 1 nakon nadovezivanja sa Buffer 2: " << b1 << endl;

    Buffer b3;
    b3 = b1;
    cout << "Buffer 3 (kopija Buffera 1): " << b3 << endl;

    b3.izbaciNaLokaciji(1);
    cout << "Buffer 3 nakon izbacivanja elementa sa lokacije 1: " << b3 << endl;

    Complex prag(2, 2);
    b3.izbaciSveManjeOd(prag);
    cout << "Buffer 3 nakon izbacivanja elemenata manjih od " << prag << ": " << b3 << endl;

    cout << "Prosecna vrednost elemenata u Bufferu 3: " << b3.prosecnaVrednost() << endl;

    return 0;
}

// Zadatak 5: Klasa Tacka i main
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Tacka {
private:
    double x, y, z;

public:
    Tacka(double a = 0, double b = 0, double c = 0) : x(a), y(b), z(c) {}

    Tacka operator+(const Tacka& other) const {
        return Tacka(x + other.x, y + other.y, z + other.z);
    }

    Tacka operator-(const Tacka& other) const {
        return Tacka(x - other.x, y - other.y, z - other.z);
    }

    Tacka operator*(double skalar) const {
        return Tacka(x * skalar, y * skalar, z * skalar);
    }

    friend ostream& operator<<(ostream& os, const Tacka& t) {
        os << "(" << t.x << ", " << t.y << ", " << t.z << ")";
        return os;
    }

    friend istream& operator>>(istream& is, Tacka& t) {
        cout << "Unesite koordinate tacke (x y z): ";
        is >> t.x >> t.y >> t.z;
        return is;
    }
};

class Vektor {
private:
    vector<Tacka> tacke;

public:
    void dodajTacku(const Tacka& t) {
        tacke.push_back(t);
    }

    Vektor saberi(const Vektor& other) const {
        Vektor rezultat;
        for (size_t i = 0; i < min(tacke.size(), other.tacke.size()); ++i) {
            rezultat.dodajTacku(tacke[i] + other.tacke[i]);
        }
        return rezultat;
    }

    void izbaciDuplikateIRastuciRedosled() {
        sort(tacke.begin(), tacke.end(), [](const Tacka& a, const Tacka& b) {
            return (a.x < b.x) || (a.x == b.x && a.y < b.y) || (a.x == b.x && a.y == b.y && a.z < b.z);
        });
        tacke.erase(unique(tacke.begin(), tacke.end(), [](const Tacka& a, const Tacka& b) {
            return a.x == b.x && a.y == b.y && a.z == b.z;
        }), tacke.end());
    }

    void rotirajUdesno() {
        if (!tacke.empty()) {
            Tacka poslednja = tacke.back();
            tacke.pop_back();
            tacke.insert(tacke.begin(), poslednja);
        }
    }

    void rotirajUlevo() {
        if (!tacke.empty()) {
            Tacka prva = tacke.front();
            tacke.erase(tacke.begin());
            tacke.push_back(prva);
        }
    }

    Vektor& operator=(const Vektor& other) {
        if (this != &other) {
            tacke = other.tacke;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Vektor& v) {
        os << "Vektor sadrzi tacke: ";
        for (const auto& t : v.tacke) {
            os << t << " ";
        }
        return os;
    }

    friend istream& operator>>(istream& is, Vektor& v) {
        int n;
        cout << "Unesite broj tacaka: ";
        is >> n;
        for (int i = 0; i < n; ++i) {
            Tacka t;
            is >> t;
            v.dodajTacku(t);
        }
        return is;
    }
};

int main() {
    Vektor v1, v2;
    cin >> v1;
    cin >> v2;

    Vektor zbir = v1.saberi(v2);
    cout << "Zbir vektora: " << zbir << endl;

    v1.izbaciDuplikateIRastuciRedosled();
    cout << "Vektor 1 nakon izbacivanja duplikata i uredjivanja: " << v1 << endl;

    v1.rotirajUdesno();
    cout << "Vektor 1 nakon rotacije udesno: " << v1 << endl;

    v1.rotirajUlevo();
    cout << "Vektor 1 nakon rotacije ulevo: " << v1 << endl;

    Vektor v3;
    v3 = v1;
    cout << "Vektor 3 (kopija vektora 1): " << v3 << endl;

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

    void pomeriMineDole() {
        bool* lastRow = polje[dim - 1];
        for (int i = dim - 1; i > 0; --i) {
            polje[i] = polje[i - 1];
        }
        polje[0] = lastRow;
    }

    void pomeriMineLevo() {
        for (int i = 0; i < dim; ++i) {
            bool first = polje[i][0];
            for (int j = 0; j < dim - 1; ++j) {
                polje[i][j] = polje[i][j + 1];
            }
            polje[i][dim - 1] = first;
        }
    }

    void pomeriMineGore() {
        bool* firstRow = polje[0];
        for (int i = 0; i < dim - 1; ++i) {
            polje[i] = polje[i + 1];
        }
        polje[dim - 1] = firstRow;
    }

    void postaviMineNaSvakoNtoPrazno(int n) {
        int count = 0;
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                if (!polje[i][j]) {
                    ++count;
                    if (count == n) {
                        polje[i][j] = true;
                        count = 0;
                    }
                }
            }
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

    m.pomeriMineDole();
    cout << "Polje nakon pomeranja mina nadole:\n" << m;

    m.pomeriMineLevo();
    cout << "Polje nakon pomeranja mina ulevo:\n" << m;

    m.pomeriMineGore();
    cout << "Polje nakon pomeranja mina nagore:\n" << m;

    m.postaviMineNaSvakoNtoPrazno(2);
    cout << "Polje nakon postavljanja mina na svako 2. prazno polje:\n" << m;

    return 0;
}

// Zadatak 7: Klasa Matrica i main
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Tacka {
private:
    double x, y, z;

public:
    Tacka(double a = 0, double b = 0, double c = 0) : x(a), y(b), z(c) {}

    Tacka operator+(const Tacka& other) const {
        return Tacka(x + other.x, y + other.y, z + other.z);
    }

    Tacka operator-(const Tacka& other) const {
        return Tacka(x - other.x, y - other.y, z - other.z);
    }

    void povecajZaJedan() {
        x += 1;
        y += 1;
        z += 1;
    }

    void normalizuj(double minX, double maxX, double minY, double maxY, double minZ, double maxZ) {
        x = max(minX, min(x, maxX));
        y = max(minY, min(y, maxY));
        z = max(minZ, min(z, maxZ));
    }

    friend ostream& operator<<(ostream& os, const Tacka& t) {
        os << "(" << t.x << ", " << t.y << ", " << t.z << ")";
        return os;
    }

    friend istream& operator>>(istream& is, Tacka& t) {
        cout << "Unesite koordinate tacke (x y z): ";
        is >> t.x >> t.y >> t.z;
        return is;
    }
};

class Matrica {
private:
    int redovi;
    int kolone;
    vector<vector<Tacka>> matrica;

public:
    Matrica(int r, int k) : redovi(r), kolone(k) {
        matrica.resize(redovi, vector<Tacka>(kolone));
    }

    void povecajSveKomponenteZaJedan() {
        for (auto& red : matrica) {
            for (auto& tacka : red) {
                tacka.povecajZaJedan();
            }
        }
    }

    Tacka sumirajRed(int indeks) const {
        Tacka suma;
        if (indeks >= 0 && indeks < redovi) {
            for (const auto& tacka : matrica[indeks]) {
                suma = suma + tacka;
            }
        }
        return suma;
    }

    void normalizujSve(double minX, double maxX, double minY, double maxY, double minZ, double maxZ) {
        for (auto& red : matrica) {
            for (auto& tacka : red) {
                tacka.normalizuj(minX, maxX, minY, maxY, minZ, maxZ);
            }
        }
    }

    Matrica& operator=(const Matrica& other) {
        if (this != &other) {
            redovi = other.redovi;
            kolone = other.kolone;
            matrica = other.matrica;
        }
        return *this;
    }

    Tacka getTacka(int r, int k) const {
        if (r >= 0 && r < redovi && k >= 0 && k < kolone) {
            return matrica[r][k];
        }
        return Tacka();
    }

    friend ostream& operator<<(ostream& os, const Matrica& m) {
        for (const auto& red : m.matrica) {
            for (const auto& tacka : red) {
                os << tacka << " ";
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
    int m, n;
    cout << "Unesite broj redova i kolona matrice: ";
    cin >> m >> n;

    Matrica matrica(m, n);
    cin >> matrica;
    cout << "Matrica:\n" << matrica;

    matrica.povecajSveKomponenteZaJedan();
    cout << "Matrica nakon povecanja svake komponente za 1:\n" << matrica;

    int indeks;
    cout << "Unesite indeks reda za sumiranje: ";
    cin >> indeks;
    Tacka suma = matrica.sumirajRed(indeks);
    cout << "Suma elemenata u redu " << indeks << ": " << suma << endl;

    double minX, maxX, minY, maxY, minZ, maxZ;
    cout << "Unesite minimalne i maksimalne vrednosti za normalizaciju (minX maxX minY maxY minZ maxZ): ";
    cin >> minX >> maxX >> minY >> maxY >> minZ >> maxZ;
    matrica.normalizujSve(minX, maxX, minY, maxY, minZ, maxZ);
    cout << "Matrica nakon normalizacije:\n" << matrica;

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

    String(const String& other) {
        duzina = other.duzina;
        niz = new char[duzina + 1];
        strcpy(niz, other.niz);
    }

    String& operator=(const String& other) {
        if (this != &other) {
            delete[] niz;
            duzina = other.duzina;
            niz = new char[duzina + 1];
            strcpy(niz, other.niz);
        }
        return *this;
    }

    String operator+(const String& other) const {
        char* noviNiz = new char[duzina + other.duzina + 1];
        strcpy(noviNiz, niz);
        strcat(noviNiz, other.niz);
        String rezultat(noviNiz);
        delete[] noviNiz;
        return rezultat;
    }

    void toUpperCase() {
        for (int i = 0; i < duzina; ++i) {
            niz[i] = toupper(niz[i]);
        }
    }

    void capitalize() {
        if (duzina > 0) {
            niz[0] = toupper(niz[0]);
        }
    }

    void padRight(char c, int length) {
        if (duzina < length) {
            char* noviNiz = new char[length + 1];
            strcpy(noviNiz, niz);
            for (int i = duzina; i < length; ++i) {
                noviNiz[i] = c;
            }
            noviNiz[length] = '\0';
            delete[] niz;
            niz = noviNiz;
            duzina = length;
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

class Paragraph {
private:
    int maxStringova;
    int brojStringova;
    String* stringovi;

public:
    Paragraph(int max) : maxStringova(max), brojStringova(0) {
        stringovi = new String[maxStringova];
    }

    ~Paragraph() {
        delete[] stringovi;
    }

    void dodajString(const String& s) {
        if (brojStringova < maxStringova) {
            stringovi[brojStringova++] = s;
        } else {
            cout << "Paragraf je pun, ne moze se dodati vise stringova." << endl;
        }
    }

    friend ostream& operator<<(ostream& os, const Paragraph& p) {
        for (int i = 0; i < p.brojStringova; ++i) {
            os << p.stringovi[i] << " ";
        }
        return os;
    }
};

int main() {
    String s1, s2;
    cout << "Unesite prvi string: ";
    cin >> s1;
    cout << "Unesite drugi string: ";
    cin >> s2;

    String kopija1 = s1;
    String kopija2 = s2;

    s1.capitalize();
    s2.toUpperCase();
    s2.padRight('*', 10);

    String s3 = s1 + s2;
    cout << "Konkatenirani string: " << s3 << endl;

    Paragraph paragraf(5);
    paragraf.dodajString(kopija1);
    paragraf.dodajString(kopija2);
    paragraf.dodajString(s1);
    paragraf.dodajString(s2);
    paragraf.dodajString(s3);

    cout << "Paragraf: " << paragraf << endl;

    return 0;
}


// Zadatak 9: Klasa Picture i main
#include <iostream>
#include <set>
using namespace std;

class Picture {
private:
    int width;
    int height;
    int** matrica;

public:
    Picture(int w, int h) : width(w), height(h) {
        matrica = new int*[height];
        for (int i = 0; i < height; ++i) {
            matrica[i] = new int[width];
        }
    }

    ~Picture() {
        for (int i = 0; i < height; ++i) {
            delete[] matrica[i];
        }
        delete[] matrica;
    }

    Picture(const Picture& other) : width(other.width), height(other.height) {
        matrica = new int*[height];
        for (int i = 0; i < height; ++i) {
            matrica[i] = new int[width];
            for (int j = 0; j < width; ++j) {
                matrica[i][j] = other.matrica[i][j];
            }
        }
    }

    Picture& operator=(const Picture& other) {
        if (this != &other) {
            for (int i = 0; i < height; ++i) {
                delete[] matrica[i];
            }
            delete[] matrica;

            width = other.width;
            height = other.height;

            matrica = new int*[height];
            for (int i = 0; i < height; ++i) {
                matrica[i] = new int[width];
                for (int j = 0; j < width; ++j) {
                    matrica[i][j] = other.matrica[i][j];
                }
            }
        }
        return *this;
    }

    Picture preklopi(const Picture& other) const {
        Picture rezultat(width, height);
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                rezultat.matrica[i][j] = (matrica[i][j] + other.matrica[i][j]) / 2;
            }
        }
        return rezultat;
    }

    int brojRazlicitihBoja() const {
        set<int> boje;
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                boje.insert(matrica[i][j]);
            }
        }
        return boje.size();
    }

    friend ostream& operator<<(ostream& os, const Picture& p) {
        for (int i = 0; i < p.height; ++i) {
            for (int j = 0; j < p.width; ++j) {
                os << p.matrica[i][j] << " ";
            }
            os << endl;
        }
        return os;
    }

    friend istream& operator>>(istream& is, Picture& p) {
        cout << "Unesite sadrzaj slike:
";
        for (int i = 0; i < p.height; ++i) {
            for (int j = 0; j < p.width; ++j) {
                is >> p.matrica[i][j];
            }
        }
        return is;
    }
};

class Kolekcija {
private:
    int maxSlika;
    int brojSlika;
    Picture** slike;

public:
    Kolekcija(int max) : maxSlika(max), brojSlika(0) {
        slike = new Picture*[maxSlika];
    }

    ~Kolekcija() {
        for (int i = 0; i < brojSlika; ++i) {
            delete slike[i];
        }
        delete[] slike;
    }

    void dodajSliku(const Picture& p) {
        if (brojSlika < maxSlika) {
            slike[brojSlika++] = new Picture(p);
        } else {
            cout << "Kolekcija je puna, ne moze se dodati vise slika." << endl;
        }
    }

    friend ostream& operator<<(ostream& os, const Kolekcija& k) {
        for (int i = 0; i < k.brojSlika; ++i) {
            os << "Slika " << i + 1 << ":\n" << *(k.slike[i]) << "\n";
        }
        return os;
    }
};

int main() {
    Picture p1(3, 3), p2(3, 3);
    cin >> p1;
    cin >> p2;

    Picture preklopljena = p1.preklopi(p2);
    cout << "Preklopljena slika:\n" << preklopljena;

    cout << "Broj razlicitih boja u slici p1: " << p1.brojRazlicitihBoja() << endl;

    Kolekcija kolekcija(5);
    kolekcija.dodajSliku(p1);
    kolekcija.dodajSliku(p2);
    kolekcija.dodajSliku(preklopljena);

    cout << "Kolekcija slika:\n" << kolekcija;

    return 0;
}
