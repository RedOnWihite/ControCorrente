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
    Conto(const string& nomeUtente, const string& password);

    void setNome(const std::string& nuovoNome);

    void setFondi(float nuoviFondi);

    void transazione(float amount);

    void stampaEC();

    void eliminaTransazione(int id);

    void salvaDatiSuFile(const std::string &nomeFile) const;

    string getName();
    string getPassword();
    int getId();
    float getFondi();

private:
    string nome;
    string password;
    int id;
    float fondi=0;
    vector<EstrattoConto> record;

    int generaNuovoId();
    void caricaDatiDaFile(const std::string& nomeFile);


};


#endif //PROGETTOUNI_CONTO_H
