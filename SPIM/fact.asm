.data
prompt:.asciiz "Number n for factorial calculation"

.text
.globl main
main:
    # Prompt user to input non-negative number
    la      $a0, prompt   
    li      $v0, 4
    syscall

    li $v0,5    #Read the number(n)
    syscall

    
    move    $t2, $v0    # n to $t2
    move 	$t3, $t2		# $t3 = $21

cal:
    sub		$t2, $t2, 1		# $t2 = $21 1t2
    beq		$t2, $zero, end	# if $t2 ==zerot1endtarget
    mul     $t3, $t3, $t2
    j   cal 


end:
    move	$a0, $t3	
    li		$v0, 1		# $v0 =1 
    syscall

    li		$v0, 10		# $v0 =10 
    syscall
    

