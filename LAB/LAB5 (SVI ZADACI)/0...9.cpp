//ZADATAK 0
#include <iostream>
#include <cstring>
using namespace std;

// Template class Set
template <typename T>
class Set {
private:
    int brojElemenata;
    T* elementi;

public:
    Set() : brojElemenata(0), elementi(nullptr) {}

    Set(int broj) : brojElemenata(broj) {
        elementi = new T[brojElemenata];
    }

    ~Set() {
        delete[] elementi;
    }

    int getBrojElemenata() const {
        return brojElemenata;
    }

    bool pripada(const T& element) const {
        for (int i = 0; i < brojElemenata; ++i) {
            if (elementi[i] == element) {
                return true;
            }
        }
        return false;
    }

    Set<T> operator*(const Set<T>& drugi) const {
        Set<T> presek;
        for (int i = 0; i < brojElemenata; ++i) {
            if (drugi.pripada(elementi[i])) {
                presek.dodaj(elementi[i]);
            }
        }
        return presek;
    }

    void dodaj(const T& element) {
        if (!pripada(element)) {
            T* noviElementi = new T[brojElemenata + 1];
            for (int i = 0; i < brojElemenata; ++i) {
                noviElementi[i] = elementi[i];
            }
            noviElementi[brojElemenata] = element;
            delete[] elementi;
            elementi = noviElementi;
            ++brojElemenata;
        }
    }

    template <typename U>
    friend istream& operator>>(istream& in, Set<U>& set);

    template <typename U>
    friend ostream& operator<<(ostream& out, const Set<U>& set);
};

// Overloading >> operator for Set
template <typename T>
istream& operator>>(istream& in, Set<T>& set) {
    for (int i = 0; i < set.brojElemenata; ++i) {
        in >> set.elementi[i];
    }
    return in;
}

// Overloading << operator for Set
template <typename T>
ostream& operator<<(ostream& out, const Set<T>& set) {
    for (int i = 0; i < set.brojElemenata; ++i) {
        out << set.elementi[i] << " ";
    }
    return out;
}

// Movie class
class Movie {
private:
    char* naziv;
    char* punoImeReditelja;
    int trajanje;

public:
    Movie() : naziv(nullptr), punoImeReditelja(nullptr), trajanje(0) {}

    ~Movie() {
        delete[] naziv;
        delete[] punoImeReditelja;
    }

    Movie& operator=(const Movie& other) {
        if (this != &other) {
            delete[] naziv;
            delete[] punoImeReditelja;
            naziv = new char[strlen(other.naziv) + 1];
            strcpy(naziv, other.naziv);
            punoImeReditelja = new char[strlen(other.punoImeReditelja) + 1];
            strcpy(punoImeReditelja, other.punoImeReditelja);
            trajanje = other.trajanje;
        }
        return *this;
    }

    bool operator==(const Movie& other) const {
        return strcmp(naziv, other.naziv) == 0 && strcmp(punoImeReditelja, other.punoImeReditelja) == 0 && trajanje == other.trajanje;
    }

    friend istream& operator>>(istream& in, Movie& movie);
    friend ostream& operator<<(ostream& out, const Movie& movie);
};

// Overloading >> operator for Movie
istream& operator>>(istream& in, Movie& movie) {
    char buffer[100];
    cout << "Unesite naziv filma: ";
    in >> ws;
    in.getline(buffer, 100);
    movie.naziv = new char[strlen(buffer) + 1];
    strcpy(movie.naziv, buffer);

    cout << "Unesite puno ime reditelja: ";
    in.getline(buffer, 100);
    movie.punoImeReditelja = new char[strlen(buffer) + 1];
    strcpy(movie.punoImeReditelja, buffer);

    cout << "Unesite trajanje filma: ";
    in >> movie.trajanje;

    return in;
}

// Overloading << operator for Movie
ostream& operator<<(ostream& out, const Movie& movie) {
    out << "Naziv: " << movie.naziv << ", Reditelj: " << movie.punoImeReditelja << ", Trajanje: " << movie.trajanje;
    return out;
}

