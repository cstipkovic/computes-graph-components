# Escrever o makefile para compilar no Mac/Linux
# Lembrando que o programa precisa funcionar no Dev C++ :/
main: clean
	gcc -o main main.c
clean:
	rm -rf ./main