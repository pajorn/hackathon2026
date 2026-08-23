ldi r0, 0xC000	; pixels
ldi r1, 0x0001
ldi r2, 0x0080	; size
ldi r3, 0x0000	; row
ldi r4, 0x0000	; col
ldi r7, 0x4000	; colours


ldi r15, 0x7FFF

call make_colours
row:
col:
; calc offset
mov r6, r3
mul r6, r2
add r6, r4
add r6, r0

call calc_pixel
add r7, r5
ld r8, r7
sub r7, r5
st r8, r6

; end col
add r4, r1
cmp r4, r2
brlt col
xor r4, r4

; end row
add r3, r1	; inc row
cmp r3, r2
brlt row


loop:
jmp loop



calc_pixel:	; this function was co-written with an LLM
push r6
push r7
push r8
push r9
push r10
push r11
push r12
push r13
push r14
push r15

; cx = -2 + col * 96 / 4096
ldi r6, 0x0060
mul r6, r4
ldi r11, 0xE000
add r6, r11

; cy = -1.5 + row * 96 / 4096
ldi r7, 0x0060
mul r7, r3
ldi r11, 0xE800
add r7, r11

; x = 0
; y = 0
; i = 0
xor r8, r8
xor r9, r9
xor r10, r10

ldi r11, 0x003F

start:

; x^2
mov r12, r8
mul r12, r8

mov r13, r8
mulh r13, r8

lsr r12, 0x000C
lsl r13, 0x0004
or r12, r13

; y^2
mov r14, r9
mul r14, r9

mov r15, r9
mulh r15, r9

lsr r14, 0x000C
lsl r15, 0x0004
or r14, r15

; if x^2 + y^2 > 4
mov r15, r12
add r15, r14

ldi r13, 0x4000
cmp r13, r15
brlt escaped

; xy
mov r13, r8
mul r13, r9

mov r15, r8
mulh r15, r9

lsr r13, 0x000C
lsl r15, 0x0004
or r13, r15

; new x = x^2 - y^2 + cx
sub r12, r14
add r12, r6

; new y = 2xy + cy
lsl r13, 0x0001
add r13, r7

; update x,y
mov r8, r12
mov r9, r13

; i++
ldi r12, 0x0001
add r10, r12

cmp r10, r11
brlt start

escaped:
mov r5, r10

pop r15
pop r14
pop r13
pop r12
pop r11
pop r10
pop r9
pop r8
pop r7
pop r6

ret


make_colours:
push r0
push r1
push r2

ldi r0, 0x4000
ldi r1, 0x0001

ldi r2, 0x0000
st r2, r0
add r0, r1

ldi r2, 0x1008
st r2, r0
add r0, r1

ldi r2, 0x200F
st r2, r0
add r0, r1

ldi r2, 0x3017
st r2, r0
add r0, r1

ldi r2, 0x401F
st r2, r0
add r0, r1

ldi r2, 0x301F
st r2, r0
add r0, r1

ldi r2, 0x201F
st r2, r0
add r0, r1

ldi r2, 0x101F
st r2, r0
add r0, r1

ldi r2, 0x001F
st r2, r0
add r0, r1

ldi r2, 0x009F
st r2, r0
add r0, r1

ldi r2, 0x011F
st r2, r0
add r0, r1

ldi r2, 0x019F
st r2, r0
add r0, r1

ldi r2, 0x021F
st r2, r0
add r0, r1

ldi r2, 0x029F
st r2, r0
add r0, r1

ldi r2, 0x031F
st r2, r0
add r0, r1

ldi r2, 0x039F
st r2, r0
add r0, r1

ldi r2, 0x03FF
st r2, r0
add r0, r1

ldi r2, 0x03F8
st r2, r0
add r0, r1

ldi r2, 0x03F0
st r2, r0
add r0, r1

ldi r2, 0x03E8
st r2, r0
add r0, r1

ldi r2, 0x03E0
st r2, r0
add r0, r1

ldi r2, 0x13E0
st r2, r0
add r0, r1

ldi r2, 0x23E0
st r2, r0
add r0, r1

ldi r2, 0x33E0
st r2, r0
add r0, r1

ldi r2, 0x43E0
st r2, r0
add r0, r1

ldi r2, 0x53E0
st r2, r0
add r0, r1

ldi r2, 0x63E0
st r2, r0
add r0, r1

ldi r2, 0x73E0
st r2, r0
add r0, r1

ldi r2, 0x7FE0
st r2, r0
add r0, r1

ldi r2, 0x7F80
st r2, r0
add r0, r1

ldi r2, 0x7F20
st r2, r0
add r0, r1

ldi r2, 0x7EC0
st r2, r0
add r0, r1

ldi r2, 0x7E60
st r2, r0
add r0, r1

ldi r2, 0x7E00
st r2, r0
add r0, r1

ldi r2, 0x7DA0
st r2, r0
add r0, r1

ldi r2, 0x7D40
st r2, r0
add r0, r1

ldi r2, 0x7CE0
st r2, r0
add r0, r1

ldi r2, 0x7C80
st r2, r0
add r0, r1

ldi r2, 0x7C40
st r2, r0
add r0, r1

ldi r2, 0x7C00
st r2, r0
add r0, r1

ldi r2, 0x7C08
st r2, r0
add r0, r1

ldi r2, 0x7C10
st r2, r0
add r0, r1

ldi r2, 0x7C18
st r2, r0
add r0, r1

ldi r2, 0x7C1F
st r2, r0
add r0, r1

ldi r2, 0x6C1F
st r2, r0
add r0, r1

ldi r2, 0x5C1F
st r2, r0
add r0, r1

ldi r2, 0x4C1F
st r2, r0
add r0, r1

ldi r2, 0x3C1F
st r2, r0
add r0, r1

ldi r2, 0x2C1F
st r2, r0
add r0, r1

ldi r2, 0x1C1F
st r2, r0
add r0, r1

ldi r2, 0x0C1F
st r2, r0
add r0, r1

ldi r2, 0x1C7F
st r2, r0
add r0, r1

ldi r2, 0x2CDF
st r2, r0
add r0, r1

ldi r2, 0x3D3F
st r2, r0
add r0, r1

ldi r2, 0x4D9F
st r2, r0
add r0, r1

ldi r2, 0x5DFF
st r2, r0
add r0, r1

ldi r2, 0x6E5F
st r2, r0
add r0, r1

ldi r2, 0x7EBF
st r2, r0
add r0, r1

ldi r2, 0x7F1F
st r2, r0
add r0, r1

ldi r2, 0x7F5F
st r2, r0
add r0, r1

ldi r2, 0x7F9F
st r2, r0
add r0, r1

ldi r2, 0x7FDF
st r2, r0
add r0, r1

ldi r2, 0x7FFF
st r2, r0
add r0, r1

ldi r2, 0x0000
st r2, r0

pop r2
pop r1
pop r0
ret
