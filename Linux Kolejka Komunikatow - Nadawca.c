/*--- Program byl pisany, aby byla mozliwosc jego skompilowania ---*/

/*---        oraz uruchomienia w terminale systemu linux        ---*/

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <sys/ipc.h>

#include <sys/msg.h>

#include <sys/types.h>

#include <unistd.h>


/*---- Struktura odpowiadajaca za odbior 100 bajtow wiadomosci----*/

	typedef struct queue 
	{
		
		long type;
		
		char message[100];
		
	}que;
	
/*------------------------------------------------------------------*/



/*------------------ Zmienne globalne ---------------------------*/

	char text [100];
	
	int end = 1, length;
	
/*---------------------------------------------------------------*/



/*------------------------- Glowna funkcja programu ---------------------------*/

	int main(void)
	{
	
	/*-----------------------------------------------------------*/
		
		/*  Funkcja msgget z flaga IPC_CREATE powoduje
			
			utworzenie nowego obiektu z zadanym kluczem
			   
			ktory bedzie przyjmowal wartosci wysylanych
			   
			paczek wiadomosci.        */
		
		int queuemsg = msgget(1234, IPC_CREAT|0666);
		
	/*--------------------------------------------------------------*/
	
	
	
	/*------------------------------------------------------------------*/
	
		/*	W petli dzieki funkcji fgets nastepuje przechwycenie tekstu 
		
			zapisanego w terminalu do zmiennej text. Przepisywane jest
			
			maksymalnie 100 znakow. Jesli wprowadzony tekst rozpoczyna sie
			
			od znaku " @ ", to wartosc zmiennej end jest ustawiana na 0,
			
			tworzony jest obiekt paczki wiadomosci mess, do zmiennej type
			
			w paczce zapisywany jest identyfikator procesu wysylajacego paczke.
			
			Nastpenie kopiowany jest ciag znakow z zmiennej text do zmiennej 
			
			w obiekcie message. Do zmiennej length zapisywana jest dlugosc
			
			przepisanego ciagu znakow, po czym wysylany jest ostatni komunikat.
			
			Na koniec zwalniane sa wszyskie nieodebrane komunikaty sa zwalniane
			
			z pamieci, obiekt queuemsg jest usuwany, a proces konczy swoje dzialanie */	
	
		while(end)
		{
			
			fgets(text, 100, stdin);
			
			if(text [0] == '@')
			{
				
				end = 0;
				
				que mess;
				
				mess.type = getpid();
				
				strcpy(mess.message, text);
				
				length = strlen(mess.message) + 1;
				
				msgsnd(queuemsg, &mess, length, 0);
				
				msgctl(queuemsg, IPC_RMID, NULL);
				
				return 0;
				
			}
			
			
			
				/*  Jesli wiadomosc nie rozpoczyna sie od znako " @ "\
				
					tworzony jest obiekt paczki wiadomosci mess, do zmiennej type
			
					w paczce zapisywany jest identyfikator procesu wysylajacego paczke.
			
					Nastpenie kopiowany jest ciag znakow z zmiennej text do zmiennej 
			
					w obiekcie message. Do zmiennej length zapisywana jest dlugosc
			
					przepisanego ciagu znakow, po czym wysylany jest ostatni komunikat.  */
			
				else
				{
					
					kolej mess;
					
					mess.type = getpid();
				
					strcpy(mess.message, text);
				
					length = strlen(mess.message) + 1;
				
					msgsnd(queuemsg, &mess, length, 0);
				
				}
			
		}	
	}
