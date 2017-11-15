#include <stdio.h>
#include <string.h>
/*nyt tämä on valmis. Toistofunktio on hiottu kuntoon ja automaatti antaa vain 50e ja 20e seteleitä */

void paaValikko(int *valinta);		/* automaatin päävalikko */
void nosto(int *saldo);		/* rahan nosto ja nykyinen saldo*/
void talletus(int *saldo);		/* rahan talletus ja nykyinen saldo*/
void nykySaldo(int saldo);		/* tilin nykyinen saldo */
void toisto(char * repeat);		/* uusi siirto */
int lueKokonaisluku(void);
void lueRoskat(void);

int main (void) {

	char tilinumero[256];
	FILE * tili;
	char pinkoodi[256];
	char tarkistusPin[256];
	int valinta;
	int saldo;
	char repeat = 0;

	printf("Syötä tilinumero: \n");
	fgets(tilinumero, 256, stdin);


	if( tilinumero[strlen(tilinumero) -1] == '\n'){
  		tilinumero[strlen(tilinumero) -1] = '\0';
	}
 	else {
		lueRoskat();
 	}

	strcat(tilinumero, ".tili");

	if ((tili = fopen (tilinumero, "r")) != NULL){
		printf("Syötä pinkoodi: \n");
		fgets(pinkoodi, 256, stdin);

		if(pinkoodi[strlen(pinkoodi) -1] == '\n'){
			pinkoodi[strlen(pinkoodi) -1] = '\0';
		}
		else{
			lueRoskat();
		}

		fgets(tarkistusPin, 256, tili);

		if(tarkistusPin[strlen(tarkistusPin) -1] == '\n'){
			tarkistusPin[strlen(tarkistusPin) -1] = '\0';
		}

		if (strcmp(pinkoodi, tarkistusPin) == 0){
			printf("Tervetuloa käyttämään Reilu-Hessun pankkiautomaattia. \nMitä saisi olla? \n");
			fscanf( tili, "%d", &saldo);
			
			while(1){	
				paaValikko(&valinta);
				do{
					switch (valinta){
		
					case 1:
						nosto(&saldo);
						toisto(&repeat);
						break;
					case 2:
						talletus(&saldo);
						toisto(&repeat);
						break;
					case 3:
						nykySaldo(saldo);
						toisto(&repeat);
						break;
					case 4:
						return(0);
						break;
					default:
						printf("Virheellinen valinta\n");
						toisto(&repeat);
					}
				}while(repeat == 'K' || repeat == 'k');
			}
		}
		else{
			printf("\nPinkoodi on virheellinen. Taidat olla joku voro... \n");
		}
		
	}else {
		printf("\nTili suljettu\n");
	}
	return(0);
}

/* Näyttää käyttäjälle vaihtoehdot ja valinnan arvon */
void paaValikko(int *valinta){

	printf("1. Nosto\n");
	printf("2. Talletus\n");
	printf("3. Tilin saldo\n");
	printf("4. Lopetus\n");
	scanf(" %d", valinta);

}

/* Kysyy käyttäjältä nostettavan rahan määrän, tallettaa nykyisen saldon ja laskee annettavien seteleiden määrän */
void nosto(int *saldo){


	int nostomaara = 0;
	int kakskyt = 0;
	int viiskyt = 0;

	printf("Voitte nostaa 20 tai 40e ja siitä eteenpäin 10e välein\n");
	printf("Paljonko haluatte nostaa?: \n");
	nostomaara = lueKokonaisluku();
	
	if (nostomaara <= *saldo){

		if(nostomaara < 20 || nostomaara == 30){
			printf("Virheellinen määrä\n\n");	
		}
		else if(nostomaara % 10 == 0){

			*saldo = *saldo - nostomaara;
			while (nostomaara > 0){	

				if (nostomaara % 50 == 0){
					viiskyt = viiskyt + 1;
					nostomaara = nostomaara - 50;
				}
				else if (nostomaara % 20 == 0){
					kakskyt = kakskyt + 1;
					nostomaara = nostomaara - 20;
				}
				/*ohjelma ei ymmärtänyt väliin putoavia lukuja, joten lisäsin tämän elsen */
				else{
					viiskyt = viiskyt +1;
					nostomaara = nostomaara -50;
				}
			}	
		}
		else{
			printf("Virheellinen määrä\n\n");
		}

		printf("Tulostettavat rahat \n");
		printf("Viiden kympin setelien määrä: %d \n", viiskyt);
		printf("Kahden kympin setelien määrä: %d \n", kakskyt);
		nykySaldo(*saldo);
	}
	else{
		printf("Tililläsi ei ole tarpeeksi paalua\n");
		nykySaldo(*saldo);
	}
}

/* Kysyy käyttäjältä talletuksen määrän ja nykyisen saldon */
void talletus(int *saldo){

	int add = 0;
	printf("\nPaljonko haluatte tallettaa?: \n");
	add = lueKokonaisluku();
	*saldo = *saldo + add;
	printf("Kiitos.\n");

}

/* Näyttää tilin nykyisen saldon */
void nykySaldo(int saldo){

	printf("Sinulla on %d shekeliä tililläsi\n", saldo);

}

/* Kysyy käyttäjältä, haluaako tämä tehdä toisen siirron */
void toisto(char * repeat){

	printf("\nHaluatko tehdä toisen siirron?\n");
	printf("Valitse Kyllä (K) tai Ei (E)? \n");
	scanf(" %c", repeat);
}

int lueKokonaisluku(void){
   
   int luku;
   char mki;
   int status;
   
   while((status = scanf("%d%c", &luku, &mki))==0  || (2 == status && mki != '\n') ){
      lueRoskat();
      printf("Et syottanyt kokonaislukua ");
   }
   
   return luku;
}

void lueRoskat(void){

   while(fgetc(stdin) != '\n');

}