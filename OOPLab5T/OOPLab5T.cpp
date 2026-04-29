#include <iostream>
#include <string>
#include <utility> // для std::move

using namespace std;

class Student {
protected:
    string pib;
    int course;
    long long id;
public:
    Student(string p = "Невідомо", int c = 1, long long i = 0) : pib(p), course(c), id(i) {
        cout << "Base Student created: " << pib << endl; // Повідомлення про створення 
    }
    virtual ~Student() { cout << "Base Student destroyed" << endl; } // Повідомлення про вилучення 

    virtual void print() {
        cout << "ПIБ: " << pib << ", Курс: " << course << ", ID: " << id << endl;
    }
    void setID(long long new_id) { id = new_id; }
};

class DiplomaStudent : public Student {
    string topic;
public:
    DiplomaStudent(string p, int c, long long i, string t) : Student(p, c, i), topic(t) {
        cout << "DiplomaStudent created" << endl;
    }
    ~DiplomaStudent() { cout << "DiplomaStudent destroyed" << endl; }

    void print() override {
        Student::print();
        cout << "Тема диплома: " << topic << endl;
    }
    void setTopic(string new_topic) { topic = new_topic; }
};

void testTask1() {
    cout << "\n--- Тест Завдання 1.1 ---" << endl;
    DiplomaStudent ds("Боднар Андрiй", 4, 12345, "Проектування систем на C++");
    ds.print();
    ds.setID(54321);
    ds.setTopic("Нова тема диплома");
    cout << "Пiсля змiн:" << endl;
    ds.print();
}

class Room {
    float area;
public:
    Room(float a = 0) : area(a) {}
    float getArea() { return area; }
};

class OneRoomApartment {
protected:
    Room room; // Кiмната втримується в класi (композицiя) [cite: 1684]
    float kitchenArea;
    int floor;
public:
    OneRoomApartment(float r_area, float k_area, int fl) : room(r_area), kitchenArea(k_area), floor(fl) {}
    virtual void print() {
        cout << "Поверх: " << floor << ", Кiмната: " << room.getArea() << "м2, Кухня: " << kitchenArea << "м2" << endl;
    }
};

class CityApartment : public OneRoomApartment {
    string city;
public:
    CityApartment(float r, float k, int f, string c) : OneRoomApartment(r, k, f), city(c) {
        cout << "CityApartment created" << endl;
    }
    ~CityApartment() { cout << "CityApartment destroyed" << endl; }

    void print() override {
        cout << "Мiсто: " << city << " | ";
        OneRoomApartment::print();
    }
};

void testTask2() {
    cout << "\n--- Тест Завдання 2.1 ---" << endl;
    CityApartment flat(20.5, 10.0, 5, "Чернiвцi");
    flat.print();
}

class SportGame {
protected:
    string* name;
public:
    SportGame(string n = "Game") : name(new string(n)) {}
    // Конструктор копiювання [cite: 1735]
    SportGame(const SportGame& other) : name(new string(*other.name)) { cout << "SportGame Copy Ctor" << endl; }
    // Конструктор перенесення [cite: 1735]
    SportGame(SportGame&& other) noexcept : name(other.name) { other.name = nullptr; cout << "SportGame Move Ctor" << endl; }

    virtual ~SportGame() { delete name; }

    virtual SportGame& operator=(const SportGame& other) {
        if (this != &other) { *name = *other.name; }
        return *this;
    }

    friend ostream& operator<<(ostream& os, const SportGame& g) {
        if (g.name) os << *g.name;
        return os;
    }
};

class Football : public SportGame {
    string* stadium;
public:
    Football(string n, string s) : SportGame(n), stadium(new string(s)) {}

    // Копiювання через базовий клас [cite: 1736]
    Football(const Football& other) : SportGame(other), stadium(new string(*other.stadium)) {
        cout << "Football Copy Ctor" << endl;
    }

    // Перенесення через базовий клас [cite: 1736]
    Football(Football&& other) noexcept : SportGame(std::move(other)), stadium(other.stadium) {
        other.stadium = nullptr;
        cout << "Football Move Ctor" << endl;
    }

    ~Football() { delete stadium; }

    Football& operator=(const Football& other) {
        if (this != &other) {
            SportGame::operator=(other);
            *stadium = *other.stadium;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Football& f) {
        os << (const SportGame&)f << " на стадiонi " << *f.stadium;
        return os;
    }
};

void testTask3() {
    cout << "\n--- Тест Завдання 3.1 ---" << endl;
    Football f1("Фiнал", "Буковина");
    cout << "Оригiнал: " << f1 << endl;
    Football f2 = f1; // Копiювання
    cout << "Копiя: " << f2 << endl;
    Football f3 = std::move(f1); // Перенесення
    cout << "Пiсля перенесення: " << f3 << endl;
}

int main() {
    setlocale(LC_CTYPE, "ukr"); // Коректне виведення кирилицi [cite: 463]
    char choice;

    do {
        cout << "\n--- Головне меню ---" << endl;
        cout << "1. Тестування Завдання 1.1 (Iєрархiя)" << endl;
        cout << "2. Тестування Завдання 2.1 (Композицiя)" << endl;
        cout << "3. Тестування Завдання 3.1 (Копiювання/Перенесення)" << endl;
        cout << "q. Вихiд" << endl;
        cout << "Ваш вибiр: ";
        cin >> choice;

        switch (choice) {
        case '1': testTask1(); break;
        case '2': testTask2(); break;
        case '3': testTask3(); break;
        case 'q': cout << "Вихiд з програми..." << endl; break;
        default: cout << "Невiрний вибiр!" << endl;
        }
    } while (choice != 'q');

    return 0;
}