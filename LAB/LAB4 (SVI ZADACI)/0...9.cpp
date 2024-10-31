//ZADATAK 0
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

class Element {
protected:
    int sifra;
    int sifraMaterijala;
    float kolicina;

public:
    Element(int sifra, int sifraMaterijala, float kolicina)
        : sifra(sifra), sifraMaterijala(sifraMaterijala), kolicina(kolicina) {}

    virtual ~Element() {}

    int getSifraMaterijala() const { return sifraMaterijala; }

    float getKolicina() const { return kolicina; }

    virtual void prikazi() const = 0;

    bool operator<(const Element& other) const { return sifra < other.sifra; }
};

class Paket : public Element {
private:
    char lot[20];
    char* tip;

public:
    Paket(int sifra, int sifraMaterijala, float kolicina, const char* lot, const char* tip)
        : Element(sifra, sifraMaterijala, kolicina) {
        strcpy(this->lot, lot);
        this->tip = new char[strlen(tip) + 1];
        strcpy(this->tip, tip);
    }

    ~Paket() { delete[] tip; }

    void prikazi() const override {
        cout << "Paket - Sifra: " << sifra << ", Sifra materijala: " << sifraMaterijala
             << ", Kolicina: " << kolicina << ", Lot: " << lot << ", Tip: " << tip << endl;
    }

    friend istream& operator>>(istream& is, Paket& p) {
        char tempTip[50];
        cout << "Unesite sifru, sifru materijala, kolicinu, lot i tip: ";
        is >> p.sifra >> p.sifraMaterijala >> p.kolicina >> p.lot >> tempTip;
        if (isalpha(tempTip[0])) {
            p.tip = new char[strlen(tempTip) + 1];
            strcpy(p.tip, tempTip);
        } else {
            cout << "Tip mora poceti slovom!" << endl;
        }
        return is;
    }
};

class Silos : public Element {
private:
    char lot[20];
    float maxKolicina;

public:
    Silos(int sifra, int sifraMaterijala, float kolicina, const char* lot, float maxKolicina)
        : Element(sifra, sifraMaterijala, kolicina), maxKolicina(maxKolicina) {
        strcpy(this->lot, lot);
        if (kolicina > maxKolicina) {
            this->kolicina = maxKolicina;
        }
    }

    void prikazi() const override {
        cout << "Silos - Sifra: " << sifra << ", Sifra materijala: " << sifraMaterijala
             << ", Kolicina: " << kolicina << ", Lot: " << lot << endl;
    }

    friend istream& operator>>(istream& is, Silos& s) {
        cout << "Unesite sifru, sifru materijala, kolicinu, lot i max kolicinu: ";
        is >> s.sifra >> s.sifraMaterijala >> s.kolicina >> s.lot >> s.maxKolicina;
        if (s.kolicina > s.maxKolicina) {
            s.kolicina = s.maxKolicina;
            cout << "Kolicina ne moze biti veca od maksimalne kolicine!" << endl;
        }
        return is;
    }
};

class Skladiste {
private:
    double maxKapacitet;
    int brojElemenata;
    vector<Element*> elementi;

public:
    Skladiste(double maxKapacitet) : maxKapacitet(maxKapacitet), brojElemenata(0) {}

    ~Skladiste() {
        for (auto& e : elementi) {
            delete e;
        }
    }

    bool dodajElement(Element* e) {
        if (ukupnaKolicina() + e->getKolicina() <= maxKapacitet) {
            elementi.push_back(e);
            brojElemenata++;
            return true;
        }
        cout << "Nema dovoljno mesta u skladistu!" << endl;
        return false;
    }

    double ukupnaKolicina() const {
        double ukupno = 0;
        for (const auto& e : elementi) {
            ukupno += e->getKolicina();
        }
        return ukupno;
    }

    void prikaziSifreMaterijala() const {
        set<int> sifre;
        for (const auto& e : elementi) {
            sifre.insert(e->getSifraMaterijala());
        }
        for (int sifra : sifre) {
            cout << "Sifra materijala: " << sifra << endl;
        }
    }

    friend ostream& operator<<(ostream& os, const Skladiste& s) {
        vector<Element*> sortirano = s.elementi;
        sort(sortirano.begin(), sortirano.end(), [](Element* a, Element* b) { return a->getSifraMaterijala() < b->getSifraMaterijala(); });
        for (const auto& e : sortirano) {
            e->prikazi();
        }
        return os;
    }
};

int main() {
    Skladiste skladiste(50000);
    ifstream inFile("elementi.txt");
    if (!inFile) {
        cout << "Greska prilikom otvaranja fajla!" << endl;
        return 1;
    }

    for (int i = 0; i < 1009; ++i) {
        int sifra, sifraMaterijala;
        float kolicina;
        char lot[20];
        char tip[50];
        inFile >> sifra >> sifraMaterijala >> kolicina >> lot >> tip;
        skladiste.dodajElement(new Paket(sifra, sifraMaterijala, kolicina, lot, tip));
    }

    for (int i = 0; i < 1009; ++i) {
        int sifra, sifraMaterijala;
        float kolicina, maxKolicina;
        char lot[20];
        inFile >> sifra >> sifraMaterijala >> kolicina >> lot >> maxKolicina;
        skladiste.dodajElement(new Silos(sifra, sifraMaterijala, kolicina, lot, maxKolicina));
    }

    inFile.close();

    cout << "Ukupna kolicina materijala u skladistu: " << skladiste.ukupnaKolicina() << " kg" << endl;

    ofstream outFile("sifre_materijala.txt");
    if (outFile.is_open()) {
        set<int> sifre;
        for (const auto& e : skladiste.elementi) {
            sifre.insert(e->getSifraMaterijala());
        }
        for (int sifra : sifre) {
            outFile << sifra << endl;
        }
        outFile.close();
    } else {
        cout << "Nije moguce otvoriti fajl za pisanje!" << endl;
    }

    cout << "Jedinstvena lista svih paketa i silosa uredjenih po lotu:" << endl;
    cout << skladiste;

    return 0;
}