int main() {
    // Testing Set with double
    Set<double> skupDouble(5);
    cout << "Unesite 5 elemenata skupa tipa double: " << endl;
    cin >> skupDouble;
    cout << "Sadrzaj skupa tipa double: " << skupDouble << endl;

    // Testing Set with Movie
    Set<Movie> skupFilmova(3);
    cout << "Unesite 3 filma: " << endl;
    cin >> skupFilmova;
    cout << "Sadrzaj skupa filmova: " << endl << skupFilmova << endl;

    return 0;
}

//ZADATAK 1
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

// Template class Array
template <typename T>
class Array {
private:
    T elementi[100]; // Static array of 100 elements
    int brojElemenata;

public:
    Array() : brojElemenata(0) {}

    T& operator[](int index) {
        return elementi[index];
    }

    int getBrojElemenata() const {
        return brojElemenata;
    }

    void ucitajElemente() {
        cout << "Unesite broj elemenata: ";
        cin >> brojElemenata;
        for (int i = 0; i < brojElemenata; ++i) {
            cout << "Unesite element na poziciji " << i << ": ";
            cin >> elementi[i];
        }
    }

    void stampajElemente() const {
        for (int i = 0; i < brojElemenata; ++i) {
            cout << elementi[i] << " ";
        }
        cout << endl;
    }

    void sort() {
        std::sort(elementi, elementi + brojElemenata);
    }
};

// Student class
class Student {
private:
    char ime[50];
    char prezime[50];
    int brojIndeksa;
    double prosecnaOcena;

public:
    Student() : brojIndeksa(0), prosecnaOcena(0.0) {
        strcpy(ime, "");
        strcpy(prezime, "");
    }

    bool operator>(const Student& other) const {
        return prosecnaOcena > other.prosecnaOcena;
    }

    Student& operator=(const Student& other) {
        if (this != &other) {
            strcpy(ime, other.ime);
            strcpy(prezime, other.prezime);
            brojIndeksa = other.brojIndeksa;
            prosecnaOcena = other.prosecnaOcena;
        }
        return *this;
    }

    friend istream& operator>>(istream& in, Student& student);
    friend ostream& operator<<(ostream& out, const Student& student);
};

// Overloading >> operator for Student
istream& operator>>(istream& in, Student& student) {
    cout << "Unesite ime: ";
    in >> ws;
    in.getline(student.ime, 50);
    cout << "Unesite prezime: ";
    in.getline(student.prezime, 50);
    cout << "Unesite broj indeksa: ";
    in >> student.brojIndeksa;
    cout << "Unesite prosecnu ocenu: ";
    in >> student.prosecnaOcena;
    return in;
}

// Overloading << operator for Student
ostream& operator<<(ostream& out, const Student& student) {
    out << "Ime: " << student.ime << ", Prezime: " << student.prezime << ", Broj indeksa: " << student.brojIndeksa << ", Prosecna ocena: " << student.prosecnaOcena;
    return out;
}

int main() {
    // Testing Array with double
    Array<double> nizDouble;
    nizDouble.ucitajElemente();
    cout << "Sadrzaj niza tipa double: ";
    nizDouble.stampajElemente();
    nizDouble.sort();
    cout << "Sortiran niz tipa double: ";
    nizDouble.stampajElemente();

    // Testing Array with Student
    Array<Student> nizStudenata;
    nizStudenata.ucitajElemente();
    cout << "Sadrzaj niza studenata: " << endl;
    nizStudenata.stampajElemente();
    nizStudenata.sort();
    cout << "Sortiran niz studenata: " << endl;
    nizStudenata.stampajElemente();

    return 0;
}

//ZADATAK 2
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

// Template class Poligon
template <typename T, int N>
class Poligon {
private:
    T tacke[N]; // Static array of points

public:
    Poligon() {}

    double obim() const {
        double sum = 0;
        for (int i = 0; i < N - 1; ++i) {
            sum += tacke[i].rastojanje(tacke[i + 1]);
        }
        sum += tacke[N - 1].rastojanje(tacke[0]);
        return sum;
    }

    Poligon& operator--() { // Prefix -- (symmetry over x-axis)
        for (int i = 0; i < N; ++i) {
            --tacke[i];
        }
        return *this;
    }

    Poligon operator--(int) { // Postfix -- (symmetry over y-axis)
        Poligon temp = *this;
        for (int i = 0; i < N; ++i) {
            tacke[i]--;
        }
        return temp;
    }

