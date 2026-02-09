#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>


//Text turn-based game for Person - Monster with health and damage
//Each entity has 3 potions to heal with. 

class Entity {
    private:
        int health;
        int damage;
        int potion = 3;

    public:
        void setDamage(int d) {
            damage = d;
        }
        int getDamage(){
            return damage;
        }
        
        void setHealth(int h) {
            health = h;
        }
        int getHealth(){
            return health;
        }

        int getPotion(){
            return potion;
        }

        void Attack(int d){
            health -= d;
        }

        void Heal(int hp){ //hp = healing power
            health += hp;
            potion --;
        }
};

int main(){
    srand(time(0));
    Entity Person;
    Entity Monster;
    std::string difficulty;
    std::string option;

    std::cout << "Welcome to txtbased battle game choose one of the difficulties: Easy (E); Normal (N); Hard (H); Quit (Q)" << "\n";

    //Initialization
    while(std::cin >> difficulty) {
        if (difficulty == "E"){
            int randomNum = rand() % 101;
            Person.setHealth(randomNum);
            randomNum = (rand() % 20);
            Person.setDamage(randomNum * 2);
            randomNum = rand() % 101;
            Monster.setHealth(randomNum);
            randomNum = rand() % 101;
            Monster.setDamage(randomNum);
            break;
        }
        else if (difficulty == "N"){
            int randomNum = rand() % 101;
            Person.setHealth(randomNum);
            randomNum = (rand() % 20);
            Person.setDamage(randomNum);
            randomNum = rand() % 101;
            Monster.setHealth(randomNum);
            randomNum = rand() % 101;
            Monster.setDamage(randomNum);
            break;
        }
        else if (difficulty == "H"){
            int randomNum = rand() % 101;
            Person.setHealth(randomNum);
            randomNum = (rand() % 20);
            Person.setDamage(randomNum);
            randomNum = rand() % 101;
            Monster.setHealth(randomNum * 2);
            randomNum = rand() % 101;
            Monster.setDamage(randomNum); 
            break;
        }
        else if (difficulty == "Q") break;
        else{
            std::cout << "Option unavailable, choose from one E, N, H, Q";
        }
    }

    std::cout << "Player stats: Health - " << Person.getHealth() << " Damage - " << Person.getDamage() << " Potions - 3" << "\n";  
    std::cout << "Monster stats: Health - " << Monster.getHealth() << " Damage - " << Monster.getDamage() << " Potions - 3" << "\n";  

    while (Person.getHealth() >= 0 && Monster.getHealth() >= 0){
        std::cout << "Choose one: Attack (A), Heal (H), Stat (S)" << "\n";
        std::cin >> option;
        int randomNum = rand() % 2;
        int randomHealth = rand() % 26;

        
        if (option == "A"){
            Monster.Attack(Person.getDamage());
            std::cout << "Player dealt " << Person.getDamage() << "hp to monster. Now with " << Monster.getHealth() << "hp. \n";

        }
        else if (option == "H" && Person.getPotion() != 0){
            Person.Heal(randomHealth);
            std::cout << "Player healed " << randomHealth << "hp. Now with " << Person.getHealth() << "\n";
        }
        else if (Person.getPotion() == 0){
            std::cout << "Player without any more potions, choose another option \n";
            continue;
        }
        else if (option == "S"){
            std::cout << "Player stats: Health - " << Person.getHealth() << " Damage - " << Person.getDamage() << " Potions - " << Person.getPotion() << "\n";  
            std::cout << "Monster stats: Health - " << Monster.getHealth() << " Damage - " << Monster.getDamage() << " Potions - " << Monster.getPotion() << "\n";
            continue;
        }

        switch (randomNum)
            {
            case 0: //Monster Attacks
                Person.Attack(Monster.getDamage());
                std::cout << "Monster attacked and dealt " << Monster.getDamage() << "hp to player. Now with " << Person.getHealth() << "hp. \n";
                break;
            
            case 1: //Monster Heals
                Monster.Heal(randomHealth);
                std::cout << "Monster healed " << randomHealth << "hp. Now with " << Monster.getHealth() << "\n";
                break;
            default:
                break;
            }
    }

    if(Person.getHealth() <= 0) std::cout << "Unfortunately, you lost. \n";
    else if (Monster.getHealth() <= 0) std::cout << "Congratulations, you won! \n";

    return 0;
}
