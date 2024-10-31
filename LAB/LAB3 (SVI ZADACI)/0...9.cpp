// Zadatak 0: Klasa Funkcija i main
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class Funkcija {
protected:
    double k;
    double n;
    char* naziv;

public:
    Funkcija() : k(1), n(0) {
        naziv = new char[strlen("Linearna funkcija") + 1];
        strcpy(naziv, "Linearna funkcija");
    }

    Funkcija(double k, double n, const char* naziv) : k(k), n(n) {
        this->naziv = new char[strlen(naziv) + 1];
        strcpy(this->naziv, naziv);
    }

    virtual ~Funkcija() {
        delete[] naziv;
    }

    virtual double vrednost(double x) const {
        return k * x + n;
    }

    virtual void prikaziFunkciju() const {
        cout << "Funkcija: " << naziv << ", k: " << k << ", n: " << n << endl;
    }
};

class KvadratnaFunkcija : public Funkcija {
public:
    KvadratnaFunkcija() : Funkcija() {
        delete[] naziv;
        naziv = new char[strlen("Kvadratna funkcija") + 1];
        strcpy(naziv, "Kvadratna funkcija");
    }

    KvadratnaFunkcija(double k, double n) : Funkcija(k, n, "Kvadratna funkcija") {}

    double vrednost(double x) const override {
        return pow(x + n, k);
    }

    void prikaziFunkciju() const override {
        cout << "Kvadratna funkcija: k = " << k << ", n = " << n << endl;
    }
};

class EksponencijalnaFunkcija : public Funkcija {
public:
    EksponencijalnaFunkcija() : Funkcija() {
        delete[] naziv;
        naziv = new char[strlen("Eksponencijalna funkcija") + 1];
        strcpy(naziv, "Eksponencijalna funkcija");
    }

    EksponencijalnaFunkcija(double k, double n) : Funkcija(k, n, "Eksponencijalna funkcija") {}

    double vrednost(double x) const override {
        return k * exp(x) + n;
    }

    void prikaziFunkciju() const override {
        cout << "Eksponencijalna funkcija: k = " << k << ", n = " << n << endl;
    }
};

int main() {
    const int SIZE = 2019;
    Funkcija* niz[SIZE];

    for (int i = 0; i < SIZE; ++i) {
        if (i < 673)
            niz[i] = new Funkcija();
        else if (i < 1346)
            niz[i] = new KvadratnaFunkcija(2, 3);
        else
            niz[i] = new EksponencijalnaFunkcija(1, 2);
    }

    for (int i = 0; i < SIZE; ++i) {
        niz[i]->prikaziFunkciju();
    }

    double minVrednost = niz[0]->vrednost(5);
    Funkcija* minFunkcija = niz[0];
    for (int i = 1; i < SIZE; ++i) {
        double vred = niz[i]->vrednost(5);
        if (vred < minVrednost) {
            minVrednost = vred;
            minFunkcija = niz[i];
        }
    }

    cout << "Funkcija sa minimalnom vrednoscu: ";
    minFunkcija->prikaziFunkciju();

    for (int i = 0; i < SIZE; ++i) {
        delete niz[i];
    }

    return 0;
}

// Zadatak 1: Klasa Figura i main
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

class Figura {
protected:
    int brojStranica;
    double* stranice;

public:
    Figura() : brojStranica(0), stranice(nullptr) {}

    Figura(int broj, double* duzine) : brojStranica(broj) {
        stranice = new double[brojStranica];
        for (int i = 0; i < brojStranica; ++i) {
            stranice[i] = duzine[i];
        }
    }

    virtual ~Figura() {
        delete[] stranice;
    }

    virtual double povrsina() const = 0;

    virtual void prikazi() const {
        cout << "Broj stranica: " << brojStranica << ", Stranice: ";
        for (int i = 0; i < brojStranica; ++i) {
            cout << stranice[i] << " ";
        }
        cout << endl;
    }
};

class Kvadrat : public Figura {
public:
    Kvadrat(double a) : Figura(4, new double[4]{a, a, a, a}) {}

    double povrsina() const override {
        return stranice[0] * stranice[0];
    }

