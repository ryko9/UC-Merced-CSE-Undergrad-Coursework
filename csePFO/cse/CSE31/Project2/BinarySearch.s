#CSE31
#David Wang
#Collab w Jason Block

.data 

original_list: .space 100 
sorted_list: .space 100

str0: .asciiz "Enter size of list (between 1 and 25): "
str1: .asciiz "Enter one list element: \n"
str2: .asciiz "Content of list: "
str3: .asciiz "Enter a key to search for: "
strYes: .asciiz "Key found!"
strNo: .asciiz "Key not found!"

newline: .asciiz "\n"


.text 

#This is the main program.
#It first asks user to enter the size of a list.
#It then asks user to input the elements of the list, one at a time.
#It then calls printList to print out content of the list.
#It then calls inSort to perform insertion sort
#It then asks user to enter a search key and calls bSearch on the sorted list.
#It then prints out search result based on return value of bSearch
main: 
	addi $sp, $sp -8
	sw $ra, 0($sp)
	li $v0, 4 
	la $a0, str0 
	syscall 
	li $v0, 5	#Read size of list from user
	syscall
	move $s0, $v0
	move $t0, $0
	la $s1, original_list
loop_in:
	li $v0, 4 
	la $a0, str1 
	syscall 
	sll $t1, $t0, 2
	add $t1, $t1, $s1
	li $v0, 5	#Read elements from user
	syscall
	sw $v0, 0($t1)
	addi $t0, $t0, 1
	bne $t0, $s0, loop_in
	
	li $v0, 4 
	la $a0, str2 
	syscall 
	move $a0, $s1
	move $a1, $s0
	jal printList	#Call print original list
	
	jal inSort	#Call inSort to perform insertion sort in original list
	sw $v0, 4($sp)
	li $v0, 4 
	la $a0, str2 
	syscall 
	lw $a0, 4($sp)
	jal printList	#Print sorted list
	
	li $v0, 4 
	la $a0, str3 
	syscall 
	li $v0, 5	#Read search key from user
	syscall
	move $a2, $v0
	lw $a0, 4($sp)
	jal bSearch	#Call bSearch to perform binary search
	
	beq $v0, $0, notFound
	li $v0, 4 
	la $a0, strYes 
	syscall 
	j end
	
notFound:
	li $v0, 4 
	la $a0, strNo 
	syscall 
end:
	lw $ra, 0($sp)
	addi $sp, $sp 8
	li $v0, 10 
	syscall
	
	
#printList takes in a list and its size as arguments. 
#It prints all the elements in one line.
printList:
		
	#a0 = A[0], #a1 = n, $s0 = i 
	#Your implementation of printList here	

	move $t1, $a0  #t1 = address of A[0]
	move $s0, $zero #i = 0 counter for for loop
forloop:	
	slt $t0, $s0, $a1 #checks if i < n and sets t0 = 1 if true and t0 = 0 if false
	beq $t0, $zero, exit #if t0 = 0, i > n jump to exit
	
	lw $a0, 0($t1) #set a0 to the VALUE at t1
	li $v0, 1 #prints a0 as integer
	syscall 
	
	li $a0, 32 #prints character 32 which is a space in ascii
	li $v0, 11
	syscall
	
	addi $t1, $t1, 4 #increment address a0 points to by 4 to get to next element of array.
	addi $s0, $s0, 1 #i += 1
	j forloop 
exit:	
	li $v0, 4
	la $a0, newline
	la $a0, original_list
	jr $ra
#inSort takes in a list and it size as arguments. 
#It performs INSERTION sort in ascending order and returns a new sorted list
#You may use the pre-defined sorted_list to store the result
inSort:
	#Your implementation of inSort here
	li	$t2, 1		# i = 1

outerFor:

	bge	$t2, $a1, outerForEnd #from i = 1 to n, if i > n then exit loop
	move	$t3, $t2 #j = i

innerWhile:
	mul	$t5, $t3, 4		# t5 = 4 * i since elements are seperated by bytes
	add	$t0, $a0, $t5		# address of A[4 * i]
	
	ble	$t3, $zero, innerWhileEnd	# while (t3 > 0).
	
	lw	$t7, 0($t0)		# t7 = A[i]
	lw	$t6, -4($t0)		# t6 = A[j - 1]
	
	bge	$t7, $t6, innerWhileEnd	# while (array[i] < array[j - 1]).
	
	lw	$t4, 0($t0) #t4 = A[j]
	sw	$t6, 0($t0)
	sw	$t4, -4($t0) #t4 = A[j - 1]
	subi	$t3, $t3, 1
	j	innerWhile

innerWhileEnd:
	addi	$t2, $t2, 1
	j	outerFor

outerForEnd:
	la	$v0, ($a0)
	jr 	$ra
	
	
#bSearch takes in a list, its size, and a search key as arguments.
#It performs binary search RECURSIVELY to look for the search key.
#It will return a 1 if the key is found, or a 0 otherwise.
#Note: you MUST NOT use iterative approach in this function.
bSearch:
	#Your implementation of bSearch here
	jr $ra
	
