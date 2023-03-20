# Executable name
NAME	:= BCH_Cartolas_txt_a_csv

# Compiler options
CC		:= c++
CFLAGS	:= -std=c++17

# Program output directory
OUT_DIR	:= output/

# Source files
SRC_FIL := main.cpp
SRC_DIR	:= src/
SRCS	:= $(addprefix $(SRC_DIR), $(SRC_FIL))

# Make executable
$(NAME): $(SRCS) | $(OUT_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Make output directory
$(OUT_DIR):
	mkdir -p $@

# Clean all program files
clean:
	rm -f $(NAME)
	rm -rf $(OUT_DIR)

.PHONY: clean
