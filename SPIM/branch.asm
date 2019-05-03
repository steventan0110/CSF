.data
strEq: .asciiz "Equal"
strNe: .asciiz "Not Equal"

.text
.globl main
main:
    li		$v0,5 		# $v0 = 5 (read in) 
    syscall
    move 	$t0, $v0		# $t0 = v0

    li		$v0, 5		# $v0 =5 
    syscall
    move 	$t1, $v0		# $t1 = v0
    bne		$t0, $t1, printNe	# if $t0 != $t1printNEtarget
    
printEq:
    la		$a0, strEq
    j print

printNe:
    la		$a0, strNe		# 
    j print

print:
    li $v0, 4
    syscall
    li $v0, 10
    syscall