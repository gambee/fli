#include <string.h>
#define BUF_DEBUG
#include "fli_buffer.h"

#define STR_LEN 12

int main(void)
{
	char c;
	int i = 0;
	char *str, *tmp = NULL;
	struct BUF_buffer buffer;

	if(str = (char *) malloc(sizeof(char)*STR_LEN + 1))
	{
		while(i < STR_LEN)
			for(c = 'a'; (c <= 'z')&&(i < STR_LEN); c++)
				str[i++] = c;
		str[STR_LEN] = '\0';
	}
	else
		*str = '\0';

	
	BUF_init(&buffer);
	BUF_puts(&buffer, str);
	BUF_strflush(&buffer, &tmp);
	BUF_print_all(&buffer);

	printf("str: %s\n", str);
	printf("tmp: %s\n", tmp);
	printf("length of buffer: %d\n", BUF_len(&buffer));
	printf("length of str   : %d\n", strlen(str));
	printf("length of tmp   : %d\n", strlen(tmp));
	
	return 0;
}
