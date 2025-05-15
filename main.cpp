#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include "nlohmann/json.hpp"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
using json = nlohmann::json;

using namespace std;


class User
{
	private:
		fstream rz;
		fstream users;
		json uzytkownicy;

	
	public:
		string username;
		bool admin;
		bool zalogowany;
		
		User()
		{
			rz.open("rezerwacje.json");
			users.open("uzytkownicy.json");
            if(!users.is_open())
            {
                cout<<"Nie znaleziono pliku z uzytkownikami, zostanie on utworzony."<<endl;
                ofstream outFile("uzytkownicy.json");
                json emptyArray = json::array();
                outFile << emptyArray;
                outFile.close();
            }else{
                cout << "Znaleziono plik z uzytkownikami." << endl; //DO wywalenia potem
                uzytkownicy = json::parse(users);
                rezerwacje = json::parse(rz);
                zalogowany = false;
                admin = false;
            }
		}

		void dodajFilm()
		{
			ifstream f("repertuar.json");
			json plik = json::parse(f);
			if(admin==false)
			{
				return;
			}
			
			string tytul, typ, jezyk, godzina;
			int id;
			
			cout<<"Podaj dane nowego seansu."<<endl;
			cout<<"Tytul: ";
			cin>>tytul;
			cout<<"Typ (2d/3d): ";
			cin>>typ;
			cout<<"Język: ";
			cin>>jezyk;
			cout<<"Godzina Rozpoczecia: ";
			cin>>godzina;

			int max = 0;
			for(auto element : plik)
			{
				if(element["id"]>max)
				{
					max=element["id"];
				}
			}
			id = max+1;
			json newSeans = {
				{"id",id},
				{"tytul",tytul},
				{"typ",typ},
				{"godzina",godzina},
				{"jezyk",jezyk}
			};
			plik.push_back(newSeans);
			
			
			ofstream o("repertuar.json");
			o<<setw(4)<<plik;
		
		}
	//! Funkcja login()
	/*!
	*
	* Służy do umożliwienia
	*
	*/
		void login()
        {
        	system("cls");
            //cout<<"\x1B[9J\x1B[0;0f";
           	string us, pass;
           	cout<<"Prosze wpisac nazwe uzytkownika"<<endl;
			int found = 0;
			while(1 == 1)
			{
				cout<<">";
				cin>>us;
				for(auto element : uzytkownicy)
				{
					system("cls");
					if(element["username"] == us)
					{
						
					 	
						while(!(pass == element["password"]))
						{
							system("cls");
		
							cout<<"znaleziono username, podaj haslo"<<endl<<">";
							cin>>pass;

							if(pass == element["password"])
							{	
								system("cls");
								username = us;
								zalogowany = true;
								if(element["admin"]!=nullptr)
								{
									admin = true;
									return;
								}

								return;
								break;
							}
						}
					}else
					{
						cout<<"Nie znaleziono podanej nazwy uzytkownika, sprobuj ponownie nobie"<<endl;
					}
					
				
				}
			}


        }
        void logout()
        {
        	zalogowany = false;
        	admin = false;
        	username = "";
        	cout<<"logout";
		}
		
        void registration()
        {
            string username, password;
            cout << "Podaj nazwe uzytkownika: ";
            cin >> username;
            
			int flag;
            for(auto element : uzytkownicy)
            {

	            if(username==element["username"])
	            {
	            	flag = 1;
				}
            	
			}
			
			while(flag == 1)
			{
				cin.clear();
	        	cout << "Ta nazwa uzytkownika jest zajeta. "<<endl<<"Podaj nazwe uzytkownika: ";
    		    cin >> username;
				for(auto element : uzytkownicy)
				{
					if(username == element["username"])
					{
						flag = 1;
						break;
					}else{
						flag = 0;
					}
				}
			}

			cout << "Podaj haslo: ";
            cin >> password;
            cout<<"\x1B[1J\x1B[0;0f";
			
			
            // Dodanie nowego użytkownika do obiektu JSON
            json newUser = {
                {"username", username},
                {"password", password},
                {"admin", nullptr}
            };
            uzytkownicy.push_back(newUser);

            // Zapisanie obiektu JSON do pliku
            //f.close(); // Zamknięcie pliku w trybie odczytu
            ofstream outFile("uzytkownicy.json");

            if (!outFile.is_open()) {
                cerr << "Nie można otworzyć pliku do zapisu." << endl;
                //return 0;
            }else
            {
                outFile << setw(4) << uzytkownicy;
                outFile.close();
                zalogowany = true;
                cout<<"Zarejestrowano pomyslnie, witaj w CineBooker!"<<endl;
            }
            
//            return 0;


        }
        
        
        void wyswietlRezerwacje()
        {
        	for(auto element : rezerwacje)
        	{
        		if(element["username"]==this->username)
        		{        				
				
					cout<<"############# Seans #"<<film["id"]<<" #############"<<endl;
					cout<<"#  Tytul filmu: "<<film["tytul"]<<endl;
					cout<<"#  Godzina rozpoczecia: "<<film["godzina"]<<endl;
					cout<<"#  Jezyk: "<<film["jezyk"]<<endl;
					cout<<"#  Typ (2d/3d): "<<film["typ"]<<endl;
					cout<<"####################################"<<endl<<endl;
				}
			}
		}
};



