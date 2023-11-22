section .text
 
 
; Принимает код возврата и завершает текущий процесс
exit: 
    mov rax, 60
    syscall
    
; Принимает указатель на нуль-терминированную строку, возвращает её длину
string_length:  
    xor rax, rax
.loop:
	cmp byte [rdi + rax], 0
	je .end
	inc rax
	jmp .loop
.end:
	ret	


    
; Принимает указатель на нуль-терминированную строку, выводит её в stdout
; Принимает указатель на нуль-терминированную строку, выводит её в stdout
print_string:
    call string_length
    mov rdx, rax
    mov rax, 1
    mov rsi, rdi
    mov rdi, 1
    syscall
    ret

    
; Принимает код символа и выводит его в stdout
%define ONE 1
print_char:
    push rdi
    mov rax, ONE
    mov rdi, ONE
    mov rsi, rsp
    mov rdx, ONE
    syscall     
    pop rdi     
    ret


; Переводит строку (выводит символ с кодом 0xA)
%define NEW_LINE_SYMB 0xA
print_newline:
    mov rdi, NEW_LINE_SYMB  ; Символ переноса строки
    jmp print_char          ; Вывод символа

    
; Выводит беззнаковое 8-байтовое число в десятичном формате 
; Совет: выделите место в стеке и храните там результаты деления
; Не забудьте перевести цифры в их ASCII коды.
%define BUFFER_SIZE1 16
%define BUFFER_SIZE2 24
print_uint:
    mov r9, 10          ; Основание 10-чной системы счисления
    mov rax, rdi    
    mov rdi, rsp    
    dec rdi         
    push 0              ; Символ окончания строки
    sub rsp, BUFFER_SIZE1; Выделения буфера в стеке для строки
.loop:
    xor rdx, rdx        ; Обнуление rdx
    div r9              ; Целочисленное деление на 10
    add rdx, '0'        ; Прибавление к остатку кода символа "0" для получения кода необходимого символа
    dec rdi             ; Уменьшения указателя на текущий записываемый символ
    mov byte[rdi], dl   ; Запись символа в буфер
    test rax, rax       ; Проверка, продолжать ли вычисление 10-чной записи числа
    jnz .loop           ; Если да, то переход на .loop
    call print_string   ; Вывод строки
    add rsp, BUFFER_SIZE2; Возврат стека в исходное состояние
    ret

    
; Выводит знаковое 8-байтовое число в десятичном формате 
print_int:
    cmp rdi, 0          ; Определение знака числа
    jge .positive       ; Если положительное - пропуск инструкций необходимых для вывода отрицательного числа
    push rdi            ; Положить в стек число
    mov rdi, '-'        ; Код символа минус
    call print_char     ; Вывод символа минус
    pop rdi             ; Достать из стека число
    neg rdi             ; Получить противоположное число
.positive:
    jmp print_uint      ; Вывод беззнакового целого числа
                        ; Распологать друг за другом без jmp не хочу, ибо меня это немного 
                        ; вводит в заблуждение с точки зрения читаемости


; Принимает два указателя на нуль-терминированные строки, возвращает 1 если они равны, 0 иначе
string_equals:
    call string_length          ; Если длины строк не равны,
    mov rdx, rax                ; то строки не равны
    xchg rdi, rsi
    call string_length
    cmp rdx, rax
    jne .false
.loop:
    mov dl, byte[rdi + rcx]     ; Побайтовое сравнение строк:
    cmp dl, byte[rsi + rcx]     ; если соотв. байты не равны,
    jne .false                  ; то строки не равны
    cmp dl, 0                   ; Если не достигнут конец строки,
    jne .loop                   ; то переход к следующей итерации
    inc rcx
    mov rax, 1                  ; 1 - строки равны
    ret                         ; Возврат
.false:
    xor rax, rax                ; 0 - строки не равны
    ret                         ; Возврат

; Читает один символ из stdin и возвращает его. Возвращает 0 если достигнут конец потока
read_char:
    xor rdi, rdi
    push 0
    xor rax, rax
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
%define SPACE_SYMB 0x20
%define TAB_SYMB 0x9
%define ENDL_SYMB 0xA

read_word:
     xor rcx, rcx           
