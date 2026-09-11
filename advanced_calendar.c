#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

// Japanese month names (Hiragana)
const char* japanese_months[] = {
    "睦月", "如月", "弥生", "卯月", "皐月", "水無月",
    "文月", "葉月", "長月", "神無月", "霜月", "師走"
};

// Japanese day names
const char* japanese_days[] = {
    "日", "月", "火", "水", "木", "金", "土"
};

// Japanese holidays
typedef struct {
    int month;
    int day;
    char name[50];
} Holiday;

Holiday holidays[] = {
    {1, 1, "元日"},
    {1, 8, "成人の日"},
    {2, 11, "建国記念の日"},
    {2, 23, "天皇誕生日"},
    {3, 20, "春分の日"},
    {4, 29, "昭和の日"},
    {5, 3, "憲法記念日"},
    {5, 4, "みどりの日"},
    {5, 5, "子どもの日"},
    {7, 15, "海の日"},
    {8, 11, "山の日"},
    {9, 16, "敬老の日"},
    {9, 23, "秋分の日"},
    {10, 10, "体育の日"},
    {11, 3, "文化の日"},
    {11, 23, "勤労感謝の日"},
    {0, 0, ""}
};

// Get the first day of the month
int getFirstDayOfMonth(int year, int month) {
    struct tm timeinfo = {0};
    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mon = month - 1;
    timeinfo.tm_mday = 1;
    mktime(&timeinfo);
    return timeinfo.tm_wday;
}

// Get days in a month
int getDaysInMonth(int year, int month) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        return 29;
    }
    return days[month - 1];
}

// Check if a day is a holiday
const char* getHolidayName(int month, int day) {
    for (int i = 0; holidays[i].month != 0; i++) {
        if (holidays[i].month == month && holidays[i].day == day) {
            return holidays[i].name;
        }
    }
    return NULL;
}

