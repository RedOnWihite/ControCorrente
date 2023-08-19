#include <iostream>
#include "Conto.h"
/*versione 1.2.1 è stato aggiunto la possibilita di eliminare un conto */
using namespace std;

int main() {
    int scelta;
    int value;
    float soldi;
    string nome;
    string password;
    string stringTmp;

    while (true) {
        cout << "\nSalve, cosa vuole fare:\n1-crea un nuovo conto\n2-accedi al tuo conto" << endl;

        while (!(cin >> scelta)) {
            cin.clear(); // Ripristina lo stato di cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora il resto dell'input non valido
            cout << "Input non valido. Riprova: ";
        }

        if (scelta == 1) {
            cout << "Inserisca il nome per il conto: ";
            cin >> nome;

            if (filesystem::exists(nome)) {
                cout << "Il conto esiste gia'." << endl;
                continue;
            } else {
                cout << "Inserisca la password per il conto: ";
                cin >> password;
            }
            break;

        } else if (scelta == 2) {
            cout << "Inserisca il nome del conto: ";
            cin >> nome;
            if (filesystem::exists(nome)) {
                cout << "Inserisca la password del conto: ";
                cin >> password;
            } else {
                cout << "Errore: il conto non esiste";
                continue;
            }
            break;

        } else {
            cout << "Scelta non valida." << endl;
            continue;
        }
    }

        Conto conto(nome, password);

    cout << "\n\ninformazioni del conto: \nnome: "<<conto.getName() << "\ntransazioni: " <<conto.getId()<<"\nsaldo contabile: "<< conto.getFondi() << endl;

    while (true) {
        cout << "\nche azione vuole eseguire?\n"
                "1-transazione\n"
                "2-visualizza estratto conto\n"
                "3-elimina una transazione\n"
                "4-cambia il nome del conto\n"
                "5-cambia il password del conto\n"
                "6-elimina il conto\n"
                "7-termina programma\n" << endl;        while (!(cin >> value)) {
            cin.clear(); // Ripristina lo stato di cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora il resto dell'input non valido
            cout << "\nInput non valido. Riprova: ";
        }
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
                cout << "inserisca il nuovo nome per il conto" << endl;
                cin >> nome;
                if (filesystem::exists(nome)) {
                    cout << "esiste gia' un conto con lo stesso nome." << endl;
                    continue;
                } else {
                    conto.changeName(nome);
                    conto.salvaDatiSuFile(nome);
                }
                break;
            }
            case 5: {
                cout << "inserisca il nuovo password per il conto" << endl;
                cin >> stringTmp;
                conto.changePsw(stringTmp);
                conto.salvaDatiSuFile(nome);
                break;
            }
            case 6: {
                cout << "sei sicuro di volor eliminare il conto?\n1-si 2-no\n" << endl;
                cin >> scelta;
                if(scelta==1){
                    cout << "inserisca il password" << endl;
                    cin >> stringTmp;
                    if(conto.getPassword()==stringTmp){
                        conto.eliminaConto();
                        exit(0);
                    }
                    else{
                        cout << "password errato" << endl;
                        break;
                    }
                }
                break;
            }
            case 7: {
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