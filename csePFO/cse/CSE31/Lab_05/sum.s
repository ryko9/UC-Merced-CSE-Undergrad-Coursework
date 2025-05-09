.data 

	x: .word 1
	y: .word 2
.text 
	main:
		lw $s0, x
		lw $s1,y
		add $t0, $s0, $0
		add $t1,$s1,  $0
		add $t2, $t0, $t1
		add $t3, $t2, $t1
		add $t4, $t3, $t2
		add $t5, $t4, $t3
		add $t6, $t5, $t4
		add $t7, $t6, $t5
		addi $a0, $t7, 0
		li   $v0, 1		# you will be asked about what the purpose of this line for syscall 
		syscall			
		li      $v0, 10		
		syscall		
		
		