#include <string>

//Fer un struct per les armes
struct Weapon {
	std::string name;
	std::string type;
	int reach;
};

// Fer uns truct per els enemics
struct Enemy {
	std::string name;
	int health;
	int damage;
	int defense;
	int rof;
	int experience;

};