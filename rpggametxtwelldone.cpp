#include <iostream>
#include <string>
#include <random>

class Entity {
private:
    int health;
    int damage;
    int potions = 3; 

public:
    // CONSTRUCTOR
    Entity(int h, int d) {
        health = h;
        damage = d;
    }

    int getHealth() const { return health; } 
    int getDamage() const { return damage; }
    int getPotions() const { return potions; }

    void TakeDamage(int incomingDamage) {
        health -= incomingDamage;
    }

    bool TryHeal(int amount) {
        if (potions > 0) {
            health += amount;
            potions--;
            return true;
        }
        return false;
    }

    bool IsAlive() const {
        return health > 0;
    }
};

int main(){
    //Random generation number using random function
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rndNumHealth(50, 100);
    std::uniform_int_distribution<> rndNumDmg(1, 25);
    std::uniform_int_distribution<> rndNumOption(0, 1);

    
    // We define pointers or use a default constructor initially. 
    // Here I will use a simple setup function or just initialize values first.
    int pHealth = 0, pDamage = 0, mHealth = 0, mDamage = 0;
    std::string difficulty;

    std::cout << "Welcome to txtbased battle game choose one of the difficulties: Easy (E); Normal (N); Hard (H); Quit (Q) \n";
    while (std::cin >> difficulty) {
        if (difficulty == "E"){
            pHealth = rndNumHealth(gen); pDamage = rndNumDmg(gen) * 2; 
            mHealth = rndNumHealth(gen);  mDamage = rndNumDmg(gen);
            break;
        } 
        else if (difficulty == "N"){
            pHealth = rndNumHealth(gen); pDamage = rndNumDmg(gen); 
            mHealth = rndNumHealth(gen);  mDamage = rndNumDmg(gen);
            break;
        }
        else if (difficulty == "H"){
            pHealth = rndNumHealth(gen); pDamage = rndNumDmg(gen); 
            mHealth = rndNumHealth(gen) * 2;  mDamage = rndNumDmg(gen);
            break;
        }
        else { std::cout << "Invalid. Try again: "; }
    }

    // CONSTRUCTOR CALL
    Entity Person(pHealth, pDamage);
    Entity Monster(mHealth, mDamage);

    std::cout << "Battle Start!\n";
    std::cout << "\nPlayer stats: \nHealth - " << Person.getHealth() << "\nDamage - " << Person.getDamage() << "\nPotions - 3" << "\n";  
    std::cout << "\nMonster stats: \nHealth - " << Monster.getHealth() << "\nDamage - " << Monster.getDamage() << "\nPotions - 3" << "\n";

    while (Person.IsAlive() && Monster.IsAlive()) {
        std::string option;
        std::cout << "\nAction? Attack (A), Heal (H), Stats (S): ";
        std::cin >> option;

        if (option == "A") {
            Monster.TakeDamage(Person.getDamage());
            std::cout << "You hit Monster for " << Person.getDamage() << " dmg. Now with " << Monster.getHealth() << "HP\n";
        } 
        else if (option == "H") {
            int healAmount = rndNumDmg(gen); //Reusing rndNumDmg because it goes from 1 to 25 the same as I want my heal potion to do 
            if (Person.TryHeal(healAmount)) {
                std::cout << "You healed " << healAmount << "HP. Now with " << Person.getHealth() << "HP\n";
            } else {
                std::cout << "No potions left!\n";
                continue;
            }
        } 
        else if (option == "S") {
            std::cout << "Player stats: \nHealth - " << Person.getHealth() << "\nDamage - " << Person.getDamage() << "\nPotions - " << Person.getPotions() << "\n";  
            std::cout << "\nMonster stats: \nHealth - " << Monster.getHealth() << "\nDamage - " << Monster.getDamage() << "\nPotions - " << Monster.getPotions() << "\n";
            continue;
        }
        else {
            std::cout << "Option not available.";
            continue;
        }

        // MONSTER TURN
        if (Monster.IsAlive()) {
            int action = rndNumOption(gen); 
            if (action == 1) {
                int healAmount = rndNumDmg(gen); //Reusing rndNumDmg because it goes from 1 to 25 the same as I want my heal potion to do 
                if (Monster.TryHeal(healAmount)) {
                    std::cout << "Monster healed " << healAmount << "HP. Now with " << Monster.getHealth() << "HP\n";
                } else {
                    action = 0; 
                }
            }
            if (action == 0) {
                Person.TakeDamage(Monster.getDamage());
                std::cout << "Monster hit you for " << Monster.getDamage() << " dmg. Now with " << Person.getHealth() << "HP\n";
            }
        }
    }

    if (Person.IsAlive()) std::cout << "VICTORY!\n";
    else std::cout << "DEFEAT.\n";


    return 0;
}