//
// Created by klela on 16/07/2026.
//
#include <iostream>

class Character {
public:
    Character(int health, int armor, int block, int attackPower) {
        Health = health;
        Armor = armor;
        Block = block;
        AttackPower = attackPower;
    }

    bool IsAlive() const {
        if (Health > 0) {
            return true;
        }
        return false;
    }

    int GetHealth() const {
        return Health;
    }

    int GetArmor() const {
        return Armor;
    }

    int GetBlock() const {
        return Block;
    }

    int GetAttackPower() const {
        return AttackPower;
    }

    void TakeDamage(int damageReduction,int incomingDamage) {
        int remainingDamage = incomingDamage-damageReduction;
        if (remainingDamage < 0) {
            remainingDamage = 0;
        }
        Health -= remainingDamage;
        if (Health<0) {
            Health=0;
        }
    }

private:
    int Health;
    int Armor;
    int Block;
    int AttackPower;

};

//Checks if a Character died and ends the game.
bool EndGame(const Character& player,const Character& opponent) {
    if (!player.IsAlive() && !opponent.IsAlive()) {
        std::cout << "It's a tie. You both died" << std::endl;
        return true;
    }
    if (player.IsAlive() && !opponent.IsAlive()) {
        std::cout << "You Win!" << std::endl;
        return true;
    }
    if (!player.IsAlive() && opponent.IsAlive()) {
        std::cout << "You Lose!" << std::endl;
        return true;
    }



    return false;
}
int main (){

    std::cout << "Text Combat Prototype" << std::endl;
    Character player = Character{100,10,15,30};
    Character opponent = Character{100,10,15,30};

    while (player.IsAlive() && opponent.IsAlive()) {
        std::cout << "Player Health: " << player.GetHealth() << std::endl;
        std::cout << "Opponent Health: " << opponent.GetHealth() << std::endl;

        //Player Move
        //Get Player Decision
        std::cout << "Attack (A) or Defend (D) ?" << std::endl;
        char answer;
        std::cin >> answer;

        //Execute Player Decision
        switch (answer) {
            case 'A':
                opponent.TakeDamage(opponent.GetArmor(),player.GetAttackPower());
                std::cout << "Your opponent got hit!" << std::endl;
                break;
            case 'D':
                std::cout << "You blocked the enemy attack." << std::endl;
                break;
            default:
                std::cout << "Invalid answer" << std::endl;
        }

        //Check if game Ended
        if (EndGame(player, opponent)) {
            break;
        }
        //Opponent Attacks
        if (answer != 'D') {
            player.TakeDamage(player.GetArmor(), opponent.GetAttackPower());
            std::cout << "You got hit!" << std::endl;
        }
        else {
            /*
            int fullReduction = 0;
            fullReduction += player.GetArmor();
            fullReduction += player.GetBlock();
            */
            int fullReduction = player.GetArmor() + player.GetBlock();
            player.TakeDamage(fullReduction,opponent.GetAttackPower());
        }

        //Check if game Ended again
        //Check if game Ended
        if (EndGame(player, opponent)) {
            break;
        }
    }

    return 0;
}