//
// Created by Matteo on 09/08/2023.
//

#ifndef CONTOCORRENTE_ESTRATTOCONTO_H
#define CONTOCORRENTE_ESTRATTOCONTO_H


#include "vector"

using namespace std;

class EstrattoConto {
public:
    EstrattoConto(float value);
    int getId() const;
    float getValue() const;
private:
    int id=0;
    float value;
};


#endif //PROGETTOUNI_ESTRATTOCONTO_H
