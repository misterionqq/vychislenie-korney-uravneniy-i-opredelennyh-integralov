section .data
    ; Constants for calculation
    three   dq 3.0
    two     dq 2.0
    one     dq 1.0
    e_const dq 2.71828182845904523536

section .text
    global f1, f2, f3

;==============================//
; Function double f1(double x) //
; Computes e^(-x) + 3          //
;==============================//

f1:
    ; Prologue
    push    ebp
    mov     ebp, esp
    sub     esp, 8

    ; Load argument x into FPU
    fld     qword [ebp+8]

    ; Calculate -x
    fchs

    ; Load e constant and compute e^(-x)
    fld     qword [e_const]
    fyl2x               ; st1 = st1 * log2(st0) (st1 = -x*log2(e), st0 pushed out
    fld1                ; Load constant 1
    fld     st1         ; Load st1 (-x*log2(e))
    fprem               ; st0 = reminder of st0 / st1 (Fractional part of -x*log2(e)) (Needed because f2xm1 requires value from (-1:1)
    f2xm1               ; st0 = 2^st0 - 1
    faddp   st1, st0    ; st1 = st1 + st0, st0 pushed out (Now, st0 = 2^(Fractional part of -x*log2(e)))
    fscale              ; st0 = st0 * 2^st1 (Now, st0 = 2 ^ (Fractional part of -x*log2(e) + Integer part of -x*log2(e)), I.e. -x*log2(e))
    fstp    st1         ; Move st0 to st1 (Now st1 is st0)

    ; Add 3
    fld     qword [three]
    faddp   st1, st0

    ; Return result
    fstp    qword [esp]
    fld     qword [esp]

    ; Epilogue
    leave
    ret

;;==============================//
;; Function double f2(double x) //
;; Computes 2x-x                //
;;==============================//

f2:
    ; Prologue
    push    ebp
    mov     ebp, esp
    sub     esp, 8

    ; Load argument x into FPU
    fld qword [ebp+8]

    ; Compute 2x
    fld qword [two]
    fmulp st1, st0

    ; Subtract 2
    fld qword [two]
    fsubp st1, st0

    ; Return result
    fstp qword [esp]
    fld qword [esp]

    ; Epilogue
    leave
    ret

;;==============================//
;; Function double f2(double x) //
;; Computes 2x-x                //
;;==============================//

f3:
    ; Prologue
    push ebp
    mov ebp, esp
    sub esp, 8

    ; Load argument x into FPU
    fld qword [ebp+8]

    ; Compute 1/x
    fld1
    fdivrp st1, st0

    ; Return result
    fstp qword [esp]
    fld qword [esp]

    ; Epilogue
    leave
    ret