    friend istream& operator>>(istream& in, Poligon& poligon) {
        for (int i = 0; i < N; ++i) {
            cout << "Unesite tacku " << i + 1 << ": ";
            in >> poligon.tacke[i];
        }
        return in;
    }

    friend ostream& operator<<(ostream& out, const Poligon& poligon) {
        for (int i = 0; i < N; ++i) {
            out << "Tacka " << i + 1 << ": " << poligon.tacke[i] << endl;
        }
        return out;
    }
};

// DekartovaTacka class
class DekartovaTacka {
private:
    double x;
    double y;

public:
    DekartovaTacka() : x(0.0), y(0.0) {}

    DekartovaTacka(double x, double y) : x(x), y(y) {}

    double rastojanje(const DekartovaTacka& other) const {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }

    DekartovaTacka& operator--() { // Prefix -- (symmetry over x-axis)
        y = -y;
        return *this;
    }

    DekartovaTacka operator--(int) { // Postfix -- (symmetry over y-axis)
        DekartovaTacka temp = *this;
        x = -x;
        return temp;
    }

    friend istream& operator>>(istream& in, DekartovaTacka& tacka) {
        cout << "Unesite x koordinatu: ";
        in >> tacka.x;
        cout << "Unesite y koordinatu: ";
        in >> tacka.y;
        return in;
    }

    friend ostream& operator<<(ostream& out, const DekartovaTacka& tacka) {
        out << "(" << tacka.x << ", " << tacka.y << ")";
        return out;
    }
};

// PolarnaTacka class
class PolarnaTacka {
private:
    double r;
    double theta;

public:
    PolarnaTacka() : r(0.0), theta(0.0) {}

    PolarnaTacka(double r, double theta) : r(r), theta(theta) {}

    double rastojanje(const PolarnaTacka& other) const {
        double x1 = r * cos(theta);
        double y1 = r * sin(theta);
        double x2 = other.r * cos(other.theta);
        double y2 = other.r * sin(other.theta);
        return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    }

    PolarnaTacka& operator--() { // Prefix -- (symmetry over x-axis)
        theta = -theta;
        return *this;
    }

    PolarnaTacka operator--(int) { // Postfix -- (symmetry over y-axis)
        PolarnaTacka temp = *this;
        theta = M_PI - theta;
        return temp;
    }

    friend istream& operator>>(istream& in, PolarnaTacka& tacka) {
        cout << "Unesite rastojanje od koordinatnog pocetka: ";
        in >> tacka.r;
        cout << "Unesite ugao (u radijanima): ";
        in >> tacka.theta;
        return in;
    }

    friend ostream& operator<<(ostream& out, const PolarnaTacka& tacka) {
        out << "(" << tacka.r << ", " << tacka.theta << " rad)";
        return out;
    }
};

int main() {
    // Testing Poligon with DekartovaTacka
    Poligon<DekartovaTacka, 3> poligonDekart;
    cout << "Unesite koordinate temena poligona (Dekartova Tacka):" << endl;
    cin >> poligonDekart;
    cout << "Poligon sa Dekartovim tackama:" << endl;
    cout << poligonDekart;
    cout << "Obim poligona: " << poligonDekart.obim() << endl;
    --poligonDekart;
    cout << "Poligon nakon preslikavanja u odnosu na x-osu:" << endl;
    cout << poligonDekart;
    poligonDekart--;
    cout << "Poligon nakon preslikavanja u odnosu na y-osu:" << endl;
    cout << poligonDekart;

    // Testing Poligon with PolarnaTacka
    Poligon<PolarnaTacka, 3> poligonPolarna;
    cout << "Unesite koordinate temena poligona (Polarna Tacka):" << endl;
    cin >> poligonPolarna;
    cout << "Poligon sa Polarnim tackama:" << endl;
    cout << poligonPolarna;
    cout << "Obim poligona: " << poligonPolarna.obim() << endl;
    --poligonPolarna;
    cout << "Poligon nakon preslikavanja u odnosu na x-osu:" << endl;
    cout << poligonPolarna;
    poligonPolarna--;
    cout << "Poligon nakon preslikavanja u odnosu na y-osu:" << endl;
    cout << poligonPolarna;

    return 0;
}

