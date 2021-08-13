//Libraries Untuk Jaringan WIFI
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

//Library Load Cell
#include "HX711.h"
//Library Servo
#include <Servo.h>

//Seting Jaringan.
const char* ssid = "Kim";
const char* password = "123456789";
const char* host = "192.168.43.162"; //Alamat IP server

// Pin Led Conection
#define PIN_LED 12
//Pin Servo
#define pin_servo 16
//Pin Load Cell
const int LOADCELL_DOUT_PIN = 5;
const int LOADCELL_SCK_PIN = 4;  

Servo myservo;
HX711 scale;


void setup() {
  Serial.begin(9600);
  
  Serial.println("Pastikan Tidak Ada Beban");
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(440.0);                           // angka untuk kalibrasi
  scale.tare(50);                                    // angka untuk reset ke nol
  Serial.println("Silahkan Untuk Menimbang");
  
  pinMode(PIN_LED, OUTPUT);

  myservo.attach(pin_servo);

  //Set Nilai Posisi 0 derajat
  myservo.write(0);

  //Setting koneksi Wifi 
  WiFi.hostname("NodeMCU");
  
  //Mulai Start Koneksi Wifi dengan memasukan sssid dan password
  WiFi.begin(ssid, password);
  Serial.println("Connecting .....");
  
  //Cek Koneksi Wifi, Selama wifi status konek wifinya tidak terkoneksi  
  while(WiFi.status() != WL_CONNECTED)
  {
  //led Mati
  digitalWrite(PIN_LED,LOW);
  //NodeMcu terus mencoba koneksi 
  Serial.print(".");
  delay(500);
  }
  //Apabila berhasil terkoneksi
  digitalWrite(PIN_LED, HIGH);
  
  //Tampilkan pesan di serial Wifi connected
  Serial.println("Wifi Connected");
  
}

void loop() {
  Serial.print("Berat");
  float berat= scale.get_units(25);                 // pengambilan data beban 25 kali
  if(berat<=0.1)                                    // angka minimal untuk ke angka nol
  {
    berat=0.0;
  }
  Serial.println(berat,1);
  if(berat<1000)                                    // jika berat kurang dari 1000 maka hasil dengan satuan gram
  {
  Serial.println("SILAHKAN TIMBANG");
  Serial.println("Berat= ");
  Serial.print(berat,1);
  Serial.println(" g");
  }
  if(berat>=1000)                                   // jika berat lebih dari 1000 maka hasil dengan satuan kg
  {
  Serial.println("SILAHKAN TIMBANG");
  float hasil=berat/1000;
  Serial.println("Berat= ");
  Serial.print(hasil);
  Serial.println(" kg");
  }
  scale.power_down();
  delay(2000);                                      // angka untuk delay dalam pengambilan data berat
  scale.power_up();

  //process cek Koneksi ke server 
    WiFiClient client;
    //Jika Clinet tidak terkoneksi konek ke host
    if(!client.connect(host, 80))
    {
      Serial.println("Connect Failed");
      //Jika Gagal Ulang kembali dari awal 
      return;
      }
      
      //Prosess Pengiriman data ke server 
      String Link;
      HTTPClient http;
      
      //saat mengeksekusi kirimdata.php maka dia mengirim nilai sensornya ke variabel sensornya
      Link = "http://" + String(host) + "/IoT-infus/arduino/write.php?berat=" + String(berat);
      
      //Eksekusi Link
      http.begin(Link);
      
      //Mode Get
      http.GET();
      
      //Baca respon setelah berhasil kirim nilai sensor
      String respon = http.getString();
      Serial.println(respon);
      
      //Jika program telah selesai maka ditutup
      http.end();

      String LinkServo;
      HTTPClient httpServo;
      //saat mengeksekusi kirimdata.php maka dia mengirim nilai sensornya ke variabel sensornya
      LinkServo = "http://" + String(host) + "/IoT-infus/arduino/writeservo.php";
      //Eksekusi Link
      httpServo.begin(LinkServo);
      //Mode Get
      httpServo.GET();
      //Baca respon setelah berhasil kirim nilai sensor
      String responServo = httpServo.getString();
      Serial.println(responServo);
      //Jika program telah selesai maka ditutup
      httpServo.end();
      myservo.write(responServo.toInt());
  
}
