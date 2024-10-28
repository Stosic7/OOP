#include <iostream>
#include <cstring>
#include <cmath>

// Zadatak 0: Klasa Skup i main
class Skup {
private:
    int brojElemenata;
    int* elementi;

public:
    Skup() : brojElemenata(0), elementi(nullptr) {}

    Skup(int broj) : brojElemenata(broj) {
        elementi = new int[broj];
    }

    ~Skup() {
        delete[] elementi;
    }

    inline int getBrojElemenata() const {
        return brojElemenata;
    }

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

    bool pripadaSkupu(int element) const {
        for (int i = 0; i < brojElemenata; ++i) {
            if (elementi[i] == element) {
                return true;
            }
        }
        return false;
    }

    void ucitajElemente() {
        std::cout << "Unesite " << brojElemenata << " elemenata: ";
        for (int i = 0; i < brojElemenata; ++i) {
            std::cin >> elementi[i];
        }
    }

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

    void prikaziElemente() const {
        std::cout << "Elementi skupa: ";
        for (int i = 0; i < brojElemenata; ++i) {
            std::cout << elementi[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    Skup* skup = new Skup(10);
    skup->ucitajElemente();
    skup->izbaciDuplikate();
    skup->sortirajNerastuci();
    skup->prikaziElemente();
    delete skup;
    return 0;
}

// Zadatak 1: Klasa Student i main
class Student {
private:
    char* imePrezime;
    int brojIndeksa;
    int maxBrojIspita;
    int brojPolozenih;
    int* ocene;

public:
    Student(int maxIspita) : maxBrojIspita(maxIspita), brojPolozenih(0) {
        imePrezime = new char[100];
        ocene = new int[maxBrojIspita];
    }

    ~Student() {
        delete[] imePrezime;
        delete[] ocene;
    }

    inline int getBrojIndeksa() const {
        return brojIndeksa;
    }

    inline int getBrojPolozenih() const {
        return brojPolozenih;
    }

    void dodajOcenu(int ocena) {
        if (brojPolozenih < maxBrojIspita) {
            ocene[brojPolozenih++] = ocena;
        }
    }

    void ucitajPodatke() {
        std::cout << "Unesite ime i prezime studenta: ";
        std::cin.ignore();
        std::cin.getline(imePrezime, 100);
        std::cout << "Unesite broj indeksa: ";
        std::cin >> brojIndeksa;
    }

    void prikaziOcene() const {
        std::cout << "Ocene (od najvece do najmanje): ";
        for (int i = brojPolozenih - 1; i >= 0; --i) {
            std::cout << ocene[i] << " ";
        }
        std::cout << std::endl;
    }

    void prikaziPodatke() const {
        std::cout << "Ime i prezime: " << imePrezime << ", Broj indeksa: " << brojIndeksa << std::endl;
    }

    void azurirajImePrezime(const char* novoImePrezime) {
        strcpy(imePrezime, novoImePrezime);
    }
};

int main() {
    Student* student = new Student(5);
    student->ucitajPodatke();
    student->dodajOcenu(10);
    student->dodajOcenu(9);
    student->prikaziOcene();
    student->prikaziPodatke();
    delete student;
    return 0;
}

// Zadatak 2: Klasa Poligon i main
class Poligon {
private:
    int brojTemena;
    int* xKoordinate;
    int* yKoordinate;

public:
    Poligon(int broj) : brojTemena(broj) {
        xKoordinate = new int[broj];
        yKoordinate = new int[broj];
    }

    ~Poligon() {
        delete[] xKoordinate;
        delete[] yKoordinate;
    }

    inline int getBrojTemena() const {
        return brojTemena;
    }

    void ucitajKoordinate() {
        std::cout << "Unesite koordinate temena: ";
        for (int i = 0; i < brojTemena; ++i) {
            std::cin >> xKoordinate[i] >> yKoordinate[i];
        }
    }

    double izracunajObim() const {
        double obim = 0;
        for (int i = 0; i < brojTemena; ++i) {
            int next = (i + 1) % brojTemena;
            obim += sqrt(pow(xKoordinate[next] - xKoordinate[i], 2) + pow(yKoordinate[next] - yKoordinate[i], 2));
        }
        return obim;
    }

    void prikaziKoordinate() const {
        std::cout << "Koordinate temena: ";
        for (int i = 0; i < brojTemena; ++i) {
            std::cout << "(" << xKoordinate[i] << ", " << yKoordinate[i] << ") ";
        }
        std::cout << std::endl;
    }
};

int main() {
    Poligon* poligon = new Poligon(4);
    poligon->ucitajKoordinate();
    std::cout << "Obim poligona: " << poligon->izracunajObim() << std::endl;
    poligon->prikaziKoordinate();
    delete poligon;
    return 0;
}

// Zadatak 3: Klasa Image i main
class Image {
private:
    int dimenzija;
    int** matrica;
    char* nazivLokacije;

public:
    Image(int dim) : dimenzija(dim) {
        matrica = new int*[dimenzija];
        for (int i = 0; i < dimenzija; ++i) {
            matrica[i] = new int[dimenzija];
        }
        nazivLokacije = new char[100];
    }

    ~Image() {
        for (int i = 0; i < dimenzija; ++i) {
            delete[] matrica[i];
        }
        delete[] matrica;
        delete[] nazivLokacije;
    }

    inline int getDimenzija() const {
        return dimenzija;
    }

    void invertujSliku() {
        for (int i = 0; i < dimenzija; ++i) {
            for (int j = 0; j < dimenzija; ++j) {
                matrica[i][j] = 1 - matrica[i][j];
            }
        }
    }

    void ucitajSadrzaj() {
        std::cout << "Unesite sadrzaj slike (0 ili 1 za svaki element): ";
        for (int i = 0; i < dimenzija; ++i) {
            for (int j = 0; j < dimenzija; ++j) {
                std::cin >> matrica[i][j];
            }
        }
    }

    void prikaziSadrzaj() const {
        std::cout << "Sadrzaj slike: \n";
        for (int i = 0; i < dimenzija; ++i) {
            for (int j = 0; j < dimenzija; ++j) {
                std::cout << matrica[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void crop(int novaDimenzija) {
        if (novaDimenzija >= dimenzija) return;
        for (int i = novaDimenzija; i < dimenzija; ++i) {
            delete[] matrica[i];
        }
        dimenzija = novaDimenzija;
    }
};

int main() {
    Image* image = new Image(5);
    image->ucitajSadrzaj();
    image->invertujSliku();
    image->prikaziSadrzaj();
    delete image;
    return 0;
}

// Zadatak 4: Klasa Buffer i main
class Buffer {
private:
    int* niz;
    int velicina;
    int brojElemenata;

public:
    Buffer(int vel) : velicina(vel), brojElemenata(0) {
        niz = new int[velicina];
    }

    ~Buffer() {
        delete[] niz;
    }

    inline int getBrojElemenata() const {
        return brojElemenata;
    }

    void push(int element) {
        if (brojElemenata < velicina) {
            niz[brojElemenata++] = element;
        }
    }

    int pop() {
        if (brojElemenata > 0) {
            return niz[--brojElemenata];
        }
        return -1; // Error value
    }

    void prikazi() const {
        std::cout << "Sadrzaj bafera: ";
        for (int i = 0; i < brojElemenata; ++i) {
            std::cout << niz[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    Buffer* buffer = new Buffer(10);
    buffer->push(5);
    buffer->push(10);
    buffer->push(15);
    buffer->prikazi();
    buffer->pop();
    buffer->prikazi();
    delete buffer;
    return 0;
}

// Zadatak 5: Klasa Vektor i main
class Vektor {
private:
    int* niz;
    int dimenzija;

public:
    Vektor(int dim) : dimenzija(dim) {
        niz = new int[dimenzija];
    }

    ~Vektor() {
        delete[] niz;
    }

    void setElement(int index, int value) {
        if (index >= 0 && index < dimenzija) {
            niz[index] = value;
        }
    }

    int getElement(int index) const {
        if (index >= 0 && index < dimenzija) {
            return niz[index];
        }
        return -1; // Error value
    }

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

    void prikazi() const {
        std::cout << "Elementi vektora: ";
        for (int i = 0; i < dimenzija; ++i) {
            std::cout << niz[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    Vektor* vektor = new Vektor(5);
    vektor->setElement(0, 10);
    vektor->setElement(1, 5);
    vektor->setElement(2, 20);
    vektor->setElement(3, 15);
    vektor->setElement(4, 25);
    vektor->sortiraj();
    vektor->prikazi();
    delete vektor;
    return 0;
}

// Zadatak 6: Klasa Minesweeper i main
class Minesweeper {
private:
    bool** polje;
    int dimenzija;
    char* nazivPolja;

public:
    Minesweeper(int dim) : dimenzija(dim) {
        polje = new bool*[dimenzija];
        for (int i = 0; i < dimenzija; ++i) {
            polje[i] = new bool[dimenzija];
        }
        nazivPolja = new char[100];
    }

    ~Minesweeper() {
        for (int i = 0; i < dimenzija; ++i) {
            delete[] polje[i];
        }
        delete[] polje;
        delete[] nazivPolja;
    }

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

    void prikaziPolje() const {
        std::cout << "Raspored mina: \n";
        for (int i = 0; i < dimenzija; ++i) {
            for (int j = 0; j < dimenzija; ++j) {
                std::cout << polje[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

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
};

int main() {
    Minesweeper* minesweeper = new Minesweeper(5);
    minesweeper->ucitajRaspored();
    minesweeper->prikaziPolje();
    std::cout << "Broj mina oko polja (2, 2): " << minesweeper->brojMina(2, 2) << std::endl;
    delete minesweeper;
    return 0;
}

// Zadatak 7: Klasa Matrica i main
class Matrica {
private:
    double** matrica;
    int redovi;
    int kolone;

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

    void unesiElemente() {
        std::cout << "Unesite elemente matrice: \n";
        for (int i = 0; i < redovi; ++i) {
            for (int j = 0; j < kolone; ++j) {
                std::cin >> matrica[i][j];
            }
        }
    }

    void prikazi() const {
        std::cout << "Elementi matrice: \n";
        for (int i = 0; i < redovi; ++i) {
            for (int j = 0; j < kolone; ++j) {
                std::cout << matrica[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    Matrica* matrica = new Matrica(3, 3);
    matrica->unesiElemente();
    matrica->prikazi();
    delete matrica;
    return 0;
}

// Zadatak 8: Klasa String i main
class String {
private:
    char* niz;
    int duzina;

public:
    String(const char* str) {
        duzina = strlen(str);
        niz = new char[duzina + 1];
        strcpy(niz, str);
    }

    ~String() {
        delete[] niz;
    }

    int pronadjiPodstring(const char* podstring) const {
        char* pos = strstr(niz, podstring);
        if (pos) {
            return pos - niz;
        }
        return -1;
    }

    void prikazi() const {
        std::cout << "String: " << niz << std::endl;
    }
};

int main() {
    String* str = new String("ana voli milovana");
    str->prikazi();
    std::cout << "Pozicija podstringa 'ana': " << str->pronadjiPodstring("ana") << std::endl;
    delete str;
    return 0;
}

// Zadatak 9: Klasa Picture i main
class Picture {
private:
    int dimenzija;
    int** matrica;

public:
    Picture(int dim) : dimenzija(dim) {
        matrica = new int*[dimenzija];
        for (int i = 0; i < dimenzija; ++i) {
            matrica[i] = new int[dimenzija];
        }
    }

    ~Picture() {
        for (int i = 0; i < dimenzija; ++i) {
            delete[] matrica[i];
        }
        delete[] matrica;
    }

    void ucitajSadrzaj() {
        std::cout << "Unesite sadrzaj slike: \n";
        for (int i = 0; i < dimenzija; ++i) {
            for (int j = 0; j < dimenzija; ++j) {
                std::cin >> matrica[i][j];
            }
        }
    }

    void prikazi() const {
        std::cout << "Sadrzaj slike: \n";
        for (int i = 0; i < dimenzija; ++i) {
            for (int j = 0; j < dimenzija; ++j) {
                std::cout << matrica[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void brightness(int s) {
        for (int i = 0; i < dimenzija; ++i) {
            for (int j = 0; j < dimenzija; ++j) {
                matrica[i][j] = std::min(512, std::max(0, matrica[i][j] + s));
            }
        }
    }
};

int main() {
    Picture* picture = new Picture(3);
    picture->ucitajSadrzaj();
    picture->brightness(100);
    picture->prikazi();
    delete picture;
    return 0;
}
