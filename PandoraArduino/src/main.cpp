#define SerialParity true

#include <Arduino.h>

#if SerialParity
  #include <SoftwareSerialParity.h>
#else
  #include <SoftwareSerial.h> 
#endif

#include <string.h>
#include <AES.h>

#if SerialParity
  SoftwareSerialParity pspSerial(2, 3); // RX, TX
#else
  SoftwareSerial pspSerial(2, 3); // RX, TX
#endif

AES aes;

#define pin_butOk 7
#define pin_led 8

byte serial_code[8] = {0};
byte *msg;
int msgLength;
byte response1a[8] = {0};
byte response1b[8] = {0}; // battery nonce
byte response2g[8] = {0};

static byte *keystore(byte key)
{
  switch (key)
  {
    case 0: {return new byte[16] {0x5C, 0x52, 0xD9, 0x1C, 0xF3, 0x82, 0xAC, 0xA4, 0x89, 0xD8, 0x81, 0x78, 0xEC, 0x16, 0x29, 0x7B };} break;
    case 1: {return new byte[16] {0x9D, 0x4F, 0x50, 0xFC, 0xE1, 0xB6, 0x8E, 0x12, 0x09, 0x30, 0x7D, 0xDB, 0xA6, 0xA5, 0xB5, 0xAA };} break;
    case 2: {return new byte[16] {0x09, 0x75, 0x98, 0x88, 0x64, 0xAC, 0xF7, 0x62, 0x1B, 0xC0, 0x90, 0x9D, 0xF0, 0xFC, 0xAB, 0xFF };} break;
    case 3: {return new byte[16] {0xC9, 0x11, 0x5C, 0xE2, 0x06, 0x4A, 0x26, 0x86, 0xD8, 0xD6, 0xD9, 0xD0, 0x8C, 0xDE, 0x30, 0x59 };} break;
    case 4: {return new byte[16] {0x66, 0x75, 0x39, 0xD2, 0xFB, 0x42, 0x73, 0xB2, 0x90, 0x3F, 0xD7, 0xA3, 0x9E, 0xD2, 0xC6, 0x0C };} break;
    case 5: {return new byte[16] {0xF4, 0xFA, 0xEF, 0x20, 0xF4, 0xDB, 0xAB, 0x31, 0xD1, 0x86, 0x74, 0xFD, 0x8F, 0x99, 0x05, 0x66 };} break;
    case 6: {return new byte[16] {0xEA, 0x0C, 0x81, 0x13, 0x63, 0xD7, 0xE9, 0x30, 0xF9, 0x61, 0x13, 0x5A, 0x4F, 0x35, 0x2D, 0xDC };} break;
    case 0xA: {return new byte[16] {0xAC, 0x00, 0xC0, 0xE3, 0xE8, 0x0A, 0xF0, 0x68, 0x3F, 0xDD, 0x17, 0x45, 0x19, 0x45, 0x43, 0xBD};} break;
    case 0xD: {return new byte[16] {0xDF, 0xF3, 0xFC, 0xD6, 0x08, 0xB0, 0x55, 0x97, 0xCF, 0x09, 0xA2, 0x3B, 0xD1, 0x7D, 0x3F, 0xD2};} break;
    case 0xD9: {return new byte[16] {0xC7, 0xAC, 0x13, 0x06, 0xDE, 0xFE, 0x39, 0xEC, 0x83, 0xA1, 0x48, 0x3B, 0x0E, 0xE2, 0xEC, 0x89};} break;
    default: {return new byte[16] {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};} break; // не найдено
  }
};

