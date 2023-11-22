%include "colon.inc"
%include "words.inc"

%define SIZE_OF_BUF 255
%define BYTES_SIZE 8
%define ONE 1

global _start

extern find_word
extern exit
extern print_string
extern print_newline
extern read_word
extern print_newline
extern print_string_err

section .rodata
hel:    db "Enter key: ", 0
rig:    db "Key find. Value is: ", 0
e_size: db "Error: max symb number is 255", 0xA, 0
e_name: db "Error: doesn't have that key", 0xA, 0

section .bss
buf: times SIZE_OF_BUF db 0

section .text

; call read_word
; if !rax:
;   print_string(error_size_mes)
; call find_word
; if rax:
;   print_string(all_right+value)
; else:
;   print_string(error_name_key)
_start:
    mov rdi, hel
    call print_string
    mov rdi, buf
    mov rsi, SIZE_OF_BUF
    call read_word
    test rax, rax
    je .s_end
    mov rsi, next_el
    mov rdi, rax
    push rdx
    call find_word
    pop rdx
    test rax, rax
    je .w_end
    add rax, BYTES_SIZE
    mov rdi, rax
    push rdi
    mov rdi, rig
    push rdx
    call print_string
    pop rdx
    pop rdi
    add rdi, ONE
    add rdi, rdx
    call print_string
    call print_newline
    jmp .end
.w_end:
    mov rdi, e_name
    call print_string_err
    jmp .end
.s_end:
    mov rdi, e_size
    call print_string_err
    jmp .end
.end:
    call exit