//ZADATAK 3
#include <iostream>
#include <vector>
using namespace std;

// Template class Image
template <typename T, int N>
class Image {
private:
    T pixels[N][N]; // Square matrix of pixels

public:
    Image() {}

    void invert() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                pixels[i][j] = !pixels[i][j];
            }
        }
    }

    void read() {
        cout << "Unesite piksele slike:" << endl;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cout << "Piksel (" << i << ", " << j << "): ";
                cin >> pixels[i][j];
            }
        }
    }

    void print() const {
        cout << "Sadrzaj slike:" << endl;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cout << pixels[i][j] << " ";
            }
            cout << endl;
        }
    }
};

// Color class
class Color {
private:
    int R;
    int G;
    int B;

public:
    Color() : R(0), G(0), B(0) {}

    Color(int r, int g, int b) : R(r), G(g), B(b) {}

    Color operator!() const {
        return Color(255 - R, 255 - G, 255 - B);
    }

    Color& operator=(const Color& other) {
        if (this != &other) {
            R = other.R;
            G = other.G;
            B = other.B;
        }
        return *this;
    }

    friend istream& operator>>(istream& in, Color& color) {
        cout << "Unesite R komponentu (0-255): ";
        in >> color.R;
        cout << "Unesite G komponentu (0-255): ";
        in >> color.G;
        cout << "Unesite B komponentu (0-255): ";
        in >> color.B;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Color& color) {
        out << "(" << color.R << ", " << color.G << ", " << color.B << ")";
        return out;
    }
};

int main() {
    // Black and white image test (int values 0 or 1)
    Image<int, 3> crnoBelaSlika;
    cout << "Crno-bela slika:" << endl;
    crnoBelaSlika.read();
    crnoBelaSlika.print();
    crnoBelaSlika.invert();
    cout << "Invertovana crno-bela slika:" << endl;
    crnoBelaSlika.print();

    // Colored image test (Color class)
    Image<Color, 2> slikaUBoji;
    cout << "Slika u boji:" << endl;
    slikaUBoji.read();
    slikaUBoji.print();
    slikaUBoji.invert();
    cout << "Invertovana slika u boji:" << endl;
    slikaUBoji.print();

    return 0;
}

//ZADATAK 4
#include <iostream>
#include <cstring>
using namespace std;

// Templated class for modeling an array of elements
template <typename T>
class Array {
private:
    T* elements;
    int size;

public:
    Array() : size(10) {
        elements = new T[size];
    }

    Array(int n) : size(n) {
        elements = new T[size];
    }

    ~Array() {
        delete[] elements;
    }

    Array(const Array& other) {
        size = other.size;
        elements = new T[size];
        for (int i = 0; i < size; ++i) {
            elements[i] = other.elements[i];
        }
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] elements;
            size = other.size;
            elements = new T[size];
            for (int i = 0; i < size; ++i) {
                elements[i] = other.elements[i];
            }
        }
        return *this;
    }

    T& operator[](int index) {
        return elements[index];
    }

    int GetSize() const {
        return size;
    }

    Array operator+(const Array& other) {
        int newSize = min(size, other.size);
        Array result(newSize);
        for (int i = 0; i < newSize; ++i) {
            result.elements[i] = elements[i] + other.elements[i];
        }
        return result;
    }

    void readElements() {
        for (int i = 0; i < size; ++i) {
            cout << "Element " << i + 1 << ": ";
            cin >> elements[i];
        }
    }

    void printElements() const {
        for (int i = 0; i < size; ++i) {
            cout << "Element " << i + 1 << ": " << elements[i] << endl;
        }
    }
};

// E3Point class
class E3Point {
private:
    double x, y, z;
    char name[50];

public:
    E3Point() : x(0), y(0), z(0) {
        strcpy(name, "");
    }

    E3Point(double x, double y, double z, const char* name) : x(x), y(y), z(z) {
        strcpy(this->name, name);
    }

    ~E3Point() {}

    E3Point operator+(const E3Point& other) const {
        char newName[100];
        strcpy(newName, name);
        strcat(newName, "_");
        strcat(newName, other.name);
        return E3Point(x + other.x, y + other.y, z + other.z, newName);
    }