static byte *challenge1_secret(byte version)
{
  switch (version)
  {
    case 0: {return new byte[8] {0xD2, 0x07, 0x22, 0x53, 0xA4, 0xF2, 0x74, 0x68};} break;
    case 1: {return new byte[8] {0xF5, 0xD7, 0xD4, 0xB5, 0x75, 0xF0, 0x8E, 0x4E};} break;
    case 2: {return new byte[8] {0xB3, 0x7A, 0x16, 0xEF, 0x55, 0x7B, 0xD0, 0x89};} break;
    case 3: {return new byte[8] {0xCC, 0x69, 0x95, 0x81, 0xFD, 0x89, 0x12, 0x6C};} break;
    case 4: {return new byte[8] {0xA0, 0x4E, 0x32, 0xBB, 0xA7, 0x13, 0x9E, 0x46};} break;
    case 5: {return new byte[8] {0x49, 0x5E, 0x03, 0x47, 0x94, 0x93, 0x1D, 0x7B};} break;
    case 6: {return new byte[8] {0xB0, 0xB8, 0x09, 0x83, 0x39, 0x89, 0xFA, 0xE2};} break;
    case 0xA: {return new byte[8] {0xC2, 0x37, 0x7E, 0x8A, 0x74, 0x09, 0x6C, 0x5F};} break;
    case 0xD: {return new byte[8] {0x58, 0x1C, 0x7F, 0x19, 0x44, 0xF9, 0x62, 0x62};} break;
    case 0x2F: {return new byte[8] {0xC9, 0xF8, 0x09, 0x45, 0x2A, 0xA2, 0xBE, 0xD5};} break;
    case 0xD9: {return new byte[8] {0x90, 0xE1, 0xF0, 0xC0, 0x01, 0x78, 0xE3, 0xFF};} break;
    default: {return new byte[8] {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};} break;
  }
};

static byte *challenge2_secret(byte version)
{
  switch (version)
  {
    case 0: {return new byte[8] {0xF4, 0xE0, 0x43, 0x13, 0xAD, 0x2E, 0xB4, 0xDB};} break;
    case 1: {return new byte[8] {0xFE, 0x7D, 0x78, 0x99, 0xBF, 0xEC, 0x47, 0xC5};} break;
    case 2: {return new byte[8] {0x86, 0x5E, 0x3E, 0xEF, 0x9D, 0xFB, 0xB1, 0xFD};} break;
    case 3: {return new byte[8] {0x30, 0x6F, 0x3A, 0x03, 0xD8, 0x6C, 0xBE, 0xE4};} break;
    case 4: {return new byte[8] {0xFF, 0x72, 0xBD, 0x2B, 0x83, 0xB8, 0x9D, 0x2F};} break;
    case 5: {return new byte[8] {0x84, 0x22, 0xDF, 0xEA, 0xE2, 0x1B, 0x63, 0xC2};} break;
    case 6: {return new byte[8] {0x58, 0xB9, 0x5A, 0xAE, 0xF3, 0x99, 0xDB, 0xD0};} break;
    case 0xA: {return new byte[8] {0x09, 0x3E, 0xC5, 0x19, 0xAF, 0x0F, 0x50, 0x2D};} break;
    case 0xD: {return new byte[8] {0x31, 0x80, 0x53, 0x87, 0x5C, 0x20, 0x3E, 0x24};} break;
    case 0x2F: {return new byte[8] {0x40, 0xD0, 0x2B, 0xAC, 0xFB, 0x1A, 0x8B, 0xEA};} break;
    case 0xD9: {return new byte[8] {0xC3, 0x4A, 0x6A, 0x7B, 0x20, 0x5F, 0xE8, 0xF9};} break;
    default: {return new byte[8] {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};} break;
  }
};

