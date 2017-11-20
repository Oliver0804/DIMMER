#define Light_level 100
//40 00 00 00 00 72 AA 67 30 62 30 77 30 23
int brightness = 128;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
byte Color_R[4];
byte Color_G[4];
byte Color_B[4];
byte Color_W[4];
byte Color_SR[4];
byte Color_SG[4];
byte Color_SB[4];
byte Color_SW[4] = {Light_level, Light_level, Light_level, Light_level};
byte Color_DR[4];
byte Color_DG[4];
byte Color_DB[4];
byte Color_DW[4];
byte buffer_RX[70];
int flag_RX = 0;
int room = 2;
int buttonState = 0;
int tiger_word = 0;

char buff[20] = {0x00};
int buff_flag = 0;

// the setup routine runs once when you press reset:
void setup() {

  // declare pin 9 to be an output:
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(26, INPUT);
  digitalWrite(26, HIGH);
  for (int color = 0; color < 20; color++) {
    analogWrite(2, color);
    analogWrite(3, color);
    analogWrite(4, color);
    analogWrite(5, color);
    delay(20);
  }
  for (int color = 0; color < 20; color++) {
    analogWrite(6, color);
    analogWrite(7, color);
    analogWrite(8, color);
    analogWrite(9, color);
    delay(20);
  }
  for (int color = 0; color < 20; color++) {
    analogWrite(10, color);
    analogWrite(11, color);
    analogWrite(12, color);
    analogWrite(13, color);
    delay(20);
  }
  for (int color = 50; color > -1; color--) {
    analogWrite(10, color);
    analogWrite(11, color);
    analogWrite(12, color);
    analogWrite(13, color);
    analogWrite(6, color);
    analogWrite(7, color);
    analogWrite(8, color);
    analogWrite(9, color);
    analogWrite(2, color);
    analogWrite(3, color);
    analogWrite(4, color);
    analogWrite(5, color);
    delay(20);
  }
  //Serial.println("HI!!!");
}

