section .data
 	int: db "%d", 10, 0
  	scan: db "%d %d", 0
  	print: db "%d", 10, 0
 	 a: dq 0
  	b: dq 0
  	op: db 0

section .text
  	global main
  	extern printf
  	extern scanf

main:
 	 push a
 	 push b
 	 push scan
  	call scanf				;wczytanie linii do zmiennych
  
  	mov eax,dword[a]
 	 mov ebx,dword[b]

gcd:
  	cmp  eax,ebx     		;sprawdzam ktory wiekszy
  	jg   grater    
  	jl   lower    
 	 jmp  exit   
grater:
  	sub  eax,ebx			;od a odejmuje b
  	jmp  gcd
lower:
  	sub  ebx,eax			;od b odejmuje a
	jmp  gcd			;zapetlanie
	
exit:
  	push eax		;3 linie dot. rysowania
  	push print
  	call printf

  	mov eax, 1
  	int 0x80