void setup()
{
  Serial.begin(115200);

  #if SerialParity
    pspSerial.begin(19200, EVEN);
  #else
    pspSerial.begin(19200); // SERIAL_8E1
  #endif

  pinMode(pin_butOk, INPUT);
  pinMode(pin_led, OUTPUT);

  digitalWrite(pin_led, LOW);

  if (digitalRead(pin_butOk))
  {
    for (int i = 0; i < 8; i++)
      serial_code[i] = 0xFF;

    digitalWrite(pin_led, HIGH);
    delay(250);
    digitalWrite(pin_led, LOW);
    delay(250);
    digitalWrite(pin_led, HIGH);
    delay(250);
    digitalWrite(pin_led, LOW);
    delay(250);
    digitalWrite(pin_led, HIGH);
    delay(250);
    digitalWrite(pin_led, LOW);

    Serial.println("Start service");
  }
  else
  {
    serial_code[0] = 0x12;
    serial_code[1] = 0x34;
    serial_code[2] = 0x56;
    serial_code[3] = 0x78;
    serial_code[4] = 0x00;
    serial_code[5] = 0x00;
    serial_code[6] = 0x00;
    serial_code[7] = 0x00;

    digitalWrite(pin_led, LOW);

    Serial.println("Start normal");
  }
}

void log_byte(byte b)
{
  if (b < 0x10)
    Serial.print("0");
  
  Serial.print(b, HEX);
  Serial.print(" ");
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
  Serial.print("Arduino: ");
  for (size_t i = 0; i < len; i++)
      log_byte(b[i]);
  Serial.println();
}

unsigned char GeneratePacketChecksum(unsigned char *inputArray, int n) // array with every sigle byte of packet w/o checksum
{
    int sum = 0;

    for (int i = 0; i < n; i++)
        sum += inputArray[i];

    return ((sum & 0xFF) ^ 0xFF); 
}

#define RAND_MAX_BITS 31
void rand_byte(uint8_t *dest, size_t size) 
{
  int r_queue = 0;
  int r_bit_count = 0;

  for (size_t i = 0; i < size; i++) 
  {
    int r = 0;

    if (r_bit_count < 8) 
    {
      int need = 8 - r_bit_count;

      r = r_queue << need;
      r_queue = rand();
      r ^= r_queue;
      r_queue >>= need;
      r_bit_count = RAND_MAX_BITS - need;
    } 
    else 
    {
      r = r_queue;
      r_queue >>= 8;
      r_bit_count -= 8;
    }
    dest[i] = r;
  }
}

static byte *MixChallenge1(byte version, byte *challenge)
{
    byte *data = new byte[16] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    byte *secret1 = challenge1_secret(version);

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

    return data;
}

static byte *MixChallenge2(byte version, byte *challenge)
{
  byte *data = new byte[16] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  byte *secret2 = challenge2_secret(version);

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

  return data;
}

static byte newmap[16] = { 0x00, 0x04, 0x08, 0x0C, 0x01, 0x05, 0x09, 0x0D, 0x02, 0x06, 0x0A, 0x0E, 0x03, 0x07, 0x0B, 0x0F };

static byte *MatrixSwap(byte *key, int key_len)
{
    byte *temp = new byte[16] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    for (int i = 0; i < key_len; i++)
        temp[i] = key[newmap[i]];

    return temp;
}

static byte *ECBEncryptBytes(byte *clearBytes, int len_clearBytes, byte *key)
{
  byte *encryptedBytes = new byte[len_clearBytes];
  // create an AES object
  
  aes.set_key(key, len_clearBytes);
  aes.encrypt(clearBytes, encryptedBytes);

  return encryptedBytes;
}