//===================================================================================================================================================================================================
//! Klasa Repertuar
/*!
*
* Klasa Repertuar zajmuje się obsługiwaniem repertuaru sali kinowej. Tu użytkownik może przejrzeć dostępne seanse, dostosować filtry wyszukiwania oraz wybrać seans który go interesuje.
*
*/
class Repertuar
{
		
	public:
		
		ifstream f;
		fstream o;
		json plik;
		json rezerwacje;
		Repertuar()
		{
			r.open("rezerwacje.json");
			rezerwacje = json::parse(r);
			f.open("repertuar.json");
            if(!f.is_open())
            {
                cout<<"Nie znaleziono pliku z repertuarem, zostanie on utworzony."<<endl;
                ofstream outFile("repertuar.json");
                json emptyArray = json::array();
                outFile << emptyArray;
                outFile.close();
            }else {
                plik = json::parse(f);
            }
		}
		
		~Repertuar()
		{
			f.close();
			r.close();
		} 
		
		//! Funkcja wyswietlRepertuar
		/*!
		*
		* Funkcja która wypisuje w konsoli informacje o aktualnym  repertuarze sali kinowej. Na chwilę obecną informacje te stanowią: Tytuł filmu, Godzina rozpoczęcia seansu, Język filmu oraz jego typ (2d lub 3d)
		*
		*/
		void wyswietlRepertuar(User* u)
		{	
			
					
			cout<<"=========== REPERTUAR ============="<<endl<<endl;
			
	//		plik[3]["tytul"] = "XD"; //
	//		o.open("repertuar.json");// 	tu jest zapisywanie do pliku
	//		o<<setw(4)<<plik;		 // 

			int i = 0;
			for(auto film : plik)
			{
				cout<<"############# Seans #"<<film["id"]<<" #############"<<endl;
				cout<<"#  Tytul filmu: "<<film["tytul"]<<endl;
				cout<<"#  Godzina rozpoczecia: "<<film["godzina"]<<endl;
				cout<<"#  Jezyk: "<<film["jezyk"]<<endl;
				cout<<"#  Typ (2d/3d): "<<film["typ"]<<endl;
				cout<<"####################################"<<endl<<endl;
				i++;
			}
			int seans;
			cout<<"Wybierz numer seansu na który chcesz kupić bilet. Wpisz '0' aby wrócić do menu"<<endl<<">";
			
			while(!(cin>>seans) || (seans<0 || seans>i))
			{
				cin.clear();
				cin.ignore(40,'\n');
				cout<<">";
					
			
			}
			if(seans==0)
			{
				system("cls");
				return;
			}else{
				if(u->zalogowany == true)
				{
					this->wybierzMiejsca(u,seans);			
				}else
				{
					u->login();
					this->wybierzMiejsca(u,seans);
				}
				
			}
			

						
		}
		
		
		
		//! Funkcja wybierzMiejsca
		/*!
		*
		* Funkcja umożliwiająca użytkownikowi zarezerwowanie miejsca na wybranym seansie
		*
		*/
		
				
	private:
		ifstream r;
		
		
		void wybierzMiejsca(User* u,int seans)
		{
            int miejsce;

			int x1=12;
			int y1=6;
            int tab[y1][x1];
            int a,b,c = 0;
            
            for(a = 0; a<y1 ;a++)
            {
            	for(b = 0; b<x1;b++)
            	{
            		tab[a][b] = c++;
				}
			}
            int getchar;
            int polozenie[0][0];
            int x=0,y=0;
          
		bool clear = false, fst = true;
		while(clear==false)
		{
			
		    do
            {
                system("cls");
                cout << "  ================== EKRAN ====================" << endl << endl;
              
				    for(int i = 0;i<y1;i++)
	                {
	                    for(int j = 0;j<x1;j++)
	                    {
	                        if(i==y && j==x){
	                            cout<<"|==X==|";
	                        }else if (tab[i][j] < 10){
	                            cout<<"|  "<<tab[i][j]<<"  |";
	                        }else if(tab[i][j] < 100){
	                            cout<<"|  "<<tab[i][j]<<" |";
	                        }else{
	                            cout<<"| "<<tab[i][j]<<" |";
	                        }
	                    }
	                    cout<<endl;
	                }
	                if(fst == false)
	                {
	                	fst=true;
	                	cout<<"Miejsce zajęte, proszę wybrać inne miejsce"<<endl;
					}
	                getchar = getch();
	
	                switch(getchar)
	                {
	                    case KEY_UP:
	                        if(y>0)
	                        {
	                            --y;
	                        }
	                        break;
	                    case KEY_DOWN:
	                        if(y<y1-1)
	                        {
	                            ++y;
	                        }
	                        break;
	                    case KEY_LEFT:
	                        if(x>0)
	                        {
	                            --x;
	                        }
	                        break;
	                    case KEY_RIGHT:
	                        if(x<x1-1)
	                        {
	                            ++x;
	                        }
	                        break;
	                    case 13:
	                        miejsce = tab[y][x];
	                        break;
	                }
	            }while(getchar!=13);
	            
			  	for(auto element : rezerwacje)
			  	{
			  		if(seans == element["idSeansu"] && miejsce == element["miejsce"])
			  		{
			  			fst = false;
			  			clear = false;
			  			break;
					}else{
						clear = true;
					}
				}
			
		}
            
            cout<<"Wybrane miejsce: "<<miejsce<<endl;
            
			this->rezerwacja(u,miejsce,seans);

        }
        
