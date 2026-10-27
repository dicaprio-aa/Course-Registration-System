/*
 * ============================================================
 *  UKF COLLEGE OF ENGINEERING & TECHNOLOGY
 *  COURSE REGISTRATION SYSTEM
 * ------------------------------------------------------------
 *  File        : course.c
 *  Description : Implementation of every function declared in
 *                course.h. Handles all UI screens, validation
 *                logic, binary file I/O and business rules for
 *                the Student, Faculty and Admin modules.
 *  Developed By: RISWANA S3 DS
 * ============================================================
 */

#include "course.h"

/* ============================================================
 *  SECTION 1 : UTILITY / UI FUNCTIONS
 * ============================================================ */

void clearScreen(void)
{
    system("cls");
}

void pauseScreen(void)
{
    printf("\n\tPress any key to continue...");
    getch();
}

void printLine(char ch, int len)
{
    int i;
    for (i = 0; i < len; i++)
        putchar(ch);
    putchar('\n');
}

void printCentered(const char *text, int width)
{
    int len = (int)strlen(text);
    int padding = (width - len) / 2;
    int i;

    if (padding < 0)
        padding = 0;

    for (i = 0; i < padding; i++)
        putchar(' ');

    printf("%s\n", text);
}

void getCurrentDateTimeStr(char *buffer)
{
    time_t now;
    struct tm *localTime;

    time(&now);
    localTime = localtime(&now);

    sprintf(buffer, "%02d-%02d-%04d %02d:%02d:%02d",
            localTime->tm_mday,
            localTime->tm_mon + 1,
            localTime->tm_year + 1900,
            localTime->tm_hour,
            localTime->tm_min,
            localTime->tm_sec);
}

void flushInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/* Reads a password from the console while masking every
 * character typed with an asterisk. Supports backspace. */
void getHiddenPassword(char *password, int maxLen)
{
    int i = 0;
    char ch;

    while (1)
    {
        ch = getch();

        if (ch == 13) /* ENTER key */
        {
            break;
        }
        else if (ch == 8) /* BACKSPACE key */
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            if (i < maxLen - 1)
            {
                password[i] = ch;
                i++;
                printf("*");
            }
        }
    }
    password[i] = '\0';
}

void printSuccess(const char *msg)
{
    printf("\n\t[ SUCCESS ] %s\n", msg);
}

void printError(const char *msg)
{
    printf("\n\t[ ERROR ] %s\n", msg);
}

void printInfo(const char *msg)
{
    printf("\n\t[ INFO ] %s\n", msg);
}

/* Draws the reusable top banner shown at the head of every
 * screen in the application. */
void showMainHeader(const char *title)
{
    clearScreen();
    printLine('=', 70);
    printCentered("UKF COLLEGE OF ENGINEERING & TECHNOLOGY", 70);
    printCentered("COURSE REGISTRATION SYSTEM", 70);
    printLine('-', 70);
    printCentered(title, 70);
    printLine('=', 70);
    printf("\n");
}

/* Animated welcome / boot-up screen shown once when the
 * application starts. Simulates loading of every module. */
void showWelcomeScreen(void)
{
    char dateTimeBuf[30];
    int i;

    clearScreen();
    printLine('*', 70);
    printCentered("WELCOME TO", 70);
    printCentered("UKF COLLEGE OF ENGINEERING & TECHNOLOGY", 70);
    printCentered("COURSE REGISTRATION SYSTEM", 70);
    printLine('*', 70);
    printf("\n");

    getCurrentDateTimeStr(dateTimeBuf);
    printf("\tCurrent Date & Time : %s\n\n", dateTimeBuf);

    printf("\tInitializing System...\n\n");
    Sleep(400);

    printf("\tLoading Student Module   [");
    for (i = 0; i < 20; i++)
    {
        printf("#");
        fflush(stdout);
        Sleep(25);
    }
    printf("] 100%%\n");

    printf("\tLoading Faculty Module   [");
    for (i = 0; i < 20; i++)
    {
        printf("#");
        fflush(stdout);
        Sleep(25);
    }
    printf("] 100%%\n");

    printf("\tLoading Admin Module     [");
    for (i = 0; i < 20; i++)
    {
        printf("#");
        fflush(stdout);
        Sleep(25);
    }
    printf("] 100%%\n");

    printf("\tLoading Database         [");
    for (i = 0; i < 20; i++)
    {
        printf("#");
        fflush(stdout);
        Sleep(25);
    }
    printf("] 100%%\n\n");

    printLine('-', 70);
    printCentered("SYSTEM READY", 70);
    printLine('-', 70);

    printf("\n\tDeveloped By : RISWANA (S3 Data Science)\n");
    pauseScreen();
}

/* Displays details about the project and its developer. */
void aboutUKF(void)
{
    showMainHeader("ABOUT UKF");

    printLine('-', 70);
    printCentered("UKF College of Engineering & Technology", 70);
    printCentered("Course Registration System", 70);
    printLine('-', 70);

    printf("\n\tThis application is a console based Course Registration\n");
    printf("\tSystem developed for UKF College of Engineering &\n");
    printf("\tTechnology. It allows students to register for courses,\n");
    printf("\tfaculty to view assigned courses and registered students,\n");
    printf("\tand administrators to manage the entire course catalogue,\n");
    printf("\tfaculty records and registration reports.\n");

    printf("\n\tDeveloped By\n");
    printf("\t--------------\n");
    printf("\tRISWANA\n");
    printf("\tS3 Data Science\n");

    pauseScreen();
}

/* ============================================================
 *  SECTION 2 : VALIDATION FUNCTIONS
 * ============================================================ */

int isValidSemester(int sem)
{
    if (sem >= 1 && sem <= 8)
        return TRUE;
    return FALSE;
}

