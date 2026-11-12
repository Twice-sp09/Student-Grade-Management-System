#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
#define SUBJECTS 5

struct Student {
    int rollNo;
    char name[100];
    float marks[SUBJECTS];
    float total;
    float average;
    char grade[3];
};

struct Student students[MAX_STUDENTS];
int studentCount = 0;

int readInt(const char *message) {
    char line[100];
    char *end;
    long value;

    while (1) {
        printf("%s", message);
        if (fgets(line, sizeof(line), stdin) == NULL)
            exit(0);

        value = strtol(line, &end, 10);
        if (end != line && *end == '\n' &&
            value >= -2147483647L && value <= 2147483647L)
            return (int)value;

        printf("Invalid input! Please enter a whole number.\n");
    }
}

float readMarks(const char *message) {
    char line[100];
    char *end;
    float value;

    while (1) {
        printf("%s", message);
        if (fgets(line, sizeof(line), stdin) == NULL)
            exit(0);

        value = strtof(line, &end);
        if (end != line && *end == '\n' &&
            value >= 0 && value <= 100)
            return value;

        printf("Invalid marks! Enter a value between 0 and 100.\n");
    }
}

void calculateGrade(struct Student *s) {
    int i;
    s->total = 0;

    for (i = 0; i < SUBJECTS; i++)
        s->total += s->marks[i];

    s->average = s->total / SUBJECTS;

    if (s->average >= 90)
        strcpy(s->grade, "A+");
    else if (s->average >= 80)
        strcpy(s->grade, "A");
    else if (s->average >= 70)
        strcpy(s->grade, "B");
    else if (s->average >= 60)
        strcpy(s->grade, "C");
    else if (s->average >= 50)
        strcpy(s->grade, "D");
    else
        strcpy(s->grade, "F");
}

int searchStudent(int rollNo) {
    int i;
    for (i = 0; i < studentCount; i++) {
        if (students[i].rollNo == rollNo)
            return i;
    }
    return -1;
}

void addStudent(void) {
    int i;
    char message[100];

    if (studentCount >= MAX_STUDENTS) {
        printf("\nStudent record limit reached!\n");
        return;
    }

    printf("\n--- ADD STUDENT ---\n");
    students[studentCount].rollNo = readInt("Enter Roll Number: ");

    if (students[studentCount].rollNo <= 0) {
        printf("Roll number must be positive!\n");
        return;
    }

    if (searchStudent(students[studentCount].rollNo) != -1) {
        printf("This roll number already exists!\n");
        return;
    }

    printf("Enter Student Name: ");
    if (fgets(students[studentCount].name,
              sizeof(students[studentCount].name), stdin) == NULL)
        return;

    students[studentCount].name[
        strcspn(students[studentCount].name, "\n")] = '\0';

    if (strlen(students[studentCount].name) == 0) {
        printf("Name cannot be empty!\n");
        return;
    }

    for (i = 0; i < SUBJECTS; i++) {
        snprintf(message, sizeof(message),
                 "Enter marks for Subject %d (0-100): ", i + 1);
        students[studentCount].marks[i] = readMarks(message);
    }

    calculateGrade(&students[studentCount]);
    studentCount++;
    printf("\nStudent record added successfully!\n");
}

void displayResult(struct Student s) {
    int i;
    printf("\n----------------------------------------\n");
    printf("          STUDENT RESULT\n");
    printf("----------------------------------------\n");
    printf("Roll Number : %d\n", s.rollNo);
    printf("Name        : %s\n", s.name);

    for (i = 0; i < SUBJECTS; i++)
        printf("Subject %d   : %.2f / 100\n", i + 1, s.marks[i]);

    printf("----------------------------------------\n");
    printf("Total Marks : %.2f / 500\n", s.total);
    printf("Average     : %.2f%%\n", s.average);
    printf("Grade       : %s\n", s.grade);
    printf("----------------------------------------\n");
}

void displayAllStudents(void) {
    int i;
    if (studentCount == 0) {
        printf("\nNo student records available!\n");
        return;
    }

    printf("\n========== ALL STUDENT RECORDS ==========\n");
    printf("%-10s %-20s %-12s %-10s %-8s\n",
           "Roll No", "Name", "Total", "Average", "Grade");
    printf("------------------------------------------------------------\n");

    for (i = 0; i < studentCount; i++) {
        printf("%-10d %-20s %-12.2f %-10.2f %-8s\n",
               students[i].rollNo, students[i].name,
               students[i].total, students[i].average,
               students[i].grade);
    }
}

void searchAndDisplay(void) {
    int rollNo, index;
    printf("\n--- SEARCH STUDENT ---\n");
    rollNo = readInt("Enter Roll Number to Search: ");
    index = searchStudent(rollNo);

    if (index == -1)
        printf("\nStudent record not found!\n");
    else
        displayResult(students[index]);
}

int main(void) {
    int choice;

    printf("========================================\n");
    printf("    STUDENT GRADE MANAGEMENT SYSTEM\n");
    printf("========================================\n");

    do {
        printf("\n-------------- MAIN MENU ---------------\n");
        printf("1. Add Student Record\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by Roll Number\n");
        printf("4. View Total Students\n");
        printf("0. Exit\n");
        printf("----------------------------------------\n");

        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAllStudents(); break;
            case 3: searchAndDisplay(); break;
            case 4: printf("\nTotal Students: %d\n", studentCount); break;
            case 0: printf("\nThank you for using the system!\n"); break;
            default: printf("\nInvalid choice! Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}
