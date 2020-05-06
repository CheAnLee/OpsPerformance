CFLAGS1 = -Wall -march=armv8-a
CFLAGS2 = -Wall -march=armv8-a+simd

OBJ = matrix_multi_fl32.o			\
      matrix_multi_fl32_neon.o		\
      matrix_multi_fl64.o			\
      matrix_multi_fl64_neon.o		\

SRCS = $(OBJ:%.o=%.c)

all:	FL32 FL32_NEON FL64 FL64_NEON INT32 INT32_NEON

FL32:	matrix_multi_fl32.c
	gcc $(CFLAGS1) $^ -o $@

FL32_NEON:	matrix_multi_fl32_neon.c
	gcc $(CFLAGS2) $^ -o $@

FL64:	matrix_multi_fl64.c
	gcc $(CFLAGS1) $^ -o $@

FL64_NEON:	matrix_multi_fl64_neon.c
	gcc $(CFLAGS2) $^ -o $@

INT32:	matrix_multi_int.c
	gcc $(CFLAGS1) $^ -o $@

INT32_NEON:	matrix_multi_int_neon.c
	gcc $(CFLAGS2) $^ -o $@

clean:
	rm FL32 FL32_NEON FL64 FL64_NEON INT32 INT32_NEON