/* Accepts a 10 digit numeric phone number. */
int isValidPhone(const char *phone)
{
    int len = (int)strlen(phone);
    int i;

    if (len != 10)
        return FALSE;

    for (i = 0; i < len; i++)
    {
        if (phone[i] < '0' || phone[i] > '9')
            return FALSE;
    }
    return TRUE;
}

/* Basic email validation: must contain exactly one '@' and at
 * least one '.' after the '@', with no spaces. */
int isValidEmail(const char *email)
{
    int len = (int)strlen(email);
    int atCount = 0;
    int atPos = -1;
    int dotAfterAt = FALSE;
    int i;

    if (len < 5)
        return FALSE;

    for (i = 0; i < len; i++)
    {
        if (email[i] == ' ')
            return FALSE;

        if (email[i] == '@')
        {
            atCount++;
            atPos = i;
        }
    }

    if (atCount != 1)
        return FALSE;

    if (atPos == 0 || atPos == len - 1)
        return FALSE;

    for (i = atPos + 1; i < len; i++)
    {
        if (email[i] == '.' && i != len - 1)
            dotAfterAt = TRUE;
    }

    return dotAfterAt;
}

/* Password must be between 4 and (MAX_LEN_PASS - 1) characters
 * and must not contain spaces. */
int isValidPasswordFormat(const char *password)
{
    int len = (int)strlen(password);
    int i;

    if (len < 4 || len >= MAX_LEN_PASS)
        return FALSE;

    for (i = 0; i < len; i++)
    {
        if (password[i] == ' ')
            return FALSE;
    }
    return TRUE;
}

int isDuplicateRegNo(const char *regno)
{
    FILE *fp;
    Student temp;
    int found = FALSE;

    fp = fopen(STUDENT_FILE, "rb");
    if (fp == NULL)
        return FALSE;

    while (fread(&temp, sizeof(Student), 1, fp) == 1)
    {
        if (strcmp(temp.regno, regno) == 0)
        {
            found = TRUE;
            break;
        }
    }

    fclose(fp);
    return found;
}

int isDuplicateFacultyId(const char *facid)
{
    FILE *fp;
    Faculty temp;
    int found = FALSE;

    fp = fopen(FACULTY_FILE, "rb");
    if (fp == NULL)
        return FALSE;

    while (fread(&temp, sizeof(Faculty), 1, fp) == 1)
    {
        if (strcmp(temp.facid, facid) == 0)
        {
            found = TRUE;
            break;
        }
    }

    fclose(fp);
    return found;
}

int isDuplicateCourseCode(const char *code)
{
    FILE *fp;
    Course temp;
    int found = FALSE;

    fp = fopen(COURSE_FILE, "rb");
    if (fp == NULL)
        return FALSE;

    while (fread(&temp, sizeof(Course), 1, fp) == 1)
    {
        if (strcmp(temp.code, code) == 0 && temp.isActive == TRUE)
        {
            found = TRUE;
            break;
        }
    }

    fclose(fp);
    return found;
}

/* ============================================================
 *  SECTION 3 : REGISTRATION HELPER FUNCTIONS
 * ============================================================ */

int isAlreadyRegistered(const char *regno, const char *code)
{
    FILE *fp;
    Registration temp;
    int found = FALSE;

    fp = fopen(REGISTRATION_FILE, "rb");
    if (fp == NULL)
        return FALSE;

    while (fread(&temp, sizeof(Registration), 1, fp) == 1)
    {
        if (strcmp(temp.regno, regno) == 0 &&
            strcmp(temp.code, code) == 0 &&
            temp.isActive == TRUE)
        {
            found = TRUE;
            break;
        }
    }

    fclose(fp);
    return found;
}

int countActiveRegistrationsForCourse(const char *code)
{
    FILE *fp;
    Registration temp;
    int count = 0;

    fp = fopen(REGISTRATION_FILE, "rb");
    if (fp == NULL)
        return 0;

    while (fread(&temp, sizeof(Registration), 1, fp) == 1)
    {
        if (strcmp(temp.code, code) == 0 && temp.isActive == TRUE)
            count++;
    }

    fclose(fp);
    return count;
}

int getCourseByCode(const char *code, Course *outCourse)
{
    FILE *fp;
    Course temp;
    int found = FALSE;

    fp = fopen(COURSE_FILE, "rb");
    if (fp == NULL)
        return FALSE;

    while (fread(&temp, sizeof(Course), 1, fp) == 1)
    {
        if (strcmp(temp.code, code) == 0 && temp.isActive == TRUE)
        {
            *outCourse = temp;
            found = TRUE;
            break;
        }
    }

    fclose(fp);
    return found;
}

/* Rewrites a single course record in-place inside courses.dat
 * by matching on course code. Returns TRUE on success. */
int updateCourseRecord(Course c)
{
    FILE *fp;
    Course temp;
    long pos;
    int updated = FALSE;

    fp = fopen(COURSE_FILE, "rb+");
    if (fp == NULL)
        return FALSE;

    while (fread(&temp, sizeof(Course), 1, fp) == 1)
    {
        if (strcmp(temp.code, c.code) == 0)
        {
            pos = ftell(fp) - (long)sizeof(Course);
            fseek(fp, pos, SEEK_SET);
            fwrite(&c, sizeof(Course), 1, fp);
            fflush(fp);
            updated = TRUE;
            break;
        }
    }

    fclose(fp);
    return updated;
}

int getFacultyById(const char *facid, Faculty *outFaculty)
{
    FILE *fp;
    Faculty temp;
    int found = FALSE;

    fp = fopen(FACULTY_FILE, "rb");
    if (fp == NULL)
        return FALSE;

    while (fread(&temp, sizeof(Faculty), 1, fp) == 1)
    {
        if (strcmp(temp.facid, facid) == 0)
        {
            *outFaculty = temp;
            found = TRUE;
            break;
        }
    }

    fclose(fp);
    return found;
}

