#include <string>
#include <iostream>
using namespace std;

class Taxi {
private:
    string licensePlate; // Номер автомобіля
    string model;       // Модель машини
    string driverName;  // Ім'я водія
    bool isAvailable;   // Чи вільне таксі
    double* fare;       // Вартість поїздки ((динамічна пам'ять))

    static int totalTaxis; // Загальна кількість таксі
    static double baseFare; // Базовий тариф для всіх

public:
    // Конструктор з аргументами
    Taxi(string plate, string mdl, string driver, bool available)
        : licensePlate(plate), model(mdl), driverName(driver), isAvailable(available) {
        fare = new double(0.0); // Виділяємо пам'ять
        totalTaxis++; // Збільшуємо лічильник
    }

    // Конструктор копіювання з новим водієм
    Taxi(const Taxi& other, string newDriver)
        : licensePlate(other.licensePlate), model(other.model),
        driverName(newDriver), isAvailable(other.isAvailable) {
        fare = new double(*other.fare); // Копіюємо дані
        totalTaxis++;
    }

    // Звичайний конструктор копіювання
    Taxi(const Taxi& other)
        : licensePlate(other.licensePlate), model(other.model),
        driverName(other.driverName), isAvailable(other.isAvailable) {
        fare = new double(*other.fare); // Копіюємо дані
        totalTaxis++;
    }

    // Деструктор
    ~Taxi() {
        delete fare; // Очищаємо пам'ять
        totalTaxis--; // Зменшуємо лічильник
    }

    // Прийняти замовлення
    void acceptOrder(double orderFare) {
        if (isAvailable) {
            *fare = orderFare;
            isAvailable = false;
            cout << "Таксі " << licensePlate << " взяло замовлення. Ціна: " << *fare << "$" << endl;
        }
        else {
            cout << "Таксі " << licensePlate << " зайняте." << endl;
        }
    }

    // Завершити поїздку
    void completeTrip() {
        if (!isAvailable) {
            isAvailable = true;
            cout << "Таксі " << licensePlate << " завершило поїздку. Ціна: " << *fare << "$" << endl;
            *fare = 0.0; // Скидаємо ціну
        }
        else {
            cout << "Таксі " << licensePlate << " не має активної поїздки." << endl;
        }
    }

    // Змінити базовий тариф
    static void setBaseFare(double newFare) {
        baseFare = newFare;
        cout << "Базовий тариф змінено на: " << baseFare << endl;
    }

    // Показати кількість таксі
    static int getTotalTaxis() {
        return totalTaxis;
    }

    // Порівняння за номером
    bool operator==(const Taxi& other) const {
        return licensePlate == other.licensePlate;
    }

    // Виведення інформації
    friend ostream& operator<<(ostream& os, const Taxi& taxi) {
        os << "Таксі: " << taxi.licensePlate << ", Модель: " << taxi.model
            << ", Водій: " << taxi.driverName << ", Вільне: "
            << (taxi.isAvailable ? "Так" : "Ні") << ", Ціна: " << *taxi.fare << "$" << endl;
        return os;
    }

    // Отримати номер
    string getLicensePlate() const { return licensePlate; }
    // Змінити водія
    void setDriverName(string name) { driverName = name; }
};

// Ініціалізація статичних змінних
int Taxi::totalTaxis = 0;
double Taxi::baseFare = 5.0;

int main() {
    system("chcp 1251"); //  кодування для української мови в консолі 

    // Створюємо статичний об'єкт
    Taxi taxi1("ВН4545ВН", "Toyota Camry", "Іван Ковальов", true);
    cout << taxi1 << endl;

    // Створюємо динамічний об'єкт
    Taxi* taxi2 = new Taxi("АА6711НВ", "Honda Accord", "Марія Денисенко", true);
    cout << *taxi2 << endl;

    // Тестуємо методи
    taxi1.acceptOrder(15.0); // Беремо замовлення
    taxi1.completeTrip();    // Завершуємо поїздку

    taxi2->acceptOrder(20.0); // Беремо замовлення
    cout << *taxi2 << endl;

    // Показуємо статичні дані
    cout << "Загальна кількість таксі: " << Taxi::getTotalTaxis() << endl;
    Taxi::setBaseFare(7.0); // Міняємо тариф
    cout << "Новий базовий тариф застосовується до всіх таксі." << endl;

    // Перевіряємо порівняння
    Taxi taxi3("AA1211ОН", "Ford Focus", "Олег Шегульцов", false);
    if (taxi1 == taxi3) {
        cout << "Таксі мають однаковий номер." << endl;
    }
    else {
        cout << "Таксі мають різні номери." << endl;
    }

    // Тестуємо конструктор копіювання
    Taxi taxi4(taxi1, "Ганна Лодишева");
    cout << taxi4 << endl;

    // Видаляємо динамічний об'єкт
    delete taxi2;

    // Перевіряємо кількість таксі
    cout << "Кількість таксі після видалення: " << Taxi::getTotalTaxis() << endl;

    return 0;
}