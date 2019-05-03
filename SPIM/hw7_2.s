######################################################################
# SPIM source file for homework 7, problem 2                         #
#                                                                    #
# In SPIM, use: load "hw7_2.s"                                       #
# Then use the step command to step through instructions.            #
#                                                                    #
# The test instruction is preceeded and followed by NOPs to make it  #
# easier to spot in the SPIM output.                                 #
######################################################################
	.text
	.globl main
main:
	nop
	not  $t0,$s0,$s1	# Test instruction -- replace as needed
	nop

	jr   $ra

