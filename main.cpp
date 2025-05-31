#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include "nlohmann/json.hpp"
using json = nlohmann::json;
//!Biblioteka nlholmann/json.hpp
/*!
 * Biblioteka do obsługi plików JSON w C++
 */

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13

using namespace std;


//===================================================================================================================================================================================================
//! Klasa Files
/*!
 * Klasa odpowiedzialna za obsługę plików z których korzysta program.
 */
 
class Files
{
	private:
		fstream users;
		fstream rez;
		fstream rep;
		json rezerwacje;
		json uzytkownicy;
		json repertuar;
	public:
		//! Konstruktor klasy Files
        /*!
         * Otwiera wszystkie potrzebne pliki i sprawdza czy zostały one otwarte prawidłowo. Jeśli plik nie został znaleziony, tworzy nowy plik.
         */
		Files()
		{
			users.open("uzytkownicy.json");
			rep.open("repertuar.json");
	        rez.open("rezerwacje.json");
	        
	            if(!users.is_open())
	            {
	                cout<<"Nie znaleziono pliku z użytkownikami, zostanie on utworzony."<<endl;
	                ofstream outFile("uzytkownicy.json");
	                json emptyArray = json::array();
	                outFile << emptyArray;
	                outFile.close();
	            }else{
	                uzytkownicy = json::parse(users);
	            }
	        
				
	            if(!rez.is_open())
	            {
	                cout<<"Nie znaleziono pliku z rezerwacjami, zostanie on utworzony."<<endl;
	                ofstream outFile("rezerwacje.json");
	                json emptyArray = json::array();
	                outFile << emptyArray;
	                outFile.close();
	            }else{
	                rezerwacje = json::parse(rez);
	            }
	            
				
				
	            if(!rep.is_open())
	            {
	                cout<<"Nie znaleziono pliku z repertuarem, zostanie on utworzony."<<endl;
	                ofstream outFile("repertuar.json");
	                json emptyArray = json::array();
	                outFile << emptyArray;
	                outFile.close();
	            }else{
	                repertuar = json::parse(rep);
	                
	            }
		}
		//! Dekonstruktor klasy Files
        /*!
         * Zamyka wszystkie otwarte w konstruktorze pliki.
         */
		~Files()
	    {
	       	users.close();
	       	rez.close();
			rep.close();
		}
		
		
		//! Funkcja getRepertuar()
        /*!
         * Zwraca zmienną repertuar, zawierającą zawartość pliku repertuar.json.
         */
		json getRepertuar()
		{
			return repertuar;
		}
		
		//! Funkcja getRepertuar()
        /*!
         * Zwraca zmienną uzytkownicy, zawierającą zawartość pliku uzytkownicy.json.
         */
		json getUzytkownicy()
		{
			return uzytkownicy;
		}
		
		//! Funkcja getRezerwacje()
        /*!
         * Zwraca zmienną rezerwacje, zawierającą zawartość pliku rezerwacje.json.
         */
		json getRezerwacje()
		{
			return rezerwacje;
		}
};
 

//===================================================================================================================================================================================================
//! Klasa User
/*!
 * Klasa odpowiadająca za zarządzanie użytkownikami, ich rejestrację, logowanie oraz zarządzanie rezerwacjami.
 * Klasa User obsługuje również dodawanie i usuwanie filmów z repertuaru, jeśli użytkownik jest administratorem.
 */
class User
{

	public:
		
		string username;
		bool admin;
		bool zalogowany;

        //! Konstruktor klasy User
        /*!
         * Konstruktor klasy User ustawia zmienne zalogowany i admin na false.
         */
		User()
		{
			zalogowany = false;
			admin = false;
		}

      
        //! Funkcja dodajFilm()
        /*!
         * Funkcja dodaje nowy film do repertuaru. Użytkownik musi być administratorem, aby móc dodać film.
         * Funkcja pobiera dane filmu od użytkownika, tworzy nowy obiekt JSON i dodaje go do repertuaru.
         * Następnie zapisuje zmiany do pliku repertuar.json wraz z unikalnym id.
         */
		void dodajFilm()
		{
			if(admin==false)
			{
				return;
			}
			Files f;
			json repertuar = f.getRepertuar();
			
			string tytul, typ, jezyk, godzina;
			int id;
			cout<<"Podaj dane nowego seansu."<<endl;
			cout<<"Tytuł: ";
			string x,y;			// zmienne do getline linie nizej
			getline(cin,y);		// dummy getline bo jak getline(cin,tytul) nie ma kolegi to dostaje pierdolca // prawdopodobnie coś z buforem
			
			getline(cin,tytul);
			cout<<"Typ (2d/3d): ";
			getline(cin,typ);
			cout<<"Język: ";
			getline(cin,jezyk);
			cout<<"Godzina Rozpoczęcia: ";
			getline(cin,godzina);

			int max = 0;
			for(auto element : repertuar)
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
			repertuar.push_back(newSeans);
			
			
			ofstream o("repertuar.json");
			o<<setw(4)<<repertuar;
			o.close();
		}

