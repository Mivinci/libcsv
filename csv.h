#ifndef LIBCSV_H
#define LIBCSV_H

#include <sys/types.h>

#define CSV_MAX_BUF 2048
#define CSV_START 0;
#define CSV_END 1
#define CSV_ERR -1;
#define CSV_OK 0;

struct csv {
    int fd;
    int n;
    size_t cur;
    size_t bytes_read;
    char sep;
    char buf[CSV_MAX_BUF];
    char **fields;
};

int csv_open(struct csv *csv, const char *path, char sep, int n);
int csv_close(struct csv *csv);
void csv_reset(struct csv *csv);
int csv_read_next(struct csv *csv, char ***fields);

#endif 