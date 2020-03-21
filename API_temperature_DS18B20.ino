
/*
 ESP8266 Wemos - Relevé température via DS18B20 et envoi Domoticz via API
 Création Dominique PAUL.
 Dépot Github : https://github.com/DomoticDIY/API-ModuleTemp_DS18B20
 Chaine YouTube du Tuto Vidéo : https://www.youtube.com/c/DomoticDIY
  
 Bibliothéques nécessaires :
 Dans IDE ARDUINO : Faire Croquis / inclure une bibliothéque / Gérer les bibliothèques, et ajouter :
  - OnWire
  - DallasTemperature
  - ESP8266Wifi.
 Installer le gestionnaire de carte ESP8266 version 2.5.0 
 Si besoin : URL à ajouter pour le Bord manager : http://arduino.esp8266.com/stable/package_esp8266com_index.json
 
 Pour prise en compte du matériel :
 Installer si besoin le Driver USB CH340G : https://wiki.wemos.cc/downloads
 dans Outils -> Type de carte : generic ESP8266 module
  Flash mode 'QIO' (régle générale, suivant votre ESP, si cela ne fonctionne pas, tester un autre mode.
  Flash size : 1M (no SPIFFS)
  Port : Le port COM de votre ESP vu par windows dans le gestionnaire de périphériques.
*/

// Inclure les librairies.
#include <ESP8266WiFi.h>
#include <OneWire.h>                                  //Librairie du bus OneWire
#include <DallasTemperature.h>                        //Librairie du capteur


// Déclaration des constantes, données à adapter à votre réseau.
// ------------------------------------------------------------
const char* ssid = "_MON_SSID_";                  // SSID du réseau Wifi
const char* password = "_MOT_DE_PASSE_WIFI_";     // Mot de passe du réseau Wifi.
const char* ipDomoticz = "192.168.1.26";           // Adresse IP ou DNS du serveur Domoticz.
const int portDomoticz = 8080;                    // Port de connexion à Domoticz.
// ------------------------------------------------------------
// Variables de configuration :
#define ONE_WIRE_BUS 2                            // Pin de connexion de la DS18B20
float valTemp = 0.0;                              // Variables contenant la valeur de température.
#define tempsPause 30                             // Nbre de secondes de pause (3600 = 1H00)
// ------------------------------------------------------------
// Variables et constantes utilisateur :
int idxDevice = 31;                               // Index du Device à actionner.
// ------------------------------------------------------------

OneWire oneWire(ONE_WIRE_BUS);              // Initialisation du Bus One Wire
DallasTemperature sensors(&oneWire);        // Utilistion du bus Onewire pour les capteurs
WiFiClient client;

// SETUP
// *****
void setup() {
  Serial.begin(115200);                       // On initialise la vitesse de transmission de la console.
  sensors.begin();                            // On initialise la bibliothèque Dallas
  setup_wifi();                               // Connexion au Wifi
}

// BOUCLE DE TRAVAIL
// *****************
void loop() {
    // On interroge la sonde de Température.
    getTemperatureC();
    // Envoi de la données via API Domoticz
    SendData(); 
    // On met le système en pause pour un temps défini
    delay(tempsPause * 1000);
}


// CONNEXION WIFI
// **************
void setup_wifi() {
  // Connexion au réseau Wifi
  delay(10);
  Serial.println();
  Serial.print("Connexion au réseau : ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    // Tant que l'on est pas connecté, on boucle.
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connecté");
  Serial.print("Addresse IP : ");
  Serial.println(WiFi.localIP());
}

// RELEVE DE TEMPERATURE.
// *********************
void getTemperatureC() {
  // On relévé la température.
  // ------------------------
  sensors.requestTemperatures();            // On demande au capteur de lire la température
  valTemp = sensors.getTempCByIndex(0);      // On stocke la température relevé dans une variable temporaire
  Serial.print("Valeur de température relevée : ");
  Serial.println(valTemp);
}

// ENVOI DES DATAS.
// ***************
void SendData () {
  // Création du lien qui sera envoyé à l'API.
  String messageOut = "/json.htm?type=command&param=udevice&idx=" + String(idxDevice) + "&nvalue=0&svalue=" + String(valTemp);
  Serial.print("Message à envoyer : ");
  Serial.println(messageOut);
  
  // Envoi de la requete à Domoticz.
  if (client.connect(ipDomoticz, portDomoticz)) {    // On se connecte au serveur Domoticz
    client.println(String("GET ") + messageOut + " HTTP/1.1");
    client.println("Connection: close");             // On ferme la connexion.
    client.println();
  } 

  // Pause de 5 secondes
  delay(5000);
  Serial.println("Message envoyé à Domoticz");
}

