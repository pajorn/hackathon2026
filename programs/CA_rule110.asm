call white_screen

; set initial pixel
ldi r1, 0xC07F ; far right
ldi r0, 0x0000 ; black
st r0, r1

ldi r1, 0x7FFF ; white
ldi r2, 0xC000 ; pixels
ldi r3, 0x0001 ; row
ldi r5, 0x0001
ldi r6, 0x0080 ; n cols/rows

main_loop:
call update_row
add r3, r5	; inc row
cmp r3, r6
brlt main_loop

; forever
a:
jmp a


update_row:
ldi r4, 0x0000 ;  col
next_col:
; setup address
mov r10, r3
sub r10, r5
mul r10, r6
add r10, r4
add r10, r2
ld r8, r10	; read up centre

mov r7, r1	; make left white
cmp r4, r0
breq left_edge
; here col != 0, so read up left
sub r10, r5
ld r7, r10
add r10, r5
left_edge:

mov r9, r1
sub r6, r5
cmp r4, r6
breq right_edge
; here col != 127, so read up right
add r10, r5
ld r9, r10
sub r10, r5
right_edge:
add r6, r5

; compute
;xor r7, r1
xor r8, r1
xor r9, r1

xor r9, r8
and r8, r7
or r8, r9

xor r8, r1

; write
add r10, r6
st r8, r10

add r4, r5	; inc col
cmp r4, r6
brlt next_col
ret


white_screen:
push r0
push r1
push r2
push r3
ldi r0, 0x7FFF ; white
ldi r1, 0xC000 ; pixel index
ldi r2, 0x0001
ldi r3, 0xC000 ; first pixel
white_again:
st r0, r1
add r1, r2 ; next pixel
cmp r1, r3
brlt done
jmp white_again
done:
pop r3
pop r2
pop r1
pop r0
ret
