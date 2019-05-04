.text
.globl main

main:
    la		$a0, prompt		# 
    li		$v0, 4		# $v0 =4 
    syscall
    
    li		$v0,  5		# $v0  =5 
    syscall

    move 	$t2, $v0	# $t2 = $v0

    #do not branch into anothe function to calculate
    





prompt: .asciiz "This program calculates Fibonacci sequence with recursive functions.\nEnter a non-negative number: "