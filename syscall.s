.global _syscall_write
.global _syscall_read
.global _syscall_open
.global _syscall_close

.text

# Function: _syscall_write
# Arguments: rdi = file descriptor (1 for stdout), rsi = buffer, rdx = count
# Returns: rax = number of bytes written
_syscall_write:
    mov $1, %rax        # syscall number for sys_write is 1 on x86_64 Linux
    syscall
    ret

# Function: _syscall_read
# Arguments: rdi = file descriptor (0 for stdin), rsi = buffer, rdx = count
# Returns: rax = number of bytes read
_syscall_read:
    mov $0, %rax        # syscall number for sys_read is 0 on x86_64 Linux
    syscall
    ret

# Function: _syscall_open
# Arguments: rdi = filename (const char*), rsi = flags (int), rdx = mode (int)
# Returns: rax = file descriptor (positive) or error code (negative)
_syscall_open:
    mov $2, %rax        # syscall number for sys_open is 2
    syscall
    ret

# Function: _syscall_close
# Arguments: rdi = file descriptor (int)
# Returns: rax = 0 on success
_syscall_close:
    mov $3, %rax        # syscall number for sys_close is 3
    syscall
    ret
