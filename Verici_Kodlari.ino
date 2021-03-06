//GY-50 Short Example Sketch
// By Arduino User JohnChi
// August 17, 2014
// Public Domain
#include&lt;Wire.h&gt;
const int GY_addr=0x68; // I2C address of the GY-50
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

#include &lt;SPI.h&gt;
#include &lt;nRF24L01.h&gt; //nrf
#include &lt;RF24.h&gt; //nrf

//Pinler tanımlanıyor...
#define CE_PIN 9 //nrf
#define CSN_PIN 10 //nrf
//Değişkenler yazılıyor.
const uint64_t pipe = 0xE8E8F0F0E1LL; //nrf
RF24 radio(CE_PIN, CSN_PIN); //nrf
int gyro[3];

void setup(){


Wire.begin();

16

Wire.beginTransmission(GY_addr);

Wire.write(0x6B); // PWR_MGMT_1 register
Wire.write(0); // set to zero (wakes up the GY-50)
Wire.endTransmission(true);
Serial.begin(9600);

radio.begin(); //nrf
radio.openWritingPipe(pipe); //nrf

}
void loop(){
Wire.beginTransmission(GY_addr);
Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
Wire.endTransmission(false);
Wire.requestFrom(GY_addr,14,true); // request a total of 14 registers
AcX=Wire.read()&lt;&lt;8|Wire.read(); // 0x3B (ACCEL_XOUT_H) &amp; 0x3C
(ACCEL_XOUT_L)
AcY=Wire.read()&lt;&lt;8|Wire.read(); // 0x3D (ACCEL_YOUT_H) &amp; 0x3E
(ACCEL_YOUT_L)
AcZ=Wire.read()&lt;&lt;8|Wire.read(); // 0x3F (ACCEL_ZOUT_H) &amp; 0x40
(ACCEL_ZOUT_L)
Tmp=Wire.read()&lt;&lt;8|Wire.read(); // 0x41 (TEMP_OUT_H) &amp; 0x42 (TEMP_OUT_L)
GyX=Wire.read()&lt;&lt;8|Wire.read(); // 0x43 (GYRO_XOUT_H) &amp; 0x44 (GYRO_XOUT_L)
GyY=Wire.read()&lt;&lt;8|Wire.read(); // 0x45 (GYRO_YOUT_H) &amp; 0x46 (GYRO_YOUT_L)
GyZ=Wire.read()&lt;&lt;8|Wire.read(); // 0x47 (GYRO_ZOUT_H) &amp; 0x48 (GYRO_ZOUT_L)
Serial.print(&quot;AcX = &quot;); Serial.print(AcX);
Serial.print(&quot; | AcY = &quot;); Serial.print(AcY);
Serial.print(&quot; | AcZ = &quot;); Serial.print(AcZ);
Serial.print(&quot; | Tmp = &quot;); Serial.print(Tmp/340.00+36.53); //equation for temperature in
degrees C from datasheet
Serial.print(&quot; | GyX = &quot;); Serial.print(GyX);
Serial.print(&quot; | GyY = &quot;); Serial.print(GyY);
Serial.print(&quot; | GyZ = &quot;); Serial.println(GyZ);
delay(333);

17

gyro[0] = analogRead(GyX);
gyro[1] = analogRead(GyY);
gyro[2] = analogRead(GyZ);
radio.write( gyro, sizeof(gyro) );