//ZADATAK 1
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

class Element {
protected:
    int tip;

public:
    Element(int tip) : tip(tip) {}
    virtual ~Element() {}

    int getTip() const { return tip; }
    virtual int getSpecVrednost() const = 0;
    virtual void prikazi() const = 0;
};

class Zemlja : public Element {
private:
    int nadmorskaVisina;

public:
    Zemlja(int nadmorskaVisina) : Element(1), nadmorskaVisina(nadmorskaVisina) {}

    int getSpecVrednost() const override { return nadmorskaVisina; }

    void prikazi() const override {
        cout << "Zemlja - Tip: " << tip << ", Nadmorska visina: " << nadmorskaVisina << endl;
    }

    friend istream& operator>>(istream& is, Zemlja& z) {
        cout << "Unesite nadmorsku visinu: ";
        is >> z.nadmorskaVisina;
        return is;
    }
};

class Voda : public Element {
private:
    float dubina;

public:
    Voda(float dubina) : Element(2), dubina(dubina) {}

    int getSpecVrednost() const override { return 0; } // Nadmorska visina vode je 0

    void prikazi() const override {
        cout << "Voda - Tip: " << tip << ", Dubina: " << dubina << endl;
    }

    friend istream& operator>>(istream& is, Voda& v) {
        cout << "Unesite dubinu: ";
        is >> v.dubina;
        return is;
    }
};

class Put {
private:
    int velicinaNiza;
    vector<Element*> elementi;

public:
    Put(int velicinaNiza) : velicinaNiza(velicinaNiza) {
        elementi.resize(velicinaNiza, nullptr);
    }

    ~Put() {
        for (auto& e : elementi) {
            delete e;
        }
    }

    void postaviElement(int indeks, Element* e) {
        if (indeks >= 0 && indeks < velicinaNiza) {
            elementi[indeks] = e;
        } else {
            cout << "Nevalidan indeks!" << endl;
        }
    }

    void prikaziBrojElemenataPoTipu() const {
        int brojZemlja = 0;
        int brojVoda = 0;
        for (const auto& e : elementi) {
            if (e != nullptr) {
                if (e->getTip() == 1) {
                    brojZemlja++;
                } else if (e->getTip() == 2) {
                    brojVoda++;
                }
            }
        }
        cout << "Broj elemenata tipa Zemlja: " << brojZemlja << endl;
        cout << "Broj elemenata tipa Voda: " << brojVoda << endl;
    }

    friend ostream& operator<<(ostream& os, const Put& p) {
        for (const auto& e : p.elementi) {
            if (e != nullptr) {
                e->prikazi();
            }
        }
        return os;
    }
};

int main() {
    Put put(2018);

    ifstream inFile("put_elementi.txt");
    if (!inFile) {
        cout << "Greska prilikom otvaranja fajla!" << endl;
        return 1;
    }

    for (int i = 0; i < 1009; ++i) {
        int nadmorskaVisina;
        inFile >> nadmorskaVisina;
        put.postaviElement(i, new Zemlja(nadmorskaVisina));
    }

    for (int i = 1009; i < 2018; ++i) {
        float dubina;
        inFile >> dubina;
        put.postaviElement(i, new Voda(dubina));
    }

    inFile.close();

    cout << "Sadrzaj puta:" << endl;
    cout << put;

    put.prikaziBrojElemenataPoTipu();

    // Racunanje prosečne nadmorske visine
    int ukupnaVisina = 0;
    int brojZemlja = 0;
    for (int i = 0; i < 1009; ++i) {
        if (put.elementi[i] != nullptr && put.elementi[i]->getTip() == 1) {
            ukupnaVisina += put.elementi[i]->getSpecVrednost();
            brojZemlja++;
        }
    }
    double prosecnaVisina = (brojZemlja > 0) ? static_cast<double>(ukupnaVisina) / brojZemlja : 0;
    cout << "Prosecna nadmorska visina na putu: " << prosecnaVisina << " m" << endl;

    return 0;
}

//ZADATAK 2
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

class Operacija {
protected:
    char* naziv;
    int drugiOperand;
    Operacija* suprotnaOperacija;

public:
    Operacija(const char* naziv, int drugiOperand, Operacija* suprotnaOperacija)
        : drugiOperand(drugiOperand), suprotnaOperacija(suprotnaOperacija) {
        this->naziv = new char[strlen(naziv) + 1];
        strcpy(this->naziv, naziv);
    }

    virtual ~Operacija() {
        delete[] naziv;
    }

    Operacija* getSuprotnaOperacija() const {
        return suprotnaOperacija;
    }

    int getDrugiOperand() const {
        return drugiOperand;
    }

    virtual void prikazi() const {
        cout << "Operacija: " << naziv << ", Drugi operand: " << drugiOperand;
        if (suprotnaOperacija) {
            cout << ", Suprotna operacija: " << suprotnaOperacija->naziv;
        }
        cout << endl;
    }

    virtual int DoOperation(int op1, int op2) const = 0;
};

class Sabiranje : public Operacija {
public:
    Sabiranje(int drugiOperand) : Operacija("Sabiranje", drugiOperand, nullptr) {}

    int DoOperation(int op1, int op2) const override {
        return op1 + op2;
    }
};

class Oduzimanje : public Operacija {
public:
    Oduzimanje(int drugiOperand) : Operacija("Oduzimanje", drugiOperand, nullptr) {}

    int DoOperation(int op1, int op2) const override {
        return op1 - op2;
    }
};

class Mnozenje : public Operacija {
public:
    Mnozenje(int drugiOperand) : Operacija("Mnozenje", drugiOperand, nullptr) {}

    int DoOperation(int op1, int op2) const override {
        return op1 * op2;
    }
};

class Deljenje : public Operacija {
public:
    Deljenje(int drugiOperand) : Operacija("Deljenje", drugiOperand, nullptr) {}

    int DoOperation(int op1, int op2) const override {
        if (op2 != 0) {
            return op1 / op2;
        } else {
            cout << "Deljenje sa nulom!" << endl;
            return 0;
        }
    }
};

