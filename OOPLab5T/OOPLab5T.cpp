#include <iostream>
#include <string>
#include <utility>

using namespace std;

class Student {
protected:
    string surname, name, patronymic; 
    int course;
    long long id;
public:
    Student() : surname(""), name(""), patronymic(""), course(1), id(0) {
        cout << "Student() - default constructor called" << endl;
    }
    
    Student(string s, string n, string p, int c, long long i) 
        : surname(s), name(n), patronymic(p), course(c), id(i) {
        cout << "Student(parameters) - base class created" << endl;
    }
    
    virtual ~Student() { cout << "~Student() - base class destruction" << endl; }

    virtual void print() const {
        cout << "Name: " << surname << " " << name << " " << patronymic 
             << " | Course: " << course << " | ID: " << id << endl;
    }
    void setID(long long new_id) { id = new_id; }
};

class DiplomaStudent : public Student {
    string topic;
public:
    DiplomaStudent() : Student(), topic("") {
        cout << "DiplomaStudent() - default constructor" << endl;
    }
    
    // Виклик конструктора базового класу
    DiplomaStudent(string s, string n, string p, int c, long long i, string t) 
        : Student(s, n, p, c, i), topic(t) {
        cout << "DiplomaStudent(parameters) - derived class created" << endl;
    }
    
    ~DiplomaStudent() { cout << "~DiplomaStudent() - derived class destruction" << endl; }

    void print() const override {
        Student::print();
        cout << "Diploma topic: " << topic << endl;
    }
    void setTopic(string new_topic) { topic = new_topic; }
};

void testTask1() {
    cout << "\n--- Data input for Task 1.1 ---" << endl;
    string s, n, p, t;
    int c;
    long long i;

    cout << "Enter surname: "; cin >> s;
    cout << "Enter name: "; cin >> n;
    cout << "Enter patronymic: "; cin >> p;
    cout << "Enter course (number): "; cin >> c;
    cout << "Enter ID (number): "; cin >> i;
    
    cin.ignore(); // Очищення буфера перед getline
    cout << "Enter diploma topic: "; getline(cin, t);

    cout << "\n--- Creating object via parameterized constructor ---" << endl;
    DiplomaStudent ds(s, n, p, c, i, t);
    
    cout << "\n--- Object data ---" << endl;
    ds.print();

    cout << "\n--- Reassignment functions test ---" << endl;
    cout << "Enter new ID: "; cin >> i;
    ds.setID(i);
    cin.ignore();
    cout << "Enter new diploma topic: "; getline(cin, t);
    ds.setTopic(t);
    
    cout << "\nUpdated data:" << endl;
    ds.print();
}


class Room {
    float area;
public:
    Room(float a = 0) : area(a) {}
    float getArea() const { return area; }
    void setArea(float a) { area = a; }
};

class OneRoomApartment {
protected:
    Room room; // Композиція
    float kitchenArea;
    int floor;
public:
    OneRoomApartment() : room(0), kitchenArea(0), floor(1) {}
    
    OneRoomApartment(float r_area, float k_area, int fl) 
        : room(r_area), kitchenArea(k_area), floor(fl) {
        cout << "OneRoomApartment(parameters) - base class created" << endl;
    }
    
    virtual void print() const {
        cout << "Floor: " << floor << " | Room: " << room.getArea() 
             << " m2 | Kitchen: " << kitchenArea << " m2" << endl;
    }
};

class CityApartment : public OneRoomApartment {
    string city;
public:
    CityApartment() : OneRoomApartment(), city("") {}
    
    CityApartment(float r, float k, int f, string c) 
        : OneRoomApartment(r, k, f), city(c) {
        cout << "CityApartment(parameters) - derived class created" << endl;
    }
    
    ~CityApartment() { cout << "~CityApartment() - destruction" << endl; }

    void print() const override {
        cout << "City: " << city << " | ";
        OneRoomApartment::print();
    }
};

void testTask2() {
    cout << "\n--- Data input for Task 2.1 ---" << endl;
    float r_area, k_area;
    int floor;
    string city;

    cout << "Enter room area (m2): "; cin >> r_area;
    cout << "Enter kitchen area (m2): "; cin >> k_area;
    cout << "Enter floor: "; cin >> floor;
    
    cin.ignore();
    cout << "Enter city name: "; getline(cin, city);

    cout << "\n--- Object creation ---" << endl;
    CityApartment flat(r_area, k_area, floor, city);
    flat.print();
}


class SportGame {
protected:
    string* name;
public:
    SportGame(string n = "") : name(new string(n)) {}
    SportGame(const SportGame& other) : name(new string(*other.name)) { cout << "SportGame: Copy constructor" << endl; }
    SportGame(SportGame&& other) noexcept : name(other.name) { other.name = nullptr; cout << "SportGame: Move constructor" << endl; }
    
    virtual ~SportGame() { delete name; }

    SportGame& operator=(const SportGame& other) {
        if (this != &other) { *name = *other.name; }
        return *this;
    }
    
    // Перевизначення виводу
    friend ostream& operator<<(ostream& os, const SportGame& g) {
        if (g.name) os << *g.name;
        return os;
    }

    // Перевизначення вводу (для базового класу)
    friend istream& operator>>(istream& is, SportGame& g) {
        cout << "Enter game name (base class): ";
        string temp;
        is >> temp;
        if (g.name) *g.name = temp;
        else g.name = new string(temp);
        return is;
    }
};

class Football : public SportGame {
    string* stadium;
public:
    Football() : SportGame(), stadium(new string("")) {}
    
    Football(const Football& other) : SportGame(other), stadium(new string(*other.stadium)) {
        cout << "Football: Copy constructor" << endl;
    }
    
    Football(Football&& other) noexcept : SportGame(std::move(other)), stadium(other.stadium) {
        other.stadium = nullptr;
        cout << "Football: Move constructor" << endl;
    }

    ~Football() { delete stadium; }

    // Перевизначення виводу з викликом базового
    friend ostream& operator<<(ostream& os, const Football& f) {
        os << (const SportGame&)f << " | Stadium: " << *f.stadium;
        return os;
    }

    // Перевизначення вводу з викликом базового
    friend istream& operator>>(istream& is, Football& f) {
        is >> (SportGame&)f; // Викликаємо введення базового класу
        cout << "Enter stadium name (derived class): ";
        string temp;
        is >> temp;
        if (f.stadium) *f.stadium = temp;
        else f.stadium = new string(temp);
        return is;
    }
};

void testTask3() {
    cout << "\n--- Test Task 3.1 (Overloading >> and <<) ---" << endl;
    Football f1;
    cin >> f1; // Працює перевантажений оператор введення!

    cout << "\nOriginal object: " << f1 << endl;
    
    cout << "\nCopy test:" << endl;
    Football f2 = f1; 
    cout << "Copy f2: " << f2 << endl;

    cout << "\nMove test:" << endl;
    Football f3 = std::move(f1); 
    cout << "Object f3 after move: " << f3 << endl;
}


int main() {
    char choice;

    do {
        cout << "\n   MAIN MENU" << endl;
        cout << "1. Task 1.1 " << endl;
        cout << "2. Task 2.1 " << endl;
        cout << "3. Task 3.1 " << endl;
        cout << "q. Exit" << endl;
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
            case '1': testTask1(); break;
            case '2': testTask2(); break;
            case '3': testTask3(); break;
            case 'q': cout << "Program terminated." << endl; break;
            default: cout << "Error: choose an option from 1 to 3 or q." << endl;
        }
    } while (choice != 'q');

    return 0;
}