[GLOBAL memset]
[GLOBAL memsetw]
[GLOBAL memcpy]
[GLOBAL memcmp]
[GLOBAL memchr]

section .text

; void memset(void *mem, char value, size_t count);
memset:
	push edi
	mov edi, [esp + 8]
	mov edx, [esp + 12]
	mov al, dl
	shl eax, 8
	mov al, dl
	shl eax, 8
	mov al, dl
	shl eax, 8
	mov al, dl
	mov edx, [esp + 16]
	mov ecx, edx
	shr ecx, 2
	rep stosd
	mov ecx, edx
	and ecx, 3
	rep stosb
	pop edi
	ret

; void memsetw(void *mem, uint16 value, size_t count);
memsetw:
	push edi
	mov edi, [esp + 8]
	mov edx, [esp + 12]
	mov ax, dx
	shl eax, 16
	mov ax, dx
	mov edx, [esp + 16]
	mov ecx, edx
	shr ecx, 1
	rep stosd
	mov ecx, edx
	and ecx, 1
	rep stosw
	pop edi
	ret

; void memcpy(void *dest, void *src, size_t count);
memcpy:
	push esi
  push edi
	mov edi, [esp + 12]
	mov esi, [esp + 16]
	mov edx, [esp + 20]
	cmp edi, esi
	jb .reversed
	mov ecx, edx
	shr ecx, 2
	rep movsd
	mov ecx, edx
	and ecx, 3
	rep movsb
 .exit:
	pop edi
  pop esi
	ret
 .reversed:
	add esi, edx
	add edi, edx
	dec esi
	dec edi
	std
	mov ecx, edx
	and ecx, 3
	rep movsb
	mov ecx, edx
	shr ecx, 2
	rep movsd
	cld
	jmp .exit

; int memcmp(void *mem1, void *mem2, size_t count);
memcmp:
	push esi
  push edi
	mov edi, [esp + 12]
	mov esi, [esp + 16]
	mov ecx, [esp + 20]
	repe cmpsb
	seta al
	setb dl
	sub al, dl
	movzx eax, al
	pop edi
  pop esi
	ret

; void *memchr(void *mem, char value, size_t count);
memchr:
	push edi
	mov edi, [esp + 8]
	mov eax, [esp + 12]
	mov ecx, [esp + 16]
	repne scasb
	jne .not_found
	dec edi
	mov eax, edi
 .exit:
	pop edi
	ret
 .not_found:
	xor eax, eax
	jmp .exit
