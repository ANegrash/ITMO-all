section .text

global exit
global string_length
global print_string
global print_newline
global print_char
global print_uint
global print_int
global string_equals
global read_char
global print_error
global read_word
global parse_uint
global parse_int
global string_copy
global print_string_err

%define SYS_READ 0x0
%define SYS_WRITE 0x1
%define SYS_EXIT 0x3C
%define DES_STDOUT 0x1
%define DES_STDIN 0x0
%define DES_STDERR 0x2
%define TAB 0x9
%define NEW_LINE 0xA
%define SPACE 0x20
%define DEC 0xA
%define ASCII_0 0x30
%define ASCII_9 0x39
%define LINE_END 0x0
%define MINUS 0x2D
%define PLUS 0x2B

; Принимает код возврата и завершает текущий процесс
exit:
    mov     rax, SYS_EXIT
    xor     rdi, rdi
    syscall


; Принимает указатель на нуль-терминированную строку, возвращает её длину
; rdi - buffer pointer, return size in rax
; --------------------------------
; while not null-term
; i++
string_length:
    xor rax, rax
.loop:
    cmp byte [rdi+rax], LINE_END
    je .end
    inc rax
    jmp .loop
.end:
    ret


print_string_err:
    call string_length
    mov rsi, rdi
    mov rdx, rax
    mov rax, 1
    mov rdi, DES_STDERR
    syscall
    ret


; Принимает указатель на нуль-терминированную строку, выводит её в stdout
; rdi - pointer
; --------------------------------
; get length by string_length
; call printf
print_string:
    call string_length
    mov rsi, rdi
    mov rdx, rax
    mov rax, SYS_WRITE
    mov rdi, DES_STDOUT
    syscall
    ret


; Переводит строку (выводит символ с кодом 0xA)
print_newline:
    mov rdi, NEW_LINE


; Принимает код символа и выводит его в stdout
; rdi - code
; --------------------------------
; push code on stack
; call printf
print_char:
    push rdi
    mov rsi, rsp
    mov rdx, 1
    mov rax, SYS_WRITE
    mov rdi, DES_STDOUT
    syscall
    pop rdi
    ret


; Выводит знаковое 8-байтовое число в десятичном формате
; rdi - num
; --------------------------------
; check if neg
; if true: printf -
;   neg i
; call print_uint with i
print_int:
    mov rax, rdi
    test rax, rax
    jns print_uint
    push rdi
    mov rdi, MINUS
    call print_char
    pop rdi
    neg rdi


; Выводит беззнаковое 8-байтовое число в десятичном формате
; Совет: выделите место в стеке и храните там результаты деления
; Не забудьте перевести цифры в их ASCII коды.
; rdi - number
; --------------------------------
; alloc 3 numbers a[]
; for 3:
; a[0] = r mod by ten
; r = r div by ten
; if r == 0: set current pos in stack variable
; start from stack variable
; get a[stack variable]
; a[...]+48
; printf
print_uint:
    push rsi
    push r10
    push r9
    mov r10, DEC
    mov r9, rsp
    xor rsi, rsi
    dec rsp
    mov byte [rsp], 0x0
    mov rax, rdi
.loop:
    xor rdx, rdx
    div r10
    add rdx, ASCII_0
    dec rsp
    mov byte [rsp], dl ; rdx - edx  dx = dh + dl
    inc rsi
    test rax, rax
    jnz .loop
    test rsi, rsi
    jz .end
    mov rdi, rsp
    call print_string
.end:
    mov rsp, r9
    pop r9
    pop r10
    pop rsi
    ret


; Принимает два указателя на нуль-терминированные строки, возвращает 1 если они равны, 0 иначе
; rdi - s1, rsi - s2
; rax - result
; --------------------------------
; while s1[i] != '\0'
;   if s1[i] != s2[i]
;       break and return 0
; if s1[i] == s2[i] == '\0'
;   return 1
; else
;   return 0
string_equals:
    xor rax, rax
    xor r8, r8
    xor r9, r9
.loop:
    mov r9b, byte [rdi+rax]
    mov r8b, byte [rsi+rax]
    cmp r9, r8
    jne .n_e
    test r9, r9
    jz .e
    inc rax
    jnz .loop
.e:
    mov rax, 1
    jmp .end
.n_e:
    mov rax, 0
.end:
    ret

; Читает один символ из stdin и возвращает его. Возвращает 0 если достигнут конец потока
; rax - return
; --------------------------------
; call read
; if r == '\0'
;   return 0
; else: return r
read_char:
    push 0
    mov rax, SYS_READ
    mov rdi, DES_STDIN
    mov rsi, rsp
    mov rdx, 1
    syscall
    pop rax
    ret

