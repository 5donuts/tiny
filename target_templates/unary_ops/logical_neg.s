.text
  .global _start

_start:
  movl  $1, %eax
  movl  $1, %ebx
  xor   $1, %ebx  # equivalent to Logical NOT (0 is false, 1 is true)
  int   $0x80
