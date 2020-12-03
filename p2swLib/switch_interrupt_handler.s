	.arch msp430g2553
	.p2align 1,0
	.text			;constants (in flash)

	.extern switch_update_interrupt_sense
	.extern clearScreen
	.extern button_state
	
	.global switch_interrupt_handler
switch_interrupt_handler:
	sub #2, r1		; making space for p2val
	call #switch_update_interrupt_sense
	mov.b r12, 0(r1)	;p2val = switch_update_interrupt_sense

if:
	mov.b #1, r13	;SW1, BIT0
	and.b 0(r1), r13
	cmp.b #0, r13		;if ((pv2al & SW1) == 0)
	jnz elseif		;(pv2al & SW1) != 0

	mov.b #0, &button_state	;button_state = 0
	jmp end

elseif:
	mov.b #2, r13	;SW2, BIT1
	and.b 0(r1), r13
	cmp.b #0, r13		;if ((pv2al & SW2) == 0)
	jnz elseif2		;(pv2al & SW2) != 0

	mov.b #1, &button_state	;button_state = 1
	jmp end

elseif2:
	mov.b #4, r13 	;SW3, BIT2
	and.b 0(r1), r13
	cmp.b #0, r13		;if ((pv2al & SW3) == 0)
	jnz elseif3		;(pv2al & SW3) != 0

	mov.b #2, &button_state	;button_state = 2
	jmp end

elseif3:
	mov.b #8, r13	;SW4, BIT3
	and.b 0(r1), r13
	cmp.b #0, r13		;if ((pv2al & SW4) == 0)
	jnz end		        ;(pv2al & SW4) != 0

	mov.b #3, &button_state	;button_state = 3
	jmp end

end:
	add #2, r1		;freeing up p2val
	pop r0			;return