/* ============================================================
 *  SECTION 4 : STUDENT MODULE
 * ============================================================ */

void studentPortal(void)
{
    int choice;
    Student loggedInStudent;

    while (1)
    {
        showMainHeader("STUDENT PORTAL");
        printf("\t1. Student Registration\n");
        printf("\t2. Student Login\n");
        printf("\t3. Back to Main Menu\n");
        printLine('-', 70);
        printf("\tEnter your choice : ");

        if (scanf("%d", &choice) != 1)
        {
            flushInputBuffer();
            printError("Invalid input.");
            pauseScreen();
            continue;
        }
        flushInputBuffer();

        switch (choice)
        {
            case 1:
                studentRegister();
                break;
            case 2:
                if (studentLogin(&loggedInStudent))
                {
                    studentDashboard(&loggedInStudent);
                }
                else
                {
                    printError("Invalid Register Number or Password.");
                    pauseScreen();
                }
                break;
            case 3:
                return;
            default:
                printError("Please choose a valid option.");
                pauseScreen();
        }
    }
}

void studentRegister(void)
{
    Student s;
    FILE *fp;

    showMainHeader("STUDENT REGISTRATION");

    printf("\tEnter Register Number : ");
    scanf("%19s", s.regno);
    flushInputBuffer();

    if (isDuplicateRegNo(s.regno))
    {
        printError("A student with this Register Number already exists.");
        pauseScreen();
        return;
    }

    printf("\tEnter Full Name       : ");
    fgets(s.name, MAX_LEN_NAME, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("\tEnter Department      : ");
    fgets(s.dept, MAX_LEN_DEPT, stdin);
    s.dept[strcspn(s.dept, "\n")] = '\0';

    printf("\tEnter Semester (1-8)  : ");
    scanf("%d", &s.semester);
    flushInputBuffer();

    if (!isValidSemester(s.semester))
    {
        printError("Semester must be between 1 and 8.");
        pauseScreen();
        return;
    }

    printf("\tEnter Phone Number    : ");
    scanf("%14s", s.phone);
    flushInputBuffer();

    if (!isValidPhone(s.phone))
    {
        printError("Phone number must be exactly 10 digits.");
        pauseScreen();
        return;
    }

    printf("\tEnter Email           : ");
    scanf("%49s", s.email);
    flushInputBuffer();

    if (!isValidEmail(s.email))
    {
        printError("Invalid email format.");
        pauseScreen();
        return;
    }

    printf("\tEnter Password        : ");
    getHiddenPassword(s.password, MAX_LEN_PASS);
    printf("\n");

    if (!isValidPasswordFormat(s.password))
    {
        printError("Password must be 4-19 characters with no spaces.");
        pauseScreen();
        return;
    }

    s.isActive = TRUE;

    fp = fopen(STUDENT_FILE, "ab");
    if (fp == NULL)
    {
        printError("Unable to open student database.");
        pauseScreen();
        return;
    }

    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);

    printSuccess("Student registered successfully!");
    pauseScreen();
}

int studentLogin(Student *s)
{
    FILE *fp;
    Student temp;
    char regno[MAX_LEN_REG];
    char password[MAX_LEN_PASS];
    int found = FALSE;

    showMainHeader("STUDENT LOGIN");

    printf("\tEnter Register Number : ");
    scanf("%19s", regno);
    flushInputBuffer();

    printf("\tEnter Password        : ");
    getHiddenPassword(password, MAX_LEN_PASS);
    printf("\n");

    fp = fopen(STUDENT_FILE, "rb");
    if (fp == NULL)
    {
        return FALSE;
    }

    while (fread(&temp, sizeof(Student), 1, fp) == 1)
    {
        if (strcmp(temp.regno, regno) == 0 &&
            strcmp(temp.password, password) == 0 &&
            temp.isActive == TRUE)
        {
            found = TRUE;
            *s = temp;
            break;
        }
    }

    fclose(fp);
    return found;
}

void studentDashboard(Student *s)
{
    int choice;

    while (1)
    {
        showMainHeader("STUDENT DASHBOARD");
        printf("\tWelcome, %s (%s)\n\n", s->name, s->regno);
        printf("\t1. View Profile\n");
        printf("\t2. View Available Courses\n");
        printf("\t3. Register Course\n");
        printf("\t4. Drop Course\n");
        printf("\t5. My Registered Courses\n");
        printf("\t6. Total Credits\n");
        printf("\t7. Change Password\n");
        printf("\t8. Logout\n");
        printLine('-', 70);
        printf("\tEnter your choice : ");

        if (scanf("%d", &choice) != 1)
        {
            flushInputBuffer();
            printError("Invalid input.");
            pauseScreen();
            continue;
        }
        flushInputBuffer();

        switch (choice)
        {
            case 1: viewProfile(*s); break;
            case 2: viewAvailableCourses(); break;
            case 3: registerCourseForStudent(*s); break;
            case 4: dropCourseForStudent(*s); break;
            case 5: myRegisteredCourses(*s); break;
            case 6: totalCredits(*s); break;
            case 7: changeStudentPassword(s); break;
            case 8: return;
            default:
                printError("Please choose a valid option.");
                pauseScreen();
        }
    }
}

void viewProfile(Student s)
{
    showMainHeader("MY PROFILE");

    printf("\tRegister Number : %s\n", s.regno);
    printf("\tName            : %s\n", s.name);
    printf("\tDepartment      : %s\n", s.dept);
    printf("\tSemester        : %d\n", s.semester);
    printf("\tPhone Number    : %s\n", s.phone);
    printf("\tEmail           : %s\n", s.email);

    pauseScreen();
}

