ldi r3, 0x000A
ldi r4, 0x0010;
ldi r5, 0x0001 ;
here:
add r3, r4; 
jmp abcde ; hi
push r0
abcde:
add r3, r5
jmp here

ldi r0, 0x0123
