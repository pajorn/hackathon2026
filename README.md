# computer/processor emulator with display output + assembler thing ??

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

## Pixel Format
2 bytes. xrrr rrgg gggb bbbb

## tree
.
├── assembler \
│   └── assembler.py \
├── emulator \
│   ├── Computer.cpp \
│   ├── Computer.h \
│   ├── Decoder.cpp \
│   ├── Decoder.h \
│   ├── emulator \
│   ├── font8x8_basic.h \
│   ├── GPU.cpp \
│   ├── GPU.h \
│   ├── josiah.cpp \
│   ├── main.cpp \
│   ├── Makefile \
│   ├── Memory.cpp \
│   ├── Memory.h \
│   ├── pajorn.cpp \
│   ├── Registers.cpp \
│   ├── Registers.h \
│   ├── Visualiser.cpp \
│   └── Visualiser.h \
├── instruction_set \
├── programs \
│   ├── cellular_automata.asm \
│   ├── screen.asm \
│   └── test.asm \
└── README.md 

## controls
| key     | function                      |
|---------|-------------------------------|
| `space` | pause/resume                  |
| `.`     | step one instruction (paused) |
| `r`     | restart program               |
| `esc`   | quit                          |
