#include <iostream>
#include <cmath>
#include <vector>

#define M_PI 3.14159265358979323846

using namespace std;

//zdefiniowana klasa 3d
class Punkt_3D {
public:
    //konstruktor klasy Punkt_3D
    Punkt_3D(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Punkt_3D() {
        x = 0;
        y = 0;
        z = 0;
    }
    ~Punkt_3D() {
        cout << "usunieto punkt" << endl;
    }
    //metoda wyswietlajaca wspolrzedne 
    void wyswietl() {
        
        cout <<"X: " << x << endl;
        cout <<"Y: " << y << endl;
        cout <<"Z: " << z << endl;
    }
    //metoda przesuwania punktu wzgledem wybranej osi
    void przesun(int wyb, float przes);
    //metoda rzutujaca dany punkt na podana plaszyczyzne
    void rzut(float ax, float by, float cz, float d);
    //metoda wykonujaca obrot punktu wedlug wybranej osi, o zadany kat
    void obrot(int wyb, double kat);
private:
    float x, y, z;
};

//zdefiniowana klasa Figura_3D
class Figura_3D {
public:
    Figura_3D(int mem) {
        //przypisanie ilosci miejsc wektora do zmiennej klasy - aby moc ja wykorzystywac w metodach
        this->mem = mem;
        if (mem >= 3) {
            //rezerwacja pamieci w wektorze "ilosc miejsc"
            figura.reserve(mem);
            //petla uzupelniajaca nasz wektor obiektami klasy Punkt_3D
            for (int i = 0; i < mem; i++) {
                cout << "Wprowadz wspolrzedne punktu " << i + 1 << " figury:"<<endl;
                float x, y, z;
                cout << "X: ";
                while(!(cin >> x)){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Niepoprawne dane! Sprobuj ponownie.";
                };
                cout << "Y: ";
                while (!(cin >> y)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Niepoprawne dane! Sprobuj ponownie.";
                };
                cout << "Z: ";
                while (!(cin >> z)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Niepoprawne dane! Sprobuj ponownie.";
                };
                figura.push_back(Punkt_3D(x, y, z));
                system("cls");
            }
        }
        else {
            //komunikat w przypadku za malej ilosci punktow i zakonczenie programu z kodem bledu.
            cout << "za malo punktow musisz podac conajmniej 3" << endl;
            exit(2137);
        }
    }
    Figura_3D() {
        //podstawowy konstruktor "bez argumentow", przyjelismy ze punktow wtedy rezerwujemy 3 poniewaz figura musi sie skladac z conajmniej 3 
        this->mem = 3;
        figura.reserve(3);
        for (int i = 0; i < 3; i++) {
            cout << "Wprowadz wspolrzedne punktu " << i + 1 << " figury:" << endl;
            float x, y, z;
            cout << "X: ";
            while (!(cin >> x)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Niepoprawne dane! Sprobuj ponownie.";
            };
            cout << "Y: ";
            while (!(cin >> y)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Niepoprawne dane! Sprobuj ponownie.";
            };
            cout << "Z: ";
            while (!(cin >> z)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Niepoprawne dane! Sprobuj ponownie.";
            };
            figura.push_back(Punkt_3D(x, y, z));
            system("cls");
        }
    }
    ~Figura_3D() {
        cout << "usunięto figure" << endl;
    }

