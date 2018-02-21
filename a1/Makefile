all:
	gcc-7 -o filter_serial -O0 -fopenmp filter_serial.c
	gcc-7 -o filter_parallel -O0 -fopenmp filter_parallel.c
	gcc-7 -o filter_parallel_dynamic -O0 -fopenmp filter_parallel_dynamic.c
	gcc-7 -o filter_parallel_unrolling -O0 -fopenmp filter_parallel_unrolling.c

clean:
	rm filter_serial filter_parallel filter_parallel_dynamic filter_parallel_unrolling
