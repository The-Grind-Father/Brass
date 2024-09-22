#pragma once
#include "stattypes.h"

class StatBlock {
public:

    StatBlock() {
        Strength = (stat_t) 1u;
        Accuracy = (stat_t) 1u;
        Agility = (stat_t) 1u;
        Defense = (stat_t) 1u;
        Energen = (stat_t) 1u;
        Luck = (stat_t) 1u;
    }

    explicit StatBlock(stat_t s, stat_t ac, stat_t ag, stat_t d, stat_t e, stat_t l) {
        Strength = s;
        Accuracy = ac;
        Agility = ag;
        Defense = d;
        Energen = e;
        Luck = l;
    }

    // getters
    stat_t getStr() { return Strength; }
    stat_t getAcc() { return Accuracy; }
    stat_t getAgi() { return Agility; }
    stat_t getDef() { return Defense; }
    stat_t getEn() { return Energen; }
    stat_t getLu() { return Luck; }

    // setters
    void setStr(stat_t str) { Strength = str; }
    void setAcc(stat_t acc) { Accuracy = acc; }
    void setAgi(stat_t agi) { Agility = agi; }
    void setDef(stat_t def) { Defense = def; }
    void setEn(stat_t en) { Energen = en; }
    void setLu(stat_t lu) { Luck = lu; }

    void setAll(stat_t str, stat_t acc, stat_t agi, stat_t def, stat_t en, stat_t lu) {
        Strength = str;
        Accuracy = acc;
        Agility = agi;
        Defense = def;
        Energen = en;
        Luck = lu;
    }

    void increaseAll(stat_t str, stat_t acc, stat_t agi, stat_t def, stat_t en, stat_t lu) {
        Strength += str;
        Accuracy += acc;
        Agility += agi;
        Defense += def;
        Energen += en;
        Luck += lu;
    }
    
private:
    stat_t Strength;
    stat_t Accuracy;
    stat_t Agility;
    stat_t Defense;
    stat_t Energen;
    stat_t Luck;
};