    void wyswietlF();
    void przesunF();
    void obrotF();
    void rzutF();

private:
    //tworzymy wektor, który będzie zbierał punkty (żabsy na monsterki)
    vector <Punkt_3D> figura;
    int mem;
};

//rozwiniecie metody rzutujacej punkt
void Punkt_3D::rzut(float ax, float by, float cz, float d) {
    //zmienne a,b,c aby moc przypisac wyniki do nich i je wyswietlic.
    float t, pom, wsp, a,b,c;
    //obliczamy wspolczynnik t ze wzoru na rzut punktu na plaszyzne
    t = (ax * ax) + (by * by) + (cz * cz);
    pom = (x * ax) + (y * by) + (z * cz) + d;
    wsp = -pom / t;

    a = wsp * ax + x;
    b = wsp * by + y;
    c = wsp * cz + z;

    cout << "Zrzutowane wspolrzedne punktu \nX: " << a << " Y: " << b << " Z: " << c<<endl;

    /* przypisanie wartosci obliczonych z rzutu do wspolrzednych obiektu (bez sensu)
    x = wsp * ax + x;
    y = wsp * by + y;
    z = wsp * cz + z;
    */
}

//rozwiniecie metody obrotu punktu
void Punkt_3D::obrot(int wyb, double kat) {
    float wsp[3][1] = { {x},{y},{z} };
    float pom[3][1];
    float s = 0;
    double rad_kat = kat * (M_PI / 180);

    switch (wyb)
    {
    case 1:
    {
        //macierz obrotu osi x jako tablica dwuwymiarowa
        float obr_os_x[3][3] = { {1,0,0},{0,cos(rad_kat),-sin(rad_kat)},{0,sin(rad_kat),cos(rad_kat)} };

        //petle wykonujące mnożenie macierzy, aby uzyskać nowy obrócony punkt
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                s += (obr_os_x[i][j] * wsp[j][0]);
            }
            pom[i][0] = s;
            s = 0;
        }
        //Zapisanie obliczonych wspolrzednych do naszych zmiennych obiektu
        x = pom[0][0];
        y = pom[1][0];
        z = pom[2][0];
        break;
    }
    case 2:
    {
        //macierz obrotu osi y jako tablica dwuwymiarowa
        float obr_os_y[3][3] = { {cos(rad_kat),0,sin(rad_kat)},{0,1,0},{-sin(rad_kat),0,cos(rad_kat)} };

        //petle wykonujące mnożenie macierzy, aby uzyskać nowy obrócony punkt
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                s += (obr_os_y[i][j] * wsp[j][0]);
            }
            pom[i][0] = s;
            s = 0;
        }
        x = pom[0][0];
        y = pom[1][0];
        z = pom[2][0];
        break;
    }
    case 3:
    {
        //macierz obrotu osi z jako tablica dwuwymiarowa
        float obr_os_z[3][3] = { {cos(rad_kat),-sin(rad_kat),0},{sin(rad_kat),cos(rad_kat),0},{0,0,1} };

        //petle wykonujące mnożenie macierzy, aby uzyskać nowy obrócony punkt
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                s += (obr_os_z[i][j] * wsp[j][0]);
            }
            pom[i][0] = s;
            s = 0;
        }
        x = pom[0][0];
        y = pom[1][0];
        z = pom[2][0];
        break;
    }
    }


}

void Punkt_3D::przesun(int wyb, float przes) {
    //switch ktorym mozna wybrac na jakiej osi chcemy przesuwac punkt
    switch (wyb)
    {
    case 1:
    {
        x += przes;
        break;
    }
    case 2:
    {
        y += przes;
        break;
    }
    case 3:
    {
        z += przes;
        break;
    }
    }
}

//rozwiniecie metody wyswietlajacej Wspolrzedne punktow figury
void Figura_3D::wyswietlF() {
    for (int i = 0; i < mem; i++) {
        //korzystamy tutaj z metody klasy Punkt_3D
        cout << "P[" << i + 1 << "]" << endl;
        figura[i].wyswietl();
    }
}

//rozwiniecie metody przesuwającej punkty figury o wybraną oś i wartość
void Figura_3D::przesunF() {
    int wyb;
    float przesun;
    for (int i = 0; i < mem; i++) {
        cout << "Na ktorej osi chcesz przesunac?\nOs x - wpisz '1'\nOs y - wpisz '2'\nOs z - wpisz '3'\n" << endl;
        while (!(cin >> wyb) || wyb > 3 || wyb < 1) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Niepoprawne dane! Sprobuj ponownie.";
        };
        cout << "O ile chcesz przesunac? " << endl;
        while (!(cin >> przesun)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Niepoprawne dane! Sprobuj ponownie.";
        };
        system("cls");
        //korzystamy z metody przesun klasy Punkt_3D
        figura[i].przesun(wyb, przesun);
    }
}

