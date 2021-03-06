// Note (13/06/2017): Updated Manchester library from github repository fails 
// when transmit data values above 767 (0x02FF), the receiver can't get the 
// packages. To avoid that, use the Manchester sources provided in this example.

#include "Manchester.h"
#include "src/AVR_Crypto_Lib_aes/aes.h"

#define MY_ID 0x1B // Decimal value: 175 - One Byte, range (0-255) | (0x00-0xFF)
#define CMD 0xFF   // Decimal value: 255 - One Byte, range (0-255) | (0x00-0xFF)
#define P_TX 9     // Transmission digital pin
#define AES_KEY_SIZE 32
#define AES_BLOCK_SIZE 16

const uint8_t key[AES_KEY_SIZE] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};

uint8_t toEncodeData[AES_BLOCK_SIZE];
aes256_ctx_t key_context;

void setup()
{
    Serial.begin(9600);
    aes256_init(key, &key_context);
    man.setupTransmit(P_TX, MAN_1200);
}

void loop()
{
    toEncodeData[0] = MY_ID;
    toEncodeData[1] = CMD;
    
    Serial.print("\nPackage to send:\n");
    Serial.print("ID: 0x");
    Serial.print(toEncodeData[0], HEX);
    Serial.print("     CMD: 0x");
    Serial.print(toEncodeData[1], HEX);
    Serial.print("\n");

    aes256_enc(toEncodeData, &key_context);
    man.transmitArray(AES_BLOCK_SIZE, toEncodeData);
    
    Serial.print("Package sent\n");
    Serial.print("\n");
    
    delay(1000);
}
