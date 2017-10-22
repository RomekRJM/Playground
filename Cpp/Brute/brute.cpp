#include <iostream>
using namespace std;

template <class T>
class Character{
private:
	string name;
	T hitPoints;
public:
	Character(string name, T hitPoints);
	string getName();
	T getHitPoints();
};

template <class T>
Character<T>::Character(string nname, T initialHitPoints){
	name = nname;
	hitPoints = initialHitPoints;
}

template <class T>
string Character<T>::getName(){
	return name;
}

template <class T>
T Character<T>::getHitPoints(){
	return hitPoints;
}

int main(int argc, char **argv) {
	string bruteName = "Brute";
	Character<float> brute = Character<float>(bruteName, 100.0);
	cout << "Brute: " << brute.getName() << ", hp: " << brute.getHitPoints()  << endl;
	return 0;
}
