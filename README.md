# asm interpreter

it converts an arm like assembly mnemonics and runs it on a virtual machine

this is the given instruction set

```c
enum opcodes {
  LDR = 0b0001,
  STR, 
  ADD, 
  SUB, 
  MOV, 
  CMP, 
  B,  
  AND, 
  ORR, 
  EOR, 
  MVN, 
  LSL, 
  LSR, 
  HALT, 
  OUT 
};
```
