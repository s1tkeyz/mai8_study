#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <stdbool.h>

const uint8_t HEX_DIGITS_AMOUNT = 16U;
const uint8_t MD5_BYTE_SIZE = 16U;
const uint8_t MD5_CHAR_SIZE = 32U;
const uint8_t BYTE_LOW = 15U;
const uint16_t STRING_MAX_CAPACITY = 2048U;
const uint32_t COLLECTION_MIN_CAPACITY = 1000000U;
const uint8_t COLLECTION_EXPAND_FACTOR = 2U;

typedef uint8_t TByte;

TByte HexCharToByte(char c) {
    if(c >= '0' && c <= '9') {
        return (TByte)(c - '0');
    }
    else {
        return (TByte)(c - 'a') + 10;
    }
}

typedef struct _tkeyvalue {
    TByte key[MD5_BYTE_SIZE];
    char* value;
} TKeyValue;

void KVDestroy(TKeyValue* kv) {
    free(kv->value);
}

void KVPrintKey(TKeyValue* kv) {
    for(uint8_t i = MD5_BYTE_SIZE; i > 0; --i) {
        printf("%02x", kv->key[i - 1]);
    }
}

uint8_t GetRadix(TByte* key, uint8_t idx) {
    uint8_t i = idx >> 1;
    if(idx & 1) {
        return key[i] >> 4;
    } 
    return key[i] & BYTE_LOW;
}

void KVInitValue(TKeyValue* kv, char* tmpbuf) {
    uint16_t sz = strlen(tmpbuf) + 1;
    kv->value = tmpbuf;
    kv->value = (char*)realloc(kv->value, sz);
}

typedef struct _tcollection {
    uint32_t capacity;
    uint32_t size;
    TKeyValue* buffer;
} TCollection;

void TCollectionInit(TCollection* obj) {
    obj->capacity = COLLECTION_MIN_CAPACITY;
    obj->size = 0;
    obj->buffer = (TKeyValue*)malloc(COLLECTION_MIN_CAPACITY * sizeof(TKeyValue));
}

void TCollectionExpand(TCollection* obj) {
    if(obj->size < obj->capacity) {
        return;
    }
    obj->buffer = (TKeyValue*)realloc(obj->buffer, obj->capacity * COLLECTION_EXPAND_FACTOR * sizeof(TKeyValue));
    obj->capacity *= COLLECTION_EXPAND_FACTOR;
}

void TCollectionPrint(TCollection* col) {
    for(uint32_t i = 0; i < col->size; ++i) {
        KVPrintKey(&col->buffer[i]);
        printf("\t%s", col->buffer[i].value);
        putchar('\n');
    }
}

void TCollectionDestroy(TCollection* col) {
    for(uint32_t i = 0; i < col->size; ++i) {
        KVDestroy(col->buffer + i);
    }
    free(col->buffer);
}

void TCollectionFit(TCollection* col) {
    if(col->size == col->capacity)
        return;
    col->buffer = (TKeyValue*)realloc(col->buffer, col->size * sizeof(TKeyValue));
    col->capacity = col->size;
}

int main(void) {
    TCollection array;
    TCollectionInit(&array);

    char* read_key_buff = (char*)malloc((MD5_CHAR_SIZE + 1) * sizeof(char));  
    while(scanf("%s", read_key_buff) != EOF) {
        TCollectionExpand(&array);

        for(uint8_t i = MD5_CHAR_SIZE; i > 0; --i) {
            array.buffer[array.size].key[(i - 1) >> 1] |= \
                (HexCharToByte(read_key_buff[MD5_CHAR_SIZE - i]) << (((i - 1) & 1) << 2));
        }

        char* read_value_buff = (char*)malloc((STRING_MAX_CAPACITY + 1) * sizeof(char));  
        scanf("%s", read_value_buff);
        KVInitValue(&array.buffer[array.size], read_value_buff);

        array.size++;
    }

    free(read_key_buff);
    TCollectionFit(&array);

    TKeyValue* tmpdest = (TKeyValue*)malloc(array.size * sizeof(TKeyValue));
    TKeyValue* tmpsrc = array.buffer;
    for(uint8_t rnd = 0; rnd < MD5_CHAR_SIZE; ++rnd) {
        uint32_t counter[HEX_DIGITS_AMOUNT] = {0};

        uint32_t j;
        for(j = 0; j < array.size; ++j) {
            uint8_t radix = GetRadix(tmpsrc[j].key, rnd);
            counter[radix]++;
        }

        for(j = 1; j < HEX_DIGITS_AMOUNT; ++j) {
            counter[j] += counter[j - 1];
        }

        for(j = array.size; j > 0; --j) {
            uint8_t rdx = GetRadix(tmpsrc[j - 1].key, rnd);
            tmpdest[counter[rdx] - 1] = tmpsrc[j - 1];
            counter[rdx]--;
        }

        TKeyValue* t = tmpsrc;
        tmpsrc = tmpdest;
        tmpdest = t;
    }

    TCollectionPrint(&array);

    free(tmpdest);
    TCollectionDestroy(&array);

    return EXIT_SUCCESS;
}