void generateSysconResponses(byte *response, int n)
{
  //byte screq[n] = {0};
  byte version = response[0];

  //for (int i = 0; i < n; i++)
  //  screq[i] = response[i];

  byte *tempKey = keystore(response[0]);
  
  Serial.print("Key ");
  for (int i = 0; i < 16; i++)
    log_byte(tempKey[i]);
  Serial.println();
  
  if (tempKey[0] == 0x00)
  {
    Serial.println("Key not found");

    for (int i = 0; i < sizeof(response1a); i++)
    {
      response1a[i] = 0xFF;
      response1b[i] = 0xFF;
      response2g[i] = 0xFF; 
    }
  }
  else
  {
    byte req[n-1] = {0};

    for (int i = 1; i < n; i++)
      req[i-1] = response[i];
    
    byte *data = MixChallenge1(version, req);
    byte *challenge1aes = ECBEncryptBytes(MatrixSwap(data, 16), 16, tempKey);
    byte challenge1a[8] = {0};

    for (int i = 0; i < 8; i++) 
      challenge1a[i] = challenge1aes[i];

    byte *challenge1baes = ECBEncryptBytes(challenge1a, 8, tempKey);

    for (int i = 0; i < sizeof(response1a); i++)
      response1a[i] = challenge1a[i]; // is correct

    rand_byte(response1b, 0x08);

    byte *data2 = MixChallenge2(version, response1b);
    byte *challenge2aes = ECBEncryptBytes(MatrixSwap(data2, 16), 16, tempKey);
    byte challenge2[8] = {0};

    for (int i = 0; i < 8; i++) 
      challenge2[i] = challenge2aes[i];

    byte *response2aes = ECBEncryptBytes(challenge2aes, 16, tempKey);

    for (int i = 0; i < 8; i++) 
      response2g[i] = response2aes[i];

    delete [] data;
    delete [] challenge1aes;
    delete [] challenge1baes;
    delete [] data2;
    delete [] challenge2aes;
    delete [] response2aes;
  }

  delete [] tempKey;
}

