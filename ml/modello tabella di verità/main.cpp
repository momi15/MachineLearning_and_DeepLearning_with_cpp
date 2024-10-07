//main.cpp
#include "main.hpp"

// definisco i 4 oggetti in modo globale
neurone NeuroneAND, NeuroneOR, NeuroneNOR, NeuroneNAND;
/*
  questo è il set di dati per allenare i modelli 
  le prime 2 colonne rapresentano le varie combinazioni e
  la terza colonna rapresenta il risultato dei vari risultati delle operazioni logiche
  */
//set di dati per l'OR
float allenamento_or[][3] = {
    {0, 0, 0},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 1}
};
//set di dati per l'NOR
float allenamento_nor[][3] = {
    {0, 0, 1},
    {0, 1, 0},
    {1, 0, 0},
    {1, 1, 0}
};
//set di dati per l'AND
float allenamento_and[][3] = {
    {0, 0, 0},
    {0, 1, 0},
    {1, 0, 0},
    {1, 1, 1}
};
//set di dati per l'NAND
float allenamento_nand[][3] = {
    {0, 0, 1},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 0}
};
//funzione sigmoidea per comprimere il risultato tra 0 e 1 quindi questo si traduce in un risultato binario
float sigmoid(float x) {
    return 1.0f / (1 + expf(-x));
}
/*funzione che restituisce un vettore di tipo float da aggiungere ad un vettore
  di vettori di tipo float chiamato risultati 

  PS: questa funzione può calcolare solo AND,NAND,OR,NOR
  
  - l'array numero rappresenta gli indici delle colonne selezionate dall'utente
  - il vettore di vettori di tipo int sono le variabili scelte dall'utente
  - l'array tridimensionale rappresenta il set di dati su cui si allena il neurone
  - la variabile numero_bit rappresenta la lunghezza di una colonna */
std::vector<float> CalcoloDigitale(int numero[], const std::vector<std::vector<int>>& variabili, float allenamento[][3], neurone& tipo, int numero_bit) {
    //vettore float che contenerà il risultato
    std::vector<float> risultato;
    /*inizia l'allenamento del neurone che che viene passato nella variabile
     tipo il primo valore che viene passato dice che non vogliamo vedere i risultato degli allenamenti
     il secondo valore che viene passato è il set di dati su cui fare l'allenamento*/
    tipo.iniziallizzazione(false, allenamento);
    /*vengono defenite le variabili:
       w1 che rapresenta il peso del primo valore che viene fatto passare
       w2 che rapresenta il secondo peso del secondo valore che vine fatto passare
       b che rapresenta il bias un termine constante che serve per far addattare meglio il set di dati al modello
    */
    float w1 = tipo.GetW1(), w2 = tipo.GetW2(), b = tipo.GetB();
    //qua vengono fatti passare i valori su cui vogliamo fare l'operazione logica
    for (int j = 0; j < numero_bit; ++j) {
        /*si calcola il risultato dei dati che sono salvati in 
          variabili grazie alla formula della retta perchè è un modello di ML fatto con la regressione lineare
          quindi si fa la formula mx+q essendo che abbiamo 2 valori di entrata abbiamo 2 m quindi diventa 
          m₁*x₁+m₂*x₂+q e poi si fa la funzione sigmoidea in modo da avere dei dati che vadano da 0 a 1 */
        risultato.push_back(sigmoid(variabili[numero[0]][j] * w1 + variabili[numero[1]][j] * w2 + b ));
    }
    //si passa il risultato dei vari calcoli 
    return risultato;
}
//funzione per calcolare XOR 
std::vector<float> CalcoloDigitaleXOR(int numero[], const std::vector<std::vector<int>>& variabili, int numero_bit) {

    NeuroneAND.iniziallizzazione(false,allenamento_and);
    NeuroneNAND.iniziallizzazione(false,allenamento_nand);
    NeuroneOR.iniziallizzazione(false,allenamento_or);
    NeuroneNOR.iniziallizzazione(false,allenamento_nor);
    //definiamo la variabile vettore di tipo float che conterrà il risultato dell'operazione
    std::vector<float> risultato;
    /*si prendono i diversi pesi e bias delle varie operazioni logiche perchè
      per fare l'XOR dobbiamo usare questa formula (x|y) & !(x&y) 
      quindi prima facciamo un OR tra i 2 valori poi facciamo una NAND e poi con i risultati
       delle 2 operazioni logiche facciamo una AND e così avremo avuto una XOR*/
    float w1_OR = NeuroneOR.GetW1(), w2_OR = NeuroneOR.GetW2(), b_OR = NeuroneOR.GetB();
    float w1_NAND = NeuroneNAND.GetW1(), w2_NAND = NeuroneNAND.GetW2(), b_NAND = NeuroneNAND.GetB();
    float w1_AND = NeuroneAND.GetW1(), w2_AND = NeuroneAND.GetW2(), b_AND = NeuroneAND.GetB();
    //qua vengono fatti passare i valori su cui vogliamo fare l'operazione logica
    for (int j = 0; j < numero_bit; ++j) {
        //facciamo finta che vengono fatti passare i valori 1 0 e che vogliamo vedere cosa fa
        //si calcola l'OR e si salva il risultato in una variabile chiamata risultatoOR 
        float risultatoOR = sigmoid(variabili[numero[0]][j] * w1_OR + variabili[numero[1]][j] * w2_OR + b_OR); // 1 OR 0 = 1
        //si calcola l'NAND e si salva il risultato in una variabile chiamata risultatoNAND
        float risultatoNAND = sigmoid(variabili[numero[0]][j] * w1_NAND + variabili[numero[1]][j] * w2_NAND + b_NAND); // 1 NAND 0 = 1 
        //ora si calcola il risultato dell'operazione usando i precedenti risultati
        float risultatoAND = sigmoid(risultatoOR * w1_AND + risultatoNAND * w2_AND + b_AND); // 1 AND 1 = 1
        //viene salvato il valore di risultatoAND nel vettore risultato
        risultato.push_back(risultatoAND);
    }
    //viene restitutito il vettore risultato
    return risultato;
}
/*funzione per calcolare l'OR,l'NOR,l'AND e la NAND usando le veriabili e i precedenti risultati
  l'array numero rapresenta la colonna selezionata dall'utente il vettore di vettori di tipo int 
  sono le variabili scelte dall'utente l'array tridimensionale è il set di dati il tipo è il neurone
  dell'operazione scelta il vettore di tipo float risultato1 rapresenta il primo risultato selezionato
  dall'utente il vettore di tipo float risultato2 rapresenta il secondo risultato scelto dall'utente 
  se aveva scelto di usare un solo risultato viene fatto passare lo stesso risultato scelto dall'utente 
  tanto non verrà usato il bool ci dice se l'utente vuole usare uno o due risultati il numero_bit è quanto è lunga una colonna*/
