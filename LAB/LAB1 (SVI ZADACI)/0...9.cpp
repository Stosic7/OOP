// ZADATAK 0, Skup
#include <iostream>
#include <cstring>
#include <cmath>

class Skup {
private:
    int brojElemenata;
    int* elementi;

public:
    // Default konstruktor koji postavlja broj elemenata skupa na 0
    Skup() : brojElemenata(0), elementi(nullptr) {}

    // Konstruktor za postavljanje broja elemenata skupa i zauzimanje neophodnog prostora u memoriji
    Skup(int broj) : brojElemenata(broj) {
        elementi = new int[broj];
    }

    // Destruktor
    ~Skup() {
        delete[] elementi;
    }

    // Inline funkcija koja vraća broj elemenata skupa
    inline int getBrojElemenata() const {
        return brojElemenata;
    }

    // Funkcija koja izbacuje duplikate iz skupa
    void izbaciDuplikate() {
        for (int i = 0; i < brojElemenata; ++i) {
            for (int j = i + 1; j < brojElemenata;) {
                if (elementi[i] == elementi[j]) {
                    for (int k = j; k < brojElemenata - 1; ++k) {
                        elementi[k] = elementi[k + 1];
                    }
                    --brojElemenata;
                } else {
                    ++j;
                }
            }
        }
    }

    // Funkcija koja ispituje da li zadati element pripada skupu
    bool pripadaSkupu(int element) const {
        for (int i = 0; i < brojElemenata; ++i) {
            if (elementi[i] == element) {
                return true;
            }
        }
        return false;
    }

    // Funkcija za učitavanje elemenata skupa sa standardnog ulaza
    void ucitajElemente() {
        std::cout << "Unesite " << brojElemenata << " elemenata: ";
        for (int i = 0; i < brojElemenata; ++i) {
            std::cin >> elementi[i];
        }
    }

    // Funkcija za uređivanje elemenata skupa u nerastuci redosled
    void sortirajNerastuci() {
        for (int i = 0; i < brojElemenata - 1; ++i) {
            for (int j = i + 1; j < brojElemenata; ++j) {
                if (elementi[i] < elementi[j]) {
                    int temp = elementi[i];
                    elementi[i] = elementi[j];
                    elementi[j] = temp;
                }
            }
        }
    }

