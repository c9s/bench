/**
 * bench.h
 * Copyright (C) 2014 c9s <c9s@c9smba.local>
 *
 * Distributed under terms of the MIT license.
 */
#ifndef BENCH_H
#define BENCH_H

#include <stdlib.h>

#define MICRO_IN_SEC 1000000.00
#define SEC_IN_MIN 60
#define NUL  '\0'

typedef struct {
    long N; // N for each run
    long R; // runs
    double secs;
    double start;
    double end;
} bench;

unsigned long unixtime();

double microtime();

void bench_start(bench *b);

void bench_stop(bench *b);

double bench_iteration_speed(bench *b);

void bench_print_summary(bench *b);

double bench_duration(bench *b);

void bench_csv_append(char *filename, int countOfB, ...);

void bench_csv_write(char *filename, int countOfB, ...);

#define MEASURE(B) \
        bench B; B.N = 1; B.R = 1; \
        printf("Measuring " #B "...\n"); \
        bench_start(&B);

#define END_MEASURE(B) \
        bench_stop(&B);

#define BENCHMARK(B, RUN) \
        bench B; \
        B.N = 100000; \
        B.R = RUN; \
        printf("Benchmarking " #B "...\n"); \
        bench_start(&B); \
        for (int ##_r = 0; ##_r < B.R ; ##_r++ ) { \
            for (int ##_i = 0; ##_i < B.N ; ##_i++ ) {

#define END_BENCHMARK(B) \
            } \
        } \
        bench_stop(&B);

#define BENCHMARK_SUMMARY(B) bench_print_summary(&B);

#define BENCHMARK_CSV_APPEND(filename, countOfB, ...) \
    bench_csv_append(filename, countOfB, __VA_ARGS__)

#define BENCHMARK_CSV_WRITE(filename, countOfB, ...) \
    bench_csv_write(filename, countOfB, __VA_ARGS__)

#define BR(b) &b

#endif /* !BENCH_H */
