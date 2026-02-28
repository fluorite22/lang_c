#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Structure for date difference
typedef struct {
    int years;
    int months;
    int days;
} DateDifference;

// Structure for date
typedef struct {
    int year;
    int month;
    int day;
} Date;

// Check leap year
bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Get days in month
int days_in_month(int year, int month) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (month == 2 && is_leap_year(year)) {
        return 29;
    }
    
    if (month < 1 || month > 12) {
        return 0;
    }
    
    return days[month - 1];
}

// Validate date
bool is_valid_date(int year, int month, int day) {
    if (year < 1 || year > 9999) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > days_in_month(year, month)) return false;
    
    return true;
}

// Parse date string YYYY-MM-DD
bool parse_date_string(const char* date_str, Date* date) {
    int year, month, day;
    
    // Check format YYYY-MM-DD
    if (strlen(date_str) != 10 || date_str[4] != '-' || date_str[7] != '-') {
        return false;
    }
    
    // Extract parts
    char year_str[5], month_str[3], day_str[3];
    
    strncpy(year_str, date_str, 4);
    year_str[4] = '\0';
    
    strncpy(month_str, date_str + 5, 2);
    month_str[2] = '\0';
    
    strncpy(day_str, date_str + 8, 2);
    day_str[2] = '\0';
    
    // Check all characters are digits
    for (int i = 0; i < 4; i++) {
        if (!isdigit(year_str[i])) return false;
    }
    for (int i = 0; i < 2; i++) {
        if (!isdigit(month_str[i])) return false;
        if (!isdigit(day_str[i])) return false;
    }
    
    // Convert to numbers
    year = atoi(year_str);
    month = atoi(month_str);
    day = atoi(day_str);
    
    // Validate date
    if (!is_valid_date(year, month, day)) {
        return false;
    }
    
    date->year = year;
    date->month = month;
    date->day = day;
    
    return true;
}

// Get current date
void get_current_date(Date* current_date) {
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    
    current_date->year = tm_info->tm_year + 1900;
    current_date->month = tm_info->tm_mon + 1;
    current_date->day = tm_info->tm_mday;
}

// Calculate difference between dates
DateDifference calculate_date_difference(Date start_date, Date end_date) {
    DateDifference diff = {0, 0, 0};
    
    // Ensure start_date <= end_date
    if (start_date.year > end_date.year ||
        (start_date.year == end_date.year && start_date.month > end_date.month) ||
        (start_date.year == end_date.year && start_date.month == end_date.month && start_date.day > end_date.day)) {
        Date temp = start_date;
        start_date = end_date;
        end_date = temp;
    }
    
    // Calculate days difference
    diff.days = end_date.day - start_date.day;
    
    // Adjust negative days
    if (diff.days < 0) {
        end_date.month--;
        
        if (end_date.month < 1) {
            end_date.month = 12;
            end_date.year--;
        }
        
        diff.days += days_in_month(end_date.year, end_date.month);
    }
    
    // Calculate months difference
    diff.months = end_date.month - start_date.month;
    
    // Adjust negative months
    if (diff.months < 0) {
        diff.months += 12;
        end_date.year--;
    }
    
    // Calculate years difference
    diff.years = end_date.year - start_date.year;
    
    return diff;
}

// Print date difference
void print_date_difference(DateDifference diff) {
    printf("%d years, %d months, %d days\n", diff.years, diff.months, diff.days);
}

// Clear input buffer
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Interactive mode
void interactive_mode() {
    char date_str[20];
    Date input_date, current_date;
    DateDifference diff;
    
    printf("=== Date Difference Calculator ===\n");
    printf("Enter date in format YYYY-MM-DD\n");
    printf("Example: 1990-05-15\n");
    printf("Date: ");
    
    if (fgets(date_str, sizeof(date_str), stdin) == NULL) {
        printf("Input error!\n");
        return;
    }
    
    date_str[strcspn(date_str, "\n")] = '\0';
    
    if (!parse_date_string(date_str, &input_date)) {
        printf("Error: invalid date format!\n");
        printf("Use format YYYY-MM-DD, example: 1990-05-15\n");
        return;
    }
    
    get_current_date(&current_date);
    
    // Check if date is in future
    if (input_date.year > current_date.year ||
        (input_date.year == current_date.year && input_date.month > current_date.month) ||
        (input_date.year == current_date.year && input_date.month == current_date.month && input_date.day > current_date.day)) {
        printf("Error: date is in the future!\n");
        return;
    }
    
    diff = calculate_date_difference(input_date, current_date);
    
    printf("\nPassed: ");
    print_date_difference(diff);
    
    printf("\nDetails:\n");
    printf("  Years: %d\n", diff.years);
    printf("  Months: %d\n", diff.months);
    printf("  Days: %d\n", diff.days);
}

// Example mode
void example_mode() {
    printf("=== Program Examples ===\n\n");
    
    Date current_date;
    get_current_date(&current_date);
    printf("Current date: %04d-%02d-%02d\n\n", 
           current_date.year, current_date.month, current_date.day);
    
    const char* test_dates[] = {
        "1990-05-15",
        "2000-12-31",
        "2020-01-01",
        "2015-03-10"
    };
    
    int num_tests = sizeof(test_dates) / sizeof(test_dates[0]);
    
    for (int i = 0; i < num_tests; i++) {
        Date test_date;
        
        if (parse_date_string(test_dates[i], &test_date)) {
            DateDifference diff = calculate_date_difference(test_date, current_date);
            
            printf("Date %s: ", test_dates[i]);
            print_date_difference(diff);
        } else {
            printf("Date %s: Parse error\n", test_dates[i]);
        }
    }
}

