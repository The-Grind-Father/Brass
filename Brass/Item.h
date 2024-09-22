#pragma once
#include <string>
#include <cstdint>


class Item {
    public:
    Item() {
        Name = "N/A";
        Price = 0u;
    }

    Item(std::string n, uint32_t p) {
        Name = n;
        Price = p;
    }

    // getters
    std::string getName() { return Name; }
    uint32_t getPrice() { return Price; }

    protected:
    std::string Name;
    uint32_t Price;
};