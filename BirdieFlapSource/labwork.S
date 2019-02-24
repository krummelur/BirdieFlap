  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #
  
  
.text
  
	##############################
	##########	HEXASC	##########
	##############################
.globl hexasc
hexasc:
	#First we must mask out all but the least significant 4 bits of a0
	# copy into v0, we don't wanna change the value of a0
	move	$v0,$a0		#copy a0 into v0 
	# mask out bits in v0
	li 		$v1,0xF		#load 0x0000000F into v1
	and 	$v0,$v0,$v1	#mask out all unrelated bits 
	sub		$v1,$v0,10 	#subtract 9 from v0, put into v1
	bgez	$v1,above10	
	nop
zeroTo9: 
# in case the value of v0 after masking is less than 10  
	addi	$v0,$v0,0x30	#add 0x30 ('0') to v0
	jr	$31
	nop
above10:
# in case the value of v0 after masking is more than 9
	addi	$v0,$v0,0x37	#add 0x37 ('7') to v0 
	jr	$31
	nop	
	
	######################################
	##########	TIME 2 STRING	##########
	######################################
.globl time2string
time2string:
	#in time2string subbroutine, we must convert the timecode from the least significant 2 bytes of a1 and store the result into the area in memory pointed at by a0
	# first we want to shift and add each ascii digit into a temporary register, if possible without using the stack
	PUSH	$31		#store return value on the stack		
	xor 	$a0, $a0, $a1	# Hi-Tek xor swap
	xor		$a1, $a0, $a1
	xor		$a0, $a0, $a1
	li 	$v0,0x0
	sb	$v0,5($a1)	#store the null terminator at proper place in memory
	jal	hexasc
	nop
	sb	$v0,4($a1)	#store the 4th number of the time 
	srl	$a0, $a0, 4
	jal	hexasc
	nop
	sb	$v0,3($a1)	#store the 3th number of the time 
	li 	$v0,0x3a
	sb	$v0,2($a1)	#store the colon at proper place in memory
	srl	$a0, $a0, 4
	jal	hexasc
	nop
	sb	$v0,1($a1)	#store the 2nd number of the time 
	srl	$a0, $a0, 4
	jal	hexasc
	nop
	sb	$v0,0($a1)	#store the 1st number of the time 	
	POP	$31		
	jr	$31
	nop
	
	
	##############################
	##########	DELAY	##########
	##############################
.globl delay
	delay:
	move	$v0,$a0
outer:	
	blez 	$v0,counterdone
	nop
	li 	$v1,4711
inner:
	sub	$v1,$v1,1
	bgtz	$v1, inner
	nop
	sub	$v0,$v0,1
	j	outer	
	nop
counterdone:
	jr	$ra
	nop
	
	##############################
	#####  ENABLE INTERRUPTS  ####
	##############################
.globl enable_interrupts
enable_interrupts:
	ei
	jr $ra
	nop