CFLAGS=-g -Wall -Wextra -Wwrite-strings

chgTxt: chgTxt.c
	gcc ${CFLAGS} -o chgTxt chgTxt.c

clean:
	rm -f chgTxt 
