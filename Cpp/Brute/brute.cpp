#include <iostream>
using namespace std;

class DamageInterceptor{
public:
    float dealDamage(float * hp, float damage);
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
	float dealDamage(float damage);
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
float Character<T>::dealDamage(float damage){
	return damageInterceptor.dealDamage(&hitPoints, damage);
}

float DamageInterceptor::dealDamage(float* hp, float damage){
    return *hp -= damage;
}

int main(int argc, char **argv) {
	string bruteName = "Brute";
	Character<float> brute = Character<float>(bruteName, 100.0);
	cout << "Brute: " << brute.getName() << ", hp: " << brute.getHitPoints()  << endl;
	brute.dealDamage(33.3);
	cout << "Brute: " << brute.getName() << ", hp: " << brute.getHitPoints()  << endl;
	return 0;
}
