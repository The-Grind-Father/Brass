#include <iostream>
#include "Combatant.h"
int main() {

    Combatant player(new Hero());

    for (int i = 0; i < 10; i++) {
        std::cout
            << player.getClassName() << "\n"
            << "-Level " << player.getLevel() << "\n"
            << "-Level EXP: " << player.getLevelEXP() << '/' << player.getLevelUpReq() << "\n"
            << "-Total EXP: " << player.getTotalEXP() << "\n"
            << "-HP: " << player.getCurrentHP() << '/' << player.getMaxHP() << "\n"
            << "-EP: " << player.getCurrentEP() << '/' << player.getMaxEP() << "\n"
            << "-Str: " << player.getStr() << "\n"
            << "-Def: " << player.getDef() << "\n"
            << "-Acc: " << player.getAcc() << "\n"
            << "-En: " << player.getEn() << "\n"
            << "-Lu: " << player.getLu() << "\n"
            << "----------------------\n";

        auto AllMeleeMoves = player.getMeleeMoves();

        std::cout << "-Melee Moves: \n";
        for (auto& melee : AllMeleeMoves) {
            std::cout << "  -" << melee.Name << "\n";
        }
        
        player.gainEXP(150);

    }

    return 0;
}