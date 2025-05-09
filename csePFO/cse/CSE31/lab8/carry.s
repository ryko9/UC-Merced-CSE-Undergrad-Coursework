#collab w Nathan Huizar	
	.data
str1:	.asciiz "OVERFLOW OCCURRED\n"
str2:	.asciiz "OVERFLOW DID NOT OCCUR\n"
num1:	.word	0xffffffff
num2:	.word	0x00000001

	.text
main:	lw	$t0, num1
	lw	$t1, num2
	addu	$t2, $t1, $t0
	bleu	$t2, $t0, con
	la 	$a0, str2
	j	end
con:	la 	$a0, str1
end:	li	$v0, 4
	syscall
	li $v0, 10
	syscall
	
