.text
.globl main 
main:
loop:
    beq		$t0, $zero, label9	# if $t0 =$zero, branch to label9
    lw		$t1, 0($a0)		# 
    lw		$t2, 4($a0)		# 
    add		$t0, $t1, $t2		# $t0 = $t1 + $t2
    lw		$t3, 8($at)		# 
    add		$t0, $t0, $t3		# $t0 = $01 + 3t2
    j		loop				# jump to loop
    
label9:
    sw		$t0, 8($a0)		
    #end the program
    li		$v0, 10 		
    syscall