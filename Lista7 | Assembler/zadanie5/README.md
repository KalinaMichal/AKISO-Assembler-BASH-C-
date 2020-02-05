Komilacja programu (Linux)



## To zadanie
```
$ arm-none-eabi-as arm.s -o arm.o
$ arm-none-eabi-gcc -specs=rdimon.specs arm.o -o arm
$ qemu-arm ./arm
```


## Pozostale zadania:
```
$ nasm -f elf32 zad2.asm -o zad2.o
$ gcc -m32 zad2.o -o zad2
$ ./zad2
```

