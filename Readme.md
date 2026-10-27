# UKF College of Engineering & Technology: Course Registration System

A console-based **Course Registration System** written in pure **C**, built as a mini project for UKF College of Engineering & Technology. It supports three user roles (Student, Faculty and Admin) and stores all data in **binary `.dat` files**, with no external database needed.

> Developed by **ASHIQ S**, Creative Developer

---

## Features

### Student Portal
- Register with register number, name, department, semester, phone, email and password
- Duplicate register numbers are blocked
- Login with masked password entry (`*`)
- View profile and available courses
- Register for or drop a course (seats update automatically)
- View registered courses and total credits
- Change password

### Faculty Portal
- Login with Faculty ID and password
- View assigned courses
- View the students registered in each assigned course

### Admin Portal
- Add, update, delete and view courses
- Add and view faculty
- View all students
- Registration report: total students, faculty, courses and registrations, plus a course-wise student count and available seats

### Validation
- Semester must be 1 to 8
- Phone number must be exactly 10 digits
- Email format check
- Password rules (4 to 19 characters, no spaces)
- Duplicate checks for register number, faculty ID and course code
- Seat capacity check: no registration when seats are full
- Duplicate course registration is blocked

---

## Tech Stack

| Item | Details |
|------|---------|
| Language | C |
| Compiler | GCC (MinGW) on Windows |
| Libraries | `stdio.h`, `stdlib.h`, `string.h`, `time.h`, `windows.h`, `conio.h` |
| Storage | Binary files using `fread` / `fwrite` |
| Design | Modular programming (3 source files) |

---

## Project Structure

```
.
├── main.c      # Entry point: welcome screen and main menu
├── course.h    # Structures, macros and function prototypes
└── course.c    # Implementation of all functions
```

Data files created automatically at runtime:

| File | Contents |
|------|----------|
| `students.dat` | Student records |
| `faculty.dat` | Faculty records |
| `courses.dat` | Course records |
| `registrations.dat` | Course registrations |

---

## How to Build and Run

**Requirements:** Windows with GCC (MinGW) installed.

```bash
gcc main.c course.c -o registration.exe
```

Run it:

```bash
# Command Prompt
registration.exe

# PowerShell
.\registration.exe
```

> This project uses `windows.h` and `conio.h`, so it runs on **Windows only**.

---

## Default Admin Login

| Username | Password |
|----------|----------|
| `admin` | `admin123` |

**Suggested first-run order:**
1. Log in as Admin and **Add Faculty**
2. **Add Course** (assign a Faculty ID)
3. Register a student from the Student Portal
4. Log in as the student and register for courses

---

## Future Improvements
- Migrate storage to SQLite or MySQL
- Password hashing
- GUI or web front-end
- Email/SMS notifications

---

## Developer

**RISWANA**
S3 Data Science
UKF College of Engineering & Technology
