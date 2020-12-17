#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "csv.h"

int csv_open(struct csv *csv, const char *path, char sep, int n) {
    if((csv->fd = open(path, O_RDWR)) == -1) return -1;
    csv->sep = sep;
    csv->n = n;
    csv->cur = 0;
    csv->bytes_read = 0;
    csv->fields = malloc(sizeof(char*)*n);
    memset(csv->buf, '\0', CSV_MAX_BUF);
    csv->fields[0] = &csv->buf[0];
    return 0;
}

int csv_close(struct csv *csv) {
    free(csv->fields);
    return close(csv->fd);
}

void csv_reset(struct csv *csv) {
    csv->cur = CSV_START;
    csv->fields[0] = &csv->buf[0];
}

int csv_read_next(struct csv *csv, char ***fields) {
    if(csv->bytes_read != 0 && csv->cur >= csv->bytes_read) return CSV_END;

    if(csv->bytes_read == 0) {
        csv->bytes_read = read(csv->fd, csv->buf, CSV_MAX_BUF);
        if(csv->bytes_read == -1) return CSV_ERR;
        csv->cur = CSV_START;
    }

    int col = 0;
    csv->fields[col] = &csv->buf[csv->cur];

    while(csv->buf[csv->cur] != '\n' && col <= csv->n) {
        if(csv->buf[csv->cur] == csv->sep) {
            csv->buf[csv->cur] = '\0';
            csv->fields[++col] = &csv->buf[csv->cur+1];
            *fields = csv->fields;
        }
        csv->cur++;
    }

    csv->buf[csv->cur++] = '\0';
    return CSV_OK;
}

int csv_write(struct csv *csv, char ***fields) {
    return CSV_OK;
}