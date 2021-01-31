#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
    OP_CONSTANT,
    OP_RETURN,
} OpCode;

typedef struct {
    int count;
    int capacity;
    uint16_t* offsets;
} LineCounts;

typedef struct {
    int count;
    int capacity;
    uint8_t* code;
    LineCounts lines;
    ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int addConstant(Chunk* chunk, Value value);

void initLineCounts(LineCounts* lines);
void freeLineCounts(LineCounts* lines);

#endif