        //! Funkcja usunFilm()
        /*!
         * Funkcja usuwa film z repertuaru. Użytkownik musi być administratorem, aby móc usunąć film.
         * Funkcja wyświetla dostępne filmy z pliku repertuar.json i pozwala użytkownikowi wybrać film do usunięcia.
         * Następnie zapisuje zmiany do pliku.
         */
		void usunFilm()
		{
			if(admin==false)
			{
				return;
			}
			Files f;
			json repertuar = f.getRepertuar();
			
			for(auto film : repertuar)
			{
				
				cout<<"############# Seans #"<<film["id"]<<" #############"<<endl;
				cout<<"#  Tytul filmu: "<<film["tytul"]<<endl;
				cout<<"#  Godzina rozpoczecia: "<<film["godzina"]<<endl;
				cout<<"#  Jezyk: "<<film["jezyk"]<<endl;
				cout<<"#  Typ (2d/3d): "<<film["typ"]<<endl;
				cout<<"####################################"<<endl<<endl;
			}
			int delNumber;
			cout<<"Podaj numer seansu który chcesz usunąć."<<endl<<">";
			while(!(cin>>delNumber))
			{
				cin.clear();
				cin.ignore(40,'\n');
				cout<<">";
			}
			
			json owFilmy;
				for(auto film : repertuar)
				{
					if(film["id"]==delNumber)
					{							
						film["id"] = nullptr;
					}
					if(!(film["id"] == nullptr))
					{
						json newFilm = {
							{"id",film["id"]},
							{"godzina",film["godzina"]},
							{"jezyk",film["jezyk"]},
							{"tytul",film["tytul"]},
							{"typ",film["typ"]}
						};
						owFilmy.push_back(newFilm);
								
					}
						
				}
				ofstream o("repertuar.json");
				o<<setw(4)<<owFilmy;
			
		}
			