    void prikazi() const override {
        cout << "Kvadrat: stranica = " << stranice[0] << ", povrsina = " << povrsina() << endl;
    }
};

class Pravougaonik : public Figura {
public:
    Pravougaonik(double a, double b) : Figura(4, new double[4]{a, b, a, b}) {}

    double povrsina() const override {
        return stranice[0] * stranice[1];
    }

    void prikazi() const override {
        cout << "Pravougaonik: stranice = " << stranice[0] << " i " << stranice[1] << ", povrsina = " << povrsina() << endl;
    }
};

int main() {
    const int SIZE = 2018;
    Figura* niz[SIZE];

    for (int i = 0; i < SIZE; ++i) {
        if (i < 1009)
            niz[i] = new Kvadrat(5);
        else
            niz[i] = new Pravougaonik(4, 6);
    }

    for (int i = 0; i < SIZE; ++i) {
        niz[i]->prikazi();
    }

    // Sortiranje po povrsini (bubble sort)
    for (int i = 0; i < SIZE - 1; ++i) {
        for (int j = 0; j < SIZE - i - 1; ++j) {
            if (niz[j]->povrsina() > niz[j + 1]->povrsina()) {
                swap(niz[j], niz[j + 1]);
            }
        }
    }

    cout << "Sortiran niz po povrsini: " << endl;
    for (int i = 0; i < SIZE; ++i) {
        niz[i]->prikazi();
    }

    // Upisivanje u fajl
    ofstream outFile("figura_sort.txt");
    for (int i = 0; i < SIZE; ++i) {
        outFile << "Povrsina: " << niz[i]->povrsina() << endl;
    }
    outFile.close();

    for (int i = 0; i < SIZE; ++i) {
        delete niz[i];
    }

    return 0;
}


// Zadatak 2: Klasa Point i main
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

class Point {
protected:
    double x;
    double y;

public:
    Point() : x(0), y(0) {}

    Point(double x, double y) : x(x), y(y) {}

    virtual ~Point() {}

    double rastojanje(const Point& other) const {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }

    virtual void printData() const {
        cout << "Point: (" << x << ", " << y << ")" << endl;
    }
};

class PointCity : public Point {
private:
    char* nazivGrada;
    char* nazivDrzave;
    int brojStanovnika;

    int parsePopulation(const string& input) {
        string cleanedInput;
        for (char c : input) {
            if (isdigit(c)) {
                cleanedInput += c;
            }
        }
        return stoi(cleanedInput);
    }

public:
    PointCity() : Point(), nazivGrada(nullptr), nazivDrzave(nullptr), brojStanovnika(0) {}

    PointCity(double x, double y, const char* grad, const char* drzava, const string& brojStanovnikaStr)
        : Point(x, y) {
        nazivGrada = new char[strlen(grad) + 1];
        strcpy(nazivGrada, grad);
        nazivDrzave = new char[strlen(drzava) + 1];
        strcpy(nazivDrzave, drzava);
        brojStanovnika = parsePopulation(brojStanovnikaStr);
    }

    ~PointCity() {
        delete[] nazivGrada;
        delete[] nazivDrzave;
    }

    void printData() const override {
        cout << "City: " << nazivGrada << ", Country: " << nazivDrzave << ", Population: " << brojStanovnika << endl;
    }

    int getBrojStanovnika() const {
        return brojStanovnika;
    }
};

int main() {
    vector<PointCity> gradovi;
    ifstream inputFile("LV3Zad3.txt");
    if (!inputFile) {
        cerr << "Greska pri otvaranju fajla!" << endl;
        return 1;
    }

    string nazivGrada, nazivDrzave, brojStanovnika;
    while (getline(inputFile, nazivGrada, '\t') && getline(inputFile, nazivDrzave, '\t') && getline(inputFile, brojStanovnika)) {
        gradovi.emplace_back(0, 0, nazivGrada.c_str(), nazivDrzave.c_str(), brojStanovnika);
    }
    inputFile.close();

    sort(gradovi.begin(), gradovi.end(), [](const PointCity& a, const PointCity& b) {
        return a.getBrojStanovnika() < b.getBrojStanovnika();
    });

    ofstream outputFile("sorted_cities.txt");
    if (!outputFile) {
        cerr << "Greska pri otvaranju fajla za upis!" << endl;
        return 1;
    }

    for (const auto& grad : gradovi) {
        outputFile << grad.getBrojStanovnika() << "\t" << grad.nazivGrada << "\t" << grad.nazivDrzave << endl;
    }
    outputFile.close();

    for (const auto& grad : gradovi) {
        grad.printData();
    }

    return 0;
}

