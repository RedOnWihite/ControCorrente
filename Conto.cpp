#include "Conto.h"

using namespace std;

Conto::Conto(const string& nomeUtente, const string& password)
        : nome(nomeUtente), password(password), id(generaNuovoId()), fondi(0) {
    namespace fs = filesystem;

    if (fs::exists(nomeUtente + "/Conto.txt")) {
        caricaDatiDaFile(nomeUtente);

        if (password != getPassword()) {
            cout << "Password errata. Accesso non consentito." << endl;
            exit(0);
        }
    } else {
        if (fs::create_directory(nomeUtente)) {
            cout << "Il conto e' stato creato con successo" << endl;
            salvaDatiSuFile(nomeUtente);
        } else {
            cout << "Errore nella creazione del conto" << endl;
            exit(0);
        }
    }
}

void Conto::caricaDatiDaFile(const string& nomeFile) {
    // Caricamento dei dati del conto
    ifstream inputFile(nomeFile + "/Conto.txt");
    if (!inputFile) {
        cerr << "Errore nell'apertura del file " << nomeFile << endl;
        exit(0);
        return;
    }

    inputFile >> nome;
    inputFile >> password;
    inputFile >> id;
    inputFile >> fondi;

    inputFile.close();

    // Caricamento dell'estratto conto
    ifstream estrattoContoFile(nomeFile + "/EstrattoConto.txt");
    if (!estrattoContoFile) {
        cerr << "Errore nell'apertura del file EstrattoConto.txt" << endl;
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


void Conto::salvaDatiSuFile(const string &nomeFile) const {
    // Salvataggio dei dati del conto
    ofstream outputFile(nomeFile + "/Conto.txt");
    if (!outputFile.is_open()) {
        cerr << "Errore nell'apertura del file " << nomeFile << endl;
        return;
    }

    outputFile << nome << "\n";
    outputFile << password << "\n";
    outputFile << id << "\n";
    outputFile << fondi << "\n";

    outputFile.close();

    // Salvataggio dell'estratto conto
    string nomeEstrattoConto = "/EstrattoConto.txt";
    ofstream estrattoContoFile(nomeFile + nomeEstrattoConto);
    if (!estrattoContoFile.is_open()) {
        std::cerr << "Errore nell'apertura del file " << nomeEstrattoConto << endl;
        return;
    }

    for (const auto& elemento : record) {
        estrattoContoFile << elemento.getId() << "\n";
        estrattoContoFile << elemento.getValue() << "\n";
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
        cout << "ID: " << elemento.getId() << ", Valore: " << elemento.getValue() << ", tipo: " << elemento.getTipo() <<endl;
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

void Conto::setNome(const std::string &nuovoNome) {
    const string directory = filesystem::current_path().string();  // Ottieni il percorso della directory corrente
    const string oldName = nome + "/" + nome + ".txt";  // Nome del file originale con percorso completo
    const string newName = nome + "/" + nuovoNome + ".txt";    // Nuovo nome desiderato con percorso completo

    // Utilizza std::rename() per rinominare il file
    if (rename(oldName.c_str(), newName.c_str()) == 0) {
        cout << "Il file è stato rinominato con successo." << endl;
    } else {
        cerr << "Errore nella rinomina del file." << endl;
    }
}

void Conto::setFondi(float nuoviFondi) {
    fondi = nuoviFondi;
}

string Conto::getPassword() {
    return password;
}