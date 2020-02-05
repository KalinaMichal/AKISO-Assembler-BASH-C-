
.data
	format: .asciz "%d\n"
	scan: .asciz "%d %d"
	num1: .word 0
	num2: .word 0

.text 
	.global main
	.extern printf
	.extern scanf
main:
	ldr r0, =scan
	ldr r1, =num1 		// laduj addres num1 do r1
	ldr r2, =num2 		// laduj addres num2 do r2
	bl scanf		// wezwij scanf
	ldr r1, =num1 		// laduj addres num1 do r1
  	ldr r2, =num2 		// laduj addres num2 do r2
  	ldr r1, [r1] 		// laduj wartosci
  	ldr r2, [r2]
gcd:
  	CMP r1, r2		//Ktore wieksze itd.
  	SUBGT r1, r1, r2	
  	SUBLT r2, r2, r1
  	BNE gcd			//taki jakby jmp
print:
  	LDR r0, =format 	//print r1
  	BL printf
  	MOV r7, #1 		// wyjscie
  	SWI 0
