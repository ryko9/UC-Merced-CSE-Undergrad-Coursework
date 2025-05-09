#collab w/ Nathan Huizar
	.data
	# This shows you can use a .word and directly encode the value in hex
	# if you so choose
num1:	.word 0x4B800000
num2:	.word 0x4B800000
num3:	.word 0x40000001
result:	.word 0
br: 	.asciiz "\n"
str1:	.asciiz "(num1 + num2) + num3 = "
str2:	.asciiz "num1 + (num2 + num3) = "

	.text
main:
	la 	$t0, num1
	lwc1 	$f2, 0($t0)
	lwc1 	$f4, 4($t0)
	lwc1 	$f6, 8($t0)

	# Print out the values of the summands

	li 	$v0, 2
	mov.s 	$f12, $f2
	syscall # Print num1
	li 	$v0, 4
	la 	$a0, br
	syscall # Print a line break
	li 	$v0, 2
	mov.s 	$f12, $f4
	syscall # Print num2
	li 	$v0, 4
	la 	$a0, br
	syscall # Print a line break
	li 	$v0, 2
	mov.s 	$f12, $f6
	syscall # Print num3
	li 	$v0, 4
	la 	$a0, br
	syscall # Print a line break
	syscall # Print another line break

	# Do the addition one way: num1 + (num2 + num3)

	add.s 	$f12, $f6, $f4
	add.s 	$f12, $f12, $f2
	
	# Transfer the value from the floating point reg to the integer reg

	swc1 	$f12, 12($t0)
	lw 	$s0, 12($t0)

	# Do the addition another way: (num1 + num2) + num3

	add.s 	$f12, $f2, $f4
	add.s 	$f12, $f12, $f6

print:	li 	$v0, 4
	la	$a0, str1
	syscall
	li	$v0, 2
	syscall
	li 	$v0, 4
	la 	$a0, br
	syscall
	la	$a0, str2
	syscall
	li	$v0, 2
	lwc1	$f12, 12($t0)
	syscall
	li 	$v0, 4
	la 	$a0, br
	syscall
