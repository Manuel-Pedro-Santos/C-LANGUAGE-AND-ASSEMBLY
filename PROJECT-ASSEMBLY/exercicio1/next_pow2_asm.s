/*
	size_t next_pow2(size_t x)
*/

	.text
	.global next_pow2
	
next_pow2:
	test	%rdi,%rdi
	jz		L0_next_pow2
	
	mov 	%rdi ,%rsi
    dec 	%rsi
    test 	%rdi, %rsi 
    jz		L1_next_pow2
    
    cmp		$0, %esi
    je		L0_next_pow2
	
	bsr 	%rdi,%rcx
	inc		%rcx
	mov 	$1, %rdi
	shl		%cl,%rdi
	
L1_next_pow2:
	mov 	%rdi, %rax
	ret
	
L0_next_pow2:
	mov		$0,%rax
	ret

	.section .note.GNU-stack
	.end