// Zadatak 3: Klasa Buffer i main
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

class Buffer {
protected:
    int kapacitet;
    int brojElemenata;
    int* bafer;

public:
    Buffer(int kapacitet) : kapacitet(kapacitet), brojElemenata(0) {
        bafer = new int[kapacitet];
    }

    virtual ~Buffer() {
        delete[] bafer;
    }

    virtual void push(int vrednost) {
        if (brojElemenata < kapacitet) {
            bafer[brojElemenata++] = vrednost;
        } else {
            cout << "Buffer je pun!" << endl;
        }
    }

    virtual void pop() {
        if (brojElemenata > 0) {
            for (int i = 1; i < brojElemenata; ++i) {
                bafer[i - 1] = bafer[i];
            }
            brojElemenata--;
        } else {
            cout << "Buffer je prazan!" << endl;
        }
    }

    virtual void clear() {
        brojElemenata = 0;
    }

    virtual void show() const {
        cout << "Buffer sadrzaj: ";
        for (int i = 0; i < brojElemenata; ++i) {
            cout << bafer[i] << " ";
        }
        cout << endl;
    }
};

class QueueBuffer : public Buffer {
public:
    QueueBuffer(int kapacitet) : Buffer(kapacitet) {}

    void pop() override {
        if (brojElemenata > 1) {
            brojElemenata--;
        } else if (brojElemenata == 1) {
            brojElemenata = 0;
        } else {
            cout << "Buffer je prazan!" << endl;
        }
    }
};

class OrderedBuffer : public Buffer {
public:
    OrderedBuffer(int kapacitet) : Buffer(kapacitet) {}

    void push(int vrednost) override {
        if (brojElemenata < kapacitet) {
            bafer[brojElemenata++] = vrednost;
            sort(bafer, bafer + brojElemenata);
        } else {
            cout << "Buffer je pun!" << endl;
        }
    }

    void clear() override {
        fill(bafer, bafer + brojElemenata, 0);
    }

    void pop() override {
        if (brojElemenata > 0) {
            int sredina = brojElemenata / 2;
            for (int i = sredina + 1; i < brojElemenata; ++i) {
                bafer[i - 1] = bafer[i];
            }
            brojElemenata--;
        } else {
            cout << "Buffer je prazan!" << endl;
        }
    }
};

int main() {
    srand(time(0));
    Buffer* buffers[3];
    buffers[0] = new Buffer(10);
    buffers[1] = new QueueBuffer(10);
    buffers[2] = new OrderedBuffer(10);

    for (int i = 0; i < 2018; ++i) {
        for (int j = 0; j < 3; ++j) {
            buffers[j]->push(rand() % 100);
            buffers[j]->push(rand() % 100);
            buffers[j]->push(rand() % 100);
            buffers[j]->pop();
            buffers[j]->pop();

            if (i % 50 == 0) {
                buffers[j]->clear();
            }

            if (i % 100 == 0) {
                cout << "Sadrzaj bafera " << j + 1 << " nakon " << i << " ciklusa: " << endl;
                buffers[j]->show();
            }
        }
    }

    for (int i = 0; i < 3; ++i) {
        delete buffers[i];
    }

    return 0;
}

// Zadatak 4: Klasa Command i izvedene klase
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class Command {
protected:
    string title;
    char* value;

public:
    Command(const string& title, const char* value) : title(title) {
        this->value = new char[strlen(value) + 1];
        strcpy(this->value, value);
    }

    virtual ~Command() {
        delete[] value;
    }

    virtual void execute() const {
        cout << "Executing command: " << title << endl;
    }
};

