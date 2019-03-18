# -----------------------------------------
# PROJECT: table
# AUTHOR : Tommy Wu (7852291)
# -----------------------------------------

# Adopted from the makefile given in class

#---------------------------------------------------------------------
# C++ COMPILER, COMPILER FLAGS, AND TARGET PROGRAM NAME
#---------------------------------------------------------------------
TARGET1  =./bin/test/test1
TARGET2  =./bin/test/test2
TARGET3  =./bin/test/test3
TARGET4  =./bin/test/test4
TARGET5  =./bin/test/test5
TARGET6  =./bin/test/test6
DIR_SRC  =./src/
DIR_OBJS =./.objects
CC       =clang
CCFLAGS  =-Wall -DNDEBUG 


#---------------------------------------------------------------------
# FILES
#---------------------------------------------------------------------
# We list all files here to make our life easier in specifying dependencies
# \ means the line is not ended. Normally HEADER=header1.h header2.h
# But we want to separate lines so they look nicer.
HEADERS=./header/set.h

SOURCES=./src/main.c

MAIN_OBJECT=$(DIR_OBJS)/main.o

TEST_OBJECT1 = ./bin/set-trial1/set.o
TEST_OBJECT2 = ./bin/set-trial2/set.o
TEST_OBJECT3 = ./bin/set-trial3/set.o
TEST_OBJECT4 = ./bin/set-trial4/set.o
TEST_OBJECT5 = ./bin/set-trial5/set.o
TEST_OBJECT6 = ./bin/set-trial6/set.o


#---------------------------------------------------------------------
# COMPILING RULES
#---------------------------------------------------------------------
# First rule is default, that is, if you don't specify specific rule, makefile will use the first rule.
default: $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5) $(TARGET6)

# Link compiled objects and create an executable binary.
# It requires to have directory for objects and to compile objects
$(TARGET1): check_headers make_directory  $(MAIN_OBJECT)
	$(CC)  $(MAIN_OBJECT) $(TEST_OBJECT1) -o $@

$(TARGET2): check_headers make_directory  $(MAIN_OBJECT)
	$(CC)  $(MAIN_OBJECT) $(TEST_OBJECT2) -o $@

$(TARGET3): check_headers make_directory  $(MAIN_OBJECT)
	$(CC)  $(MAIN_OBJECT) $(TEST_OBJECT3) -o $@

$(TARGET4): check_headers make_directory  $(MAIN_OBJECT)
	$(CC)  $(MAIN_OBJECT) $(TEST_OBJECT4) -o $@

$(TARGET5): check_headers make_directory  $(MAIN_OBJECT)
	$(CC)  $(MAIN_OBJECT) $(TEST_OBJECT5) -o $@

$(TARGET6): check_headers make_directory  $(MAIN_OBJECT)
	$(CC)  $(MAIN_OBJECT) $(TEST_OBJECT6) -o $@


check_headers: $(HEADERS)

make_directory:
	mkdir -p $(DIR_OBJS)/

# Compile C files
$(DIR_OBJS)/%.o: $(DIR_SRC)%.c
	$(CC) $(CCFLAGS) -c $? -o $@

# Clean removes every object and binary
clean:
	rm -rf $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5) $(TARGET6) $(MAIN_OBJECT) $(DIR_OBJS)/


#---------------------------------------------------------------------
# END OF MAKEFILE
#---------------------------------------------------------------------
