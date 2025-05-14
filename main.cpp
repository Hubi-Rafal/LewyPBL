#include <iostream>
#include <fstream>
#include <stdio.h>
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
		
		fstream f;
		json plik;
		
	
	public:
		string username;
		bool admin;
		bool zalogowany;
		
		User()
		{
			
			f.open("uzytkownicy.json");
            if(!f.is_open())
            {
                cout<<"Nie znaleziono pliku z uzytkownikami, zostanie on utworzony."<<endl;
                ofstream outFile("uzytkownicy.json");
                json emptyArray = json::array();
                outFile << emptyArray;
                outFile.close();
            }else{
                cout << "Znaleziono plik z uzytkownikami." << endl; //DO wywalenia potem
                plik = json::parse(f);
                zalogowany = false;
                admin = false;
            }
		}
		
		void dodajFilm()
		{
			if(admin==false)
			{
				return;
			}
			cout<<"Podaj tytuł nowego filmu."<<endl<<">";
			
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
			while(found == 0)
			{
				cout<<">";
				cin>>us;
				for(auto element : plik)
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

								
								break;
							}
						}
					}else
					{
						cout<<"Nie znaleziono podanej nazwy uzytkownika, sprobuj ponownie nobie"<<endl;
					}
					

				}
				return;
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
            for(auto element : plik)
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
				for(auto element : plik)
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
            plik.push_back(newUser);

            // Zapisanie obiektu JSON do pliku
            //f.close(); // Zamknięcie pliku w trybie odczytu
            ofstream outFile("uzytkownicy.json");

            if (!outFile.is_open()) {
                cerr << "Nie można otworzyć pliku do zapisu." << endl;
                //return 0;
            }else
            {
                outFile << setw(4) << plik;
                outFile.close();
                zalogowany = true;
                cout<<"Zarejestrowano pomyslnie, witaj w CineBooker!"<<endl;
            }
            
//            return 0;


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
		ofstream o;
		json plik;
		
		Repertuar()
		{
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
		} 
		
		//! Funkcja wyswietlRepertuar
		/*!
		*
		* Funkcja która wypisuje w konsoli informacje o aktualnym  repertuarze sali kinowej. Na chwilę obecną informacje te stanowią: Tytuł filmu, Godzina rozpoczęcia seansu, Język filmu oraz jego typ (2d lub 3d)
		*
		*/
		void wyswietlRepertuar()
		{	
			
					
			cout<<"=========== REPERTUAR ============="<<endl<<endl;
			
	//		plik[3]["tytul"] = "XD"; //
	//		o.open("repertuar.json");// 	tu jest zapisywanie do pliku
	//		o<<setw(4)<<plik;		 // 

			int i = 0;
			for(auto film : plik)
			{
				cout<<"############# Seans #"<<i+1<<" #############"<<endl;
				cout<<"#  Tytul filmu: "<<film["tytul"]<<endl;
				cout<<"#  Godzina rozpoczecia: "<<film["godzina"]<<endl;
				cout<<"#  Jezyk: "<<film["Jezyk"]<<endl;
				cout<<"#  Typ (2d/3d): "<<film["typ"]<<endl;
				cout<<"####################################"<<endl<<endl;
				i++;
			}
			
			int wybor;
			cout<<"Wybierz numer seansu na który chcesz kupić bilet. Wpisz '0' aby wrócić do menu"<<endl<<">";
			
			while(!(cin>>wybor))
			{
				cin.clear();
				cin.ignore(40,'\n');
				cout<<">";
			};

			

						
		}
		
		//! Funkcja wybierzMiejsca
		/*!
		*
		* Funkcja umożliwiająca użytkownikowi zarezerwowanie miejsca na wybranym seansie
		*
		*/
		void wybierzMiejsca(int zalogowany)
		{
            int miejsce;
			
			int x1=4;
			int y1=4;
            int tab[x1][y1];
            int a,b;
            
            for(a = 0; a<y1 ;a++)
            {
            	for(b = 0; b<x1;b++)
            	{
            		
            		tab[a][b] = a*b;
				}
			}
            int getchar;
            int polozenie[0][0];
            int x=0,y=0;
            do
            {
                system("cls");
                for(int i = 0;i<y1;i++)
                {
                    for(int j = 0;j<x1;j++)
                    {
                        if(i==y && j==x){
                            cout<<"|=X=|";
                        }else{
                            cout<<"| "<<tab[i][j]<<" |";
                        }
                    }
                    cout<<endl;
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
            
            cout<<"Wybrane miejsce: "<<miejsce<<endl;
            if(zalogowany == 0)
            {
//            	string username = 
			}
            
            
            system("pause");
		}
		
	private:
		
		
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
		int start()
		{
			int wybor;
			User u;
			while(wybor!=4)
			{
				
				
				if(u.zalogowany == false)
				{
					cout<<"Witaj w menu głownym serwisu CineBooker."<<endl<<endl;
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
							rp.wyswietlRepertuar();
							break;
					}	
				}else if(u.admin == true)
				{
					system("cls");
					cin.clear();
					cout<<"Hello admin"<<endl;
					cout<<"[1] -- Wyloguj"<<endl;
					cout<<"[2] -- Edytuj repertuar"<<endl;
					cout<<"[4] -- Wyjdz"<<endl;
					cout<<u.username<<">";
					cin>>wybor;
					switch(wybor)
					{
						case 1:
							u.logout();
							
							break;
						case 2:
							rp.wyswietlRepertuar();
							break;
							
						case 4:
							return 0;
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
							rp.wyswietlRepertuar();
							break;
							
						case 4:
							return 0;
							break;
					}
				
				}
			}
		}
			
	
			
	
};



//===================================================================================================================================================================================================
int main(int argc, char** argv) {


//    User u;
//    u.registration();

	Controller c;
	c.start();
//	Repertuar r;
//	r.wybierzMiejsca(1);




//	system("pause");
	return 0;
}