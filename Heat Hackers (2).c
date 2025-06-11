#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_HISTORY 100
#define MAX_FAVORITES 50


typedef struct {
    float input;
    float output;
    char from[10];
    char to[10];
} Conversion;

Conversion history[MAX_HISTORY];
Conversion favorites[MAX_FAVORITES];
int historyCount = 0, favCount = 0;

HANDLE hConsole;
void setColor(int color) {
    SetConsoleTextAttribute(hConsole, color);
}

void printHeader() {
    setColor(13);
    printf("\n🌡️  =============== TEMPERATURE CONVERTER  ===============🌡️\n");
    printf("╔═══════════════════════════════════════════════════════════════════════╗\n");
    printf("║    🌈 Welcome to Temperature Converter System!                        ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════╝\n");
    setColor(7);
}

int isValidUnit(char *unit) {
    return strcmp(unit, "C") == 0 || strcmp(unit, "F") == 0 || strcmp(unit, "K") == 0;
}

float convertTemp(float temp, char from[], char to[]) {
    if (strcmp(from, "C") == 0 && strcmp(to, "F") == 0)
        return temp * 9 / 5 + 32;
    if (strcmp(from, "F") == 0 && strcmp(to, "C") == 0)
        return (temp - 32) * 5 / 9;
    if (strcmp(from, "C") == 0 && strcmp(to, "K") == 0)
        return temp + 273.15;
    if (strcmp(from, "K") == 0 && strcmp(to, "C") == 0)
        return temp - 273.15;
    if (strcmp(from, "F") == 0 && strcmp(to, "K") == 0)
        return (temp - 32) * 5 / 9 + 273.15;
    if (strcmp(from, "K") == 0 && strcmp(to, "F") == 0)
        return (temp - 273.15) * 9 / 5 + 32;
    return temp;
}

void addToHistory(float in, float out, char from[], char to[]) {
    if (historyCount < MAX_HISTORY) {
        history[historyCount++] = (Conversion){ in, out, "", "" };
        strcpy(history[historyCount - 1].from, from);
        strcpy(history[historyCount - 1].to, to);
    }
}

void showHistory() {
    setColor(6); 
    printf("\n📘 Conversion History:\n");
    for (int i = 0; i < historyCount; i++) {
        printf("  %.2f %s → %.2f %s\n", history[i].input, history[i].from, history[i].output, history[i].to);
    }
    setColor(7);
}

void addToFavorites(Conversion c) {
    if (favCount < MAX_FAVORITES) {
        favorites[favCount++] = c;
        setColor(10); 
        printf("💾 Saved to favorites!\n");
        setColor(7);
    }
}

void showFavorites() {
    setColor(6); 
    printf("\n🌟 Favorite Conversions:\n");
    for (int i = 0; i < favCount; i++) {
        printf("  %.2f %s → %.2f %s\n", favorites[i].input, favorites[i].from, favorites[i].output, favorites[i].to);
    }
    setColor(7);
}

void realWorldContext() {
    setColor(6);
    printf("\n🌍 Real-World Examples:\n");
    printf("  Water freezes at 0°C / 32°F / 273.15K\n");
    printf("  Water boils at 100°C / 212°F / 373.15K\n");
    printf("  Human body temperature: 37°C / 98.6°F / 310.15K\n");
    setColor(7);
}

void quizMode() {
    struct {
        char question[100];
        char answer[10];
    } quiz[] = {
        {"What is the boiling point of water in Celsius?", "100"},
        {"What is 0°C in Fahrenheit?", "32"},
        {"What is absolute zero in Kelvin?", "0"},
        {"What is normal human body temp in Celsius?", "37"},
        {"What is 100°C in Kelvin?", "373"},
        {"What is 98.6°F in Celsius?", "37"}
    };
    int total = sizeof(quiz) / sizeof(quiz[0]);
    int passed = 0;

    for (int i = 0; i < total; i++) {
        char userAns[20];
        int attempts = 0;
        while (attempts < 3) {
            setColor(9); 
            printf("\n🧠 Q%d: %s\n", i + 1, quiz[i].question);
            printf("Your Answer: ");
            setColor(7);
            scanf("%s", userAns);

            if (strcmp(userAns, quiz[i].answer) == 0) {
                setColor(10); 
                printf("🎉 Correct!\n");
                setColor(7);
                passed++;
                break;
            } else {
                attempts++;
                setColor(12); 
                if (attempts == 3)
                    printf("❌ You failed! Correct Answer: %s\n", quiz[i].answer);
                else
                    printf("⚠️ Wrong! Try again (%d/3)\n", attempts);
                setColor(7);
            }
        }
    }

    if (passed == total) {
        setColor(10);
        printf("\n🏆 Woohoo! You aced the quiz!\n");
    } else {
        setColor(3); 
        printf("\n😢 Better luck next time. You got %d out of %d correct.\n", passed, total);
    }
    setColor(7);
}

void mainMenu() {
    int choice;
    float input, result;
    char from[5], to[5], fav;

    do {
        printHeader();
        setColor(15);
        printf("\nMenu:\n");

        setColor(6); 
        printf(" 1. Convert Temperature\n");
        printf(" 2. Temperature Quiz\n");
        printf(" 3. View History\n");
        printf(" 4. View Favorites\n");
        printf(" 5. Real World Info\n");
        printf(" 6. Exit\n");

        setColor(10);
        printf("Enter choice: ");
        setColor(7);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                setColor(6); 
                printf("\n🌡️ Convert Temperature\n");

                setColor(9);
                printf("Enter temperature: ");
                scanf("%f", &input);

                setColor(15);
                printf("From (C/F/K): ");
                scanf("%s", from);

                printf("To (C/F/K): ");
                scanf("%s", to);
                setColor(7);

                if (!isValidUnit(from) || !isValidUnit(to)) {
                    setColor(12);
                    printf("⚠️ Invalid unit entered! Please use only C, F, or K.\n");
                    setColor(7);
                    break;
                }

                result = convertTemp(input, from, to);
                setColor(10);
                printf("✅ Result: %.2f %s → %.2f %s\n", input, from, result, to);
                setColor(7);

                addToHistory(input, result, from, to);

                setColor(14);
                printf("💾 Save to favorites? (y/n): ");
                setColor(7);
                scanf(" %c", &fav);
                if (fav == 'y' || fav == 'Y') {
                    Conversion c = { input, result, "", "" };
                    strcpy(c.from, from);
                    strcpy(c.to, to);
                    addToFavorites(c);
                }
                break;

            case 2:
                quizMode();
                break;

            case 3:
                showHistory();
                break;

            case 4:
                showFavorites();
                break;

            case 5:
                realWorldContext();
                break;

            case 6:
                setColor(13);
                printf("👋 Thank you for using Temperature Converter System!\n");
                setColor(7);
                break;

            default:
                setColor(12);
                printf("⚠️ Invalid choice. Please try again.\n");
                setColor(7);
        }

        printf("\n🔁 Press Enter to continue...");
        getchar(); getchar(); 
    } while (choice != 6);
}


int main() {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
    mainMenu();
    return 0;
}