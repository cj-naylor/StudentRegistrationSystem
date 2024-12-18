#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STUDENTS 1000
#define MAX_COURSES 100
#define MAX_REGISTRATIONS 1000

typedef struct {
  int studentID;
  char name[100];
  float gpa;
} Student;

typedef struct {
  int courseID;
  char courseName[100];
  int creditHours;
} Course;

typedef struct {
  int studentID;
  int courseID;
  char semester[10];
  float grade;
  time_t registrationTime;
} Registration;

Student students[MAX_STUDENTS];
Course courses[MAX_COURSES];
Registration *registrations;
int studentCount = 0;
int courseCount = 0;
int registrationCount = 0;

void addStudent();
void addCourse();
void displayStudents(int number);
void displayCourses(int number);
void displayStudentByID(int studentID);
void displayCourseByID(int courseID);
void storeStudentsToFile();
void storeCoursesToFile();
int isStudentIDExists(int studentID);
int isCourseIDExists(int courseID);

void registerCourse(int studentID, int courseID, const char *semester);
void withdrawCourse(int studentID, int courseID);
void updateGrade(int studentID, int courseID, float newGrade);
void printRegisteredCoursesForStudentByID(int studentID);
void printRegisteredStudentsForCourseByID(int courseID);
void printRegisteredCoursesForStudentByName(const char *studentName);
void printRegisteredStudentsForCourseByName(const char *courseName);
void storeRegistrationsToFile();

void loadStudentsFromFile(const char *filename);
void loadCoursesFromFile(const char *filename);
void loadRegistrationsFromFile(const char *filename);
void calculateAverageGPA(int studentID);
void rankStudents();

int main() {
  registrations = malloc(MAX_REGISTRATIONS * sizeof(Registration));
  if (registrations == NULL) {
    printf("Memory allocation failed!\n");
    return 1;
  }
  studentCount = 0;
  courseCount = 0;
  registrationCount = 0;

  int choice;
  while (1) {
    printf("--- Student Registration System ---\n");
    printf("1. Add a new student\n");
    printf("2. Add a new course\n");
    printf("3. Display all students\n");
    printf("4. Display all courses\n");
    printf("5. Display student by ID\n");
    printf("6. Display course by ID\n");
    printf("7. Register a course\n");
    printf("8. Withdraw from a course\n");
    printf("9. Update grade\n");
    printf("10. Print registered courses for a student by ID\n");
    printf("11. Print registered students for a course by ID\n");
    printf("12. Print registered courses for a student by name\n");
    printf("13. Print registered students for a course by name\n");
    printf("14. Save registrations to registrations.csv\n");
    printf("15. Exit\n");
    printf("16. Load students from file\n");
    printf("17. Load courses from file\n");
    printf("18. Load registrations from file\n");
    printf("19. Calculate GPA for a student\n");
    printf("20. Rank students by GPA\n");
    printf("21. Save students to students.csv\n");
    printf("22. Save courses to courses.csv\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      addStudent();
      break;
    case 2:
      addCourse();
      break;
    case 3:
      displayStudents(-1);
      break;
    case 4:
      displayCourses(-1);
      break;
    case 5: {
      int studentID;
      printf("Enter student ID: ");
      scanf("%d", &studentID);
      displayStudentByID(studentID);
      break;
    }
    case 6: {
      int courseID;
      printf("Enter course ID: ");
      scanf("%d", &courseID);
      displayCourseByID(courseID);
      break;
    }
    case 7: {
      int studentID, courseID;
      char semester[10];
      printf("Enter student ID: ");
      scanf("%d", &studentID);
      printf("Enter course ID: ");
      scanf("%d", &courseID);
      printf("Enter semester: ");
      scanf("%s", semester);
      registerCourse(studentID, courseID, semester);
      break;
    }
    case 8: {
      int studentID, courseID;
      printf("Enter student ID: ");
      scanf("%d", &studentID);
      printf("Enter course ID: ");
      scanf("%d", &courseID);
      withdrawCourse(studentID, courseID);
      break;
    }
    case 9: {
      int studentID, courseID;
      float newGrade;
      printf("Enter student ID: ");
      scanf("%d", &studentID);
      printf("Enter course ID: ");
      scanf("%d", &courseID);
      printf("Enter new grade: ");
      scanf("%f", &newGrade);
      updateGrade(studentID, courseID, newGrade);
      break;
    }
    case 10: {
      int studentID;
      printf("Enter student ID: ");
      scanf("%d", &studentID);
      printRegisteredCoursesForStudentByID(studentID);
      break;
    }
    case 11: {
      int courseID;
      printf("Enter course ID: ");
      scanf("%d", &courseID);
      printRegisteredStudentsForCourseByID(courseID);
      break;
    }
    case 12: {
      char studentName[100];
      printf("Enter student name: ");
      scanf("%s", studentName);
      printRegisteredCoursesForStudentByName(studentName);
      break;
    }
    case 13: {
      char courseName[100];
      printf("Enter course name: ");
      scanf("%s", courseName);
      printRegisteredStudentsForCourseByName(courseName);
      break;
    }
    case 14:
      storeRegistrationsToFile();
      break;
    case 15:
      printf("Exiting...\n");
      free(registrations);
      exit(0);

    case 16: {
      loadStudentsFromFile("students.csv");
      break;
    }
    case 17: {
      loadCoursesFromFile("courses.csv");
      break;
    }
    case 18: {
      loadRegistrationsFromFile("registrations.csv");
      break;
    }
    case 19: {
      int studentID;
      printf("Enter student ID: ");
      scanf("%d", &studentID);
      calculateAverageGPA(studentID);
      break;
    }
    case 20:
      rankStudents();
      break;
    case 21:
      storeStudentsToFile();
      break;
    case 22:
      storeCoursesToFile();
      break;
    default:
      printf("Invalid choice. Please try again.\n");
    }
  }
  return 0;
}