class Kalkulator {
private:
    int akumulator;
    char* naziv;
    vector<Operacija*> stek;
    int maxOperacija;

public:
    Kalkulator(const char* naziv, int maxOperacija) : akumulator(0), maxOperacija(maxOperacija) {
        this->naziv = new char[strlen(naziv) + 1];
        strcpy(this->naziv, naziv);
    }

    ~Kalkulator() {
        delete[] naziv;
        for (auto& op : stek) {
            delete op;
        }
    }

    void reset() {
        akumulator = 0;
        for (auto& op : stek) {
            delete op;
        }
        stek.clear();
    }

    void prikaziAkumulator() const {
        cout << "Akumulator: " << akumulator << endl;
    }

    void Do(Operacija& novaOperacija) {
        if (stek.size() < maxOperacija) {
            int op2 = novaOperacija.getDrugiOperand();
            akumulator = novaOperacija.DoOperation(akumulator, op2);
            stek.push_back(&novaOperacija);
            prikaziAkumulator();
        } else {
            cout << "Stek operacija je pun!" << endl;
        }
    }

    void Undo() {
        if (!stek.empty()) {
            Operacija* zadnjaOperacija = stek.back();
            stek.pop_back();
            if (zadnjaOperacija->getSuprotnaOperacija()) {
                int op2 = zadnjaOperacija->getDrugiOperand();
                akumulator = zadnjaOperacija->getSuprotnaOperacija()->DoOperation(akumulator, op2);
                prikaziAkumulator();
            }
        } else {
            cout << "Nema operacija za poništavanje!" << endl;
        }
    }
};

int main() {
    Kalkulator kalkulator("Moj Kalkulator", 2020);

    ifstream inFile("operacije.txt");
    if (!inFile) {
        cout << "Greska prilikom otvaranja fajla!" << endl;
        return 1;
    }

    for (int i = 0; i < 505; ++i) {
        int operand;
        inFile >> operand;
        Sabiranje* sabiranje = new Sabiranje(operand);
        kalkulator.Do(*sabiranje);
    }

    for (int i = 0; i < 505; ++i) {
        int operand;
        inFile >> operand;
        Oduzimanje* oduzimanje = new Oduzimanje(operand);
        kalkulator.Do(*oduzimanje);
    }

    for (int i = 0; i < 505; ++i) {
        int operand;
        inFile >> operand;
        Mnozenje* mnozenje = new Mnozenje(operand);
        kalkulator.Do(*mnozenje);
    }

    for (int i = 0; i < 505; ++i) {
        int operand;
        inFile >> operand;
        Deljenje* deljenje = new Deljenje(operand);
        kalkulator.Do(*deljenje);
    }

    kalkulator.Undo();
    kalkulator.Undo();

    inFile.close();

    return 0;
}

//ZADATAK 3
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

class Process {
protected:
    int sifra;
    int stanje; // 0 - kreiran, 1 - startovan, 2 - zaustavljen
    int tip;

public:
    Process(int sifra, int tip) : sifra(sifra), tip(tip), stanje(0) {}

    int getSifra() const {
        return sifra;
    }

    int getStanje() const {
        return stanje;
    }

    virtual void prikazi() const {
        cout << "Sifra: " << sifra << ", Stanje: " << stanje << ", Tip: " << tip << endl;
    }

    virtual void Start(char* parameter) = 0;
    virtual void Stop() = 0;
};

class PublicProcess : public Process {
private:
    char* creatorName;

public:
    PublicProcess(int sifra, const char* creatorName) : Process(sifra, 0) {
        this->creatorName = new char[strlen(creatorName) + 1];
        strcpy(this->creatorName, creatorName);
    }

    ~PublicProcess() {
        delete[] creatorName;
    }

    void Start(char* userName) override {
        if (strcmp(creatorName, userName) != 0) {
            delete[] creatorName;
            creatorName = new char[strlen(userName) + 1];
            strcpy(creatorName, userName);
        }
        stanje = 1;
    }

    void Stop() override {
        if (stanje == 1) {
            stanje = 2;
        }
    }

    void prikazi() const override {
        Process::prikazi();
        cout << "Kreator: " << creatorName << endl;
    }
};

class PrivateProcess : public Process {
private:
    char* code;

public:
    PrivateProcess(int sifra, const char* code) : Process(sifra, 1) {
        this->code = new char[strlen(code) + 1];
        strcpy(this->code, code);
    }

    ~PrivateProcess() {
        delete[] code;
    }

    void Start(char* userCode) override {
        if (strcmp(code, userCode) == 0) {
            stanje = 1;
        } else {
            cout << "Pogresan kod!" << endl;
        }
    }

    void Stop() override {
        if (stanje == 1) {
            stanje = 2;
        }
    }

    void prikazi() const override {
        Process::prikazi();
        cout << "Kod: " << code << endl;
    }
};

class ProcessQueue {
private:
    int maxElements;
    vector<Process*> aktivniProcesi;
    vector<Process*> cekajuciProcesi;

public:
    ProcessQueue(int maxElements) : maxElements(maxElements) {}

    ~ProcessQueue() {
        for (auto& proces : aktivniProcesi) {
            delete proces;
        }
        for (auto& proces : cekajuciProcesi) {
            delete proces;
        }
    }

    void dodajProces(Process* proces, bool aktivan) {
        if (aktivan) {
            if (aktivniProcesi.size() < maxElements) {
                aktivniProcesi.push_back(proces);
            } else {
                cout << "Nema mesta u aktivnim procesima!" << endl;
            }
        } else {
            if (cekajuciProcesi.size() < maxElements) {
                cekajuciProcesi.push_back(proces);
            } else {
                cout << "Nema mesta u cekajucim procesima!" << endl;
            }
        }
    }

    void izbaciProceseStanje2() {
        auto it = remove_if(aktivniProcesi.begin(), aktivniProcesi.end(), [](Process* p) {
            return p->getStanje() == 2;
        });
        aktivniProcesi.erase(it, aktivniProcesi.end());

        it = remove_if(cekajuciProcesi.begin(), cekajuciProcesi.end(), [](Process* p) {
            return p->getStanje() == 2;
        });
        cekajuciProcesi.erase(it, cekajuciProcesi.end());
    }

