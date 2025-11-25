#include "Basicio.h"

// Helper to calculate string length manually
static unsigned long _strlen(const char* str) {
    unsigned long len = 0;
    if (!str) return 0;
    while (str[len] != '\0') {
        ++len;
    }
    return len;
}

void IO::print(const char* str) {
    _syscall_write(1, str, _strlen(str));
}

void IO::printLine(const char* str) {
    _syscall_write(1, str, _strlen(str));
    _syscall_write(1, "\n", 1);
}

void IO::printChar(char c) {
    _syscall_write(1, &c, 1);
}

void IO::printInt(long n) {
    if (n == 0) {
        _syscall_write(1, "0", 1);
        return;
    }

    if (n < 0) {
        _syscall_write(1, "-", 1);
        n = -n;
    }

    char buffer[32];
    int index = 0;

    while (n > 0 && index < 31) {
        int digit = (int)(n % 10);
        buffer[index++] = (char)('0' + digit);
        n /= 10;
    }

    // Digits are in reverse order in buffer[0..index-1]
    while (index > 0) {
        --index;
        _syscall_write(1, &buffer[index], 1);
    }
}

void IO::printFloat(float n, int precision) {
    // Handle negative values
    if (n < 0.0f) {
        _syscall_write(1, "-", 1);
        n = -n;
    }

    long intPart = (long)n;
    printInt(intPart);
    printChar('.');

    float remainder = n - (float)intPart;
    if (precision < 0) precision = 0;
    if (precision > 6) precision = 6; // avoid too many iterations

    for (int i = 0; i < precision; ++i) {
        remainder *= 10.0f;
        int digit = (int)remainder;
        printChar((char)('0' + digit));
        remainder -= (float)digit;
    }
}

int IO::openFile(const char* filename) {
    return (int)_syscall_open(filename, 0, 0); // 0 is O_RDONLY
}

void IO::closeFile(int fd) {
    _syscall_close(fd);
}

// Overload readLine to take a file descriptor
long IO::readLine(int fd, char* buffer, long maxLen) {
    if (!buffer || maxLen <= 0) return 0;
    long count = 0;
    while (count < maxLen - 1) {
        char c;
        long nread = _syscall_read(fd, &c, 1);
        if (nread <= 0) break;
        if (c == '\n') break; // Stop at newline
        // skip carriage return if present
        if (c != '\r') buffer[count++] = c; 
    }
    buffer[count] = '\0';
    return count;
}
