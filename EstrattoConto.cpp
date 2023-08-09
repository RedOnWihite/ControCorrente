//
// Created by Matteo on 09/08/2023.
//

#include "EstrattoConto.h"

EstrattoConto::EstrattoConto(float value) : value(value) {
    id++;
}

float EstrattoConto::getValue() const {
    return value;
}

int EstrattoConto::getId() const {
    return id;
}