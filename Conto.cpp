#include "Conto.h"

using namespace std;

Conto::Conto(const string& nomeUtente)
        : nome(nomeUtente), id(generaNuovoId()), fondi(0) {
    namespace fs = std::filesystem;
    if (fs::create_directory(nomeUtente)) {
        std::cout << "Il conto e' stato creato con successo\n";
    } else {
        std::cout << "Errore nella creazione del conto\n";
        exit(0);
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
    while (estrattoContoFile >> id >> value) {
        record.push_back(EstrattoConto(id, value)); // Crea e aggiungi un nuovo oggetto EstrattoConto al vettore record
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
        estrattoContoFile << elemento.getTipo() << "\n";
    }

    estrattoContoFile.close();
}

void Conto::transazione(float amount){
    if (amount < 0) {
        cout << "e' stato prelevato: " << -amount << " euro dal conto" << endl;
    } else {
        cout << "sono stati depositati: " << amount << " euro sul conto" << endl;
    }
    fondi += amount;

    // Incrementa l'ID
    ++id;

    // Crea un nuovo oggetto EstrattoConto con l'ID e il valore aggiornati, e aggiungilo al vettore record
    record.push_back(EstrattoConto(id, amount));
}

void Conto::stampaEC() {
    for (const auto& elemento : record) {
        std::cout << "ID: " << elemento.getId() << ", Valore: " << elemento.getValue() << ", tipo: " << elemento.getTipo() <<std::endl;
    }
}

void Conto::eliminaTransazione(int id) {
    auto it = record.begin();
    while (it != record.end()) {
        if (it->getId() == id) {
            record.erase(it); // Elimina l'elemento
            return; // Termina prematuramente la funzione
        } else {
            ++it; // Passa all'elemento successivo
        }
    }
    cout << "Errore: non e' stato trovato l'elemento desiderato" << endl;
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