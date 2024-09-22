#pragma once
#include <cstdint>
#include <string>
#include <cmath>
#include <memory>
#include <vector>
#include "statblock.h"
#include "stattypes.h"
#include "pointwell.h"
#include "melee.h"
#include "move.h"
#include "Item.h"
#include "firearm.h"
#include "ammotype.h"

// COMBATANTCLASS(Hero,15,15,5,5,5,5,5,5)
// COMBATANTCLASS(Juicehead,12,18,4,5,5,5,6,5)
// COMBATANTCLASS(Guard,20,10,6,5,4,6,5,4)
// COMBATANTCLASS(Marksman, 15,15,3,7,6,4,5,5)

#define COMBATANTCONSTRUCT\
    HP->setMax(BASEHP);\
    HP->restore();\
    EP->setMax(BASEEP);\
    EP->restore();\
    setAll(BASEST, BASEDE, BASEAG, BASEAC, BASEEN, BASELU);

typedef std::uint64_t exp_t;
typedef std::uint16_t level_t;

class CombatantDelegate : public StatBlock {
public:
    CombatantDelegate() {
        CurrentLevel = 1u;
        TotalEXP = 0u;
        LevelEXP = 0u;
        levelUpReq = 100u;
        HP = std::make_unique<PointWell>();
        EP = std::make_unique<PointWell>();
    }

    virtual void LevelUp() = 0;
    virtual std::string getClassName() = 0;

    std::unique_ptr<PointWell> HP;
    std::unique_ptr<PointWell> EP;
    std::vector<Melee> MeleeMoves;

    // Level/EXP functions

    void gainEXP(exp_t gained_exp) {
        TotalEXP += gained_exp;
        LevelEXP += gained_exp;
        while (levelup_check()) {}
    }

    level_t getLevel() { return CurrentLevel; }
    exp_t getLevelExp() { return LevelEXP; }
    exp_t getTotalExp() { return TotalEXP; }
    exp_t getLevelUpReq() { return levelUpReq; }
    exp_t getEXPNeeded() { return levelUpReq - LevelEXP; }

    //HP functions
    bool spendHP(pw_t amt) {
        if (amt >= HP->getCurrent()) return false;
        HP->decrease(amt);
        return true;
    }

    // EP functions
    bool spendEP(pw_t amt) {
        if (amt > EP->getCurrent()) return false;
        EP->decrease(amt);
        return true;
    }

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

class Hero : public CombatantDelegate {
    public:
        static const pw_t BASEHP = (pw_t) 15u;
        static const pw_t BASEEP = (pw_t) 15u;
        static const stat_t BASEST = (stat_t) 5u;
        static const stat_t BASEDE = (stat_t) 5u;
        static const stat_t BASEAG = (stat_t) 5u;
        static const stat_t BASEAC = (stat_t) 5u;
        static const stat_t BASEEN = (stat_t) 5u;
        static const stat_t BASELU = (stat_t) 5u;
        
        std::string getClassName() override {return std::string("Hero"); }

        Hero() : CombatantDelegate() {
            COMBATANTCONSTRUCT
            MeleeMoves.emplace_back("Light", false, 0u, 0u, 5u, AILMENT::NONE, AILCHANCE::NONE);
            MeleeMoves.emplace_back("Heavy", false, 3u, 0u, 12u, AILMENT::NONE, AILCHANCE::NONE);
        }

    private:
        void LevelUp() override {
             HP->setMax((pw_t)((BASEHP/4.f) + HP->getMax()));
             HP->restore();
             EP->setMax((pw_t)((BASEEP/4.f) + EP->getMax()));
             EP->restore();
             increaseAll((stat_t)ceil((double)(getStr()/8.f)),
                 (stat_t)ceil((double)(getAcc()/8.f)),
                 (stat_t)ceil((double)(getAgi()/8.f)),
                 (stat_t)ceil((double)(getDef()/8.f)),
                 (stat_t)ceil((double)(getEn()/8.f)),
                 (stat_t)ceil((double)(getLu()/8.f)));
            if (CurrentLevel == 3)
                MeleeMoves.emplace_back("Sweep", true, 5u, 0u, 4u, AILMENT::NONE, AILCHANCE::NONE);
            if (CurrentLevel == 5)
                MeleeMoves.emplace_back("Head Blow", false, 0u, 0u, 5u, AILMENT::ACC, AILCHANCE::MED);
        }

};

class Combatant {
private:
    CombatantDelegate* cmbtclass;

public:
    Combatant() = delete;
    Combatant(CombatantDelegate* cmbt) : cmbtclass(cmbt) {}
    ~Combatant() { delete cmbtclass; cmbtclass = nullptr; }

    std::string getClassName() { return cmbtclass->getClassName(); }

    // Level/EXP functions
    level_t getLevel() { return cmbtclass->getLevel(); }
    exp_t getLevelEXP() { return cmbtclass->getLevelExp(); }
    exp_t getTotalEXP() { return cmbtclass->getTotalExp(); }
    exp_t getLevelUpReq() { return cmbtclass->getLevelUpReq(); }
    exp_t getEXPNeeded() { return cmbtclass->getEXPNeeded(); }
    void gainEXP(exp_t amt) { return cmbtclass->gainEXP(amt); }

    // HP functions
    pw_t getCurrentHP() { return cmbtclass->HP->getCurrent(); }
    pw_t getMaxHP() { return cmbtclass->HP->getMax(); }
    void setMaxHP(pw_t amt) { cmbtclass->HP->setMax(amt); }
    void decreaseHP(pw_t amt) { cmbtclass->HP->decrease(amt); }
    void increaseHP(pw_t amt) { cmbtclass->HP->increase(amt); }
    void restoreHP() { cmbtclass->HP->restore(); }
    bool spendHP(pw_t amt) { return cmbtclass->spendHP(amt); }

    // EP funcntions
    pw_t getCurrentEP() { return cmbtclass->EP->getCurrent(); }
    pw_t getMaxEP() { return cmbtclass->EP->getMax(); }
    void setMaxEP(pw_t amt) { cmbtclass->EP->setMax(amt); }
    void decreaseEP(pw_t amt) { cmbtclass->EP->decrease(amt); }
    void increaseEP(pw_t amt) { cmbtclass->EP->increase(amt); }
    void restoreEP() { cmbtclass->EP->restore(); }
    bool spendEP(pw_t amt) { return cmbtclass->spendEP(amt); }

    // Statblock functions (inherited for stattblock.h)
    stat_t getStr() { return cmbtclass->getStr(); }
    stat_t getAcc() { return cmbtclass->getAcc(); }
    stat_t getDef() { return cmbtclass->getDef(); }
    stat_t getEn() { return cmbtclass->getEn(); }
    stat_t getLu() { return cmbtclass->getLu(); }

    // returns melee moves
    std::vector<Melee> getMeleeMoves() { return cmbtclass->MeleeMoves; }

};