#ifndef CONTOCORRENTE_ESTRATTOCONTO_H
#define CONTOCORRENTE_ESTRATTOCONTO_H

#include "string"
#include "vector"

using namespace std;

class EstrattoConto {
public:
    EstrattoConto(int id, float value);
    int getId() const;
    float getValue() const;
    string getTipo() const;
private:
    int id=0;
    float value;
    string tipo;
};


#endif //PROGETTOUNI_ESTRATTOCONTO_H
