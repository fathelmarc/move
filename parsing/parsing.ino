struct gabungdata {
  char buffer[50];//menampung setiap karakter
  int counter; // menghitung index karakter yang tersimpan
  float hasil_parsing;//digunakan untuk menyimpan data yang sudah siap diparsi1ng
  String stringData, singhasil[10];
  bool sing;
} par;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
//  updateParse();
//  Serial.println(par.hasil_parsing);
  parsing();
  Serial.println(par.singhasil[1]);
  Serial.println(par.singhasil[2]);
  Serial.println(par.singhasil[3]);
  Serial.println(par.singhasil[4]);

}
void parsing() {
  while (Serial.available()) {
    char inchar = Serial.read();
    par.stringData += inchar;
    if (inchar = '\n') {
      par.sing = true;
    }
    if (par.sing) {
      int q = 0;
      for (int i = 0; i < par.stringData.length(); i++) {
        if (par.stringData[i] == '!') {
          q++;
          par.singhasil[1] = "";
        }else if(par.stringData[i] == '@'){
          q++;
          par.singhasil[2] = "";
        }else if(par.stringData[i] == '#'){
          q++;
          par.singhasil[3] = "";
        }else if(par.stringData[i] == '$'){
          q++;
          par.singhasil[4] = "";
        }else{
          par.singhasil[q] += par.stringData[i];
        }
      }
    }
  }
}
void updateParse() {
  while (Serial.available()) {
    char tmp = Serial.read();
    par.buffer[par.counter++] = tmp;
    if (tmp = '\n') {
      par.buffer[par.counter] = 0;
      par.hasil_parsing = atof(strtok(par.buffer + 5, ","));
      par.counter = 0;
    }
  }
}