; Принимает: адрес начала буфера, размер буфера
; Читает в буфер слово из stdin, пропуская пробельные символы в начале, .
; Пробельные символы это пробел 0x20, табуляция 0x9 и перевод строки 0xA.
; Останавливается и возвращает 0 если слово слишком большое для буфера
; При успехе возвращает адрес буфера в rax, длину слова в rdx.
; При неудаче возвращает 0 в rax
; Эта функция должна дописывать к слову нуль-терминатор
; rdi - buf, rsi - size
; rax - buf or 0, rdx - size
; --------------------------------
; before call set buffer and size
; while true:
;   call read_char
;   if not 0x20, 0x9, 0xA:
;   break
; i = 0
; while i < size
; call read_char
; if '\0':
;   s[i] = '\0'
;   rax = s, rdx = i
;   return
; else s[i] = r
; endwhile
; rax = 0
; return
read_word:
    push rdi
    push rsi
    mov r8, rdi
    xor r9, r9
.loop1:
    call read_char
    cmp rax, TAB
    je .loop1
    cmp rax, NEW_LINE
    je .loop1
    cmp rax, SPACE
    je .loop1
    jmp .g
.loop2:
    call read_char
.g:
    cmp r9, [rsp]
    ja .f_end
    mov byte [r8+r9], al
    inc r9
    cmp rax, TAB
    je .t_end
    cmp rax, NEW_LINE
    je .t_end
    cmp rax, SPACE
    je .t_end
    cmp rax, LINE_END
    jne .loop2
.t_end:
    mov rax, r8
    dec r9
    mov rdx, r9
    mov byte [r8+r9], 0
    jmp .end
.f_end:
    xor rax, rax
.end:
    pop rsi
    pop rdi
    ret


; Принимает указатель на строку, пытается
; прочитать из её начала беззнаковое число.
; Возвращает в rax: число, rdx : его длину в символах
; rdx = 0 если число прочитать не удалось
; rdi - pointer
; --------------------------------
; before call set str, set size as prev registers
; for i in size:
;   if s[i] > 47 and < 57:
;       acc * 10
;       acc += s[i]-47
;   else if i > 0
;       rax = acc, rdx = i
;       return
;   else
;       rdx = 0
;       return
parse_uint:
    push rbx
    xor rax, rax
    xor rbx, rbx
    xor rcx, rcx
    mov r10, DEC
    mov r11, ASCII_0
.loop:
    mov al, byte [rdi+rbx]
    cmp rax, ASCII_9
    ja .stop
    cmp rax, ASCII_0
    jb .stop
    sub rax, r11
    push rax
    mov rax, rcx
    mul r10
    mov rcx, rax
    pop rax
    add rcx, rax
    inc rbx
    jmp .loop
.stop:
    test rbx, rbx
    je .w_end
    mov rdx, rbx
    mov rax, rcx
    jmp .end
.w_end:
    xor rdx, rdx
.end:
    pop rbx
    ret


; Принимает указатель на строку, пытается
; прочитать из её начала знаковое число.
; Если есть знак, пробелы между ним и числом не разрешены.
; Возвращает в rax: число, rdx : его длину в символах (включая знак, если он был)
; rdx = 0 если число прочитать не удалось
; rdi - pointer
; --------------------------------
; s = true
; call read_char
; if r == -:
;     i++
;     s = false
; else if s == +:
;     i++
; else if r > 47 and < 57:
;     acc += r
; else:
;     rdx = 0
;     return
; call parse_uint
; acc = acc*10^size + r
; rax = acc, rdx = size + i
; return
parse_int:
    push rdi
    xor r8, r8
    xor r9, r9
    xor rax, rax
    mov al, byte [rdi]
    cmp rax, PLUS ; +
    je .pos
    cmp rax, MINUS ; -
    je .neg
.pos1:
    call parse_uint
    test rdx, rdx
    je .fail
    test r8, r8
    je .p
    neg rax
.p:
    test r9, r9
    je .end
    inc rdx
    jmp .end
.fail:
    xor rax, rax
.end:
    pop rdi
    ret
.neg:
    mov r8, 0x1
.pos:
    inc r9
    inc rdi
    jmp .pos1

; Принимает указатель на строку, указатель на буфер и длину буфера
; Копирует строку в буфер
; Возвращает длину строки если она умещается в буфер, иначе 0
; rdi - copy, rsi - pointer_buf, rdx - size
; --------------------------------
; call string_length
; if r > size
;     return 0
; else:
;     for i in r:
;       p_b[i] = p_s[i]
; return r
string_copy:
    push rbx
    call string_length ; calc length entered str
    cmp rax, rdx
    ja .f_end
    xor rbx, rbx
.loop:
    mov cl, [rdi+rbx]
    mov [rsi+rbx], cl
    cmp rbx, rax
    je .end
    inc rbx
    jmp .loop
.f_end:
    xor rax, rax
    jmp .e
.end:
    mov rax, rbx
.e:
    pop rbx
    ret