/* OS kernel code */

void main(void) {
	*(char *)0xb8000 = 'D';
	*(char *)0xb8001 = 0x0F;
	*(char *)0xb8002 = 'o';
	*(char *)0xb8003 = 0x0F;
	*(char *)0xb8004 = 'x';
	*(char *)0xb8005 = 0x0F;
	return;
}
