typedef enum {
    OK = 0,
    ERROR = -1,
    NOT_FOUND = -2,
    INVALID_INPUT = -3,
    OUT_OF_RANGE = -4,
    MEMORY_ERROR = -5,
    ALREADY_EXISTS = -6,
    DISCONNECTED = -7
} statusCode;

#include <Servo.h>

Servo myservo; 

int pos = 0;    

#define MAX_BUFFER_LENGTH 35

struct buffer {
    char buffer[MAX_BUFFER_LENGTH + 1]; // +1 for the null terminator
    uint8_t currentIndex;
};

struct buffer clientBuffer;

void setup() {
  myservo.attach(6); 
  Serial.begin(9600);
  // Serial.println("De beunrobot is gestart");

  // char* message = "#50|500&";
  // uint16_t values[2] = {0};
  // readBytes(message, values, 2);
  // Serial.println(values[0]);
  // Serial.println(values[1]);

  bufferInit(&clientBuffer);
}

void loop() {
  // for (pos = 0; pos <= 180; pos += 1) { 
  //   myservo.write(pos);             
  //   delay(5);                       
  // }
  // for (pos = 180; pos >= 0; pos -= 1) { 
  //   myservo.write(pos);              
  //   delay(5);                       
  // }

  // char* message = "#50|500&";
  uint16_t values[2] = {0};

  while ((Serial.available())) {
        char currentChar = Serial.read();
        switch (currentChar) {
            case '#':
                bufferInit(&clientBuffer);
                bufferAddChar(&clientBuffer, currentChar);
                break;
            case '&':
                bufferAddChar(&clientBuffer, currentChar);
                bufferAddNullTerminator(&clientBuffer);
                // convertTcpToCan(clientBuffer.buffer, &messageBuffer, &canFrame);
                readBytes(clientBuffer.buffer, values, 2);
                Serial.println(values[0]);
                Serial.println(values[1]);
                bufferInit(&clientBuffer);
                break;
            default:
                bufferAddChar(&clientBuffer, currentChar);
                break;
        }
    }
}


statusCode readBytes(const char* message, uint16_t* data, uint8_t length) {
    if (!message || !data) {
        return INVALID_INPUT;
    }
    // Save the current index where the data should be stored
    uint8_t currentIndex = 0;
    for (size_t i = 0; i < strlen(message); i++) {
        // Skip the start and end bytes
        if (message[i] == '&' || message[i] == '#') {
            continue;
        }
        // If the separator is found, move to the next byte
        if (message[i] == '|') {
            currentIndex++;
            if (currentIndex >= length) {
                return OUT_OF_RANGE;
            }
            continue;
        }
        data[currentIndex] = (uint16_t)(data[currentIndex] * 10 + (message[i] - '0'));
    }
    return OK;
}
