.text
  .global _start

_start:
  movl  $1, %eax  ; use the _exit syscall
  movl  $2, %ebx  ; error code 2
  int   $0x80     ; make syscall