    // Funkcija za prikaz elemenata skupa na standardni izlaz
    void prikaziElemente() const {
        std::cout << "Elementi skupa: ";
        for (int i = 0; i < brojElemenata; ++i) {
            std::cout << elementi[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    // Kreiranje objekta klase Skup u dinamičkoj zoni memorije koji sadrži 10 elemenata
    Skup* skup1 = new Skup(10);
    skup1->ucitajElemente();
    skup1->izbaciDuplikate();
    skup1->sortirajNerastuci();
    skup1->prikaziElemente();

    // Ispitivanje da li nekoliko brojeva pripada skupu
    int brojeviZaProveru[] = {5, 10, 15};
    for (int broj : brojeviZaProveru) {
        if (skup1->pripadaSkupu(broj)) {
            std::cout << "Element " << broj << " pripada skupu." << std::endl;
        } else {
            std::cout << "Element " << broj << " ne pripada skupu." << std::endl;
        }
    }

    // Kreiranje drugog objekta klase Skup u dinamičkoj zoni memorije i testiranje svih funkcija
    Skup* skup2 = new Skup(5);
    skup2->ucitajElemente();
    skup2->izbaciDuplikate();
    skup2->sortirajNerastuci();
    skup2->prikaziElemente();

    delete skup1;
    delete skup2;

    return 0;
}


// Zadatak 1: Klasa Student i main
#include <iostream>
#include <algorithm>
#include <cstring>

class Student {
private:
    char* imePrezime;
    int brojIndeksa;
    int maxBrojIspita;
    int brojPolozenih;
    int* ocene;

public:
    // Konstruktor koji inicijalizuje maksimalni broj ispita na fakultetu
    Student(int maxIspita) : maxBrojIspita(maxIspita), brojPolozenih(0) {
        imePrezime = new char[100];
        ocene = new int[maxBrojIspita];
    }

    // Destruktor
    ~Student() {
        delete[] imePrezime;
        delete[] ocene;
    }

    // Inline funkcije koje vraćaju broj indeksa i broj položenih ispita
    inline int getBrojIndeksa() const {
        return brojIndeksa;
    }

    inline int getBrojPolozenih() const {
        return brojPolozenih;
    }

    // Funkcija koja u niz ocena dodaje ocenu sa poslednjeg položenog ispita
    void dodajOcenu(int ocena) {
        if (ocena < 5 || ocena > 10) {
            std::cout << "Ocena mora biti u opsegu od 5 do 10!" << std::endl;
            return;
        }

        if (brojPolozenih < maxBrojIspita) {
            ocene[brojPolozenih++] = ocena;
        } else {
            std::cout << "Nema više mesta za dodavanje ocena!" << std::endl;
        }
    }

    // Funkcija za učitavanje podataka o studentu sa standardnog ulaza
    void ucitajPodatke() {
        std::cout << "Unesite ime i prezime studenta: ";
        std::cin.ignore();
        std::cin.getline(imePrezime, 100);
        std::cout << "Unesite broj indeksa: ";
        std::cin >> brojIndeksa;
    }

    // Funkcija koja na standardnom izlazu prikazuje sve ocene od najveće do najmanje
    void prikaziOcene() const {
        if (brojPolozenih == 0) {
            std::cout << "Student nema položenih ispita." << std::endl;
            return;
        }

        int* sortiraneOcene = new int[brojPolozenih];
        std::copy(ocene, ocene + brojPolozenih, sortiraneOcene);
        std::sort(sortiraneOcene, sortiraneOcene + brojPolozenih, std::greater<int>());

        std::cout << "Ocene (od najveće do najmanje): ";
        for (int i = 0; i < brojPolozenih; ++i) {
            std::cout << sortiraneOcene[i] << " ";
        }
        std::cout << std::endl;

        delete[] sortiraneOcene;
    }

    // Funkcija za prikaz podataka o studentu na standardni izlaz
    void prikaziPodatke() const {
        std::cout << "Ime i prezime: " << imePrezime << ", Broj indeksa: " << brojIndeksa << std::endl;
    }

    // Funkcija koja ažurira ime i prezime studenta
    void azurirajImePrezime(const char* novoImePrezime) {
        strcpy(imePrezime, novoImePrezime);
    }
};

int main() {
    // Kreiranje objekta klase Student sa proizvoljnim brojem ispita
    Student student(5);
    student.ucitajPodatke();
    student.dodajOcenu(10);
    student.dodajOcenu(9);
    student.dodajOcenu(7);
    student.prikaziOcene();
    student.prikaziPodatke();

    // Kreiranje drugog objekta klase Student u dinamičkoj zoni memorije
    Student* student2 = new Student(3);
    student2->ucitajPodatke();
    student2->dodajOcenu(6);
    student2->dodajOcenu(8);
    student2->prikaziOcene();
    student2->prikaziPodatke();
    student2->azurirajImePrezime("Novo Ime Prezime");
    std::cout << "Podaci nakon ažuriranja imena: " << std::endl;
    student2->prikaziPodatke();

    delete student2;

    return 0;
}


// Zadatak 2: Klasa Poligon i main
#include <iostream>
#include <cmath>
#include <limits>

class Poligon {
private:
    int brojTemena;
    int* xKoordinate;
    int* yKoordinate;

public:
    // Default konstruktor koji postavlja broj temena na 0
    Poligon() : brojTemena(0), xKoordinate(nullptr), yKoordinate(nullptr) {}

    // Konstruktor sa parametrima za inicijalizaciju broja temena
    Poligon(int broj) : brojTemena(broj) {
        xKoordinate = new int[broj];
        yKoordinate = new int[broj];
    }

    // Destruktor
    ~Poligon() {
        delete[] xKoordinate;
        delete[] yKoordinate;
    }

    // Inline funkcija koja vraća broj temena poligona
    inline int getBrojTemena() const {
        return brojTemena;
    }

    // Funkcija za unos koordinata temena
    void ucitajKoordinate() {
        std::cout << "Unesite koordinate temena: ";
        for (int i = 0; i < brojTemena; ++i) {
            std::cin >> xKoordinate[i] >> yKoordinate[i];
        }
    }

    // Funkcija za izračunavanje obima poligona
    double izracunajObim() const {
        double obim = 0;
        for (int i = 0; i < brojTemena; ++i) {
            int next = (i + 1) % brojTemena;
            obim += sqrt(pow(xKoordinate[next] - xKoordinate[i], 2) + pow(yKoordinate[next] - yKoordinate[i], 2));
        }
        return obim;
    }

    // Funkcija koja vraća dve međusobno najudaljenije tačke
    void najudaljenijeTacke() const {
        if (brojTemena < 2) {
            std::cout << "Nema dovoljno temena za izračunavanje najudaljenijih tačaka." << std::endl;
            return;
        }

        double maxUdaljenost = std::numeric_limits<double>::min();
        int t1 = 0, t2 = 1;

        for (int i = 0; i < brojTemena; ++i) {
            for (int j = i + 1; j < brojTemena; ++j) {
                double udaljenost = sqrt(pow(xKoordinate[j] - xKoordinate[i], 2) + pow(yKoordinate[j] - yKoordinate[i], 2));
                if (udaljenost > maxUdaljenost) {
                    maxUdaljenost = udaljenost;
                    t1 = i;
                    t2 = j;
                }
            }
        }

        std::cout << "Najudaljenije tacke su: (" << xKoordinate[t1] << ", " << yKoordinate[t1] << ") i ("
                  << xKoordinate[t2] << ", " << yKoordinate[t2] << ") sa udaljenoscu: " << maxUdaljenost << std::endl;
    }

    // Funkcija za prikaz koordinata temena
    void prikaziKoordinate() const {
        std::cout << "Koordinate temena: ";
        for (int i = 0; i < brojTemena; ++i) {
            std::cout << "(" << xKoordinate[i] << ", " << yKoordinate[i] << ") ";
        }
        std::cout << std::endl;
    }

    // Funkcija za izbacivanje jednog temena iz poligona
    void izbaciTeme(int indeks) {
        if (indeks < 0 || indeks >= brojTemena) {
            std::cout << "Neispravan indeks!" << std::endl;
            return;
        }

        int* noviX = new int[brojTemena - 1];
        int* noviY = new int[brojTemena - 1];

        for (int i = 0, j = 0; i < brojTemena; ++i) {
            if (i == indeks) continue;
            noviX[j] = xKoordinate[i];
            noviY[j] = yKoordinate[i];
            ++j;
        }

        delete[] xKoordinate;
        delete[] yKoordinate;

        xKoordinate = noviX;
        yKoordinate = noviY;
        --brojTemena;
    }
};

int main() {
    // Kreiranje objekta klase Poligon sa proizvoljnim brojem temena
    Poligon poligon(4);
    poligon.ucitajKoordinate();
    std::cout << "Obim poligona: " << poligon.izracunajObim() << std::endl;
    poligon.prikaziKoordinate();

    // Kreiranje drugog poligona u dinamičkoj zoni memorije
    Poligon* poligon2 = new Poligon(5);
    poligon2->ucitajKoordinate();
    poligon2->prikaziKoordinate();
    poligon2->najudaljenijeTacke();
    poligon2->izbaciTeme(2);
    std::cout << "Poligon nakon izbacivanja temena: " << std::endl;
    poligon2->prikaziKoordinate();

    delete poligon2;

    return 0;
}


// Zadatak 3: Klasa Image i main
#include <iostream>
#include <cstring>

class Image {
private:
    int dimenzija;
    int** matrica;
    char* nazivLokacije;

public:
    // Default konstruktor koji postavlja dimenziju matrice na 0
    Image() : dimenzija(0), matrica(nullptr) {
        nazivLokacije = new char[1];
        strcpy(nazivLokacije, "");
    }

    // Konstruktor za postavljanje veličine matrice
    Image(int dim) : dimenzija(dim) {
        matrica = new int*[dimenzija];
        for (int i = 0; i < dimenzija; ++i) {
            matrica[i] = new int[dimenzija]();
        }
        nazivLokacije = new char[100];
        strcpy(nazivLokacije, "Nema naziva");
    }

    // Destruktor
    ~Image() {
        for (int i = 0; i < dimenzija; ++i) {
            delete[] matrica[i];
        }
        delete[] matrica;
        delete[] nazivLokacije;
    }

    // Inline funkcija koja vraća dimenziju matrice
    inline int getDimenzija() const {
        return dimenzija;
    }

    // Funkcija koja invertuje sliku
    void invertujSliku() {
        for (int i = 0; i < dimenzija; ++i) {
            for (int j = 0; j < dimenzija; ++j) {
                matrica[i][j] = 1 - matrica[i][j];
            }
        }
    }

    // Funkcija za učitavanje sadržaja slike sa standardnog ulaza
    void ucitajSadrzaj() {
        std::cout << "Unesite sadrzaj slike (0 ili 1 za svaki element): ";
        for (int i = 0; i < dimenzija; ++i) {
            for (int j = 0; j < dimenzija; ++j) {
                std::cin >> matrica[i][j];
            }
        }
    }

    // Funkcija za prikazivanje sadržaja slike na standardni izlaz
    void prikaziSadrzaj() const {
        std::cout << "Sadrzaj slike: \n";
        for (int i = 0; i < dimenzija; ++i) {
            for (int j = 0; j < dimenzija; ++j) {
                std::cout << matrica[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Funkcija koja redukuje dimenzije slike prostim odsecanjem (crop)
    void crop(int novaDimenzija) {
        if (novaDimenzija >= dimenzija) return;

        // Oslobađanje viška redova
        for (int i = novaDimenzija; i < dimenzija; ++i) {
            delete[] matrica[i];
        }

        // Stvaranje nove matrice manje dimenzije
        int** novaMatrica = new int*[novaDimenzija];
        for (int i = 0; i < novaDimenzija; ++i) {
            novaMatrica[i] = new int[novaDimenzija];
            for (int j = 0; j < novaDimenzija; ++j) {
                novaMatrica[i][j] = matrica[i][j];
            }
        }

        // Oslobađanje stare matrice
        delete[] matrica;

        // Ažuriranje matrice i dimenzije
        matrica = novaMatrica;
        dimenzija = novaDimenzija;
    }
};

int main() {
    // Kreiranje objekta klase Image sa proizvoljnom veličinom
    Image image(5);
    image.ucitajSadrzaj();
    image.invertujSliku();
    std::cout << "Invertovana slika: \n";
    image.prikaziSadrzaj();

    // Kreiranje drugog objekta klase Image u dinamičkoj zoni memorije
    Image* image2 = new Image(3);
    image2->ucitajSadrzaj();
    std::cout << "Originalna slika 2: \n";
    image2->prikaziSadrzaj();
    image2->crop(2);
    std::cout << "Slika 2 nakon crop-a na dimenziju 2x2: \n";
    image2->prikaziSadrzaj();

    delete image2;

    return 0;
}


// Zadatak 4: Klasa Buffer i main
#include <iostream>
#include <algorithm>

class Buffer {
private:
    int* niz;
    int velicina;
    int brojElemenata;

public:
    // Default konstruktor koji postavlja veličinu bafera na 0
    Buffer() : niz(nullptr), velicina(0), brojElemenata(0) {}

    // Konstruktor sa parametrima za postavljanje veličine bafera
    Buffer(int vel) : velicina(vel), brojElemenata(0) {
        niz = new int[velicina];
    }

    // Destruktor
    ~Buffer() {
        delete[] niz;
    }

    // Inline funkcija koja vraća trenutni broj elemenata u baferu
    inline int getBrojElemenata() const {
        return brojElemenata;
    }

    // Funkcija koja dodaje element na kraj bafera
    void push(int element) {
        if (brojElemenata >= velicina) {
            duplirajVelicinu();
        }
        niz[brojElemenata++] = element;
    }

    // Funkcija koja uklanja poslednji element iz bafera i vraća ga
    int pop() {
        if (brojElemenata > 0) {
            return niz[--brojElemenata];
        }
        return -1; // Error value
    }

    // Funkcija koja prikazuje sadržaj bafera na standardni izlaz
    void prikazi() const {
        std::cout << "Sadržaj bafera: ";
        for (int i = 0; i < brojElemenata; ++i) {
            std::cout << niz[i] << " ";
        }
        std::cout << std::endl;
    }

    // Funkcija koja duplira veličinu bafera
    void duplirajVelicinu() {
        int novaVelicina = velicina * 2;
        int* noviNiz = new int[novaVelicina];
        std::copy(niz, niz + brojElemenata, noviNiz);
        delete[] niz;
        niz = noviNiz;
        velicina = novaVelicina;
    }

    // Funkcija koja izbacuje nezauzeta mesta iz bafera
    void izbaciNezauzetaMesta() {
        int* noviNiz = new int[brojElemenata];
        std::copy(niz, niz + brojElemenata, noviNiz);
        delete[] niz;
        niz = noviNiz;
        velicina = brojElemenata;
    }
};

int main() {
    // Kreiranje objekta klase Buffer i upisivanje prvih n prirodnih brojeva
    int n = 5;
    Buffer buffer1(n);
    for (int i = 1; i <= n; ++i) {
        buffer1.push(i);
    }
    buffer1.prikazi();

    // Kreiranje drugog bafera u dinamičkoj zoni memorije i kopiranje sadržaja iz prvog
    Buffer* buffer2 = new Buffer(buffer1.getBrojElemenata());
    for (int i = 0; i < buffer1.getBrojElemenata(); ++i) {
        buffer2->push(buffer1.pop());
    }
    buffer2->prikazi();

    // Vraćanje elemenata u prvi bafer za dalju manipulaciju
    for (int i = n; i > 0; --i) {
        buffer1.push(i);
    }

    // Izbacivanje m elemenata iz prvog bafera
    int m = 2;
    for (int i = 0; i < m; ++i) {
        buffer1.pop();
    }

    // Prikaz trenutnog broja elemenata u oba bafera i njihovih sadržaja
    std::cout << "Broj elemenata u buffer1: " << buffer1.getBrojElemenata() << std::endl;
    buffer1.prikazi();

    std::cout << "Broj elemenata u buffer2: " << buffer2->getBrojElemenata() << std::endl;
    buffer2->prikazi();

    delete buffer2;

    return 0;
}


// Zadatak 5: Klasa Vektor i main
#include <iostream>
#include <cmath>

class Vektor {
private:
    int* niz;
    int dimenzija;

public:
    // Default konstruktor koji postavlja dimenziju vektora na 0
    Vektor() : niz(nullptr), dimenzija(0) {}

    // Konstruktor sa parametrima
    Vektor(int dim) : dimenzija(dim) {
        niz = new int[dimenzija];
    }

    // Destruktor
    ~Vektor() {
        delete[] niz;
    }

    // Inline funkcija za postavljanje k-tog elementa
    void setElement(int index, int value) {
        if (index >= 0 && index < dimenzija) {
            niz[index] = value;
        }
    }

    // Konstantna inline funkcija za vraćanje k-tog elementa
    int getElement(int index) const {
        if (index >= 0 && index < dimenzija) {
            return niz[index];
        }
        return -1; // Greška
    }

    // Funkcija za uređivanje elemenata u neopadajući redosled
    void sortiraj() {
        for (int i = 0; i < dimenzija - 1; ++i) {
            for (int j = i + 1; j < dimenzija; ++j) {
                if (niz[i] > niz[j]) {
                    int temp = niz[i];
                    niz[i] = niz[j];
                    niz[j] = temp;
                }
            }
        }
    }

    // Funkcija za računanje skalarnog proizvoda dva vektora
    int skalarniProizvod(const Vektor& v) const {
        if (dimenzija != v.dimenzija) {
            std::cerr << "Vektori moraju imati istu dimenziju za skalarni proizvod!" << std::endl;
            return 0;
        }
        int proizvod = 0;
        for (int i = 0; i < dimenzija; ++i) {
            proizvod += niz[i] * v.getElement(i);
        }
        return proizvod;
    }

    // Funkcija koja vraća indeks elementa koji je najbliži srednjoj vrednosti
    int indeksNajbliziSrednjoj() const {
        if (dimenzija == 0) return -1;

        double suma = 0;
        for (int i = 0; i < dimenzija; ++i) {
            suma += niz[i];
        }
        double srednjaVrednost = suma / dimenzija;

        int najbliziIndeks = 0;
        double najmanjaRazlika = std::abs(niz[0] - srednjaVrednost);
        for (int i = 1; i < dimenzija; ++i) {
            double razlika = std::abs(niz[i] - srednjaVrednost);
            if (razlika < najmanjaRazlika) {
                najmanjaRazlika = razlika;
                najbliziIndeks = i;
            }
        }
        return najbliziIndeks;
    }

    // Funkcija za prikazivanje elemenata vektora
    void prikazi() const {
        std::cout << "Elementi vektora: ";
        for (int i = 0; i < dimenzija; ++i) {
            std::cout << niz[i] << " ";
        }
        std::cout << std::endl;
    }

    // Funkcija za unos elemenata sa standardnog ulaza
    void ucitajElemente() {
        std::cout << "Unesite elemente vektora: ";
        for (int i = 0; i < dimenzija; ++i) {
            std::cin >> niz[i];
        }
    }
};

int main() {
    // Kreiranje objekta klase Vektor i učitavanje elemenata sa standardnog ulaza
    Vektor vektor1(5);
    vektor1.ucitajElemente();
    vektor1.sortiraj();
    vektor1.prikazi();

    // Kreiranje još jednog objekta u dinamičkoj zoni memorije
    Vektor* vektor2 = new Vektor(5);
    vektor2->ucitajElemente();
    vektor2->prikazi();

    // Testiranje skalarnog proizvoda
    std::cout << "Skalarni proizvod vektor1 i vektor2: " << vektor1.skalarniProizvod(*vektor2) << std::endl;

    // Prikaz indeksa elementa najbližeg srednjoj vrednosti za vektor1
    int indeks = vektor1.indeksNajbliziSrednjoj();
    if (indeks != -1) {
        std::cout << "Indeks elementa najblizeg srednjoj vrednosti u vektor1: " << indeks << std::endl;
    }

    delete vektor2;

    return 0;
}


// Zadatak 6: Klasa Minesweeper i main
#include <iostream>
#include <cstring>

class Minesweeper {
private:
    bool** polje;
    int dimenzija;
    char* nazivPolja;

public:
    // Default konstruktor koji postavlja dimenziju matrice na 10x10
    Minesweeper() : dimenzija(10) {
        polje = new bool*[dimenzija];
        for (int i = 0; i < dimenzija; ++i) {
            polje[i] = new bool[dimenzija]();
        }
        nazivPolja = new char[100];
        strcpy(nazivPolja, "Minsko polje");
    }

    // Konstruktor sa parametrima
    Minesweeper(int dim, const char* naziv = "Minsko polje") : dimenzija(dim) {
        polje = new bool*[dimenzija];
        for (int i = 0; i < dimenzija; ++i) {
            polje[i] = new bool[dimenzija]();
        }
        nazivPolja = new char[strlen(naziv) + 1];
        strcpy(nazivPolja, naziv);
    }

    // Destruktor
    ~Minesweeper() {
        for (int i = 0; i < dimenzija; ++i) {
            delete[] polje[i];
        }
        delete[] polje;
        delete[] nazivPolja;
    }

    // Inline funkcije za vraćanje dimenzija polja
    int getDimenzija() const { return dimenzija; }

    // Funkcija za učitavanje rasporeda mina
    void ucitajRaspored() {
        std::cout << "Unesite raspored mina (0 ili 1 za svaki element): ";
        for (int i = 0; i < dimenzija; ++i) {
            for (int j = 0; j < dimenzija; ++j) {
                int vrednost;
                std::cin >> vrednost;
                polje[i][j] = (vrednost == 1);
            }
        }
    }

    // Funkcija za prikaz minskog polja
    void prikaziPolje() const {
        std::cout << "Raspored mina: \n";
        for (int i = 0; i < dimenzija; ++i) {
            for (int j = 0; j < dimenzija; ++j) {
                std::cout << (polje[i][j] ? "1 " : "0 ");
            }
            std::cout << std::endl;
        }
    }

    // Funkcija koja vraća broj mina koje okružuju zadato polje
    int brojMina(int x, int y) const {
        if (x < 0 || x >= dimenzija || y < 0 || y >= dimenzija) {
            return -1;
        }
        if (polje[x][y]) {
            return -1;
        }
        int count = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int nx = x + i;
                int ny = y + j;
                if (nx >= 0 && nx < dimenzija && ny >= 0 && ny < dimenzija && polje[nx][ny]) {
                    ++count;
                }
            }
        }
        return count;
    }

    // Funkcija koja izbacuje sve redove i kolone bez mina
    void izbaciRedoveIKoloneBezMina() {
        bool* redoviZaBrisanje = new bool[dimenzija]();
        bool* koloneZaBrisanje = new bool[dimenzija]();

        for (int i = 0; i < dimenzija; ++i) {
            bool minaURedu = false;
            bool minaUKoloni = false;
            for (int j = 0; j < dimenzija; ++j) {
                if (polje[i][j]) minaURedu = true;
                if (polje[j][i]) minaUKoloni = true;
            }
            if (!minaURedu) redoviZaBrisanje[i] = true;
            if (!minaUKoloni) koloneZaBrisanje[i] = true;
        }

        std::cout << "Polje nakon izbacivanja redova i kolona bez mina:\n";
        for (int i = 0; i < dimenzija; ++i) {
            if (redoviZaBrisanje[i]) continue;
            for (int j = 0; j < dimenzija; ++j) {
                if (koloneZaBrisanje[j]) continue;
                std::cout << (polje[i][j] ? "1 " : "0 ");
            }
            std::cout << std::endl;
        }

        delete[] redoviZaBrisanje;
        delete[] koloneZaBrisanje;
    }
};

int main() {
    // Kreiranje objekta klase Minesweeper sa default dimenzijama 10x10
    Minesweeper minesweeper;
    minesweeper.ucitajRaspored();
    
    // Učitavanje pozicije polja
    int x, y;
    std::cout << "Unesite poziciju polja (x y): ";
    std::cin >> x >> y;

    // Provera da li je na toj poziciji mina
    if (minesweeper.brojMina(x, y) == -1) {
        std::cout << "Na polju (" << x << ", " << y << ") nalazi se mina. Prikazuje se cela tabla: \n";
        minesweeper.prikaziPolje();
    } else {
        std::cout << "Broj mina oko polja (" << x << ", " << y << "): " << minesweeper.brojMina(x, y) << std::endl;
    }

    // Kreiranje još jednog objekta u dinamičkoj zoni memorije
    Minesweeper* dynMinesweeper = new Minesweeper(5);
    dynMinesweeper->ucitajRaspored();
    dynMinesweeper->prikaziPolje();
    dynMinesweeper->izbaciRedoveIKoloneBezMina();
    delete dynMinesweeper;

    return 0;
}


// Zadatak 7: Klasa Matrica i main
#include <iostream>
#include <cstring>

class Matrica {
private:
    double** matrica;
    int redovi;
    int kolone;
    char* naziv;

public:
    // Konstruktor bez parametara (dimenzija 20x20)
    Matrica() : redovi(20), kolone(20) {
        naziv = new char[8]; // Default naziv "Matrica"
        strcpy(naziv, "Matrica");
        matrica = new double*[redovi];
        for (int i = 0; i < redovi; ++i) {
            matrica[i] = new double[kolone]();
        }
    }

    // Konstruktor sa parametrima za postavljanje dimenzija matrice
    Matrica(int r, int k, const char* nazivMatrice = "Matrica") : redovi(r), kolone(k) {
        naziv = new char[strlen(nazivMatrice) + 1];
        strcpy(naziv, nazivMatrice);
        matrica = new double*[redovi];
        for (int i = 0; i < redovi; ++i) {
            matrica[i] = new double[kolone]();
        }
    }

    // Destruktor
    ~Matrica() {
        for (int i = 0; i < redovi; ++i) {
            delete[] matrica[i];
        }
        delete[] matrica;
        delete[] naziv;
    }

    // Inline funkcije koje vraćaju dimenzije matrice
    int getRedovi() const { return redovi; }
    int getKolone() const { return kolone; }

    // Funkcija koja vraća sumu elemenata traženog reda
    double sumaReda(int red) const {
        if (red < 0 || red >= redovi) {
            std::cerr << "Neispravan indeks reda!" << std::endl;
            return 0;
        }
        double suma = 0;
        for (int j = 0; j < kolone; ++j) {
            suma += matrica[red][j];
        }
        return suma;
    }

    // Funkcija koja vraća sumu elemenata tražene kolone
    double sumaKolone(int kolona) const {
        if (kolona < 0 || kolona >= kolone) {
            std::cerr << "Neispravan indeks kolone!" << std::endl;
            return 0;
        }
        double suma = 0;
        for (int i = 0; i < redovi; ++i) {
            suma += matrica[i][kolona];
        }
        return suma;
    }

    // Funkcija za unos elemenata matrice sa standardnog ulaza
    void unesiElemente() {
        std::cout << "Unesite elemente matrice (" << redovi << "x" << kolone << "): \n";
        for (int i = 0; i < redovi; ++i) {
            for (int j = 0; j < kolone; ++j) {
                std::cin >> matrica[i][j];
            }
        }
    }

    // Funkcija za prikaz matrice na standardni izlaz
    void prikazi() const {
        std::cout << "Naziv matrice: " << naziv << "\nElementi matrice: \n";
        for (int i = 0; i < redovi; ++i) {
            for (int j = 0; j < kolone; ++j) {
                std::cout << matrica[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Funkcija za računanje Kronekerovog proizvoda dve matrice
    static Matrica kronekerProizvod(const Matrica& A, const Matrica& B) {
        int noviRedovi = A.redovi * B.redovi;
        int noveKolone = A.kolone * B.kolone;
        Matrica rezultat(noviRedovi, noveKolone);

        for (int i = 0; i < A.redovi; ++i) {
            for (int j = 0; j < A.kolone; ++j) {
                for (int k = 0; k < B.redovi; ++k) {
                    for (int l = 0; l < B.kolone; ++l) {
                        rezultat.matrica[i * B.redovi + k][j * B.kolone + l] = A.matrica[i][j] * B.matrica[k][l];
                    }
                }
            }
        }
        return rezultat;
    }

    // Funkcija za računanje proizvoda dve matrice
    static Matrica proizvod(const Matrica& A, const Matrica& B) {
        if (A.kolone != B.redovi) {
            std::cerr << "Matrice nisu kompatibilne za množenje!" << std::endl;
            return Matrica(0, 0);
        }

        Matrica rezultat(A.redovi, B.kolone);
        for (int i = 0; i < A.redovi; ++i) {
            for (int j = 0; j < B.kolone; ++j) {
                rezultat.matrica[i][j] = 0;
                for (int k = 0; k < A.kolone; ++k) {
                    rezultat.matrica[i][j] += A.matrica[i][k] * B.matrica[k][j];
                }
            }
        }
        return rezultat;
    }
};

int main() {
    // Kreiranje objekta klase Matrica sa default dimenzijama 20x20
    Matrica matrica;
    matrica.unesiElemente();
    matrica.prikazi();

    // Provera sume elemenata prvog reda i prve kolone
    std::cout << "Suma elemenata prvog reda: " << matrica.sumaReda(0) << std::endl;
    std::cout << "Suma elemenata prve kolone: " << matrica.sumaKolone(0) << std::endl;

    // Kreiranje još jedne matrice i testiranje proizvoda matrica
    Matrica matricaA(2, 3, "A");
    Matrica matricaB(3, 2, "B");
    matricaA.unesiElemente();
    matricaB.unesiElemente();
    
    Matrica rezultat = Matrica::proizvod(matricaA, matricaB);
    rezultat.prikazi();

    // Testiranje Kronekerovog proizvoda
    Matrica kronekerRezultat = Matrica::kronekerProizvod(matricaA, matricaB);
    kronekerRezultat.prikazi();

    return 0;
}


// Zadatak 8: Klasa String i main
#include <iostream>
#include <cstring>

class String {
private:
    char* niz;
    int duzina;

public:
    // Konstruktor bez argumenata
    String() : niz(nullptr), duzina(0) {}

    // Konstruktor sa argumentom
    String(const char* str) {
        duzina = strlen(str);
        niz = new char[duzina + 1];
        strcpy(niz, str);
    }

    // Destruktor
    ~String() {
        delete[] niz;
    }

    // Inline funkcija za vraćanje dužine stringa
    int getDuzina() const { return duzina; }

    // Funkcija koja pronalazi početnu poziciju zadatog podstringa u stringu
    int pronadjiPodstring(const char* podstring) const {
        char* pos = strstr(niz, podstring);
        if (pos) {
            return pos - niz;
        }
        return -1;
    }

    // Funkcija za učitavanje stringa sa standardnog ulaza
    void ucitaj() {
        char temp[11]; // Maksimalna dužina stringa je 10 karaktera + null terminator
        std::cout << "Unesite string (maksimalno 10 karaktera): ";
        std::cin.getline(temp, 11);
        duzina = strlen(temp);
        niz = new char[duzina + 1];
        strcpy(niz, temp);
    }

    // Funkcija za prikaz stringa na standardni izlaz
    void prikazi() const {
        std::cout << "String: " << niz << std::endl;
    }
};

int main() {
    // Kreiranje objekta klase String sa maksimalnom dužinom od 10 karaktera
    String str;
    str.ucitaj();
    str.prikazi();

    // Provera da li string sadrži podstring "ana"
    if (str.pronadjiPodstring("ana") != -1) {
        std::cout << "String sadrzi podstring 'ana'" << std::endl;
    } else {
        std::cout << "String ne sadrzi podstring 'ana'" << std::endl;
    }

    // Kreiranje drugog objekta klase String u dinamičkoj zoni memorije
    String* dynStr = new String("ana voli milovana");
    dynStr->prikazi();
    std::cout << "Pozicija podstringa 'ana': " << dynStr->pronadjiPodstring("ana") << std::endl;
    delete dynStr;

    return 0;
}


// ZADATAK 9
#include <iostream>
#include <utility>
#include <algorithm>
#include <cmath>

class Picture {
private:
    int** matrica;
    int width;
    int height;

public:
    // Default konstruktor
    Picture() : matrica(nullptr), width(0), height(0) {}

    // Konstruktor sa dimenzijom
    Picture(int dim) : width(dim), height(dim) {
        matrica = new int*[height];
        for (int i = 0; i < height; ++i) {
            matrica[i] = new int[width];
            for (int j = 0; j < width; ++j) {
                matrica[i][j] = 0;
            }
        }
    }

    // Destruktor
    ~Picture() {
        for (int i = 0; i < height; ++i) {
            delete[] matrica[i];
        }
        delete[] matrica;
    }

    // Inline funkcija za vraćanje dimenzije
    inline std::pair<int, int> getDimensions() const { return {width, height}; }

    // Funkcija za dodavanje osvetljenosti
    void brightness(int s) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                matrica[i][j] = std::min(512, std::max(0, matrica[i][j] + s));
            }
        }
    }

    // Funkcija za prikaz slike
    void display() const {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                std::cout << matrica[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Funkcija za promenu veličine slike
    void resize(int nWidth, int nHeight) {
        double nXFactor = static_cast<double>(width) / nWidth;
        double nYFactor = static_cast<double>(height) / nHeight;

        int** newMatrica = new int*[nHeight];
        for (int i = 0; i < nHeight; ++i) {
            newMatrica[i] = new int[nWidth];
            for (int j = 0; j < nWidth; ++j) {
                int srcX = static_cast<int>(std::floor(j * nXFactor));
                int srcY = static_cast<int>(std::floor(i * nYFactor));
                newMatrica[i][j] = matrica[srcY][srcX];
            }
        }

        for (int i = 0; i < height; ++i) {
            delete[] matrica[i];
        }
        delete[] matrica;

        matrica = newMatrica;
        width = nWidth;
        height = nHeight;
    }

    // Učitavanje sadržaja iz standardnog ulaza
    void loadFromInput() {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                std::cin >> matrica[i][j];
                matrica[i][j] = std::min(512, std::max(0, matrica[i][j]));
            }
        }
    }
};

int main() {
    // Kreiranje objekta klase Picture dimenzija 10x10
    Picture picture(10);

    // Učitavanje sadržaja matrice sa standardnog ulaza
    std::cout << "Unesite elemente matrice (10x10):" << std::endl;
    picture.loadFromInput();

    // Prikazivanje originalne slike
    std::cout << "Originalna slika:" << std::endl;
    picture.display();

    // Prikazivanje dimenzija slike
    auto dimensions = picture.getDimensions();
    std::cout << "Dimenzije slike su: " << dimensions.first << "x" << dimensions.second << std::endl;

    // Promena osvetljenosti
    picture.brightness(50);
    std::cout << "Slika sa promenjenom osvetljenošću:" << std::endl;
    picture.display();

    // Promena veličine slike
    picture.resize(5, 5);
    std::cout << "Slika nakon promene veličine (5x5):" << std::endl;
    picture.display();

    return 0;
}

