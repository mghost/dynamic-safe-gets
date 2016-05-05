#ifndef __safe_gets_c__
#define __safe_gets_c__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifdef __default_length__
#undef __default_length__
#endif

#define __default_length__ 10

/*
#define _debug
#define _verbose
/**/

int get_length() {
	int length;

	printf("  [*] length of string?   ");
	scanf("%d", &length);

	/* ASSERTION: char got by stdin must be '\n' */
	assert(getchar() == 10);
	
	if(length<=0)
		length = __default_length__;
	
	return length;
}

int skip() {
	char ch;
	int skipped = 0;

	while((ch=getchar())!=EOF && ch!=10) {
		skipped++;
		#ifdef _debug
		printf("  [D] skipped #%d char ( = %d )\n", skipped, ch);
		#endif
	}
	return skipped;
}

char* my_gets(int length, int* skp) {
	int counter = 0, skipped;
	char ch, *buffer = (char*)malloc((length+1) * sizeof(char));

	/* PRE - 1: length >= 0 */
	#ifdef _debug
	assert(length >= 0);
	#endif

	/* PRE - 2: buffer != NULL and strlen(buffer) >= 0 */
	#ifdef _debug
	assert(buffer && strlen(buffer)>=0);
	#endif

	/*** WATCH OUT: no controls on buffer's pointer!! ***/

	while(counter<length && ((ch=getchar())!=EOF && ch!=10)) {
		/* INV - 1: counter < length */
		assert(counter < length);

		/* INV - 2: ch != EOF and ch != 10 */
		assert(ch!=EOF && ch!=10);

		#ifdef _debug
		printf("  [D] input char:  %d\n", ch);
		#endif

		buffer[counter++] = ch;
	}
	/* puts end-of-string at end of buffer */
	buffer[length] = 0;

	skipped = skip();

	/* POST - 1: length of buffer <= length and length of buffer >= 0 */
	#ifdef _debug
	int sl = strlen(buffer);

	assert(sl>=0 && sl<=length);
	#endif

	/* POST - 2: skipped >= 0 */
	#ifdef _debug
	assert(skipped >= 0);
	#endif

	/* if passed a good pointer, assign the second return value */
	if(skp)
		*skp = skipped;

	return buffer;
}

int main(void) {
	int length = get_length(), skipped;
	char* buffer;

	printf("  [*] give me a string (of %d char(s)), please:  ", length);
	buffer = my_gets(length, &skipped);

	printf("  [+] input the string '%s' [length: %d]\n", buffer, strlen(buffer));
	if(skipped > 0)
		printf("    [-] yet, be ashamed of yourself! [skipped: %d]\n", skipped);
	return 0;
}

#endif
