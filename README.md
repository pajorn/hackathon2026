# 16-bit computer emulator
a 16-bit computer built from pure logic: cpu, memory, gpu, 128x128 display, assembler to write programs, and a visualiser that shows the machine running.

requires sdl2 and python3.
    cd emulator && make
    python3 ../assembler/assembler.py ../programs/screen.asm
    ./emulator ../programs/screen.bin

## memory 
| range | use |
|-------|-----|
| `0000` – `7FFF` | program and data                         |
| `8000` – `BFFF` | stack   |
| `C000` – `FFFF` | gpu, framebuffer, 128×128|

## pixel format
16 bits, rgb555: `? rrrrr ggggg bbbbb`. bit 15 (?) unused

## Instruction Set
|Instruction|Something|
|---|---|
|nop
|mov r1, r2
|ld r1, r2 | moves (the content of the address pointed to by r2) into r1
|st r1, r2 | moves r1 into (the address pointed to by r2)
|jmp label | jumps to a label in code
|jmp 0x???? | jumps to a specific memory region
|push r1 | pushes r1 onto stack
|pop r1 | pops r1 off stack
|ldi r1, 0x???? | moves 0x???? into r1
|call label | call "function". same args as jmp
|call 0x???? | call "function". same args as jmp
|ret | return after being called
|cmp r1, r2 | sub but without affecting destination register. (affects flags for branching)
|breq label | branch if equal (equal flag set). same args as jmp
|breq 0x???? | branch if equal (equal flag set). same args as jmp
|brlt label | branch if less than (negative flag set) (r1 < r2 after cmp/sub). same args as jmp
|brlt 0x???? | branch if less than (negative flag set) (r1 < r2 after cmp/sub). same args as jmp
|add r1, r2 | r1 = r1 + r2
|sub r1, r2 | r1 = r1 - r2
|and r1, r2 | r1 = r1 & r2
|or r1, r2 | r1 = r1 | r2
|xor r1, r2 | r1 = r1 ^ r2
|lsl r1, 0x???? | r1 = r1 << 0x????
|lsr r1, 0x???? | r1 = r1 >> 0x????
|mul r1, r2 | r1 = r1 * r2

## layout

    assmbler/ assmbler
    emulator/ C++ source, Makefile
    programs/ some assembly programs


