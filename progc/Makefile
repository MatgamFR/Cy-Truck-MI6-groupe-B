#-----------------------------------------
# VARIABLES
#-----------------------------------------
TEST_EXE = cy_truck
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
BUILD_DIR=build
OBJ2=$(addprefix $(BUILD_DIR)/, $(OBJ))

#-----------------------------------------
# REBUILD
#-----------------------------------------
all : $(TEST_EXE) 

#-----------------------------------------
# MAIN
#-----------------------------------------

$(BUILD_DIR)/%.o: %.c truck.h $(BUILD_DIR)
	@gcc -c $< -o $@

$(TEST_EXE) : $(OBJ2)
	@gcc $^ -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/
	
#-----------------------------------------
# RUN
#-----------------------------------------
run : $(TEST_EXE)
	LD_LIBRARY_PATH=./$(LIB_DIR) ./$(TEST_EXE) 2> err.log


#-----------------------------------------
# CLEAN / REBUILD
#-----------------------------------------
clean :
	@echo "Removing library..."
	@rm -f $(BUILD_DIR)/*.o
	@echo "Removing test executable..."
	@rm -f $(TEST_EXE)
	
rebuild : clean $(TEST_EXE)	

