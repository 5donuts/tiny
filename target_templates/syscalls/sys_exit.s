 .text
   .global _start

 _start:
   movl  $1, %eax  # use the _exit syscall
   movl  $2, %ebx  # exit with status code 2
   int   $0x80     # make the syscall