    void startujSveProcese() {
        for (auto& proces : aktivniProcesi) {
            if (proces->getStanje() == 0) {
                char param[] = "start";
                proces->Start(param);
            }
        }
        for (auto& proces : cekajuciProcesi) {
            if (proces->getStanje() == 0) {
                char param[] = "start";
                proces->Start(param);
            }
        }
    }

    void zaustaviSveProcese() {
        for (auto& proces : aktivniProcesi) {
            if (proces->getStanje() == 1) {
                proces->Stop();
            }
        }
        for (auto& proces : cekajuciProcesi) {
            if (proces->getStanje() == 1) {
                proces->Stop();
            }
        }
    }

    ProcessQueue operator+(const ProcessQueue& other) {
        ProcessQueue novaQueue(maxElements + other.maxElements);
        novaQueue.aktivniProcesi = aktivniProcesi;
        novaQueue.aktivniProcesi.insert(novaQueue.aktivniProcesi.end(), other.aktivniProcesi.begin(), other.aktivniProcesi.end());
        novaQueue.cekajuciProcesi = cekajuciProcesi;
        novaQueue.cekajuciProcesi.insert(novaQueue.cekajuciProcesi.end(), other.cekajuciProcesi.begin(), other.cekajuciProcesi.end());
        return novaQueue;
    }

    void prikaziSveProcese() const {
        cout << "Aktivni procesi:" << endl;
        for (const auto& proces : aktivniProcesi) {
            proces->prikazi();
        }
        cout << "Cekajuci procesi:" << endl;
        for (const auto& proces : cekajuciProcesi) {
            proces->prikazi();
        }
    }
};

int main() {
    ProcessQueue queue(10);

    PublicProcess* p1 = new PublicProcess(1, "user1");
    PrivateProcess* p2 = new PrivateProcess(2, "code123");
    PublicProcess* p3 = new PublicProcess(3, "user2");
    PrivateProcess* p4 = new PrivateProcess(4, "code456");

    queue.dodajProces(p1, true);
    queue.dodajProces(p2, false);
    queue.dodajProces(p3, true);
    queue.dodajProces(p4, false);

    queue.prikaziSveProcese();

    queue.startujSveProcese();
    queue.prikaziSveProcese();

    queue.zaustaviSveProcese();
    queue.prikaziSveProcese();

    queue.izbaciProceseStanje2();
    queue.prikaziSveProcese();

    return 0;
}

//ZADATAK 4
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

class SegmentPuta {
protected:
    string naziv;
    double koeficijentTezine;
    double koeficijentLepote;

public:
    SegmentPuta(string naziv) : naziv(naziv), koeficijentTezine(0), koeficijentLepote(0) {}
    virtual ~SegmentPuta() {}

    virtual void izracunajKoeficijente() = 0;

    double getKoeficijentTezine() const {
        return koeficijentTezine;
    }

    double getKoeficijentLepote() const {
        return koeficijentLepote;
    }

    virtual void prikazi() const {
        cout << "Naziv: " << naziv << ", Koeficijent tezine: " << koeficijentTezine << ", Koeficijent lepote: " << koeficijentLepote << endl;
    }
};

class More : public SegmentPuta {
private:
    double povrsina;
    double stepenPlavetnila;
    int maxSnagaVetra;

public:
    More(string naziv, double povrsina, double stepenPlavetnila, int maxSnagaVetra)
        : SegmentPuta(naziv), povrsina(povrsina), stepenPlavetnila(stepenPlavetnila), maxSnagaVetra(maxSnagaVetra) {}

    void izracunajKoeficijente() override {
        koeficijentLepote = (maxSnagaVetra * stepenPlavetnila) / povrsina;
        koeficijentTezine = (maxSnagaVetra * povrsina) / (koeficijentLepote - 1);
    }

    void prikazi() const override {
        SegmentPuta::prikazi();
        cout << "Povrsina: " << povrsina << ", Stepen plavetnila: " << stepenPlavetnila << ", Max snaga vetra: " << maxSnagaVetra << endl;
    }
};

class Gora : public SegmentPuta {
private:
    double povrsina;
    double duzinaPuta;
    double relRazlikaVisine;
    double stepenInverznePosumljenosti;

public:
    Gora(string naziv, double povrsina, double duzinaPuta, double relRazlikaVisine, double stepenInverznePosumljenosti)
        : SegmentPuta(naziv), povrsina(povrsina), duzinaPuta(duzinaPuta), relRazlikaVisine(relRazlikaVisine), stepenInverznePosumljenosti(stepenInverznePosumljenosti) {}

    void izracunajKoeficijente() override {
        koeficijentTezine = (stepenInverznePosumljenosti * duzinaPuta) / (duzinaPuta + povrsina + relRazlikaVisine + duzinaPuta / povrsina);
        koeficijentLepote = (1 - stepenInverznePosumljenosti) * relRazlikaVisine;
    }

    void prikazi() const override {
        SegmentPuta::prikazi();
        cout << "Povrsina: " << povrsina << ", Duzina puta: " << duzinaPuta << ", Relativna razlika visine: " << relRazlikaVisine << ", Stepen inverzne posumljenosti: " << stepenInverznePosumljenosti << endl;
    }
};

class Mocvara : public SegmentPuta {
private:
    double povrsina;
    double stepenZitkosti;

public:
    Mocvara(string naziv, double povrsina, double stepenZitkosti)
        : SegmentPuta(naziv), povrsina(povrsina), stepenZitkosti(stepenZitkosti) {}

    void izracunajKoeficijente() override {
        koeficijentTezine = (1 - stepenZitkosti) * (1 - 1 / (stepenZitkosti * povrsina));
        koeficijentLepote = 1 - koeficijentTezine;
    }

