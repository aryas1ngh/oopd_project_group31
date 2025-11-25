#ifndef BASICIO_H
#define BASICIO_H
#define O_RDONLY 00
#define O_WRONLY 01
#define O_CREAT  0100
#define O_TRUNC  01000

// Declarations of the assembly functions for low-level syscalls
extern "C" long _syscall_write(int fd, const char* buf, unsigned long count);
extern "C" long _syscall_read(int fd, char* buf, unsigned long count);
extern "C" long _syscall_open(const char* filename, int flags, int mode);
extern "C" long _syscall_close(int fd);

namespace IO {
    // Basic output helpers
    void print(const char* str);
    void printLine(const char* str);
    void printInt(long n);
    void printFloat(float n, int precision = 2);
    void printChar(char c);

    // Basic input helper: reads a line from stdin (fd = 0) into buffer.
    // Returns number of bytes read (excluding terminating '\0').
    long readLine(char* buffer, long maxLen);
    // File helpers
    int openFile(const char* filename);
    void closeFile(int fd);

    // Update readLine to take a file descriptor (default 0 = stdin)
    long readLine(int fd, char* buffer, long maxLen); 
    
    // Keep the overload for backward compatibility if you want
    inline long readLine(char* buffer, long maxLen) { return readLine(0, buffer, maxLen); }
}

#endif
