/* Ovaj program napravljen je u sklopu projekta iz kolegija Operacijska Istraživanja 2.
 * Program rješava problem nabave.
 * Autor: Josip Žemberi 
 * Fakultet Organizacije i Informatike, lipanj 2013.
 */
#include <iostream>
#include <fstream>

using namespace std;
char ime_datoteke[40];
fstream dat;

int glavniIzbornik(){
    int izbor;
    bool ok = true;
    do{
        cout << endl << "IZBORNIK" << endl << endl;
        cout << " 1. Rucno postavljanje zadatka" << endl << endl;
        cout << " 2. Ucitavanje zadatka iz tekstualne datoteke" << endl << endl;
        cout << " 9. Izlaz" << endl << endl;
        cout << " Izbor: ";
        cin >> izbor;
        if(!cin){
             ok = false;
             cin.clear();
             cin.ignore();
             cout << "Greska >> Potrebno je upisati broj!" << endl;
        } 
        else if (izbor != 1 && izbor != 2 && izbor != 9) ok = false;
        else ok = true;
    }while(!ok);    
    return izbor;
}

int main(){
    int broj_razdoblja; 
    int maksimalna_kolicina_nabave;
    int rata_povecanja_kolicine_nabave;
    int trosak_nabave;
    int maksimalan_kapacitet_skladista;
    int trosak_skladista_po_jedinici;
    int *potraznja;
    bool ok = true; // za kontrolu unosa dali je ok
    int izbor;
    
    cout << endl << "--------------------------------------------------------------------------------" << endl;
    cout << " Operacijska istrazivanja 2" << endl << endl;
    cout << " Dinamicko programiranje: Problem nabave" << endl << endl;
    cout << " Autor: Josip Zemberi" << endl << endl;
    cout << " Fakultet organizacije i informatike, lipanj 2013." << endl;
    cout << endl << "--------------------------------------------------------------------------------" << endl;
    cout << " U slucaju da se nakon izracuna ne prikazu svi koraci pritisnite alt + space" << endl << endl;
    cout << " Odaberite 'Properties'" << endl << endl;
    cout << " Odaberite tab 'Layout'" << endl << endl;
    cout << " Povecajte 'Height' u dijelu 'Screen Buffer Size' na npr. 1000" << endl << endl;
    cout << " Ponovno postavite zadatak (unesite podatke)" << endl;  
    cout << endl << "--------------------------------------------------------------------------------" << endl;
    
     do{   
        izbor = glavniIzbornik();
        switch(izbor){
            case 1:{
                // unos potrebnih podataka (zadavanje zadatka)
                cout << endl << "POSTAVLJANJE ZADATKA" << endl << endl;
                do{
                    cout << "Broj razdoblja: ";
                    cin >> broj_razdoblja;
                    if(!cin){
                         broj_razdoblja = 0;
                         cin.clear();
                         cin.ignore();
                         cout << "Greska >> Potrebno je upisati broj!" << endl;
                    } 
                    else if(broj_razdoblja == 0){
                        cout << "Greska >> Broj razdoblja ne moze biti 0!" << endl;
                    }
                }while(broj_razdoblja == 0);
                
                potraznja = new int[broj_razdoblja];
                
                for(int i = 0; i < broj_razdoblja; i++){
                    do{
                        cout << endl << "Potraznja za razdoblje " << i + 1 << ": ";
                        cin >> potraznja[i];
                        
                        if(!cin){
                         ok = false;
                         cin.clear();
                         cin.ignore();
                         cout << "Greska >> Potrebno je upisati broj!" << endl;
                        } 
                        else ok = true;
                                    
                    }while(!ok);   
                }
                
                do{
                    cout << endl << "Rata povecanja kolicine nabave: ";
                    cin >> rata_povecanja_kolicine_nabave;
                    if(!cin){
                         rata_povecanja_kolicine_nabave = 0;
                         cin.clear();
                         cin.ignore();
                         cout << "Greska >> Potrebno je upisati broj!" << endl;
                    } 
                    else if(rata_povecanja_kolicine_nabave == 0){
                        cout << "Greska >> Rata povecanja kolicine nabave ne moze biti 0!" << endl;
                    }
                }while(rata_povecanja_kolicine_nabave == 0);
                
                do{
                    cout << endl << "Maksimalna kolicina nabave: ";
                    cin >> maksimalna_kolicina_nabave;
                    if(!cin){
                         maksimalna_kolicina_nabave = 0;
                         cin.clear();
                         cin.ignore();
                         cout << "Greska >> Potrebno je upisati broj!" << endl;
                    } 
                    else if(maksimalna_kolicina_nabave == 0){
                        cout << "Greska >> Maksimalna kolicina nabave ne moze biti 0!" << endl;
                    }
                }while(maksimalna_kolicina_nabave == 0);       
                
                do{
                    cout << endl << "Trosak jedne nabave: ";
                    cin >> trosak_nabave;
                    
                    if(!cin){
                     ok = false;
                     cin.clear();
                     cin.ignore();
                     cout << "Greska >> Potrebno je upisati broj!" << endl;
                    } 
                    else ok = true;                    
                }while(!ok);  
                
                do{
                    cout << endl << "Maksimalan kapacitet skladista: ";
                    cin >> maksimalan_kapacitet_skladista;
                    if(!cin){
                         maksimalan_kapacitet_skladista = 0;
                         cin.clear();
                         cin.ignore();
                         cout << "Greska >> Potrebno je upisati broj!" << endl;
                    } 
                    else if(maksimalan_kapacitet_skladista == 0){
                        cout << "Greska >> Maksimalan kapacitet skladista ne moze biti 0!" << endl;
                    }
                }while(maksimalan_kapacitet_skladista == 0);
                
                do{
                    cout << endl << "Trosak skladistenja po jedinici robe: ";
                    cin >> trosak_skladista_po_jedinici;
                    if(!cin){
                     ok = false;
                     cin.clear();
                     cin.ignore();
                     cout << "Greska >> Potrebno je upisati broj!" << endl;
                    } 
                    else ok = true;                    
                }while(!ok);  
                
                
                break;
                }// case 1
            case 2:{
                cin.ignore();
                do{
                    cout << endl << "Naziv datoteke iz koje zelite ucitati zadatak: ";
                    cin.getline(ime_datoteke, 40);
                    
                    if(strlen(ime_datoteke) == 0){
                         strcpy(ime_datoteke, "z1.txt"); // za defoultno (ako se samo pritisne enter)
                         cout << endl << "Ucitavama datoteku... " << ime_datoteke << " (defaultan naziv)" << endl;
                    }
                    else cout << endl << "Ucitavama datoteku... " << ime_datoteke << endl;
                    dat.open(ime_datoteke, ios::in);
                    if(!dat){
                         cout << "Datoteku nije moguce otvoriti!" << endl << "Provjerite dali ste upisali tocan naziv" << endl;
                         dat.close();
                         dat.clear();
                         ok = false;
                    }
                    else ok = true;
                }while(!ok);
                char red[1000];
                int trenutni_red = 0;
                char podatak[100];
                cout << endl << "--------------------------------------------------------------------------------" << endl;
                cout << endl << "UCITANI ZADATAK" << endl << endl;
                while(1){
                    trenutni_red++;
                  dat.getline (red,1000,'\n');
                	char * naziv_varijable;
                    naziv_varijable = strtok (red, ":");
                    char * vrijednost_varijable;
                    vrijednost_varijable = strtok (NULL, ":");
                	
                	if(trenutni_red == 1){
                        broj_razdoblja = atoi(vrijednost_varijable);
                        cout << "Broj razdoblja: " << broj_razdoblja << endl << endl;
                        potraznja = new int[broj_razdoblja];
                    }
                    else if(trenutni_red > 1 && trenutni_red < broj_razdoblja+2){
                        potraznja[trenutni_red - 2] = atoi(vrijednost_varijable);
                        cout << "Potraznja za razdoblje "<< trenutni_red - 1 << ": " << potraznja[trenutni_red - 2] << endl << endl;
                    }
                    else if(trenutni_red == broj_razdoblja+2){
                        rata_povecanja_kolicine_nabave = atoi(vrijednost_varijable);
                        cout << "Rata povecanja kolicine nabave: " << rata_povecanja_kolicine_nabave << endl << endl; 
                    }
                    else if(trenutni_red == broj_razdoblja+3){
                        maksimalna_kolicina_nabave = atoi(vrijednost_varijable);
                        cout << "Maksimalna kolicina nabave: " << maksimalna_kolicina_nabave << endl << endl; 
                    }
                    else if(trenutni_red == broj_razdoblja+4){
                        trosak_nabave = atoi(vrijednost_varijable);
                        cout << "Trosak jedne nabave: " << trosak_nabave << endl << endl; 
                    }
                    else if(trenutni_red == broj_razdoblja+5){
                        maksimalan_kapacitet_skladista = atoi(vrijednost_varijable);
                        cout << "Maksimalni kapacitet skladista: " << maksimalan_kapacitet_skladista << endl << endl; 
                    }
                    else if(trenutni_red == broj_razdoblja+6){
                        trosak_skladista_po_jedinici = atoi(vrijednost_varijable);
                        cout << "Trosak skladistenja po jedinici robe: " << trosak_skladista_po_jedinici << endl << endl; 
                    }
                    
                    memset(red,0,strlen(red));
                	if (dat.eof()) break;
                }
                
                dat.close();
                dat.clear();
                break;
                }//case 2
            
        }// switch
        if(izbor == 9) break;
        char ime_datoteke_rjesenja[40];
        
        do{
            cout << endl << "ODABIR NACINA PRIKAZA RJESENJA" << endl << endl;
            cout << " 1. Ispisi rjesenje na ekranu konzole" << endl << endl;
            cout << " 2. Spremi rjesenje u tekstualnu datoteku s ispisom prilagodenim za Notepad" << endl << endl;
            cout << " 3. Spremi rjesenje u tekstualnu datoteku s ispisom prilagodenim za WordPad" << endl << endl;
            cout << " 9. Odustani i izadi iz programa" << endl << endl;
            cout << " Izbor: ";
            cin >> izbor;
            if(!cin){
                 ok = false;
                 cin.clear();
                 cin.ignore();
                 cout << "Greska >> Potrebno je upisati broj!" << endl;
            } 
            else if (izbor != 1 && izbor != 2  && izbor != 3 && izbor != 9) ok = false;
            else ok = true;
        }while(!ok);
        
        cout << endl << "--------------------------------------------------------------------------------" << endl;
        
        if(izbor == 2 || izbor == 3){
                cin.ignore();
                cout << endl << "Naziv datoteke u koju zelite spremiti rjesenje zadatka: ";
                cin.getline(ime_datoteke_rjesenja, 40);
                if(strlen(ime_datoteke_rjesenja) == 0) strcpy(ime_datoteke_rjesenja, "rjesenje_zadatka.txt");   
                
            freopen (ime_datoteke_rjesenja,"w",stdout);    
            
        } 
        else if (izbor == 9) break;
        
        cout << endl << "IZRACUN ZADATKA" << endl;
        
        // algoritam za rješavanje zadatka 
        int broj_mogucih_kolicina_zaliha = (int)(maksimalan_kapacitet_skladista / rata_povecanja_kolicine_nabave) + 1;
        
        int zalihe[broj_mogucih_kolicina_zaliha];
        for(int i = 0; i < broj_mogucih_kolicina_zaliha; i++){
            zalihe[i] = i * rata_povecanja_kolicine_nabave;
        }
        int f[broj_razdoblja][broj_mogucih_kolicina_zaliha];
        int Q[broj_razdoblja][broj_mogucih_kolicina_zaliha];
        int nabava[broj_razdoblja][2]; // nabava[broj_razdoblja][0] <= nabava(broj_razdoblja) <= nabava[broj_razdoblja][1]
        cout << endl << "zalihe(i) + potraznja(i) - " << maksimalan_kapacitet_skladista << " <= nabava(i) <= zalihe(i) + potraznja(i)" << endl;
        
        cout << endl << "RAZDOBLJE 1" << endl;
        
        int i = 0;
        cout << endl << "\t" << maksimalan_kapacitet_skladista << " + " << potraznja[i] << " - " << maksimalan_kapacitet_skladista;
        cout << " <= nabava(" << i + 1 << ") <= " << maksimalan_kapacitet_skladista << " + " << potraznja[i] << endl;
        nabava[i][0] = maksimalan_kapacitet_skladista + potraznja[i] - maksimalan_kapacitet_skladista;
        nabava[i][1] = maksimalan_kapacitet_skladista + potraznja[i];
        
        // provjera da nabava nije manja od nule ili veće od dopuštene
        if(nabava[i][0] < 0) nabava[i][0] = 0;
        if(nabava[i][1] > maksimalna_kolicina_nabave) nabava[i][1] = maksimalna_kolicina_nabave;
        
        cout << "\t" << nabava[i][0] << " <= nabava(" << i + 1 << ") <= " << nabava[i][1]<< endl << endl;
        
        int index = 0;
        for(int j = nabava[i][0]; j <= nabava[i][1]; j += rata_povecanja_kolicine_nabave){
            cout << "f(" << i + 1 << ")[" << zalihe[index] << "]" << " = " << "[" << j << ", " << zalihe[index] <<"]" << " = ";
            int trosak_nabave_pom = 0;
            if(j > 0) trosak_nabave_pom = trosak_nabave;
            int trosak_skladista = zalihe[index] * trosak_skladista_po_jedinici;
            Q[i][index] = j;
            f[i][index] = trosak_nabave_pom + trosak_skladista;
            cout << trosak_nabave_pom << " + " << trosak_skladista << " = " << f[i][index] << endl; 
            index++; 
        }
     
        for(i=1; i < broj_razdoblja; i++){
            index = 0;
            cout << endl << "RAZDOBLJE " << i+1 << endl << endl;
            
            for(index = 0; index < broj_mogucih_kolicina_zaliha; index++){
                cout << "f(" << i+1 << ") = " << "zalihe[" << zalihe[index] << "]";
                cout << endl << "\t" << zalihe[index] << " + " << potraznja[i] << " - " << maksimalan_kapacitet_skladista;
                cout << " <= nabava(" << i + 1 << ") <= " << zalihe[index] << " + " << potraznja[i] << endl;
                nabava[i][0] = zalihe[index] + potraznja[i] - maksimalan_kapacitet_skladista;
                nabava[i][1] = zalihe[index] + potraznja[i];
                
                // provjera da nabava nije manja od nule ili veće od dopuštene
                if(nabava[i][0] < 0) nabava[i][0] = 0;
                if(nabava[i][1] > maksimalna_kolicina_nabave) nabava[i][1] = maksimalna_kolicina_nabave;
                
                cout << "\t" << nabava[i][0] << " <= nabava(" << i + 1 << ") <= " << nabava[i][1]<< endl << endl;
                cout << "f(" << i+1 << ")[" << zalihe[index] << "] = min{" << endl;
                
                f[i][index] = 2147483647; // max int jer tražimo min f u for petlji
                for(int j = nabava[i][0]; j <= nabava[i][1]; j += rata_povecanja_kolicine_nabave){
                    cout <<"\t[" << j << ", " << zalihe[index] << "]" << " + " << "[" << zalihe[index];
                    cout << " + " << potraznja[i] <<" - " << j << "]" << " = ";
                    int trosak_nabave_pom = 0;
                    if(j > 0) trosak_nabave_pom = trosak_nabave;
                    int trosak_skladista = zalihe[index] * trosak_skladista_po_jedinici;
                    int zalihe_za_f_prethodno = zalihe[index] + potraznja[i] - j;
                    if(zalihe_za_f_prethodno < 0) zalihe_za_f_prethodno = 0;
                    if(zalihe_za_f_prethodno > maksimalan_kapacitet_skladista) zalihe_za_f_prethodno = maksimalan_kapacitet_skladista;
                    int index_za_f_prethodno = 0;
                    if(zalihe_za_f_prethodno > 0) index_za_f_prethodno = (int)(zalihe_za_f_prethodno/rata_povecanja_kolicine_nabave);
                    int f_pomocno = trosak_nabave_pom + trosak_skladista + f[i-1][index_za_f_prethodno];
                    if(f_pomocno < f[i][index]){
                         f[i][index] = f_pomocno;
                         Q[i][index] = j;
                    }
                    cout << trosak_nabave_pom << " + " << trosak_skladista << " + ";
                    cout << f[i-1][index_za_f_prethodno] << " = " << f_pomocno << endl; 
                }
                cout << "\t}" << endl;
                cout << "f(" << i+1 << ")[" << zalihe[index] << "] = " << f[i][index] << endl << endl;
            }
        }
        
        cout << "TABLICA RJESENJA PROBLEMA NABAVE" << endl << endl;
    
        int broj_dijelova_tablice = (int)(broj_razdoblja / 4);
        if(broj_razdoblja % 4 != 0) broj_dijelova_tablice++;
        for(int k = 1; k <= broj_dijelova_tablice; k++){
            cout << "I\t";
            for(int i = ((k-1)*4); i < 4*k; i++){
                cout << "Q(" << i + 1 << ")\t" << "f(" << i + 1 << ")\t";
                if(i == (broj_razdoblja - 1)) break;
            }
            
            for(int i = 0; i < broj_mogucih_kolicina_zaliha; i++){
                cout << endl << zalihe[i] << "\t";
                for(int j = ((k-1)*4); j < 4*k; j++){
                    cout << Q[j][i] << "\t" << f[j][i] << "\t";
                    if(j == (broj_razdoblja - 1)) break;
                }
            }
            cout << endl << endl;   
        }
           
        int tablica[broj_razdoblja][6];
        tablica[broj_razdoblja-1][2] = potraznja[broj_razdoblja-1];
        tablica[broj_razdoblja-1][3] = 0;
        int index_za_Q = 0;
        
        tablica[broj_razdoblja-1][1] = Q[broj_razdoblja-1][index_za_Q];
        tablica[broj_razdoblja-1][0] = tablica[broj_razdoblja-1][3] + tablica[broj_razdoblja-1][2] - tablica[broj_razdoblja-1][1];
        
        for(int i = broj_razdoblja-2; i >= 0; i--){
            tablica[i][2] = potraznja[i];
            tablica[i][3] = tablica[i+1][0]; 
            index_za_Q = 0;
            if(tablica[i][3] > 0) index_za_Q = (int)(tablica[i][3]/rata_povecanja_kolicine_nabave);
            tablica[i][1] = Q[i][index_za_Q];
            tablica[i][0] = tablica[i][3] + tablica[i][2] - tablica[i][1];   
        }
        
        int suma_stupaca[2] ={0,0};
        
        for(int i = 0; i < broj_razdoblja; i++){
            if(tablica[i][1] != 0) tablica[i][4] = trosak_nabave;
            else tablica[i][4] = 0;
            suma_stupaca[0] += tablica[i][4];
            if(tablica[i][3] != 0) tablica[i][5] = tablica[i][3] * trosak_skladista_po_jedinici;
            else tablica[i][5] = 0;
            suma_stupaca[1] += tablica[i][5];
        }
        
        
        cout << endl << "ANALIZA DOBIVENIH REZULTATA" << endl;
        
        
        // ispis prilagoden WordPadu
        if(izbor == 3){
            cout << endl << "Raz(i)\tI(i-1)\tQ(i)\tD(i)\tI(i)\tCp(i)\tCh(i)";
            for(int i = 0; i < broj_razdoblja; i++){
            cout << endl << i+1 << "\t\t" << tablica[i][0] << "\t\t" << tablica[i][1] << "\t";
            cout << tablica[i][2] << "\t" << tablica[i][3] << "\t" << tablica[i][4] << "\t" << tablica[i][5] << "\t";           
            }
            cout << endl << "\t\t\t\t\t\tSuma:\t" << suma_stupaca[0] << "\t" << suma_stupaca[1] << "\t";
            cout << endl << "\t\t\t\t\t\tUkupno:\t" << suma_stupaca[0] + suma_stupaca[1] << "\t" << endl;
        }
        // ispis prilagoden konzoli
        else{
            cout << endl << "Raz(i)\tI(i-1)\tQ(i)\tD(i)\tI(i)\tCp(i)\tCh(i)";
            for(int i = 0; i < broj_razdoblja; i++){
            cout << endl << i+1 << "\t" << tablica[i][0] << "\t" << tablica[i][1] << "\t";
            cout << tablica[i][2] << "\t" << tablica[i][3] << "\t" << tablica[i][4] << "\t" << tablica[i][5] << "\t";           
            }
            cout << endl << "\t\t\t\tSuma:\t" << suma_stupaca[0] << "\t" << suma_stupaca[1] << "\t";
            cout << endl << "\t\t\t\t\tUkupno:\t" << suma_stupaca[0] + suma_stupaca[1] << "\t" << endl;
        }
        
        if(izbor == 2 || izbor == 3){
            fclose(stdout);   
            freopen( "CON", "w", stdout );
            cout << endl << "Rjesenje zadatka spremljeno je u datoteku: " << ime_datoteke_rjesenja << endl;
        }
        
    }while(izbor != 9);    
    
    delete [] potraznja;
        
    return 0;
}
