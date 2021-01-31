#include <stdlib.h>

#include <stdio.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    //chunk->lines = NULL;
    initLineCounts(&chunk->lines);
    initValueArray(&chunk->constants);
}

void freeChunk(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    //FREE_ARRAY(int, &chunk->lines, &chunk->lines->capacity);
    freeLineCounts(&chunk->lines);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
        //chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
    }

    if (chunk->lines.capacity < line) {
        int oldLinesCapacity = chunk->lines.capacity;
        chunk->lines.capacity = GROW_CAPACITY(oldLinesCapacity);
        chunk->lines.offsets = GROW_ARRAY(uint16_t, chunk->lines.offsets, oldLinesCapacity, chunk->lines.capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->lines.offsets[line]++;
    // // printf("Added offset to line: %d\n", line);
    // // printf("New offset at line %d: %d\n", line, chunk->lines.offsets[line]);
    //chunk->lines[chunk->count] = line;
    chunk->count++;
}

int addConstant(Chunk* chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

void initLineCounts(LineCounts* lines) {
    lines->count = 0;
    lines->capacity = 0;
    lines->offsets = NULL;
}

void freeLineCounts(LineCounts* lines) {
    FREE_ARRAY(uint16_t, lines->offsets, lines->capacity);
    initLineCounts(lines);
}
