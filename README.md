# OpsPerformance

## Description
Estimate the performance of processor can provide by matrix multiplication.

## Environment
1. Raspberry Pi 3 B+

## NEON
NEON is supported in A53 and SIMD can help on the performance. The size of register for SIMD is fixed in 128 bits, so for single precision and double precision floating-point calculation, it can provide different number of data at once.
1. Single Precision (32-bit): 4 number at once.
2. Double Precision (64-bit): 2 number at once.

## Result

![Screenshot](https://github.com/CheAnLee/OpsPerformance/blob/master/picture/FL_benchmark_A53.png)
