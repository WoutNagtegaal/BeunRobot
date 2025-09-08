#define MAX_NUMBER_LENGTH 4
// #define MAX_BUFFER_LENGTH 35

// struct buffer {
//     char buffer[MAX_BUFFER_LENGTH + 1]; // +1 for the null terminator
//     uint8_t currentIndex;
// };

// Function to initialize the buffer
statusCode bufferInit(struct buffer* buffer) {
    if (!buffer) {
        return INVALID_INPUT;
    }
    // Setting the index to 0 to indicate that the buffer is empty
    buffer->currentIndex = 0;
    return OK;
}

// Function to add a character to the buffer
statusCode bufferAddChar(struct buffer* buffer, char character) {
    if (!buffer) {
        return INVALID_INPUT;
    }

    if (buffer->currentIndex >= MAX_BUFFER_LENGTH - 1) {
        return OUT_OF_RANGE;
    }

    buffer->buffer[buffer->currentIndex] = character; // Add the character to the buffer
    buffer->currentIndex++;
    return OK;
}

// Function to add a number to the buffer
statusCode bufferAddNumber(struct buffer* buffer, uint8_t number) {
    if (!buffer) {
        return INVALID_INPUT;
    }

    if (buffer->currentIndex >= MAX_BUFFER_LENGTH - 1) {
        return OUT_OF_RANGE;
    }

    char numberBuffer[MAX_NUMBER_LENGTH] = {0};
    int32_t writtenToBuffer =
        snprintf(numberBuffer, MAX_NUMBER_LENGTH, "%d", number); // Convert number to string

    // Check if the number was written to the buffer correctly
    // The return value of snprintf is the number of characters written to the buffer or a negative
    // if an error occurred
    if (writtenToBuffer < 0 || writtenToBuffer >= MAX_NUMBER_LENGTH) {
        return OUT_OF_RANGE;
    }

    // Check if the number fits in the buffer, otherwise return OUT_OF_RANGE
    if (buffer->currentIndex + (uint8_t)strlen(numberBuffer) > MAX_BUFFER_LENGTH - 1) {
        return OUT_OF_RANGE;
    }

    // Add the number to the buffer
    if (strncat(buffer->buffer, numberBuffer, MAX_NUMBER_LENGTH) == NULL) {
        return OUT_OF_RANGE;
    }

    buffer->currentIndex += (uint8_t)strlen(numberBuffer);
    return OK;
}

statusCode bufferAddNullTerminator(struct buffer* buffer) {
    if (!buffer) {
        return INVALID_INPUT;
    }
    // No need to check if the buffer is full, as the null terminator is only one character and the
    // buffer has space for it

    // Add the null terminator to the buffer
    buffer->buffer[buffer->currentIndex] = '\0'; // Add the null terminator to the buffer
    buffer->currentIndex++;
    return OK;
}