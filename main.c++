#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

const int MAX_PRODOTTI = 100;
const int MAX_MOVIMENTI = 1000;
const char FILE_BACKUP[] = "inventario.txt";

struct Prodotto {
    string codice;
    string nome;
    int quantita;
    double prezzo;
};

struct Movimento {
    string codiceProdotto;
    string tipo;
    int quantita;
    string data;
};

struct Ordine {
    string codiceProdotto;
    int quantitaOrdinata;
    string dataOrdine;
};

Prodotto inventario[MAX_PRODOTTI];
Movimento movimenti[MAX_MOVIMENTI];
Ordine ordini[MAX_PRODOTTI];

int numProdotti = 0;
int numMovimenti = 0;
int numOrdini = 0;

int trovaProdotto(string codice) {
    for (int i = 0; i < numProdotti; i++) {
        if (inventario[i].codice == codice) {
            return i;
        }
    }
    return -1;
}

void aggiungiProdotto() {
    if (numProdotti >= MAX_PRODOTTI) {
        cout << "Magazzino pieno!\n";
        return;
    }

    Prodotto p;
    cout << "Codice prodotto: ";
    cin >> p.codice;

    if (trovaProdotto(p.codice) != -1) {
        cout << "Prodotto gia' esistente!\n";
        return;
    }

    cin.ignore();
    cout << "Nome: ";
    getline(cin, p.nome);
    cout << "Quantita iniziale: ";
    cin >> p.quantita;
    cout << "Prezzo unitario: ";
    cin >> p.prezzo;

    inventario[numProdotti++] = p;
    cout << "Prodotto aggiunto con successo!\n";
}

void registraMovimento() {
    if (numMovimenti >= MAX_MOVIMENTI) {
        cout << "Limite movimenti raggiunto!\n";
        return;
    }

    string codice;
    cout << "Codice prodotto: ";
    cin >> codice;

    int idx = trovaProdotto(codice);
    if (idx == -1) {
        cout << "Prodotto non trovato!\n";
        return;
    }

    Movimento m;
    m.codiceProdotto = codice;

    cout << "Tipo movimento (E=Entrata, U=Uscita): ";
    char tipo;
    cin >> tipo;

    if (tipo == 'E' || tipo == 'e') {
        m.tipo = "ENTRATA";
    } else if (tipo == 'U' || tipo == 'u') {
        m.tipo = "USCITA";
    } else {
        cout << "Tipo non valido!\n";
        return;
    }

    cout << "Quantita: ";
    cin >> m.quantita;

    if (m.tipo == "USCITA" && m.quantita > inventario[idx].quantita) {
        cout << "Quantita insufficiente!\n";
        return;
    }

    cout << "Data (formato GG/MM/AAAA): ";
    cin >> m.data;

    if (m.tipo == "ENTRATA") {
        inventario[idx].quantita += m.quantita;
    } else {
        inventario[idx].quantita -= m.quantita;
    }

    movimenti[numMovimenti++] = m;
    cout << "Movimento registrato!\n";
}

void verificaOrdini() {
    for (int i = 0; i < numProdotti; i++) {
        if (numOrdini < MAX_PRODOTTI) {
            ordini[numOrdini].codiceProdotto = inventario[i].codice;
            
            cout << "Data ordine (formato GG/MM/AAAA): ";
            cin >> ordini[numOrdini].dataOrdine;
            
            numOrdini++;
            cout << "Generato ordine per: " << inventario[i].nome << endl;
        }
    }
}

void stampaReport() {
    cout << "=====================================  REPORT INVENTARIO  =====================================" << endl;
    cout << "CODICE" << setw(30) << "NOME" 
         << setw(10) << "QTA" << setw(15) << "PREZZO" << endl;

    for (int i = 0; i < numProdotti; i++) {
        cout << setw(10) << inventario[i].codice 
             << setw(30) << inventario[i].nome 
             << setw(10) << inventario[i].quantita 
             << setw(15) << fixed << setprecision(2) << inventario[i].prezzo << endl;
    }
    
    cout << "\n=============================================================================================" << endl;
    cout << "\n========================================  MOVIMENTI  ========================================" << endl;
    for (int i = 0; i < numMovimenti; i++) {
        cout << movimenti[i].data << " - " 
             << movimenti[i].codiceProdotto << " - " 
             << movimenti[i].tipo << " - " 
             << movimenti[i].quantita << endl;
    }

    cout << "\n=============================================================================================" << endl;
    cout << "\n=====================================  ORDINI IN CORSO  =====================================" << endl;
    for (int i = 0; i < numOrdini; i++) {
        cout << ordini[i].dataOrdine << " - " 
             << ordini[i].codiceProdotto << " - " 
             << ordini[i].quantitaOrdinata << endl;
    }
    cout << "\n=============================================================================================" << endl;
}

