default rel

section .rodata
earth_year_in_sec: dd 31557600.0

orbital_periods:
dd 0.2408467   ; Mercury
dd 0.61519726  ; Venus
dd 1.0         ; Earth
dd 1.8808158   ; Mars
dd 11.862615   ; Jupiter
dd 29.447498   ; Saturn
dd 84.016846   ; Uranus
dd 164.79132   ; Neptune

;
; Given an age in seconds, calculate how old someone is in terms of a given
; planet's solar years.
;
; Parameters:
;   rdi - planet
;   rsi - seconds
; Returns:
;   xmm0 - age
;
section .text
global age
age:
    lea rax, [orbital_periods]       ; Load orbital periods
    movss xmm1, [rax + rdi * 4]      ; Read orbital period
    mulss xmm1, [earth_year_in_sec]  ; Multiply by earth year

    cvtsi2ss xmm0, esi               ; Convert seconds to float
    divss xmm0, xmm1                 ; Divide by orbital period
    ret
