all:
	gcc mystat.c -o mystat -w
	gcc myls.c -o myls -w
	gcc mytail.c -o mytail -w
	gcc mytree.c -o mytree -w
clean: 
	rm  mystat myls mytail mytree
