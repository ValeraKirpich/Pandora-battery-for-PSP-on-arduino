#define SerialParity 1

#include <Arduino.h>
#include "keys.h"
#include <string.h>
#include <AES.h>
//#include "XTEA-Cipher.h"

#if SerialParity
#include <SoftwareSerialParity.h>
#else
#include <SoftwareSerial.h>
#endif

#define debugSerial Serial

#if SerialParity
SoftwareSerialParity pspSerial(2, 3); // RX, TX
#else
SoftwareSerial pspSerial(2, 3); // RX, TX
#endif

//AES aes;

#define pin_butOk 7
#define pin_debugLed 8 // new 11

byte serial_code[8] = {0};
byte msg[24] = {0};
//byte *msg;
int msgLength;
byte version;
byte pspdata[4] = {0};
byte challenge1a[16] = {0};
byte challenge1b[16] = {0};
byte tempBuffer[24] = {0};

void debugLed(const uint8_t count, const uint8_t speed)
{
  for (int i=0; i<count; i++)
  {
    digitalWrite(pin_debugLed, 0);
    delay(speed);
    digitalWrite(pin_debugLed, 1);
    delay(speed);
  }
}

void setup()
{
#if SerialParity
  pspSerial.begin(19200, EVEN);
#else
  pspSerial.begin(19200);       // SERIAL_8E1
#endif

  //xtea.begin(XTEA_ROUNDS, XTEA_MAC_ROUNDS); //?

  debugSerial.begin(115200);

  pinMode(pin_butOk, INPUT);
  pinMode(pin_debugLed, OUTPUT);

  digitalWrite(pin_debugLed, HIGH);

  if (digitalRead(pin_butOk))
  {
    serial_code[0] = 0xA5;
    serial_code[1] = 0x06;
    serial_code[2] = 0x06;
    serial_code[3] = 0xFF;
    serial_code[4] = 0xFF;
    serial_code[5] = 0xFF;
    serial_code[6] = 0xFF;
    serial_code[7] = 0x52;

    debugLed(3, 250);
    debugSerial.println("Start service");
  }
  else
  {
    // 34 12 78 56
    serial_code[0] = 0xA5;
    serial_code[1] = 0x06;
    serial_code[2] = 0x06;
    serial_code[3] = 0x56;
    serial_code[4] = 0x00;
    serial_code[5] = 0x00;
    serial_code[6] = 0x00;
    serial_code[7] = 0x4E;

    debugLed(1, 1000);
    debugSerial.println("Start normal");
  }
}

void log_byte(byte b)
{
  if (b < 0x10)
    debugSerial.print("0");

  debugSerial.print(b, HEX);
  debugSerial.print(" ");

  //debugSerial.printf("%#02X ", b);
}

void psp_write(byte *b, int len)
{
#if SerialParity
  pspSerial.write(b, len);
#else
  for (size_t i = 0; i < len; i++)
    pspSerial.write(b[i]);
#endif

  // log
  debugSerial.print("Arduino: ");
  for (size_t i = 0; i < len; i++)
    log_byte(b[i]);
  debugSerial.println();
}

unsigned char GeneratePacketChecksum(byte *inputArray, int len) 
{
  int sum = 0;

  for (int i = 0; i < len; i++)
    sum += inputArray[i];

  return ((sum & 0xFF) ^ 0xFF);
}

void MixChallenge1(byte *data, byte version, byte *challenge)
{
  byte secret1[8] = {0};
  get_challenge1_secret(secret1, version);

  data[0] = secret1[0];
  data[4] = secret1[1];
  data[8] = secret1[2];
  data[0xC] = secret1[3];
  data[1] = secret1[4];
  data[5] = secret1[5];
  data[9] = secret1[6];
  data[0xD] = secret1[7];
  data[2] = challenge[0];
  data[6] = challenge[1];
  data[0xA] = challenge[2];
  data[0xE] = challenge[3];
  data[3] = challenge[4];
  data[7] = challenge[5];
  data[0xB] = challenge[6];
  data[0xF] = challenge[7];
}

