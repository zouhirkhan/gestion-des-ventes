#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
//#include <Myconio.h>
#include <windows.h>
#define MAX 100

const int BTN_ENTER=13;
const int BTN_SPACE=32;
const int BTN_BACKSPACE=8;
const int BTN_ESC=27;

void gotoxy(int x, int y)
{
COORD coord;
coord.X = x;
coord.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void textcolor(int ForgC)
 {
 WORD wColor;

  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
                 //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
 }
 return;
}

 void input();
 void writefile();
 void search();
 void output();
 void Date_Sys();
 void Articl_REC();
 void Time_REC();
 void AffichSpace();
 
FILE *fp;
 
  struct Compte {	
  	char CIN[10];
	char NOMC[25];
	char PREC[25];
	char TelePhon[10];
	float RestePayment;
	float Payment;
	char DatePay[10];	
  }Client;
  
  struct Saisie
{   char ART[MAX];
    float PRIX;
}Saisie;

struct Date{	
	   int jour;
	   int mois;
	   int an;
	   }Date;
	   
char NOMC[25]; //clientNom[25]
char PREC[25]; // clientPrenom[25]
char CIN[10];
struct Saisie To[MAX];
  
int tl,sl,ts;
int y,i;
char ch;
int j;
char ch;
char choix;
int size = 0;   
int pos; // positionArticle
float TOPRIX=0;//Total Prix
int h, min, s;

