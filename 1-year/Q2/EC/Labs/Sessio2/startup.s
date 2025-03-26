###################################
# Standard startup code.  Invokes the routine "main"
# and calls exit() on return from main
	.text
	jal	main

	li	$v0, 10
	syscall			# syscall 10 (exit)


