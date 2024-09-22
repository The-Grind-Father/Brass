#pragma once
#include <memory>
#include "pointwell.h"

class Ammunition {

public:

private:
    std::unique_ptr<PointWell> Rifle;
    std::unique_ptr<PointWell> Slug;
    std::unique_ptr<PointWell> HandCannon;
    std::unique_ptr<PointWell> Explosive;
};