// the loop routine runs over and over again forever:
void loop() {
  buttonState = digitalRead(26);
  if (buttonState == LOW && tiger_word == 0) {
    tiger_word = 1;

  }
  if (buttonState == HIGH && tiger_word == 1) {
    tiger_word = 0;
  }
  flag_RX = 0;
  while (Serial.available()) {
    buffer_RX[flag_RX++] = (char)Serial.read();
    //Serial.print(".");
  }
  while (Serial1.available()) {
    buffer_RX[flag_RX++] = (char)Serial1.read();
    //Serial.print(".");
  }
  buff_flag = 0;
  while (Serial2.available()) {
    buff[buff_flag] = Serial2.read();
    Serial.print(buff[buff_flag]);
    buff_flag++;
    delay(5);
  }
  for (int x = 0; x < 50; x++) {
    //Serial.print(buffer_RX[x]);
    if (buffer_RX[x] == '@' && buffer_RX[x + 10 + 3] == '#') {
      //Serial.println("OK!");
      buffer_RX[x] = 0;
      flag_RX = 0;
      switch (buffer_RX[x + 1]) {
        case 0x00:

          Serial.println("A1");
          Serial.println(buffer_RX[x + 3 + 3]);
          Serial.println(buffer_RX[x + 5 + 3]);
          Serial.println(buffer_RX[x + 7 + 3]);
          Serial.println(buffer_RX[x + 9 + 3]);

          Color_SR[1] = (int)buffer_RX[x + 3 + 3];
          Color_SG[1] = buffer_RX[x + 5 + 3];
          Color_SB[1] = buffer_RX[x + 7 + 3];
          Color_SW[1] = buffer_RX[x + 9 + 3];
          //analogWrite(2, Color_R[1]);
          //analogWrite(3, Color_G[1]);
          //analogWrite(4, Color_B[1]);
          //analogWrite(5, Color_W[1]);

          break;
        case 0x01:

          Serial.println("A2");
          Serial.println(buffer_RX[x + 3 + 3]);
          Serial.println(buffer_RX[x + 5 + 3]);
          Serial.println(buffer_RX[x + 7 + 3]);
          Serial.println(buffer_RX[x + 9 + 3]);

          Color_SR[2] = buffer_RX[x + 3 + 3];
          Color_SG[2] = buffer_RX[x + 5 + 3];
          Color_SB[2] = buffer_RX[x + 7 + 3];
          Color_SW[2] = buffer_RX[x + 9 + 3];
          //analogWrite(6, Color_R[2]);
          //analogWrite(7, Color_G[2]);
          //analogWrite(8, Color_B[2]);
          //analogWrite(9, Color_W[2]);

          break;
        case 0x02:

          Serial.println("A3");
          Serial.println(buffer_RX[x + 3 + 3]);
          Serial.println(buffer_RX[x + 5 + 3]);
          Serial.println(buffer_RX[x + 7 + 3]);
          Serial.println(buffer_RX[x + 9 + 3]);

          Color_SR[3] = buffer_RX[x + 3 + 3];
          Color_SG[3] = buffer_RX[x + 5 + 3];
          Color_SB[3] = buffer_RX[x + 7 + 3];
          Color_SW[3] = buffer_RX[x + 9 + 3];
          //analogWrite(10, Color_R[3]);
          // analogWrite(11, Color_G[3]);
          //analogWrite(12, Color_B[3]);
          //analogWrite(13, Color_W[3]);

          break;
        case '4':
          Serial.println("A4");
          Serial.println(buffer_RX[x + 3]);
          Serial.println(buffer_RX[x + 5]);
          Serial.println(buffer_RX[x + 7]);
          Serial.println(buffer_RX[x + 9]);
          break;
        case '5':
          break;
      }
    }
  }
  // Serial.print(Color_R[1]);
  // Serial.print("\t");
  // Serial.print(Color_SR[1]);
  // Serial.println("\t");
  change_color();
  voice_ctr();
  delay(2);
}
void change_color() {
  if (Color_SR[1] > Color_R[1]) {
    Color_R[1] = Color_R[1] + 1;
    //analogWrite(2, Color_R[1]);
    //Serial.print("+");
  } else if (Color_SR[1] < Color_R[1]) {
    Color_R[1] =  Color_R[1] - 1;
    //analogWrite(2, Color_R[1]);
    //Serial.print("-");
  }
  if (Color_SB[1] > Color_B[1]) {
    Color_B[1] = Color_B[1] + 1;
    // analogWrite(3, Color_B[1]);
  } else if (Color_SB[1] < Color_B[1]) {
    Color_B[1] = Color_B[1] - 1;
    // analogWrite(3, Color_B[1]);
  }
  if (Color_SG[1] > Color_G[1]) {
    Color_G[1] = Color_G[1] + 1;
    //analogWrite(4, Color_G[1]);
  } else if (Color_SG[1] < Color_G[1]) {
    Color_G[1] = Color_G[1] - 1;
    // analogWrite(4, Color_G[1]);
  }
  if (Color_SW[1] > Color_W[1]) {
    Color_W[1] = Color_W[1] + 1;
    //analogWrite(5, Color_W[1]);
  } else if (Color_SW[1] < Color_W[1]) {
    Color_W[1] = Color_W[1] - 1;
    //analogWrite(5, Color_W[1]);
  }

  if (Color_SR[2] > Color_R[2]) {
    Color_R[2] = Color_R[2] + 1;
    // analogWrite(6, Color_R[2]);
  } else if (Color_SR[2] < Color_R[2]) {
    Color_R[2] =  Color_R[2] - 1;
    //analogWrite(6, Color_R[2]);
  }
  if (Color_SB[2] > Color_B[2]) {
    Color_B[2] = Color_B[2] + 1;
    //analogWrite(7, Color_B[2]);
  } else if (Color_SB[2] < Color_B[2]) {
    Color_B[2] = Color_B[2] - 1;
    //analogWrite(7, Color_B[2]);
  }
  if (Color_SG[2] > Color_G[2]) {
    Color_G[2] = Color_G[2] + 1;
    //analogWrite(8, Color_G[2]);
  } else if (Color_SG[2] < Color_G[2]) {
    Color_G[2] = Color_G[2] - 1;
    //analogWrite(8, Color_G[2]);
  }
  if (Color_SW[2] > Color_W[2]) {
    Color_W[2] = Color_W[2] + 1;
    //analogWrite(9, Color_W[2]);
  } else if (Color_SW[2] < Color_W[2]) {
    Color_W[2] = Color_W[2] - 1;
    //analogWrite(9, Color_W[2]);
  }


  if (Color_SR[3] > Color_R[3]) {
    Color_R[3] = Color_R[3] + 1;
    // analogWrite(10, Color_R[3]);
  } else if (Color_SR[3] < Color_R[3]) {
    Color_R[3] =  Color_R[3] - 1;
    //analogWrite(10, Color_R[3]);
  }
  if (Color_SB[3] > Color_B[3]) {
    Color_B[3] = Color_B[3] + 1;
    //analogWrite(11, Color_B[3]);
  } else if (Color_SB[3] < Color_B[3]) {
    Color_B[3] = Color_B[3] - 1;
    //analogWrite(11, Color_B[3]);
  }
  if (Color_SG[3] > Color_G[3]) {
    Color_G[3] = Color_G[3] + 1;
    // analogWrite(12, Color_G[3]);
  } else if (Color_SG[3] < Color_G[3]) {
    Color_G[3] = Color_G[3] - 1;
    // analogWrite(12, Color_G[3]);
  }
  if (Color_SW[3] > Color_W[3]) {
    Color_W[3] = Color_W[3] + 1;
    // analogWrite(13, Color_W[3]);
  } else if (Color_SW[3] < Color_W[3]) {
    Color_W[3] = Color_W[3] - 1;
    //analogWrite(13, Color_W[3]);
  }
  analogWrite(2, Color_R[1]);
  analogWrite(3, Color_B[1]);
  analogWrite(4, Color_G[1]);
  analogWrite(5, Color_W[1]);

  analogWrite(6, Color_R[2]);
  analogWrite(7, Color_B[2]);
  analogWrite(8, Color_G[2]);
  analogWrite(9, Color_W[2]);

  analogWrite(10, Color_R[3]);
  analogWrite(11, Color_B[3]);
  analogWrite(12, Color_G[3]);
  analogWrite(13, Color_W[3]);
}
void voice_ctr() {
  if (buff[0] != 0x00) {
    for (int x = 0; x < 20; x++) {
      //Serial.print(buff[x]);
      if (x == 0) {
        if (buff[x] == '1' && buff[x + 1] != '0' ) {
          Serial.println("!");
          for (int color = 0; color < 10; color++) {
            analogWrite(2, color);
            analogWrite(3, color);
            analogWrite(4, color);
            analogWrite(5, color);
            delay(5);
          }
          for (int color = 20; color > -1; color--) {
            analogWrite(2, color);
            analogWrite(3, color);
            analogWrite(4, color);
            analogWrite(5, color);
            delay(5);
          }
          for (int color = 0; color < 10; color++) {
            analogWrite(6, color);
            analogWrite(7, color);
            analogWrite(8, color);
            analogWrite(9, color);
            delay(5);
          }
          for (int color = 20; color > -1; color--) {
            analogWrite(6, color);
            analogWrite(7, color);
            analogWrite(8, color);
            analogWrite(9, color);
            delay(5);
          }
          for (int color = 0; color < 10; color++) {
            analogWrite(10, color);
            analogWrite(11, color);
            analogWrite(12, color);
            analogWrite(13, color);
            delay(5);
          }
          for (int color = 20; color > -1; color--) {
            analogWrite(10, color);
            analogWrite(11, color);
            analogWrite(12, color);
            analogWrite(13, color);
            delay(5);
          }
        }
      }
      if (x == 2) {
        //Serial.print(buff[x]);
        if (buff[x] == '0') {
          Serial.println("!");
        } else if (buff[x] == '1') {
          Serial.println("Change Light to Green");
          if (room != 0) {
            Color_SW[room] = Color_SR[room] = Color_SB[room] = Color_SG[room] = 0;
            Color_SG[room] = Light_level;
          } else {
            for (int c = 1; c <= 3; c++) {
              Color_SW[c] = Color_SR[c] = Color_SB[c] = Color_SG[c] = 0;
              Color_SG[c] = Light_level;
            }
          }
          //SG = 200;
          //SW = SR = SB = 0;
        } else if (buff[x] == '2') {
          Serial.println("TV power");
          if (room != 0) {
            Color_SW[room] = Color_SR[room] = Color_SB[room] = Color_SG[room] = 0;
            Color_SW[room] = Light_level;
          } else {
            for (int c = 1; c <= 3; c++) {
              Color_SW[c] = Color_SR[c] = Color_SB[c] = Color_SG[c] = 0;
              Color_SW[c] = Light_level;
            }
          }
        } else if (buff[x] == '3') {
          Serial.println("All lights");
          room = 0;
          if (Color_SW[1] != 0 || Color_SR[1] != 0 || Color_SB[1] != 0 || Color_SG[1] != 0 ||
              Color_SW[2] != 0 || Color_SR[2] != 0 || Color_SB[2] != 0 || Color_SG[2] != 0 ||
              Color_SW[3] != 0 || Color_SR[3] != 0 || Color_SB[3] != 0 || Color_SG[3] != 0) {
            for (int g = 0; g <= 3; g++) {
              Color_DW[g] = Color_SW[g];
              Color_DR[g] = Color_SR[g];
              Color_DB[g] = Color_SB[g];
              Color_DG[g] = Color_SG[g];
            }
            Color_SW[1] = Color_SR[1] = Color_SB[1] = Color_SG[1] = 0;
            Color_SW[2] = Color_SR[2] = Color_SB[2] = Color_SG[2] = 0;
            Color_SW[3] = Color_SR[3] = Color_SB[3] = Color_SG[3] = 0;
            //SW = SG = SB = SR = 0;
          } else {
            room=1;
            if (Color_SW[room] == Color_DW[room] && Color_SR[room] == Color_DR[room] && Color_SG[room] == Color_DG[room] && Color_SB[room] == Color_DB[room]) {
              Color_SW[room] = Light_level;
            } else {
              Color_SW[room] = Color_DW[room];
              Color_SR[room] = Color_DR[room];
              Color_SG[room] = Color_DG[room];
              Color_SB[room] = Color_DB[room];
            }
            room++;
            if (Color_SW[room] == Color_DW[room] && Color_SR[room] == Color_DR[room] && Color_SG[room] == Color_DG[room] && Color_SB[room] == Color_DB[room]) {
              Color_SW[room] = Light_level;
            } else {
              Color_SW[room] = Color_DW[room];
              Color_SR[room] = Color_DR[room];
              Color_SG[room] = Color_DG[room];
              Color_SB[room] = Color_DB[room];
            }
            room++;
            if (Color_SW[room] == Color_DW[room] && Color_SR[room] == Color_DR[room] && Color_SG[room] == Color_DG[room] && Color_SB[room] == Color_DB[room]) {
              Color_SW[room] = Light_level;
            } else {
              Color_SW[room] = Color_DW[room];
              Color_SR[room] = Color_DR[room];
              Color_SG[room] = Color_DG[room];
              Color_SB[room] = Color_DB[room];
            }
            room = 0;
            /*for (int g = 0; g <= 3; g++) {
              Color_SW[g] = Color_DW[g];
              Color_SR[g] = Color_DR[g];
              Color_SG[g] = Color_DG[g];
              Color_SB[g] = Color_DB[g];
            }*/
          }

        } else if (buff[x] == '4') {
          Serial.println("Living room lights");
          //digitalWrite(LED_2, !digitalRead(LED_2));
          room = 1;
          if (Color_SW[room] != 0 || Color_SR[room] != 0 || Color_SB[room] != 0 || Color_SG[room] != 0) {
            Color_DW[room] = Color_SW[room];
            Color_DR[room] = Color_SR[room];
            Color_DB[room] = Color_SB[room];
            Color_DG[room] = Color_SG[room];
            Color_SW[room] = Color_SR[room] = Color_SB[room] = Color_SG[room] = 0;
          } else {
            if (Color_SW[room] == Color_DW[room] && Color_SR[room] == Color_DR[room] && Color_SG[room] == Color_DG[room] && Color_SB[room] == Color_DB[room]) {
              Color_SW[room] = Light_level;
            } else {
              Color_SW[room] = Color_DW[room];
              Color_SR[room] = Color_DR[room];
              Color_SG[room] = Color_DG[room];
              Color_SB[room] = Color_DB[room];
            }
          }
        } else if (buff[x] == '5') {
          Serial.println("Kitchen lights");
          //digitalWrite(LED_1, !digitalRead(LED_1))
          room = 3;
          if (Color_SW[room] != 0 || Color_SR[room] != 0 || Color_SB[room] != 0 || Color_SG[room] != 0) {
            Color_DW[room] = Color_SW[room];
            Color_DR[room] = Color_SR[room];
            Color_DB[room] = Color_SB[room];
            Color_DG[room] = Color_SG[room];
            Color_SW[room] = Color_SR[room] = Color_SB[room] = Color_SG[room] = 0;
          } else {
            if (Color_SW[room] == Color_DW[room] && Color_SR[room] == Color_DR[room] && Color_SG[room] == Color_DG[room] && Color_SB[room] == Color_DB[room]) {
              Color_SW[room] = Light_level;
            } else {
              Color_SW[room] = Color_DW[room];
              Color_SR[room] = Color_DR[room];
              Color_SG[room] = Color_DG[room];
              Color_SB[room] = Color_DB[room];
            }
          }
        } else if (buff[x] == '6') {
          Serial.println("Change Light to Red");
          if (room != 0) {
            Color_SW[room] = Color_SR[room] = Color_SB[room] = Color_SG[room] = 0;
            Color_SR[room] = Light_level;
          } else {
            for (int c = 1; c <= 3; c++) {
              Color_SW[c] = Color_SR[c] = Color_SB[c] = Color_SG[c] = 0;
              Color_SR[c] = Light_level;
            }
          }
        } else if (buff[x] == '7') {
          Serial.println("Bedroom lights");
          room = 2;
          if (Color_SW[room] != 0 || Color_SR[room] != 0 || Color_SB[room] != 0 || Color_SG[room] != 0) {
            Color_DW[room] = Color_SW[room];
            Color_DR[room] = Color_SR[room];
            Color_DB[room] = Color_SB[room];
            Color_DG[room] = Color_SG[room];
            Color_SW[room] = Color_SR[room] = Color_SB[room] = Color_SG[room] = 0;
          } else {
            if (Color_SW[room] == Color_DW[room] && Color_SR[room] == Color_DR[room] && Color_SG[room] == Color_DG[room] && Color_SB[room] == Color_DB[room]) {
              Color_SW[room] = Light_level;
            } else {
              Color_SW[room] = Color_DW[room];
              Color_SR[room] = Color_DR[room];
              Color_SG[room] = Color_DG[room];
              Color_SB[room] = Color_DB[room];
            }
          }
        } else if (buff[x] == '8') {
          Serial.println("Change light to Blue");
          if (room != 0) {
            Color_SW[room] = Color_SR[room] = Color_SB[room] = Color_SG[room] = 0;
            Color_SB[room] = Light_level;
          } else {
            for (int c = 1; c <= 3; c++) {
              Color_SW[c] = Color_SR[c] = Color_SB[c] = Color_SG[c] = 0;
              Color_SB[c] = Light_level;
            }
          }
        }
      }
      buff[x] = 0x00;
    }
  }
}
