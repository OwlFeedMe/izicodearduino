#include <MaxMatrix.h>
#include <avr/pgmspace.h>

#include <LedControl.h>





int altavoz = 12;  //pin salida del altavoz, el otro pin del altavoz es GND
//octava alta
int Si2 = 1975;
int LaS2 = 1864;
int La2 = 1760;
int SolS2 = 1661;
int Sol2 = 1567;
int FaS2 = 1479;
int Fa2 = 1396;
int Mi2 = 1318;
int ReS2 = 1244;
int Re2 = 1174;
int DoS2 = 1108;
int Do2 = 1046;
//octava baja
int Si = 987;
int LaS = 932;
int La = 880;
int SolS = 830;
int Sol = 783;
int FaS = 739;
int Fa =  698;
int Mi =  659;
int ReS = 622;
int Re = 587;
int DoS = 554;
int Do = 523;
int bpm = 120;
//definimos las notas
int negra = 60000 / bpm;
int   negrap = negra * 1.5;
int blanca = negra * 2;
int blancap = blanca * 1.5;
int redonda = negra * 4;
int redondap = redonda * 1.5;
int corchea = negra / 2;
int corcheap = corchea * 1.5;
int semicorchea = negra / 4;
int  semicorcheap = semicorchea * 1.5;

int DIN = 8;
int CS =  9;
int CLK = 10;
int res1[] = {8,  16, 24,  28,  31,  35,  41,  45,  47,  52,  56,  58,  64};
int res2[] = {12,  20,  22,  28,  38,  41,  44,  50,  53,  61,  67,  69};
int linea1[] = {8,  16, 24,  28,  31,  35,  41,  45,  47,  52,  56,  58,  64};
int linea2[] = {12,  20,  22,  28,  38,  41,  44,  50,  53,  61,  67,  69};
int pos1 = 0;
int pos2 = 0;
unsigned long estadoA;
unsigned long estadoC;
int estadoAC;
int puntos = 0;
LedControl lc = LedControl(DIN, CLK, CS, 1);
//definimos la variable del tiempo
boolean game = true;
int estado = 0;
int estadoa = 0;
int salida = 0;
int botonI = 0;
int botonD = 0;
boolean resultado = false;
boolean puntoD = false;
boolean puntoI = false;
int a = 0;
int Nota[] = {Do, Do, Re, Do, Fa, Mi, Do, Do, Re, Do, Sol, Fa, Do, Do, Do2, La, Fa, Mi, Re, LaS, LaS, La, Fa, Sol, Fa};
char mensaje1[] = "" ; //Escriba el mensaje a desplegar
void setup() {
  lc.shutdown(0, false);      //The MAX72XX is in power-saving mode on startup
  lc.setIntensity(0, 5);     // Set the brightness to maximum value
  lc.clearDisplay(0);
  pinMode(7, INPUT);
  pinMode(5, INPUT);
  pinMode(4, INPUT);

  pinMode(altavoz, OUTPUT);
  //definimos la relacion de tiempo entre las notas


}

