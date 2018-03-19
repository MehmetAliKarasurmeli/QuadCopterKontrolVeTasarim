// Kütüphaneler projeye dahil ediliyor.
#include &lt;SPI.h&gt;
#include &lt;nRF24L01.h&gt; //nrf
#include &lt;RF24.h&gt; //nrf

//Pinler tanımlanıyor...
#define CE_PIN 10 //nrf
#define CSN_PIN 9 //nrf

//Değişkenler yazılıyor.
const uint64_t pipe = 0xE8E8F0F0E1LL; //nrf
RF24 radio(CE_PIN, CSN_PIN); //nrf

int gyro[3]; //3 elemanlı joystick değişkenimizi tanımladık. Bu elemanlardan ilki Y ekseni,
ikincisi X ekseni, 3.sü de joystick&#39;in orta butonu.

void setup()
{

Serial.begin(9600);
radio.begin(); //nrf
radio.openReadingPipe(1,pipe); //nrf
radio.startListening();; //nrf

19

}

void loop() {
if ( radio.available() ) //Eğer sinyal algılarsan... //nrf
{
radio.read( gyro, sizeof(gyro) ); //Bu sinyallerden gelen verileri 3 elemanlı joystick
değişkenine sırasıyla yaz. //nrf



Serial.print (&quot;gyrox=&quot;);
Serial.println (gyro[0]);
delay(500);
Serial.print (&quot;gyroy=&quot;);
Serial.println (gyro[1]);
Serial.print (&quot; gyroz=&quot;);
Serial.println (gyro[2]);

}

}
