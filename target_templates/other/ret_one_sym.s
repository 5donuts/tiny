.text
  .global _start

_start:
  movl  $1, %ebx
  movl  $1, %eax
  int   $0x80   # NB: this is exactly the same as ret_one.s
