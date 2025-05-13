#include <iostream>
#include <fstream>
#include <stdio.h>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

using namespace std;


class User
{
	private:
		bool zalogowany;
};


class userAdmin : User
{
	
};

class loggedUser : User
{
	
};


//===================================================================================================================================================================================================
//! Klasa UserHandle
/*!
*
* Klasa UserHandle zajmuje się obsługą akcji logowania się przez użytkownika do systemu CineBooker. Gdy użytkownik jest zalogowany, klasa ta umożliwia mu również kupienie biletu na wybrany seans
*
*/

    class UserHandle
    {
        public:
        	int zalogowany = 0; /*!< Zmienna odpowiadająca statusowi zalogowania użytkownika. 0 -- niezalogowany; 1 -- zalogowany */
        
			//! Funkcja login
			/*!
			*
			* Funkcja odpowiedzialna za logowanie do serwisu
			*
			*/
            void login()
            {
				cout<<"Welcome user"<<endl;
				
				system("pause");
            }
            //! Funkcja userHandler
			/*!
			*
			* Funkcja odpowiedzialna za nawigację po panelu uzytkownika serwisu
			*
			*/
            void userHandler()
            {
            	int wybor;	
				cout<<"Witaj w panelu uzytkownika aplikacji CineBooker."<<endl<<endl;
				cout<<"[1] -- Przegladaj rezerwacje"<<endl;
				cout<<"[2] -- Przegladaj repertuar"<<endl;
				cout<<">";
				cin>>wybor;
				system("pause");
			}
			
            //! Funkcja przegladajRezerwacje
			/*!
			*
			* Funkcja pozwalająca zalogowanemu użytkownikowi przeglądać i zarządzać dokonanymi rezerwacjami
			*
			*/
            void przegladajRezerwacje()
            {
            	
			}
            
            
    };
    
//===================================================================================================================================================================================================
//! Klasa Admin
/*!
*
* Klasa Admin słuzy do edytowania i zarządzania salami, seansami oraz repertuarem filmowym kina.
*
*/

class Admin
{
	public:
		//! Funkcja lobbyAdmin
		/*!
		*
		* Stanowi menu główne administratora, stąd administrator może wybrać w jaki sposób chce zarządzać salami kinowymi.
		*
		*/
		void lobbyAdmin()
		{
			int wybor;
			cout<<"Witaj w panelu administracyjnym aplikacji CineBooker."<<endl<<endl;
			cout<<"[1] -- Zarzadzaj Repertuarem"<<endl;
			cout<<"[2] -- Zarzadzaj Seansami"<<endl;
			cout<<"[3] -- Zarzadzaj Salami"<<endl;
			cout<<">";
			cin>>wybor;
			
			this->adminHandler(wybor);
		}
		private:
			//! Funkcja adminHandler
			/*!
			*
			* Obsługuje czynności które użytkownik może podjąć w panelu administratora
			*
			*/
			void adminHandler(int wybor)
			{
				switch(wybor)
				{
					case 1:
						//
						break;
					case 2:
						//
						break;					
					case 3:
						//
						break;				
					case 4:
						//
						break;
						
				}
				
				system("pause");
			}
			//! Funkcja edytujFilm
			/*!
			*
			* Pozwala edytować informacje o wyświetlanym przez kino filmie
			*
			*/
			void edytujFilm()
			{
				
				system("pause");
			}
			
			
			//! Funkcja edytujSeans
			/*!
			*
			* Pozwala edytować zaplanowany seans.
			*
			*/
			void edytujSeans()
			{
				
				system("pause");
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
			plik = json::parse(f);
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
			cout<<"Czy chcesdz wybrać któryś z seansów?"<<endl<<">";
			cin>>wybor;
			while(!isdigit(wybor))
			{
				
				
				fflush(stdin);
				cout<<">";
				cin>>wybor;
			};
			
		
		}
		//! Funkcja wybierzSeans
		/*!
		*
		* Funkcja służąca do umożliwienia użytkownikowi wybranie pożądanego przez niego seansu
		*
		*/
		void wybierzSeans()
		{
			
				system("pause");
		}
		
		//! Funkcja wybierzMiejsca
		/*!
		*
		* Funkcja umożliwiająca użytkownikowi zarezerwowanie miejsca na wybranym seansie
		*
		*/
		void wybierzMiejsca()
		{
			
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
	public:
		
		
		//! Funkcja Start
		/*!
		* Funkcja inicjalizująca menu główne, z którego użytkownik może przemieszczać się po programie
		*/
		int start()
		{
			int wybor;
			
			cout<<"Witaj w serwisie CineBooker."<<endl<<endl;
			cout<<"[1] -- Login"<<endl;
			cout<<"[2] -- Przegladaj repertuar"<<endl;
			cout<<">";
			cin>>wybor;
			
			this->inputHandler(wybor);	
		}
	private:
		
		Admin adm; /*!< Obiekt klasy Admin */
		Repertuar rp; /*!< Obiekt klasy Repertuar */
		UserHandle uh; /*!< Obiekt klasy userHandle */
		
		//! Funkcja inputHandler
		/*!
		* Funkcja obsługująca wybór dokonany przez użytkownika w funkcji start(). Zależnie od wartości wpisanej przez użytkownika, funkcja handler() odsyła go do innych metod i klas zawartych w programie.
		*/
		void inputHandler(int wybor)
		{
			
			switch(wybor)
			{
				case 1:
					system("cls");
					uh.login();
					break;
				case 2:
					system("cls");
					rp.wyswietlRepertuar();
					break;					
				case 3:
					system("cls");
					adm.lobbyAdmin();
					break;
					
			}
			
				system("pause");
			
		}
	
};



//===================================================================================================================================================================================================
int main(int argc, char** argv) {
	
	Controller c;
//	c.start();
	Repertuar r;
	r.wyswietlRepertuar();
	//fstream f("uzytkownicy.json");
	
	
	
//	json xd = json::parse(f);
	/*cout<<xd.at("nazwaUzytkownika").at(0)<<endl;
	//xd["tytul"][1] = "xd2";
	if(xd["admin"][0]==nullptr)
	{
		cout<<xd;
		
	}
	int i = 0;
	
	for(auto _ : xd)
	{
		cout<<xd["username"][i]<<" | ";
		cout<<xd["password"][i]<<" | ";
		cout<<xd["admin"][i]<<" | ";
		cout<<endl;
		i++;
	}
	*/



	system("pause");
	return 0;
}