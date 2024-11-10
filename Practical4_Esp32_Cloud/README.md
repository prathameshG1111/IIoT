## Documenting the IIOT practical to send DHT11 Sensor Data to the Cloud (AWS)

## Step 1 : AWS configs

 - Go to [AWS](https://console.aws.amazon.com/),  make sure you're in Mumbai Server
 - Go to IoT Core
 - Manage > All Devices > Things
 - Create Thing
 - Create single Thing
 - Set thing name, select No Shadow >  Next
 - Auto Generate a new Certificate
 - Create a new policy (Opens new Tab)
 - Create policy name, * in policy action and policy resource & click Create
 - Go back to Previous tab
 - Select just created policy and Create Thing
 - Download the Device Certificate, Public Key, Private Key & Root CA 1
 - Go to Side Bar > Connect > Domain Configuration > Copy the Domain name and store it somewhere

##### By the end of this, you should have an AWS IoT Thing Setup, the Keys, certificates and the domain(endpoint) ready.

## Step 2 : Arduino IDE configs

 - Download libraries 
	 - DHT sensor library by Adafruit
	 - DHT sensor library for ESPx by beegee_tokyo
	 - ArduinoJson by Benoit Blanchon
	 - PubSubClient by Nick O'Leary
- SideBar > Boards Manager > Download esp32 by Espressif Systems
- Clone the GitHub Repo: `git clone https://github.com/Nycto-c05/esp32_aws/`
- Make sure the sketch.ino and secrets.h are in the same folder
- Update the secrets.h file with your credentials
	- Set the WIFI_SSID, WIFI_PASSWORD & AWS Endpoint (Domain Config)
	- Update the Amazon Root CA 1 Certificate
	- Update the Device Certificate
	- Update the Private Key
- Connect the ESP32 and all the DHT11 connections as per the Screenshot given
- Select the port & the device
- Plug in (ffs if you didn't do that already, go eat a d)
- Give the port permission : `sudo chmod a+rw /dev/ttyACM0` (or whatever your port name is)
- Upload
- Open Serial Monitor to confirm connection, Select Both NL & CR, and set Baud Rate to 115200 baud
- You should see the Sensor Readings (if you don't, Skill Issue)

## Step 3 :  AWS - Publish Data to Cloud

 - Go back to AWS console
 - Side Bar > Test >  MQTT Test Client
 - Enter Topic Filter > iotfrontier/pub & Click Subscribe
 - Data should be Visible now


 