        //! Funkcja rezerwacja
		/*!
		*
		* Funkcja zapisująca rezerwację do  pliku rezerwacje.json
		*
		*/
		void rezerwacja(User* u, int miejsce, int idSeansu)
		{
			
			json newRezerwacja = {
				{"username", u->username},
				{"idSeansu", idSeansu},
				{"miejsce", miejsce}
			};
			rezerwacje.push_back(newRezerwacja);
			
			ofstream o("rezerwacje.json");
			
			o<<setw(4)<<rezerwacje;
			o.close();
			system("pause");
			
		}
		
};                      

//===================================================================================================================================================================================================
//! Klasa Controller
/*!
*
* Klasa, od której zaczyna się działanie programu, i która odsyła wchodzącego z nim w interakcję użytkownika do poszczególnych funkcji programu, zaleznie od inputu.
* 
*/

class Controller
{
	private:
		
		Repertuar rp; /*!< Obiekt klasy Repertuar */
		int zalogowany;
		
	public:

		//! Funkcja Start
		/*!
		* Funkcja inicjalizująca menu główne, z którego użytkownik może przemieszczać się po programie
		*/
		void start()
		{
			int wybor;
			User u;
			while(wybor!=4)
			{


				if(u.zalogowany == false)
				{
					cout<<"Witaj w menu głównym serwisu CineBooker."<<endl<<endl;
					cout<<"[1] -- Login"<<endl;
					cout<<"[2] -- Rejestracja"<<endl;
					cout<<"[3] -- Przegladaj repertuar"<<endl;
					cout<<"[4] -- Wyjdz"<<endl;
					cout<<">";
					cin>>wybor;
					switch(wybor)
					{
						case 1:
							u.login();
							break;
						case 2:
							u.registration();
							
							
							break;
							
						case 3:
							rp.wyswietlRepertuar(&u);
							break;
					}	
				}else if(u.admin == true)
				{
					system("cls");
					cin.clear();
					cout<<"Hello admin"<<endl;
					cout<<"[1] -- Wyloguj"<<endl;
					cout<<"[2] -- Dodaj film"<<endl;
					cout<<"[4] -- Wyjdz"<<endl;
					cout<<u.username<<">";
					cin>>wybor;
					switch(wybor)
					{
						case 1:
							u.logout();

							break;
						case 2:
							u.dodajFilm();
							break;

						case 4:
							return;
							break;
					}
				}else
				{
					system("cls");
					cin.clear();
					cout<<"[1] -- Wyloguj"<<endl;
					cout<<"[2] -- Przegladaj repertuar"<<endl;
					cout<<"[4] -- Wyjdz"<<endl;
					cout<<u.username<<">";
					cin>>wybor;
					switch(wybor)
					{
						case 1:
							u.logout();
							break;
						case 2:
							rp.wyswietlRepertuar(&u);
							break;
							
						case 4:
							return;
							break;
					}
				
				}
			}
		}

};



//===================================================================================================================================================================================================
int main(int argc, char** argv) {

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

//    User u;
//    u.registration();

	Controller c;
	c.start();
//	Repertuar r;
//	r.wybierzMiejsca(1);


/*
ifstream x("rezerwacje.json");
json plik = json::parse(x);
int i = 0;
json rezerwacje;

for(json element : plik)
{
	if(!(element["username"] == nullptr))
	{
		json newRezerwacja = {
			{"username",element["username"]},
			{"idSeansu",element["idSeansu"]},
			{"miejsce",element["miejsce"]}
		};
		rezerwacje.push_back(newRezerwacja);
	}
}
x.close();
ofstream o("rezerwacje.json");
o<<setw(4)<<rezerwacje;
*/


	system("pause");
	return 0;
}