void viewAvailableCourses(void)
{
    FILE *fp;
    Course temp;
    int count = 0;

    showMainHeader("AVAILABLE COURSES");

    fp = fopen(COURSE_FILE, "rb");
    if (fp == NULL)
    {
        printInfo("No courses have been added yet.");
        pauseScreen();
        return;
    }

    printf("\t%-8s %-24s %-4s %-4s %-10s %-6s\n",
           "Code", "Course Name", "Sem", "Crd", "Faculty", "Seats");
    printLine('-', 70);

    while (fread(&temp, sizeof(Course), 1, fp) == 1)
    {
        if (temp.isActive == TRUE)
        {
            printf("\t%-8s %-24s %-4d %-4d %-10s %-2d/%-2d\n",
                   temp.code, temp.name, temp.semester, temp.credits,
                   temp.facid, temp.availSeats, temp.maxSeats);
            count++;
        }
    }

    fclose(fp);

    if (count == 0)
        printInfo("No active courses available at the moment.");

    pauseScreen();
}

void registerCourseForStudent(Student s)
{
    char code[MAX_LEN_CODE];
    Course c;
    Registration r;
    FILE *fp;

    showMainHeader("REGISTER COURSE");

    printf("\tEnter Course Code to register : ");
    scanf("%9s", code);
    flushInputBuffer();

    if (!getCourseByCode(code, &c))
    {
        printError("Course not found.");
        pauseScreen();
        return;
    }

    if (isAlreadyRegistered(s.regno, code))
    {
        printError("You are already registered for this course.");
        pauseScreen();
        return;
    }

    if (c.availSeats <= 0)
    {
        printError("No seats available for this course.");
        pauseScreen();
        return;
    }

    /* Reduce available seats and persist */
    c.availSeats = c.availSeats - 1;
    updateCourseRecord(c);

    strcpy(r.regno, s.regno);
    strcpy(r.code, c.code);
    getCurrentDateTimeStr(r.dateTime);
    r.isActive = TRUE;

    fp = fopen(REGISTRATION_FILE, "ab");
    if (fp == NULL)
    {
        printError("Unable to open registration database.");
        pauseScreen();
        return;
    }
    fwrite(&r, sizeof(Registration), 1, fp);
    fclose(fp);

    printSuccess("Course registered successfully!");
    pauseScreen();
}

void dropCourseForStudent(Student s)
{
    char code[MAX_LEN_CODE];
    FILE *fp;
    Registration temp;
    long pos;
    int found = FALSE;
    Course c;

    showMainHeader("DROP COURSE");

    printf("\tEnter Course Code to drop : ");
    scanf("%9s", code);
    flushInputBuffer();

    fp = fopen(REGISTRATION_FILE, "rb+");
    if (fp == NULL)
    {
        printError("You have no registered courses.");
        pauseScreen();
        return;
    }

    while (fread(&temp, sizeof(Registration), 1, fp) == 1)
    {
        if (strcmp(temp.regno, s.regno) == 0 &&
            strcmp(temp.code, code) == 0 &&
            temp.isActive == TRUE)
        {
            temp.isActive = FALSE;
            pos = ftell(fp) - (long)sizeof(Registration);
            fseek(fp, pos, SEEK_SET);
            fwrite(&temp, sizeof(Registration), 1, fp);
            fflush(fp);
            found = TRUE;
            break;
        }
    }
    fclose(fp);

    if (!found)
    {
        printError("Active registration for this course was not found.");
        pauseScreen();
        return;
    }

    /* Increase available seats back */
    if (getCourseByCode(code, &c))
    {
        c.availSeats = c.availSeats + 1;
        updateCourseRecord(c);
    }

    printSuccess("Course dropped successfully!");
    pauseScreen();
}

void myRegisteredCourses(Student s)
{
    FILE *fp;
    Registration temp;
    Course c;
    int count = 0;

    showMainHeader("MY REGISTERED COURSES");

    fp = fopen(REGISTRATION_FILE, "rb");
    if (fp == NULL)
    {
        printInfo("You have not registered for any courses yet.");
        pauseScreen();
        return;
    }

    printf("\t%-8s %-24s %-4s %-4s %-20s\n",
           "Code", "Course Name", "Sem", "Crd", "Registered On");
    printLine('-', 70);

    while (fread(&temp, sizeof(Registration), 1, fp) == 1)
    {
        if (strcmp(temp.regno, s.regno) == 0 && temp.isActive == TRUE)
        {
            if (getCourseByCode(temp.code, &c))
            {
                printf("\t%-8s %-24s %-4d %-4d %-20s\n",
                       c.code, c.name, c.semester, c.credits, temp.dateTime);
                count++;
            }
        }
    }

    fclose(fp);

    if (count == 0)
        printInfo("You have not registered for any courses yet.");

    pauseScreen();
}

void totalCredits(Student s)
{
    FILE *fp;
    Registration temp;
    Course c;
    int total = 0;

    showMainHeader("TOTAL CREDITS");

    fp = fopen(REGISTRATION_FILE, "rb");
    if (fp != NULL)
    {
        while (fread(&temp, sizeof(Registration), 1, fp) == 1)
        {
            if (strcmp(temp.regno, s.regno) == 0 && temp.isActive == TRUE)
            {
                if (getCourseByCode(temp.code, &c))
                    total += c.credits;
            }
        }
        fclose(fp);
    }

    printf("\tTotal Registered Credits : %d\n", total);
    pauseScreen();
}