    E3Point& operator=(const E3Point& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
            strcpy(name, other.name);
        }
        return *this;
    }

    friend istream& operator>>(istream& in, E3Point& point) {
        cout << "Unesite ime tacke: ";
        in >> point.name;
        cout << "Unesite X koordinatu: ";
        in >> point.x;
        cout << "Unesite Y koordinatu: ";
        in >> point.y;
        cout << "Unesite Z koordinatu: ";
        in >> point.z;
        return in;
    }

    friend ostream& operator<<(ostream& out, const E3Point& point) {
        out << "Tacka " << point.name << " (" << point.x << ", " << point.y << ", " << point.z << ")";
        return out;
    }
};

int main() {
    // Testing Array with int type
    Array<int> intArray1(5);
    Array<int> intArray2(5);

    cout << "Unesite elemente prvog celobrojnog niza:" << endl;
    intArray1.readElements();
    cout << "Unesite elemente drugog celobrojnog niza:" << endl;
    intArray2.readElements();

    Array<int> intArraySum = intArray1 + intArray2;
    cout << "Suma celobrojnih nizova:" << endl;
    intArraySum.printElements();

    // Testing Array with E3Point type
    Array<E3Point> pointArray1(3);
    Array<E3Point> pointArray2(3);

    cout << "Unesite elemente prvog niza tacaka:" << endl;
    pointArray1.readElements();
    cout << "Unesite elemente drugog niza tacaka:" << endl;
    pointArray2.readElements();

    Array<E3Point> pointArraySum = pointArray1 + pointArray2;
    cout << "Suma nizova tacaka:" << endl;
    pointArraySum.printElements();

    return 0;
}

//ZADATAK 5
#include <iostream>
#include <iomanip>
using namespace std;

// Templated class for modeling a matrix
template <typename T>
class Matrix {
private:
    T** elements;
    int rows;
    int cols;

public:
    Matrix() : rows(12), cols(12) {
        elements = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            elements[i] = new T[cols]();
        }
    }

    Matrix(int r, int c) : rows(r), cols(c) {
        elements = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            elements[i] = new T[cols]();
        }
    }

    ~Matrix() {
        for (int i = 0; i < rows; ++i) {
            delete[] elements[i];
        }
        delete[] elements;
    }

    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        elements = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            elements[i] = new T[cols];
            for (int j = 0; j < cols; ++j) {
                elements[i][j] = other.elements[i][j];
            }
        }
    }

    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            for (int i = 0; i < rows; ++i) {
                delete[] elements[i];
            }
            delete[] elements;

            rows = other.rows;
            cols = other.cols;
            elements = new T*[rows];
            for (int i = 0; i < rows; ++i) {
                elements[i] = new T[cols];
                for (int j = 0; j < cols; ++j) {
                    elements[i][j] = other.elements[i][j];
                }
            }
        }
        return *this;
    }

    T GetElement(int x, int y) const {
        return elements[x][y];
    }

    void SetElement(int x, int y, T newValue) {
        elements[x][y] = newValue;
    }

    int GetRows() const {
        return rows;
    }

    int GetCols() const {
        return cols;
    }

    Matrix operator*(const Matrix& other) {
        if (cols != other.rows) {
            throw invalid_argument("Matrix dimensions do not match for multiplication.");
        }

        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                for (int k = 0; k < cols; ++k) {
                    result.elements[i][j] = result.elements[i][j] + (elements[i][k] * other.elements[k][j]);
                }
            }
        }
        return result;
    }

    void ReadElements() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << "Element (" << i + 1 << ", " << j + 1 << "): ";
                cin >> elements[i][j];
            }
        }
    }

    void PrintElements() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << elements[i][j] << " ";
            }
            cout << endl;
        }
    }
};

// Complex class
class Complex {
private:
    double real;
    double imag;

public:
    Complex() : real(0), imag(0) {}

    Complex(double r, double i) : real(r), imag(i) {}

    ~Complex() {}

    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
    }

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex& operator=(const Complex& other) {
        if (this != &other) {
            real = other.real;
            imag = other.imag;
        }
        return *this;
    }

    friend istream& operator>>(istream& in, Complex& c) {
        cout << "Unesite realni deo: ";
        in >> c.real;
        cout << "Unesite imaginarni deo: ";
        in >> c.imag;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Complex& c) {
        out << c.real << " + j" << c.imag;
        return out;
    }
};

