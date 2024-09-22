#pragma once
#include <cstdint>
#include <string>
#include <cmath>
#include <memory>
#include "statblock.h"
#include "stattypes.h"

typedef std::uint64_t exp_t;
typedef std::uint16_t level_t;

class NurseDeligate : public StatBlock {

public:
    NurseDeligate() {
        CurrentLevel = 1u;
        LevelEXP = 0u;
        TotalEXP = 0u;
        levelUpReq = 100u;
        setAll(5,5,5,5,5,5);
    }

    std::string getClassName() { return "Nurse"; }

    // Level/EXP Functions

    void gainEXP(exp_t gained_exp) {
        TotalEXP += gained_exp;
        LevelEXP += gained_exp;
        while (levelup_check()) {}
    }

    void LevelUp() {
        increaseAll((stat_t)ceil((double)(getStr()/8.f)),
            (stat_t)ceil((double)(getAcc()/8.f)),
            (stat_t)ceil((double)(getAgi()/8.f)),
            (stat_t)ceil((double)(getDef()/8.f)),
            (stat_t)ceil((double)(getEn()/8.f)),
            (stat_t)ceil((double)(getLu()/8.f)));
    }

    level_t getLevel() { return CurrentLevel; }
    exp_t getLevelExp() { return LevelEXP; }
    exp_t getTotalExp() { return TotalEXP; }
    exp_t getLevelUpReq() { return levelUpReq; }
    exp_t getEXPNeeded() { return levelUpReq - LevelEXP; }


protected:
    level_t CurrentLevel;
    exp_t LevelEXP;
    exp_t TotalEXP;
    exp_t levelUpReq;

    bool levelup_check() {
        if (LevelEXP > levelUpReq) {
            CurrentLevel++;
            LevelEXP -= levelUpReq;
            LevelUp();
            levelUpReq *= 1.5;
            return true;
        }
        return false;
    }
};