void addStudent() {
  if (studentCount >= MAX_STUDENTS) {
    printf("Cannot add more students, limit reached.\n");
    return;
  }

  int studentID;
  printf("Enter student ID: ");
  scanf("%d", &studentID);

  if (isStudentIDExists(studentID)) {
    printf(
        "Student ID already exists. Please try again with a different ID.\n");
    return;
  }

  students[studentCount].studentID = studentID;
  printf("Enter student name: ");
  scanf("%s", students[studentCount].name);
  printf("Enter student GPA: ");
  scanf("%f", &students[studentCount].gpa);
  studentCount++;
  printf("Student added successfully.\n");
}

void addCourse() {
  if (courseCount >= MAX_COURSES) {
    printf("Cannot add more courses, limit reached.\n");
    return;
  }

  int courseID;
  printf("Enter course ID: ");
  scanf("%d", &courseID);

  if (isCourseIDExists(courseID)) {
    printf("Course ID already exists. Please try again with a different ID.\n");
    return;
  }

  courses[courseCount].courseID = courseID;
  printf("Enter course name: ");
  scanf("%s", courses[courseCount].courseName);
  printf("Enter number of credit hours: ");
  scanf("%d", &courses[courseCount].creditHours);
  courseCount++;
  printf("Course added successfully.\n");
}

void displayStudents(int number) {
  if (studentCount == 0) {
    printf("No students available.\n");
    return;
  }

  printf("--- List of Students ---\n");
  for (int i = 0; i < (number == -1 ? studentCount : number); i++) {
    printf("ID: %d, Name: %s, GPA: %.2f\n", students[i].studentID,
           students[i].name, students[i].gpa);
  }
}

void displayCourses(int number) {
  if (courseCount == 0) {
    printf("No courses available.\n");
    return;
  }

  printf("--- List of Courses ---\n");
  for (int i = 0; i < (number == -1 ? courseCount : number); i++) {
    printf("ID: %d, Name: %s, Credit Hours: %d\n", courses[i].courseID,
           courses[i].courseName, courses[i].creditHours);
  }
}

void displayStudentByID(int studentID) {
  for (int i = 0; i < studentCount; i++) {
    if (students[i].studentID == studentID) {
      printf("ID: %d, Name: %s, GPA: %.2f\n", students[i].studentID,
             students[i].name, students[i].gpa);
      return;
    }
  }
  printf("Student with ID %d not found.\n", studentID);
}

void displayCourseByID(int courseID) {
  for (int i = 0; i < courseCount; i++) {
    if (courses[i].courseID == courseID) {
      printf("ID: %d, Name: %s, Credit Hours: %d\n", courses[i].courseID,
             courses[i].courseName, courses[i].creditHours);
      return;
    }
  }
  printf("Course with ID %d not found.\n", courseID);
}

int isStudentIDExists(int studentID) {
  for (int i = 0; i < studentCount; i++) {
    if (students[i].studentID == studentID) {
      return 1;
    }
  }
  return 0;
}