    void prikazi() const override {
        SegmentPuta::prikazi();
        cout << "Povrsina: " << povrsina << ", Stepen zitkosti: " << stepenZitkosti << endl;
    }
};

int main() {
    vector<SegmentPuta*> put;
    ifstream ulaz("put.txt");
    string tip, naziv;
    double povrsina, stepenPlavetnila, duzinaPuta, relRazlikaVisine, stepenInverznePosumljenosti, stepenZitkosti;
    int maxSnagaVetra;

    while (ulaz >> tip) {
        ulaz >> naziv;
        if (tip == "More") {
            ulaz >> povrsina >> stepenPlavetnila >> maxSnagaVetra;
            put.push_back(new More(naziv, povrsina, stepenPlavetnila, maxSnagaVetra));
        } else if (tip == "Gora") {
            ulaz >> povrsina >> duzinaPuta >> relRazlikaVisine >> stepenInverznePosumljenosti;
            put.push_back(new Gora(naziv, povrsina, duzinaPuta, relRazlikaVisine, stepenInverznePosumljenosti));
        } else if (tip == "Mocvara") {
            ulaz >> povrsina >> stepenZitkosti;
            put.push_back(new Mocvara(naziv, povrsina, stepenZitkosti));
        }
    }

    ulaz.close();

    for (auto& segment : put) {
        segment->izracunajKoeficijente();
    }

    sort(put.begin(), put.end(), [](SegmentPuta* a, SegmentPuta* b) {
        return a->getKoeficijentTezine() < b->getKoeficijentTezine();
    });

    ofstream izlaz("sortirani_tezina.txt");
    for (const auto& segment : put) {
        segment->prikazi();
        izlaz << segment->getKoeficijentTezine() << " " << segment->getKoeficijentLepote() << endl;
    }
    izlaz.close();

    sort(put.begin(), put.end(), [](SegmentPuta* a, SegmentPuta* b) {
        return a->getKoeficijentLepote() < b->getKoeficijentLepote();
    });

    ofstream izlaz2("sortirani_lepota.txt");
    for (const auto& segment : put) {
        segment->prikazi();
        izlaz2 << segment->getKoeficijentTezine() << " " << segment->getKoeficijentLepote() << endl;
    }
    izlaz2.close();

    for (auto& segment : put) {
        delete segment;
    }

    return 0;
}

//ZADATAK 5
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class Step {
protected:
    char* naziv;
    char* tip;

public:
    Step(const char* naziv, const char* tip) {
        this->naziv = new char[strlen(naziv) + 1];
        strcpy(this->naziv, naziv);
        this->tip = new char[strlen(tip) + 1];
        strcpy(this->tip, tip);
    }

    virtual ~Step() {
        delete[] naziv;
        delete[] tip;
    }

    const char* getNaziv() const {
        return naziv;
    }

    virtual int GetSpecAttribute() const = 0;

    virtual void prikazi() const {
        cout << "Naziv: " << naziv << ", Tip: " << tip << ", Specijalni atribut: " << GetSpecAttribute() << endl;
    }
};

class Activity : public Step {
private:
    int obavezna;

public:
    Activity(const char* naziv, int obavezna) : Step(naziv, "Activity"), obavezna(obavezna) {}

    int GetSpecAttribute() const override {
        return obavezna;
    }

    friend istream& operator>>(istream& is, Activity& a) {
        char naziv[50];
        int obavezna;
        is >> naziv >> obavezna;
        a = Activity(naziv, obavezna);
        return is;
    }
};

class State : public Step {
private:
    int prioritet;

public:
    State(const char* naziv, int prioritet) : Step(naziv, "State"), prioritet(prioritet) {}

    int GetSpecAttribute() const override {
        return prioritet;
    }

    friend istream& operator>>(istream& is, State& s) {
        char naziv[50];
        int prioritet;
        is >> naziv >> prioritet;
        s = State(naziv, prioritet);
        return is;
    }
};

class Workflow {
private:
    int duzina;
    Step** koraci;

public:
    Workflow(int duzina) : duzina(duzina) {
        koraci = new Step*[duzina];
        for (int i = 0; i < duzina; ++i) {
            koraci[i] = nullptr;
        }
    }

    ~Workflow() {
        for (int i = 0; i < duzina; ++i) {
            delete koraci[i];
        }
        delete[] koraci;
    }

    Workflow(const Workflow& other) : duzina(other.duzina) {
        koraci = new Step*[duzina];
        for (int i = 0; i < duzina; ++i) {
            if (other.koraci[i]) {
                if (strcmp(other.koraci[i]->getNaziv(), "Activity") == 0) {
                    koraci[i] = new Activity(*dynamic_cast<Activity*>(other.koraci[i]));
                } else {
                    koraci[i] = new State(*dynamic_cast<State*>(other.koraci[i]));
                }
            } else {
                koraci[i] = nullptr;
            }
        }
    }

    void InsertAt(int index, Step* step) {
        if (index >= 0 && index < duzina) {
            delete koraci[index];
            koraci[index] = step;
        }
    }

    void RemoveAt(int index) {
        if (index >= 0 && index < duzina) {
            delete koraci[index];
            koraci[index] = nullptr;
        }
    }

    vector<Step*> GetSpecificSteps(const char* tip) const {
        vector<Step*> result;
        for (int i = 0; i < duzina; ++i) {
            if (koraci[i] && strcmp(koraci[i]->getNaziv(), tip) == 0) {
                result.push_back(koraci[i]);
            }
        }
        return result;
    }

    friend ostream& operator<<(ostream& os, const Workflow& wf) {
        for (int i = 0; i < wf.duzina; ++i) {
            if (wf.koraci[i]) {
                wf.koraci[i]->prikazi();
            }
        }
        return os;
    }
};

