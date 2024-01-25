; Copia uma string numa outra
; Compilar com: nasm -f elfx T1LucasRochaLM.asm (onde x é o sistema, 32 ou 64 bits)
; Linkar com : ld T1LucasRochaLM.o -o trabalho
; Executar com: ./T1LucasRochaLM

SECTION .data
    arqInput db "entrada.txt",0
    arqOutput db "saida.dat",0
    strInput times 30    db  "Hoje e festa na computacao, oba!",0Ah,0h
    strSub times 10    db  "casa do Joazinho",0h      ; substring para ser substituida
    strBusca                db  "computacao",0h   ;substring a ser localizada
    auxIndex         db    0
    indexInit         db    0
    aux_text   times 100   db  0
    indexEnd          db    0
    fd db 0
    slenght           equ   16    ; tamanho da frase casa do Joazinho
    alenght           equ   $- aux_text
    SCREEN            equ   1
    sublenght         equ   10    ; tamanho da palavra computação
    flenght           equ   33    ; tamanho da frase de entrada
    ;end .data

section .bss
    strRead resb 0 ;string para ler do arquivo

; COPIA UMA STRING PARA UMA OUTRA
; %1: a string source
; %2 a string de destino
%macro _strcpy 2

    push    rbx
    push    rdx
    push    rax

    mov     rbx, %1
    mov     rdx, %2

    xor     esi, esi

    %%copy:
        xor     rax, rax
        cmp     byte [ebx+esi], 0
        jz      %%endcopy

        mov     byte al, [ebx+esi]
        mov     byte [edx+esi], al
        inc     esi
        jmp     %%copy
    %%endcopy:
        pop     rax
        pop     rdx
        pop     rbx
%endmacro

; COPIA N CARACTERES DUMA STRING PARA UMA OUTRA
; %1 a string de destino
; %2 a string source
; %3 indice para o inicio da copia na string source
; %4 indice para o fim da copia na string source
; %5 indice para o inicio de armazenamento na string destino
%macro _strncpy 5

    push  rax
    push  rcx
    push  rdx
    push  rbx

    xor ebx,ebx
    xor esi,esi
    xor edi,edi
    mov   rcx, %1
    mov   rdx, %2
    mov   esi, %3
    mov   edi, %4
    mov   ebx, %5

    %%copy:
        xor     rax, rax
        cmp     esi, edi
        je      %%endcopy

        mov     byte al, [edx+esi]
        mov     byte [ecx+ebx], al
        inc     esi
        inc     ebx
        jmp     %%copy
    %%endcopy:
        pop rbx
        pop rdx
        pop rcx
        pop rax
%endmacro

; LOCALIZAR UMA SUBSTRING NUMA STRING
; %1 a string a ser scaneada
; %2 a substring a ser localizada
; %3 retornar indice da primeira ocorrencia da substring na string maior
%macro _strstr 3
    push rax
    push rbx
    push rcx
    push rdx

    mov   rdx, %1
    mov   rbx, %2

    xor  esi, esi
    xor  edi, edi

  %%occurence:
      xor  rax, rax
      cmp   byte [ebx+edi], 0
      jz    %%finished
      mov   byte al,[ebx+edi]
      jmp   %%strncmp

  %%strncmp:
      cmp     byte [edx+esi], 0
      jz      %%finished
      cmp     byte [edx+esi], al
      je      %%isEquals

      cmp     edi, 0
      jne     %%retry

      inc     esi
      jmp     %%strncmp

  %%retry:
      xor     edi, edi
      mov [%3], edi
      jmp %%occurence

  %%isEquals:
      cmp   byte [%3], 0
      je    %%init
      inc   esi
      inc   edi
      jmp   %%occurence

      %%init:
          mov [%3] , esi
          inc   esi
          inc   edi
          jmp   %%occurence

  %%finished:
      pop rdx
      pop rcx
      pop rbx
      pop rax
%endmacro

; PRINTA UMA STRING
; %1 a string
; %2 tamanho da string
%macro _printer 2

    push rax
    push rbx
    push rcx
    push rdx

    mov     rdx, %2
    mov     rcx, %1
    mov     rbx, SCREEN
    mov     rax, 4
    int     80h

    pop rdx
    pop rcx
    pop rbx
    pop rax

%endmacro

;SAIR 
%macro _exit 0
    mov    rbx, 0
    mov    rax, 1
    int    80h
%endmacro


SECTION .text
global  _start

_start:

_printer strInput, flenght

_strstr strInput, strBusca, indexInit

;cria arquivo
mov rax,2
mov rdi,arqInput
mov rsi,64
mov rdx,1
mov [fd],rax
syscall

;armazenar no arquivo                 
mov rax,1
mov rdi,[fd]
mov rsi,strInput
mov rdx,flenght 
syscall

;fecha arq
mov rax,3
mov rdi,arqInput
syscall

;ABRE PARA LEITURA
mov rax,2
mov rdi,arqInput
mov rsi,64
mov rdx,0
syscall

mov [fd],rax

;leitura do arq
mov rax,0
mov rdi,[fd]
mov rsi,strRead
mov rdx,flenght
syscall

;fecha arq
mov rax,3
mov rdi,arqInput
syscall

;printa conteudo do arq
_printer strRead, flenght

; COPIA A PRIMEIRA PARTE DA STRING DE ORIGEM E DEPOIS CONCATENAR COM A PALAVRA DE SUBSTITUICAO
; %1 a string de destino
; %2 a string source
; %3 indice para o inicio da copia na string de origem
; %4 indice para o fim da copia na string de origem
; %5 indice para o inicio de armazenamento na string destino
_strncpy aux_text, strInput, 0, [indexInit-0], 0
_strncpy aux_text, strSub, 0, slenght, [indexInit-0]


mov eax, [indexInit-0]          ;indice da primeira ocorrencia na eax como int
add eax, slenght                ;soma o tamanho da substring localizada para descartar ela da copia

push rax                        ;guarda o valor na pilha

mov eax, [indexInit-0]          ;indice da primeira ocorrencia na eax como int
add eax, sublenght              ;soma o tamanho da substring substituida para não sobre escrever

pop rcx                         ;pega o indice para continua a copia da string de origem

mov [indexEnd], ecx

; COPIA O RESTANTE DA STRING SOURCE
; %1 a string de destino
; %2 a string de origem
; %3 indice para o inicio da copia na string de origem
; %4 indice para o fim da copia na string de origem
; %5 indice para o inicio de armazenamento na string destino
_strncpy aux_text, strInput, eax, flenght,[indexEnd]

;armazena a alteracao no arquivo de saida
;cria arquivo de saida
mov rdi,arqOutput
mov rsi,1
mov rdx,1
mov rax,2
mov [fd],rax
syscall

;armazenar no arquivo de saida              
mov rax,1
mov rdi,[fd]
mov rsi,aux_text
mov rdx,alenght
syscall

;fecha arquivo de saida
mov rax,3
mov rdi,arqOutput
syscall

_printer aux_text, alenght   ;printa a string de destino
_exit