.loop:
    push rdi                
    push rsi
    push rcx
    call read_char          ; Чтение символа
    pop rcx                 ; Снимаем данные из стека
    pop rsi
    pop rdi
    cmp rax, SPACE_SYMB           ; Проверяем не пробел ли это 
    je .whitespace
    cmp rax, TAB_SYMB
    je .whitespace
    cmp rax, ENDL_SYMB
    je .whitespace
    cmp rax, 0              ; Проверяем на конец ввода
    je .end
    mov [rdi + rcx], rax    ; Сохраняем символ
    inc rcx                 ; Увеличиваем счетчик длины на 1
    cmp rcx, rsi            ; Проверка на переполнение буфера
    jge .err
    jmp .loop
.whitespace:
    cmp rcx, 0              ; Если начало слова, то пропускаем пробельные символы,
    je .loop                ; Иначе завершаем ввод слова
    jmp .end
.err:
    xor rax, rax            ; Обнуление возвращаемых значений
    xor rdx, rdx            ; и возврат при ошибке
    ret
.end:
    xor rax, rax            ; Запись в память нуль-терминатора
    mov [rdi + rcx], rax
    mov rax, rdi            ; Адрес буфера в rax
    mov rdx, rcx            ; Записываем длину строки в rdx
    ret                     ; Возвращаемся из функции
 

; Принимает указатель на строку, пытается
; прочитать из её начала беззнаковое число.
; Возвращает в rax: число, rdx : его длину в символах
; rdx = 0 если число прочитать не удалось
parse_uint:
    push rbx
    xor rdx, rdx
    xor rax, rax
    xor rbx, rbx
.loop:
    mov bl, byte [rdi + rdx]
    cmp bl, '0' 
    jl .end
    cmp bl, '9'
    jg .end
    sub bl, '0'    ; конвертим в число
    push rdx
    mov rdx, 10
    mul rdx
    pop rdx
    add rax, rbx
    inc rdx         ; length++
    jmp .loop
.end:
    pop rbx
    ret             ; Возвращаемся из функции

    
; Принимает указатель на строку, пытается
; прочитать из её начала знаковое число.
; Если есть знак, пробелы между ним и числом не разрешены.
; Возвращает в rax: число, rdx : его длину в символах (включая знак, если он был) 
; rdx = 0 если число прочитать не удалось
parse_int:
    mov r8, 10                  ; r8 = 10 для умножения на 10
    xor rcx, rcx                ; len = 0
    xor rax, rax                ; rax = 0, будет аккумулировать число
    push 1                      ; is_positive = [rsp] = 1
.loop:
    movzx r9, byte [rdi + rcx] ; r9 = buff[len]
    cmp r9b, '-'                ; if(r9 == '-') goto .minus
    je .minus
    cmp r9b, '0'                ; если r9 не содержит число, то 
    jb .check  ; goto .check
    cmp r9b, '9'
    ja .check
    xor rdx, rdx                ; rax = rax * 10
    mul r8
    sub r9b, '0'                ; r9 теперь содержит цифру, а не ее код
    add rax, r9                 ; rax = rax + r9
.continue:
    inc rcx    ; len++
    jmp .loop 
.minus:
    mov r10, 0 ; is_positive = 0
    mov [rsp], r10 
    jmp .continue 
.check:
    pop r10 ; if(!is_positive) goto .neg
    cmp r10, 0
    je .neg 
    jmp .end
.neg:
    neg rax 
    jmp .end
.end:
    mov rdx, rcx 
    ret



; Принимает указатель на строку, указатель на буфер и длину буфера
; Копирует строку в буфер
; Возвращает длину строки если она умещается в буфер, иначе 0
string_copy:
    call string_length      ; Определение длины строки
    inc rax                 ; Увеличим, так как дописываем \0 
    cmp rax, rdx            ; Сравнение длины строки и размера буфера
    jg .small_buffer        ; Если длина строки больше размера буфера - переход к возврату нуля
    xor rcx, rcx            
.loop:
    mov rdx, [rdi + rcx]    ; Запись в rdx текущего элемента строки
    mov [rsi + rcx], rdx    ; Запись в буфер текущего элемента строки
    inc rcx                 ; Инкремент счетчика
    cmp byte[rdi + rcx], 0  ; Смотрим, достигли ли терминатора
    jne .loop               ; Если не достигли, то повторение итерации цикла
    ret
.small_buffer:
    xor rax, rax            ; Обнуление rax
    ret

