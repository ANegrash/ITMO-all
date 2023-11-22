section .text

extern string_equals
extern print_string
global find_word

; rsi - dict, rdi - str
; rax - error - 0
; rax - result - rsi
;----------------------------------
; for i in list:
;   r = string_equals(get_key(i), rdi)
;   if r:
;       jmp find
; ret 0
; .find:
; ret get_value(i)
find_word:
.loop:
    push rdi
    push rsi
    add rsi, 8
    call string_equals
    pop rsi
    pop rdi
    test rax, rax
    jne .t_end
    mov r8, [rsi]
    mov rsi, r8
    test rsi, rsi
    jne .loop
.f_end:
    xor rax, rax
    ret
.t_end:
    mov rax, rsi
    ret