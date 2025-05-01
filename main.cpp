#include <iostream>
#include <fstream>
#include <stdio.h>
//#include "header_files/repertuar.h"
//#include "header_files/admin.h"

using namespace std;
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
			* Funkcja umożliwiająca użytkownikowi zalogowanie się do serwisu
			*
			*/
            void login()
            {

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
            
            
            void platnosc()
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
			}
			//! Funkcja edytujFilm
			/*!
			*
			* Pozwala edytować informacje o wyświetlanym przez kino filmie
			*
			*/
			void edytujFilm()
			{
				
			}
			
			
			//! Funkcja edytujSeans
			/*!
			*
			* Pozwala edytować zaplanowany seans.
			*
			*/
			void edytujSeans()
			{
				
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
		
		//! Funkcja lineCount
		/*!
		*
		* Funkcja obliczająca długość pliku służącego w programie za 'bazę danych'. Na podstawie uzyskanej wartości program ustanawia wielkość tablicy przechowującej informacje o seansach, oraz ilość tych seansów.
		*
		*/
		int lineCount() 
		{
			fstream plik;
			plik.open("repertuar.txt",ios::in);
			string tekst;
			int lines = 0;
			while(!plik.eof())
			{
				getline(plik,tekst);
				++lines;
			}
			plik.close();
			return lines;
		}
		//! Funkcja wyswietlRepertuar
		/*!
		*
		* Funkcja która wypisuje w konsoli informacje o aktualnym  repertuarze sali kinowej. Na chwilę obecną informacje te stanowią: Tytuł filmu, Godzina rozpoczęcia seansu, Język filmu oraz jego typ (2d lub 3d)
		*
		*/
		void wyswietlRepertuar()
		{	
			fstream plik;
			string text;
			
			int lines = lineCount();

			
			plik.open("repertuar.txt",ios::in);
			
			cout<<"=========== REPERTUAR ============="<<endl<<endl;
			int atrybutyFilmu = 4;
			
			string filmy[atrybutyFilmu][lines];
			
			int i, j;
			for(i=0;i<lines;++i)
			{
				for(j = 0;j<atrybutyFilmu;++j)
				{
					getline(plik,filmy[j][i]);

				}
			}
			
			
			for(int nrSeansu = 0; nrSeansu<lines/4; nrSeansu++)
			{
				cout<<"############# Seans #"<<nrSeansu+1<<" #############"<<endl;
				cout<<"#  Tytul filmu: "<<filmy[0][nrSeansu]<<endl;
				cout<<"#  Godzina rozpoczecia: "<<filmy[1][nrSeansu]<<endl;
				cout<<"#  Jezyk: "<<filmy[2][nrSeansu]<<endl;
				cout<<"#  Typ (2d/3d): "<<filmy[3][nrSeansu]<<endl;
				cout<<"####################################"<<endl<<endl;
				
			}
		}
		//! Funkcja wybierzSeans
		/*!
		*
		* Funkcja służąca do umożliwienia użytkownikowi wybranie pożądanego przez niego seansu
		*
		*/
		void wybierzSeans()
		{
			
		}
		
		//! Funkcja wybierzMiejsca
		/*!
		*
		* Funkcja umożliwiająca użytkownikowi zarezerwowanie miejsca na wybranym seansie
		*
		*/
		void wybierzMiejsca()
		{
			
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
		
		Admin adm; /*!< Obiekt klasy Admin znajdującej się w pliku admin.h */
		Repertuar rp; /*!< Obiekt klasy Repertuar znajdującej się w pliku repertuar.h */
		
		//! Funkcja inputHandler
		/*!
		* Funkcja obsługująca wybór dokonany przez użytkownika w funkcji start(). Zależnie od wartości wpisanej przez użytkownika, funkcja handler() odsyła go do innych metod i klas zawartych w programie.
		*/
		void inputHandler(int wybor)
		{
			
			switch(wybor)
			{
				case 1:
					cout<<"Welcome user";
					break;
				case 2:
					system("cls");
					rp.wyswietl_repertuar();
					break;					
				case 3:
					system("cls");
					adm.lobbyAdmin();
					break;
					
			}
			
		}
	
};



//===================================================================================================================================================================================================
int main(int argc, char** argv) {
	
	Controller c;
	c.start();

	system("pause");
	return 0;
}