class CommandDraw : public Command {
public:
    CommandDraw(const char* value) : Command("Draw", value) {}

    void execute() const override {
        cout << "Executing Draw command with value: " << value << endl;
    }
};

class CommandSave : public Command {
public:
    CommandSave(const char* value) : Command("Save", value) {}

    void execute() const override {
        cout << "Executing Save command with value: " << value << endl;
    }
};

class CommandPrint : public Command {
public:
    CommandPrint(const char* value) : Command("Print", value) {}

    void execute() const override {
        cout << "Executing Print command with value: " << value << endl;
    }
};

class CommandHistory {
private:
    vector<Command*> commands;
    int maxCommands;

public:
    CommandHistory(int maxCommands) : maxCommands(maxCommands) {}

    ~CommandHistory() {
        for (auto command : commands) {
            delete command;
        }
    }

    void undo() {
        if (!commands.empty()) {
            delete commands.back();
            commands.pop_back();
        } else {
            cout << "No commands to undo!" << endl;
        }
    }

    void create(int x) {
        if (commands.size() >= maxCommands) {
            delete commands.front();
            commands.erase(commands.begin());
        }

        switch (x % 3) {
            case 0:
                commands.push_back(new CommandDraw("Drawing something"));
                break;
            case 1:
                commands.push_back(new CommandSave("Saving something"));
                break;
            case 2:
                commands.push_back(new CommandPrint("Printing something"));
                break;
        }
    }

    void execute() const {
        if (!commands.empty()) {
            commands.back()->execute();
        } else {
            cout << "No commands to execute!" << endl;
        }
    }

    void executeAll() const {
        for (const auto& command : commands) {
            command->execute();
        }
    }

    void clear() {
        while (!commands.empty()) {
            undo();
        }
    }
};

int main() {
    CommandHistory history(2019);

    for (int i = 0; i < 2019; ++i) {
        history.create(i);
    }

    cout << "Executing all commands:" << endl;
    history.executeAll();

    cout << "Clearing command history..." << endl;
    history.clear();

    return 0;
}


// Zadatak 5: Klasa Broj, RacionalanBroj, KompleksanBroj, i main
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Broj {
protected:
    char* vrsta;
    double vrednost;

    virtual void postaviVrednost(double vred) {
        vrednost = vred;
    }

public:
    Broj(const char* vrsta, double vred) : vrednost(vred) {
        this->vrsta = new char[strlen(vrsta) + 1];
        strcpy(this->vrsta, vrsta);
    }

    virtual ~Broj() {
        delete[] vrsta;
    }

    bool operator>(const Broj& other) const {
        return vrednost > other.vrednost;
    }

    virtual void Print() const {
        cout << "Vrsta: " << vrsta << ", Vrednost: " << vrednost << endl;
    }

    virtual double getVrednost() const {
        return vrednost;
    }
};

class RacionalanBroj : public Broj {
private:
    int a;
    int b;

public:
    RacionalanBroj(int a, int b) : Broj("Racionalan", static_cast<double>(a) / b), a(a), b(b) {}

    void Print() const override {
        cout << "Vrsta: " << vrsta << ", Vrednost: " << a << "/" << b << " = " << vrednost << endl;
    }
};

class KompleksanBroj : public Broj {
private:
    double real;
    double imaginarni;

public:
    KompleksanBroj(double real, double imaginarni) : Broj("Kompleksan", sqrt(real * real + imaginarni * imaginarni)), real(real), imaginarni(imaginarni) {}

    void Print() const override {
        cout << "Vrsta: " << vrsta << ", Vrednost: " << real << " + j" << imaginarni << " (modul: " << vrednost << ")" << endl;
    }
};

