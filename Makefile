s=safe_gets
sc=$(s).c

do: compile
	./$(s)

compile: $(sc)
	gcc -o $(s) $(sc)