int isCourseIDExists(int courseID) {
  for (int i = 0; i < courseCount; i++) {
    if (courses[i].courseID == courseID) {
      return 1;
    }
  }
  return 0;
}

void registerCourse(int studentID, int courseID, const char *semester) {
  if (!isStudentIDExists(studentID) || !isCourseIDExists(courseID)) {
    printf("Student ID or Course ID does not exist.\n");
    return;
  }

  for (int i = 0; i < registrationCount; i++) {
    if (registrations[i].studentID == studentID &&
        registrations[i].courseID == courseID) {
      printf("Student is already registered for this course.\n");
      return;
    }
  }

  registrations[registrationCount].studentID = studentID;
  registrations[registrationCount].courseID = courseID;
  strcpy(registrations[registrationCount].semester, semester);
  registrations[registrationCount].grade = -1;
  registrations[registrationCount].registrationTime = time(NULL);
  registrationCount++;
  printf("Registration successful.\n");
}

void withdrawCourse(int studentID, int courseID) {
  for (int i = 0; i < registrationCount; i++) {
    if (registrations[i].studentID == studentID &&
        registrations[i].courseID == courseID) {
      for (int j = i; j < registrationCount - 1; j++) {
        registrations[j] = registrations[j + 1];
      }
      registrationCount--;
      printf("Withdrawal successful.\n");
      return;
    }
  }
  printf("Student is not registered for this course.\n");
}

void updateGrade(int studentID, int courseID, float newGrade) {
  for (int i = 0; i < registrationCount; i++) {
    if (registrations[i].studentID == studentID &&
        registrations[i].courseID == courseID) {
      registrations[i].grade = newGrade;
      printf("Grade updated successfully.\n");
      return;
    }
  }
  printf("Student is not registered for this course.\n");
}

void printRegisteredCoursesForStudentByID(int studentID) {
  printf("--- Courses for Student ID %d ---\n", studentID);
  for (int i = 0; i < registrationCount; i++) {
    if (registrations[i].studentID == studentID) {
      printf("Course ID: %d, Semester: %s, Grade: %.2f\n",
             registrations[i].courseID, registrations[i].semester,
             registrations[i].grade);
    }
  }
}

void printRegisteredStudentsForCourseByID(int courseID) {
  printf("--- Students for Course ID %d ---\n", courseID);
  for (int i = 0; i < registrationCount; i++) {
    if (registrations[i].courseID == courseID) {
      printf("Student ID: %d, Grade: %.2f\n", registrations[i].studentID,
             registrations[i].grade);
    }
  }
}

void printRegisteredCoursesForStudentByName(const char *studentName) {
  int found = 0;
  for (int i = 0; i < studentCount; i++) {
    if (strcmp(students[i].name, studentName) == 0) {
      printRegisteredCoursesForStudentByID(students[i].studentID);
      found = 1;
      break;
    }
  }
  if (!found) {
    printf("Student not found.\n");
  }
}

void printRegisteredStudentsForCourseByName(const char *courseName) {
  int found = 0;
  for (int i = 0; i < courseCount; i++) {
    if (strcmp(courses[i].courseName, courseName) == 0) {
      printRegisteredStudentsForCourseByID(courses[i].courseID);
      found = 1;
      break;
    }
  }
  if (!found) {
    printf("Course not found.\n");
  }
}

void storeRegistrationsToFile() {
  FILE *file = fopen("registrations.csv", "w");
  if (!file) {
    printf("Error saving registrations to file.\n");
    return;
  }
  fprintf(file, "StudentID,CourseID,Semester,Grade\n");
  for (int i = 0; i < registrationCount; i++) {
    fprintf(file, "%d,%d,%s,%.2f\n", registrations[i].studentID,
            registrations[i].courseID, registrations[i].semester,
            registrations[i].grade);
  }
  fclose(file);
  printf("Registrations saved to registrations.csv successfully.\n");
}

void loadStudentsFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    char buffer[256];
    fgets(buffer, sizeof(buffer), file);

    studentCount = 0;

    while (fscanf(file, "%d,%99[^,],%f\n", &students[studentCount].studentID,
                  students[studentCount].name,
                  &students[studentCount].gpa) == 3) {
        printf("Loaded Student ID: %d, Name: %s, GPA: %.2f\n",
               students[studentCount].studentID,
               students[studentCount].name,
               students[studentCount].gpa);
        studentCount++;
    }
    fclose(file);
    printf("Students loaded from %s successfully. Total students: %d\n", filename, studentCount);
}