int main() {
    const int SIZE = 2018;
    Broj* niz[SIZE];

    srand(time(0));

    for (int i = 0; i < 1009; ++i) {
        int a = rand() % 100 + 1;
        int b = rand() % 100 + 1;
        niz[i] = new RacionalanBroj(a, b);
    }

    for (int i = 1009; i < SIZE; ++i) {
        double real = rand() % 100 + 1;
        double imaginarni = rand() % 100 + 1;
        niz[i] = new KompleksanBroj(real, imaginarni);
    }

    sort(niz, niz + SIZE, [](Broj* a, Broj* b) {
        return a->getVrednost() > b->getVrednost();
    });

    ofstream outFile("sorted_broj.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < SIZE; ++i) {
            outFile << "Vrsta: " << typeid(*niz[i]).name() << ", Vrednost: " << niz[i]->getVrednost() << endl;
            niz[i]->Print();
        }
        outFile.close();
    } else {
        cout << "Nije moguce otvoriti fajl za pisanje!" << endl;
    }

    for (int i = 0; i < SIZE; ++i) {
        delete niz[i];
    }

    return 0;
}

// Zadatak 6: Klasa Window, DialogWindow, DocumentWindow, i main
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

class Window {
protected:
    char* title;
    bool state; // true = otvoren, false = zatvoren

public:
    Window(const char* title) : state(false) {
        this->title = new char[strlen(title) + 1];
        strcpy(this->title, title);
    }

    virtual ~Window() {
        delete[] title;
    }

    void open() {
        state = true;
    }

    void close() {
        state = false;
    }

    virtual void draw() const {
        cout << "Window: " << title << ", State: " << (state ? "Open" : "Closed") << endl;
    }

    const char* getTitle() const {
        return title;
    }
};

class DialogWindow : public Window {
public:
    DialogWindow(const char* title) : Window(title) {}

    void draw() const override {
        cout << "DialogWindow nacrtan: " << title << ", State: " << (state ? "Open" : "Closed") << endl;
    }

    int confirm() {
        close();
        return 1;
    }

    int cancel() {
        close();
        return 0;
    }
};

class DocumentWindow : public Window {
public:
    DocumentWindow(const char* title) : Window(title) {}

    void draw() const override {
        cout << "DocumentWindow nacrtan: " << title << ", State: " << (state ? "Open" : "Closed") << endl;
    }
};

int main() {
    const int SIZE = 2018;
    Window* windows[SIZE];

    for (int i = 0; i < 1009; ++i) {
        windows[i] = new DialogWindow("DialogWindow");
    }

    for (int i = 1009; i < SIZE; ++i) {
        windows[i] = new DocumentWindow("DocumentWindow");
    }

    for (int i = 0; i < SIZE; ++i) {
        windows[i]->open();
        windows[i]->draw();
    }

    sort(windows, windows + SIZE, [](Window* a, Window* b) {
        return strcmp(a->getTitle(), b->getTitle()) < 0;
    });

    ofstream outFile("sorted_windows.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < SIZE; ++i) {
            outFile << "Window: " << windows[i]->getTitle() << ", State: " << (windows[i]->getTitle() ? "Open" : "Closed") << endl;
        }
        outFile.close();
    } else {
        cout << "Nije moguce otvoriti fajl za pisanje!" << endl;
    }

    for (int i = 0; i < SIZE; ++i) {
        delete windows[i];
    }

    return 0;
}

// Zadatak 7: Klasa Artikal, Laptop, Torba, i main
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

class Artikal {
protected:
    char* naziv;
    double cena;

public:
    Artikal(const char* naziv, double cena) : cena(cena) {
        this->naziv = new char[strlen(naziv) + 1];
        strcpy(this->naziv, naziv);
    }

    virtual ~Artikal() {
        delete[] naziv;
    }

    virtual void showDescription() const {
        cout << "Naziv: " << naziv << ", Cena: " << cena << endl;
    }

    double getPrice() const {
        return cena;
    }
};

class Laptop : public Artikal {
private:
    char* opis;
    bool stanje; // true = uključen, false = isključen

public:
    Laptop(const char* naziv, double cena, const char* opis) : Artikal(naziv, cena), stanje(false) {
        this->opis = new char[strlen(opis) + 1];
        strcpy(this->opis, opis);
    }

    ~Laptop() {
        delete[] opis;
    }

    void showDescription() const override {
        cout << "Naziv: " << naziv << ", Cena: " << cena << ", Opis: " << opis << endl;
    }

    void turnOn() {
        stanje = true;
        cout << "Laptop " << naziv << " je uključen." << endl;
    }

