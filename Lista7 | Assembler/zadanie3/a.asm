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
  
  finit					;moduł zmiennoprzecinkowy
  fld qword [i]		;st(0) = x
  fldl2e				;st(1) = x | st(0) = log2(e)
  fmulp					;st(0) = x*log2(e)
  fld st0				;st(1) = x*log2(e) | st(0) = x*log2(e)
  frndint				;st(1) = x*log2(e) | st(0) = INT[x*log2(e)]
  fsub st1,st0				;st(1) = x*log2(e)-INT[x*log2(e)] | st(0) = INT[x*log2(e)]
  fxch st1				;st(1) = INT[x*log2(e)] | st(0) = x*log2(e)-INT[x*log2(e)]
  f2xm1					;st(1) = INT[x*log2(e)] | st(0) = 2^(x*log2(e)-INT[x*log2(e)])-1
  fld1					;st(2) = INT[x*log2(e)] | st(1) = 2^(x*log2(e)-INT[x*log2(e)])-1 | st(0) = 1
  faddp					;st(1) = INT[x*log2(e)] | st(0) = 2^(x*log2(e)-INT[x*log2(e)])
  fscale				;st(1) = INT[x*log2(e)] | st(0) = 2^(x*log2(e))
  fstp st1				;st(0) = 2^(x*log2(e))
  fld1					;st(1) = 2^(x*log2(e)) | st(0) = 1
  fld1					;st(2) = 2^(x*log2(e)) | st(1) = 1 | st(0) = 1
  faddp					;st(1) = 2^(x*log2(e)) | st(0) = 2
  fdivp					;st(0) = 2^(x*log2(e))/2
	
			;1 gotwe

  fld qword [i]		;st(1) = 2^(x*log2(e))/2 | st(0) = x
  fchs					;st(1) = 2^(x*log2(e))/2 | st(0) = -x
  fldl2e				;st(2) = 2^(x*log2(e))/2 | st(1) = -x | st(0) = log2(e)
  fmulp					;st(1) = 2^(x*log2(e))/2 | st(0) = -x*log2(e)
  fld st0				;st(2) = 2^(x*log2(e))/2 | st(1) = -x*log2(e) | st(0) = -x*log2(e)
  frndint				;st(2) = 2^(x*log2(e))/2 | st(1) = -x*log2(e) | st(0) = INT[-x*log2(e)]
  fsub st1,st0				;st(2) = 2^(x*log2(e))/2 | st(1) = -x*log2(e)-INT[-x*log2(e)] | st(0) = INT[-x*log2(e)]
  fxch st1				;st(2) = 2^(x*log2(e))/2 | st(1) = INT[-x*log2(e)] | st(0) = -x*log2(e)-INT[-x*log2(e)]
  f2xm1					;st(2) = 2^(x*log2(e))/2 | st(1) = INT[-x*log2(e)] | st(0) = 2^(-x*log2(e)-INT[-x*log2(e)])-1
  fld1					;st(3) = 2^(x*log2(e))/2 | st(2) = INT[-x*log2(e)] | st(1) = 2^(-x*log2(e)-INT[-x*log2(e)])-1 | st(0) = 1
  faddp					;st(2) = 2^(x*log2(e))/2 | st(1) = INT[-x*log2(e)] | st(0) = 2^(-x*log2(e)-INT[-x*log2(e)])
  fscale				;st(2) = 2^(x*log2(e))/2 | st(1) = INT[-x*log2(e)] | st(0) = 2^(-x*log2(e)) 
  fld1					;st(3) = 2^(x*log2(e))/2 | st(2) = INT[-x*log2(e)] | st(1) = 2^(-x*log2(e)) | st(0) = 1
  fld1					;st(4) = 2^(x*log2(e))/2 | st(3) = INT[-x*log2(e)] | st(2) = 2^(-x*log2(e)) | st(1) = 1 | st(0) = 1
  faddp					;st(3) = 2^(x*log2(e))/2 | st(2) = INT[-x*log2(e)] | st(1) = 2^(-x*log2(e)) | st(0) = 2
  fdivp					;st(2) = 2^(x*log2(e))/2 | st(1) = INT[-x*log2(e)] | st(0) = 2^(-x*log2(e))/2
  fstp st1				;st(1) = 2^(x*log2(e))/2 | st(0) = 2^(-x*log2(e))/2
  fsubp					;st(0) = 2^(-x*log2(e))/2 - 2^(x*log2(e))/2
  
printresult:
  fst qword [i]
  push dword [i+4]
  push dword [i]
  push print
  call printf
  
end:
  mov eax, 1
  int 0x80



;fscale = Zaokrągla st1 w kierunku zera by otrzymać liczbę całkowitą, następnie podnosi dwójkę do potęgi określonej tą liczbą całkowitą, wynik mnoży przez st0. Wynik zapamiętywany jest w st0. 
;2^int(tmp1) + 2^fract(tmp1) = 2^(x*log2(e))
;fprem =  fract(st0)
;tmp1=log2(e) 