void changeStudentPassword(Student *s)
{
    char oldPassword[MAX_LEN_PASS];
    char newPassword[MAX_LEN_PASS];
    FILE *fp;
    Student temp;
    long pos;
    int found = FALSE;

    showMainHeader("CHANGE PASSWORD");

    printf("\tEnter Current Password : ");
    getHiddenPassword(oldPassword, MAX_LEN_PASS);
    printf("\n");

    if (strcmp(oldPassword, s->password) != 0)
    {
        printError("Current password is incorrect.");
        pauseScreen();
        return;
    }

    printf("\tEnter New Password     : ");
    getHiddenPassword(newPassword, MAX_LEN_PASS);
    printf("\n");

    if (!isValidPasswordFormat(newPassword))
    {
        printError("Password must be 4-19 characters with no spaces.");
        pauseScreen();
        return;
    }

    fp = fopen(STUDENT_FILE, "rb+");
    if (fp == NULL)
    {
        printError("Unable to open student database.");
        pauseScreen();
        return;
    }

    while (fread(&temp, sizeof(Student), 1, fp) == 1)
    {
        if (strcmp(temp.regno, s->regno) == 0)
        {
            strcpy(temp.password, newPassword);
            pos = ftell(fp) - (long)sizeof(Student);
            fseek(fp, pos, SEEK_SET);
            fwrite(&temp, sizeof(Student), 1, fp);
            fflush(fp);
            found = TRUE;
            break;
        }
    }
    fclose(fp);

    if (found)
    {
        strcpy(s->password, newPassword);
        printSuccess("Password changed successfully!");
    }
    else
    {
        printError("Student record not found.");
    }

    pauseScreen();
}

/* ============================================================
 *  SECTION 5 : FACULTY MODULE
 * ============================================================ */

void facultyPortal(void)
{
    Faculty loggedInFaculty;

    if (facultyLogin(&loggedInFaculty))
    {
        facultyDashboard(loggedInFaculty);
    }
    else
    {
        printError("Invalid Faculty ID or Password.");
        pauseScreen();
    }
}

int facultyLogin(Faculty *f)
{
    FILE *fp;
    Faculty temp;
    char facid[MAX_LEN_FACID];
    char password[MAX_LEN_PASS];
    int found = FALSE;

    showMainHeader("FACULTY LOGIN");

    printf("\tEnter Faculty ID : ");
    scanf("%19s", facid);
    flushInputBuffer();

    printf("\tEnter Password   : ");
    getHiddenPassword(password, MAX_LEN_PASS);
    printf("\n");

    fp = fopen(FACULTY_FILE, "rb");
    if (fp == NULL)
        return FALSE;

    while (fread(&temp, sizeof(Faculty), 1, fp) == 1)
    {
        if (strcmp(temp.facid, facid) == 0 &&
            strcmp(temp.password, password) == 0)
        {
            found = TRUE;
            *f = temp;
            break;
        }
    }

    fclose(fp);
    return found;
}

void facultyDashboard(Faculty f)
{
    int choice;

    while (1)
    {
        showMainHeader("FACULTY DASHBOARD");
        printf("\tWelcome, %s (%s)\n\n", f.name, f.facid);
        printf("\t1. View Assigned Courses\n");
        printf("\t2. View Registered Students\n");
        printf("\t3. Logout\n");
        printLine('-', 70);
        printf("\tEnter your choice : ");

        if (scanf("%d", &choice) != 1)
        {
            flushInputBuffer();
            printError("Invalid input.");
            pauseScreen();
            continue;
        }
        flushInputBuffer();

        switch (choice)
        {
            case 1: viewAssignedCourses(f); break;
            case 2: viewRegisteredStudentsForFaculty(f); break;
            case 3: return;
            default:
                printError("Please choose a valid option.");
                pauseScreen();
        }
    }
}

void viewAssignedCourses(Faculty f)
{
    FILE *fp;
    Course temp;
    int count = 0;

    showMainHeader("ASSIGNED COURSES");

    fp = fopen(COURSE_FILE, "rb");
    if (fp == NULL)
    {
        printInfo("No courses have been assigned to you yet.");
        pauseScreen();
        return;
    }

    printf("\t%-8s %-24s %-4s %-4s %-6s\n",
           "Code", "Course Name", "Sem", "Crd", "Seats");
    printLine('-', 70);

    while (fread(&temp, sizeof(Course), 1, fp) == 1)
    {
        if (temp.isActive == TRUE && strcmp(temp.facid, f.facid) == 0)
        {
            printf("\t%-8s %-24s %-4d %-4d %-2d/%-2d\n",
                   temp.code, temp.name, temp.semester, temp.credits,
                   temp.availSeats, temp.maxSeats);
            count++;
        }
    }

    fclose(fp);

    if (count == 0)
        printInfo("No courses have been assigned to you yet.");

    pauseScreen();
}

void viewRegisteredStudentsForFaculty(Faculty f)
{
    FILE *courseFp, *regFp;
    Course c;
    Registration r;
    Student s;
    int totalStudents = 0;

    showMainHeader("REGISTERED STUDENTS");

    courseFp = fopen(COURSE_FILE, "rb");
    if (courseFp == NULL)
    {
        printInfo("No courses have been assigned to you yet.");
        pauseScreen();
        return;
    }

    while (fread(&c, sizeof(Course), 1, courseFp) == 1)
    {
        if (c.isActive == TRUE && strcmp(c.facid, f.facid) == 0)
        {
            int courseHasStudents = 0;

            printf("\n\tCourse : %s - %s\n", c.code, c.name);
            printLine('-', 70);

            regFp = fopen(REGISTRATION_FILE, "rb");
            if (regFp != NULL)
            {
                while (fread(&r, sizeof(Registration), 1, regFp) == 1)
                {
                    if (r.isActive == TRUE && strcmp(r.code, c.code) == 0)
                    {
                        FILE *stuFp = fopen(STUDENT_FILE, "rb");
                        if (stuFp != NULL)
                        {
                            while (fread(&s, sizeof(Student), 1, stuFp) == 1)
                            {
                                if (strcmp(s.regno, r.regno) == 0)
                                {
                                    printf("\t%-12s %-24s %-10s\n",
                                           s.regno, s.name, s.dept);
                                    courseHasStudents = 1;
                                    totalStudents++;
                                    break;
                                }
                            }
                            fclose(stuFp);
                        }
                    }
                }
                fclose(regFp);
            }

            if (!courseHasStudents)
                printf("\t(No students registered for this course)\n");
        }
    }

    fclose(courseFp);

    if (totalStudents == 0)
        printf("\n");

    pauseScreen();
}

