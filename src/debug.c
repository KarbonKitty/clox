#include <stdio.h>

#include "debug.h"
#include "value.h"

void disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);

    for (int offset = 0; offset < chunk->count;) {
        offset = disassembleInstruction(chunk, offset);
    }
}

static int simpleInstruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

static int constantInstruction(const char* name, Chunk* chunk, int offset) {
    uint8_t constant = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");
    return offset + 2;
}

static int getLine(Chunk* chunk, int offset) {
    int runningTotal = -1;
    int i = 0;
    while (runningTotal < offset) {
        runningTotal += chunk->lines.offsets[i++];
    }
    return --i;
}

int disassembleInstruction(Chunk* chunk, int offset) {
    printf("%04d ", offset);

    int previousLine = offset > 0 ? getLine(chunk, offset - 1) : -1;
    int currentLine = getLine(chunk, offset);

    if (currentLine == previousLine) {
        printf("   | ");
    } else {
        printf("%4d ", currentLine);
    }

    uint8_t instruction = chunk->code[offset];
    switch (instruction)
    {
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}
