section .data
earth_year_in_sec: dd 31557600.0

orbital_periods:
dd 0.2408467  ; Mercury
dd 0.61519726 ; Venus
dd 1.0        ; Earth
dd 1.8808158  ; Mars
dd 11.862615  ; Jupiter
dd 29.447498  ; Saturn
dd 84.016846  ; Uranus
dd 164.79132  ; Neptune

section .text
global age
age:
    mov rax, orbital_periods
    movss xmm1, [rax + rdi * 4]
    mulss xmm1, [rel earth_year_in_sec]

    cvtsi2ss xmm0, esi
    divss xmm0, xmm1
    ret
