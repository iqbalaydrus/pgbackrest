/***********************************************************************************************************************************
Buffer IO Read

Read from a Buffer object using the IoWrite interface.
***********************************************************************************************************************************/
#ifndef COMMON_IO_BUFFERREAD_H
#define COMMON_IO_BUFFERREAD_H

/***********************************************************************************************************************************
Object type
***********************************************************************************************************************************/
typedef struct IoBufferRead IoBufferRead;

#include "common/io/read.h"

/***********************************************************************************************************************************
Constructor
***********************************************************************************************************************************/
IoBufferRead *ioBufferReadNew(const Buffer *buffer);

/***********************************************************************************************************************************
Functions
***********************************************************************************************************************************/
size_t ioBufferRead(IoBufferRead *this, Buffer *buffer);
IoBufferRead *ioBufferReadMove(IoBufferRead *this, MemContext *parentNew);

/***********************************************************************************************************************************
Getters
***********************************************************************************************************************************/
bool ioBufferReadEof(const IoBufferRead *this);
IoRead *ioBufferReadIo(const IoBufferRead *this);

/***********************************************************************************************************************************
Destructor
***********************************************************************************************************************************/
void ioBufferReadFree(IoBufferRead *this);

/***********************************************************************************************************************************
Macros for function logging
***********************************************************************************************************************************/
#define FUNCTION_DEBUG_IO_BUFFER_READ_TYPE                                                                                         \
    IoBufferRead *
#define FUNCTION_DEBUG_IO_BUFFER_READ_FORMAT(value, buffer, bufferSize)                                                            \
    objToLog(value, "IoBufferRead", buffer, bufferSize)

#endif