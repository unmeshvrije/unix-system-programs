gcc -c server.c
gcc -c client.c
gcc -c add_svc.c
gcc -c add_clnt.c
gcc -c add_xdr.c

gcc -o server server.o add_svc.o add_xdr.o
gcc -o client client.o add_clnt.o add_xdr.o