/* ============================================================
 *  SECTION 6 : ADMIN MODULE
 * ============================================================ */

void adminPortal(void)
{
    if (adminLogin())
    {
        adminDashboard();
    }
    else
    {
        printError("Invalid Admin Username or Password.");
        pauseScreen();
    }
}

int adminLogin(void)
{
    char username[MAX_LEN_NAME];
    char password[MAX_LEN_PASS];

    showMainHeader("ADMIN LOGIN");

    printf("\tEnter Username : ");
    scanf("%49s", username);
    flushInputBuffer();

    printf("\tEnter Password : ");
    getHiddenPassword(password, MAX_LEN_PASS);
    printf("\n");

    if (strcmp(username, ADMIN_USERNAME) == 0 &&
        strcmp(password, ADMIN_PASSWORD) == 0)
        return TRUE;

    return FALSE;
}

void adminDashboard(void)
{
    int choice;

    while (1)
    {
        showMainHeader("ADMIN DASHBOARD");
        printf("\t1. Add Course\n");
        printf("\t2. Update Course\n");
        printf("\t3. Delete Course\n");
        printf("\t4. View Courses\n");
        printf("\t5. Add Faculty\n");
        printf("\t6. View Faculty\n");
        printf("\t7. View Students\n");
        printf("\t8. Registration Report\n");
        printf("\t9. Logout\n");
        printLine('-', 70);
        printf("\tEnter your choice : ");

        if (scanf("%d", &choice) != 1)
        {
            flushInputBuffer();
            printError("Invalid input.");
            pauseScreen();
            continue;
        }
        flushInputBuffer();

        switch (choice)
        {
            case 1: addCourse(); break;
            case 2: updateCourse(); break;
            case 3: deleteCourse(); break;
            case 4: viewCourses(); break;
            case 5: addFaculty(); break;
            case 6: viewFaculty(); break;
            case 7: viewStudents(); break;
            case 8: registrationReport(); break;
            case 9: return;
            default:
                printError("Please choose a valid option.");
                pauseScreen();
        }
    }
}

void addCourse(void)
{
    Course c;
    Faculty f;
    FILE *fp;

    showMainHeader("ADD COURSE");

    printf("\tEnter Course Code       : ");
    scanf("%9s", c.code);
    flushInputBuffer();

    if (isDuplicateCourseCode(c.code))
    {
        printError("A course with this code already exists.");
        pauseScreen();
        return;
    }

    printf("\tEnter Course Name       : ");
    fgets(c.name, MAX_LEN_NAME, stdin);
    c.name[strcspn(c.name, "\n")] = '\0';

    printf("\tEnter Semester (1-8)    : ");
    scanf("%d", &c.semester);
    flushInputBuffer();

    if (!isValidSemester(c.semester))
    {
        printError("Semester must be between 1 and 8.");
        pauseScreen();
        return;
    }

    printf("\tEnter Credits           : ");
    scanf("%d", &c.credits);
    flushInputBuffer();

    if (c.credits <= 0 || c.credits > 10)
    {
        printError("Credits must be between 1 and 10.");
        pauseScreen();
        return;
    }

    printf("\tEnter Faculty ID        : ");
    scanf("%19s", c.facid);
    flushInputBuffer();

    if (!getFacultyById(c.facid, &f))
    {
        printError("No faculty found with this ID. Add the faculty first.");
        pauseScreen();
        return;
    }

    printf("\tEnter Maximum Seats     : ");
    scanf("%d", &c.maxSeats);
    flushInputBuffer();

    if (c.maxSeats <= 0)
    {
        printError("Maximum seats must be a positive number.");
        pauseScreen();
        return;
    }

    c.availSeats = c.maxSeats;
    c.isActive = TRUE;

    fp = fopen(COURSE_FILE, "ab");
    if (fp == NULL)
    {
        printError("Unable to open course database.");
        pauseScreen();
        return;
    }

    fwrite(&c, sizeof(Course), 1, fp);
    fclose(fp);

    printSuccess("Course added successfully!");
    pauseScreen();
}

