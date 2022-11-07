#define LED1 36
#define LED2 38
#define LED3 39
#define LED4 40
#define blue_button 5
#define red_button 7
#define ldr 14
#define buzzer 45
int luminosidade = analogRead(ldr); //guarda o valor da leitura do ldr em uma variável.
int binario[4]; //Define uma variável que será um vetor de 4 espaços.
int armazena[100]; //Define uma variável que armazena até 100 posições em um vetor para guardar os valores ao pressionar o botão
int i = 0; //Variável que funcionará como índice.
int qtdBinarios = 0; //Variável que funcionará como índice.
void converte_binario(int luz){ // Função que converte valores em binários.
  while (qtdBinarios != 4){
    binario[qtdBinarios]= luz % 2;
    luz = luz/2;
    qtdBinarios += 1;
  }
  qtdBinarios = 0;
}
void acende_luzinha(){ //Função que irá acender os leds de acordo com o valor em binário ( 0 e 1) .
  if (binario[0] == 0){
    digitalWrite(LED1, LOW); }
  else{
    digitalWrite(LED1, HIGH);
  }
  if (binario[1] == 0){
    digitalWrite(LED2, LOW);}
  else{
    digitalWrite(LED2, HIGH);
  }
  if (binario[2] == 0){
    digitalWrite(LED3, LOW);}
  else{
    digitalWrite(LED3, HIGH);
  }
  if (binario[3] == 0){
    digitalWrite(LED4, LOW);}
  else{
    digitalWrite(LED4, HIGH);
  }
}

void barulinho(int som){ // Função que toca uma nota musical para cada valor possível da leitura do ldr.
  if (som == 0){
    tone(buzzer,330.3,500);
  } else if (som == 1){
    tone(buzzer,350,500);
  } else if (som == 2){
    tone(buzzer,370.6,500);
  } else if (som == 3){
    tone(buzzer,392.4,500);
  } else if (som ==4){
    tone(buzzer,416.6,500);
  } else if (som ==5){
    tone(buzzer,468.8,500);
  } else if (som ==6){
    tone(buzzer,497.4,500);
  } else if (som ==7){
    tone(buzzer,526.3,500);
  } else if (som ==8){
    tone(buzzer,557.7,500);
  } else if (som ==9){
    tone(buzzer,589.2,500);
  } else if (som ==10){
    tone(buzzer,625.3,500);
  } else if (som ==11){
    tone(buzzer,663,500);
  } else if (som ==12){
    tone(buzzer,701.1,500);
  } else if (som ==13){
    tone(buzzer,792.4,500);
  } else if (som ==14){
    tone(buzzer,834.8,500);
  } else if (som ==15){
    tone(buzzer,887.2,500);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32-S3!");
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(blue_button, INPUT_PULLUP);
  pinMode(red_button, INPUT_PULLUP);
  pinMode(ldr, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int luminosidade = analogRead(ldr);
  int luz_convertida = luminosidade/269;
  converte_binario(luz_convertida); 
  acende_luzinha();
  delay(500);
  if (digitalRead(blue_button) == LOW) { // quando pressionar o botão ele vai armazenar as leituras do ldr e vai tocar o buzzer para aquela leitura
    armazena[i] = luz_convertida;
    barulinho(luz_convertida);
    i += 1;
    Serial.println(luz_convertida);
    delay(500);
  }
  if (digitalRead(red_button) == LOW) { // quando pressionar o botão vai exibir a sequência armazenada do outro botão nos leds e no buzzer.
    while (i > 0){
      barulinho(armazena[i]);
      converte_binario(armazena[i]);
      delay(350);
      acende_luzinha();
      i = i -1;
      Serial.println(luz_convertida);
    }
    armazena[i] = 0;
  }
}
