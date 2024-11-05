# Compiler and flags
CC = g++
CFLAGS = -fopenmp -O2 -lm 
PROF_FLAGS = -pg

# Source file
SRC = $(Pr)

# Parameters 
N_THREADS = $(n)
N_RECTS = $(r)
PARAM = $(Params)

# Targets
TARGET_INTEGRAL = integral
TARGET_MANDELBROT = mandelbrot

# Directories
PROFILE_DIR = profiles
OUT_DIR = out


# Default target (builds both programs)
all: $(TARGET_INTEGRAL) $(TARGET_MANDELBROT) 

# Conditional build target
build:
	$(CC) $(CFLAGS) -o  $(OUT_DIR)/$(Pr) $(Pr).c

# Conditional run target
run:
	./$(OUT_DIR)/$(SRC) $(n) $(r)



# Profile the specified program
profile:
#   create a folder for the profile file if not exist 
	@mkdir -p $(OUT_DIR)

	$(CC)  $(CFLAGS) $(PROF_FLAGS)   -o  $(OUT_DIR)/$(SRC) $(SRC).c
	./$(OUT_DIR)/$(SRC)  $(n) $(r) 

	gprof $(OUT_DIR)/$(SRC) gmon.out > $(PROFILE_DIR)/$(Pr)_profile.txt
	
	cat $(PROFILE_DIR)/$(Pr)_profile.txt

# Time measurement rule
time: 
	@echo "Timing execution of $(Pr) with $(n) threads "
	@time $(OUT_DIR)/$(Pr) $(n) $(r) >> /dev/null


# Build each program individually
$(TARGET_INTEGRAL): integral.c
	$(CC) $(CFLAGS) -o $(OUT_DIR)/$(TARGET_INTEGRAL) integral.c

$(TARGET_MANDELBROT): mandelbrot.c
	$(CC) $(CFLAGS) -o $(OUT_DIR)/$(TARGET_MANDELBROT) mandelbrot.c

# Clean command
clean:
	rm -rf $(OUT_DIR)/* $(PROFILE_DIR)/*  gmon.out
