.text
.globl main 
main:
    li $t0, 10 #number of iterations
    li $t1, 0 #t1 is the counter
    li $t2, 17 #the value to modify
loop:
    beq		$t1, $t0, end 	# if $t1 == 0t1 end loop
    add		$t2, $t2, $t1		# $t2 = $21 + 1t2
    addi	$t1, $t1, 1			# $t1 = $t1 + 1 
    j		loop				# jump to loop
end:
    li		$v0, 10 		# $v0  10= 
    syscall

    
    
    
    