int main() {
    Workflow W1(2018);

    for (int i = 0; i < 1009; ++i) {
        W1.InsertAt(i, new Activity("Activity", i % 2));
    }
    for (int i = 1009; i < 2018; ++i) {
        W1.InsertAt(i, new State("State", i % 5));
    }

    cout << "Prikaz Workflow W1:" << endl;
    cout << W1;

    vector<Step*> aktivnosti = W1.GetSpecificSteps("Activity");
    Workflow W3(aktivnosti.size());
    for (size_t i = 0; i < aktivnosti.size(); ++i) {
        W3.InsertAt(i, aktivnosti[i]);
    }

    cout << "Prikaz Workflow W3 (samo aktivnosti):" << endl;
    cout << W3;

    Workflow W4 = W1; // Testiranje konstruktora za kopiranje
    cout << "Prikaz Workflow W4 (kopija W1):" << endl;
    cout << W4;

    Workflow W5(2018);
    W5 = W3; // Testiranje operatora dodele
    cout << "Prikaz Workflow W5 (dodeljen W3):" << endl;
    cout << W5;

    return 0;
}

//ZADATAK 6
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class FileSystemElement {
protected:
    char* ime;
    char* ekstenzija;
    FileSystemElement* roditelj;

public:
    FileSystemElement(const char* ime, const char* ekstenzija) : roditelj(nullptr) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        this->ekstenzija = new char[strlen(ekstenzija) + 1];
        strcpy(this->ekstenzija, ekstenzija);
    }

    virtual ~FileSystemElement() {
        delete[] ime;
        delete[] ekstenzija;
    }

    void setRoditelj(FileSystemElement* r) {
        roditelj = r;
    }

    virtual char* punoKvalifikovanoIme() const = 0;
    virtual void PrintList() const = 0;
};

class Folder : public FileSystemElement {
private:
    FileSystemElement* elementi[2018];
    int brojElemenata;

public:
    Folder(const char* ime) : FileSystemElement(ime, ""), brojElemenata(0) {
        for (int i = 0; i < 2018; ++i) {
            elementi[i] = nullptr;
        }
    }

    ~Folder() {
        for (int i = 0; i < brojElemenata; ++i) {
            delete elementi[i];
        }
    }

    char* punoKvalifikovanoIme() const override {
        string punoIme = ime;
        FileSystemElement* trenutni = roditelj;
        while (trenutni) {
            punoIme = string(trenutni->ime) + "/" + punoIme;
            trenutni = trenutni->roditelj;
        }
        char* rezultat = new char[punoIme.length() + 1];
        strcpy(rezultat, punoIme.c_str());
        return rezultat;
    }

    void PrintList() const override {
        cout << "Folder: " << ime << endl;
        for (int i = 0; i < brojElemenata; ++i) {
            if (elementi[i]) {
                elementi[i]->PrintList();
            }
        }
    }

    void dodajElement(FileSystemElement* element) {
        if (brojElemenata < 2018) {
            elementi[brojElemenata++] = element;
            element->setRoditelj(this);
        }
    }

    void ukloniElement(int indeks) {
        if (indeks >= 0 && indeks < brojElemenata) {
            elementi[indeks]->setRoditelj(nullptr);
            delete elementi[indeks];
            elementi[indeks] = nullptr;
            for (int i = indeks; i < brojElemenata - 1; ++i) {
                elementi[i] = elementi[i + 1];
            }
            elementi[--brojElemenata] = nullptr;
        }
    }
};

class File : public FileSystemElement {
public:
    File(const char* ime, const char* ekstenzija) : FileSystemElement(ime, ekstenzija) {}

    char* punoKvalifikovanoIme() const override {
        string punoIme = ime;
        if (strlen(ekstenzija) > 0) {
            punoIme += ".";
            punoIme += ekstenzija;
        }
        FileSystemElement* trenutni = roditelj;
        while (trenutni) {
            punoIme = string(trenutni->ime) + "/" + punoIme;
            trenutni = trenutni->roditelj;
        }
        char* rezultat = new char[punoIme.length() + 1];
        strcpy(rezultat, punoIme.c_str());
        return rezultat;
    }

    void PrintList() const override {
        if (roditelj) {
            cout << "Fajlovi u istom folderu kao " << ime << ":" << endl;
            for (int i = 0; i < 2018; ++i) {
                Folder* folder = dynamic_cast<Folder*>(roditelj);
                if (folder && folder->elementi[i]) {
                    File* fajl = dynamic_cast<File*>(folder->elementi[i]);
                    if (fajl) {
                        cout << fajl->ime << "." << fajl->ekstenzija << endl;
                    }
                }
            }
        }
    }
};

int main() {
    Folder* root = new Folder("root");
    Folder* folder1 = new Folder("folder1");
    Folder* folder2 = new Folder("folder2");
    File* file1 = new File("file1", "txt");
    File* file2 = new File("file2", "cpp");
    File* file3 = new File("file3", "h");

    root->dodajElement(folder1);
    root->dodajElement(folder2);
    folder1->dodajElement(file1);
    folder1->dodajElement(file2);
    folder2->dodajElement(file3);

    cout << "Prikaz liste foldera root:" << endl;
    root->PrintList();

    cout << "\nPrikaz liste fajlova u folderu folder1:" << endl;
    file1->PrintList();

    delete root;

    return 0;
}

//ZADATAK 7
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

class Radnik {
protected:
    int JMBG;
    char* imePrezime;
    int godinaZaposljenja;
    int godineStarosti;
    double osnovicaPlate;

public:
    Radnik(int jmbg, const char* ime, int godinaZaposljenja, int godineStarosti, double osnovica)
        : JMBG(jmbg), godinaZaposljenja(godinaZaposljenja), godineStarosti(godineStarosti), osnovicaPlate(osnovica) {
        imePrezime = new char[strlen(ime) + 1];
        strcpy(imePrezime, ime);
    }

    virtual ~Radnik() {
        delete[] imePrezime;
    }

    int getJMBG() const { return JMBG; }
    const char* getImePrezime() const { return imePrezime; }
    int getGodinaZaposljenja() const { return godinaZaposljenja; }

    virtual double plata() const = 0;

    Radnik& operator++() {
        osnovicaPlate *= 1.1;
        return *this;
    }

    Radnik& operator--() {
        osnovicaPlate *= 0.9;
        return *this;
    }

