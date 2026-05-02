#include <iostream>
#include <string>
#include <utility>

using namespace std;

class Student {
protected:
    string surname, name, pobatykovi; 
    int course;
    long long id;
public:
    Student() : surname(""), name(""),pobatykovi(""), course(1), id(0) {
        cout << "Student() - викликано конструктор за замовчуванням" << endl;
    }
    
    Student(string s, string n, string p, int c, long long i) 
        : surname(s), name(n),pobatykovi(p), course(c), id(i) {
        cout << "Student(параметри) - створено базовий клас" << endl;
    }
    
    virtual ~Student() { cout << "~Student() - вилучення базового класу" << endl; }

    virtual void print() const {
        cout << "ПIБ: " << surname << " " << name << " " <<pobatykovi 
             << " | Курс: " << course << " | ID: " << id << endl;
    }
    void setID(long long new_id) { id = new_id; }
};

class DiplomaStudent : public Student {
    string topic;
public:
    DiplomaStudent() : Student(), topic("") {
        cout << "DiplomaStudent() - конструктор за замовчуванням" << endl;
    }
    
    // Виклик конструктора базового класу
    DiplomaStudent(string s, string n, string p, int c, long long i, string t) 
        : Student(s, n, p, c, i), topic(t) {
        cout << "DiplomaStudent(параметри) - створено дочiрнiй клас" << endl;
    }
    
    ~DiplomaStudent() { cout << "~DiplomaStudent() - вилучення дочiрнього класу" << endl; }

    void print() const override {
        Student::print();
        cout << "Тема диплома: " << topic << endl;
    }
    void setTopic(string new_topic) { topic = new_topic; }
};

void testTask1() {
    cout << "\n--- Введення даних для Завдання 1.1 ---" << endl;
    string s, n, p, t;
    int c;
    long long i;

    cout << "Введiть прiзвище: "; cin >> s;
    cout << "Введiть iм'я: "; cin >> n;
    cout << "Введiть по-батьковi: "; cin >> p;
    cout << "Введiть курс (число): "; cin >> c;
    cout << "Введiть ID (число): "; cin >> i;
    
    cin.ignore(); // Очищення буфера перед getline
    cout << "Введiть тему диплома: "; getline(cin, t);

    cout << "\n--- Створення об'єкта через конструктор з параметрами ---" << endl;
    DiplomaStudent ds(s, n, p, c, i, t);
    
    cout << "\n--- Данi об'єкта ---" << endl;
    ds.print();

    cout << "\n--- Тест функцiй перепризначення ---" << endl;
    cout << "Введiть новий ID: "; cin >> i;
    ds.setID(i);
    cin.ignore();
    cout << "Введiть нову тему диплома: "; getline(cin, t);
    ds.setTopic(t);
    
    cout << "\nОновленi данi:" << endl;
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
        cout << "OneRoomApartment(параметри) - базовий клас створено" << endl;
    }
    
    virtual void print() const {
        cout << "Поверх: " << floor << " | Кiмната: " << room.getArea() 
             << " м2 | Кухня: " << kitchenArea << " м2" << endl;
    }
};

class CityApartment : public OneRoomApartment {
    string city;
public:
    CityApartment() : OneRoomApartment(), city("") {}
    
    CityApartment(float r, float k, int f, string c) 
        : OneRoomApartment(r, k, f), city(c) {
        cout << "CityApartment(параметри) - дочiрнiй клас створено" << endl;
    }
    
    ~CityApartment() { cout << "~CityApartment() - вилучення" << endl; }

    void print() const override {
        cout << "Мiсто: " << city << " | ";
        OneRoomApartment::print();
    }
};

void testTask2() {
    cout << "\n--- Введення даних для Завдання 2.1 ---" << endl;
    float r_area, k_area;
    int floor;
    string city;

    cout << "Введiть площу кiмнати (м2): "; cin >> r_area;
    cout << "Введiть площу кухнi (м2): "; cin >> k_area;
    cout << "Введiть поверх: "; cin >> floor;
    
    cin.ignore();
    cout << "Введiть назву мiста: "; getline(cin, city);

    cout << "\n--- Створення об'єкта ---" << endl;
    CityApartment flat(r_area, k_area, floor, city);
    flat.print();
}


class SportGame {
protected:
    string* name;
public:
    SportGame(string n = "") : name(new string(n)) {}
    SportGame(const SportGame& other) : name(new string(*other.name)) { cout << "SportGame: Конструктор копiювання" << endl; }
    SportGame(SportGame&& other) noexcept : name(other.name) { other.name = nullptr; cout << "SportGame: Конструктор перенесення" << endl; }
    
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
        cout << "Введiть назву гри (базовий клас): ";
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
        cout << "Football: Конструктор копiювання" << endl;
    }
    
    Football(Football&& other) noexcept : SportGame(std::move(other)), stadium(other.stadium) {
        other.stadium = nullptr;
        cout << "Football: Конструктор перенесення" << endl;
    }

    ~Football() { delete stadium; }

    // Перевизначення виводу з викликом базового
    friend ostream& operator<<(ostream& os, const Football& f) {
        os << (const SportGame&)f << " | Стадiон: " << *f.stadium;
        return os;
    }

    // Перевизначення вводу з викликом базового
    friend istream& operator>>(istream& is, Football& f) {
        is >> (SportGame&)f; // Викликаємо введення базового класу
        cout << "Введiть назву стадiону (дочiрнiй клас): ";
        string temp;
        is >> temp;
        if (f.stadium) *f.stadium = temp;
        else f.stadium = new string(temp);
        return is;
    }
};

void testTask3() {
    cout << "\n--- Тест Завдання 3.1 (Перевантаження >> та <<) ---" << endl;
    Football f1;
    cin >> f1; // Працює перевантажений оператор введення!

    cout << "\nОригiнальний об'єкт: " << f1 << endl;
    
    cout << "\nТест копiювання:" << endl;
    Football f2 = f1; 
    cout << "Копiя f2: " << f2 << endl;

    cout << "\nТест перенесення:" << endl;
    Football f3 = std::move(f1); 
    cout << "Об'єкт f3 пiсля перенесення: " << f3 << endl;
}


int main() {
    setlocale(LC_CTYPE, "ukr");
    char choice;

    do {
        cout << "\n=========== ГОЛОВНЕ МЕНЮ ===========" << endl;
        cout << "1. Завдання 1.1 (Спадкування)" << endl;
        cout << "2. Завдання 2.1 (Композицiя)" << endl;
        cout << "3. Завдання 3.1 (Ввiд/Вивiд у потiк)" << endl;
        cout << "q. Вихiд" << endl;
        cout << "Ваш вибiр: ";
        cin >> choice;

        switch (choice) {
            case '1': testTask1(); break;
            case '2': testTask2(); break;
            case '3': testTask3(); break;
            case 'q': cout << "Програму завершено." << endl; break;
            default: cout << "Помилка: оберiть пункт вiд 1 до 3 або q." << endl;
        }
    } while (choice != 'q');

    return 0;
}