.text
  .global _start

_start:
  movl  $1, %eax
  movl  $1, %ebx  # the value to take the logical NOT of
  xor   $1, %ebx  # NB: this is only valid for 0x01 and 0x00 values
  int   $0x80
