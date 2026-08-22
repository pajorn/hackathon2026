ldi r0, 0xC000 ; current pixel
ldi r1, 0xC000 ; beginning of mem
ldi r2, 0x7C00 ; pixel colour
ldi r3, 0x0001
ldi r4, 0xFFFF ; some ones

hi:
st r2, r0 ; set pixel
add r0, r3 ; increment pixel

cmp r0, r1
brlt reposition
jmp hi

reposition:
mov r0, r1 ; return to start of pixels
call change_colour
jmp hi

change_colour:
push r1
ldi r1, 0x7C00
cmp r2, r1
breq red
jmp not_red
red:
ldi r2, 0x03E0
jmp colour_done
not_red:
ldi r1, 0x03E0
cmp r2, r1
breq green
jmp not_green
green:
ldi r2, 0x001F
jmp colour_done
not_green: ; must be blue
ldi r2, 0x7C00
colour_done:
pop r1
ret