std::vector<float> CalcoloDigitaleConRisultati(int numero[], const std::vector<std::vector<int>>& variabili, float allenamento[][3], neurone& tipo, const std::vector<float>& risultato1, const std::vector<float>& risultato2, bool piuRisultati, int numero_bit) {
    //definiamo la variabile vettore di tipo float che conterrà il risultato dell'operazione
    std::vector<float> risultato;
    //inizia l'allenamento del neurone sul set di dati
    tipo.iniziallizzazione(false, allenamento);
    //si prendono i diversi pesi e il bias
    float w1 = tipo.GetW1(), w2 = tipo.GetW2(), b = tipo.GetB();
    //vengono passati i valori su cui vogliamo fare il calcolo
    for (int j = 0; j < numero_bit; ++j) {
        //se ci sono più risultati vengono passati i 2 risultati scelti dal utente in precedenza
        if (piuRisultati) {
            risultato.push_back(sigmoid(risultato1[j] * w1 + risultato2[j] * w2 + b));
        }
        //altrimenti si passa la variabile scelta dall'utente e il risultato scelto dall'utente in precedenza
         else {
            //viene salvato il risultato nella variabile risultato 
            risultato.push_back(sigmoid(variabili[numero[0]][j] * w1 + risultato1[j] * w2 + b));
        }
    }
    //viene restituita la variabile risultato
    return risultato;
}
//funzione per calcolare XOR con uno o due risultati
std::vector<float> CalcoloDigitaleXOR(int numero[], const std::vector<std::vector<int>>& variabili, const std::vector<float>& risultato1, const std::vector<float>& risultato2, bool piuRisultati, int numero_bit) {
    //alleniamo tutti e 4 i neuroni con il loro set di dati
    NeuroneAND.iniziallizzazione(false,allenamento_and);
    NeuroneNAND.iniziallizzazione(false,allenamento_nand);
    NeuroneOR.iniziallizzazione(false,allenamento_or);
    NeuroneNOR.iniziallizzazione(false,allenamento_nor);
    //variabile in cui verrà salvato il risultato
    std::vector<float> risultato;
    //si prendono vari pesi e bias
    float w1_OR = NeuroneOR.GetW1(), w2_OR = NeuroneOR.GetW2(), b_OR = NeuroneOR.GetB();
    float w1_NAND = NeuroneNAND.GetW1(), w2_NAND = NeuroneNAND.GetW2(), b_NAND = NeuroneNAND.GetB();
    float w1_AND = NeuroneAND.GetW1(), w2_AND = NeuroneAND.GetW2(), b_AND = NeuroneAND.GetB();
    //se vuole fare con 2 risultati
    if (piuRisultati) {
        //for per far passare il valore di risultato1 e di risultato2
        for (int j = 0; j < numero_bit; ++j) {
            //si calcola l'OR e si salva il risultato
            float risultatoOR = sigmoid(risultato1[j] * w1_OR + risultato2[j] * w2_OR + b_OR);
            //si calcola l'NAND e si salva il risultato
            float risultatoNAND = sigmoid(risultato1[j] * w1_NAND + risultato2[j] * w2_NAND + b_NAND);
            //si calcola l'AND e si salva il risultato
            float risultatoAND = sigmoid(risultatoOR * w1_AND + risultatoNAND * w2_AND + b_AND);
            //si salva il risultato dell'AND in risultato
            risultato.push_back(risultatoAND);
        }
    } //se vuole usare un solo risultato
    else {
        //for per far passare il valore di varibili della colonna selezionata e di risultato1
       for (int i = 0; i < numero_bit; ++i) {
            //si calcola l'OR e si salva il risultato
            float risultatoOR = sigmoid(variabili[numero[0]][i] * w1_OR + risultato1[i] * w2_OR + b_OR);
            //si calcola l'NAND e si salva il risultato
            float risultatoNAND = sigmoid(variabili[numero[0]][i] * w1_NAND + risultato1[i] * w2_NAND + b_NAND);
            //si calcola l'AND e si salva il risultato
            float risultatoAND = sigmoid(risultatoOR * w1_AND + risultatoNAND * w2_AND + b_AND);
            //si salva il risultato dell'AND in risultato
            risultato.push_back(risultatoAND);
        }
    }
    //si restituisce il risultato
    return risultato;
}
//funzione per la gestione delle operazioni logihe OR,NOR,AND,NAND
void gestione_risposte(std::vector<std::vector<float>>& risultati, int numero[], const std::vector<std::vector<int>>& variabili, float allenamento[][3], neurone& tipo, std::vector<float>& supRisultati, int numero_bit, int numero_variabili) {
    //variabile che avrà le risposte dell'utente
    std::string operazione;
    //vettore che avrà il numero delle colonne selezionate
    std::vector<int> NumeroRisultato(2);
    //se il vettore risultati non è vuoto
    if (!risultati.empty()) {
        std::cout << "\nVuoi lavorare con i precedenti risultati? Se sì, scrivere 'si', altrimenti scrivere 'no'\n";
        std::cin >> operazione;
        //se l'utente scrive si e c'è più di un risultato salvato
        if (operazione == "si"&&risultati.size()>1) {
            std::cout << "\nVuoi lavorare con più risultati?\n";
            std::cin >> operazione;
            //se scrive si
            if (operazione == "si") {
                std::cout << "\nScrivi il primo risultato: ";
                std::cin >> NumeroRisultato[0];
                //viene fatto -1 perchè il vettore conta da 0 l'utente parte da 1
                NumeroRisultato[0] -= 1;
                std::cout << "\nScrivi il secondo risultato: ";
                std::cin >> NumeroRisultato[1];
                NumeroRisultato[1] -= 1;
                //viene chiamata la funzione e salva il valore nella variabile di supporto supRisultati
                supRisultati = CalcoloDigitaleConRisultati(numero, variabili, allenamento, tipo, risultati[NumeroRisultato[0]], risultati[NumeroRisultato[1]], true, numero_bit);
            } // se scrive qualcosa diversa da si
            else {
                // se sono salvati più risultati
                if(risultati.size()>1){
                    std::cout << "\nCon quale risultato vuoi lavorare?";
                    std::cin >> NumeroRisultato[0];
                    NumeroRisultato[0] -= 1;
                    }
                    //se è salvato un solo risultato
                    else{
                        std::cout<<"e' stato preso l'unico risultato salvato!";
                        NumeroRisultato[0]=0;
                    }
                std::cout<<"\n con quale variabile vuoi lavorare?";
                std::cin>>numero[0];
                numero[0]-=1;
                //viene chiamata la funzione il cui risultato viene salvato in supRisultati
                supRisultati = CalcoloDigitaleConRisultati(numero, variabili, allenamento, tipo, risultati[NumeroRisultato[0]], risultati[NumeroRisultato[0]], false, numero_bit);
            }
        } else {
            std::cout<<"e' stato preso l'unico risisultato salvato!";
            NumeroRisultato[0]=0;
            std::cout<<"\n con quale variabile vuoi lavorare?";
            std::cin>>numero[0];
            numero[0]-=1;
            //viene chiamata la funzione il cui risultato viene salvato in supRisultati
            supRisultati = CalcoloDigitaleConRisultati(numero, variabili, allenamento, tipo, risultati[NumeroRisultato[0]], risultati[NumeroRisultato[0]], false, numero_bit);
        }
    } else {
        //viene chiamata la funzione il cui risultato viene salvato in supRisultati
        supRisultati = CalcoloDigitale(numero, variabili, allenamento, tipo, numero_bit);
    }
    //viene salvato i valori di supRisultati
    risultati.push_back(supRisultati);
}
//funzione principale
int main() {
    NeuroneAND.iniziallizzazione(false,allenamento_and);
    NeuroneNAND.iniziallizzazione(false,allenamento_nand);
    NeuroneOR.iniziallizzazione(false,allenamento_and);
    NeuroneNOR.iniziallizzazione(false,allenamento_and);
    //nella prima variabile verrà salvato il numero di variabili
    //nella seconda variabile verrà usata per prendere i valori(delle variabili) scritti dall'utente 
    int numero_variabili = 0, dato=0;
    //verrà usata per prendere le risposte dall'utente
    std::string risposta;
    //scritta fatta con gli ansi code in questo caso serve per fare la scritta in grassetto e colorata ecco una fonte molto
    // utile per vedere tutte le potenzialità degli ansi code https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
    std::cout << "\n\033[1;33m BENVENUTO NELLA INTELLIGENZA ARTIFICIALE CHE TI CALCOLA LA TABELLA DI VERITA'\033[0;0m\n";
    //do while che controlla che ci siano almeno 2 variabili 
    do{
    std::cout << "\nScrivi quante variabili vuoi usare\n";
    std::cin >> numero_variabili;
    if(numero_variabili<2){
        std::cout<<"\n \033[1;31m devono essere 2 o piu' variabili per ovvie ragioni \033[0;0m \n";
    }
    }while(numero_variabili<2);
    //si calcola il numero di bit che ci dovrebbero essere
    int numero_bit = pow(2, numero_variabili-1);
    //viene definita la variabile che conterà il valore delle variabili definendo anche la sua grandezza
    std::vector<std::vector<int>> variabili(numero_variabili, std::vector<int>(numero_bit));
    //variabile in cui veranno salvati i vari risultati
    std::vector<std::vector<float>> risultati;
    //variabile di supporto in cui verrano salvati i risultati delle singole operazioni che poi verranno salvate in risultati
    std::vector<float> supRisultati;
    //2 for concatenati per far scorrere il vettore e poter salvare i valori al suo interno
    for (int i = 0; i < numero_variabili; ++i) {
        std::cout << "Scrivi i bit della colonna numero " << i+1 << ":\n";
        for (int j = 0; j < numero_bit; ++j) {
            std::cin >> dato;
            //controlla se dato è diverso da 0 o 1 e se è diverso chiede che venga ri scritto 
            while (dato != 0 && dato != 1) {
                std::cout << "\033[1;33m Ripetere il numero perchè non è un numero binario\n\033[0;0m";
                std::cin >> dato;
            }
            variabili[i][j] = dato;
        }
    }
    //ciclo infinito
    while (true) {
        //variabile in cui verrà salvato la colonna selezionata
        int numero[2] = {0, 1};
        std::cout << "Quale operazione vuoi fare?\n";
        //continua a chiedere l'operazione fino a quando è diversa da AND,NAND,OR o XOR 
        do {
            std::cin >> risposta;
        } while (risposta != "and" && risposta != "AND" && risposta != "And" &&
                 risposta != "Nand" && risposta != "NAND" && risposta != "nand" &&
                 risposta != "or" && risposta != "OR" && risposta != "Or" &&
                 risposta != "nor" && risposta != "NOR" && risposta != "Nor" &&
                 risposta != "Xor" && risposta != "XOR" && risposta != "xor");
        //se il numero di variabili è superiore a 2 e se non ci sono risultati salvati
        if (numero_variabili >2&& risultati.empty()) {
            std::cout << "\nSu quali variabili vuoi lavorare?\n";
            std::cout << "Scrivi la prima variabile\n";
            std::cin >> numero[0];
            std::cout << "Scrivi la seconda variabile\n";
            std::cin >> numero[1];
            numero[0] -= 1;
            numero[1] -= 1;
        }
        //se ci sono solo 2 risultati per il momento si prendono le prime 2 colonne
        else{
            numero[0]=0;
            numero[1]=1;
        }
        //filtra la risposta dell'utente e vede che operazione voleva fare poi chiama la funzione passando i valori necessari
        if (risposta == "and" || risposta == "AND" || risposta == "And") {
            gestione_risposte(risultati, numero, variabili, allenamento_and, NeuroneAND, supRisultati, numero_bit, numero_variabili);
        } else if (risposta == "nand" || risposta == "NAND" || risposta == "Nand") {
            gestione_risposte(risultati, numero, variabili, allenamento_nand, NeuroneNAND, supRisultati, numero_bit, numero_variabili);
        } else if (risposta == "or" || risposta == "OR" || risposta == "Or") {
            gestione_risposte(risultati, numero, variabili, allenamento_or, NeuroneOR, supRisultati, numero_bit, numero_variabili);
        } else if (risposta == "nor" || risposta == "NOR" || risposta == "Nor") {
            gestione_risposte(risultati, numero, variabili, allenamento_nor, NeuroneNOR, supRisultati, numero_bit, numero_variabili);
        } else if (risposta == "xor" || risposta == "XOR" || risposta == "Xor") {
            //se è salvato almeno un risultato
            if (!risultati.empty()) {
                std::cout << "\nVuoi lavorare con i precedenti risultati? Se sì, scrivere 'si', altrimenti scrivere 'no'\n";
                std::cin >> risposta;
                //se scrive si e ci sono più risultati salvati
                if (risposta == "si"&&risultati.size()>1) {
                    std::cout << "\nVuoi lavorare con più risultati?\n";
                    std::cin >> risposta;
                    if (risposta == "si") {
                        //conteranno il numero della colonna selezionato dall'utente
                        int NumeroRisultato1, NumeroRisultato2;
                        std::cout << "\nScrivi il primo risultato: ";
                        std::cin >> NumeroRisultato1;
                        std::cout << "\nScrivi il secondo risultato: ";
                        std::cin >> NumeroRisultato2;
                        //si prende il risultato della funzione faccendo passare le corrette colonne con i risultati scelti facendo -1 perchè il vettore parte da 0 l'utente in genere no e poi si salva in supRisultati
                        supRisultati = CalcoloDigitaleXOR(numero, variabili, risultati[NumeroRisultato1 - 1], risultati[NumeroRisultato2 - 1], true, numero_bit);
                    }
                    //se ha scritto una cosa diversa dal si o se è salvato un solo risultato
                    else {
                        //conterrà la colonna del vettore risultato desiderata
                        int NumeroRisultato;
                        std::cout << "\nCon quale risultato vuoi lavorare?";
                        std::cin >> NumeroRisultato;
                        NumeroRisultato -= 1;
                        std::cout<<"\n con quale variabile vuoi lavorare?";
                        std::cin>>numero[0];
                        //si prende il risultato e lo si salva in supRisultati
                        supRisultati = CalcoloDigitaleXOR(numero, variabili, risultati[NumeroRisultato - 1], risultati[NumeroRisultato - 1], false, numero_bit);
                    }
                    //si salva il risultato nel vettore di vettori risultati
                    risultati.push_back(supRisultati);
                }
                //se è salvato un unico risultato
                else if(risultati.size()==1){
                    int NumeroRisultato;
                    std::cout<<"e' stato preso l'unico risisultato salvato!";
                    NumeroRisultato=0;
                    std::cout<<"\n con quale variabile vuoi lavorare?";
                    std::cin>>numero[0];
                    numero[0]-=1;
                    //si salva in supRisultati
                    supRisultati = CalcoloDigitaleXOR(numero, variabili, numero_bit);
                    //si salva in Risultati
                    risultati.push_back(supRisultati);
                } else {
                    //si salva in supRisultati
                    supRisultati = CalcoloDigitaleXOR(numero, variabili, numero_bit);
                    //si salva in Risultati
                    risultati.push_back(supRisultati);
                }
        }//se non ci sono risultati salvati
        else{
            supRisultati = CalcoloDigitaleXOR(numero, variabili, numero_bit);
            risultati.push_back(supRisultati);
        }
        }
        // si stampa il risultato
        std::cout << "\nRisultato: \n";
        //si stampa il risultato 
        for (float r : supRisultati) {
            //si arrotonda il risultato per averlo con solo o 0 o 1 quindi senza numeri con la virgola
            std::cout <<std::round(r) <<std::endl;
        }
        std::cout << "\n\nVuoi continuare? (si/no)\n";
        std::cin >> risposta;
        //se si scrive qualcosa differente dal si si blocca il tutto
        if (risposta != "si") {
            break;
        }
    }

    return 0;
}
