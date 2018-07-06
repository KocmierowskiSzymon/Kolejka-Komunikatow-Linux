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
		
		char message [100];
		
	}que;

/*---------------------------------------------------------------------*/



/*----------- Zmienna globalna -----------*/

	int end = 1;

/*----------------------------------------*/	



/*--------------- Glowna funkcja programu ----------------*/

	int main(int argum, char *names[])
	{
		/*-----------------------------------------*/
		
			/* Funkcja msgget z flaga IPC_CREATE powoduje
			
			   utworzenie nowego obiektu z zadanym kluczem
			   
			   ktory bedzie przyjmowal wartosci przychodzacych 
			   
			   paczek wiadomosci. Zostala utworzona struktura
			   
			   do ktorej beda przepisywane odbierane wiadomosci */
		
			int queueamsg = msgget(1234, IPC_CREAT|0666);
		
			que mess;
		
		/*---------------------------------------------*/
		
		
		
		
		/*-----------------------------------------------*/
		
			/* W petli za pomoca funckji msgrcv odbierane
			   
			   sa obiekty z wiadomoscia, ktore maja taki
			   
			   sam klucz, jak stworzony wczesniej obiekt 
			   
			   queuemsg. Zapisywane sa 100 bajtow wiadomosci
			   
			   i identyfikator procesu wysylajacego do obiektu mess.
			   
			   Jesli wiadomosc rozpoczyna sievod znaku " @ ", to wszystkie
			   
			   nieodebrane wiadomosci sa zwalniane z pamieci, obiekt 
			   
			   queuemsg jest usuwany, a proces konczy swoje dzialanie  */
		
			while(end)
			{
			
				msgrcv(queuemsg, &mess, sizeof(mess.message) + 1, mess.type, 0);
				
				printf("Odebralem wiadomosc od procesu o numerze: %ld\n", mess.type);
				
				printf("Proces %d: %s\n", getpid(), mess.message);
				
				
				if(mess.message [0] == '@')
				{
						
						msgctl(queuemsg, IPC_RMID, NULL);
						
						return 0;
						
				}
				
			}
			
		/*-----------------------------------------------------*/
	}
	
/*---------------------------------------------------------*/	
