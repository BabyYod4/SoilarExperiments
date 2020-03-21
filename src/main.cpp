#include "libsoilar/drivers/rfm95w/rfm95w.h"            
#include INIT_ENVOIRMENT

// Uno Receiver
/*
  DIO0 - D2
  RESET - D8
  NSS - D9
  SCK - D13
  MOSI - D11
  MISO - D12
*/

// Due Receiver
/*
  DIO0 - D22
  RESET - D12
  NSS - D13
  SCK - D74
  MOSI - D75
  MISO - D74
*/



LoraEndnode receiver;

LoraEndnodeSettings settings = { 
  .frequencyMHz = RFM95W_CALC_FEQ_FAST( ((long)(867E6) - 125000) ),  
  .signalBandwidthHz = RFM95W_BW_250KHZ,
  .preambleLength = RFM95W_DEFAULT_PREAMBLE_LENGTH,
  .txPowerdBm = RFM95W_DEFAULT_TX_POWER,
  .spreadingFactor = 10,
  .codeRate = RFM95W_CODE_RATE_4_6,
  .syncWord = 0x12,
  .enableCRC = true,
  .lowPowerReceiveMode = true,
  .invertIQ = false
};

Rfm95wInterface interface = { 0, 9, 8, 2 };

uint8_t buff[11] = {0};

ISR_CODE void received(void);

void received(void){

  // received a packet
  print("Received packet '");
  if ( receiver.read(buff, 11) == LORA_PKG_CORRUPTED ){
    Serial.println("Corrupted");
  } else{
    Serial.print("Received packet '");
    Serial.print(buff[4]); 
    Serial.print("-");
    Serial.print(buff[5]); 
    Serial.print("-"); 
    Serial.print(buff[6]); 
    Serial.print("-"); 
    Serial.print(buff[7]); 
    Serial.print("-");
    Serial.print(buff[8]); 
    Serial.print("'\r\n");   
  }
  
}

void setup(){

  Serial.begin(9600);
  Serial.println("LoRa Receiver");

  if ( CreateRfm95W(&receiver, &interface, &settings) == LORA_ERROR_WRONG_DEVICE ) {
    Serial.println("Starting LoRa failed!");
    while(1);
  }

  receiver.setOnReceiveCallback( received );

}

void loop(){}