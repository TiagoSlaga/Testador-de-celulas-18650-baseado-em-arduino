/*
  Testador de células 18650 de Íons de Lítio.
    Realiza a leitura da tensão em cada celula atravez de um pino analogico.
    Atravez de um pino digital realiza o acionamento de um circuito
    que drena uma corrente constante pré configurada.(Ex: 1A); 
    As leituras e resultados dos testes são printados em um display
    LCD.
    Codigo sendo desenvolvido para testar 6 baterias simultaneamente.
    até o momento pode testar apenas 2.
*/

#include <LiquidCrystal.h>

// Definições dos pinos para o display LCD.
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// variaveis. 
int bat1, bat2;
int cap_bat1, cap_bat2;
unsigned long tempo_bat1, tempo_bat2;
float vbat1, vbat2;
bool start_test_bat1, start_test_bat2;

// Funções.
void teste_bat1();
void teste_bat2();
void tela1(); 
void tela2();  



void setup() {
    //Inicialização do display
    lcd.begin(16, 2);

    //Configuração dos pinos a serem utilizados em cada bateria.

    //Celula 01
    pinMode(A0, INPUT);
    pinMode(8, OUTPUT);

    //Celula 02
    pinMode(A1, INPUT);
    pinMode(9, OUTPUT);


}

void loop() {
  //leituras analogicas
  bat1 = analogRead(A0);
  bat2 = analogRead(A1);

  //conversão dos valores para volts
  vbat1 = (map(bat1, 0, 1023, 0 , 500)/100.0);
  vbat2 = (map(bat2, 0, 1023, 0 , 500)/100.0);


  //Função para teste e print dos dados da bateria 01
  teste_bat1();
  tela1();

  //Função para teste e print dos dados da bateria 02
  teste_bat2();
  tela2();

}

void teste_bat1(){

  if(vbat1 > 4.00 && start_test_bat1 == false){ //Inicia o teste se a bateria estiver acima de 4V.
    start_test_bat1 = true;
    tempo_bat1 = millis();
    }

  if(start_test_bat1 == true){ //Verifica quanto tempo a bateria esta em teste e calcula a capacidade
    digitalWrite(8, LOW);
    cap_bat1 = (millis() - tempo_bat1) /3600; 

    
    if(vbat1 < 2.75){  // Finaliza o teste quando a celula atinge 2.75V
      start_test_bat1 = false;
    }
  }

  else { //Desliga o consumo de corrente
    digitalWrite(8, HIGH);
  }
  
}


void teste_bat2(){

  if(vbat2 > 4.00 && start_test_bat2 == false){  //Inicia o teste se a bateria estiver acima de 4V.
    start_test_bat2 = true;
    tempo_bat2 = millis();
    }

  if(start_test_bat2 == true){  //Verifica quanto tempo a celula esta em teste e calcula a capacidade.
    digitalWrite(9, LOW);
    cap_bat2 = (millis() - tempo_bat2) /3600; 

    
    if(vbat1 < 2.75){ // Finaliza o teste quando a celula atinge 2.75V
      start_test_bat2 = false;
    }
  }

  else { //Desliga o consumo de corrente
    digitalWrite(9, HIGH);
  }
  
}


void tela1(){ // Mostra valores de tensão, capacidade e estado do teste na bateria 01.

    lcd.clear(); // Limpa o display

  if(start_test_bat1 == true){
    lcd.setCursor(1, 1);
    lcd.print("Bat 01 ");
    lcd.print("Testando... ");
    }
    else{
    lcd.setCursor(1, 1);
    lcd.print("Bat 01 ");
    lcd.print("Parado... ");   
    }
  
  lcd.setCursor(1, 2);
  lcd.print(cap_bat1);
  lcd.print(" mAh  ");
  lcd.print(vbat1);
  lcd.print(" V");

  delay(1000);
  }

  
void tela2(){
    lcd.clear();

  if(start_test_bat2 == true){
    lcd.setCursor(1, 1);
    lcd.print("Bat 02 ");
    lcd.print("Testando... ");
    }
    else{
    lcd.setCursor(1, 1);
    lcd.print("Bat 02 ");
    lcd.print("Parado... ");   
    }
  
  lcd.setCursor(1, 2);
  lcd.print(cap_bat2);
  lcd.print(" mAh  ");
  lcd.print(vbat2);
  lcd.print(" V");

  delay(1000);
  }