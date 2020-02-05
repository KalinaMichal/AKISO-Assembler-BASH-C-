SYS_EXIT  equ 1
SYS_WRITE equ 4
SYS_READ  equ 3
STDIN     equ 0

STDOUT    equ 1
section	 .text
	global _start    	;must be declared for using gcc
	_start:              	;tell linker entry point

	call read_ebx		;czytam takie jakby n
				;wczytujemy jak ma wygladac nasze drzewo
	mov ecx, 0		;ecx=0

;ecx-linijka
;edx-element linijki

;cale drzewo
l1:
	inc ecx			;ecx++
	mov edx, 0		;edx=0

;pojedynczy poziom drzewa 
l2:
	inc edx			;edx++
	mov eax, edx		;eax=edx
	call print_eax		
	call space
	cmp ecx, edx		;czy wieksze
;czy num, el nie jest wiekszy od linijki, jesli jest to idziemy dalej
	jne l2			;tak
	mov eax, 10		;eax=10
	call print_char
;druk znak konca lini.

;sprawdzam czy num linijki jest mniejszy niz nasz docel. rozm drzewa
	cmp ecx, ebx		;czy wieksze
	jne l1			;tak

   
	mov eax,SYS_EXIT    	;system call number (sys_exit)
	int 0x80            	;call kernel



print_eax: 			;prints intuger from eax
	push eax			;wywalam wszystko zeby niestracic rejestrow. -push daje na szczyt stosu - sroda, daje to na szczyt.
	push ebx
	push ecx
	push edx
	mov dword [tmp], 0x0		; = 
	mov ecx, 10			;ecx=10
loop: ;pushes chracters to stack
	mov edx, 0			;edx=0
	div ecx				; eax=eax%ecx
	add edx, '0'			; jest w ' ' bo jak do edx dodam kod ASCI(0) to mam kod edx.
	push edx 
	inc dword [tmp]
	cmp eax, 0x0			; 0x0 bo sprawdzam czy to nie jest ostatni znak.
	jne loop			;skok jesli nierowne -sroda
	mov ebx, STDOUT 	;prepare registers for write
	mov ecx, char			; ecx=char.
	mov edx, 1			;edx=1
loop2:	; prints stack
	pop dword [char]		;pop tzn. zdejmuje ze stosu 1 cyferke i dod. do char
	mov word [char+1], 0		;bo mam 2 bajty 1 jest literka a 2 jest 0
	mov eax, SYS_WRITE		
	int 0x80			;0x80 bo chce wyswietlic, jest wyw. sys. bo syswrite
	dec dword [tmp]
	cmp dword [tmp], 0x0		;czy rowne 0.
	jne loop2
	pop edx				;pop tzn. odtwarzamy rejestry przed wyw. tej funkcji.
	pop ecx
	pop ebx
	pop eax
	ret

space: ;just prints one space
	push eax
	push ebx
	push ecx
	push edx
	mov dword [char], '  '		;dodaje sb spacje do char, robie to w 4 bajtach bo dword.
	mov word [char+1], 0
	mov ebx, STDOUT
	mov ecx, char
	mov edx, 1
	mov eax, SYS_WRITE		
	int 0x80			;0x80 bo wyw. sys..
	pop edx
	pop ecx
	pop ebx
	pop eax
	ret				;return, ktokolwiek wyw. za pom. call to wraca do tego goscia.

print_char: ;just prints one character from eax
	push eax
	push ebx
	push ecx
	push edx
	mov dword [char], eax
	mov word [char+1], 0		;wywalam 1 z wartosci bo ja juz zalatwilem-sroda
	mov ebx, STDOUT			;STDOUT 
	mov ecx, char			
	mov edx, 1
	mov eax, SYS_WRITE		;SYS_WRITE
	int 0x80			;
	pop edx
	pop ecx
	pop ebx
	pop eax
	ret

read_ebx: ;read int from stdin to ebx
	push eax
	push ecx
	push edx			
	mov eax, SYS_READ		;eax=SYS_READ	SYS_READ to daje to co mam zrobic(czyli ktore wyw.sys)
	mov ebx, STDIN			;ebx=STDIN	STDIN to z ktorego wejscia
	mov ecx, buff			;ecx=buff	buff to adres pam. do ktorej zapisze
	mov edx, b_len 			;edx dlugosc
	int 0x80 ; read to buff

	mov ebx, 0 			;resulatat
	mov ecx, 0 			;counter
	mov dword [tmp2], 1 		;multiplyer, o ile bd mnozyl z tekstu na inta to 1 razy 1, 2 razy 10, 3 razy 100 itd.
o_loop: 				;find end of string, tak dlugo az nie znajdziemy konca, czyli 10
	inc ecx				;ecx++
	cmp word [buff+ecx], 10		;czy rowne, mam tu 10 bo patrz 3 linijki wyzej
	jne o_loop			;nie

;ogolnie to jak mam liczbe abcdef to najpierw jedzie f potem e potem d itd.
read_loop: 			; loop do zmiany stringa na inta
	dec ecx				;robie to tu a nie 2 lin nizej bo ostatni dodany to info o koncu
	mov eax, dword [buff+ecx]
	and eax, 0x0000000f		;get only last 4 bits 4 bo tylko one przechowuja cyfre, pozost to kod ASCII | op. and: wynik w eax | Chodzi o to ze kod ascii dla 1 to xxxx0001 a np 6 to xxxx0110
	mul dword [tmp2]		;mnoz. cyfre * tmp2(czyli multipilcator)
	add ebx, eax
	mov eax, 10
	mul dword [tmp2]
	mov dword [tmp2], eax
	cmp ecx, 0			;czy koniec
	jne read_loop			;nie
	pop edx				;odtwarzam wszytko
	pop ecx
	pop eax
	ret
	
section	 .data
buff 	times 100 db 0		;to jest nasz buffor(max 100)
b_len 	equ 100			;to dl. buffora
text	db 'K'			;musi byc cokolwiek bo nie moze byc puste

section	 .bss
char	resd 1			;resd to double dlatego mam 4 bajty 2 slowa
tmp	resd 1
tmp2	resd 1



;pop : zdejmuje ze szczytu stosu wartość i kopiuje ją do rejestru ogólnego przeznaczenia
;rejestr. og. przezn. , rejestr segmentowy (poza CS) lub adres w pamięci.
;max wartosc to conajmniej 2^31-sroda
