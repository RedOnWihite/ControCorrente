//
// Created by Matteo on 09/08/2023.
//

#include "Conto.h"

using namespace std;

Conto::Conto(const string& nomeUtente)
        : nome(nomeUtente), id(generaNuovoId()), fondi(0) {
    namespace fs = std::filesystem;
    if (fs::create_directory(nomeUtente)) {
        std::cout << "Il conto è stato creato con successo\n";
    } else {
        std::cout << "Errore nella creazione del conto\n";
    }

    salvaDatiSuFile(nomeUtente);
}


void Conto::caricaDatiDaFile(const std::string& nomeFile) {
    // Caricamento dei dati del conto
    std::ifstream inputFile(nomeFile + "/Conto.txt");
    if (!inputFile) {
        std::cerr << "Errore nell'apertura del file " << nomeFile << std::endl;
        return;
    }

    inputFile >> nome;
    inputFile >> id;
    inputFile >> fondi;

    inputFile.close();

    // Caricamento dell'estratto conto
    std::ifstream estrattoContoFile(nomeFile + "/EstrattoConto.txt");
    if (!estrattoContoFile) {
        std::cerr << "Errore nell'apertura del file EstrattoConto.txt" << std::endl;
        return;
    }

    record.clear(); // Assicuriamoci di svuotare il vettore prima di caricare nuovi dati

    int id;
    float value;

    // Continua a leggere dal file finché ci sono dati disponibili
    while (estrattoContoFile >> value) {
        record.push_back(value); // Aggiungi un nuovo oggetto EstrattoConto al vettore record
    }

    estrattoContoFile.close();
}


void Conto::salvaDatiSuFile(const std::string &nomeFile) const {
    // Salvataggio dei dati del conto
    std::ofstream outputFile(nomeFile + "/Conto.txt");
    if (!outputFile) {
        std::cerr << "Errore nell'apertura del file " << nomeFile << std::endl;
        return;
    }

    outputFile << nome << "\n";
    outputFile << id << "\n";
    outputFile << fondi << "\n";

    outputFile.close();

    // Salvataggio dell'estratto conto
    std::string nomeEstrattoConto = "EstrattoConto.txt";
    std::ofstream estrattoContoFile(nomeEstrattoConto);
    if (!estrattoContoFile) {
        std::cerr << "Errore nell'apertura del file " << nomeEstrattoConto << std::endl;
        return;
    }

    for (const auto& elemento : record) {
        estrattoContoFile << elemento.getId() << "\n";
        estrattoContoFile << elemento.getValue() << "\n";
    }

    estrattoContoFile.close();
}

void Conto::transazione(float amount){
    if(amount<0){
        cout<<"è stato prelevato: "<<amount<<" soldi dal conto"<<endl;
    } else{
        cout<<"è stato depositato: "<<amount<<" soldi dal conto"<<endl;
    }
    fondi=fondi+amount;
    record.push_back(amount);
}

void Conto::stampaEC() {
    for (const auto& elemento : record) {
        std::cout << "ID: " << elemento.getId() << ", Valore: " << elemento.getValue() << std::endl;
    }
}

//generazione base
int Conto::generaNuovoId() {
    static int prossimoId = 0;
    return prossimoId++;
}

int Conto::getId() {
    return id;
}

string Conto::getName() {
    return nome;
}

float Conto::getFondi() {
    return fondi;
}

void Conto::setNome(const string &nuovoNome) {
    nome=nuovoNome;
}

void Conto::setId(int nuovoId) {
    id = nuovoId;
}

void Conto::setFondi(float nuoviFondi) {
    fondi = nuoviFondi;
}
