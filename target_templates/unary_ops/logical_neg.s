.text
  .global _start

_start:
  movl  $1, %eax
  movl  $1, %ebx  # the value to take the logical NOT of
  cmp   $1, %ebx  # test %ebx == "true" (1)
  jne   ne
    movl  $0, %ebx  # if %ebx == "true", set %ebx = "false"
    jmp skip
  ne:
    movl  $1, %ebx  # if %ebx != "true", set %ebx = "true"
  skip:
  int   $0x80
