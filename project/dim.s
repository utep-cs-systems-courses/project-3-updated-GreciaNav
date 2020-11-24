	.arch msp430g2553
	.p2align 1,0
	.text			;constants (in flash)
jt:
	.word option0		;jt[0]
	.word option1		;jt[1]
	.word option2		;jt[2]
	
	.extern dim_state
	.extern toggle_red
	.extern toggle_red75
	.extern toggle_red25
	
	.global dim
dim:
	;;  range check on selector (dim_state)
	cmp.b #3, &dim_state
	jhs end			

	;; index into jt  
	mov.b &dim_state, r13
	add.b r13, r13
	mov jt(r13), r0

	;; switch table options 

option0:
	call #toggle_red 	;toggle_red()
	jmp end			;break

option1:
	call #toggle_red75	;toggle_red75()
	jmp end			;break

option2:
	call #toggle_red25	;toggle_red25()

end:
	pop r0			;return
