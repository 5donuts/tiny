.text
  .global _start

_start:
  movl  $1, %eax
  movl  $1, %ebx
  neg   %ebx
  int   $0x80
