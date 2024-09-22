#pragma once
#include <string>
#include <cstdint>

enum class AILMENT {NONE, STR, DEF, AGI, ACC, EN };
enum class AILCHANCE {NONE, LOW, MED, HIGH, ALWAYS};

struct Melee {
    Melee(std::string name, bool all, uint32_t hp, uint32_t ep, uint32_t dmg, AILMENT ail, AILCHANCE chance) : 
    Name(name), All(all), HPcost(hp), EPcost(ep), Damage(dmg), Ail(ail), Chance(chance) {};

    std::string Name = "N/A";
    bool All = false;
    uint32_t HPcost = 0u;
    uint32_t EPcost = 0u;
    uint32_t Damage = 1u;
    AILMENT Ail = AILMENT::NONE;
    AILCHANCE Chance = AILCHANCE::NONE;
};