// Print calendar with colors
void printJapaneseCalendarWithColors(int year, int month) {
    printf("\n");
    printf("\033[1;36m");  // Cyan color
    printf("       %d年 %s\n", year, japanese_months[month - 1]);
    printf("════════════════════════════════════════\n");
    printf("\033[0m");  // Reset color
    
    // Print day headers
    printf("\033[1;33m");  // Yellow color
    for (int i = 0; i < 7; i++) {
        printf("  %s  ", japanese_days[i]);
    }
    printf("\n");
    printf("════════════════════════════════════════\n");
    printf("\033[0m");  // Reset color
    
    int firstDay = getFirstDayOfMonth(year, month);
    int daysInMonth = getDaysInMonth(year, month);
    
    // Print empty spaces
    for (int i = 0; i < firstDay; i++) {
        printf("     ");
    }
    
    // Print days
    for (int day = 1; day <= daysInMonth; day++) {
        const char* holiday = getHolidayName(month, day);
        
        if (holiday) {
            printf("\033[1;31m");  // Red for holidays
        } else if ((firstDay + day - 1) % 7 == 0) {
            printf("\033[1;31m");  // Red for Sundays
        } else if ((firstDay + day - 1) % 7 == 6) {
            printf("\033[1;34m");  // Blue for Saturdays
        }
        
        printf("%3d  ", day);
        printf("\033[0m");  // Reset color
        
        if ((firstDay + day) % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n");
    printf("════════════════════════════════════════\n");
}

// Print calendar with holiday details
void printCalendarWithHolidays(int year, int month) {
    printf("\n\033[1;36m");
    printf("       %d年 %s (祝日付き)\n", year, japanese_months[month - 1]);
    printf("════════════════════════════════════════\n");
    printf("\033[0m");
    
    // Print day headers
    printf("\033[1;33m");
    for (int i = 0; i < 7; i++) {
        printf("  %s  ", japanese_days[i]);
    }
    printf("\n");
    printf("════════════════════════════════════════\n");
    printf("\033[0m");
    
    int firstDay = getFirstDayOfMonth(year, month);
    int daysInMonth = getDaysInMonth(year, month);
    
    for (int i = 0; i < firstDay; i++) {
        printf("     ");
    }
    
    for (int day = 1; day <= daysInMonth; day++) {
        const char* holiday = getHolidayName(month, day);
        
        if (holiday) {
            printf("\033[1;31m%3d✱ \033[0m", day);
        } else if ((firstDay + day - 1) % 7 == 0) {
            printf("\033[1;31m%3d  \033[0m", day);
        } else if ((firstDay + day - 1) % 7 == 6) {
            printf("\033[1;34m%3d  \033[0m", day);
        } else {
            printf("%3d  ", day);
        }
        
        if ((firstDay + day) % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n");
    
    // Print holidays list
    printf("\033[1;31m祝日:\033[0m\n");
    for (int i = 0; holidays[i].month != 0; i++) {
        if (holidays[i].month == month) {
            printf("  %d月%d日: %s\n", holidays[i].month, holidays[i].day, holidays[i].name);
        }
    }
    printf("════════════════════════════════════════\n");
}

// Print year overview (all 12 months)
void printYearOverview(int year) {
    printf("\n\033[1;35m");
    printf("═══════════════════════════════════════════════════════\n");
    printf("            %d年 (Japanese Calendar)\n", year);
    printf("═══════════════════════════════════════════════════════\n");
    printf("\033[0m");
    
    for (int month = 1; month <= 12; month++) {
        printf("\033[1;33m%s\033[0m ", japanese_months[month - 1]);
        
        int firstDay = getFirstDayOfMonth(year, month);
        int daysInMonth = getDaysInMonth(year, month);
        
        for (int i = 0; i < firstDay; i++) {
            printf("  ");
        }
        
        for (int day = 1; day <= daysInMonth; day++) {
            if ((firstDay + day - 1) % 7 == 0) {
                printf("\033[1;31m%2d\033[0m ", day);
            } else if ((firstDay + day - 1) % 7 == 6) {
                printf("\033[1;34m%2d\033[0m ", day);
            } else {
                printf("%2d ", day);
            }
            
            if ((firstDay + day) % 7 == 0) {
                printf("\n           ");
            }
        }
        printf("\n\n");
    }
    printf("═══════════════════════════════════════════════════════\n");
}

// Interactive menu
void interactiveMode() {
    time_t now = time(NULL);
    struct tm* timeinfo = localtime(&now);
    int year = timeinfo->tm_year + 1900;
    int month = timeinfo->tm_mon + 1;
    
    int choice;
    
    while (1) {
        printf("\n\033[1;36m╔════════════════════════════════════╗\033[0m\n");
        printf("\033[1;36m║    日本カレンダー (Japanese Calendar)   ║\033[0m\n");
        printf("\033[1;36m╠════════════════════════════════════╣\033[0m\n");
        printf("\033[1;36m║\033[0m 1. 現在の月を表示 (Show Current Month)\n");
        printf("\033[1;36m║\033[0m 2. 指定した月を表示 (Show Custom Month)\n");
        printf("\033[1;36m║\033[0m 3. 祝日付きで表示 (Show with Holidays)\n");
        printf("\033[1;36m║\033[0m 4. 年間カレンダー (Year Overview)\n");
        printf("\033[1;36m║\033[0m 5. 次の月へ (Next Month)\n");
        printf("\033[1;36m║\033[0m 6. 前の月へ (Previous Month)\n");
        printf("\033[1;36m║\033[0m 7. 終了 (Exit)\n");
        printf("\033[1;36m╚════════════════════════════════════╝\033[0m\n");
        printf("選択してください (Choose): ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printJapaneseCalendarWithColors(year, month);
                break;
            
            case 2: {
                int y, m;
                printf("年を入力 (Enter year): ");
                scanf("%d", &y);
                printf("月を入力 (Enter month 1-12): ");
                scanf("%d", &m);
                if (y > 0 && m >= 1 && m <= 12) {
                    printJapaneseCalendarWithColors(y, m);
                } else {
                    printf("\033[1;31m無効な入力です (Invalid input)\033[0m\n");
                }
                break;
            }
            
            case 3:
                printCalendarWithHolidays(year, month);
                break;
            
            case 4:
                printYearOverview(year);
                break;
            
            case 5:
                month++;
                if (month > 12) {
                    month = 1;
                    year++;
                }
                printf("→ %d年 %s に移動しました\n", year, japanese_months[month - 1]);
                break;
            
            case 6:
                month--;
                if (month < 1) {
                    month = 12;
                    year--;
                }
                printf("← %d年 %s に移動しました\n", year, japanese_months[month - 1]);
                break;
            
            case 7:
                printf("\033[1;32mさようなら！(Goodbye!)\033[0m\n");
                exit(0);
            
            default:
                printf("\033[1;31m無効な選択です (Invalid choice)\033[0m\n");
        }
    }
}

int main() {
    printf("\033[1;35m");
    printf("╔═════════════════════════════════════════╗\n");
    printf("║   🗓️  高度な日本カレンダープログラム 🗓️  ║\n");
    printf("║    Advanced Japanese Calendar Program   ║\n");
    printf("╚═════════════════════════════════════════╝\n");
    printf("\033[0m");
    
    interactiveMode();
    
    return 0;
}