void salvaBackup() {
    ofstream file(FILE_BACKUP);
    if (!file) {
        cout << "Errore apertura file!\n";
        return;
    }

    // Intestazione prodotti
    file << "========================================   PRODOTTI   ========================================" << endl;
    file << setw(20) << left << "CODICE" << "| "
         << setw(20) << left << "Nome" << "| "
         << setw(15) << left << "QTA" << "| "
         << setw(10) << left << "PREZZO" << endl;
    
    for (int i = 0; i < numProdotti; i++) {
        file << setw(20) << left << inventario[i].codice << "| "
             << setw(20) << left << inventario[i].nome << "| "
             << setw(15) << left << inventario[i].quantita << "| "
             << setw(10) << left << fixed << setprecision(2) << inventario[i].prezzo << endl;
    }

    // Intestazione movimenti
    file << "\n========================================   MOVIMENTI   ========================================" << endl;
    file << setw(20) << left << "CODICE" << "| "
         << setw(20) << left << "Tipo" << "| "
         << setw(15) << left << "QTA" << "| "
         << setw(10) << left << "Data" << endl;
    
    for (int i = 0; i < numMovimenti; i++) {
        file << setw(20) << left << movimenti[i].codiceProdotto << "| "
             << setw(20) << left << movimenti[i].tipo << "| "
             << setw(15) << left << movimenti[i].quantita << "| "
             << setw(10) << left << movimenti[i].data << endl;
    }

    // Intestazione ordini
    file << "\n========================================   ORDINI   ========================================" << endl;
    file << setw(20) << left << "CODICE" << "| "
         << setw(15) << left << "QTA" << "| "
         << setw(10) << left << "Data" << endl;
    
    for (int i = 0; i < numOrdini; i++) {
        file << setw(20) << left << ordini[i].codiceProdotto << "| "
             << setw(15) << left << ordini[i].quantitaOrdinata << "| "
             << setw(10) << left << ordini[i].dataOrdine << endl;
    }

    file.close();
    cout << "Backup salvato con successo!\n";
}

void caricaBackup() {
    ifstream file(FILE_BACKUP);
    if (!file) {
        cout << "File non trovato! Inizializzato nuovo inventario.\n";
        return;
    }

    string linea;
    numProdotti = 0;
    numMovimenti = 0;
    numOrdini = 0;
    
    // Salta le intestazioni
    for (int i = 0; i < 3; i++) getline(file, linea);
    
    // Carica prodotti
    while (getline(file, linea)) {
        if (linea.empty() || linea.find("===") != string::npos) break;
        
        Prodotto p;
        size_t pos1 = linea.find('|');
        size_t pos2 = linea.find('|', pos1 + 1);
        size_t pos3 = linea.find('|', pos2 + 1);
        
        p.codice = linea.substr(0, pos1);
        p.codice.erase(p.codice.find_last_not_of(' ') + 1);
        
        p.nome = linea.substr(pos1 + 2, pos2 - pos1 - 2);
        p.nome.erase(p.nome.find_last_not_of(' ') + 1);
        
        p.quantita = stoi(linea.substr(pos2 + 2, pos3 - pos2 - 2));
        p.prezzo = stod(linea.substr(pos3 + 2));
        
        inventario[numProdotti++] = p;
    }
    
    // Salta le intestazioni movimenti
    for (int i = 0; i < 3; i++) getline(file, linea);
    
    // Carica movimenti
    while (getline(file, linea)) {
        if (linea.empty() || linea.find("===") != string::npos) break;
        
        Movimento m;
        size_t pos1 = linea.find('|');
        size_t pos2 = linea.find('|', pos1 + 1);
        size_t pos3 = linea.find('|', pos2 + 1);
        
        m.codiceProdotto = linea.substr(0, pos1);
        m.codiceProdotto.erase(m.codiceProdotto.find_last_not_of(' ') + 1);
        
        m.tipo = linea.substr(pos1 + 2, pos2 - pos1 - 2);
        m.tipo.erase(m.tipo.find_last_not_of(' ') + 1);
        
        m.quantita = stoi(linea.substr(pos2 + 2, pos3 - pos2 - 2));
        m.data = linea.substr(pos3 + 2);
        m.data.erase(m.data.find_last_not_of(' ') + 1);
        
        movimenti[numMovimenti++] = m;
    }
    
    // Salta le intestazioni ordini
    for (int i = 0; i < 3; i++) getline(file, linea);
    
    // Carica ordini
    while (getline(file, linea)) {
        if (linea.empty()) break;
        
        Ordine o;
        size_t pos1 = linea.find('|');
        size_t pos2 = linea.find('|', pos1 + 1);
        
        o.codiceProdotto = linea.substr(0, pos1);
        o.codiceProdotto.erase(o.codiceProdotto.find_last_not_of(' ') + 1);
        
        o.quantitaOrdinata = stoi(linea.substr(pos1 + 2, pos2 - pos1 - 2));
        o.dataOrdine = linea.substr(pos2 + 2);
        o.dataOrdine.erase(o.dataOrdine.find_last_not_of(' ') + 1);
        
        ordini[numOrdini++] = o;
    }

    file.close();
    cout << "Backup caricato con successo!\n";
}

void menuPrincipale() {
    char ripeti;
    int scelta;

    do {
        cout << "\n===================================== GESTIONE MAGAZZINO ====================================" << endl << endl;
        cout << "1. Aggiungi prodotto" << endl;
        cout << "2. Registra movimento" << endl;
        cout << "3. Genera ordini automatici" << endl;
        cout << "4. Stampa report" << endl;
        cout << "5. Salva backup" << endl;
        cout << "6. Carica backup" << endl;
        cout << "0. Esci" << endl;
        cout << "Scelta: ";
        cin >> scelta;

        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        switch(scelta) {
            case 1: aggiungiProdotto(); break;
            case 2: registraMovimento(); break;
            case 3: verificaOrdini(); break;
            case 4: stampaReport(); break;
            case 5: salvaBackup(); break;
            case 6: caricaBackup(); break;
            case 0: cout << "Arrivederci!\n"; break;
            default: cout << "Scelta non valida!\n"; break;
        }

        if (scelta != 0) {
            cout << "\nVuoi effettuare un'altra operazione? (S/N): ";
            cin >> ripeti;

            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
        } else {
            ripeti = 'N';
        }

    } while (ripeti == 'S' || ripeti == 's');
}

int main() {
    caricaBackup();
    menuPrincipale();
    return 0;
}