void updateCourse(void)
{
    char code[MAX_LEN_CODE];
    FILE *fp;
    Course temp;
    long pos;
    int found = FALSE;
    int choice;

    showMainHeader("UPDATE COURSE");

    printf("\tEnter Course Code to update : ");
    scanf("%9s", code);
    flushInputBuffer();

    fp = fopen(COURSE_FILE, "rb+");
    if (fp == NULL)
    {
        printError("No courses found.");
        pauseScreen();
        return;
    }

    while (fread(&temp, sizeof(Course), 1, fp) == 1)
    {
        if (strcmp(temp.code, code) == 0 && temp.isActive == TRUE)
        {
            found = TRUE;
            break;
        }
    }

    if (!found)
    {
        fclose(fp);
        printError("Course not found.");
        pauseScreen();
        return;
    }

    printf("\n\tCurrent Details\n");
    printf("\tName      : %s\n", temp.name);
    printf("\tSemester  : %d\n", temp.semester);
    printf("\tCredits   : %d\n", temp.credits);
    printf("\tFaculty ID: %s\n", temp.facid);
    printf("\tMax Seats : %d\n", temp.maxSeats);
    printf("\tAvailable : %d\n", temp.availSeats);

    printf("\n\tWhat do you want to update?\n");
    printf("\t1. Course Name\n");
    printf("\t2. Semester\n");
    printf("\t3. Credits\n");
    printf("\t4. Faculty ID\n");
    printf("\t5. Maximum Seats\n");
    printf("\t6. Cancel\n");
    printf("\tEnter your choice : ");
    scanf("%d", &choice);
    flushInputBuffer();

    switch (choice)
    {
        case 1:
            printf("\tEnter New Course Name : ");
            fgets(temp.name, MAX_LEN_NAME, stdin);
            temp.name[strcspn(temp.name, "\n")] = '\0';
            break;
        case 2:
        {
            int sem;
            printf("\tEnter New Semester (1-8) : ");
            scanf("%d", &sem);
            flushInputBuffer();
            if (!isValidSemester(sem))
            {
                fclose(fp);
                printError("Semester must be between 1 and 8.");
                pauseScreen();
                return;
            }
            temp.semester = sem;
            break;
        }
        case 3:
        {
            int credits;
            printf("\tEnter New Credits : ");
            scanf("%d", &credits);
            flushInputBuffer();
            if (credits <= 0 || credits > 10)
            {
                fclose(fp);
                printError("Credits must be between 1 and 10.");
                pauseScreen();
                return;
            }
            temp.credits = credits;
            break;
        }
        case 4:
        {
            Faculty f;
            char facid[MAX_LEN_FACID];
            printf("\tEnter New Faculty ID : ");
            scanf("%19s", facid);
            flushInputBuffer();
            if (!getFacultyById(facid, &f))
            {
                fclose(fp);
                printError("No faculty found with this ID.");
                pauseScreen();
                return;
            }
            strcpy(temp.facid, facid);
            break;
        }
        case 5:
        {
            int newMax;
            int diff;
            printf("\tEnter New Maximum Seats : ");
            scanf("%d", &newMax);
            flushInputBuffer();
            if (newMax <= 0)
            {
                fclose(fp);
                printError("Maximum seats must be a positive number.");
                pauseScreen();
                return;
            }
            diff = newMax - temp.maxSeats;
            temp.maxSeats = newMax;
            temp.availSeats = temp.availSeats + diff;
            if (temp.availSeats < 0)
                temp.availSeats = 0;
            break;
        }
        case 6:
            fclose(fp);
            printInfo("Update cancelled.");
            pauseScreen();
            return;
        default:
            fclose(fp);
            printError("Invalid option.");
            pauseScreen();
            return;
    }

    pos = ftell(fp) - (long)sizeof(Course);
    fseek(fp, pos, SEEK_SET);
    fwrite(&temp, sizeof(Course), 1, fp);
    fflush(fp);
    fclose(fp);

    printSuccess("Course updated successfully!");
    pauseScreen();
}

void deleteCourse(void)
{
    char code[MAX_LEN_CODE];
    FILE *fp;
    Course temp;
    long pos;
    int found = FALSE;
    char confirm;

    showMainHeader("DELETE COURSE");

    printf("\tEnter Course Code to delete : ");
    scanf("%9s", code);
    flushInputBuffer();

    if (!isDuplicateCourseCode(code))
    {
        printError("Course not found.");
        pauseScreen();
        return;
    }

    printf("\tAre you sure you want to delete this course? (y/n) : ");
    scanf(" %c", &confirm);
    flushInputBuffer();

    if (confirm != 'y' && confirm != 'Y')
    {
        printInfo("Deletion cancelled.");
        pauseScreen();
        return;
    }

    fp = fopen(COURSE_FILE, "rb+");
    if (fp == NULL)
    {
        printError("No courses found.");
        pauseScreen();
        return;
    }

    while (fread(&temp, sizeof(Course), 1, fp) == 1)
    {
        if (strcmp(temp.code, code) == 0 && temp.isActive == TRUE)
        {
            temp.isActive = FALSE;
            pos = ftell(fp) - (long)sizeof(Course);
            fseek(fp, pos, SEEK_SET);
            fwrite(&temp, sizeof(Course), 1, fp);
            fflush(fp);
            found = TRUE;
            break;
        }
    }
    fclose(fp);

    if (found)
        printSuccess("Course deleted successfully!");
    else
        printError("Course not found.");

    pauseScreen();
}

void viewCourses(void)
{
    FILE *fp;
    Course temp;
    int count = 0;

    showMainHeader("ALL COURSES");

    fp = fopen(COURSE_FILE, "rb");
    if (fp == NULL)
    {
        printInfo("No courses have been added yet.");
        pauseScreen();
        return;
    }

    printf("\t%-8s %-24s %-4s %-4s %-10s %-6s\n",
           "Code", "Course Name", "Sem", "Crd", "Faculty", "Seats");
    printLine('-', 70);

    while (fread(&temp, sizeof(Course), 1, fp) == 1)
    {
        if (temp.isActive == TRUE)
        {
            printf("\t%-8s %-24s %-4d %-4d %-10s %-2d/%-2d\n",
                   temp.code, temp.name, temp.semester, temp.credits,
                   temp.facid, temp.availSeats, temp.maxSeats);
            count++;
        }
    }

    fclose(fp);

    printf("\n\tTotal Courses : %d\n", count);
    pauseScreen();
}

void addFaculty(void)
{
    Faculty f;
    FILE *fp;

    showMainHeader("ADD FACULTY");

    printf("\tEnter Faculty ID    : ");
    scanf("%19s", f.facid);
    flushInputBuffer();

    if (isDuplicateFacultyId(f.facid))
    {
        printError("A faculty member with this ID already exists.");
        pauseScreen();
        return;
    }

    printf("\tEnter Faculty Name  : ");
    fgets(f.name, MAX_LEN_NAME, stdin);
    f.name[strcspn(f.name, "\n")] = '\0';

    printf("\tEnter Department    : ");
    fgets(f.dept, MAX_LEN_DEPT, stdin);
    f.dept[strcspn(f.dept, "\n")] = '\0';

    printf("\tEnter Password      : ");
    getHiddenPassword(f.password, MAX_LEN_PASS);
    printf("\n");

    if (!isValidPasswordFormat(f.password))
    {
        printError("Password must be 4-19 characters with no spaces.");
        pauseScreen();
        return;
    }

    fp = fopen(FACULTY_FILE, "ab");
    if (fp == NULL)
    {
        printError("Unable to open faculty database.");
        pauseScreen();
        return;
    }

    fwrite(&f, sizeof(Faculty), 1, fp);
    fclose(fp);

    printSuccess("Faculty added successfully!");
    pauseScreen();
}

