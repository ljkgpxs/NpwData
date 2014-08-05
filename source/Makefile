all:
	gcc checkey.c -o checkey -L. -lnpwdata -Wall 
	gcc wrt.c -o wrt -L. -lnpwdata -Wall
	gcc getser.c -o getser -L. -lnpwdata -Wall

lib:
	gcc NpwData_Lib.c -o libnpwdata.so -shared -fPIC -Wall

