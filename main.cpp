#include <iostream>
#include "Conto.h"

using namespace std;

int main() {
    int value;
    float soldi;
    string nome;
    cout << "inserisca il nome per il conto" << endl;
    cin >> nome;
    Conto conto(nome);
    while (true) {
        cout << "che azione vuole eseguire?\n1-transazione\n2-visualizza estratto conto\n3-termina programma" << endl;
        cin >> value;
        switch (value) {
            case 1: {
                cout << "cosa vuole fare? 1-prelievo 2-ricarica" << endl;
                cin >> value;
                cout << "quanti soldi" << endl;
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
                cout << "programma terminato" << endl;
                return 0;
            }
            default: {
                cout << "Scelta non valida." << endl;
                break;
            }
        }
    }
}