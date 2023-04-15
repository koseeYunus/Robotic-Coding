#include <Servo.h>// servo motor kütüphanesi
#include <NewPing.h>


//motor pinleri
#define SolMotorileri 2
#define SolMotorGeri 3
#define SagMotorileri 4
#define SagMotorGeri 5
//sensör pinleri
#define USTrigger 6
#define USEcho 7
#define Maksimum_uzaklik 100

Servo servo; //servo motor tanımlama
NewPing sonar(USTrigger, USEcho, Maksimum_uzaklik);//ultrasonik sensör tanımlama
//kullanılacak eleman tanımı
int uzaklik;
int on_uzaklik;
int sol_uzaklik;
int sag_uzaklik;
int zaman;

// program ilk çalıştığında sadece bir kez çalışacak programlar
void setup(){
//motor çıkışları
pinMode(SolMotorileri, OUTPUT);
pinMode(SolMotorGeri, OUTPUT);
pinMode(SagMotorileri, OUTPUT);
pinMode(SagMotorGeri, OUTPUT);
servo.attach(8); //servo pin tanımı
Serial.begin(9600);
}

// sonsuz döngü
void loop()
{
  //delay(500);
  servo.write(90);
  sensor_olcum();
  on_uzaklik = uzaklik;

  Serial.print("On uzaklik : ");
  Serial.println(on_uzaklik);
  //delay(2000);

  if(on_uzaklik > 20 || on_uzaklik <= 2)
  {
    ileri();
  }
  else
  {
    dur();
    servo.write(180);
    delay(1000);
    sensor_olcum();
    sol_uzaklik = uzaklik;

    Serial.print("sol uzaklik : ");
    Serial.println(sol_uzaklik);
    //delay(2000);

    servo.write(0);
    delay(1000);
    sensor_olcum();
    sag_uzaklik = uzaklik;
    
    Serial.print("sag uzaklik : ");
    Serial.println(sag_uzaklik);
    //delay(2000);

    servo.write(90);
    delay(500);
    if(sag_uzaklik>sol_uzaklik)
    {
      sag();
      delay(200);
      ileri();
    }
    else if(sol_uzaklik >sag_uzaklik)
    {
      sol();
      delay(200);
      ileri();
    }
    else
    {
      geri();
    }
  }
}
  
// robotun yön komutları
void ileri()
{
digitalWrite(SolMotorGeri, LOW);
digitalWrite(SolMotorileri, HIGH);
digitalWrite(SagMotorGeri, LOW);
digitalWrite(SagMotorileri, HIGH);
}
  
void geri()
{
digitalWrite(SolMotorileri, LOW);
digitalWrite(SolMotorGeri, HIGH);
digitalWrite(SagMotorileri, LOW);
digitalWrite(SagMotorGeri, HIGH);
}
  
void sol()
{
digitalWrite(SolMotorileri, LOW);
digitalWrite(SolMotorGeri, HIGH);
digitalWrite(SagMotorGeri, LOW);
digitalWrite(SagMotorileri, HIGH);
  
}
  
void sag()
{
digitalWrite(SolMotorGeri, LOW);
digitalWrite(SolMotorileri, HIGH);
digitalWrite(SagMotorileri, LOW);
digitalWrite(SagMotorGeri, HIGH);
}
  
void dur()
{
digitalWrite(SolMotorGeri, LOW);
digitalWrite(SolMotorileri, LOW);
digitalWrite(SagMotorileri, LOW);
digitalWrite(SagMotorGeri, LOW);
}
// sensörün mesafe ölçümü
void sensor_olcum()
{
  delay(50);
  uzaklik = sonar.ping_cm();
}
