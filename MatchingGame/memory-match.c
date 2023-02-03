#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

// Kartlarim sayilardan degil buyuk ve kucuk harflerden olusuyor. Bunun icin int matrisimi %c ile ekrana yazdirdim.
// Tum dizileri int olarak tanýmlayýp birbirine esitleyerek ekrana yazdiriyorum. 

void swap (int *a, int *b){ //Kartlari random dagitmak icin ikili degisim yapiyorum.
    int temp = *a;
    *a = *b;
    *b = temp;
}

void random(int n, int m, int matris[n][m] ){  //Matrisi swap yardimiyla karistiriyorum.
	int i,j;
	srand(time(NULL));
	for(i=n-1; i>=0; i--){
		for(j=m-1;j>=0; j--){
			int k= rand()%(i+1);
			int l= rand()%(j+1);
			swap(&matris[i][j], &matris[k][l]);
		}
	}
}

void printCharMatris(int n, int m, int matris[n][m]){   
	int i,j;
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			printf("%c    ",matris[i][j]);
		}
		printf("\n\n");
	}
}

int main(){

	int level;
    int i,j,k=0;
    int userRow1,userColumn1, userRow2, userColumn2,compRow1, compColumn1, compRow2, compColumn2;
    int countUser=0,countComp=0; //Bilgisayarin ve userin dogru eslestirme sayilari.
    int guessUser=0, guessComp=0; //Tahmin sayilari.

	printf("***WELCOME TO THE GAME OF FINDING MATCH CARDS.***\n\n");
	printf("Try to find the same letters!\n\n");
	
	printf("Please choose a level:\n1.EASY\n2.MEDIUM\n3.HARD\nIf you want to exit, choose 0.\n");	 //Level secimi.
	scanf("%d", &level);
	
	while(!(level==1 || level==2 || level==3) && level!=0){
		printf("You entered invalid number. Please try again.\nPlease choose a level:\n1.EASY\n2.MEDIUM\n3.HARD\nIf you want to exit, choose 0.\n");
		scanf("%d", &level);
	}
	
	if(level==1){	
		int gameBoard[4][4]= {65,66,67,68,69,70,71,72,65,66,67,68,69,70,71,72}; //Sayilari char seklinde yazdirip harfler olarak kullaniyorum.
		int stars[4][4];
		int x[100], y[100], value[100]; //Hafiza kisminda koordinatlari ve degeri(harfi) tutan diziler.
		
		random(4,4,gameBoard);
		printf("\n");
		printCharMatris(4,4,gameBoard);
		for (i=0; i<4; i++){
		 	for(j=0; j<4; j++){
			  	stars[i][j]=42;
			}
		}
		printf("\n");
		printCharMatris(4,4,stars);
		int duringGame=0;
		while(duringGame==0){
			
			int compTurn=0;
			int userTurn=0;
			while(userTurn==0){	
				printf("The player's turn.\n");
				
				printf("Enter a coordinate of the first card you want to open.\n");
				scanf("%d %d", &userRow1, &userColumn1);
				guessUser++;
				
				while(userRow1<1 || userRow1>4 || userColumn1<1 || userColumn1>4){     //Kullanici yanlis koordinat girerse tekrar koordinat aliyorum.
					printf("You entered invalid coordinate. Please try again:\n");
					printf("Enter a coordinate of the first card you want to open.\n");
					scanf("%d %d", &userRow1, &userColumn1);
				}
				
				while(stars[userRow1-1][userColumn1-1]==45){          // Secilen koordinat daha once eslesmis (-) ise tekrar koordinat aliyorum.
					printf("You cannot choose an opened card.\n");
					printf("Enter a coordinate of the first card you want to open.\n");
					scanf("%d %d", &userRow1, &userColumn1);
				}
				userRow1--;      //Satir ve sutunu azaltma sebebim C'de indisin 0'dan basliyor olmasi.
				userColumn1--;
				
				for(i=0; i<4; i++){    // Koordinati yildizli matriste aciyorum.
			    	for(j=0; j<4; j++){
						if(i==userRow1 && j==userColumn1){ 
							stars[i][j]=gameBoard[i][j]; 
						}
						printf("%c    ", stars[i][j]);	
					}
			    	printf("\n\n");
				}
					
				printf("Enter a coordinate of the second card you want to open.\n"); //Ayni islemi ikinci koordinatlar icin yapiyoruz.
				scanf("%d %d", &userRow2, &userColumn2);
				guessUser++;
				
				while(userRow2<1 || userRow2>4 || userColumn2<1 || userColumn2>4){
					printf("You entered invalid coordinate. Please try again:");
					printf("Enter a coordinate of the second card you want to open.\n");
					scanf("%d %d", &userRow2, &userColumn2);
				}
				
				while(stars[userRow2-1][userColumn2-1]==45){
					printf("You cannot choose an opened card.\n");
					printf("Enter a coordinate of the second card you want to open.\n");
					scanf("%d %d", &userRow2, &userColumn2);
				}
				
				while((userRow1+1)==userRow2 && (userColumn1+1)==userColumn2){
					printf("You have just opened this card. Please choose another coordinate.\n	");
					scanf("%d %d", &userRow2, &userColumn2);
				}	
				
				userRow2--;
				userColumn2--;
				
				for(i=0; i<4; i++){
			    	for(j=0; j<4; j++){
						if(i==userRow2 && j==userColumn2){
							stars[i][j]=gameBoard[i][j];
						}
						printf("%c    ", stars[i][j]);	
					}	
			    	printf("\n\n");
				}
				
				if(gameBoard[userRow1][userColumn1]==gameBoard[userRow2][userColumn2]){  //Girilen iki koordinattaki kartlar es ise aciyorum.
					
					printf("CORRECT MATCHING!\n");
					countUser++;
					printf("\nScor: PLAYER %d-%d COMPUTER\n",countUser, countComp);
					
					if(countUser+countComp==8 || countUser==5 || countComp==5){   //Oyunun ne zaman bitecegi kosulu.
						userTurn=1;
						compTurn=1;
						duringGame=1;	
					}
					
					stars[userRow1][userColumn1]=45; // Es kartlari eksi ile gösteriyoruz. 
					stars[userRow2][userColumn2]=45;	
				}
				else{   //Kullanicinin actigi kartlar es degilse hafizaya aliyorum.
					x[k]=userRow1;
					y[k]=userColumn1;
					value[k]=gameBoard[userRow1][userColumn1];
					k++;
					x[k]=userRow2;
					y[k]=userColumn2;
					value[k]=gameBoard[userRow2][userColumn2];
					k++;
					
					userTurn=1;
					stars[userRow1][userColumn1]=42; //Kullanicinin eslesmeyen kartlarinin koordinatlarini yildiza tekrar cevirdim.
					stars[userRow2][userColumn2]=42;
				}
			}
			printf("Cards are turned off.\n");
			sleep(1);
			printf("\n");   //Ekrana kapali kartlari yazdiriyorum.
			for(i=0; i<4; i++){
				for(j=0; j<4; j++){
					printf("%c    ",stars[i][j]);
				}
				printf("\n\n");
			}
			
			while(compTurn==0){
				printf("Turn of computer.\n");

				int sameValue=1;   //Hafizasinda ayný iki harf var mi?
				for(i=(k-1); i>(k-4); i--){   
					for(j=i-1; j>(k-3); j--){
						if(value[i]==value[j] && x[i]!=x[j] && y[i]!=y[j] && stars[x[i]][y[i]]!=45 && stars[x[j]][y[j]]!=45){							
							compRow1=x[i];
							compRow2=x[j];
							compColumn1=y[i];
							compColumn2=y[j];
							i=k-5;
							j=k-4; 
							sameValue=0;
						}
					}
				}
				
				if(sameValue==0){
					printf("\nCoordinate of the first card of the computer:\n");
					printf("%d %d\n", compRow1+1, compColumn1+1);
					guessComp++;
					
					for(i=0; i<4; i++){
					   	for(j=0; j<4; j++){			
							if(i==compRow1 && j==compColumn1){ 
								stars[i][j]=gameBoard[i][j]; 
							}	
							printf("%c    ", stars[i][j]);	
						}	
					  	printf("\n\n");
					}
					sleep(1);
					printf("\nCoordinate of the second card of the computer:\n");
					printf("%d %d\n", compRow2+1, compColumn2+1);
					guessComp++;
					
					for(i=0; i<4; i++){
					   	for(j=0; j<4; j++){			
							if(i==compRow2 && j==compColumn2){ 
								stars[i][j]=gameBoard[i][j]; 
							}	
							printf("%c    ", stars[i][j]);	
						}	
					  	printf("\n\n");
					}
					
					printf("CORRECT MATCHING!\n");
					countComp++;
					printf("\nScor: PLAYER %d-%d COMPUTER\n",countUser, countComp);

					stars[compRow1][compColumn1]=45;
					stars[compRow2][compColumn2]=45;
					sleep(1);
					for(i=0; i<4; i++){
					   	for(j=0; j<4; j++){				
							printf("%c    ", stars[i][j]);	
						}	
					  	printf("\n\n");
					}	
				}
				
				else{
					printf("Coordinate of the first card of the computer:\n");
					compRow1=rand()%4+1;
					compColumn1=rand()%4+1;
					guessComp++;
					
					while(stars[compRow1-1][compColumn1-1]==45){   // Bilgisayarin random actigi kart daha once eslesmis kartlardan biriyse tekrar koordinat aliyorum.
						compRow1=rand()%4+1;
						compColumn1=rand()%4+1;
					}
					
					printf("%d %d\n", compRow1, compColumn1);
					compRow1--;
					compColumn1--;
	
					for(i=0; i<4; i++){
						for(j=0; j<4; j++){			
							if(i==compRow1 && j==compColumn1){
								stars[i][j]=gameBoard[i][j]; 		
							}	
							printf("%c    ", stars[i][j]);	
						}
						printf("\n\n");
					}
					sleep(1);	
					int memory=0;    //Actigi kartin esi hafizasinda var mi?
					int open;        //Varsa acilacak olan kart icin indis.
					for(i=(k-1); i>(k-4); i--){
						if(gameBoard[compRow1][compColumn1]==value[i] && x[i]!=compRow1 && y[i]!=compColumn1){
							open=i;
							memory=1;
						}
					}
					if(memory==1){     // Actigi kartin esi hafizasinda var.
						printf("\nCoordinate of the second card of the computer:\n");
						guessComp++;
						compRow2=x[open]+1, compColumn2=y[open]+1;
						printf("%d %d\n",compRow2,compColumn2);
						stars[x[open]][y[open]]=gameBoard[x[open]][y[open]]; 
						memory=0;
		
						for(i=0; i<4; i++){
						   	for(j=0; j<4; j++){	
						   		printf("%c    ", stars[i][j]);
						   	}
						   	printf("\n\n");
						}
						printf("CORRECT MATCHING!\n");
						countComp++;
						printf("\nScor: PLAYER %d-%d COMPUTER\n",countUser, countComp);
							
						if(countUser+countComp==8 || countUser==5 || countComp==5){
							userTurn=1;
							compTurn=1;
							duringGame=1;
						}
						stars[compRow1][compColumn1]=45;
						stars[compRow2-1][compColumn2-1]=45;	
					}
					else{  //Actigi kartin esi hafizasinda yok. Random kart acmali.
						printf("Coordinate of the second card of the computer:\n");
						compRow2=rand()%4+1;
						compColumn2=rand()%4+1;
						guessComp++;
								
						while(stars[compRow2-1][compColumn2-1]==45){
							srand(time(NULL));
							compRow2=rand()%4+1;
							compColumn2=rand()%4+1;
						}
								
						while(compRow1+1==compRow2 && compColumn1+1==compColumn2){
							compRow2=rand()%4+1;
							compColumn2=rand()%4+1;
						}	
	
						printf("%d %d\n", compRow2, compColumn2);
						compRow2--;
						compColumn2--;
						
						for(i=0; i<4; i++){
						   	for(j=0; j<4; j++){			
								if(i==compRow2 && j==compColumn2){ 
									stars[i][j]=gameBoard[i][j]; 
								}	
								printf("%c    ", stars[i][j]);	
							}	
						  	printf("\n\n");
						}
						sleep(1);	
						if(gameBoard[compRow1][compColumn1]==gameBoard[compRow2][compColumn2]){		//Ýki random actigi kart esitse. 
							stars[compRow1][compColumn1]=45;
							stars[compRow2][compColumn2]=45;
							printf("CORRECT MATCHING!\n");
							countComp++;
							printf("\nScor: PLAYER %d-%d COMPUTER\n",countUser, countComp);
							
							if(countUser+countComp==8 || countUser==5 || countComp==5){
								userTurn=1;
								compTurn=1;
								duringGame=1;
							}
						}
						else{  //Ýki random actigi kart esit degilse hafizaya attim.
							x[k]=compRow1;
							y[k]=compColumn1;
							value[k]=gameBoard[compRow1][compColumn1];
							k++;
							x[k]=compRow2;
							y[k]=compColumn2;
							value[k]=gameBoard[compRow2][compColumn2];
							k++;
	
							stars[compRow1][compColumn1]=42; //Actigi koordinatlari tekrar yildiza cevirdim.
							stars[compRow2][compColumn2]=42;
							compTurn=1;		
						}
					}					
				}				
			}
		}
		printf("\n");
		
		if(countComp>countUser){
			printf("COMPUTER HAS WON.\n");
			printf("Number of guess: %d\n", guessComp/2);
		}
		else if(countComp<countUser){
			printf("PLAYER HAS WON.\n");
			printf("Number of guess: %d\n", guessUser/2);
		}
		else{
			printf("DRAW.\n");
		}	
    }
	else if(level==2){
		int gameBoard[6][6]= {65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82};
		int stars[6][6];
		int x[100], y[100], value[100]; 
		
		random(6,6,gameBoard);
		printf("\n");
		printCharMatris(6,6,gameBoard);
		for (i=0; i<6; i++){
			for(j=0; j<6; j++){
				stars[i][j]=42;
			}
		}
		printf("\n");
		printCharMatris(6,6,stars);
		int duringGame=0;
		while(duringGame==0){
			
			int compTurn=0;
			int userTurn=0;
			while(userTurn==0){		
				printf("The player's turn.\n");
				
				printf("Enter a coordinate of the first card you want to open.\n");
				scanf("%d %d", &userRow1, &userColumn1);
				guessUser++;
				
				while(userRow1<1 || userRow1>6 || userColumn1<1 || userColumn1>6){
					printf("You entered invalid coordinate. Please try again:\n");
					printf("Enter a coordinate of the first card you want to open.\n");
					scanf("%d %d", &userRow1, &userColumn1);
				}
				
				while(stars[userRow1-1][userColumn1-1]==45){
					printf("You cannot choose an opened card.\n");
					printf("Enter a coordinate of the first card you want to open.\n");
					scanf("%d %d", &userRow1, &userColumn1);
				}
				userRow1--;
				userColumn1--;
				
				for(i=0; i<6; i++){    
			    	for(j=0; j<6; j++){
						if(i==userRow1 && j==userColumn1){ 
							stars[i][j]=gameBoard[i][j]; 
						}
						printf("%c    ", stars[i][j]);	
					}
			    	printf("\n\n");
				}
					
				printf("Enter a coordinate of the second card you want to open.\n"); 
				scanf("%d %d", &userRow2, &userColumn2);
				guessUser++;
				
				while(userRow2<1 || userRow2>6 || userColumn2<1 || userColumn2>6){
					printf("You entered invalid coordinate. Please try again:");
					printf("Enter a coordinate of the second card you want to open.\n");
					scanf("%d %d", &userRow2, &userColumn2);
				}
				
				while(stars[userRow2-1][userColumn2-1]==45){
					printf("You cannot choose an opened card.\n");
					printf("Enter a coordinate of the second card you want to open.\n");
					scanf("%d %d", &userRow2, &userColumn2);
				}
				
				while((userRow1+1)==userRow2 && (userColumn1+1)==userColumn2){
					printf("You have just opened this card. Please choose another coordinate.");
					scanf("%d %d", &userRow2, &userColumn2);
				}	
				
				userRow2--;
				userColumn2--;
				
				for(i=0; i<6; i++){
			    	for(j=0; j<6; j++){
						if(i==userRow2 && j==userColumn2){
							stars[i][j]=gameBoard[i][j];
						}
						printf("%c    ", stars[i][j]);	
					}	
			   		printf("\n\n");
				}
				
				if(gameBoard[userRow1][userColumn1]==gameBoard[userRow2][userColumn2]){
					printf("CORRECT MATCHING!\n");
					countUser++;
					printf("\nScor: USER %d-%d COMPUTER\n",countUser, countComp);
					
					if(countUser+countComp==18 || countUser==10 || countComp==10){
						userTurn=1;
						compTurn=1;
						duringGame=1;	
					}			
					stars[userRow1][userColumn1]=45; 
					stars[userRow2][userColumn2]=45;	
				}
				else{	
					x[k]=userRow1;
					y[k]=userColumn1;
					value[k]=gameBoard[userRow1][userColumn1];
					k++;
					x[k]=userRow2;
					y[k]=userColumn2;
					value[k]=gameBoard[userRow2][userColumn2];
					k++;

					userTurn=1;
					stars[userRow1][userColumn1]=42; 
					stars[userRow2][userColumn2]=42;
				}
			}
			printf("Cards are turned off.\n");
			sleep(1);
			printf("\n");
			for(i=0; i<6; i++){
				for(j=0; j<6; j++){
					printf("%c    ",stars[i][j]);
				}
				printf("\n\n");
			}	

			while(compTurn==0){
				printf("Turn of computer.\n");
				
				int sameValue=1;
				
				for(i=(k-1); i>(k-8); i--){
					for(j=i-1; j>(k-7); j--){
						if(value[i]==value[j] && x[i]!=x[j] && y[i]!=y[j] && stars[x[i]][y[i]]!=45 && stars[x[j]][y[j]]!=45){							
							compRow1=x[i];
							compRow2=x[j];
							compColumn1=y[i];
							compColumn2=y[j];
							i=k-9;
							j=k-8;
							sameValue=0;
						}
					}
				}	
				if(sameValue==0){
					printf("\nCoordinate of the first card of the computer:\n");
					printf("%d %d\n", compRow1+1, compColumn1+1);
					guessComp++;
					
					for(i=0; i<6; i++){
					   	for(j=0; j<6; j++){			
							if(i==compRow1 && j==compColumn1){ 
								stars[i][j]=gameBoard[i][j]; 
							}	
							printf("%c    ", stars[i][j]);	
						}	
					  	printf("\n\n");
					}
					sleep(1);
					printf("\nCoordinate of the second card of the computer:\n");
					printf("%d %d\n", compRow2+1, compColumn2+1);
					guessComp++;
					
					for(i=0; i<6; i++){
					   	for(j=0; j<6; j++){			
							if(i==compRow2 && j==compColumn2){ 
								stars[i][j]=gameBoard[i][j]; 
							}	
							printf("%c    ", stars[i][j]);	
						}	
					  	printf("\n\n");
					}
					
					printf("CORRECT MATCHING!\n");
					countComp++;

					stars[compRow1][compColumn1]=45;
					stars[compRow2][compColumn2]=45;
					sleep(1);
					for(i=0; i<6; i++){
					   	for(j=0; j<6; j++){				
							printf("%c    ", stars[i][j]);	
						}	
					  	printf("\n\n");
					}	
				}
			
				else{	
					printf("Coordinate of the first card of the computer:\n");
					compRow1=rand()%6+1;
					compColumn1=rand()%6+1;
					guessComp++;
					
					while(stars[compRow1-1][compColumn1-1]==45){
						compRow1=rand()%6+1;
						compColumn1=rand()%6+1;
					}
					
					printf("%d %d\n", compRow1, compColumn1);
					compRow1--;
					compColumn1--;
	
					for(i=0; i<6; i++){
						for(j=0; j<6; j++){			
							if(i==compRow1 && j==compColumn1){ 
								stars[i][j]=gameBoard[i][j]; 		
							}	
							printf("%c    ", stars[i][j]);	
						}
						printf("\n\n");
					}
					sleep(1);
					int memory=0;
					int open;
					for(i=(k-1); i>(k-7); i--){
						if(gameBoard[compRow1][compColumn1]==value[i] && x[i]!=compRow1 && y[i]!=compColumn1 ){
							open=i;
							memory=1;
						}
					}
					if(memory==1){
						printf("\nCoordinate of the second card of the computer:\n");
						guessComp++;
						compRow2=x[open]+1, compColumn2=y[open]+1;
						printf("%d %d\n",compRow2, compColumn2);
						stars[x[open]][y[open]]=gameBoard[x[open]][y[open]]; 
						memory=0;
				
						for(i=0; i<6; i++){
						   	for(j=0; j<6; j++){	
						   		printf("%c    ", stars[i][j]);
						   	}
						   	printf("\n\n");
						}
						printf("CORRECT MATCHING!\n");
						countComp++;
							
						if(countUser+countComp==18 || countUser==10 || countComp==10){
							userTurn=1;
							compTurn=1;
							duringGame=1;
						}
						stars[compRow1][compColumn1]=45;
						stars[compRow2-1][compColumn2-1]=45;	
					}
					else{
						printf("Coordinate of the second card of the computer:\n");
						compRow2=rand()%6+1;
						compColumn2=rand()%6+1;
						guessComp++;
								
						while(stars[compRow2-1][compColumn2-1]==45){
							srand(time(NULL));
							compRow2=rand()%6+1;
							compColumn2=rand()%6+1;
						}
								
						while(compRow1+1==compRow2 && compColumn1+1==compColumn2){
							compRow2=rand()%6+1;
							compColumn2=rand()%6+1;
						}	
	
						printf("%d %d\n", compRow2, compColumn2);
						compRow2--;
						compColumn2--;

						for(i=0; i<6; i++){
						   	for(j=0; j<6; j++){			
								if(i==compRow2 && j==compColumn2){ 
									stars[i][j]=gameBoard[i][j]; 
								}	
								printf("%c    ", stars[i][j]);	
							}	
						  	printf("\n\n");
						}
						sleep(1);		
						if(gameBoard[compRow1][compColumn1]==gameBoard[compRow2][compColumn2]){		
							stars[compRow1][compColumn1]=45;
							stars[compRow2][compColumn2]=45;
							printf("CORRECT MATCHING!\n");
							countComp++;
							
							if(countUser+countComp==18 || countUser==10 || countComp==10){
								userTurn=1;
								compTurn=1;
								duringGame=1;
							}
						}
						else{
							x[k]=compRow1;
							y[k]=compColumn1;
							value[k]=gameBoard[compRow1][compColumn1];
							k++;
							x[k]=compRow2;
							y[k]=compColumn2;
							value[k]=gameBoard[compRow2][compColumn2];
							k++;
	
							stars[compRow1][compColumn1]=42;
							stars[compRow2][compColumn2]=42;
							compTurn=1;		
						}
					}			
				}
				printf("Cards are turned off.\n");
				sleep(1);
				printf("\n");
				for(i=0; i<6; i++){
					for(j=0; j<6; j++){
						printf("%c    ",stars[i][j]);
					}
					printf("\n\n");
				}	
			}
		}
		printf("\n");
		
		if(countComp>countUser){
			printf("COMPUTER HAS WON.\n");
			printf("Number of guess: %d\n", guessComp/2);
		}
		else if(countComp<countUser){
			printf("PLAYER HAS WON.\n");
			printf("Number of guess: %d\n", guessUser/2);
		}
		else{
			printf("DRAW.\n");
		}	
		
	}
	else if(level==3){
		int gameBoard[8][8]= {65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,97,98,99,100,101,102,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,97,98,99,100,101,102};
		int stars[8][8];
		int x[200], y[200], value[200]; 
		
		random(8,8,gameBoard);
		printf("\n");
		printCharMatris(8,8,gameBoard);
		
		for (i=0; i<8; i++){
		    for(j=0; j<8; j++){
		    	stars[i][j]=42;
			}
		}
		printf("\n");
		printCharMatris(8,8,stars);
		
		int duringGame=0;
		while(duringGame==0){
			
			int compTurn=0;
			int userTurn=0;
			while(userTurn==0){

				printf("The player's turn.\n");
				
				printf("Enter a coordinate of the first card you want to open.\n");
				scanf("%d %d", &userRow1, &userColumn1);
				guessUser++;
				
				while(userRow1<1 || userRow1>8 || userColumn1<1 || userColumn1>8){
					printf("You entered invalid coordinate. Please try again:\n");
					printf("Enter a coordinate of the first card you want to open.\n");
					scanf("%d %d", &userRow1, &userColumn1);
				}
				
				while(stars[userRow1-1][userColumn1-1]==45){
					printf("You cannot choose an opened card.\n");
					printf("Enter a coordinate of the first card you want to open.\n");
					scanf("%d %d", &userRow1, &userColumn1);
				}
				userRow1--;
				userColumn1--;

				for(i=0; i<8; i++){    
			    		for(j=0; j<8; j++){
							if(i==userRow1 && j==userColumn1){ 
								stars[i][j]=gameBoard[i][j]; 
							}
							printf("%c    ", stars[i][j]);	
						}
			    		printf("\n\n");
					}
					
				printf("Enter a coordinate of the second card you want to open.\n"); 
				scanf("%d %d", &userRow2, &userColumn2);
				guessUser++;
				
				while(userRow2<1 || userRow2>8 || userColumn2<1 || userColumn2>8){
					printf("You entered invalid coordinate. Please try again:");
					printf("Enter a coordinate of the second card you want to open.\n");
					scanf("%d %d", &userRow2, &userColumn2);
				}
				
				while(stars[userRow2-1][userColumn2-1]==45){
					printf("You cannot choose an opened card.\n");
					printf("Enter a coordinate of the second card you want to open.\n");
					scanf("%d %d", &userRow2, &userColumn2);
				}
				
				while((userRow1+1)==userRow2 && (userColumn1+1)==userColumn2){
					printf("You have just opened this card. Please choose another coordinate.");
					scanf("%d %d", &userRow2, &userColumn2);
				}	
				
				userRow2--;
				userColumn2--;
				
				for(i=0; i<8; i++){
			    		for(j=0; j<8; j++){
							if(i==userRow2 && j==userColumn2){
								stars[i][j]=gameBoard[i][j];
							}
							printf("%c    ", stars[i][j]);	
						}	
			    		printf("\n\n");
				}
				
				if(gameBoard[userRow1][userColumn1]==gameBoard[userRow2][userColumn2]){
					
					printf("CORRECT MATCHING!\n");
					countUser++;
					printf("\nScor: USER %d-%d COMPUTER\n",countUser, countComp);
					
					if(countUser+countComp==32 || countUser==17 || countComp==17){
						userTurn=1;
						compTurn=1;
						duringGame=1;	
					}
					
					stars[userRow1][userColumn1]=45; 
					stars[userRow2][userColumn2]=45;	
				}
				else{
					x[k]=userRow1;
					y[k]=userColumn1;
					value[k]=gameBoard[userRow1][userColumn1];
					k++;
					x[k]=userRow2;
					y[k]=userColumn2;
					value[k]=gameBoard[userRow2][userColumn2];
					k++;

					userTurn=1;
					stars[userRow1][userColumn1]=42; 
					stars[userRow2][userColumn2]=42;
				}
			}			
			printf("Cards are turned off.\n");
			sleep(1);
			printf("\n");   
			for(i=0; i<8; i++){
				for(j=0; j<8; j++){
					printf("%c    ",stars[i][j]);
				}
				printf("\n\n");
			}
			
			while(compTurn==0){
				printf("Turn of computer.\n");
				
				int sameValue=1;
				
				for(i=(k-1); i>(k-18); i--){
					for(j=i-1; j>(k-17); j--){
						if(value[i]==value[j] && x[i]!=x[j] && y[i]!=y[j] && stars[x[i]][y[i]]!=45 && stars[x[j]][y[j]]!=45){							
							compRow1=x[i];
							compRow2=x[j];
							compColumn1=y[i];
							compColumn2=y[j];
							i=k-19;
							j=k-18;
							sameValue=0;
						}
					}
				}
				
				if(sameValue==0){
					printf("\nCoordinate of the first card of the computer:\n");
					printf("%d %d\n", compRow1+1, compColumn1+1);
					guessComp++;
					
					for(i=0; i<8; i++){
					   	for(j=0; j<8; j++){			
							if(i==compRow1 && j==compColumn1){ 
								stars[i][j]=gameBoard[i][j]; 
							}	
							printf("%c    ", stars[i][j]);	
						}	
					  	printf("\n\n");
					}
					sleep(1);
					printf("\nCoordinate of the second card of the computer:\n");
					printf("%d %d\n", compRow2+1, compColumn2+1);
					guessComp++;
					
					for(i=0; i<8; i++){
					   	for(j=0; j<8; j++){			
							if(i==compRow2 && j==compColumn2){ 
								stars[i][j]=gameBoard[i][j]; 
							}	
							printf("%c    ", stars[i][j]);	
						}	
					  	printf("\n\n");
					}
					
					printf("CORRECT MATCHING!\n");
					countComp++;

					stars[compRow1][compColumn1]=45;
					stars[compRow2][compColumn2]=45;
					sleep(1);
					for(i=0; i<8; i++){
					   	for(j=0; j<8; j++){				
							printf("%c    ", stars[i][j]);	
						}	
					  	printf("\n\n");
					}	
				}
				
				else{
					
					printf("Coordinate of the first card of the computer:\n");
					compRow1=rand()%8+1;
					compColumn1=rand()%8+1;
					guessComp++;
					
					while(stars[compRow1-1][compColumn1-1]==45){
						compRow1=rand()%8+1;
						compColumn1=rand()%8+1;
					}
					
					printf("%d %d\n", compRow1, compColumn1);
					compRow1--;
					compColumn1--;
	
					for(i=0; i<8; i++){
						for(j=0; j<8; j++){			
							if(i==compRow1 && j==compColumn1){ 
								stars[i][j]=gameBoard[i][j]; 		
							}	
							printf("%c    ", stars[i][j]);	
						}
						printf("\n\n");
					}
					sleep(1);
					int memory=0; 
					int open;  
					for(i=(k-1); i>(k-17); i--){
						if(gameBoard[compRow1][compColumn1]==value[i] && x[i]!=compRow1 && y[i]!=compColumn1 ){
							open=i;
							memory=1;
						}
					}
					if(memory==1){
						printf("\nCoordinate of the second card of the computer:\n");
						guessComp++;
						compRow2=x[open]+1, compColumn2=y[open]+1;
						printf("%d %d\n",i+1,j+1);
						stars[x[open]][y[open]]=gameBoard[x[open]][y[open]]; 
						memory=0;
		
						for(i=0; i<8; i++){
						   	for(j=0; j<8; j++){	
						   		printf("%c    ", stars[i][j]);
						   	}
						   	printf("\n\n");
						}
						printf("CORRECT MATCHING!\n");
						countComp++;
							
						if(countUser+countComp==32 || countUser==17 || countComp==17){
							userTurn=1;
							compTurn=1;
							duringGame=1;
						}
						stars[compRow1][compColumn1]=45;
						stars[compRow2-1][compColumn2-1]=45;	
					}
					else{
						printf("Coordinate of the second card of the computer:\n");
						compRow2=rand()%8+1;
						compColumn2=rand()%8+1;
						guessComp++;
								
						while(stars[compRow2-1][compColumn2-1]==45){
							srand(time(NULL));
							compRow2=rand()%8+1;
							compColumn2=rand()%8+1;
						}
								
						while(compRow1+1==compRow2 && compColumn1+1==compColumn2){
							compRow2=rand()%8+1;
							compColumn2=rand()%8+1;
						}	
	
						printf("%d %d\n", compRow2, compColumn2);
						compRow2--;
						compColumn2--;
						
	
						for(i=0; i<8; i++){
						   	for(j=0; j<8; j++){			
								if(i==compRow2 && j==compColumn2){ 
									stars[i][j]=gameBoard[i][j]; 
								}	
								printf("%c    ", stars[i][j]);	
							}	
						  	printf("\n\n");
						}
						sleep(1);		
						if(gameBoard[compRow1][compColumn1]==gameBoard[compRow2][compColumn2]){		
							stars[compRow1][compColumn1]=45;
							stars[compRow2][compColumn2]=45;
							printf("CORRECT MATCHING!\n");
							countComp++;
							
							if(countUser+countComp==32 || countUser==17 || countComp==17){
								userTurn=1;
								compTurn=1;
								duringGame=1;
							}
						}
						else{
							x[k]=compRow1;
							y[k]=compColumn1;
							value[k]=gameBoard[compRow1][compColumn1];
							k++;
							x[k]=compRow2;
							y[k]=compColumn2;
							value[k]=gameBoard[compRow2][compColumn2];
							k++;
	
							stars[compRow1][compColumn1]=42;
							stars[compRow2][compColumn2]=42;
							compTurn=1;		
						}
					}			
				}				
				printf("Cards are turned off.\n");
				sleep(1);
				printf("\n");   
				for(i=0; i<8; i++){
					for(j=0; j<8; j++){
						printf("%c    ",stars[i][j]);
					}
					printf("\n\n");
				}	
			}	
		}
		printf("\n");
		
		if(countComp>countUser){
			printf("COMPUTER HAS WON.\n");
			printf("Number of guess: %d\n", guessComp/2);
		}
		else if(countComp<countUser){
			printf("PLAYER HAS WON.\n");
			printf("Number of guess: %d\n", guessUser/2);
		}
		else{
			printf("DRAW.\n");
		}		
		
	}
	else if(level==0){	
	}
	printf("\nEnd of the game.");
	
	return 0;
}