int main()
{
	system("MODE CON COLS=167 LINES=9999");//sets window size!
	
    char NOMC[25]; //clientNom[25]
    char PREC[25]; // clientPrenom[25]  
 
ECHEC :
     system("cls");
     Date_Sys();
      size = 0;
      
     do{
        for( i=1;i<75;i++){gotoxy(i,5);textcolor(4);printf("Ü");} 
        for( i=91;i<167;i++){gotoxy(i,5);textcolor(4);printf("Ü");} 
	
        for( y=15;y<28;y++){gotoxy(62,y);textcolor(13);printf("บ");}
        for( y=15;y<28;y++){gotoxy(108,y);textcolor(13);printf("บ");}
 
      gotoxy(76,6);textcolor(14);printf("MENU PRINCIPAL");
      gotoxy(62,14);textcolor(13);printf("ษอออออออออออออออออออออออออออออออออออออออออออออป"); 
	  gotoxy(63,17);textcolor(14);printf("         1 -    Nouvelle Saisie");
	  gotoxy(63,19);textcolor(14);printf("         2 -    Facturation");
	  gotoxy(63,21);textcolor(14);printf("         3 -    L'historique Client");
	  gotoxy(62,24);textcolor(13);printf("ฬอออออออออออออออออออออออออออออออออออออออออออออน");
	  gotoxy(62,28);textcolor(13);printf("ศอออออออออออออออออออออออออออออออออออออออออออออผ");	  
	       
	       	     	 do{
        gotoxy(66,26);textcolor(4);printf("    Tapez numero du choix desirez ");
          Sleep(400);
        gotoxy(66,26);textcolor(14);printf("    Tapez numero du choix desirez ");
          Sleep(400);       				
		 }while(!kbhit());
		     
	       choix=getche();
	  }while(choix<='0' || choix>'3');
	  
   system("cls");
    switch(choix)
    {
    case '1':
    {
START :
        system("cls");
          Date_Sys();
          
        for( i=1;i<75;i++){gotoxy(i,5);textcolor(4);printf("Ü");} 
        for( i=92;i<167;i++){gotoxy(i,5);textcolor(4);printf("Ü");}
       
        gotoxy(1,2);textcolor(3);printf(" - Pour continuer l'operation tapez : ENTER");
        gotoxy(39,2);textcolor(14);printf("ENTER");
        gotoxy(1,3);textcolor(3);printf(" - Pour annuler l'operation tapez : ESC");
        gotoxy(37,3);textcolor(14);printf("ESC");
        gotoxy(76,6);textcolor(3);printf("NOUVELLE SAISIE");
        
        for( y=16;y<23;y++){gotoxy(60,y);textcolor(4);printf("บ");}
        for( y=16;y<23;y++){gotoxy(112,y);textcolor(4);printf("บ");} 
        gotoxy(60,16);textcolor(4);printf("ษอออออออออออออออออออออออออออออออออออออออออออออออออออป");
        gotoxy(60,23);textcolor(4);printf("ศอออออออออออออออออออออออออออออออออออออออออออออออออออผ");
 
		   	     	 do{
         gotoxy(72,19);textcolor(4);printf("- CIN Client: ");
          Sleep(400);
         gotoxy(72,19);textcolor(14);printf("- CIN Client: ");
          Sleep(400);        				
		 }while(!kbhit());
     
	     gotoxy(86,19);textcolor(13);scanf("%s",CIN);
		 
		 for (j = 0; CIN[j]!='\0'; j++){
	         if((CIN[j] >= 'A' && CIN[j] <= 'Z') || (CIN[j] >= 'a' && CIN[j] <= 'z') || (CIN[j] >= '0' && CIN[j] <= '9'))	
	              strupr(CIN);
		 
        else{
         gotoxy(70,25);textcolor(3);printf("- saisie incorrecte !!");
         gotoxy(70,26);textcolor(3);printf("- Tapez (ENTER) pour r้essaye:");
         gotoxy(79,26);textcolor(14);printf("ENTER");
         
         	ch = getch();  
            goto START;
         }  
        }          
        ch = getch();
        if(ch == BTN_ESC)
            goto START;
        
        char filename[38]; // client_cin
        
        strcpy(filename, "datasource/client_");
        strcat(filename,CIN);
        strcat(filename,".txt");
        int exist = cfileexists(filename);
        
    	if(!exist){	
    		gotoxy(70,27);textcolor(3);printf("- Tapez (ENTER) pour le Ajouter ");
            gotoxy(79,27);textcolor(14);printf("ENTER");
            gotoxy(60,28);textcolor(3);printf(" - Tapez autre touche pour retour au MENU PRINCIPAL .");
    			   	     	 do{
         gotoxy(60,25);textcolor(4);printf("Ce Client n'existe pas. Ajouter comme nouveau client ? ");
          Sleep(400);
         gotoxy(60,25);textcolor(14);printf("Ce Client n'existe pas. Ajouter comme nouveau client ? ");
          Sleep(400);        				
		 }while(!kbhit());
		 
    		ch = getch();
    	
        	if(ch != BTN_ENTER){
        			goto START;           	
			}
            
            else{
            	 system("cls");
            		 Date_Sys();
        for( i=1;i<75;i++){gotoxy(i,4);textcolor(4);printf("Ü");} 
        for( i=92;i<167;i++){gotoxy(i,4);textcolor(4);printf("Ü");}
       
        gotoxy(1,2);textcolor(3);printf(" - Pour continuer l'operation tapez : ENTER");
        gotoxy(39,2);textcolor(14);printf("ENTER");
        gotoxy(1,3);textcolor(3);printf(" - Pour annuler l'operation tapez : ESC");
        gotoxy(37,3);textcolor(14);printf("ESC");
        gotoxy(76,5);textcolor(3);printf("NOUVELLE SAISIE");
        for( y=16;y<23;y++){gotoxy(60,y);textcolor(4);printf("บ");}
        for( y=16;y<23;y++){gotoxy(114,y);textcolor(4);printf("บ");} 
        gotoxy(60,16);textcolor(4);printf("ษอออออออออออออออออออออออออออออออออออออออออออออออออออออป");
        gotoxy(60,23);textcolor(4);printf("ศอออออออออออออออออออออออออออออออออออออออออออออออออออออผ");
        gotoxy(70,17);textcolor(4);printf("- CIN : ");
        gotoxy(78,17);textcolor(14);printf("%s",CIN);
		        do{ 	
					gotoxy(70,19);textcolor(4);printf("- Nom Client : ");
					Sleep(400);
					gotoxy(70,19);textcolor(14);printf("- Nom Client : ");
					Sleep(400);
				}while(!kbhit());
		  
		    	textcolor(3);gotoxy(85,19);scanf("%s",NOMC);
		    
				for (j = 0; NOMC[j]!='\0'; j++){
				    if((NOMC[j] >= 'A' && NOMC[j] <= 'Z') || (NOMC[j] >= 'a' && NOMC[j] <= 'z') || (NOMC[j] == ' '))
				        	strupr(NOMC);
				    else{
				        gotoxy(70,25);textcolor(3);printf("- Nom incorrect !!");
				        gotoxy(70,26);textcolor(3);printf("- Tapez (ENTER) pour r้essaye:");
				        gotoxy(79,26);textcolor(14);printf("ENTER");
					        ch = getch();  
				            goto START;
				    }
			    }	    		  
				do{
		        	gotoxy(70,21);textcolor(4);printf("- Prenom Client : ");
		        	Sleep(400);
		        	gotoxy(70,21);textcolor(14);printf("- Prenom Client : ");
		    		Sleep(400); 				
				}while(!kbhit());
				 
				textcolor(3);gotoxy(88,21);scanf("%s",PREC);	 
				 
		        for (j = 0; PREC[j]!='\0'; j++){
			        if((PREC[j] >= 'A' && PREC[j] <= 'Z') || (PREC[j] >= 'a' && PREC[j] <= 'z') || (PREC[j] == ' '))	
			            strupr(PREC);
				 
			        else{
				        gotoxy(70,25);textcolor(3);printf("- PreNom incorrect !!");
				        gotoxy(70,26);textcolor(3);printf("- Tapez (ENTER) pour r้essaye:");
				        gotoxy(79,26);textcolor(14);printf("ENTER");
				         
			        	ch = getch();  
			            goto START;
			        }
		        }
		        FILE *fs=fopen(filename,"wb");
				fprintf(fs,"\n%s %s\n",NOMC,PREC);
				fclose(fs);
			}
		}
             
	 FILE *fp=fopen(filename,"ab");
	 
	 if(fp == NULL)
   {
      printf("Error!");   
      exit(1);  
	             
   }else{	  
	 system("cls");

	  char nom_prenom_client[100];
	
    FILE *fs=fopen(filename,"rb");
	fgets (nom_prenom_client, 100, fs);
	fclose(fs);
	
        gotoxy(1,2);textcolor(3);printf(" - Pour calculer le total tapez : SPACE");
        gotoxy(35,2);textcolor(14);printf("SPACE");
        gotoxy(1,3);textcolor(3);printf(" - Pour continuer l'operation tapez : ENTER");
        gotoxy(39,3);textcolor(14);printf("ENTER");
        gotoxy(1,4);textcolor(3);printf(" - Pour supprimer un article : BACKSPACE");
        gotoxy(32,4);textcolor(14);printf("BACKSPACE");
        gotoxy(1,5);textcolor(3);printf(" - Pour annuler l'operation tapez : ESC");
        gotoxy(37,5);textcolor(14);printf("ESC");		      

        gotoxy(70,3);textcolor(2);printf("CLIENT : ");
        gotoxy(79,3);textcolor(14);printf("%s %s",CIN,nom_prenom_client);
        
           Date_Sys();
           
       for( i=1;i<167;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
        printf("\n");
                
        for( i=0; i < 100; i++)
        {
            size++;
CALCUL :    
            fflush(stdin);	  
            AffichSpace();
            textcolor(11);printf("- Nom Article %d : ",i+1);
            textcolor(14);gets(To[i].ART);
            AffichSpace();
            textcolor(12);printf("- Prix Article %d : ",i+1);
            textcolor(14);scanf("%f",&To[i].PRIX);   

            TOPRIX = TOPRIX + To[i].PRIX;
     
            ch = getch();

            if(ch == BTN_ESC)
                goto ECHEC;

            if(ch == BTN_BACKSPACE)
            {
SUPR :
                system("cls");

        gotoxy(1,2);textcolor(3);printf(" - Pour calculer le total tapez : SPACE");
        gotoxy(35,2);textcolor(14);printf("SPACE");
        gotoxy(1,3);textcolor(3);printf(" - Pour continuer l'operation tapez : ENTER");
        gotoxy(39,3);textcolor(14);printf("ENTER");
        gotoxy(1,4);textcolor(3);printf(" - Pour supprimer un article : BACKSPACE");
        gotoxy(32,4);textcolor(14);printf("BACKSPACE");
        gotoxy(1,5);textcolor(3);printf(" - Pour annuler l'operation tapez : ESC");
        gotoxy(37,5);textcolor(14);printf("ESC");
        
        gotoxy(70,3);textcolor(2);printf("CLIENT : ");
        gotoxy(79,3);textcolor(14);printf("%s %s",CIN,nom_prenom_client);
            Date_Sys();
           
        for( i=1;i<167;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
        printf("\n");
        
                AffichSpace();
                textcolor(14);printf("- Les articles sont :\n\n");
                for(i=0; i<size; i++)
                {
                    AffichSpace();
                    textcolor(11);printf("- Article %d = %s",i+1,To[i].ART);
                    AffichSpace();
                    textcolor(12);printf("- Prix %d = %.2f\n",i+1,To[i].PRIX);                  
                }

                // Position de l'๏ฟฝl๏ฟฝment d'entr๏ฟฝe ๏ฟฝ supprimer
                AffichSpace();
                textcolor(14);printf("- Enter numero d'article que vous voulez supprimer : ");
                scanf("%d", &pos);
                 Date_Sys();
                // Position de suppression non valide
                if(pos < 0 || pos > size)
                {
                    AffichSpace();
                    textcolor(3);printf("- SVP entrer un article enter 1 to %d", size);
                }
                else
                {
                    // soustraire le prix de l'article supprim๏ฟฝ
                    TOPRIX = TOPRIX - To[pos-1].PRIX;

                    // Copier la valeur de l'๏ฟฝl๏ฟฝment suivant dans l'๏ฟฝl๏ฟฝment actuel
                    for( j=pos-1; j < size-1; j++)
                    {
                        To[j].PRIX= To[j+1].PRIX;
                    }
                    for( i=pos-1; i<size-1; i++)
                    {
                        strcpy(To[i].ART, To[i+1].ART);
                    }
                    // D๏ฟฝcr๏ฟฝmenter la taille du tableau de 1
                    size--;
                }
                // Tableau d'impression apr๏ฟฝs suppression
                system("cls");
                 
        gotoxy(1,2);textcolor(3);printf(" - Pour calculer le total tapez : SPACE");
        gotoxy(35,2);textcolor(14);printf("SPACE");
        gotoxy(1,3);textcolor(3);printf(" - Pour continuer l'operation tapez : ENTER");
        gotoxy(39,3);textcolor(14);printf("ENTER");
        gotoxy(1,4);textcolor(3);printf(" - Pour supprimer un article : BACKSPACE");
        gotoxy(32,4);textcolor(14);printf("BACKSPACE");
        gotoxy(1,5);textcolor(3);printf(" - Pour annuler l'operation tapez : ESC");
        gotoxy(37,5);textcolor(14);printf("ESC");
        
        gotoxy(70,3);textcolor(2);printf("CLIENT : ");
        gotoxy(79,3);textcolor(14);printf("%s %s",CIN,nom_prenom_client);
        
            Date_Sys();
           
        for( i=1;i<167;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
        printf("\n");
        
                AffichSpace();
                textcolor(10);printf("- Les articles sont : \n\n");

                for( i=0; i < size; i++)
                {
                    AffichSpace();
                   textcolor(11); printf("- Article %d = %s",i+1,To[i].ART);
                    AffichSpace();
                   textcolor(12); printf("- Prix %d = %.2f\n",i+1,To[i].PRIX);     
                }                          
                ch = getch();
                if(ch == BTN_ESC)
                    goto ECHEC;
                else if(ch == BTN_SPACE)
                    goto TOTAL;
                else if(ch == BTN_ENTER)
                    goto CALCUL;
                else if(ch == BTN_BACKSPACE)               
                    goto SUPR;               
                else
                    goto TOTAL; 			             
            }
            
            //enregistrement des article + time + total
       fprintf(fp,"\n- Nom Article  : %s \n",To[i].ART);
       fprintf(fp,"- Prix Article : %.2f ",To[i].PRIX);
   
            if(ch == BTN_SPACE)          
                goto TOTAL;            
        }     
      
TOTAL :
         Time_REC(filename);
        
        fprintf(fp,"\n\n= Total prix : %.2f ",TOPRIX); 
        fprintf(fp,"\nฤฤฤฤฤฤฤฤฤฤฤฤฤฤ\n");
          textcolor(4);printf("\nÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ\n\n");
          AffichSpace();
          textcolor(14);printf("- Total prix est : %.2f ",TOPRIX);
          AffichSpace();
          textcolor(4);printf("อออออออออออออออออออออออออออ\n\n");
          textcolor(3);printf(" - Pour une (NOUVELLE SAISIE) tapez : ");
          textcolor(14);printf("SPACE\n");
          textcolor(3);printf(" - Tapez autre touche pour retour au MENU PRINCIPAL .");
          textcolor(14);printf("\n\n\n");
             
        TOPRIX=0;
        Date_Sys();
 
	       }  
	  fclose(fp);
	  
            ch = getch();
        if(ch == BTN_SPACE)
            goto START;
        else
            goto ECHEC;	
} break;

    case '2':
    { 
     int n;
HISTO :	  
	   system("cls");

	 //    _setcursortype(_NOCURSOR);
	  	  Date_Sys();
	    for( i=1;i<75;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
        for( i=95;i<167;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
		gotoxy(76,7);textcolor(14);printf("FACTURATION CLIENT");
        for( y=15;y<28;y++){gotoxy(62,y);textcolor(13);printf("บ");}
        for( y=15;y<28;y++){gotoxy(108,y);textcolor(13);printf("บ");}
 
      gotoxy(62,14);textcolor(13);printf("ษอออออออออออออออออออออออออออออออออออออออออออออป"); 
	  gotoxy(63,16);textcolor(2);printf("       1 -    Ajouter une facture");
	  gotoxy(63,18);textcolor(2);printf("       2 -    Rechercher une facture");
	  gotoxy(63,20);textcolor(2);printf("       3 -    Supprimer une facture");
	  gotoxy(63,22);textcolor(2);printf("       4 -    Menu Principal");  
	  gotoxy(62,24);textcolor(13);printf("ฬอออออออออออออออออออออออออออออออออออออออออออออน");
	  gotoxy(62,28);textcolor(13);printf("ศอออออออออออออออออออออออออออออออออออออออออออออผ");
	 
	  do{
	       
	       	     	 do{
        gotoxy(66,26);textcolor(4);printf("    Tapez numero du choix desirez ");
          Sleep(400);
        gotoxy(66,26);textcolor(14);printf("    Tapez numero du choix desirez ");
          Sleep(400);        				
		 }while(!kbhit());
	       
	       ch=getche();
	  }while(ch<='0' || ch>'4');
	  switch(ch){
		case '1':{
AJOUTE :							
             system("cls");
             Date_Sys();
        for( i=1;i<75;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
        for( i=96;i<167;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
		gotoxy(76,7);textcolor(14);printf("AJOUTER UNE FACTURE");
		
		for( y=16;y<23;y++){gotoxy(60,y);textcolor(4);printf("บ");}
        for( y=16;y<23;y++){gotoxy(114,y);textcolor(4);printf("บ");} 
        gotoxy(60,16);textcolor(4);printf("ษอออออออออออออออออออออออออออออออออออออออออออออออออออออป");
        gotoxy(60,23);textcolor(4);printf("ศอออออออออออออออออออออออออออออออออออออออออออออออออออออผ");      
        
        	     	 do{
         gotoxy(72,19);textcolor(4);printf("- CIN Client: ");
          Sleep(400);
         gotoxy(72,19);textcolor(14);printf("- CIN Client: ");
          Sleep(400);        				
		 }while(!kbhit());
     
	     gotoxy(86,19);textcolor(13);scanf("%s",Client.CIN);
		 
		 for (j = 0; Client.CIN[j]!='\0'; j++){
	         if((Client.CIN[j] >= 'A' && Client.CIN[j] <= 'Z') || (Client.CIN[j] >= 'a' && Client.CIN[j] <= 'z') || (Client.CIN[j] >= '0' && Client.CIN[j] <= '9'))	
	              strupr(Client.CIN);		 
        else{   	
         gotoxy(70,25);textcolor(3);printf("- saisie incorrecte !!");
         gotoxy(70,26);textcolor(3);printf("- Tapez (ENTER) pour r้essaye:");
         gotoxy(79,26);textcolor(14);printf("ENTER");
         
         	ch = getch();  
            goto HISTO;
         }
        }
        char Filename[38]; // client_cin
        FILE *fp;
        
        strcpy(Filename, "datafacture/client_");
        strcat(Filename,Client.CIN);
        strcat(Filename,".txt");
        int exist = cfileexists(Filename);
        
        fp=fopen(Filename,"ab");	     
	  
    	if(!exist){
    		     // clrscr();
    			 Date_Sys();
                 for( i=1;i<75;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
                 for( i=96;i<167;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
	           	 gotoxy(76,7);textcolor(14);printf("AJOUTER UNE FACTURE");
		  		
    		gotoxy(60,26);textcolor(3);printf(" - Pour Ajouter un client tapez : ENTER");
            gotoxy(94,26);textcolor(14);printf("ENTER");
            gotoxy(60,27);textcolor(3);printf(" - Pour Rechercher un client tapez : SPACE");
            gotoxy(97,27);textcolor(14);printf("SPACE");
            gotoxy(60,28);textcolor(3);printf(" - Tapez autre touche pour retour au MENU PRINCIPAL .");
            
            	     	 do{
         gotoxy(60,24);textcolor(14);printf("Ce client n'existe pas. Ajouter comme nouveau client ? ");
          Sleep(400);
         gotoxy(60,24);textcolor(4);printf("Ce client n'existe pas. Ajouter comme nouveau client ? ");
          Sleep(400);        				
		 }while(!kbhit());

    	     ch = getch(); 
        	if(ch != BTN_ENTER){
        		goto HISTO;           	
			}
            
   else{
         system("cls");
           Date_Sys(); 
           rewind(fp);
		for( i=1;i<75;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
        for( i=96;i<167;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
		gotoxy(76,7);textcolor(14);printf("AJOUTER UNE FACTURE");
		
      gotoxy(60,10);textcolor(13);printf("CIN Client         :");
	  gotoxy(82,10);textcolor(14);printf("%s",Client.CIN);
      gotoxy(60,11);textcolor(13);printf("Nom Client         :");
	  gotoxy(82,11);textcolor(14);scanf("%s",Client.NOMC);
	  gotoxy(60,12);textcolor(13);printf("PreNom Client      :");
	  gotoxy(82,12);textcolor(14);scanf("%s",Client.PREC);
	  gotoxy(60,13);textcolor(13);printf("Telephone no       :");
	  gotoxy(82,13);textcolor(14);scanf("%s",&Client.TelePhon);
	  gotoxy(60,14);textcolor(13);printf("Reste de Paiement  :");
	  gotoxy(82,14);textcolor(14);scanf("%f",&Client.RestePayment);
	  gotoxy(60,15);textcolor(13);printf("Paiement actuel    :");
	  gotoxy(82,15);textcolor(14);scanf("%f",&Client.Payment);
	  gotoxy(60,16);textcolor(13);printf("date Payment(J/M/A):");
	  gotoxy(82,16);textcolor(14);scanf("%s",Client.DatePay);
	  
	    fwrite(&Client,sizeof(Client),1,fp);	
	    
	  gotoxy(1,2);textcolor(3);printf(" - Pour Ajouter un autre client tapez : SPACE");
      gotoxy(41,2);textcolor(14);printf("SPACE");
      gotoxy(1,3);textcolor(3);printf(" - Pour Rechercher un client tapez : ENTER");
      gotoxy(38,3);textcolor(14);printf("ENTER");
      gotoxy(1,4);textcolor(3);printf(" - Tapez autre touche pour retour au MENU PRINCIPAL .");	 
	             
      fclose(fp);
      
	   ch = getch();
        if(ch == BTN_ENTER){
           goto CONSULT;	 
		}else if(ch == BTN_SPACE){         
           goto AJOUTE; 	
        }else{
          goto ECHEC;
			}        
   }
         }else{
         	 Date_Sys();
          for( i=1;i<75;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
          for( i=96;i<167;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
	    	gotoxy(76,7);textcolor(14);printf("AJOUTER UNE FACTURE");
		 		
		 	gotoxy(58,26);textcolor(3);printf(" - Pour Ajouter un client tapez : ENTER");
            gotoxy(92,26);textcolor(14);printf("ENTER");
            gotoxy(58,27);textcolor(3);printf(" - Pour Rechercher un client tapez : SPACE");
            gotoxy(95,27);textcolor(14);printf("SPACE");
            gotoxy(58,28);textcolor(3);printf(" - Tapez autre touche pour retour au MENU PRINCIPAL .");
            
    		 do{
         gotoxy(58,24);textcolor(14);printf("- Ce client est deja existe . vous voulez le consulter ? ");
          Sleep(400);
         gotoxy(58,24);textcolor(4);printf("- Ce client est deja existe . vous voulez le consulter ? ");
          Sleep(400);        				
		 }while(!kbhit());
   	
         	ch = getch();
        if(ch == BTN_ENTER)
            goto AJOUTE;
        else if(ch == BTN_SPACE)
            goto CONSULT;
        else
            goto ECHEC;	
}	
		}	break;

		case '2':{
CONSULT :			
				 system("cls");
	//		_setcursortype(_NOCURSOR);
				  Date_Sys();

	   char cin[10];
	   int n,i,m=1;
	   char Filename[38]; // client_cin
        FILE *fp;
	 	   Date_Sys();
	 	   
        for( i=1;i<74;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
        for( i=96;i<167;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
		gotoxy(74,7);textcolor(14);printf("RECHERCHER UNE FACTURE");
        
        for( y=16;y<23;y++){gotoxy(60,y);textcolor(4);printf("บ");}
        for( y=16;y<23;y++){gotoxy(114,y);textcolor(4);printf("บ");} 
        gotoxy(60,16);textcolor(4);printf("ษอออออออออออออออออออออออออออออออออออออออออออออออออออออป");
        gotoxy(60,23);textcolor(4);printf("ศอออออออออออออออออออออออออออออออออออออออออออออออออออออผ");
     
        	     	 do{
         gotoxy(72,19);textcolor(4);printf("- CIN Client: ");
          Sleep(400);
         gotoxy(72,19);textcolor(14);printf("- CIN Client: ");
          Sleep(400);        				
		 }while(!kbhit());
		 
		 textcolor(11);gotoxy(86,19);scanf("%s",cin);
		 
		 for (j = 0; cin[j]!='\0'; j++){
	         if((cin[j] >= 'A' && cin[j] <= 'Z') || (cin[j] >= 'a' && cin[j] <= 'z') || (cin[j] >= '0' && cin[j] <= '9'))	
	              strupr(cin);		 
        else{
        	 Date_Sys();
        for( i=1;i<74;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
        for( i=96;i<167;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
		gotoxy(74,7);textcolor(14);printf("RECHERCHER UNE FACTURE");
		
         gotoxy(70,25);textcolor(3);printf("- saisie incorrecte !!");
         gotoxy(70,26);textcolor(3);printf("- Tapez (ENTER) pour r้essaye:");
         gotoxy(79,26);textcolor(14);printf("ENTER");
         
         	ch = getch();  
            goto HISTO;
         }
}	  
        strcpy(Filename, "datafacture/client_");
        strcat(Filename,cin);
        strcat(Filename,".txt");
        int exist = cfileexists(Filename);
        
   	if(exist){
	             FILE *fp;
	            fp=fopen(Filename,"rb");
	
	        if(fp == NULL)
           {
              printf("Error!");   
              exit(1);  	             
             }else{
		      fseek(fp,0,SEEK_END);
	   	      tl=ftell(fp);
		      sl=sizeof(Client);
		      ts=tl/sl;
		      fseek(fp,(ts-1)*sl,SEEK_SET);
		      fread(&Client,sizeof(Client),1,fp);
	
    //   _setcursortype(_NOCURSOR);
		    	
		       	 Date_Sys();	
		       	 		   
			     fseek(fp,0,SEEK_SET);		
	    while(fread(&Client,sizeof(Client),1,fp)){
			
				 	  system("cls");
			        Date_Sys();
        for( i=1;i<74;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
        for( i=96;i<167;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
		gotoxy(74,7);textcolor(14);printf("RECHERCHER UNE FACTURE");
		
	    gotoxy(70,13);textcolor(12);printf("- CIN client        :");
	    gotoxy(92,13);textcolor(2);printf("%s",Client.CIN);
	    gotoxy(70,14);textcolor(12);printf("- Nom Client        :");
	    gotoxy(92,14);textcolor(2);printf("%s",Client.NOMC);
	    gotoxy(70,15);textcolor(12);printf("- Prenom Client     :");
	    gotoxy(92,15);textcolor(2);printf("%s",Client.PREC);
	    gotoxy(70,16);textcolor(12);printf("- Telephone         :");
	    gotoxy(92,16);textcolor(2);printf("%s",Client.TelePhon);
	    gotoxy(70,17);textcolor(12);printf("- Reste de Paiement :");
	    gotoxy(92,17);textcolor(2);printf("%.2f",Client.RestePayment);
	    gotoxy(70,18);textcolor(12);printf("- Paiement actuel   :");
	    gotoxy(92,18);textcolor(2);printf("%.2f",Client.Payment);
	    gotoxy(70,19);textcolor(12);printf("- Date de paiement  :");
	    gotoxy(92,19);textcolor(2);printf("%s",Client.DatePay);
	   
	   gotoxy(1,2);textcolor(3);printf(" - Pour Ajouter un client tapez : SPACE");
       gotoxy(35,2);textcolor(14);printf("SPACE");
       gotoxy(1,3);textcolor(3);printf(" - Pour Rechercher un client tapez : ENTER");
       gotoxy(38,3);textcolor(14);printf("ENTER");
       gotoxy(1,4);textcolor(3);printf(" - Tapez autre touche pour retour au MENU PRINCIPAL .");
	   	      
        fclose(fp);
	 }	 
	        ch = getch();
        if(ch == BTN_ENTER)
           goto CONSULT; 
        else if(ch == BTN_SPACE)
            goto AJOUTE;
        else
            goto ECHEC;					    					   
}			
			ch = getch();
        if(ch == BTN_ENTER)
            goto AJOUTE;
        else
            goto ECHEC;          
} else{
	        Date_Sys();
        for( i=1;i<74;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
        for( i=96;i<167;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
		gotoxy(74,7);textcolor(14);printf("RECHERCHER UNE FACTURE");
			
			gotoxy(58,26);textcolor(3);printf(" - Pour Ajouter un client tapez : ENTER");
            gotoxy(92,26);textcolor(14);printf("ENTER");
            gotoxy(58,27);textcolor(3);printf(" - Pour Rechercher un client tapez : SPACE");
            gotoxy(95,27);textcolor(14);printf("SPACE");
            gotoxy(58,28);textcolor(3);printf(" - Tapez autre touche pour retour au MENU PRINCIPAL .");
    	
    		     	     	 do{
         	gotoxy(58,24);textcolor(14);printf("- Ce client n'existe pas. Ajouter comme nouveau client ? ");
            Sleep(400);
        	gotoxy(58,24);textcolor(4);printf("- Ce client n'existe pas. Ajouter comme nouveau client ? ");
            Sleep(400);        				
	     	 }while(!kbhit());
	     	   	
         	ch = getch();
        if(ch == BTN_ENTER)
            goto AJOUTE;
        else if(ch == BTN_SPACE)
            goto CONSULT;
        else
            goto ECHEC;
		}
	
}	break;

case '3':{
	 system("cls");
//			_setcursortype(_NOCURSOR);
	char Filedel[20];		
	char cin[10];
	int n,i,m=1;
	int size;
	 	   Date_Sys();
	 	   
        for( i=1;i<74;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
        for( i=95;i<167;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
		gotoxy(74,7);textcolor(14);printf("SUPPRIMER UNE FACTURE");
			 	  
	 	char Filename[38]; // client_cin
        FILE *fp;
        
        for( y=16;y<23;y++){gotoxy(60,y);textcolor(4);printf("บ");}
        for( y=16;y<23;y++){gotoxy(114,y);textcolor(4);printf("บ");} 
        gotoxy(60,16);textcolor(4);printf("ษอออออออออออออออออออออออออออออออออออออออออออออออออออออป");
        gotoxy(60,23);textcolor(4);printf("ศอออออออออออออออออออออออออออออออออออออออออออออออออออออผ");
     
        	     	 do{
         gotoxy(72,19);textcolor(4);printf("- CIN Client: ");
          Sleep(400);
         gotoxy(72,19);textcolor(14);printf("- CIN Client: ");
          Sleep(400);        				
		 }while(!kbhit());
		 
		 textcolor(11);gotoxy(86,19);scanf("%s",cin);
		 
		 for (j = 0; cin[j]!='\0'; j++){
	         if((cin[j] >= 'A' && cin[j] <= 'Z') || (cin[j] >= 'a' && cin[j] <= 'z') || (cin[j] >= '0' && cin[j] <= '9'))	
	              strupr(cin);		 
        else{
        	 Date_Sys();
        for( i=1;i<74;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
        for( i=95;i<167;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
		gotoxy(74,7);textcolor(14);printf("SUPPRIMER UNE FACTURE");
		
         gotoxy(70,25);textcolor(3);printf("- saisie incorrecte !!");
         gotoxy(70,26);textcolor(3);printf("- Tapez (ENTER) pour r้essaye:");
         gotoxy(79,26);textcolor(14);printf("ENTER");
         
         	ch = getch();  
            goto HISTO;
         }
}	  
        strcpy(Filename, "datafacture/client_");
        strcat(Filename,cin);
        strcat(Filename,".txt");
        int exist = cfileexists(Filename);
        
    	if(exist){
	 FILE *fp;
	 fp=fopen(Filename,"rb");
	 
	        fseek(fp,0,SEEK_END);
		    tl=ftell(fp);
		    sl=sizeof(Client);
		    ts=tl/sl;
		    fseek(fp,(ts-1)*sl,SEEK_SET);
		    fread(&Client,sizeof(Client),1,fp);
	
   //    _setcursortype(_NOCURSOR);
		    	
		       	 Date_Sys();		       	 
    
			     fseek(fp,0,SEEK_SET);		
	 while(fread(&Client,sizeof(Client),1,fp)){
			
				 	 system("cls");
		        	 Date_Sys();
        for( i=1;i<74;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
        for( i=95;i<167;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
		gotoxy(74,7);textcolor(14);printf("SUPPRIMER UNE FACTURE");
		
    	gotoxy(70,13);textcolor(12);printf("- CIN Client        :");
	    gotoxy(92,13);textcolor(2);printf("%s",Client.CIN);
	    gotoxy(70,14);textcolor(12);printf("- Nom Client        :");
	    gotoxy(92,14);textcolor(2);printf("%s",Client.NOMC);
	    gotoxy(70,15);textcolor(12);printf("- Prenom Client     :");
	    gotoxy(92,15);textcolor(2);printf("%s",Client.PREC);
	    gotoxy(70,16);textcolor(12);printf("- Telephone         :");
	    gotoxy(92,16);textcolor(2);printf("%s",Client.TelePhon);
	    gotoxy(70,17);textcolor(12);printf("- Reste de Paiement :");
	    gotoxy(92,17);textcolor(2);printf("%.2f",Client.RestePayment);
	    gotoxy(70,18);textcolor(12);printf("- Paiement Actuel   :");
	    gotoxy(92,18);textcolor(2);printf("%.2f",Client.Payment);
	    gotoxy(70,19);textcolor(12);printf("- Date de Paiement  :");
	    gotoxy(92,19);textcolor(2);printf("%s",Client.DatePay);   
}
 	    fclose(fp);
 	 	
 	      gotoxy(60,25);textcolor(13);printf("- Tapez (ENTER) pour supprimer :");
		  gotoxy(69,25);textcolor(14);printf("ENTER");
		  gotoxy(60,26);textcolor(13);printf("- Tapez autre touche pour retour au MENU PRINCIPAL .");
		  
 	    	 do{
         gotoxy(65,23);textcolor(4);printf("Voulez-vous supprimer cette FACTURE?:");
          Sleep(400);
         gotoxy(65,23);textcolor(14);printf("Voulez-vous supprimer cette FACTURE?:");
          Sleep(400);       				
		 }while(!kbhit());
		  
		 ch = getch();
     
        if(ch == BTN_ENTER){
	     remove(Filename);
            goto ECHEC;
       	}
        else{
        	 goto ECHEC;
		}
    
           }else{
	 Date_Sys();
	 
            for( i=1;i<74;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
            for( i=95;i<167;i++){gotoxy(i,6);textcolor(4);printf("Ü");} 
		    gotoxy(74,7);textcolor(14);printf("RECHERCHER UNE FACTURE");
		   		
		   	gotoxy(58,27);textcolor(3);printf(" - Pour Ajouter un client tapez : ENTER");
            gotoxy(92,27);textcolor(14);printf("ENTER");
            gotoxy(58,28);textcolor(3);printf(" - Pour Rechercher un client tapez : SPACE");
            gotoxy(95,28);textcolor(14);printf("SPACE");
            gotoxy(58,29);textcolor(3);printf(" - Tapez autre touche pour retour au MENU PRINCIPAL .");
            
    		  	 do{
           gotoxy(58,25);textcolor(4);printf("- Ce client n'existe pas. Ajouter comme nouveau client ? ");
           Sleep(400);
           gotoxy(58,25);textcolor(14);printf("- Ce client n'existe pas. Ajouter comme nouveau client ? ");
           Sleep(400);         				
	     	 }while(!kbhit());
		 	
        	ch = getch();
        if(ch == BTN_ENTER)
            goto AJOUTE;
        else if(ch == BTN_SPACE)
            goto CONSULT;
        else
            goto ECHEC;
		}   
    	
    } break;

 default:{
   goto ECHEC;
}	break;
 } 	
 }
    case '3':
    {
HESTO :
    	
         system("cls");
           Date_Sys();
           
        for( i=1;i<75;i++){gotoxy(i,5);textcolor(4);printf("Ü");} 
        for( i=96;i<167;i++){gotoxy(i,5);textcolor(4);printf("Ü");}
       
        gotoxy(1,2);textcolor(3);printf(" - Pour continuer l'operation tapez : ENTER");
        gotoxy(39,2);textcolor(14);printf("ENTER");
        gotoxy(1,3);textcolor(3);printf(" - Pour annuler l'operation tapez : ESC");
        gotoxy(37,3);textcolor(14);printf("ESC");
        gotoxy(76,6);textcolor(14);printf("NOUVELLE HISTORIQUE");
        for( y=16;y<23;y++){gotoxy(60,y);textcolor(4);printf("บ");}
        for( y=16;y<23;y++){gotoxy(114,y);textcolor(4);printf("บ");} 
        gotoxy(60,16);textcolor(4);printf("ษอออออออออออออออออออออออออออออออออออออออออออออออออออออป");
        gotoxy(60,23);textcolor(4);printf("ศอออออออออออออออออออออออออออออออออออออออออออออออออออออผ");	
    	 
    	 do{
         gotoxy(70,19);textcolor(4);printf("- CIN Client: ");
          Sleep(400);
         gotoxy(70,19);textcolor(14);printf("- CIN Client: ");
          Sleep(400);        				
		 }while(!kbhit());
		 
		 textcolor(3);gotoxy(84,19);scanf("%s",CIN);
		 
		 for (j = 0; CIN[j]!='\0'; j++){
	         if((CIN[j] >= 'A' && CIN[j] <= 'Z') || (CIN[j] >= 'a' && CIN[j] <= 'z') || (CIN[j] >= '0' && CIN[j] <= '9'))	
	              strupr(CIN);		 
        else{
         gotoxy(70,25);textcolor(3);printf("- saisie incorrecte !!");
         gotoxy(70,26);textcolor(3);printf("- Tapez (ENTER) pour r้essaye:");
         gotoxy(79,26);textcolor(14);printf("ENTER");
         gotoxy(79,27);textcolor(3);printf("- Tapez autre touche pour retour au MENU PRINCIPAL:");
         
         	ch = getch();  
            goto HESTO;
         }   
        }          
           ch = getch(); 	
      	if(ch != BTN_ENTER){
       		goto HESTO;  
     	}
        
         char filename[38]; // client_cin
        
        strcpy(filename, "datasource/client_");
        strcat(filename,CIN);
        strcat(filename,".txt");
        
        int exist = cfileexists(filename);
        
        int day, mois, an;
        char DateDebut[11];
        char line[MAX];
        
    	if(exist){
    	
    	FILE *fs=fopen(filename,"rb");

	        if (fs == NULL) {
                             printf("Error!");   
                             exit(1);  	          
                            } else {
                    	        system("cls");
                  	           Date_Sys();
        for( i=1;i<75;i++){gotoxy(i,4);textcolor(4);printf("Ü");} 
        for( i=94;i<167;i++){gotoxy(i,4);textcolor(4);printf("Ü");}
       
        gotoxy(1,2);textcolor(3);printf(" - Pour une autre recherche tapez : ENTER");
        gotoxy(37,2);textcolor(14);printf("ENTER");
        gotoxy(1,3);textcolor(3);printf(" - Tapez autre touche pour retour au MENU PRINCIPAL .");
       
        gotoxy(76,5);textcolor(14);printf("HISTORIQUE CLIENT");
        printf("\n");
        textcolor(14);
		   
		   while (fgets(line, MAX, fs) != NULL){
		   	fflush(stdout);
       	         printf("                                                                         ");
       	         
       	          printf("%s", line);
	        } 
                ch = getch(); 	
        		if(ch == BTN_ENTER){
        			goto HESTO;  
		       	}else{
				goto ECHEC;
		     	}
   
  }
        fclose(fs);
					
    	    	ch = getch();
    	
        		if(ch == BTN_ENTER){
        			goto HESTO;  
		       	}else{
				goto ECHEC;
		}          
            }else{       
    	gotoxy(70,26);textcolor(3);printf("- Tapez (ENTER) pour reessaye:");
        gotoxy(79,26);textcolor(14);printf("ENTER");
        gotoxy(70,27);textcolor(3);printf("- Tapez autre touche pour retour au MENU PRINCIPAL .");
        
        		  	 do{
           gotoxy(70,25);textcolor(4);printf("- Ce client n'existe pas ? ");
           Sleep(400);
          gotoxy(70,25);textcolor(14);printf("- Ce client n'existe pas ? ");
           Sleep(400);         				
	     	 }while(!kbhit());
	     	 
    		    ch = getch(); 	
        	if(ch == BTN_ENTER){
        		goto HESTO;  
			}else{
				goto ECHEC;
			}
		}
   
    } break;
    default:
    { exit(0);
    } break;
    
    }
    
    return 0;
}

void AffichSpace()
{
    printf("\n                                                                  ");
    return;
}

 void Date_Sys()
{
  int h, min, s;
  time_t now;

  // Renvoie l'heure actuelle
  	time(&now);
  // Convertir au format heure locale
  struct tm *local = localtime(&now);
  h = local->tm_hour;
  min = local->tm_min;
  s = local->tm_sec;
  Date.jour = local->tm_mday;
  Date.mois = local->tm_mon + 1;
  Date.an = local->tm_year + 1900; 
  // Afficher la date courante
  gotoxy(145,3);textcolor(15);printf("La date : %02d/%02d/%d  ", Date.jour, Date.mois, Date.an);
  gotoxy(145,2);textcolor(15);printf("L'heure : %02d:%02d  ", h, min );	 
  return ;
}

void Time_REC(char *filename)
{
	      int h, min, s;
 
 FILE *fp=fopen(filename,"ab");
	 
	 if(fp == NULL)
   {
      printf("Error!");   
      exit(1);             
   }else{
    time_t now; 
  // Renvoie l'heure actuelle
  time(&now);
  struct tm *local = localtime(&now);
  h = local->tm_hour;
  min = local->tm_min;
  s = local->tm_sec;
  Date.jour = local->tm_mday;
  Date.mois = local->tm_mon + 1;
  Date.an = local->tm_year + 1900; 
  //register  
 
               fprintf(fp,"\n%02d/%02d/%d  ", Date.jour, Date.mois, Date.an);              
               fprintf(fp,"%02d:%02d:%02d  ", h, min, s);
               fprintf(fp,"\nออออออออออ  อออออออออ");
           	 
		  }  fclose(fp);
       return ;
}

/*
 * Check if a file exist using fopen() function
 * return 1 if the file exist otherwise return 0
 */
int cfileexists(const char * filename){
    /* try to open file to read */
    FILE *file;
    if (file = fopen(filename, "rb")){
        fclose(file);
        return 1;
    }
    return 0;
}

