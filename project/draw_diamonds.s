	.arch msp430g2553
	.p2align 1,0
	.text			;constants (in flash)

	.extern diamond_color_state
	.extern clearScreen
	.extern drawDiamond
jt:
	.word case0		;jt[0]
	.word case1		;jt[1]
	.word case2		;jt[2]

	.global draw_diamonds
draw_diamonds:
	;; range check on selector (diamond_color_state)
	mov.b #1, r13		;placeholder to compare 1
	cmp.b &diamond_color_state, r13
	jl case2		;if N!=V, draw_diamonds > 1

	mov.b &diamond_color_state, r13
	add.b r13, r13
	mov jt(r13), r0

case0:
	mov.b #0x0000, r12 	;COLOR_BLACK
	call #clearScreen	;clearScreen(COLOR_BLACK)
	mov.b #60, r12
	mov #0xffe0, r13	;COLOR_CYAN
	call #drawDiamond	;drawDiamond(60,COLOR_CYAN)
	add.b #1, &diamond_color_state ;diamond_color_state++
	jmp end
case1:
	mov.b #60, r12
	mov #0xf800, r13	;COLOR_BLUE
	call #drawDiamond	;drawDiamond(60,COLOR_BLUE)
	add.b #1, &diamond_color_state ;diamond_color_state++
	jmp end
case2:
	mov.b #60, r12
	mov #0xf114, r13	;COLOR_PURPLE
	call #drawDiamond	;drawDiamond(60,COLOR_PURPLE)
	mov.b #0, &diamond_color_state ;diamond_color_state = 0
	jmp end
end:
	pop r0			;return
