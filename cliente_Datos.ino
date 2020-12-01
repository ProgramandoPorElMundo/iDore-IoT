//#include <time.h>
#include <SoftwareSerial.h>
//#include <pgmspace.h>
#include <TinyGPS.h>


SoftwareSerial puertoGPS 	(2,3);
SoftwareSerial puertoGSMS	(4,5);

char captura_Datos[65];

int recibido_Datos			= 4;
int enviado_Datos			= 5;
int count					= 0;
int sensor_Puerta			= 6;
bool estado_Ubicacion		= false; 

 void setup()
 {
 	Serial.begin(9600);
 	puertoGPS.begin(9600);
 	puertoGSMS.begin(9600);


 	while(!Serial){
 	  
 	}
 	pinMode(recibido_Datos, OUTPUT);
 	pinMode(enviado_Datos, 	OUTPUT);
 	pinMode(sensor_Puerta, 	OUTPUT);

 	conexion_Servidor();
 	configuracio_Sms();
 }


void loop()
{
	estado_Sensor();
	if (estado_Ubicacion == true){

		while(puertoGPS.available() > 0 ){
			for (count = 0; count < 65; count++)
			{
				captura_Datos[count] = puertoGPS.read();
				led_IndicadoresRecibido();

			}
			for (count = 18; count < 26; count++)
			{
				Serial.print("UBICACION GPS \n");
				Serial.print("LATITUD: \t");
				Serial.print(captura_Datos[count]);
				led_IndicadoresEnvio();
			}
			for (count = 27; count <45; count++)
			{
				Serial.print("\nLONGITUD: \t");
				Serial.print(captura_Datos[count]);
				Serial.print("\n");
			}
		}
		estado_Ubicacion = false;
	}
}

void conexion_Servidor(){
	while(Serial.available() == 0){
		Serial.print("ESPERANDO CONEXION CON EL SERVIDOR\n");
		delay(1000);
	}
	if(Serial.available() > 0){
		Serial.print("CONEXION ESTABLECIDA CON EL SERVIDOR\n");
		delay(1000);
		while(Serial.available() > 0){
			int dato_Temporal = Serial.read();
			dato_Temporal = 0;
		}
	}
}

void configuracio_Sms(){
	puertoGSMS.print("AT+CMGF = 1");
	delay(100);
	puertoGSMS.println("AT+CMGS=\"+5219381163812\"");
	delay(100);
}

void estado_Sensor(){
	estado_Ubicacion = digitalRead(sensor_Puerta);
}

void led_IndicadoresEnvio(){
	digitalWrite(enviado_Datos, HIGH);
	delay(200);
	digitalWrite(enviado_Datos, LOW);
}

void led_IndicadoresRecibido(){
	digitalWrite(recibido_Datos, HIGH);
	delay(200);
	digitalWrite(recibido_Datos, LOW);
}
