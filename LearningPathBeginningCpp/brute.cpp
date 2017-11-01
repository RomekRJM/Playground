#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Weapon {
private:
    string name;
    float minDamage;
    float maxDamage;
public:

    Weapon() : Weapon("Bare hands", 1.0, 3.0) {
    };
    Weapon(string _name, float _minDamage, float _maxDamage);
    float hit();
};

class DamageInterceptor {
public:
    virtual float dealDamage(float * hp, Weapon weapon);
};

class CriticalDamageInterceptor : public DamageInterceptor {
private:
    const float criticalMultiplier = 1.5;
public:
    float dealDamage(float * hp, Weapon weapon) override;
};

template <class T>
class Character {
private:
    string name;
    T hitPoints;
    DamageInterceptor* damageInterceptor;
    Weapon weapon;
public:
    Character(string name, T hitPoints);
    string getName();
    T getHitPoints();
    float receiveDamage(Character aggressor);
    void setDamageInterceptor(DamageInterceptor* damageInterceptor);
    void setWeapon(Weapon w);
    Weapon getWeapon();
};

template <class T>
Character<T>::Character(string nname, T initialHitPoints) {
    name = nname;
    hitPoints = initialHitPoints;
    damageInterceptor = new DamageInterceptor();
}

template <class T>
string Character<T>::getName() {
    return name;
}

template <class T>
T Character<T>::getHitPoints() {
    return hitPoints;
}

template <class T>
void Character<T>::setWeapon(Weapon w) {
    weapon = w;
}

template <class T>
Weapon Character<T>::getWeapon() {
    return weapon;
}

template <class T>
float Character<T>::receiveDamage(Character aggressor) {
    return damageInterceptor->dealDamage(&hitPoints, aggressor.getWeapon());
}

template <class T>
void Character<T>::setDamageInterceptor(DamageInterceptor* _damageInterceptor) {
    damageInterceptor = _damageInterceptor;
}

float DamageInterceptor::dealDamage(float* hp, Weapon weapon) {
    float hit = weapon.hit();
    *hp -= hit;
    return hit;
}

float CriticalDamageInterceptor::dealDamage(float* hp, Weapon weapon) {
    float hit = weapon.hit() * criticalMultiplier;
    *hp -= hit;
    return hit;
}

Weapon::Weapon(string _name, float _minDamage, float _maxDamage) {
    name = _name;
    minDamage = _minDamage;
    maxDamage = _maxDamage;
}

float Weapon::hit() {
    srand(static_cast<unsigned> (time(0)));
    return minDamage + static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / (maxDamage - minDamage)));
}

void fight() {
    string bruteName = "Brute";
    Character<float> brute = Character<float>(bruteName, 100.0);
    Weapon oblivionMace = Weapon("Oblivion mace", 13, 21);
    brute.setWeapon(oblivionMace);

    string opponentName = "Arrger";
    Character<float> arrgor = Character<float>(opponentName, 100.0);
    Weapon talonsLance = Weapon("Talon's lance", 15, 19);
    arrgor.setWeapon(talonsLance);
    CriticalDamageInterceptor* criticalDamageInterceptor = new CriticalDamageInterceptor();
    arrgor.setDamageInterceptor(criticalDamageInterceptor);

    do {
        arrgor.receiveDamage(brute);
        brute.receiveDamage(arrgor);
        cout << "Brute, hp: " << brute.getHitPoints() << endl;
        cout << "Arrgor, hp: " << arrgor.getHitPoints() << endl;
    } while (brute.getHitPoints() > 0 && arrgor.getHitPoints() > 0);
}

int main(int argc, char **argv) {
    fight();

    return 0;
}