int Tiempo[] = {corchea, corchea, negra, negra, negra, blanca, corchea, corchea, negra, negra, negra, blanca, corchea, corchea, negra, negra, negra, negra, blanca, corchea, corchea, negra, negra, negra, blanca};
void resets() {
  for (int i = 0; i < 13; i++) {
    linea1[i] = res1[i];
  }
  for (int i = 0; i < 12; i++) {
    linea2[i] = res2[i];
  }


}
void move() {
  int ba = 0;
  int ba2 = 0;
  int b = 0;
  for (b = 0; b < 13; b++) {
    if (linea1[b] == 0) {
      ba++;


    } else {

      noTone(altavoz);
    }
    linea1[b] = linea1[b] - 1;

  }
  if (ba == 1) {
    puntoI = true;
  } else {
    puntoI = false;
  }
  a = a + 1;
  if (a == 23) {
    a = 0;
  }
  for (b = 0; b < 12; b++) {
    if (linea2[b] == 0) {
      ba2++;

    } else {

      noTone(altavoz);
    }

    linea2[b] = linea2[b] - 1;

  }
  if (ba2 == 1) {
    puntoD = true;
  } else {
    puntoD = false;
  }

}
void rungame() {
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, B00000000);
    lc.setLed(0, 0, 0, HIGH);
    lc.setLed(0, 7, 0, HIGH);
    lc.setLed(0, 3, 0, HIGH);
    lc.setLed(0, 4, 0, HIGH);
  }
  //
  int i = 0;
  int b = 0;
  for (b = 0; b < 13; b++) {
    if (linea1[b] > 7) {
    } else {
      int z = linea1[b];
      lc.setLed(0, 1, z, HIGH);
      lc.setLed(0, 2, z, HIGH);
      if (z == 0) {
        tone(altavoz, Nota[a], Tiempo[a]);
      }
    }
  }
  for (b = 0; b < 12; b++) {
    if (linea2[b] > 7) {} else {
      int x = linea2[b];
      lc.setLed(0, 5, x, HIGH);
      lc.setLed(0, 6, x, HIGH); if (x == 0) {
        tone(altavoz, Nota[a], Tiempo[a]);
      }
    }
  }
}
void loop() {
  if (linea2[11] == -1) {
    game = false;
  }
  botonI = digitalRead(5);
  botonD = digitalRead(4);
  estado = digitalRead(7);
  estadoC = millis();
  estadoAC += estadoC - estadoA;
  if ((estado == HIGH) && (estadoa == LOW)) {
    salida = 1 - salida;
    delay(50);
  }
  estadoa = estado;
  if (salida == 1) {
    if (game == true) {
      rungame();
    }
    if (game == false) {
      if (resultado == false) {
        resultado = true;
        lc.clearDisplay(0);
      }
      resets();
      switch (puntos)
      {
        case 0:
          { byte pun[] = {0x00, 0x00, 0x7e, 0x81, 0x81, 0x7e, 0x00, 0x00};
            printByte(pun);
          }
          break;
        case 1:
          { byte pun[] = {0x00, 0x00, 0x00, 0xff, 0x02, 0x04, 0x00, 0x00};
            printByte(pun);
          }
          break;
        case 2:
          { byte pun1[] = {0x00, 0x00, 0x8e, 0x91, 0xa1, 0xc6, 0x00, 0x00};
            printByte(pun1);
          }
          break;
        case 3: {
            byte pun2[] = {0x00, 0x00, 0x42, 0x81, 0x89, 0x76, 0x00, 0x00};
            printByte(pun2);
          }
          break;
        case 4: {
            byte pun3[] = {0x00, 0x00, 0x0f, 0x08, 0x08, 0xff, 0x00, 0x00};
            printByte(pun3);
          }
          break;
        case 5: {
            byte pun4[] = {0x00,0x00,0x6f,0x89,0x89,0x71,0x00,0x00};
            printByte(pun4);
          }
          break;
        case 6: {
            byte pun5[] = {0x00, 0x00, 0x7e, 0x89, 0x89, 0x72, 0x00, 0x00};
            printByte(pun5);
          }
          break;
        case 7: {
            byte pun6[] = {0x00, 0x00, 0x01, 0xe1, 0x19, 0x07, 0x00, 0x00};
            printByte(pun6);
          }
          break;
        case 8: {
            byte pun7[] = {0x00, 0x00, 0xff, 0x89, 0x89, 0xff, 0x00, 0x00};
            printByte(pun7);
          }
          break;
        case 9: {
            byte pun8[] = {0x00, 0x00, 0x0f, 0x09, 0x09, 0xff, 0x00, 0x00};
            printByte(pun8);
          }
          break;
        case 10: {
            byte pun9[] = {0x00, 0x00, 0x0f, 0x09, 0x09, 0xff, 0x00, 0x00};
            printByte(pun9);
          }
          break;
        case 11: {
            byte pun10[] = {0x04, 0x02, 0xff, 0x00, 0x7e, 0x81, 0x7e, 0x00};
            printByte(pun10);
          }
          break;
        case 12: {
            byte pun11[] = {0x04, 0x02, 0xff, 0x00, 0x04, 0x02, 0xff, 0x00};
            printByte(pun11);
          }
          break;
        case 13: {
            byte pun12[] = {0x04, 0x02, 0xff, 0x00, 0xe2, 0x91, 0x8e, 0x00};
            printByte(pun12);
          }
          break;
        case 14: {
            byte pun13[] = {0x04, 0x02, 0xff, 0x00, 0x42, 0x89, 0x76, 0x00};
            printByte(pun13);
          }
          break;
        case 15: {
            byte pun14[] = {0x04, 0x02, 0xff, 0x00, 0x0f, 0x08, 0xff, 0x00};
            printByte(pun14);
          }
          break;
        case 16: {
            byte pun15[] = {0x04, 0x02, 0xff, 0x00, 0x71, 0x89, 0x8f, 0x00};
            printByte(pun15);
          }
          break;
        case 17: {
            byte pun16[] = {0x04, 0x02, 0xff, 0x00, 0x7e, 0x89, 0x71, 0x00};
            printByte(pun16);
          }
          break;
        case 18: {
            byte pun17[] = {0x04, 0x02, 0xff, 0x00, 0x01, 0xf1, 0x0f, 0x00};
            printByte(pun17);
          }
          break;
        case 19: {
            byte pun18[] = {0x04, 0x02, 0xff, 0x00, 0xff, 0x89, 0xff, 0x00};
            printByte(pun18);
          }
          break;
        case 20: {
            byte pun19[] = {0x04, 0x02, 0xff, 0x00, 0x0f, 0x09, 0xff, 0x00};
            printByte(pun19);
          }
          break;
        case 21: {
            byte pun20[] = {0xc6, 0xa1, 0x9e, 0x00, 0x7e, 0x81, 0x7e, 0x00};
            printByte(pun20);
          }
          break;
        case 22: {
            byte pun21[] = {0xc6, 0xa1, 0x9e, 0x00, 0x04, 0x02, 0xff, 0x00};
            printByte(pun21);
          }
          break;
        case 23: {
            byte pun22[] = {0xc6, 0xa1, 0x9e, 0x00, 0x42, 0x89, 0x76, 0x00};
            printByte(pun22);
          }
          break;
        case 24: {
            byte pun23[] = {0xc6, 0xa1, 0x9e, 0x00, 0x0f, 0x08, 0xff, 0x00};
            printByte(pun23);
          }
          break;
        case 25: {
            byte pun24[] = {0xc6,0xa1,0x9e,0x00,0x4f,0x89,0x71,0x00};
            printByte(pun24);
          }
          break;
        default: break;
      }
    }
    if (estadoAC > 200) {
      estadoAC = 0;
      move();
    }
  } else {
    resultado=false;
    puntos=0;
    game = true;
    lc.clearDisplay(0);         
  }
 
  if ((botonI == HIGH) && (puntoI == true)) {
    puntos++;
    puntoI = false;
  }
  if ((botonD == HIGH) && (puntoD == true)) {
    puntos++;
    puntoD = false;
  }
 
  estadoA = estadoC;




}

void printByte(byte character [])
{
  int i = 0;
  for (i = 0; i < 8; i++)
  {
    lc.setRow(0, i, character[i]);
  }
}


