#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, const char* argv[]) {
    Chunk chunk;
    initChunk(&chunk);

    int constant = addConstant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT, 1);
    writeChunk(&chunk, constant, 1);

    int second = addConstant(&chunk, 2.4);
    writeChunk(&chunk, OP_CONSTANT, 2);
    writeChunk(&chunk, second, 2);

    int third = addConstant(&chunk, 3.6);
    writeChunk(&chunk, OP_CONSTANT, 2);
    writeChunk(&chunk, third, 2);

    writeChunk(&chunk, OP_RETURN, 3);

    disassembleChunk(&chunk, "test chunk");

    freeChunk(&chunk);

    return 0;
}
