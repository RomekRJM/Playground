#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Weapon{
private:
    string name;
    float minDamage;
    float maxDamage;
public:
    Weapon(string _name, float _minDamage, float _maxDamage);
    float hit();
};

class DamageInterceptor{
public:
    float dealDamage(float * hp, Weapon weapon);
};

class CriticalDamageInterceptor : public DamageInterceptor{
private:
    const float criticalMultiplier = 3.33;
public:
    float dealDamage(float * hp, Weapon weapon);
};

template <class T>
class Character{
private:
	string name;
	T hitPoints;
	DamageInterceptor damageInterceptor;
public:
	Character(string name, T hitPoints);
	string getName();
	T getHitPoints();
	float dealDamage(Weapon weapon);
	void setDamageInterceptor(DamageInterceptor damageInterceptor);
};

template <class T>
Character<T>::Character(string nname, T initialHitPoints){
	name = nname;
	hitPoints = initialHitPoints;
	damageInterceptor = DamageInterceptor();
}

template <class T>
string Character<T>::getName(){
	return name;
}

template <class T>
T Character<T>::getHitPoints(){
	return hitPoints;
}

template <class T>
float Character<T>::dealDamage(Weapon weapon){
	return damageInterceptor.dealDamage(&hitPoints, weapon);
}

template <class T>
void Character<T>::setDamageInterceptor(DamageInterceptor _damageInterceptor){
        damageInterceptor = _damageInterceptor;
}

float DamageInterceptor::dealDamage(float* hp, Weapon weapon){
    return *hp -= weapon.hit();
}

float CriticalDamageInterceptor::dealDamage(float* hp, Weapon weapon){
    cout << "Critical" << endl;
    return *hp -= weapon.hit() * criticalMultiplier;
}

Weapon::Weapon(string _name, float _minDamage, float _maxDamage){
    name = _name;
    minDamage = _minDamage;
    maxDamage = _maxDamage;
}

float Weapon::hit(){
    srand (static_cast <unsigned> (time(0)));
    return minDamage + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxDamage-minDamage)));
}

int main(int argc, char **argv) {
	string bruteName = "Brute";
	Character<float> brute = Character<float>(bruteName, 100.0);
	Weapon oblivionMace = Weapon("Oblivion mace", 13, 21);
	cout << "Brute: " << brute.getName() << ", hp: " << brute.getHitPoints()  << endl;
	brute.dealDamage(oblivionMace);
	cout << "Brute receives hit on DamageInterceptor: " << brute.getName() << ", hp: " << brute.getHitPoints()  << endl;
	brute.setDamageInterceptor(CriticalDamageInterceptor());
	brute.dealDamage(oblivionMace);
	cout << "Brute receives hit on CriticalDamageInterceptor: " << brute.getName() << ", hp: " << brute.getHitPoints()  << endl;
	return 0;
}
