#include "v03VEC.h"


bool isnumber(string str) //check if string is number;
{
    for(int i = 0; i < str.length(); i++)
    {
        if(!isdigit(str[i]))
        {
            return 0;
        }
    }
    return 1;
}

bool equality(studentas &x, studentas &y)
{
    if(x.pavarde == y.pavarde) 
    {
        return x.pavarde < y.pavarde;
    } else return x.vardas < y.vardas;
}


void mediana(studentas &temp, int n) //mediana search function;
{
    sort(temp.paz.begin(), temp.paz.end()); //sorting grades (descending);
    float mid1, mid2;
    if(n == 2*(n/2))
    {
        mid1 = temp.paz[n/2 - 1];
        mid2 = temp.paz[n/2];
        temp.med = (mid1+mid2)/2;
    } 
    else 
    {
        mid1 = temp.paz[n/2];
        temp.med = mid1;
    }
}

void pild(studentas& temp) //function to insert data by hand;
{
    cout << "Iveskite varda ir pavarde: "; cin >> temp.vardas >> temp.pavarde;
    char pas;
    cout << "Jei norite atsitiktinai sugeneruoti pažymius ir egzamino rezultatą, įveskite (k), jei duomenis įvesite pats, įveskite (s): " << endl;
    do
    {
        cin >> pas;
    } while (pas != 's' && pas != 'S' && pas != 'k' && pas != 'K' );

    string check;
    if (pas == 's' || pas == 'S')
    {
        cout << "Iveskite pazymius (norint nebevesti pažymiu rašykite: '0' ): ";
        while(true)
        {
            cin >> check;
            if(!isnumber(check)) 
            {
                cout << "Iveskite SKAICIU [1; 10] be simboliu ar raidziu. Į intervalą nepatenkantys skaičiai nebus apdorojami" << endl;
                continue;
            }

            int check_nd = stoi(check);
        
            if(check_nd == 0)
            {
                if(temp.paz.size() == 0)
                {
                    temp.paz.push_back(check_nd);
                    break;
                } else break;
            } else if(check_nd > 0 && check_nd <=10)
                    {
                        temp.paz.push_back(check_nd);
                    } else if(check_nd < 0 || check_nd > 10)
                        {
                            cout << "Iveskite SKAICIU intervale [1; 10]: " << endl;
                            continue;
                        }
        }

        cout << "Iveskite egzamino paz.: ";
        while(true)
        {
            cin >> check;
            if(!isnumber(check)) 
            {
                cout << "Iveskite SKAICIU [1; 10] be simboliu ar raidziu. Į intervalą nepatenkantys skaičiai nebus abdorojami" << endl;
                continue;
            }

            int check_nd = stoi(check);
            if(check_nd > 0 && check_nd <=10)
                {
                    temp.egz = check_nd;
                } else if(check_nd < 0 || check_nd > 10)
                        {
                            cout << "Iveskite SKAICIU intervale: [1; 10]" << endl;
                            continue;
                        }
            break;
        }

    } else if(pas == 'k' || pas == 'K')
        { 
            cout << "Generuojami pažymiai: " << endl;
            srand(time(0));
            int a = (rand()%10)+1; //generating amount of random numbers
            for (int i = 0; i < a; i++)
            {
                int c = (rand()%10)+1; //generating random numbers;
                cout << c << " ";
                temp.paz.push_back(c);
            }
            cout << endl;
            cout << "Generuojamas egzamino pažymys: " << endl;
            int c = (rand()%10)+1; //generating random exam grade;
            cout << c << endl;
            temp.egz = c;
        } 
}

void eil_po_eil(string read_vardas, studentas& temp, vector<studentas> &mas) //read data from file;
{
    string eil, zod, skaic;
    int times;
    ifstream open_f; //(read_vardas)
    try
    {
        open_f.open(read_vardas);
        if(open_f.fail())
        throw read_vardas;
    }
    catch(string pvd)
    {
        cout << "Nėrastas failas: " << pvd << endl;
        cout << "Paleiskite programa is naujo pasitikrine, ar egzistuoja toks failas Jūsų direktorijoje.." << endl;
        exit(0);
    }
 
    getline(open_f, eil);
    times = count(eil.begin(), eil.end(), 'N'); //counting a number of homework;
    while (open_f)
    { 
      if (!open_f.eof()) 
        {
            open_f >> temp.vardas >> temp.pavarde;
            for(int i = 0; i < times; i++)
            {
                int a;
                open_f >> a;
                temp.paz.push_back(a);
            }
            int a;
            open_f >> a; 
            temp.egz = a;
            mas.push_back(temp);
            temp.paz.resize(0);
        }   else break;
    }
}


void spausd(vector<studentas> &mas, char ats) //printing data to file;
{
    ofstream fr ("rezultatai.txt");
    fr << "------------------------------------------------------------------------------" <<endl;
    fr  << left << setw(16) << "Vardas"  << left << setw(14) << "Pavardė " << left << setw(12)  << "Galutinis(Vid.)/Galutinis(Med.)"<<  endl;
    fr << "------------------------------------------------------------------------------" <<endl;

    for(auto &k : mas)
    {
        fr  << left << setw(16) << k.vardas  << left << setw(14) << k.pavarde;
        for(int i = 0; i < k.paz.size(); i++)
        {
            k.gal += k.paz[i];
        } 
    
        if (ats == 'G' || ats == 'g')
        {
            double kint = (0.4*k.gal/(double)k.paz.size() +  k.egz*0.6);
            fr << left << setw(19)  << setprecision(2) << fixed << kint  << " - " << endl;  
        }

        if(ats == 'M' || ats == 'm')
        {
            mediana(k, k.paz.size());
            fr << left << setw(19)  << " - " << (0.4*k.med + k.egz*0.6)<< endl;
        }
    }
}
