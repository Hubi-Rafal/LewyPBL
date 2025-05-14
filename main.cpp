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

/*
class User
{
	private:
		bool zalogowany;
		bool admin;
		ifstream f;
		json plik;
	
	
	public:
		User()
		{
			f.open("uzytkownicy.json");
			plik = json::parse(f);
			zalogowany = 0;
			admin = 0;
		}
	
		string login()
        {
        	system("cls");
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
					if(element["username"]==us)
					{
					 	
						while(!(pass == element["password"]))
						{
							system("cls");
		
							cout<<"znaleziono username, podaj haslo"<<endl<<">";
							cin>>pass;

							if(pass == element["password"])
							{	
								system("cls");
								return us;
								break;
							}
						}
					}else
					{
						cout<<"Nie znaleziono podanej nazwy uzytkownika, sprobuj ponownie nobie"<<endl;
					//	continue;
					}

				}
				
			}


        }
        void logout()
        {
        	cout<<"logout";
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
			while(!(cin>>wybor))
			{
				
				cin.clear();
				cin.ignore(40,'\n');
				cout<<">";
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
		
		Controller()
		{
			zalogowany = 0;
			
		}
		//! Funkcja Start
		/*!
		* Funkcja inicjalizująca menu główne, z którego użytkownik może przemieszczać się po programie
		*/
/*		int start()
		{
			int wybor;
			while(wybor!=4)
			{
				
				User u;
				if(zalogowany == 0)
				{
					cout<<"Witaj w menu głównym serwisu CineBooker."<<endl<<endl;
					cout<<"[1] -- Login"<<endl;
					cout<<"[2] -- Przegladaj repertuar"<<endl;
					cout<<"[4] -- Wyjdz"<<endl;
					cout<<">";
					cin>>wybor;
					switch(wybor)
					{
						case 1:
							
							username = u.login();
							if(username!="0")
							{
								zalogowany = 1;
								break;
							}
							break;
						case 2:
							rp.wyswietlRepertuar();
							break;
					}	
				}else
				{
				
					cin.clear();
					cout<<"[1] -- Wyloguj"<<endl;
					cout<<"[2] -- Przegladaj repertuar"<<endl;
					cout<<"[4] -- Wyjdz"<<endl;
					cout<<username<<">";
					cin>>wybor;
					switch(wybor)
					{
						case 1:
							u.logout();
							break;
					}
				
				}
	
			
		
			
			}

				
		}
			
	*/
	private:
		
		Repertuar rp; /*!< Obiekt klasy Repertuar */
		int zalogowany;
		string username;		
	
};



//===================================================================================================================================================================================================
int main(int argc, char** argv) {
	
	Controller c;
//	c.start();
//	Repertuar r;
//	r.wyswietlRepertuar();
/*User u;
string a = u.login(result);

if(a[0]=="0")
{
	cout<<"not found";
}else{
	cout<<us;
	int zalogowany = 1;
}*/
	int tab[3][3] = {0,1,2,3,4,5,6,7,8};
	int getchar;
	int polozenie[0][0];
	int x=0,y=0;
	do
	{
		system("cls");
		for(int i = 0;i<3;i++)
		{	
			for(int j = 0;j<3;j++)
			{
				if(i==y && j==x){
					cout<<"| "<<"X"<<" |";
					
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
				if(y<2)
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
				if(x<2)
				{
					++x;					
				}

				break;
			case 13:
				cout<<tab[y][x];
				return 0;
				break;
		}
		
	}while(x!=13);
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