    bool operator<(const Radnik& other) const {
        return godineStarosti < other.godineStarosti;
    }

    virtual void prikaziPodatke() const = 0;
};

class Developer : public Radnik {
private:
    char* tip;
    int prekovremeniSati;

public:
    Developer(int jmbg, const char* ime, int godinaZaposljenja, int godineStarosti, double osnovica, const char* tip, int prekovremeni)
        : Radnik(jmbg, ime, godinaZaposljenja, godineStarosti, osnovica), prekovremeniSati(prekovremeni) {
        this->tip = new char[strlen(tip) + 1];
        strcpy(this->tip, tip);
    }

    ~Developer() {
        delete[] tip;
    }

    double plata() const override {
        return 25 * osnovicaPlate + 1500 * godinaZaposljenja + 1000 * prekovremeniSati;
    }

    void prikaziPodatke() const override {
        cout << "Developer: " << imePrezime << ", Plata: " << plata() << endl;
    }
};

class Menager : public Radnik {
private:
    char* tip;

public:
    Menager(int jmbg, const char* ime, int godinaZaposljenja, int godineStarosti, double osnovica, const char* tip)
        : Radnik(jmbg, ime, godinaZaposljenja, godineStarosti, osnovica) {
        this->tip = new char[strlen(tip) + 1];
        strcpy(this->tip, tip);
    }

    ~Menager() {
        delete[] tip;
    }

    double plata() const override {
        return 30 * osnovicaPlate + 1000 * godinaZaposljenja;
    }

    void prikaziPodatke() const override {
        cout << "Menager: " << imePrezime << ", Plata: " << plata() << endl;
    }
};

class Preduzece {
private:
    char* naziv;
    int budzet;
    Radnik** radnici;
    int maxBrojRadnika;
    int brojRadnika;

public:
    Preduzece(const char* naziv, int budzet, int maxBrojRadnika)
        : budzet(budzet), maxBrojRadnika(maxBrojRadnika), brojRadnika(0) {
        this->naziv = new char[strlen(naziv) + 1];
        strcpy(this->naziv, naziv);
        radnici = new Radnik*[maxBrojRadnika];
    }

    ~Preduzece() {
        delete[] naziv;
        for (int i = 0; i < brojRadnika; ++i) {
            delete radnici[i];
        }
        delete[] radnici;
    }

    void dodajRadnika(Radnik* radnik) {
        if (brojRadnika < maxBrojRadnika) {
            radnici[brojRadnika++] = radnik;
        }
    }

    void obrisiRadnika(int jmbg) {
        for (int i = 0; i < brojRadnika; ++i) {
            if (radnici[i]->getJMBG() == jmbg) {
                delete radnici[i];
                for (int j = i; j < brojRadnika - 1; ++j) {
                    radnici[j] = radnici[j + 1];
                }
                brojRadnika--;
                break;
            }
        }
    }

    double ukupnaZarada() const {
        double suma = 0;
        for (int i = 0; i < brojRadnika; ++i) {
            suma += radnici[i]->plata();
        }
        return suma;
    }

    bool rentabilna() const {
        return budzet > ukupnaZarada();
    }

    Preduzece& operator++() {
        for (int i = 0; i < brojRadnika; ++i) {
            ++(*radnici[i]);
        }
        return *this;
    }

    Preduzece& operator--() {
        for (int i = 0; i < brojRadnika; ++i) {
            --(*radnici[i]);
        }
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Preduzece& p) {
        os << "Preduzece: " << p.naziv << ", Budzet: " << p.budzet << endl;
        for (int i = 0; i < p.brojRadnika; ++i) {
            p.radnici[i]->prikaziPodatke();
        }
        return os;
    }
};

int main() {
    Preduzece firma("TechCorp", 10000000, 2018);

    for (int i = 0; i < 1009; ++i) {
        firma.dodajRadnika(new Developer(1000 + i, "Dev", 2015, 30, 50000, "programer", 10));
    }

    for (int i = 0; i < 1009; ++i) {
        firma.dodajRadnika(new Menager(2000 + i, "Menager", 2010, 40, 60000, "finansijski"));
    }

    if (firma.rentabilna()) {
        ++firma;
    } else {
        --firma;
    }

    cout << firma;

    return 0;
}

//ZADATAK 8
#include <iostream>
#include <cstring>
using namespace std;

class Zadatak {
private:
    int kod;
    int stepenTezine;

public:
    Zadatak() : kod(0), stepenTezine(0) {}
    ~Zadatak() {}

    void postavi(int k, int t) {
        kod = k;
        stepenTezine = t;
    }

    int getKod() const { return kod; }
    int getStepenTezine() const { return stepenTezine; }
};

class Heroj {
protected:
    char* ime;
    int vekRodjenja;
    Zadatak* zadaci[17];
    int brojZadataka;

public:
    Heroj(const char* ime, int vek) : vekRodjenja(vek), brojZadataka(0) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        for (int i = 0; i < 17; ++i) {
            zadaci[i] = nullptr;
        }
    }

    virtual ~Heroj() {
        delete[] ime;
        for (int i = 0; i < brojZadataka; ++i) {
            delete zadaci[i];
        }
    }

    Heroj& operator=(const Heroj& other) {
        if (this != &other) {
            delete[] ime;
            ime = new char[strlen(other.ime) + 1];
            strcpy(ime, other.ime);
            vekRodjenja = other.vekRodjenja;
            brojZadataka = other.brojZadataka;
            for (int i = 0; i < brojZadataka; ++i) {
                zadaci[i] = new Zadatak(*other.zadaci[i]);
            }
        }
        return *this;
    }

    Zadatak* operator[](int indeks) const {
        return zadaci[indeks];
    }

    const char* getIme() const { return ime; }
    int getBrojZadataka() const { return brojZadataka; }

    virtual void dodajZadatak(Zadatak* zadatak) = 0;
    virtual void prikazi() const = 0;
};

class MitskiHeroj : public Heroj {
private:
    int brojMitova;
    int minimalnaTezina;

public:
    MitskiHeroj(const char* ime, int vek, int mitovi, int minTezina)
        : Heroj(ime, vek), brojMitova(mitovi), minimalnaTezina(minTezina) {}

