#ifndef CODEGEN_H
#define CODEGEN_H

// definitions for linux syscalls
#define SYS_EXIT 0x01

// struct to hold a syscall code & its arguments
typedef struct {
  int code; // in %eax
  void *arg1; // in %ebx
  void *arg2; // in %ecx
  void *arg3; // in %edx
  void *arg4; // in %esi
  void *arg5; // in %edi
} syscall;

// function declarations
// NB: functions are defined in main.c
void make_syscall(syscall *); // make a syscall with some arguments
// TODO write more declarations & implement these

#endif // CODEGEN_H