    void turnOff() {
        stanje = false;
        cout << "Laptop " << naziv << " je isključen." << endl;
    }
};

class Torba : public Artikal {
private:
    Artikal* sadrzaj;

public:
    Torba(const char* naziv, double cena) : Artikal(naziv, cena), sadrzaj(nullptr) {}

    void showDescription() const override {
        cout << "Torba za Laptop računar" << endl;
        if (sadrzaj != nullptr) {
            sadrzaj->showDescription();
        }
    }

    void put(Artikal& a) {
        if (sadrzaj == nullptr) {
            sadrzaj = &a;
            cout << "Artikal " << a.getPrice() << " smešten u torbu." << endl;
        } else {
            cout << "Torba je već puna!" << endl;
        }
    }

    void remove() {
        if (sadrzaj != nullptr) {
            sadrzaj = nullptr;
            cout << "Artikal izvađen iz torbe." << endl;
        } else {
            cout << "Torba je već prazna!" << endl;
        }
    }
};

int main() {
    const int SIZE = 2018;
    Artikal* artikli[SIZE];

    for (int i = 0; i < 1009; ++i) {
        artikli[i] = new Laptop("Laptop", rand() % 1000 + 500, "High performance laptop");
    }

    for (int i = 1009; i < SIZE; ++i) {
        artikli[i] = new Torba("Torba", rand() % 100 + 50);
    }

    for (int i = 0; i < SIZE; ++i) {
        artikli[i]->showDescription();
    }

    sort(artikli, artikli + SIZE, [](Artikal* a, Artikal* b) {
        return a->getPrice() < b->getPrice();
    });

    ofstream outFile("sorted_artikli.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < SIZE; ++i) {
            outFile << "Naziv: " << typeid(*artikli[i]).name() << ", Cena: " << artikli[i]->getPrice() << endl;
        }
        outFile.close();
    } else {
        cout << "Nije moguce otvoriti fajl za pisanje!" << endl;
    }

    for (int i = 0; i < SIZE; ++i) {
        delete artikli[i];
    }

    return 0;
}

// Zadatak 8: Klasa GeometrijskaSlika, Krug, Kvadrat, i main
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

class GeometrijskaSlika {
private:
    int R, G, B;
    double tezisteX, tezisteY;

protected:
    virtual double povrsina() const = 0;

public:
    GeometrijskaSlika(int R, int G, int B, double x, double y) : R(R), G(G), B(B), tezisteX(x), tezisteY(y) {}

    double rastojanjeOdPocetka() const {
        return sqrt(pow(tezisteX, 2) + pow(tezisteY, 2));
    }

    void transliraj(double dx, double dy) {
        tezisteX += dx;
        tezisteY += dy;
    }

    virtual void Show() const {
        cout << "Boja (R, G, B): (" << R << ", " << G << ", " << B << ")";
        cout << ", Teziste: (" << tezisteX << ", " << tezisteY << ")" << endl;
    }

    bool vecaOd(const GeometrijskaSlika& druga) const {
        return povrsina() > druga.povrsina();
    }

    virtual ~GeometrijskaSlika() {}
};

class Krug : public GeometrijskaSlika {
private:
    double poluprecnik;

protected:
    double povrsina() const override {
        return M_PI * poluprecnik * poluprecnik;
    }

public:
    Krug(int R, int G, int B, double x, double y, double poluprecnik)
        : GeometrijskaSlika(R, G, B, x, y), poluprecnik(poluprecnik) {}

    void Show() const override {
        cout << "Krug - ";
        GeometrijskaSlika::Show();
        cout << "Poluprecnik: " << poluprecnik << ", Povrsina: " << povrsina() << endl;
    }
};

class Kvadrat : public GeometrijskaSlika {
private:
    double stranica;

protected:
    double povrsina() const override {
        return stranica * stranica;
    }

public:
    Kvadrat(int R, int G, int B, double x, double y, double stranica)
        : GeometrijskaSlika(R, G, B, x, y), stranica(stranica) {}

