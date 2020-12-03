#include "SoftwareSerial.h"

SoftwareSerial puertoGSMS	(2,3);

const byte indicador_IoT		= 2;
const int sensor_Bahia          = 3;
const int recibido_Datos		= 4;
const int enviado_Datos			= 5;

bool estado_Bahia               = false;

int count					    = 0;

void setup()
{
    Serial.begin(9600);
    puertoGSMS.begin(9600);


    while(!Serial)
    {

    }

	pinMode(recibido_Datos, OUTPUT);
	pinMode(enviado_Datos, 	OUTPUT);
	pinMode(sensor_Bahia, 	INPUT);

    conexion_Servidor();
	configuracio_Sms();
}

void loop()
{
    bahia();
    if(estado_Bahia == true){
        for (count = 0; count == 1; count++);
        {
            Serial.print("AUTOMOVIL DETECTADO \n");
            delay(1000);
            puertoGSMS.print(indicador_IoT);
            delay(1000);
            puertoGSMS.print('a');
            delay(1000);
            while (estado_Bahia == true)
            {
                bahia();
                Serial.print("LIMPIANDO BUFFER DE COMUNICACION\n");
            }
            
        }
    }
    Serial.print("BAHIA LIBRE\n");
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

void bahia(){
    int sensor_Estado = digitalRead(sensor_Bahia);
}