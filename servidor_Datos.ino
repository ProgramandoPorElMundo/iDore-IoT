#include "SoftwareSerial.h"

SoftwareSerial puertoGSMS	(2,3);

const byte indicador_IoT_1		= 1;
const byte indicador_IoT_2		= 2;
const byte indicador_IoT_3		= 3;
const int recibido_Datos		= 4;
const int enviado_Datos			= 5;

int count					= 0;
char dato[15];
char captura_Datos_1[15];
char captura_Datos_2[15];

 void setup()
 {
 	Serial.begin(9600);
 	puertoGSMS.begin(9600);


 	while(!Serial){
 	  
 	}
 	pinMode(recibido_Datos, OUTPUT);
 	pinMode(enviado_Datos, 	OUTPUT);

 	conexion_Cliente_1();
    conexion_Cliente_2();
    conexion_Cliente_3();

 	configuracio_Sms();
 }


void loop()
{
    while (puertoGSMS.available())
    {
        if(char indicador_Datos = puertoGSMS.read() == indicador_IoT_1){
            delay(1000);
            dispositivo_1();
            
        }

        if(char indicador_Datos = puertoGSMS.read() == indicador_IoT_2){
            delay(1000);
            dispositivo_2();
        
        }
    }



}

void conexion_Cliente_1(){
    puertoGSMS.print(indicador_IoT_1);
    while(puertoGSMS.available() > 0){
        if(byte indicador = puertoGSMS.read() == indicador_IoT_1){
		    Serial.print("CONEXION ESTABLECIDA CON EL TRANSPORTE \n");
		    delay(1000);
		    while(puertoGSMS.available() > 0){
			    int dato_Temporal = puertoGSMS.read();
			    dato_Temporal = 0;
                Serial.print("LIMPIANDO BUFFER DE COMUNICACION \n");
            }
	    }
	}
}

void conexion_Cliente_2(){
    puertoGSMS.print(indicador_IoT_2);
    while(puertoGSMS.available() > 0){
        if(byte indicador = puertoGSMS.read() == indicador_IoT_2){
		    Serial.print("CONEXION ESTABLECIDA CON LA BAHIA \n");
		    delay(1000);
		    while(puertoGSMS.available() > 0){
			    int dato_Temporal = puertoGSMS.read();
			    dato_Temporal = 0;
                Serial.print("LIMPIANDO BUFFER DE COMUNICACION \n");
            }
	    }
	}
}

void conexion_Cliente_3(){
    puertoGSMS.print(indicador_IoT_3);
    while(puertoGSMS.available() > 0)
    {
        if(byte indicador = puertoGSMS.read() == indicador_IoT_3)
        {
		    Serial.print("CONEXION ESTABLECIDA CON PICK UP DELIVERY \n");
		    delay(1000);
		    while(puertoGSMS.available() > 0){
			    int dato_Temporal = puertoGSMS.read();
			    dato_Temporal = 0;
                Serial.print("LIMPIANDO BUFFER DE COMUNICACION \n");
            }
	    }
	}
}

void configuracio_Sms(){
	puertoGSMS.print("AT+CMGF = 1");
	delay(100);
	puertoGSMS.println("AT+CMGS=\"+5219993335815\"");
	delay(100);
    puertoGSMS.print("\n");
}

void dispositivo_1(){
    for (count = 0; count < 15; count++)
    {
        dato[count] = puertoGSMS.read();
    }    
    Serial.print(indicador_IoT_1);
    delay(1000);
    for (count = 0; count < 15; count++)
    {
        Serial.print(dato[count]);
        delay(100);
    }
    
}

void dispositivo_2(){
    if(char dato = puertoGSMS.read() == 'a')
    {
        delay(1000);
        Serial.print(dato);
    }
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
