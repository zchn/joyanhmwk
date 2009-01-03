LEX=flex -l
YACC=yacc -t -r all

CC=gcc -DYYDEBUG=1 -g

all:sc
	@echo "COMPLETE!"

lex.yy.c:sc.l y.tab.c
	$(LEX) sc.l

sc:lex.yy.o y.tab.o symtab.o backpatch.o
	$(CC) -o $@ $^ -ly -ll

y.tab.c:sc.y
	$(YACC) -d $<

.c.o:
	$(CC) -c $<

clean:
	rm -f *.o
	rm -f sc y.tab.h y.tab.c lex.yy.c

test:
	./sc test.c out.run

run:
	~/bin/cp_machine out.run
