
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

int outPin = 2;

byte uid[] = {89,151,19,188};
bool lock = false;
int count = 0;

int timer = 11;

MFRC522 rfid(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
	Serial.begin(9600);		// Initialize serial communications with the PC
	SPI.begin();			// Init SPI bus
	rfid.PCD_Init();		// Init MFRC522
	rfid.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
  pinMode(outPin, OUTPUT);
}

void loop() {
  
	// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if (rfid.PICC_IsNewCardPresent() and rfid.PICC_ReadCardSerial()) {
      
      for(int i = 0; i < rfid.uid.size; i++){
      
        if(rfid.uid.uidByte[i] == uid[i]){
          //Serial.print(rfid.uid.uidByte[i]);
          //Serial.print(rfid.uid.uidByte[i]);
          //Serial.print(",");
          count++;
        }
      }
      
      if(count == 4){
        //Serial.print("count = 4");
        door();
      }


      count = 0;
	  }

    if(timer == 0){
      timer = 11;
      digitalWrite(RST_PIN, HIGH);
      delay(1);
      digitalWrite(RST_PIN, LOW);
      rfid.PCD_Init();
    }
    
    timer--;
}


void door(){
  digitalWrite(outPin, HIGH);
  delay(750);
  digitalWrite(outPin, LOW);
  delay(2500);
}
