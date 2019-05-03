######################################################################
# SPIM source file for homework 7, problem 1                         #
#                                                                    #
# In SPIM, use: load "hw7_1.s"                                       #
# Then use the step command to step through instructions.            #
#                                                                    #
# The test instruction is preceeded and followed by NOPs to make it  #
# easier to spot in the SPIM output.  The branch target is set to    #
# next instruction so that the code will execute the same way        #
# regardless of whether the branch is taken or not.                  #
######################################################################
	.text
	.globl main
main:
	nop
	lw		$s0, 0x10010011 		# $s0  0x10010010= 
		# Test instruction -- replace as needed
next:
	nop

	jr   $ra

