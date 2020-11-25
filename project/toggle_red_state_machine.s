	.arch msp430g2553
	.p2align 1,0
	.text			;constants (in flash)

	.extern toggle_state
	.extern red_on
jt:
	.word case0		;jt[0]
	.word case1		;jt[1]

	.global toggle_red_state_machine
	
toggle_red_state_machine:
	mov.b #0, r13		;placeholder to compare 0
	cmp.b r12, r13	        ;unsigned comp
	jl case1		;if N!=V

	mov.b r12, r13
	add.b r13, r13
	mov jt(r13), r0
	
case0:
	mov.b #1, &red_on	;red_on = 1
	mov.b #1, r12		;to return 1
	jmp end

case1:
	mov.b #0, &red_on	;red_on = 0
	mov.b #0, r12		;to return 0

end:
	pop r0			;return
	