int main() {
    // Testing Matrix with int type
    Matrix<int> intMatrix1(2, 2);
    Matrix<int> intMatrix2(2, 2);

    cout << "Unesite elemente prve celobrojne matrice:" << endl;
    intMatrix1.ReadElements();
    cout << "Unesite elemente druge celobrojne matrice:" << endl;
    intMatrix2.ReadElements();

    try {
        Matrix<int> intMatrixProduct = intMatrix1 * intMatrix2;
        cout << "Proizvod celobrojnih matrica:" << endl;
        intMatrixProduct.PrintElements();
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    // Testing Matrix with Complex type
    Matrix<Complex> complexMatrix1(2, 2);
    Matrix<Complex> complexMatrix2(2, 2);

    cout << "Unesite elemente prve matrice kompleksnih brojeva:" << endl;
    complexMatrix1.ReadElements();
    cout << "Unesite elemente druge matrice kompleksnih brojeva:" << endl;
    complexMatrix2.ReadElements();

    try {
        Matrix<Complex> complexMatrixProduct = complexMatrix1 * complexMatrix2;
        cout << "Proizvod matrica kompleksnih brojeva:" << endl;
        complexMatrixProduct.PrintElements();
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}

//ZADATAK 6
#include <iostream>
#include <cmath>
using namespace std;

// Templated class for modeling a polynomial
template <typename T, int Degree>
class Polynom {
private:
    T coefficients[Degree + 1];

public:
    Polynom() {
        for (int i = 0; i <= Degree; ++i) {
            coefficients[i] = T();
        }
    }

    void readCoefficients() {
        cout << "Unesite koeficijente polinoma (od konstantnog clana do najviseg stepena):" << endl;
        for (int i = 0; i <= Degree; ++i) {
            cout << "Koeficijent uz x^" << i << ": ";
            cin >> coefficients[i];
        }
    }

    T evaluate(T x) const {
        T result = T();
        for (int i = 0; i <= Degree; ++i) {
            result = result + coefficients[i] * pow(x, i);
        }
        return result;
    }
};

// Complex class
class Complex {
private:
    double real;
    double imag;

public:
    Complex() : real(0), imag(0) {}

    Complex(double r, double i) : real(r), imag(i) {}

    ~Complex() {}

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
    }

    Complex& operator=(const Complex& other) {
        if (this != &other) {
            real = other.real;
            imag = other.imag;
        }
        return *this;
    }

    friend istream& operator>>(istream& in, Complex& c) {
        cout << "Unesite realni deo: ";
        in >> c.real;
        cout << "Unesite imaginarni deo: ";
        in >> c.imag;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Complex& c) {
        out << c.real << " + j" << c.imag;
        return out;
    }
};

int main() {
    // Testing Polynom with double type
    Polynom<double, 5> realPolynom;
    realPolynom.readCoefficients();
    double x = 2.0;
    cout << "Vrednost realnog polinoma za x = " << x << " je: " << realPolynom.evaluate(x) << endl;

    // Testing Polynom with Complex type
    Polynom<Complex, 5> complexPolynom;
    complexPolynom.readCoefficients();
    Complex cx(2.0, 0.0);
    cout << "Vrednost kompleksnog polinoma za x = " << cx << " je: " << complexPolynom.evaluate(cx) << endl;

    return 0;
}

//ZADATAK 7
#include <iostream>
#include <string>
using namespace std;

// Template class for Buffer
template <typename T, int MaxSize>
class Buffer {
private:
    T items[MaxSize];
    int currentSize;

public:
    Buffer() : currentSize(0) {}

    void add(const T& item) {
        if (currentSize < MaxSize) {
            items[currentSize++] = item;
        } else {
            cout << "Buffer je pun!" << endl;
        }
    }

    T getItem(int index) const {
        if (index >= 0 && index < currentSize) {
            return items[index];
        } else {
            throw out_of_range("Indeks je van opsega!");
        }
    }

    T getFirst() const {
        if (currentSize > 0) {
            return items[0];
        } else {
            throw out_of_range("Buffer je prazan!");
        }
    }

    T getLast() const {
        if (currentSize > 0) {
            return items[currentSize - 1];
        } else {
            throw out_of_range("Buffer je prazan!");
        }
    }
};

// Class Student
class Student {
private:
    string ime;
    string prezime;
    int brojIndeksa;
    double prosecnaOcena;

public:
    Student() : ime(""), prezime(""), brojIndeksa(0), prosecnaOcena(0.0) {}

    Student(const Student& other) : ime(other.ime), prezime(other.prezime), brojIndeksa(other.brojIndeksa), prosecnaOcena(other.prosecnaOcena) {}

    Student& operator=(const Student& other) {
        if (this != &other) {
            ime = other.ime;
            prezime = other.prezime;
            brojIndeksa = other.brojIndeksa;
            prosecnaOcena = other.prosecnaOcena;
        }
        return *this;
    }

    friend istream& operator>>(istream& in, Student& s) {
        cout << "Unesite ime: ";
        in >> s.ime;
        cout << "Unesite prezime: ";
        in >> s.prezime;
        cout << "Unesite broj indeksa: ";
        in >> s.brojIndeksa;
        cout << "Unesite prosecnu ocenu: ";
        in >> s.prosecnaOcena;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Student& s) {
        out << "Ime: " << s.ime << ", Prezime: " << s.prezime << ", Broj indeksa: " << s.brojIndeksa << ", Prosecna ocena: " << s.prosecnaOcena;
        return out;
    }
};

int main() {
    // Buffer for characters
    Buffer<char, 10> charBuffer;
    charBuffer.add('A');
    charBuffer.add('B');
    charBuffer.add('C');
    cout << "Prvi element u charBuffer: " << charBuffer.getFirst() << endl;
    cout << "Zadnji element u charBuffer: " << charBuffer.getLast() << endl;

    // Buffer for students
    Buffer<Student, 5> studentBuffer;
    Student s1, s2;
    cout << "Unos prvog studenta:" << endl;
    cin >> s1;
    studentBuffer.add(s1);

    cout << "Unos drugog studenta:" << endl;
    cin >> s2;
    studentBuffer.add(s2);

    cout << "Prvi student u bufferu:" << endl;
    cout << studentBuffer.getFirst() << endl;

    cout << "Zadnji student u bufferu:" << endl;
    cout << studentBuffer.getLast() << endl;

    return 0;
}

//ZADATAK 8
#include <iostream>
#include <string>
using namespace std;

// Template class for Cursor
template <typename T, int MaxSize>
class Cursor {
private:
    T items[MaxSize];
    int currentSize;
    int current;

public:
    Cursor() : currentSize(0), current(0) {}

    void add(const T& item) {
        if (currentSize < MaxSize) {
            items[currentSize++] = item;
        } else {
            cout << "Cursor je pun!" << endl;
        }
    }

    T getCurrent() const {
        if (currentSize > 0) {
            return items[current];
        } else {
            throw out_of_range("Cursor je prazan!");
        }
    }

    Cursor& operator--() {
        if (current > 0) {
            --current;
        }
        return *this;
    }

    Cursor& operator++() {
        if (current < currentSize - 1) {
            ++current;
        }
        return *this;
    }

    Cursor& operator-(int n) {
        if (current >= n) {
            current -= n;
        } else {
            current = 0;
        }
        return *this;
    }

    Cursor& operator+(int n) {
        if (current + n < currentSize) {
            current += n;
        } else {
            current = currentSize - 1;
        }
        return *this;
    }
};

// Class Pravougaonik
class Pravougaonik {
private:
    double duzina;
    double sirina;

public:
    Pravougaonik() : duzina(0), sirina(0) {}

    Pravougaonik(double d, double s) : duzina(d), sirina(s) {}

    friend istream& operator>>(istream& in, Pravougaonik& p) {
        cout << "Unesite duzinu: ";
        in >> p.duzina;
        cout << "Unesite sirinu: ";
        in >> p.sirina;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Pravougaonik& p) {
        out << "Pravougaonik (duzina: " << p.duzina << ", sirina: " << p.sirina << ")";
        return out;
    }
};

int main() {
    // Cursor for characters
    Cursor<char, 20> charCursor;
    charCursor.add('A');
    charCursor.add('B');
    charCursor.add('C');
    cout << "Trenutni element u charCursor: " << charCursor.getCurrent() << endl;
    ++charCursor;
    cout << "Nakon pomeranja udesno, trenutni element u charCursor: " << charCursor.getCurrent() << endl;
    --charCursor;
    cout << "Nakon pomeranja ulevo, trenutni element u charCursor: " << charCursor.getCurrent() << endl;

    // Cursor for rectangles
    Cursor<Pravougaonik, 20> pravougaonikCursor;
    Pravougaonik p1, p2;
    cout << "Unos prvog pravougaonika:" << endl;
    cin >> p1;
    pravougaonikCursor.add(p1);

    cout << "Unos drugog pravougaonika:" << endl;
    cin >> p2;
    pravougaonikCursor.add(p2);

    cout << "Trenutni pravougaonik u cursoru:" << endl;
    cout << pravougaonikCursor.getCurrent() << endl;

    ++pravougaonikCursor;
    cout << "Nakon pomeranja udesno, trenutni pravougaonik u cursoru:" << endl;
    cout << pravougaonikCursor.getCurrent() << endl;

    return 0;
}

//ZADATAK 9
#include <iostream>
#include <string>
using namespace std;

// Template class for Bioskop
template <typename T, int Rows, int Cols>
class Bioskop {
private:
    T seats[Rows][Cols];

public:
    Bioskop() {
        for (int i = 0; i < Rows; ++i) {
            for (int j = 0; j < Cols; ++j) {
                seats[i][j] = T();
            }
        }
    }

    T& operator()(int row, int col) {
        return seats[row][col];
    }

    double averageAge() const {
        double totalAge = 0;
        int count = 0;
        for (int i = 0; i < Rows; ++i) {
            for (int j = 0; j < Cols; ++j) {
                if (seats[i][j].isPresent()) {
                    totalAge += seats[i][j].getAge();
                    ++count;
                }
            }
        }
        return (count > 0) ? (totalAge / count) : 0;
    }

    double averageRating() const {
        double totalRating = 0;
        int count = 0;
        for (int i = 0; i < Rows; ++i) {
            for (int j = 0; j < Cols; ++j) {
                if (seats[i][j].isPresent()) {
                    totalRating += seats[i][j].getRating();
                    ++count;
                }
            }
        }
        return (count > 0) ? (totalRating / count) : 0;
    }
};

// Class Gledalac
class Gledalac {
private:
    string imePrezime;
    int starost;
    int ocenaFilma;
    bool prisutan;

public:
    Gledalac() : imePrezime(""), starost(0), ocenaFilma(0), prisutan(false) {}

    Gledalac(string imePrezime, int starost, int ocenaFilma, bool prisutan)
        : imePrezime(imePrezime), starost(starost), ocenaFilma(ocenaFilma), prisutan(prisutan) {}

    bool isPresent() const {
        return prisutan;
    }

    int getAge() const {
        return starost;
    }

    int getRating() const {
        return ocenaFilma;
    }

    friend istream& operator>>(istream& in, Gledalac& g) {
        cout << "Da li je gledalac prisutan? (1 za da, 0 za ne): ";
        in >> g.prisutan;
        if (g.prisutan) {
            cout << "Unesite ime i prezime: ";
            in.ignore();
            getline(in, g.imePrezime);
            cout << "Unesite starost: ";
            in >> g.starost;
            cout << "Unesite ocenu filma: ";
            in >> g.ocenaFilma;
        }
        return in;
    }

    friend ostream& operator<<(ostream& out, const Gledalac& g) {
        if (g.prisutan) {
            out << "Ime i prezime: " << g.imePrezime << ", Starost: " << g.starost << ", Ocena filma: " << g.ocenaFilma;
        } else {
            out << "Mesto je prazno.";
        }
        return out;
    }
};

int main() {
    const int rows = 5;
    const int cols = 5;
    Bioskop<Gledalac, rows, cols> bioskop;

    // Fill some seats with audience members
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            Gledalac g;
            cout << "Unos podataka za gledaoca na mestu (" << i << ", " << j << "):" << endl;
            cin >> g;
            bioskop(i, j) = g;
        }
    }

    // Display average age and rating
    cout << "Prosecna starost gledalaca: " << bioskop.averageAge() << endl;
    cout << "Prosecna ocena filma: " << bioskop.averageRating() << endl;

    return 0;
}
