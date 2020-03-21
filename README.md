# API-ModuleTemp_DS18B20
Capteur de température autonome. Transfert des données à Domoticz, via les API Domoticz

But : Utilisation des API Domoticz. Remonter les informations de température depuis un capteur autonome, et transfèrer l'information à Domoticz via les API intégrées.

Voici comment créer un capteur de tempèrature, à l'aide d'un module DS18B20, support d'un ESP8266, et envoyant les informations à Domoticz via ses API. L'intéret est de récupérer les informations de température, et les transmettre à Domoticz. 

# Explications et Tuto vidéo
Dans la suite des créations d'objets connectés, nous allons voir dans cette vidéo, comment créer un détecteur de température autonome. L’objet connecté fonctionne via les API Domoticz, et lui transmet les informations.

## Utilitaires à installer
Driver USB CH340G : https://wiki.wemos.cc/downloads
Logiciel Arduino IDE : https://www.arduino.cc/en/Main/Software
URL à ajouter pour le Bord manager : http://arduino.esp8266.com/stable/package_esp8266com_index.json
Installer la prise en charge des cartes ESP8266

## Bibliothéques à installer
Faire Croquis / Gérer les bibliothéques, puis rechercher et installer :
- Onewire
- DallasTemperature

## Tuto vidéo
Vidéo explicative sur YouTube : https://youtu.be/Tx1G_40WfQs