void Figura_3D::obrotF() {
    int wyb;
    float kat;
    cout << "Wokol ktorej osi chcesz obrocic?\nOs x - wpisz '1'\nOs y - wpisz '2'\nOs z - wpisz '3'\n";
    while (!(cin >> wyb)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Niepoprawne dane! Sprobuj ponownie.";
    };
    cout << "Podaj kat obrotu w stopniach"<<endl;
    while (!(cin >> kat)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Niepoprawne dane! Sprobuj ponownie.";
    };
    system("cls");
    for (int i = 0; i < mem; i++) {
        figura[i].obrot(wyb, kat);
    }
}

void Figura_3D::rzutF() {
    float a, b, c, d;
    cout << "Podaj wspolczynniki swojej plaszczyzny:" << endl;
    cout << "Ax: ";
    while (!(cin >> a)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Niepoprawne dane! Sprobuj ponownie.";
    };
    cout << "By: ";
    while (!(cin >> b)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Niepoprawne dane! Sprobuj ponownie.";
    };
    cout << "Cz: ";
    while (!(cin >> c)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Niepoprawne dane! Sprobuj ponownie.";
    };
    cout << "D: ";
    while (!(cin >> d)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Niepoprawne dane! Sprobuj ponownie.";
    };
    system("cls");
    cout << "Rownanie twojej plaszczyzny wyglada tak:" << endl;
    cout << a << "x+ " << b << "y+ " << c << "z+ " << d<<endl;
    for (int i = 0; i < mem; i++) {
        cout << "P[" << i + 1 << "]" << endl;
        figura[i].rzut(a, b, c, d);
    }
}


int main(int argc, const char* argv[]) {
    char zakoncz, zakoncz2;
    int wyb;
    int ilosc;
    cout << "---------:::  Program Figury Trojwymiarowe :::---------" << endl << "Witaj! Najpierw stworz figure. Co najmniej z 3 punktow!" << endl;
    do {
        cout << "Podaj ilosc punktow: ";

        //walidacja wprowadzania danych
        while (!(cin >> ilosc)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "Podaj prawidlowe dane! Prawidlowy typ danych to liczba, zaczynajaca sie od 3." << endl;
        };

        cout << endl;

        Figura_3D* F1 = new Figura_3D(ilosc);
        do {

            cout << "Co chcesz zrobic z figura?\n1.Przesun\n2.Obroc\n3.Rzut na plaszczyzne\n4.Wyswietl wspolrzedne " << endl;

            while (!(cin >> wyb)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");
                cout << "Podaj prawidlowe dane! Prawidlowy typ danych to liczba!" << endl;
                cout << "Co chcesz zrobic z figura?\n1.Przesun\n2.Obroc\n3.Rzut na plaszczyzne\n4.Wyswietl wspolrzedne " << endl;
            };

            system("cls");

            switch (wyb)
            {
            case 1:
            {
                F1->przesunF();
                break;
            }
            case 2:
            {
                F1->obrotF();
                break;
            }
            case 3:
            {
                F1->rzutF();
                break;
            }
            case 4:
            {
                F1->wyswietlF();
                break;
            }
            default:
            {
                cout << "Wybierz od 1-4" << endl;
                break;
            }
            }

            cout << "Kontynuuj operacje na figurze. Wpisz 'k'.\nZakoncz operacje na figurze. Wpisz 'x'.";
            while (!(cin >> zakoncz2)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");
                cout << "Podaj prawidlowe dane!" << endl << "Zakoncz operacje na figurze 'x'. Kontynuuj operacje na figurze wpisz 'k'";
            };
            system("cls");
        } while (zakoncz2 != 'x');

        cout << "Chcesz zakonczyc program? Wpisz 'x'.\nNowa figura? Wpisz 'k'. " << endl;
        while (!(cin >> zakoncz)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "Podaj prawidlowe dane!" << endl << "Zakoncz program wpisz 'x'. Nowa figura wpisz 'k'";
        };
        
    } while (zakoncz != 'x');
      return 0;
}