void MixChallenge2(byte *data, byte version, byte *challenge)
{
  byte secret2[8] = {0}; 
  get_challenge2_secret(secret2, version);

  data[0] = challenge[0];
  data[4] = challenge[1];
  data[8] = challenge[2];
  data[0xC] = challenge[3];
  data[1] = challenge[4];
  data[5] = challenge[5];
  data[9] = challenge[6];
  data[0xD] = challenge[7];
  data[2] = secret2[0];
  data[6] = secret2[1];
  data[0xA] = secret2[2];
  data[0xE] = secret2[3];
  data[3] = secret2[4];
  data[7] = secret2[5];
  data[0xB] = secret2[6];
  data[0xF] = secret2[7];
}

/*
void MatrixSwap(byte *data, byte *key, uint8_t keyLen)
{
  byte newmap[16] = {0};

  memcpy_P(newmap, newmap, 16);

  for (int i = 0; i < keyLen; i++)
    data[i] = key[newmap[i]];
}
*/

void MatrixSwap(byte* data, int length)
{
  byte temp[length] = {0};
  //byte newMap[length] = {8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7};
  byte newMap[length] = {0x00, 0x04, 0x08, 0x0C, 0x01, 0x05, 0x09, 0x0D, 0x02, 0x06, 0x0A, 0x0E, 0x03, 0x07, 0x0B, 0x0F};

  for (int i = 0; i < length; i++)
  {
    temp[i] = data[newMap[i]];
  }

  memcpy(data, temp, length);
}

/*
void ECBEncryptBytes(byte *encryptedBytes, byte *Bytes, byte *key)
{
  aes.set_key(key, 128);    
  aes.encrypt(Bytes, encryptedBytes);
}
*/

void generateSysconResponses()
{
  version = msg[0];

  byte tempKey[16] = {0};
  get_keystore(tempKey, version);

  tempBuffer[0] = 0xA5;
  tempBuffer[1] = 0x12;
  tempBuffer[2] = 0x06;

  if (tempKey[0] == 0)
  {
    debugSerial.println("Key not found");

    for (int i = 3; i < 19; i++)
      tempBuffer[i] = 0xFF;

    return;
  }

  byte req[msgLength - 1] = {0};

  for (int i = 1; i < msgLength; i++)
    req[i-1] = msg[i];

  byte data[16];
  MixChallenge1(data, version, req);
  MatrixSwap(data, 16);

/*
  memcpy(challenge1a, data, 16);
  xtea.ecbEncrypt(tempKey, challenge1a, 16);
*/

  AES aesEncryptor1;
  aesEncryptor1.set_key(tempKey, 16);
  aesEncryptor1.encrypt(data, challenge1a);

  byte second[16];
  memcpy(second, challenge1a, 16);

/*
  memcpy(challenge1b, second, 16);
  xtea.ecbEncrypt(tempKey, challenge1b, 16);
*/

  AES aesEncryptor2;
  aesEncryptor2.set_key(tempKey, 16);
  aesEncryptor2.encrypt(second, challenge1b);

  MatrixSwap(challenge1b, 16);

  memcpy(tempBuffer + 3, challenge1a, 8);
  memcpy(tempBuffer + 3 + 8, challenge1b, 8);
}