void loadCoursesFromFile(const char *filename) {
  FILE *file1 = fopen(filename, "r");
  if (!file1) {
    printf("Error opening file: %s\n", filename);
    return;
  }

  char buffer[256];
  fgets(buffer, sizeof(buffer), file1);
  
  courseCount = 0;

  while (fscanf(file1, "%d,%99[^,],%d\n", &courses[courseCount].courseID,
                courses[courseCount].courseName,
                &courses[courseCount].creditHours) == 3) {
    if (!isCourseIDExists(courses[courseCount].courseID)) {
      courseCount++;
    } else {
      printf("Duplicate course ID %d found; ignoring.\n",
             courses[courseCount].courseID);
    }
  }
  fclose(file1);
  printf("Courses loaded from %s successfully.\n", filename);
}

void loadRegistrationsFromFile(const char *filename) {
    FILE *file2 = fopen(filename, "r");
    if (!file2) {
        printf("Error opening file: %s\n", filename);
        return;
    }
  
    char buffer[256];
    fgets(buffer, sizeof(buffer), file2);
    registrationCount = 0;  

    while (fscanf(file2, "%d,%d,%9[^,],%f\n",
                  &registrations[registrationCount].studentID,
                  &registrations[registrationCount].courseID,
                  registrations[registrationCount].semester,
                  &registrations[registrationCount].grade) == 4) {
        if (isStudentIDExists(registrations[registrationCount].studentID) &&
            isCourseIDExists(registrations[registrationCount].courseID)) {
            registrationCount++;
        } else {
            printf("Invalid registration found; ignoring entry for Student ID %d and Course ID %d.\n",
                   registrations[registrationCount].studentID,
                   registrations[registrationCount].courseID);
        }
    }
    fclose(file2);
    printf("Registrations loaded from %s successfully.\n", filename);
}

void calculateAverageGPA(int studentID) {
  float totalPoints = 0.0;
  int totalCredits = 0;

  for (int i = 0; i < registrationCount; i++) {
    if (registrations[i].studentID == studentID &&
        registrations[i].grade >= 0) {
      int courseID = registrations[i].courseID;
      for (int j = 0; j < courseCount; j++) {
        if (courses[j].courseID == courseID) {
          totalPoints += registrations[i].grade * courses[j].creditHours;
          totalCredits += courses[j].creditHours;
          break;
        }
      }
    }
  }

  if (totalCredits > 0) {
    students[studentID].gpa = totalPoints / totalCredits;
  } else {
    students[studentID].gpa = 0.0;
  }

  printf("GPA for student ID %d calculated: %.2f\n", studentID,
         students[studentID].gpa);
}

void rankStudents() {
  int indices[MAX_STUDENTS];
  for (int i = 0; i < studentCount; i++) {
    indices[i] = i;
  }

  for (int i = 0; i < studentCount - 1; i++) {
    for (int j = 0; j < studentCount - i - 1; j++) {
      if (students[indices[j]].gpa < students[indices[j + 1]].gpa) {
        int temp = indices[j];
        indices[j] = indices[j + 1];
        indices[j + 1] = temp;
      }
    }
  }

  printf("--- Ranked Students ---\n");
  for (int i = 0; i < studentCount; i++) {
    printf("Rank %d: ID: %d, Name: %s, GPA: %.2f\n", i + 1,
           students[indices[i]].studentID, students[indices[i]].name,
           students[indices[i]].gpa);
  }
}

void storeStudentsToFile() {
  FILE *file = fopen("students.csv", "w");
  if (!file) {
    printf("Error saving students to file.\n");
    return;
  }
  fprintf(file, "StudentID,Name,GPA\n");
  for (int i = 0; i < studentCount; i++) {
    fprintf(file, "%d,%s,%.2f\n", students[i].studentID, students[i].name,
            students[i].gpa);
  }
  fclose(file);
  printf("Students saved to students.csv successfully.\n");
}

void storeCoursesToFile() {
  FILE *file = fopen("courses.csv", "w");
  if (!file) {
    printf("Error saving courses to file.\n");
    return;
  }
  fprintf(file, "CourseID,CourseName,CreditHours\n");
  for (int i = 0; i < courseCount; i++) {
    fprintf(file, "%d,%s,%d\n", courses[i].courseID, courses[i].courseName,
            courses[i].creditHours);
  }
  fclose(file);
  printf("Courses saved to courses.csv successfully.\n");
}