void loop() // run over and over
{
  byte pspdata[4] = {0};
  
  while (true)
  {
    if (pspSerial.available() > 0)
    {
      pspdata[0] = pspSerial.read();

      Serial.print("PSP:     ");
      log_byte(pspdata[0]);

      if (pspdata[0] == 0x5A)
      {
        pspdata[1] = pspSerial.read();               // packet length

        log_byte(pspdata[1]);

        pspdata[2] = pspSerial.read();               // operation code

        log_byte(pspdata[2]);

        if (pspdata[1] == 0x02)                             // if packet has no message then byte after the opcode is the checksum
        {
          pspdata[3] = pspSerial.read();           // checksum
          msgLength = 0;
        }
        else  // packet contains a message
        {
          msgLength = ((int)pspdata[1] - 2); // operation code is read already (-1); packet len includes
                                                  // checksum so to  get actual msg length we do -1 again                        
          while (pspSerial.available() < (int)pspdata[1] - 1) 
          { 
            delayMicroseconds(10); 
          }; // wait until bytestoread has remaining msg and csum (opcode is already read so -1)

          delete [] msg; 
          msg = new byte[msgLength];

          Serial.print("(");
          for (int i = 0; i < msgLength; i++) 
          {
            msg[i] = pspSerial.read();
            log_byte(msg[i]);
          }
          Serial.print(") ");

          pspdata[3] = pspSerial.read();
        }

        log_byte(pspdata[3]);
        Serial.println();

        switch (pspdata[2])
        {
          case 0x01: // ok
          { 
            byte answer[] = { 0xA5, 0x05, 0x06, 0x10, 0xC3, 0x06, 0x76 };

            psp_write(answer, sizeof (answer));
          }
          break;

          case 0x0C: // ok
          {
            byte headersn[3] = { 0xA5, 0x06, 0x06 };
            //byte serialno[] = serial_code[8];
            byte tempsn[7] = {0};
            byte tempsnLE[4] = {0};
            byte tempsn1[1] = {0};
            int order[4] = { 1, 0, 3, 2 };
                                      
            for (int i = 0; i < 4; i++) 
              tempsnLE[i] = serial_code[order[i]];
  
            tempsn[0] = headersn[0];
            tempsn[1] = headersn[1];
            tempsn[2] = headersn[2];

            tempsn[3] = tempsnLE[0];
            tempsn[4] = tempsnLE[1];
            tempsn[5] = tempsnLE[2];
            tempsn[6] = tempsnLE[3];

            tempsn1[0] = GeneratePacketChecksum(tempsn, sizeof(tempsn));

            psp_write(tempsn, sizeof(tempsn));
            psp_write(tempsn1, sizeof(tempsn1));
          }
          break;

          case 0x80:
          {
            generateSysconResponses(msg, msgLength);

            // create 19 byte long byte array  (a5 12 06 + bytes from response 1a + bytes from response 1b) and calculate
            // its checksum using GeneratePacketChecksum
            // send the array and checksum over serial
            byte header[3] = { 0xA5, 0x12, 0x06 };
            byte temp[19] = {0}; 

  //
            for(int i = 0; i < sizeof(header); i++)
              temp[i] = header[i];

            for(int i = 0; i < sizeof(response1a); i++)
              temp[i + sizeof(header)] = response1a[i];

            for(int i = 0; i < sizeof(response1b); i++)
              temp[i + sizeof(header) + sizeof(response1a)] = response1b[i];
  //         
            byte temp111[1] = {0};

            temp111[0] = GeneratePacketChecksum(temp, sizeof(temp));
      
            psp_write(temp, sizeof(temp)); 
            psp_write(temp111, 1);                       
          }
          break;

          case 0x81:
          {
            byte header1[3] = { 0xA5, 0x0A, 0x06 };
            byte temp1[11] = {0};
            byte cs1[1] = {0};

            for(int i = 0; i < sizeof(header1); i++)
              temp1[i] = header1[i];

            for(int i = 0; i < sizeof(response2g); i++)
              temp1[i + sizeof(header1)] = response2g[i];

            cs1[0] = GeneratePacketChecksum(temp1, sizeof(temp1));

            psp_write(temp1, sizeof(temp1));
            psp_write(cs1, sizeof(cs1));
          }
          break;

          case 0x03:
          {
            byte answer3[] = { 0xA5, 0x04, 0x06, 0x36, 0x10, 0x0A };

            psp_write(answer3, sizeof (answer3));

          }
          break;

          case 0x07:
          {
            byte answer4[] = { 0xA5, 0x04, 0x06, 0x08, 0x07, 0x41 };

              psp_write(answer4, sizeof (answer4));

          }
          break;

          case 0x0B:
          {
            byte answer5[] = { 0xA5, 0x04, 0x06, 0x0F, 0x00, 0x41 };

              psp_write(answer5, sizeof (answer5));

          }
          break;

          case 0x09:
          {
            byte answer6[] = { 0xA5, 0x04, 0x06, 0x01, 0x04, 0x4B };

              psp_write(answer6, sizeof (answer6));

          }
          break;

          case 0x02:
          {
            byte answer7[] = { 0xA5, 0x03, 0x06, 0x1B, 0x36 };

              psp_write(answer7, sizeof (answer7));

          }
          break;

          case 0x04:
          {
            byte answer8[] = { 0xA5, 0x04, 0x06, 0x68, 0x10, 0xD8 };

              psp_write(answer8, sizeof (answer8));

          }
          break;

          case 0x16:
          {
            byte answer9[] = { 0xA5, 0x13, 0x06, 0x53, 0x6F, 0x6E, 0x79, 0x45, 0x6E, 0x65, 0x72,
                                            0x67, 0x79, 0x44, 0x65, 0x76, 0x69, 0x63, 0x65, 0x73, 0x6B };

              psp_write(answer9, sizeof (answer9));

          }
          break;

          case 0x0D: // UNKNOWN
          {
            byte answer10[] = { 0xA5, 0x07, 0x06, 0x9D, 0x10, 0x10, 0x28, 0x14, 0x54 };
              
            psp_write(answer10, sizeof (answer10));
          }
          break;

          case 0x08: // UNKNOWN (1250?)
          {
            byte answer11[] = { 0xA5, 0x04, 0x06, 0xE2, 0x04, 0x6A };
            
            psp_write(answer11, sizeof (answer11));
          }
          break;

          default  :
          {
            Serial.println("No option selected");
          }
        }                      
      } 
      else Serial.println();
    }
  }
}