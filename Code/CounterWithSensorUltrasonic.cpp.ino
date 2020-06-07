//library kumpulan perintah untuk menampilkan karakter pada LCD
#include <LiquidCrystal.h> 

//Mendefine posisi pin arduino yang dihubungkan dengan sensor ultrasonik
#define trigPin 2
#define echoPin 3
//Define pin push button
#define button 4

//Memberitahu Arduino pin mana saja yang dihubungkan dengan LCD
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
 

//Set inisialisasi nilai counter
int counter = 0;
int currentState = 0;
int previousState = 0;

//Inisialisasi hasil hitung setiap sesi
int i=1; //nomor sesi
int c[100]={0}; //array nilai per sesi
int *result = &c[0]; //pointer untuk menyimpan setiap sesi


void setup(){

  //Ultrasonic Sensor Code
  //put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  //LCD Code
  //Memberitahu LCD bahwa kita menggunakan Layar LCD berukuran
  //lebar 16 karakter dan tinggi 2 karakter
  lcd.begin(16, 2);
  //Membersihkan layar
  lcd.clear();
}


void loop(){
  
  //Menyimpan dan mencetak hasil hitung ketika push button ditekan
  //pada sesi tersebut
  *result = counter;
  int state = digitalRead(button);
  if(state == HIGH){
    //Membersihkan layar
    lcd.clear();
    //Hasil Perhitungan Sesi ke-i
    Serial.print("Hasil hitung ke-"); Serial.print(i);
    Serial.print(" : "); Serial.println(*result);
    counter=0;
    if(*result != 0){
      i++; result++;
    }
    //Data Tersimpan Keseluruhan Sesi
    int j=0;
    Serial.print("Data tersimpan dari ");
    Serial.print(i-1);
    Serial.print(" sesi : ");   
    Serial.print(c[j]); j++;
    while(j<i-1){
      Serial.print(", ");
      Serial.print(c[j]);
      j++;
    }
    Serial.println();
    Serial.println();
    delay(1000);
  }

  //LCD Code  
  //Set kursor pada posisi 0 (pojok kiri atas)
  lcd.setCursor(0,0);
  //Menampilkan kata "Count:" pada posisi awal
  lcd.print("Count:");
  

  //Memindahkan pada posisi 1 dibaris kedua
  lcd.setCursor(0,1);
  //Menampilkan nilai counter saat inisialisasi
  lcd.print(counter);

  
  //Sensor Code
  // put your main code here, to run repeatedly:
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  //Cek kondisi apakah posisi benda berjarak <=10 cm dari sensor
  if (distance <= 10){
    currentState = 1;
  }
  else{
    currentState = 0;
  }
  delay(100);
  if(currentState != previousState){
    if(currentState == 1){
      counter += 1;
      //Untuk uji di serial monitor
      if(counter==1) {
        Serial.print("Counter Sesi ");
        Serial.print(i);
        Serial.println(" :");
      }
      Serial.println(counter);
      
      //Memindahkan pada posisi 1 dibaris kedua
      lcd.setCursor(0,1);
      //Menampilkan jumlah saat ini
      lcd.print(counter);
    }
    previousState=currentState;
  }
}
