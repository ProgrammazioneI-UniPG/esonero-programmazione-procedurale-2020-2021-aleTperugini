#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//VARIABILI
char plainText[129];
char key[129];
char cipherText[129];
char decrypText[129];
time_t seed;
int plainTextLen;
int control = 0;
char method = 0;

//FUNZIONI
int enterKey();
int randKey();
int cipher();

int cipher(void){

  int i, c;
  //CIFRATURA
  for(i=0; i<plainTextLen; i++){

      c = plainText[i]^key[i];
      cipherText[i] = c;
  }
  cipherText[i] = '\0';

  printf("\nTesto cifrato: %s\n",cipherText );
  printf("Testo cifrato in int(per vedere se sono stati generati caratteri da 0 a 31):\n");
  for(i=0; i<plainTextLen; i++){

    printf("|%d|",cipherText[i] );
  }

  //DECIFRATURA
  for(i=0; i<plainTextLen; i++){

      c = cipherText[i]^key[i];
      decrypText[i] = c;
  }
  decrypText[i] = '\0';

  printf("\nTesto decifrato: %s\n", decrypText);

  return 0;
}

int enterKey(void){

    int i, control1 = 0;
    int keyLen;

    int ch1;
    while ((ch1 = getchar()) != '\n' && ch1 != EOF);

    //RICHIESTA CHIAVE MIMINO LUNGA QUANTO PlainText
    do{
      printf("\nInserisci una chiave di lunghezza minima %d e massimo 128\n", plainTextLen );

      fgets(key, plainTextLen+1, stdin);
      for(i = 0; i<129; i++){
        if(key[i]=='\n'){
          key[i]='\0';
          break;
        }
      }
      keyLen = strlen(key);
      if(keyLen<plainTextLen){

        printf("\nErrore: chiave troppo corta\n");
      }
      else{

        printf("La chiave è : %s\n", key);
        control1=1;
      }
    }
    while(control1==0);

    //CIFRATURA
    cipher();

    return 0;
}

int randKey(void){

    int i, r;
    srand((unsigned)time(&seed));

    for(i=0; i<plainTextLen; i++){

      r = (rand() % 96) + 32;
      key[i] = r;
    }
    key[i] = '\0';

    printf("Chiave generata: %s\n", key);

    //CIFRATURA
    cipher();

    return 0;
}

int main(){
  //RICHIESTA STRINGA PlainText
  printf("Inserire una stringa lunga massimo 128 caratteri\nTutti i caratteri in eccesso verranno rimossi\n");

  fgets(plainText, 129, stdin);
  for(int i = 0; i<129; i++){
    if(plainText[i]=='\n'){
      plainText[i]='\0';
      break;
    }
  }
  plainTextLen = strlen(plainText);

  printf("La stringa è: %s\nLunghezza stringa: %d\n\nScegli un metodo per inserire la chiave\nDigita [1] per inserire manualmente la chiave\naltrimenti, digita [2] per generarla casualmente\n", plainText, plainTextLen);

  do{
    //SCELTA METODO PER LA CHIAVE Key
    scanf("%c", &method );

    switch (method) {
      case '1':
          printf("\nHai scelto di inserire la chiave\n");
          control = 1;
          enterKey();
          break;
      case '2':
          printf("\nHai scelto di generare una chiave casuale\n");
          control = 1;
          randKey();
          break;
      default:
          printf("Input non corretto\nDigita [1] per inserire manualmente la chiave\naltrimenti, digita [2] per generarla casualmente\n");
    }

    char ch;
    while((ch= getchar()) != '\n' && ch != EOF);
  }
  while(control==0);

  return 0;
}