        //! Funkcja login()
        /*!
         * Funkcja loguje użytkownika do systemu. Użytkownik musi podać poprawną nazwę użytkownika i hasło.
         * Jeśli dane są poprawne, użytkownik zostaje zalogowany i może korzystać z systemu.
         * Jeśli dane są niepoprawne, użytkownik zostaje poproszony o ponowne podanie danych.
         */
		void login()
        {
        	Files f;
        	json uzytkownicy = f.getUzytkownicy();
        	system("cls");
           	string us, pass;
           	cout<<"LOGOWANIE"<<endl<<"Proszę wpisać nazwę użytkownika"<<endl<<">";
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
		
							cout<<"Nazwa użytkownika rozpoznana, podaj hasło"<<endl<<">";
							cin>>pass;

							if(pass == element["password"])
							{	
								system("cls");
								username = us;
								zalogowany = true;
								admin = element["admin"];
								return;
							}
						}
					}else
					{
						cout<<"Nie znaleziono podanej nazwy użytkownika, spróbuj ponownie"<<endl;
					}
				}
			}
        }

        //! Funkcja logout()
        /*!
         * Funkcja wylogowuje użytkownika z systemu. Użytkownik zostaje przeniesiony do menu głównego.
         * Zmienne zalogowany , admin i username są resetowane.
         */
        void logout()
        {
        	zalogowany = false;
        	admin = false;
        	username = "";
        	system("cls");
        	cout<<"Wylogowano pomyślnie."<<endl;
		}

        //! Funkcja registration()
        /*!
         * Funkcja rejestruje nowego użytkownika w systemie. Użytkownik musi podać unikalną nazwę użytkownika i hasło.
         * Jeśli nazwa użytkownika jest już zajęta, użytkownik zostaje poproszony o podanie innej.
         * Nowy użytkownik zostaje dodany do pliku uzytkownicy.json.
         */
        void registration()
        {
        	Files f;
        	json uzytkownicy = f.getUzytkownicy();
            string password;
            cout << "Podaj nazwę użytkownika: ";
            cin >> username;
            
			int flag = 0;
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
	        	cout << "Ta nazwa użytkownika jest zajęta. "<<endl<<"Podaj nazwę użytkownika: ";
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

			cout << "Podaj hasło: ";
            cin >> password;
            cout<<"\x1B[1J\x1B[0;0f";

            // Dodanie nowego użytkownika do obiektu JSON
            json newUser = {
                {"username", username},
                {"password", password},
                {"admin", false}
            };
            uzytkownicy.push_back(newUser);

            ofstream outFile("uzytkownicy.json");

            if (!outFile.is_open()) {
                cerr << "Nie można otworzyć pliku do zapisu." << endl;
            }else
            {
                outFile << setw(4) << uzytkownicy;
                outFile.close();
                zalogowany = true;
                cout<<"Zarejestrowano pomyślnie, witaj w CineBooker!"<<endl;
            }
        }

        //! Funkcja wyswietlRezerwacje()
        /*!
         * Funkcja przeszukuje plik rezerwacje.json i wyświetla wszystkie rezerwacje przypisane do zalogowanego użytkownika.
         * Następnie pozwala użytkownikowi anulować rezerwację podając jej ID.
         */
        void wyswietlRezerwacje()
        {
        	system("cls");
        	Files f;
        	json repertuar = f.getRepertuar();
        	json rezerwacje = f.getRezerwacje();
        	
 			int i = 0;
        	for(auto element : rezerwacje)
        	{
        		if(element["username"]==this->username)
        		{
					for(auto film : repertuar)
					{
						if(element["idSeansu"] == film["id"])
						{	
							cout<<"############# Rezerwacja #"<<element["id"]<<" #############"<<endl;
							cout<<"#  Tytul filmu: "<<film["tytul"]<<endl;
							cout<<"#  Godzina rozpoczecia: "<<film["godzina"]<<endl;
							cout<<"#  Jezyk: "<<film["jezyk"]<<endl;
							cout<<"#  Typ (2d/3d): "<<film["typ"]<<endl;
							cout<<"#  Miejsce: "<<element["miejsce"]<<endl;				
							cout<<"####################################"<<endl<<endl;
							i++;
						}						
					}
				}
			}

			int delNumber;
			cout<<"Czy chcesz anulować którąś z rezerwacji?"<<endl<<"[X] - Anuluj rezerwację o podanym numerze."<<endl<<"[0] -- Wróć do menu głównego."<<endl;
			cout<<this->username<<">";

			while(!(cin>>delNumber))
			{
				cin.clear();
				cin.ignore(40,'\n');
				cout<<">";
			}

			if(delNumber == 0)
			{
				return;
			}else
			{
				int x = 1;
				json owRezerwacje;
				for(auto element:rezerwacje)
				{
					if(element["username"]==this->username)
					{
						if(element["id"] == delNumber)
						{
							element["id"] = nullptr;
						}
					}
					if(!(element["id"] == nullptr))
					{
						json newRezerwacja = {
							{"id",x},
							{"username",element["username"]},
							{"idSeansu",element["idSeansu"]},
							{"miejsce",element["miejsce"]}
						};
						owRezerwacje.push_back(newRezerwacja);
								
						x++;
					}
				}

				
				ofstream o("rezerwacje.json");
                if (!o.is_open()) {
                    cerr << "Nie można otworzyć pliku do zapisu." << endl;
                }
                else
                {
                    o<<setw(4)<<owRezerwacje;
                    o.close();
                    system("cls");
                    cout<<"Anulowano rezerwację o ID: "<<delNumber<<endl;
                    system("pause");
                }
			}
		}
};

//===================================================================================================================================================================================================
//! Klasa Repertuar
/*!
* Klasa odpowiadająca za zarządzanie repertuarem filmów. Klasa ta wyświetla repertuar filmów, pozwala użytkownikowi na wybór seansu oraz rezerwację miejsc.
*/
class Repertuar
{
	public:

