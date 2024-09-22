#pragma once
#include <string>
#include <cstdint>
#include "Item.h"
#include "pointwell.h"
#include "ammotype.h"

class Firearm : public Item {

public:
    Firearm() : Item() {
        Name = "N/A";
        Ammotype = AMMOTYPE::PISTOL;
        Price = 0u;
        Damage = 0u;
        Magazine = PointWell(0u,1u);
    }

    Firearm(std::string name, AMMOTYPE ammotype, uint32_t price, uint32_t damage, uint32_t magsize) : Item() {
        Name = name;
        Price = price;
        Damage = damage;
        Magazine = PointWell(0u, magsize);
    }

    // getters
    uint32_t getDmg() { return Damage; }
    uint32_t getMagAmmo() { return Magazine.getCurrent(); }
    uint32_t getMagSize() { return Magazine.getMax(); }
    AMMOTYPE getAmmoType() { return Ammotype; }

    // setters
    void increaseDmg(uint32_t dmg) { Damage += dmg; }
    void increaseMagSize(uint32_t amt) { Magazine.increase(amt); }
    void rld(PointWell ammo) {
        if (ammo.getCurrent() <= Magazine.getMax() - Magazine.getCurrent())
          Magazine.restore();
        Magazine.increase(ammo.getCurrent());  
    }

private:
    uint32_t Damage;
    PointWell Magazine;
    AMMOTYPE Ammotype;
};