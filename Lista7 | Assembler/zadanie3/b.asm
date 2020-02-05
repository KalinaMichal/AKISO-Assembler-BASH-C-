section .data
  scan: db "%lf", 0
  print: db "%lf", 10, 0

section .bss
  i resb 0
  
section .text
  global main
  extern printf
  extern scanf

main:
  push i
  push scan
  call scanf
  
  finit
  fld qword [i]	;st(0) = x
  fld qword [i]	;st(0) = x | st(1) = x
  fmulp 		;st(0) = x^2
  fld1			;st(1) = x^2 | st(0) = 1
  faddp			;st(0) = x^2 + 1
  fsqrt			;st(0) = sqrt(x^2+1)
  fld qword [i]	;st(1) = sqrt(x^2+1) | st(0) = x
  faddp			;st(0) = sqrt(x^2+1)+x
  fldln2		;st(1) = sqrt(x^2+1)+x | st(0) = ln2
  fxch			;st(1) = ln2 | st(0) = sqrt(x^2+1)+x FXCH — Exchange Register Contents
  fyl2x			;st(0) = (ln2*log_2(sqrt(x^2+1)+x))) = sinh^(-1)(x)
  
printresult:
  fst qword [i]
  push dword [i+4]
  push dword [i]
  push print
  call printf
  
end:
  mov eax, 1
  int 0x80
