/* gate_management.c
   Simple Gate Management System (console-based, file-backed)
   Compile: gcc -o gate_management gate_management.c
   Run: ./gate_management
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILE_NAME "gate.dat"
#define PLATE_LEN 32
#define OWNER_LEN 64
#define TIME_LEN 32

typedef struct {
    int id;                     // unique record id
    char plate[PLATE_LEN];      // vehicle plate number
    char owner[OWNER_LEN];      // owner/driver name
    char time_in[TIME_LEN];     // entry timestamp
    char time_out[TIME_LEN];    // exit timestamp (empty if still inside)
    int inside;                 // 1 if currently inside, 0 if exited
} VehicleRecord;

int next_id(void) {
    FILE *f = fopen(FILE_NAME, "rb");
    if (!f) return 1;
    VehicleRecord tmp;
    int last = 0;
    while (fread(&tmp, sizeof(tmp), 1, f) == 1) last = tmp.id;
    fclose(f);
    return last + 1;
}

void timestamp_now(char *buf, size_t n) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(buf, n, "%Y-%m-%d %H:%M:%S", tm);
}

void add_entry() {
    VehicleRecord rec;
    rec.id = next_id();
    printf("Enter plate number: ");
    scanf(" %31[^\n]", rec.plate);
    printf("Enter owner/driver name: ");
    scanf(" %63[^\n]", rec.owner);
    timestamp_now(rec.time_in, sizeof(rec.time_in));
    rec.time_out[0] = '\0';
    rec.inside = 1;

    FILE *f = fopen(FILE_NAME, "ab");
    if (!f) { perror("Unable to open file"); return; }
    fwrite(&rec, sizeof(rec), 1, f);
    fclose(f);

    printf("Entry added: ID %d, Plate %s, Time in %s\n", rec.id, rec.plate, rec.time_in);
}

void mark_exit() {
    char plate[PLATE_LEN];
    printf("Enter plate number to mark exit: ");
    scanf(" %31[^\n]", plate);

    FILE *f = fopen(FILE_NAME, "r+b");
    if (!f) { perror("Unable to open file"); return; }

    VehicleRecord rec;
    int found = 0;
    while (fread(&rec, sizeof(rec), 1, f) == 1) {
        if (rec.inside && strcasecmp(rec.plate, plate) == 0) {
            // mark this record as exited
            found = 1;
            timestamp_now(rec.time_out, sizeof(rec.time_out));
            rec.inside = 0;
            // move file pointer back and overwrite
            fseek(f, -((long)sizeof(rec)), SEEK_CUR);
            fwrite(&rec, sizeof(rec), 1, f);
            printf("Marked exit for ID %d, Plate %s, Time out %s\n", rec.id, rec.plate, rec.time_out);
            break;
        }
    }

    if (!found) printf("No matching vehicle currently inside with plate '%s'.\n", plate);
    fclose(f);
}

void view_all() {
    FILE *f = fopen(FILE_NAME, "rb");
    if (!f) { printf("No records yet.\n"); return; }
    VehicleRecord rec;
    printf("\n%-4s  %-12s  %-15s  %-19s  %-19s  %s\n", "ID", "Plate", "Owner", "Time In", "Time Out", "Status");
    printf("--------------------------------------------------------------------------------------\n");
    while (fread(&rec, sizeof(rec), 1, f) == 1) {
        printf("%-4d  %-12s  %-15s  %-19s  %-19s  %s\n",
               rec.id, rec.plate, rec.owner,
               rec.time_in,
               rec.time_out[0] ? rec.time_out : "-----",
               rec.inside ? "Inside" : "Exited");
    }
    fclose(f);
    printf("\n");
}

void search_plate() {
    char plate[PLATE_LEN];
    printf("Enter plate number to search: ");
    scanf(" %31[^\n]", plate);

    FILE *f = fopen(FILE_NAME, "rb");
    if (!f) { printf("No records.\n"); return; }
    VehicleRecord rec;
    int found = 0;
    while (fread(&rec, sizeof(rec), 1, f) == 1) {
        if (strcasecmp(rec.plate, plate) == 0) {
            if (!found) {
                printf("\nResults:\n");
                printf("%-4s  %-12s  %-15s  %-19s  %-19s  %s\n", "ID", "Plate", "Owner", "Time In", "Time Out", "Status");
                printf("--------------------------------------------------------------------------------------\n");
            }
            found = 1;
            printf("%-4d  %-12s  %-15s  %-19s  %-19s  %s\n",
                   rec.id, rec.plate, rec.owner,
                   rec.time_in,
                   rec.time_out[0] ? rec.time_out : "-----",
                   rec.inside ? "Inside" : "Exited");
        }
    }
    if (!found) printf("No records found for plate '%s'.\n", plate);
    fclose(f);
}

void count_inside() {
    FILE *f = fopen(FILE_NAME, "rb");
    if (!f) { printf("0 vehicles inside.\n"); return; }
    VehicleRecord rec;
    int count = 0;
    while (fread(&rec, sizeof(rec), 1, f) == 1) if (rec.inside) count++;
    fclose(f);
    printf("Vehicles currently inside: %d\n", count);
}

void delete_record() {
    int id;
    printf("Enter record ID to delete: ");
    if (scanf("%d", &id) != 1) { printf("Invalid input.\n"); return; }

    FILE *f = fopen(FILE_NAME, "rb");
    if (!f) { printf("No records.\n"); return; }

    FILE *tmp = fopen("tmp.dat", "wb");
    if (!tmp) { perror("tmp file"); fclose(f); return; }

    VehicleRecord rec;
    int found = 0;
    while (fread(&rec, sizeof(rec), 1, f) == 1) {
        if (rec.id == id) { found = 1; continue; } // skip to delete
        fwrite(&rec, sizeof(rec), 1, tmp);
    }
    fclose(f);
    fclose(tmp);

    if (found) {
        remove(FILE_NAME);
        rename("tmp.dat", FILE_NAME);
        printf("Record ID %d deleted.\n", id);
    } else {
        remove("tmp.dat");
        printf("Record ID %d not found.\n", id);
    }
}

void menu() {
    printf("Gate Management System\n");
    printf("----------------------\n");
    printf("1. Add entry\n");
    printf("2. Mark exit\n");
    printf("3. View all records\n");
    printf("4. Search by plate\n");
    printf("5. Count vehicles inside\n");
    printf("6. Delete a record (by ID)\n");
    printf("0. Exit\n");
}

int main(void) {
    int choice;
    do {
        menu();
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            // clear bad input
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Invalid input. Try again.\n");
            continue;
        }
        switch (choice) {
            case 1: add_entry(); break;
            case 2: mark_exit(); break;
            case 3: view_all(); break;
            case 4: search_plate(); break;
            case 5: count_inside(); break;
            case 6: delete_record(); break;
            case 0: printf("Exiting.\n"); break;
            default: printf("Unknown option. Try again.\n"); break;
        }
    } while (choice != 0);

    return 0;
}
