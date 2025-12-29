all:
	gcc -Wall --pedantic src/main.c src/gauss.c src/backsubst.c src/mat_io.c -o bin/gauss

multitest:
	cc -Wall --pedantic ./src/multitest.c ./src/gauss.c ./src/backsubst.c ./src/mat_io.c -o ./bin/multitest

test: all
	bin/gauss dane/A dane/b

test_main: all 
	bin/gauss dane/A1.txt dane/b1.txt outputSample/sample1.txt

test_multitest: multitest
	./bin/multitest 
