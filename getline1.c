#include "shell.h"

/**
 * bufferInput - buffers chained commands
 * @info: Pointer to ShellInfo struct
 * @buffer: Address of buffer
 * @bufferSize: Address of buffer size variable
 *
 * Return: Bytes read
 */
ssize_t bufferInput(ShellInfo *info, char **buffer, size_t *bufferSize)
{
    ssize_t bytesRead = 0;
    size_t currentSize = 0;

    if (!*bufferSize)
    {
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, blockCtrlC);
        bytesRead = getline(buffer, &currentSize, stdin);

        if (bytesRead > 0)
        {
            if ((*buffer)[bytesRead - 1] == '\n')
            {
                (*buffer)[bytesRead - 1] = '\0'; /* Remove trailing newline */
                bytesRead--;
            }
            info->linecountFlag = 1;
            removeComments(*buffer);
            addToHistory(info, *buffer);
            *bufferSize = bytesRead;
            info->commandBuffer = buffer;
        }
    }

    return bytesRead;
}

/**
 * getInput - gets a line minus the newline
 * @info: Pointer to ShellInfo struct
 *
 * Return: Bytes read
 */
ssize_t getInput(ShellInfo *info)
{
    static char *buffer; /* The ';' command chain buffer */
    static size_t currentIndex, lastIndex, bufferSize;
    ssize_t bytesRead = 0;
    char **currentBuffer = &(info->argument), *ptr;

    _putchar(BUF_FLUSH);
    bytesRead = bufferInput(info, &buffer, &bufferSize);

    if (bytesRead == -1) /* EOF */
        return -1;

    if (bufferSize) /* We have commands left in the chain buffer */
    {
        lastIndex = currentIndex; /* Initialize new iterator to current buffer position */
        ptr = buffer + currentIndex; /* Get pointer for return */
        checkCommandChain(info, buffer, &lastIndex, currentIndex, bufferSize);

        while (lastIndex < bufferSize) /* Iterate to semicolon or end */
        {
            if (isCommandChain(info, buffer, &lastIndex))
                break;
            lastIndex++;
        }

        currentIndex = lastIndex + 1; /* Increment past nulled ';' */
        if (currentIndex >= bufferSize) /* Reached the end of the buffer? */
        {
            currentIndex = bufferSize = 0; /* Reset position and length */
            info->commandBufferType = CMD_NORMAL;
        }

        *currentBuffer = ptr; /* Pass back pointer to the current command position */
        return _strlen(ptr); /* Return the length of the current command */
    }

    *currentBuffer = buffer; /* Not a chain; pass back buffer from getline() */
    return bytesRead; /* Return length of buffer from getline() */
}

/**
 * readBuffer - reads a buffer
 * @info: Pointer to ShellInfo struct
 * @buffer: Buffer
 * @currentIndex: Size
 *
 * Return: bytesRead
 */
ssize_t readBuffer(ShellInfo *info, char *buffer, size_t *currentIndex)
{
    ssize_t bytesRead = 0;

    if (*currentIndex)
        return 0;

    bytesRead = read(info->readfd, buffer, READ_BUFFER_SIZE);

    if (bytesRead >= 0)
        *currentIndex = bytesRead;

    return bytesRead;
}

/**
 * customGetline - gets the next line of input from STDIN
 * @info: Pointer to ShellInfo struct
 * @pointer: Address of pointer to buffer, preallocated or NULL
 * @length: Size of preallocated pointer buffer if not NULL
 *
 * Return: bytesRead
 */
int customGetline(ShellInfo *info, char **pointer, size_t *length)
{
    static char buffer[READ_BUFFER_SIZE];
    static size_t currentIndex = 0, bufferLength = 0;
    size_t k;
    ssize_t bytesRead = 0, totalBytesRead = 0;
    char *p = NULL, *newPointer = NULL, *c;

    p = *pointer;
    if (p && length)
        totalBytesRead = *length;

    if (currentIndex == bufferLength)
    {
        currentIndex = bufferLength = 0;
    }

    bytesRead = readBuffer(info, buffer, &bufferLength);

    if (bytesRead == -1 || (bytesRead == 0 && bufferLength == 0))
        return -1;

    c = _strchr(buffer + currentIndex, '\n');
    k = c ? 1 + (unsigned int)(c - buffer) : bufferLength;

    newPointer = _realloc(p, totalBytesRead, totalBytesRead ? totalBytesRead + k : k + 1);
    if (!newPointer) /* MALLOC FAILURE! */
    {
        if (p)
            free(p);
        return -1;
    }

    if (totalBytesRead)
        _strncat(newPointer, buffer + currentIndex, k - currentIndex);
    else
        _strncpy(newPointer, buffer + currentIndex, k - currentIndex + 1);

    totalBytesRead += k - currentIndex;
    currentIndex = k;
    p = newPointer;

    if (length)
        *length = totalBytesRead;
    *pointer = p;
    return totalBytesRead;
}

/**
 * blockCtrlC - blocks ctrl-C
 * @sigNum: The signal number
 *
 * Return: void
 */
void blockCtrlC(__attribute__((unused)) int sigNum)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}