    void Show() const override {
        cout << "Kvadrat - ";
        GeometrijskaSlika::Show();
        cout << "Stranica: " << stranica << ", Povrsina: " << povrsina() << endl;
    }
};

int main() {
    srand(time(0));
    const int SIZE = 2018;
    vector<GeometrijskaSlika*> slike;

    for (int i = 0; i < SIZE / 2; ++i) {
        slike.push_back(new Krug(rand() % 256, rand() % 256, rand() % 256, rand() % 256, rand() % 256, rand() % 256));
    }

    for (int i = SIZE / 2; i < SIZE; ++i) {
        slike.push_back(new Kvadrat(rand() % 256, rand() % 256, rand() % 256, rand() % 256, rand() % 256, rand() % 256));
    }

    for (auto& slika : slike) {
        double dx = (rand() % 256 - 128) / 10.0;
        double dy = (rand() % 256 - 128) / 10.0;
        slika->transliraj(dx, dy);
    }

    sort(slike.begin(), slike.end(), [](GeometrijskaSlika* a, GeometrijskaSlika* b) {
        return a->povrsina() < b->povrsina();
    });

    ofstream outFile("sorted_slike.txt");
    if (outFile.is_open()) {
        for (const auto& slika : slike) {
            slika->Show();
            outFile << "Povrsina: " << slika->povrsina() << ", Rastojanje od pocetka: " << slika->rastojanjeOdPocetka() << endl;
        }
        outFile.close();
    } else {
        cout << "Nije moguce otvoriti fajl za pisanje!" << endl;
    }

    for (auto& slika : slike) {
        delete slika;
    }

    return 0;
}

// Zadatak 9: Klasa Displej, DekadniMatricniDisplej, i main
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

class Displej {
protected:
    int cifra;

public:
    Displej() : cifra(0) {}

    virtual void set(int vrednost) {
        if (vrednost >= 0 && vrednost < 16) {
            cifra = vrednost;
        } else {
            cout << "Nevalidna vrednost!" << endl;
        }
    }

    void reset() {
        cifra = 0;
    }

    virtual void increment() {
        cifra = (cifra + 1) % 16;
    }

    virtual void show() const {
        cout << "Cifra: " << hex << cifra << endl;
    }
};

class DekadniMatricniDisplej : public Displej {
private:
    int matrica[5][3];

public:
    DekadniMatricniDisplej() {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 3; ++j) {
                matrica[i][j] = 0;
            }
        }
    }

    void set(int vrednost) override {
        if (vrednost >= 0 && vrednost < 10) {
            cifra = vrednost;
        } else {
            cout << "Nevalidna vrednost!" << endl;
        }
    }

    void increment() override {
        cifra = (cifra + 1) % 10;
    }

    void loadMatrixFromFile(const string& filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 3; ++j) {
                    inFile >> matrica[i][j];
                }
            }
            inFile.close();
        } else {
            cout << "Nije moguce otvoriti fajl za citanje!" << endl;
        }
    }

    void show() const override {
        Displej::show();
        cout << "Matrica piksela:" << endl;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << matrica[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Displej d;
    DekadniMatricniDisplej dmd;

    d.set(9);
    dmd.set(9);

    const int k = 50001;
    for (int i = 0; i < k; ++i) {
        d.increment();
        dmd.increment();
        if (i % 2018 == 0) {
            cout << "Displej nakon " << i << " inkrementiranja:" << endl;
            d.show();
            cout << "Dekadni Matricni Displej nakon " << i << " inkrementiranja:" << endl;
            dmd.show();
        }
    }

    d.reset();
    dmd.reset();

    for (int i = 0; i < k; ++i) {
        d.increment();
        dmd.increment();
        if (i % 2018 == 0) {
            cout << "Displej nakon " << i << " inkrementiranja (nakon reseta):" << endl;
            d.show();
            cout << "Dekadni Matricni Displej nakon " << i << " inkrementiranja (nakon reseta):" << endl;
            dmd.show();
        }
    }

    cout << "Krajnje stanje Displeja:" << endl;
    d.show();
    cout << "Krajnje stanje Dekadnog Matricnog Displeja:" << endl;
    dmd.show();

    return 0;
}