void loop()
{
  if (pspSerial.available() > 3)
  {
    pspdata[0] = pspSerial.read();

    debugSerial.print("PSP:     ");
    log_byte(pspdata[0]);

    if (pspdata[0] == 0x5A)
    {
      pspdata[1] = pspSerial.read(); // packet length
      pspdata[2] = pspSerial.read(); // operation code

      log_byte(pspdata[1]);
      log_byte(pspdata[2]);

      if (pspdata[1] == 0x02) // if packet has no message then byte after the opcode is the checksum
        msgLength = 0;
      else // packet contains a message
      {
        msgLength = ((int)pspdata[1] - 2); 

        while (pspSerial.available() < (int)pspdata[1] - 1)
        {
          delayMicroseconds(10);
        }; // wait until bytestoread has remaining msg and csum (opcode is already read so -1)

        //msg = malloc(msgLength);

        for (int i = 0; i < msgLength; i++)
          msg[i] = pspSerial.read();

        debugSerial.print("( ");
        for (int i = 0; i < msgLength; i++)
          log_byte(msg[i]);
        debugSerial.print(") ");
      }

      pspdata[3] = pspSerial.read();

      log_byte(pspdata[3]);
      debugSerial.println();

      switch (pspdata[2])
      {

      case 0x01:
      {
        memcpy_P(tempBuffer, answer_01, 7);
        psp_write(tempBuffer, 7);
      }
      break;

      case 0x0C:
      {
        byte tempcs[1] = {0};

        for (int i = 0; i < 7; i++)
          tempBuffer[i] = serial_code[i];

        tempcs[0] = GeneratePacketChecksum(tempBuffer, 7);

        psp_write(tempBuffer, 7);
        psp_write(tempcs, 1);
      }
      break;

      case 0x80:
      {
        byte tempCS[1] = {0};

        generateSysconResponses();

        tempCS[0] = GeneratePacketChecksum(tempBuffer, 19);

        psp_write(tempBuffer, 19);
        psp_write(tempCS, 1);
      }
      break;

      case 0x81:
      {
        tempBuffer[0] = 0xA5;
        tempBuffer[1] = 0x12;
        tempBuffer[2] = 0x06;

        byte data2[16] = {0};
        MixChallenge2(data2, version, challenge1b);
        MatrixSwap(data2, 16);

        byte tempKey[16] = {0};
        get_keystore(tempKey, version);

        AES encrypted;
        byte challenge2[16] = {0};
        byte response2[16] = {0};

        encrypted.set_key(tempKey, 128);
        encrypted.encrypt(data2, challenge2);
        encrypted.encrypt(challenge2, response2);

        memcpy(tempBuffer + 3, response2, 16);

        byte tempCS[1] = {0};
        tempCS[0] = GeneratePacketChecksum(tempBuffer, 19);

        psp_write(tempBuffer, 19);
        psp_write(tempCS, 1);
      }
      break;

      case 0x03:
      {
        memcpy_P(tempBuffer, answer_03, 6);
        psp_write(tempBuffer, 6);
      }
      break;

      case 0x07:
      {
        memcpy_P(tempBuffer, answer_07, 6);
        psp_write(tempBuffer, 6);
      }
      break;

      case 0x0B:
      {
        memcpy_P(tempBuffer, answer_0B, 6);
        psp_write(tempBuffer, 6);
      }
      break;

      case 0x09:
      {
        memcpy_P(tempBuffer, answer_09, 6);
        psp_write(tempBuffer, 6);
      }
      break;

      case 0x02:
      {
        memcpy_P(tempBuffer, answer_02, 5);
        psp_write(tempBuffer, 5);
      }
      break;

      case 0x04:
      {
        memcpy_P(tempBuffer, answer_04, 6);
        psp_write(tempBuffer, 6);
      }
      break;

      case 0x16:
      {
        memcpy_P(tempBuffer, answer_16, 21);
        psp_write(tempBuffer, 21);
      }
      break;

      case 0x0D:
      { 
        memcpy_P(tempBuffer, answer_0D, 9);
        psp_write(tempBuffer, 9);
      }
      break;

      case 0x08:
      {
        memcpy_P(tempBuffer, answer_08, 6);
        psp_write(tempBuffer, 6);
      }
      break;

      default:
      {
        debugSerial.print("No option selected ");
        log_byte(pspdata[2]);
        debugSerial.println();
      }
      }
    }
    else
      debugSerial.println();
  }

  for (int i = 3; i < 19; i++)
      tempBuffer[i] = 0x00;

  //free(msg);
}
