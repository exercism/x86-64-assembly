section .data
protein_names:
   Methionine     db "Methionine", 0
   Phenylalanine  db "Phenylalanine", 0
   Leucine        db "Leucine", 0
   Serine         db "Serine", 0
   Tyrosine       db "Tyrosine", 0
   Cysteine       db "Cysteine", 0
   Tryptophan     db "Tryptophan", 0

codon_map:
   db "AUG", 0
   db "UUU", 1, "UUC", 1
   db "UUA", 2, "UUG", 2
   db "UCU", 3, "UCC", 3, "UCA", 3, "UCG", 3
   db "UAU", 4, "UAC", 4
   db "UGU", 5, "UGC", 5
   db "UGG", 6
   db "UAA", 7, "UAG", 7, "UGA", 7
   db 0

protein_list: dq Methionine, Phenylalanine, Leucine, Serine, Tyrosine, Cysteine, Tryptophan, 0

section .bss
output: resq 10

section .text

global proteins
proteins:                 ;;extern const char **proteins(const char *rna);
   push rbx
   cld
   lea rdx, [rel output]
   xor eax, eax           ; clear upper bits
.next_codon:
   mov rbx, rdi           ; after call to find_codon, rdi points to the next codon
   call find_codon
   test esi, esi
   je .terminate
   mov byte al, [rsi]
   cmp al, 7              ; STOP codon
   je .terminate
   lea rbx, [rel protein_list]
   mov rbx, [rbx + 8*rax] 
   mov qword [rdx], rbx
   add rdx, 8
   jmp .next_codon
.terminate:
   mov qword [rdx], 0
   lea rax, [rel output]
   pop rbx
   ret

find_codon:               ; in: rbx ; out: rsi, rdi ; uses: rcx
   lea rsi, [rel codon_map-1]
.next_codon:
   mov rdi, rbx           ; rbx points to the current codon
   inc rsi
   cmp byte [rsi], 0
   je .invalid_codon
.check_codon:
   mov ecx, 3
   repe cmpsb
   je .codon_found
   add rsi, rcx
   jmp .next_codon
.codon_found:
   ret                    ; rsi points to the codon nr, rdi points to the next codon
.invalid_codon:
   xor esi, esi
   ret 

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif

