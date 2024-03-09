#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MONTHS 12

// Function to compare values for qsort.
int compare(const void* a, const void* b) {
    double diff = *(double*)a - *(double*)b;
    return (diff > 0) - (diff < 0);
}

// Function to calculate the moving average.
void moving_average(double sales[], double mov_avg[]) {
    for (int i = 0; i <= MONTHS - 6; i++) {
        double sum = 0.0;
        for (int j = i; j < i + 6; j++) {
            sum += sales[j];
        }
        mov_avg[i] = sum / 6;
    }
}

// Function to print the sales report.
void print_sales_report(const double sales[], const char *months[]) {
    printf("Monthly sales report for 2022:\n");
    printf("Month        Sales\n");
    for (int i = 0; i < MONTHS; i++) {
        printf("%-12s $%.2f\n", months[i], sales[i]);
    }
}

// Function to print the sales summary.
void print_sales_summary(double sales[], const char *months[]) {
    double total = 0.0, min = sales[0], max = sales[0];
    int min_month = 0, max_month = 0;

    for (int i = 0; i < MONTHS; i++) {
        total += sales[i];
        if (sales[i] < min) {
            min = sales[i];
            min_month = i;
        }
        if (sales[i] > max) {
            max = sales[i];
            max_month = i;
        }
    }

    printf("\nSales summary:\n");
    printf("Minimum sales: $%.2f (%s)\n", min, months[min_month]);
    printf("Maximum sales: $%.2f (%s)\n", max, months[max_month]);
    printf("Average sales: $%.2f\n", total / MONTHS);
}

// Function to print the six-month moving average report.
void print_moving_average(double mov_avg[]) {
    const char *months[] = {"January", "February", "March", "April", "May", "June",
                            "July", "August", "September", "October", "November", "December"};
    printf("\nSix-Month Moving Average Report:\n");
    for (int i = 0; i <= MONTHS - 6; i++) {
        printf("%s - %s $%.2f\n", months[i], months[i+5], mov_avg[i]);
    }
}

// Main program
int main() {
    double sales[MONTHS], mov_avg[MONTHS - 5];
    const char *months[MONTHS] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    // Replace "sales_data.txt" with the path to your sales data file.
    FILE* file = fopen("sales_data.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read sales data from file.
    for (int i = 0; i < MONTHS && fscanf(file, "%lf", &sales[i]) == 1; i++);
    fclose(file);

    // Print the sales report.
    print_sales_report(sales, months);

    // Calculate and print the sales summary.
    print_sales_summary(sales, months);

    // Calculate and print the six-month moving average report.
    moving_average(sales, mov_avg);
    print_moving_average(mov_avg);

    // Sort the sales data from highest to lowest and print the report.
    double sorted_sales[MONTHS];
    memcpy(sorted_sales, sales, sizeof(sales));
    qsort(sorted_sales, MONTHS, sizeof(double), compare);
    printf("\nSales Report (Highest to Lowest):\n");
    printf("Month        Sales\n");
    for (int i = MONTHS - 1; i >= 0; i--) {
        // Find the index of the sorted sale in the original array to get the month name.
        for (int j = 0; j < MONTHS; j++) {
            if (sorted_sales[i] == sales[j]) {
                printf("%-12s $%.2f\n", months[j], sorted_sales[i]);
                break;
            }
        }
    }

    return 0;
}
