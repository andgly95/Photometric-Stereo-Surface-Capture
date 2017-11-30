########################################
##
## Makefile
## LINUX compilation 
##
##############################################





#FLAGS
C++FLAG = -g -std=c++11

MATH_LIBS = -lm

EXEC_DIR=.


.cc.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@


#Including
INCLUDES=  -I. 

#-->All libraries (without LEDA)
LIBS_ALL =  -L/usr/lib -L/usr/local/lib 


#First Program (ListTest)

Cpp_OBJ_1=image.o s1.o ImageEditor.o Sphere.o
Cpp_OBJ_2=image.o s2.o ImageEditor.o Sphere.o
Cpp_OBJ_3=image.o s3.o ImageEditor.o Sphere.o
Cpp_OBJ_4=image.o s4.o ImageEditor.o Sphere.o

PROGRAM_NAME1=s1
PROGRAM_NAME2=s2
PROGRAM_NAME3=s3
PROGRAM_NAME4=s4

$(PROGRAM_NAME1): $(Cpp_OBJ_1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_1) $(INCLUDES) $(LIBS_ALL)

$(PROGRAM_NAME2): $(Cpp_OBJ_2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_2) $(INCLUDES) $(LIBS_ALL)

$(PROGRAM_NAME3): $(Cpp_OBJ_3)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_3) $(INCLUDES) $(LIBS_ALL)
$(PROGRAM_NAME4): $(Cpp_OBJ_4)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_4) $(INCLUDES) $(LIBS_ALL)

all: 
	make $(PROGRAM_NAME1) 
	make $(PROGRAM_NAME2) 
	make $(PROGRAM_NAME3) 
	make $(PROGRAM_NAME4) 


clean:
	(rm -f *.o;)

(:
