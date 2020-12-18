#include <stdio.h>
#include <csv.h>

int main() {
    struct csv file;
    char **fields;
    csv_open(&file, "testdata.csv", ',', 3);

    while (csv_read_next(&file, &fields) != CSV_END) {
        printf("%s ", fields[0]);
        printf("%s ", fields[1]);
        printf("%s ", fields[2]);
        printf("\n");
    }

    printf("%d\n", csv_read_next(&file, &fields));
    csv_reset(&file);
    printf("%d\n", csv_read_next(&file, &fields));
    printf("%s ", fields[0]);
        printf("%s ", fields[1]);
        printf("%s ", fields[2]);

    csv_close(&file);
    return 0;
}