		//! Funkcja wyswietlRepertuar
		/*!
		 * Funkcja wyświetla repertuar filmów pobrany z pliku repertuar.json. Użytkownik może wybrać seans, na który chce kupić bilet.
		 * Jeśli użytkownik nie jest zalogowany, zostaje poproszony o zalogowanie się.
		 *
         * @param u Wskaźnik do obiektu klasy User, reprezentujący zalogowanego użytkownika.
		 */
		void wyswietlRepertuar(User* u)
		{	
			Files f;
    		json repertuar = f.getRepertuar();
					
			cout<<"=========== REPERTUAR ============="<<endl<<endl;
			
			int i = 0;
			for(auto film : repertuar)
			{
				cout<<"############# Seans #"<<film["id"]<<" #############"<<endl;
				cout<<"#  Tytuł filmu: "<<film["tytul"]<<endl;
				cout<<"#  Godzina rozpoczęcia: "<<film["godzina"]<<endl;
				cout<<"#  Język: "<<film["jezyk"]<<endl;
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

	private:

        //! Funkcja wybierzMiejsca
        /*!
         * Funkcja wyświetla dostępne miejsca w sali kinowej i pozwala użytkownikowi wybrać miejsce na konkretny seans.
         * Jeśli miejsce jest już zajęte, użytkownik zostaje poproszony o wybranie innego miejsca.
         *
         * @param u Wskaźnik do obiektu klasy User, reprezentujący zalogowanego użytkownika.
         * @param seans Seans, na który użytkownik chce zarezerwować bilet.
         */
		void wybierzMiejsca(User* u,int seans)
		{
			Files f;
        	json rezerwacje = f.getRezerwacje();
        	
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
	                    case KEY_ENTER:
	                        miejsce = tab[y][x];
	                        break;
	            	}
	        }while(getchar!=KEY_ENTER);
	            
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
		 * Funkcja rezerwuje miejsce dla użytkownika na wcześniej wybrany seans. Tworzy nowy obiekt JSON z danymi rezerwacji i zapisuje go do pliku rezerwacje.json.
         * Funkcja generuje unikalne ID dla każdej rezerwacji.
         *
         * @param u Wskaźnik do obiektu klasy User, reprezentujący zalogowanego użytkownika.
         * @param miejsce Miejsce, które użytkownik chce zarezerwować.
         * @param idSeansu ID seansu, na który użytkownik chce zarezerwować miejsce.
		 */
		void rezerwacja(User* u, int miejsce, int idSeansu)
		{
			Files f;
        	json rezerwacje = f.getRezerwacje();
        	
				int max = 0;
			for(auto element : rezerwacje)
			{
				if(element["id"]>max)
				{
					max=element["id"];
				}
			}
			int id = max+1;
			json newRezerwacja = {
				{"id",id},
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
 * Klasa, od której zaczyna się działanie programu, i która odsyła wchodzącego z nim w interakcję użytkownika do poszczególnych funkcji programu.
 */

class Controller
{
	private:
		
		Repertuar rp; /*!< Obiekt klasy Repertuar */
        User u; /*!< Obiekt klasy User */
		
	public:

		//! Funkcja start
		/*!
		 * Funkcja inicjalizująca menu główne, z którego użytkownik może przemieszczać się po programie.
		 * Funkcja ta wyświetla dostępne opcje i pozwala użytkownikowi na wybór akcji.
		 * Użytkownik może się zalogować, zarejestrować, przeglądać repertuar lub wyjść z programu.
		 * Funkcja ta obsługuje również panel administratora, jeśli użytkownik jest administratorem.
		 */
		void start()
		{
			int wybor = 0;
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
					while(!(cin>>wybor))
					{
						cin.clear();
						cin.ignore(40,'\n');
						cout<<">";
					}
					switch(wybor)
					{
						case 1:
							u.login();
							break;
						case 2:
							system("cls");
							u.registration();
							break;
							
						case 3:
							system("cls");
							rp.wyswietlRepertuar(&u);
							break;
					}	
				}else if(u.admin == true)
				{
					system("cls");
					cin.clear();
					cout<<"Panel administratora CineBooker"<<endl;
					cout<<"[1] -- Wyloguj"<<endl;
					cout<<"[2] -- Dodaj film"<<endl;
					cout<<"[3] -- Usuń film"<<endl;
					cout<<"[4] -- Wyjdz"<<endl;
					cout<<u.username<<">";
					while(!(cin>>wybor))
					{
						cin.clear();
						cin.ignore(40,'\n');
						cout<<">";	
					}
					switch(wybor)
					{
						case 1:
							u.logout();

							break;
						case 2:
							system("cls");
							u.dodajFilm();
							break;
						case 3:
							system("cls");
							u.usunFilm();
							break;

						case 4:
							return;
							break;
					}
				}else
				{
					system("cls");
					cin.clear();
					cout<<"Panel użytkownika CineBooker."<<endl;
					cout<<"[1] -- Wyloguj"<<endl;
					cout<<"[2] -- Przegladaj repertuar"<<endl;
					cout<<"[3] -- Twoje Rezerwacje"<<endl;
					cout<<"[4] -- Wyjdz"<<endl;
					cout<<u.username<<">";
					while(!(cin>>wybor))
					{
						cin.clear();
						cin.ignore(40,'\n');
						cout<<">";
					}
					switch(wybor)
					{
						case 1:
							u.logout();
							break;
						case 2:
							system("cls");
							rp.wyswietlRepertuar(&u);
							break;
						case 3:
							u.wyswietlRezerwacje();
							break;
							
						case 4:
							return;
					}
				}
			}
		}
};

//===================================================================================================================================================================================================

int main(int argc, char** argv) {

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

	Controller c;
	c.start();

	system("pause");
	return 0;
}