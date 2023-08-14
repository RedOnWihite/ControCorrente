#include <iostream>
#include "Conto.h"
/*versione 1.2 è stato aggiunto una funzione che chiede se si vuole fare un accesso o una registrazione e cerca se
 è già presente un account con lo stesso nome(unico) e implementa una nuova caratteristica, un password
 che protegge gli conti dei vari utenti
 fixed:
 -salvataggio del file contoCorrente
 -salvataggio del file conto
 -apertura dei file
 -rinominazione dei file*/

using namespace std;

int main() {
    int scelta;
    int value;
    float soldi;
    string nome;
    string password;

    while (true) {
        cout << "Salve, cosa vuole fare:\n1-crea un nuovo conto\n2-accedi al tuo conto" << endl;
        cin >> scelta;

        if (scelta == 1) {
            cout << "Inserisca il nome per il conto: ";
            cin >> nome;

            if (filesystem::exists(nome)) {
                cout << "Il conto esiste gia'." << endl;
                exit(0);
            } else {
                cout << "Inserisca la password per il conto: ";
                cin >> password;
            }
            break;

        } else if (scelta == 2) {
            cout << "Inserisca il nome del conto: ";
            cin >> nome;
            cout << "Inserisca la password del conto: ";
            cin >> password;
            break;

        } else {
            cout << "Scelta non valida." << endl;
            continue;
        }
    }

        Conto conto(nome, password);

    while (true) {
        cout << "\nche azione vuole eseguire?\n1-transazione\n2-visualizza estratto conto\n3-elimina una transazione\n4-termina programma\n" << endl;
        cin >> value;
        switch (value) {
            case 1: {
                cout << "cosa vuole fare? 1-prelievo 2-ricarica\n" << endl;
                cin >> value;
                cout << "quanti euro" << endl;
                cin >> soldi;
                switch (value) {
                    case 1: {
                        conto.transazione(-soldi);
                        break;
                    }
                    case 2: {
                        conto.transazione(soldi);
                        break;
                    }
                    default: {
                        cout << "Scelta non valida." << endl;
                        break;
                    }
                }
                break; // Aggiungi il break per uscire dallo switch esterno
            }
            case 2: {
                conto.stampaEC();
                break;
            }
            case 3: {
                conto.stampaEC();
                cout << "inserisca l'id della transazione da eliminare" << endl;
                cin>>value;
                conto.eliminaTransazione(value);
                break;
            }
            case 4: {
                cout << "programma terminato" << endl;
                conto.salvaDatiSuFile(nome);
                return 0;
            }
            default: {
                cout << "Scelta non valida." << endl;
                break;
            }
        }
    }
}