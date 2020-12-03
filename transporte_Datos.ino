#include "SoftwareSerial.h"

SoftwareSerial puertoGPS 	(2,3);
SoftwareSerial puertoGSMS	(4,5);

const byte indicador_IoT		= 1;
const int recibido_Datos		= 4;
const int enviado_Datos			= 5;
const int sensor_Puerta			= 6;
const double Cuadrante_00		= 18.6290844;
const double Cuadrante_01		= 18.6580888;
const double Cuadrante_10		= -91.8255665;
const double Cuadrante_11		= -91.8245579;

int count					= 0;
bool estado_Ubicacion		= false; 
char captura_Datos_1[15];
char captura_Datos_2[15];

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
		
		while(puertoGPS.available() > 0 )
		{
			puertoGSMS.print(indicador_IoT);
			puertoGSMS.print("\nUBICACION\n");
			puertoGSMS.print("LATITUD: \t");
			
			for (count = 0; count < 60; count++ )
			{
				if(count >= 20 && count <35){
					captura_Datos_1[count] = puertoGPS.read();
					puertoGSMS.print(captura_Datos_1);
				}
				if (count >= 35 && count < 60){
					captura_Datos_2[count] = puertoGPS.read();
					puertoGSMS.print(captura_Datos_2);
				}
			}
		}
		led_IndicadoresRecibido();
		led_IndicadoresEnvio();
		estado_Ubicacion = false;
	}
}

void conexion_Servidor(){
	while(puertoGSMS.available() == 0){
		Serial.print("ESPERANDO CONEXION CON EL SERVIDOR\n");
		delay(1000);
	}
	if(byte indicador = puertoGSMS.read() == indicador_IoT){
		delay(1000);
		Serial.print("CONEXION ESTABLECIDA CON EL SERVIDOR\n");
		puertoGSMS.print(indicador_IoT);
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
