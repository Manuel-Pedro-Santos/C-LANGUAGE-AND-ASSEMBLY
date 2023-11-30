/*
char *my_strtok(char *str, const char *sep)
{
	static char *p = NULL;
	if (str != NULL)
		p = str;
	if (p == NULL || *p == 0)
		return NULL;
	while (strchr(sep, *p) != NULL)
		++p;
	if (*p == 0)
		return NULL;
	char *q = p;
	while (*p != 0 && strchr(sep, *p) == NULL)
		++p;
	*p++ = 0;
	return q;
}
*/
	.section .data
    my_start: .quad 0
	.bss

	.text
	.global my_strtok
my_strtok:       
    cmpb    $0, %dil
    jnz     .L0_my_strtok

    cmpq    $0, my_start
    jz     .L7_my_strtok
    
    cmpb	$0, (my_start)
    jnz		.L4_my_strtok
.L7_my_strtok:
    movq    $0, %rax
    ret

.L0_my_strtok:
    movq    %rdi, my_start

.L4_my_strtok:
    movq    my_start, %rcx

.L1_my_strtok:
    movq   $0, %r9
    movq    (my_start), %r9

    cmpb    $0, (%r9)         
    jz      .L2_my_strtok
           
    movq    %rsi , %r10
    jmp      .L5_my_strtok
    
.L6_my_strtok:
    movb    $0,(%r9) 
    incq    my_start
    movq    %rcx, %rax
    ret

.L5_my_strtok:
    cmpb     $0,(%rsi)
    je 		.L3_my_strtok
    movq    $0, %r8 
    movb    (%rsi), %r8b
    cmpb    (%r9), %r8b
    je      .L6_my_strtok
    inc     %rsi
    jmp 	.L5_my_strtok
    
.L3_my_strtok:
    movq %r10 , %rsi
    incq    my_start
    jmp     .L1_my_strtok

.L2_my_strtok:
    movq    $0, my_start
    movq    %rcx, %rax
    ret


	.section .note.GNU-stack
	.end