void viewFaculty(void)
{
    FILE *fp;
    Faculty temp;
    int count = 0;

    showMainHeader("ALL FACULTY");

    fp = fopen(FACULTY_FILE, "rb");
    if (fp == NULL)
    {
        printInfo("No faculty members have been added yet.");
        pauseScreen();
        return;
    }

    printf("\t%-10s %-24s %-15s\n", "Fac ID", "Name", "Department");
    printLine('-', 70);

    while (fread(&temp, sizeof(Faculty), 1, fp) == 1)
    {
        printf("\t%-10s %-24s %-15s\n", temp.facid, temp.name, temp.dept);
        count++;
    }

    fclose(fp);

    printf("\n\tTotal Faculty : %d\n", count);
    pauseScreen();
}

void viewStudents(void)
{
    FILE *fp;
    Student temp;
    int count = 0;

    showMainHeader("ALL STUDENTS");

    fp = fopen(STUDENT_FILE, "rb");
    if (fp == NULL)
    {
        printInfo("No students have registered yet.");
        pauseScreen();
        return;
    }

    printf("\t%-12s %-20s %-12s %-4s %-12s\n",
           "Reg No", "Name", "Department", "Sem", "Phone");
    printLine('-', 70);

    while (fread(&temp, sizeof(Student), 1, fp) == 1)
    {
        if (temp.isActive == TRUE)
        {
            printf("\t%-12s %-20s %-12s %-4d %-12s\n",
                   temp.regno, temp.name, temp.dept, temp.semester, temp.phone);
            count++;
        }
    }

    fclose(fp);

    printf("\n\tTotal Students : %d\n", count);
    pauseScreen();
}

void registrationReport(void)
{
    FILE *fp;
    int totalStudents = 0, totalFaculty = 0, totalCourses = 0, totalRegs = 0;
    Student stu;
    Faculty fac;
    Course crs;
    Registration reg;

    showMainHeader("REGISTRATION REPORT");

    fp = fopen(STUDENT_FILE, "rb");
    if (fp != NULL)
    {
        while (fread(&stu, sizeof(Student), 1, fp) == 1)
            if (stu.isActive == TRUE) totalStudents++;
        fclose(fp);
    }

    fp = fopen(FACULTY_FILE, "rb");
    if (fp != NULL)
    {
        while (fread(&fac, sizeof(Faculty), 1, fp) == 1)
            totalFaculty++;
        fclose(fp);
    }

    fp = fopen(COURSE_FILE, "rb");
    if (fp != NULL)
    {
        while (fread(&crs, sizeof(Course), 1, fp) == 1)
            if (crs.isActive == TRUE) totalCourses++;
        fclose(fp);
    }

    fp = fopen(REGISTRATION_FILE, "rb");
    if (fp != NULL)
    {
        while (fread(&reg, sizeof(Registration), 1, fp) == 1)
            if (reg.isActive == TRUE) totalRegs++;
        fclose(fp);
    }

    printf("\tTotal Students       : %d\n", totalStudents);
    printf("\tTotal Faculty        : %d\n", totalFaculty);
    printf("\tTotal Courses        : %d\n", totalCourses);
    printf("\tTotal Registrations  : %d\n\n", totalRegs);

    printLine('-', 70);
    printCentered("COURSE-WISE STUDENT COUNT & AVAILABLE SEATS", 70);
    printLine('-', 70);

    fp = fopen(COURSE_FILE, "rb");
    if (fp != NULL)
    {
        printf("\t%-8s %-24s %-12s %-8s\n",
               "Code", "Course Name", "Registered", "Available");
        printLine('-', 70);

        while (fread(&crs, sizeof(Course), 1, fp) == 1)
        {
            if (crs.isActive == TRUE)
            {
                int registeredCount = countActiveRegistrationsForCourse(crs.code);
                printf("\t%-8s %-24s %-12d %-8d\n",
                       crs.code, crs.name, registeredCount, crs.availSeats);
            }
        }
        fclose(fp);
    }

    pauseScreen();
}

/* ============================================================
 *  SECTION 7 : MAIN MENU
 * ============================================================ */

void mainMenu(void)
{
    int choice;
    int exitProgram = FALSE;

    while (!exitProgram)
    {
        showMainHeader("MAIN MENU");

        printf("\t1. Student Portal\n");
        printf("\t2. Faculty Portal\n");
        printf("\t3. Admin Portal\n");
        printf("\t4. About UKF\n");
        printf("\t5. Exit\n");
        printLine('-', 70);
        printf("\tEnter your choice : ");

        if (scanf("%d", &choice) != 1)
        {
            flushInputBuffer();
            printError("Invalid input. Please enter a number.");
            pauseScreen();
            continue;
        }
        flushInputBuffer();

        switch (choice)
        {
            case 1:
                studentPortal();
                break;
            case 2:
                facultyPortal();
                break;
            case 3:
                adminPortal();
                break;
            case 4:
                aboutUKF();
                break;
            case 5:
                showMainHeader("EXIT");
                printCentered("Thank you for using UKF Course Registration System", 70);
                printCentered("Developed By RISWANA - S3 Data Science", 70);
                printf("\n");
                exitProgram = TRUE;
                break;
            default:
                printError("Please choose a valid option (1-5).");
                pauseScreen();
        }
    }
}