    void dodajZadatak(Zadatak* zadatak) override {
        if (brojZadataka < 17 && zadatak->getStepenTezine() >= minimalnaTezina) {
            zadaci[brojZadataka++] = zadatak;
        }
    }

    void prikazi() const override {
        cout << "Mitski heroj: " << ime << ", Vek: " << vekRodjenja << ", Broj mitova: " << brojMitova << ", Zadaci: " << brojZadataka << endl;
    }
};

class BitskiHeroj : public Heroj {
public:
    BitskiHeroj(const char* ime, int vek) : Heroj(ime, vek) {}

    void dodajZadatak(Zadatak* zadatak) override {
        if (brojZadataka < 17 && (zadatak->getStepenTezine() == 0 || zadatak->getStepenTezine() == 1)) {
            zadaci[brojZadataka++] = zadatak;
        }
    }

    void prikazi() const override {
        cout << "Bitski heroj: " << ime << ", Vek: " << vekRodjenja << ", Zadaci: " << brojZadataka << endl;
    }
};

int main() {
    Heroj* heroji[20];
    for (int i = 0; i < 20; ++i) {
        if (i % 2 == 0) {
            heroji[i] = new MitskiHeroj("Mitski Heroj", 1000 + i, 10, 2);
        } else {
            heroji[i] = new BitskiHeroj("Bitski Heroj", 1000 + i);
        }
    }

    Zadatak zadaci[30];
    for (int i = 0; i < 30; ++i) {
        zadaci[i].postavi(i + 1, i % 3);
    }

    for (int i = 0; i < 30; ++i) {
        heroji[i % 20]->dodajZadatak(new Zadatak(zadaci[i]));
    }

    cout << "Heroji sa vise od 3 zadatka:" << endl;
    for (int i = 0; i < 20; ++i) {
        if (heroji[i]->getBrojZadataka() > 3) {
            cout << heroji[i]->getIme() << endl;
        }
    }

    for (int i = 0; i < 20; ++i) {
        delete heroji[i];
    }

    return 0;
}

//ZADATAK 9
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

class Protivnik {
protected:
    string ime;
    double koefBorbenost;
    double koefMagija;

public:
    Protivnik(const string& ime) : ime(ime), koefBorbenost(0), koefMagija(0) {}
    virtual ~Protivnik() {}

    double getBorbenost() const { return koefBorbenost; }
    double getMagija() const { return koefMagija; }

    virtual void izracunajKoeficijente() = 0;
    virtual void prikazi() const = 0;
};

class Azdaja : public Protivnik {
private:
    double sjajnostKrljusti;
    double simetrijaKrila;
    double temperaturaVatre;
    double snagaUdarca;

public:
    Azdaja(const string& ime, double s, double k, double t, double u)
        : Protivnik(ime), sjajnostKrljusti(s), simetrijaKrila(k), temperaturaVatre(t), snagaUdarca(u) {}

    void izracunajKoeficijente() override {
        koefBorbenost = temperaturaVatre * (1 + simetrijaKrila) * snagaUdarca;
        koefMagija = sjajnostKrljusti * simetrijaKrila;
    }

    void prikazi() const override {
        cout << "Azdaja: " << ime << ", B: " << koefBorbenost << ", M: " << koefMagija << endl;
    }
};

class Mantikor : public Protivnik {
private:
    double intenzitetCrvene;
    double simetrijaRogova;
    double efikasnostOtrova;
    double snagaUgriza;

public:
    Mantikor(const string& ime, double i, double k, double o, double u)
        : Protivnik(ime), intenzitetCrvene(i), simetrijaRogova(k), efikasnostOtrova(o), snagaUgriza(u) {}

    void izracunajKoeficijente() override {
        koefBorbenost = 0.5 * (snagaUgriza + efikasnostOtrova) * simetrijaRogova;
        koefMagija = intenzitetCrvene * (simetrijaRogova + efikasnostOtrova + snagaUgriza) / 3;
    }

    void prikazi() const override {
        cout << "Mantikor: " << ime << ", B: " << koefBorbenost << ", M: " << koefMagija << endl;
    }
};

class BeliZec : public Protivnik {
private:
    double intenzitetBele;
    double wakizashiSkill;

public:
    BeliZec(const string& ime, double c, double w)
        : Protivnik(ime), intenzitetBele(c), wakizashiSkill(w) {}

    void izracunajKoeficijente() override {
        koefBorbenost = wakizashiSkill;
        koefMagija = intenzitetBele;
    }

    void prikazi() const override {
        cout << "Beli Zec: " << ime << ", B: " << koefBorbenost << ", M: " << koefMagija << endl;
    }
};

int main() {
    vector<Protivnik*> protivnici;
    for (int i = 0; i < 777; ++i) {
        protivnici.push_back(new Azdaja("Azdaja" + to_string(i), 0.5, 0.6, 0.7, 0.8));
        protivnici.push_back(new Mantikor("Mantikor" + to_string(i), 0.6, 0.5, 0.7, 0.9));
        protivnici.push_back(new BeliZec("Beli Zec" + to_string(i), 0.7, 0.8));
    }

    for (auto& protivnik : protivnici) {
        protivnik->izracunajKoeficijente();
    }

    cout << "Sortirano po borbenosti:" << endl;
    sort(protivnici.begin(), protivnici.end(), [](Protivnik* a, Protivnik* b) {
        return a->getBorbenost() > b->getBorbenost();
    });
    for (const auto& protivnik : protivnici) {
        protivnik->prikazi();
    }

    cout << "\nSortirano po magiji:" << endl;
    sort(protivnici.begin(), protivnici.end(), [](Protivnik* a, Protivnik* b) {
        return a->getMagija() > b->getMagija();
    });
    for (const auto& protivnik : protivnici) {
        protivnik->prikazi();
    }

    for (auto& protivnik : protivnici) {
        delete protivnik;
    }

    return 0;
}
