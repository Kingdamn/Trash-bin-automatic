#include <NewPing.h>          //memanggil library ultrasonic
#include <Servo.h>            //memanggil library servo

//sensor sampah
#define TRIGGER_PIN   6       //pin trigger dihubungkan ke pin 8 arduino
#define ECHO_PIN      7       //pin echo dihubungkan ke pin 7 arduino
//sensor kapasitas
#define TRIGGER_PIN2  8      //pin trigger dihubungkan ke pin 10 arduino
#define ECHO_PIN2     9       //pin echo dihubungkan ke pin 9 arduino
#define MAX_DISTANCE 200      //batas jarak dari sensor

#include <LiquidCrystal_I2C.h>         //memanggil library LCD
//inisialisasi nomor pin LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);   //kalau masih tidak tampil, ganti menjadi 0x3f(alamat i2c)


#include <SoftwareSerial.h>

Servo servoAne;
NewPing sampah(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);      //membuat variabel sampah
NewPing kapasitas(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE); //membuat variabel kapasitas


void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  servoAne.attach(10);            //inisialisasi pin servo
  servoAne.write(0);

}

void loop() {
   delay(50);
  int US1 = sampah.ping_cm();
  int US2 = kapasitas.ping_cm();  
  US2 = map(US2,15,2,0,100);
   

  //tampil ke serial monitor 
  Serial.print("sampah : ");
  Serial.print(US1);
  Serial.println("cm ");


  //tampilkan ke lcd
  lcd.setCursor(3, 0); //set kolom dan baris
  lcd.print(" Kapasitas ");
  lcd.setCursor(0, 1); //set kolom dan baris
  lcd.print("Tong Sampah:");
  lcd.print(US2);
  lcd.print("%");
  delay (50);

  //Jika sensor mendeteksi orang mendekati tong sampah, maka tetapkan servo di posisi 180 derajat 
  //dan nyalakan led hijau serta matikan led merah. kemudian DFpalyer menyala sebagai suara'
  if(US1 == 0){}
  else if(US1 <= 8   ){
    servoAne.write(180);            //posisikan servo di 180 derajat
    delay (4000);       
    //durasi disesuaikan 
    servoAne.write(0); 
  }

   //Jika sensor tidak mendeteksi ada orang di dekat tong sampah, maka tetapkan servo di posisi 0 derajat 
   //dan nyalakan led merah serta matikan led hijau.
  else{
    servoAne.write(0);  //posisikan servo di 0 derajat
    delay(5);

  }
}
