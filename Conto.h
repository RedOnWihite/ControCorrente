#ifndef CONTOCORRENTE_CONTO_H
#define CONTOCORRENTE_CONTO_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include "EstrattoConto.h"
#include <filesystem>

using namespace std;


class Conto {
public:
    Conto(const string& nomeUtente);

    void setNome(const std::string& nuovoNome);

    void setId(int nuovoId);

    void setFondi(float nuoviFondi);

    void transazione(float amount);

    void stampaEC();

    void eliminaTransazione(int id);

    string getName();
    int getId();
    float getFondi();

private:
    string nome;
    int id;
    float fondi=0;
    vector<EstrattoConto> record;

    int generaNuovoId();
    void caricaDatiDaFile(const std::string& nomeFile);
    void salvaDatiSuFile(const std::string &nomeFile) const;


};


#endif //PROGETTOUNI_CONTO_H
