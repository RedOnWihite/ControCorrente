#include <iostream>
#include "Conto.h"
/*versione 1.1 aggiunta di una funzione per eliminazione di una trasazione nell'estratto conto, e aggiunto di un
attributo che descrive il tipo di transazione ed è stato sistemato un problema con l'incrementazione dei id*/

using namespace std;

int main() {
    int value;
    float soldi;
    string nome;
    cout << "inserisca il nome per il conto" << endl;
    cin >> nome;
    Conto conto(nome);
    while (true) {
        cout << "che azione vuole eseguire?\n1-transazione\n2-visualizza estratto conto\n3-elimina una transazione\n4-termina programma" << endl;
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
                conto.stampaEC();
                cout << "inserisca l'id della transazione da eliminare" << endl;
                cin>>value;
                conto.eliminaTransazione(value);
                break;
            }
            case 4: {
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