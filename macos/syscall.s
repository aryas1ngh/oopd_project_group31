.global __syscall_write
.global __syscall_read
.global __syscall_open
.global __syscall_close

.text

# -----------------------------------------------------------------------------
# macOS System Call Wrappers (x86_64 via Rosetta)
#
# Note on Symbols:
# macOS compilers prepend an underscore to C function names. 
# We use double underscores (e.g., __syscall_write) so the linker
# matches them to the C++ declaration 'extern "C" ... _syscall_write'.
#
# Note on Syscall Numbers (BSD Class 0x2000000):
# write (4), read (3), open (5), close (6).
# -----------------------------------------------------------------------------

# Function: _syscall_write
# Arguments: rdi = fd, rsi = buffer, rdx = count
# Returns: rax = bytes written
__syscall_write:
    mov $0x2000004, %rax    # 0x2000000 + 4 (sys_write)
    syscall
    ret

# Function: _syscall_read
# Arguments: rdi = fd, rsi = buffer, rdx = count
# Returns: rax = bytes read
__syscall_read:
    mov $0x2000003, %rax    # 0x2000000 + 3 (sys_read)
    syscall
    ret

# Function: _syscall_open
# Arguments: rdi = path, rsi = flags, rdx = mode
# Returns: rax = fd
__syscall_open:
    mov $0x2000005, %rax    # 0x2000000 + 5 (sys_open)
    syscall
    ret

# Function: _syscall_close
# Arguments: rdi = fd
# Returns: rax = 0 on success
__syscall_close:
    mov $0x2000006, %rax    # 0x2000000 + 6 (sys_close)
    syscall
    ret