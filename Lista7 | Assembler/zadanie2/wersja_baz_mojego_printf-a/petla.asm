section .data
 int: db "%d", 10, 0
  scan: db "%d", 0
  print: db "%d", 10, 0
  a: dq 0
  op: db 0

section .text
  global main
  extern printf
  extern scanf

main:
  push a
  push scan
  call scanf				;wczytanie linii do zmiennych
  
  finit						;inicjalizacja modułu zmiennoprzecinkowego
  fld qword [a]				;załaduj a
  mov ebx,0
  mov eax,0
  mov ecx,dword[a]

	start:
	cmp ebx,dword[a]
	je exit			;jeśli rowne zakończ program
	inc ebx
	mov eax,0

	draw:
	cmp eax,ebx
	je start	

	inc eax			;eax+1
  	push eax		;3 linie dot. rysowania
  	push print
  	call printf
	call draw		;zapetlanie

exit:
  jmp main
