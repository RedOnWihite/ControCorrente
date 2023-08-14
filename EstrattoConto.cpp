#include "EstrattoConto.h"

EstrattoConto::EstrattoConto(int id, float value) : id(id), value(value) {
    if (value < 0) {
        tipo = "prelievo";
    } else {
        tipo = "deposito";
    }
}

float EstrattoConto::getValue() const {
    return value;
}

int EstrattoConto::getId() const {
    return id;
}

string EstrattoConto::getTipo() const{
    return tipo;
}