// Compare two dates
void compare_dates_mode() {
    char date1_str[20], date2_str[20];
    Date date1, date2;
    DateDifference diff;
    
    printf("=== Compare Two Dates ===\n");
    
    printf("Enter first date (YYYY-MM-DD): ");
    fgets(date1_str, sizeof(date1_str), stdin);
    date1_str[strcspn(date1_str, "\n")] = '\0';
    
    if (!parse_date_string(date1_str, &date1)) {
        printf("Error in first date!\n");
        return;
    }
    
    printf("Enter second date (YYYY-MM-DD): ");
    fgets(date2_str, sizeof(date2_str), stdin);
    date2_str[strcspn(date2_str, "\n")] = '\0';
    
    if (!parse_date_string(date2_str, &date2)) {
        printf("Error in second date!\n");
        return;
    }
    
    diff = calculate_date_difference(date1, date2);
    
    printf("\nDifference between dates:\n");
    printf("  From %04d-%02d-%02d to %04d-%02d-%02d\n",
           date1.year, date1.month, date1.day,
           date2.year, date2.month, date2.day);
    printf("  Is: ");
    print_date_difference(diff);
}

// Age calculator
void age_calculator_mode() {
    char birth_date_str[20];
    Date birth_date, current_date;
    DateDifference diff;
    
    printf("=== Age Calculator ===\n");
    printf("Enter birth date (YYYY-MM-DD): ");
    
    fgets(birth_date_str, sizeof(birth_date_str), stdin);
    birth_date_str[strcspn(birth_date_str, "\n")] = '\0';
    
    if (!parse_date_string(birth_date_str, &birth_date)) {
        printf("Invalid date format!\n");
        return;
    }
    
    get_current_date(&current_date);
    
    // Check if birth date is in future
    if (birth_date.year > current_date.year ||
        (birth_date.year == current_date.year && birth_date.month > current_date.month) ||
        (birth_date.year == current_date.year && birth_date.month == current_date.month && birth_date.day > current_date.day)) {
        printf("Birth date cannot be in the future!\n");
        return;
    }
    
    diff = calculate_date_difference(birth_date, current_date);
    
    printf("\nYour age:\n");
    printf("  ");
    print_date_difference(diff);
    
    // Additional info
    printf("\nAdditional information:\n");
    printf("  Total months: %d\n", diff.years * 12 + diff.months);
    
    long total_days_approx = diff.years * 365 + diff.months * 30 + diff.days;
    printf("  Total days (approx): %ld\n", total_days_approx);
    printf("  Total weeks (approx): %ld\n", total_days_approx / 7);
}

// Check date validity
void check_date_validity() {
    char date_str[20];
    Date date;
    
    printf("=== Check Date Validity ===\n");
    printf("Enter date to check (YYYY-MM-DD): ");
    fgets(date_str, sizeof(date_str), stdin);
    date_str[strcspn(date_str, "\n")] = '\0';
    
    if (parse_date_string(date_str, &date)) {
        printf("Date %s is valid!\n", date_str);
        
        if (is_leap_year(date.year)) {
            printf("Year %d is leap year\n", date.year);
        } else {
            printf("Year %d is not leap year\n", date.year);
        }
        
        printf("Month %d of year %d has %d days\n", 
               date.month, date.year, days_in_month(date.year, date.month));
    } else {
        printf("Date %s is invalid!\n", date_str);
    }
}

// Show menu
void show_menu() {
    int choice;
    
    while (1) {
        printf("\n====================================\n");
        printf("    DATE DIFFERENCE CALCULATOR\n");
        printf("====================================\n");
        printf("1. Interactive calculation\n");
        printf("2. Test examples\n");
        printf("3. Age calculator\n");
        printf("4. Compare two dates\n");
        printf("5. Check date validity\n");
        printf("0. Exit\n");
        printf("\nChoose action (0-5): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            clear_input_buffer();
            continue;
        }
        
        clear_input_buffer();
        
        switch (choice) {
            case 1:
                printf("\n");
                interactive_mode();
                break;
                
            case 2:
                printf("\n");
                example_mode();
                break;
                
            case 3:
                printf("\n");
                age_calculator_mode();
                break;
                
            case 4:
                printf("\n");
                compare_dates_mode();
                break;
                
            case 5:
                printf("\n");
                check_date_validity();
                break;
                
            case 0:
                printf("Exiting program...\n");
                return;
                
            default:
                printf("Invalid choice! Please choose 0-5.\n");
        }
        
        printf("\nPress Enter to continue...");
        getchar();
    }
}

// Simple version
void simple_version() {
    char date_str[20];
    Date input_date, current_date;
    
    printf("=== Simple Date Calculator ===\n");
    printf("Enter date (YYYY-MM-DD): ");
    
    fgets(date_str, sizeof(date_str), stdin);
    date_str[strcspn(date_str, "\n")] = '\0';
    
    if (!parse_date_string(date_str, &input_date)) {
        printf("Invalid date format!\n");
        return;
    }
    
    get_current_date(&current_date);
    
    if (input_date.year > current_date.year ||
        (input_date.year == current_date.year && input_date.month > current_date.month) ||
        (input_date.year == current_date.year && input_date.month == current_date.month && input_date.day > current_date.day)) {
        printf("Date is in the future!\n");
        return;
    }
    
    DateDifference diff = calculate_date_difference(input_date, current_date);
    
    printf("Passed: ");
    print_date_difference(diff);
}

// Main function
int main() {
    // Set UTF-8 for Windows
    #ifdef _WIN32
        system("chcp 65001 > nul");
    #endif
    
    printf("Date Difference Calculator\n");
    printf("===========================\n\n");
    
    show_menu();
    
    return 0;
}
