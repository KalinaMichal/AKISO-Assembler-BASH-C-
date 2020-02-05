section .data
  int: db "%d", 10, 0		;DB - Define Byte. 8 bits
  scan: db "%d", 0
  print: db "%08x%08x%08x%08x", 10, 0
  num: dd 0			;DD-Define double word
  n1: dd 1
  result: dd 0			;DQ-define quadword

section .text
  global main
  extern scanf		;obiekt zawiera sie w innej jednostce
  extern printf

main:
  push num		;skanowanie itd.
  push scan
  call scanf
  mov eax, dword [num]	;kopiuje cos do czegos
  movd xmm1,dword [n1]	;movd-move doubleword

  multiplyloop:
    movd xmm2,eax	;move xmm2=eax
    pmuludq xmm1,xmm2   ;mnożenie 32-bitowych liczb bez znaku, wyniki są 64-bitowe xmm1*xmm2
    dec eax		;eax--
    cmp eax,1		;czy eax==1
    je end		;tak
    jmp multiplyloop
  
end:
  movdqu oword[result],xmm1	;ladowanie xmm z 18-bit mem. loc.
  push dword [result]
  push dword [result+4]		;ucinam smieci kolejno po 8 znkaow		
  push dword [result+8]		;jakbym niczego nie dod. to pok. wynik pare razy
  push dword [result+12]
  push print
  call printf
	jmp main
