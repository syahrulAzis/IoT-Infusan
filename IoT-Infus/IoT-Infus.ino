#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

//Library Servo
#include <Servo.h>

//Seting Jaringan.
const char* ssid = "hayo";
const char* password = "KARANGHAUR";
const char* host = "192.168.240.232"; //Alamat IP server

#define PIN_LED 16
#define pin_servo 5

Servo myservo;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
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

  myservo.attach(pin_servo);

  //Set Nilai Posisi 0 derajat
  myservo.write(0);
}

void loop() {
  WiFiClient client;
    //Jika Clinet tidak terkoneksi konek ke host
    if(!client.connect(host,80))
    {
      Serial.println("Connect Failed To Server");
      //Jika Gagal Ulang kembali dari awal 
      return;
      }
      String Link;
      HTTPClient http;
      
      //saat mengeksekusi kirimdata.php maka dia mengirim nilai sensornya ke variabel sensornya
      Link = "http://" + String(host) + "/IoT-infus/arduino/writeservo.php";
      
      //Eksekusi Link
      http.begin(Link);
      
      //Mode Get
      http.GET();
      
      //Baca respon setelah berhasil kirim nilai sensor
      String respon = http.getString();
      Serial.println(respon);
      
      //Jika program telah selesai maka ditutup
      http.end();

      myservo.write(respon.toInt());
}
