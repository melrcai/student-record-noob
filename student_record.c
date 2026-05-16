#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <ctype.h> 
#define TOTAL_WIDTH 50

struct Student { 
  int id;
  char first_name[50];
  char last_name[50];
  float grade;
};

struct User { 
  char username[50];
  char password[50];
  int isAdmin;
};

int strcasecmp_custom (const char *s1, const char *s2); // FUNCTION PROTOTYPE (DECLARATION)
int isValidName(char name[]); 
void getValidName(char name[], int size, const char *label); 
void printCentered(char* text, char symbol);
void printBoxedCentered(char* text);
void admin(struct Student students[], int *userCount);
void student(struct Student students[], int studentCount);
void UserLogin(struct User user[], int *xstudentCount, struct Student students[], int *ystudentCount);
void addStudent(struct Student students[], int *count); 
void viewStudents(struct Student students[], int count);
int searchStudent(struct Student students[], int count);
void deleteStudent(struct Student students[], int *count);
void bubbleSort (struct Student students[], int count);
void studentReport (struct Student students[], int count);
int loadFromFile (struct Student students[]);
void saveToFile (struct Student students[], int count);



int main(void) {

    struct Student students [100]; 
    struct User user [100]; 
    int studentCount = loadFromFile(students); 
    int userCount =  0;
    UserLogin(user, &userCount, students, &studentCount);
    return 0;
}

// HELPER FUNCTION FOR CASE INSENSITIVE
int strcasecmp_custom (const char *s1, const char *s2) {
  while (*s1 && *s2){
    unsigned char c1 = tolower((unsigned char) *s1);
    unsigned char c2 = tolower((unsigned char) *s2);    
  if (c1 != c2){
     return c1 - c2; 
  }     
    s1++; 
    s2++;
  }
  // loop wll finished bcos alr hit \0
  return (tolower((unsigned char)*s1) - tolower((unsigned char)*s2)); 
}

// FUNCTION DEFINITION
int isValidName(char name[]) {
   // check if it is empty // 
  if (strlen(name) == 0)
   return 0; 

   // check if spaces only // 
  for (int i = 0; name[i] != '\0'; i++) { 
   if (!isspace(name[i]))
   return 1; 
   } 
}

void getValidName(char name[], int size, const char *label) {
   int valid; 
   
   do {
    valid = 1; 
    printf("%s", label);
    fgets(name, size, stdin); 

    name[strcspn(name, "\n")] = 0; 
   
    if (!isValidName(name)){
     printf("This cannot be blank or spaces only!\n"); 
     valid = 0;
    }
   } while (!valid); 

}

void printCentered(char* text, char symbol) {
    int textLen = strlen(text);
    int sidePadding = (TOTAL_WIDTH - textLen) / 2;
    
    printf("\n");
    for(int i = 0; i < sidePadding; i++) printf("%c", symbol);
    printf("%s", text);
    for(int i = 0; i < (TOTAL_WIDTH - textLen - sidePadding); i++) printf("%c", symbol);
    printf("\n");
}

void printBoxedCentered(char* text) {
    int textLen = strlen(text);
    int totalInside = TOTAL_WIDTH - 2; 
    int sidePadding = (totalInside - textLen) / 2;
    
    printf("|");
    for (int i = 0; i < sidePadding; i++) printf(" "); 
    printf("%s", text); 
    for(int i = 0; i < (totalInside - textLen - sidePadding); i++) printf(" ");
    printf("|\n"); 
}

void admin(struct Student students[], int *studentCount) {
  int choice = 0; 
  printCentered(" STUDENT MANAGER ", '=');
  do {
    printCentered(" ADMIN PANEL ", '=');
    printf("1. Add Student\n");
    printf("2. View Students\n");
    printf("3. Search Student\n");
    printf("4. Delete Student\n");
    printf("5. Sort Students\n");
    printf("6. View Reports / Analytics\n");
    printf("7. Exit");
    printCentered("", '=');
    printf("Choose: ");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        addStudent(students, studentCount);
        break;

      case 2:
        viewStudents(students, *studentCount);
        break;

      case 3:  
        searchStudent(students, *studentCount);
        break;
      
      case 4:
        deleteStudent(students, studentCount);
        break;

      case 5:
        bubbleSort(students, *studentCount);  
        break;

      case 6:
        studentReport(students, *studentCount);
        break;

      case 7:
        saveToFile(students, *studentCount);
        printCentered(" You have exited! ", '=');
        break;
      default:
        printCentered(" Invalid Choice! Please select 1 -  7", '=');

    }
  } while (choice != 7); 

}

void student(struct Student students[], int studentCount) {
  int choice = 0;
  do {
  printCentered(" Student Panel ", '=');
    printf("1. View Student\n");
    printf("2. Search Students\n");
    printf("3. Sort Student\n");
    printf("4. Exit");
    printCentered("", '=');
    printf("Choose: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      viewStudents(students, studentCount);
      break;
    case 2:
      searchStudent(students, studentCount);
      break;
    case 3:
      bubbleSort(students, studentCount);
      break; 
    case 4:
      printCentered(" You have exited! ", '=');
      break;
    default:
      printCentered(" Invalid Choice! Please select 1 -  7", '=');
      break;
    }
  } while (choice != 4);
  
}

void UserLogin(struct User user[], int *userCount, struct Student students[], int *studentCount) {

  strcpy(user[0].username, "admin");
  strcpy(user[0].password, "admin123");
  user[0].isAdmin = 1; //admin account

  strcpy(user[1].username, "mel");
  strcpy(user[1].password, "mel123");
  user[1].isAdmin = 0; //student account

  *userCount = 2; // two users alr exist
  char inputUsername[50];
  char inputPassword[50];
  int attempts = 0;
  int authenticated = 0;
  int loggedInIndex = -1;

  while (attempts < 3 && !authenticated) {
    printf("\nLogin: ");
    scanf("%s", inputUsername);
    printf("Password: ");
    scanf("%s", inputPassword);

    for (int i = 0; i < *userCount; i++) {
      if (strcmp(user[i].username, inputUsername) == 0 &&
          strcmp(user[i].password, inputPassword) == 0) {
        authenticated = 1;
        loggedInIndex = i;
        break;
      }
    }

  if (!authenticated) {
    attempts++;
    printf("Invalid credentials. %d attempt/s left.\n", 3 - attempts);
    }
  }

if (authenticated) {
  printCentered(" Login Successful! ", ' ');
  
    if (user[loggedInIndex].isAdmin == 1) {
        admin(students, studentCount);
    } else {
        student(students, *studentCount);
    }
} else {
    printCentered(" Too many failed attempts. Exiting program. ", ' ');
    exit(1); 
  }
}

void addStudent(struct Student students[], int *count) { 
  system("cls"); 
   printCentered(" Adding student... ", ' ');
   int newID;
   int duplicate = 0;

   do {
    printf("\nEnter your ID: ");
    scanf("%d", &newID);

    if (newID < 0){
      printf("Invalid. ID should be positive\n");
    }
   } while (newID < 0);

   for (int i = 0; i < *count; i++) {
    if (students[i].id == newID) {
      duplicate = 1;
      break;
    }
   }

   if (duplicate){
    printf("ID already exists!\n");
    return; 
   }

   students[*count].id = newID;

   getchar(); 

   getValidName(students[*count].first_name, 
                sizeof(students[*count].first_name),
                "Enter your first name: ");

   getValidName(students[*count].last_name, 
                sizeof(students[*count].last_name),
                "Enter your last name: ");

   printf("Enter your Grade: "); 
   scanf("%f", &students[*count].grade); 
   printf("--------------------------------------------------\n");

   (*count)++; // *count → actual variable in main changes
   // pointers allow us to modify main’s variables directly, so no return value is needed
   printf("Student added! Current count = %d\n", *count);
} 

void viewStudents(struct Student students[], int count) {
  system("cls");
  printCentered(" Viewing student... ", ' ');
    if (count == 0) {
      printf("There's no record of students!\n");
      printf("-------------------------------------------\n"); 
      return;
    }
  printf("Stored Student:\n");
    printf("+========+============================+==========+\n");
    printf("| %-6s | %-26s | %-8s |\n", "ID", "NAME", "Grade");
    printf("+========+============================+==========+\n");
    for (int i = 0; i < count; i++) {
      char fullName [100];
      sprintf(fullName, "%s, %s",
              students[i].last_name,
              students[i].first_name);

      printf("| %-6d | %-26s | %-8.2f |\n", 
              students[i].id, 
              fullName, 
              students[i].grade); 
  }

    printf("+========+============================+==========+\n");
    printf("Press Enter to Continue...\n");
    while(getchar() != '\n');
    getchar();
}

int searchStudent(struct Student students[], int count){
  int choice = 0;
  int searchID;
  int found = 0;
  char searchFirst[100];
  char searchLast[100];

    system("cls"); 
    printf("\n+------------------------------------------------+\n");
    printBoxedCentered(" HOW DO YOU WANT TO SEARCH? ");
    printf("+------------------------------------------------+\n");
    printf("| %-46s |\n", "[1] Search student by ID");
    printf("| %-46s |\n", "[2] Search student by name");
    printf("+------------------------------------------------+\n");

    printf("Choose: ");
    scanf("%d", &choice);

    if (choice == 1) {
      printf("\nEnter the ID of the student: "); 
      scanf("%d", &searchID); 
      
      printf("+========+============================+==========+\n");
      printf("| %-6s | %-26s | %-8s |\n", "ID", "Name", "Grade");
      printf("+========+============================+==========+\n");

      // found = 0; // not found yet // ig i dont need to reset found here
        for (int i = 0; i < count; i++) {
          if (students[i].id == searchID){
            found = 1;

            char fullName[100]; 
            // concatenate strings into fullname
            sprintf (fullName, "%s, %s", // → sprint is a built in function btw = used to fills the empty box of fullname with formatted text
                    students[i].last_name,
                    students[i].first_name);

            printf("| %-6d | %-26s | %-8.2f |\n",
                  students[i].id,
                  fullName,
                  students[i].grade);

          break; // stop searching once found
        }
    } 

    if (found){
      printf("+========+============================+==========+\n");
    } else {
      char buffer[100]; // temp bucket for the txt
      // 1. this build the message into the buffer including the variable
      sprintf(buffer, "Error: Student with ID '%d' not found in records.", searchID);
      if (strlen(buffer) <= 46) {
        printf("| %-46s |\n", buffer);
      } else {
        char line1[47];
        strncpy(line1, buffer, 46);
        line1[46] = '\0';

        char* line2 = buffer + 46;
        printf("| %-46s |\n", line1);
        printf("| %-46s |\n", line2);
      }
      printf("+================================================+\n");
    } 

    printf("Press Enter to Continue...\n");
    while(getchar() != '\n');
    getchar();
  }

  else if (choice == 2) { 
      system("cls");
      while (getchar() != '\n'); 
      printf("\nEnter student's first name: ");
      fgets(searchFirst, sizeof(searchFirst), stdin); 
      searchFirst[strcspn(searchFirst, "\n")] = 0; 
      
      printf("Enter student's last name: ");
      fgets(searchLast, sizeof(searchLast), stdin);
      searchLast[strcspn(searchLast, "\n")] = 0; 
  
      printf("+========+============================+==========+\n");
      printf("| %-6s | %-26s | %-8s |\n", "ID", "Name", "Grade");
      printf("+========+============================+==========+\n");
   //  found = 0; // not found yet // same hir as well ig
    for (int i = 0; i < count; i++) {
        if (strcasecmp_custom(students[i].first_name, searchFirst) == 0 && 
            strcasecmp_custom(students[i].last_name, searchLast) == 0){
        found = 1;
        
            char fullName[100]; 
            // concatenate strings into fullname
            sprintf (fullName, "%s, %s", // → sprint is a built in function btw = used to fills the empty box of fullname with formatted text
                    students[i].last_name,
                    students[i].first_name);

            printf("| %-6d | %-26s | %-8.2f |\n",
                  students[i].id,
                  fullName,
                  students[i].grade);

        break; // stop searching once found
      }
    }
    if (found){
      printf("+========+============================+==========+\n");
    } else {
      char buffer[100]; // temp bucket for the txt
      // 1. this build the message into the buffer including the variable
      sprintf(buffer, "Error: Student '%s %s' not found in records.", searchFirst, searchLast);
      // 2. pass the finished buffer to the func
      if (strlen(buffer) <= 46) {
          // if it fits, just print it normally
          printf("| %-46s |\n", buffer);
      } else {
          // if it's too long, split it
          char line1[47];
          strncpy(line1, buffer, 46);
          line1[46] = '\0'; // cap the first 46 chars

          char* line2 = buffer + 46; // the pointer to the rest of the string

          printf("| %-46s |\n", line1); 
          printf("| %-46s |\n", line2); 
      }
      printf("+================================================+\n");
    }
    
    printf("Press Enter to Continue...\n");
    getchar();
    } 
    
    if (choice < 1 || choice > 2) {
    printf("\n=== Invalid Choice! Please select 1 - 2 ===\n");
    } 
  } 

void deleteStudent (struct Student students[], int *count) {
   system("cls");
   printCentered(" Deleting Student... ", ' ');
   printf("Enter the ID of the student to delete: ");
   int searchID = 0;
   scanf("%d", &searchID);
   int found = 0; // not found yet

     for (int i = 0; i < *count; i++) {
       if (students[i].id == searchID){
         found = 1;

         printCentered(" Student Information: ", ' ');
         printf("+========+============================+==========+\n"); 
         printf("| %-6s | %-26s | %-8s |\n", "ID", "Name", "Grade");
         printf("+========+============================+==========+\n");
            char fullName[100]; 
            sprintf (fullName, "%s, %s", 
                    students[i].last_name,
                    students[i].first_name);

            printf("| %-6d | %-26s | %-8.2f |\n",
                  students[i].id,
                  fullName,
                  students[i].grade);

         printf("+========+============================+==========+\n");
         char userChoice[4]; // for yes or no
         printf("\nAre you sure you want to delete this student? (yes/no) \n");
         scanf("%3s", userChoice); // %3s → reads up to 3 characters to avoid overflow. → userChoice is already an array, so no & needed here

         for (int j = 0; userChoice[j]; j++) {
           userChoice[j] = tolower(userChoice[j]);
         } // this converts all letters to lowercase before comparing
        
         if (strcmp(userChoice, "yes") == 0) {  
                 for (int j = i; j < *count - 1; j++) {
                   students[j] = students[j + 1];  // shift left, basically overwrite to delete
                 }
                 (*count)--;  // reduce total number of students
                 printCentered(" Student Deleted! ", '='); 
                 break; // stop loop after deletion
         } else if (strcmp(userChoice, "no") == 0) {                           
             printCentered(" Deletion Cancelled ", '=');
         } else {
             printCentered(" Invalid Input ", '=');
         }
                  
         break; // stop searching once found
       }
     }

    if (!found){
      
      printf("+================================================+\n");
      char buffer[100]; 
      sprintf(buffer, "Error: Student with ID '%d' not found in records.", searchID);
      
      if (strlen(buffer) <= 46){
       printf("| %-46s |\n", buffer); 
      } else {
        char line1[47];
        strncpy(line1, buffer, 46);
        line1[46] = '\0';

        char* line2 = buffer + 46;

        printf("| %-46s |\n", line1); 
        printf("| %-46s |\n", line2); 
        
      }
      printf("+================================================+\n");
    } 

    printf("Press Enter to Continue...\n");
    while(getchar() != '\n');
    getchar();
   
}

void bubbleSort (struct Student students[], int count) { 
  system("cls");
  int choice;
  
  printf("\n+------------------------------------------------+\n");
  printBoxedCentered(" HOW DO YOU WANT TO SORT? ");
  printf("+------------------------------------------------+\n");
  printf("| %-46s |\n", "[1] Sort by Grade");
  printf("| %-46s |\n", "[2] Sort by Last Name");
  printf("+------------------------------------------------+\n");

  printf("Choose: ");
  scanf("%d", &choice);

  if (choice == 1){
    printCentered(" Sorting Student by Grade... ", ' ');
    printf("+========+============================+==========+\n");
    printf("| %-6s | %-26s | %-8s |\n", "ID", "Name", "Grade");
    printf("+========+============================+==========+\n");
    for (int i = 0; i < count - 1; i++) {   
        for (int j = 0; j < count - 1 - i; j++) {
          if (students[j].grade > students[j + 1].grade) {
            struct Student temp = students[j];
            students[j] = students[j + 1];
            students[j + 1] = temp;
          }
        }
    }

    for (int i = 0; i < count; i++) { 
      char fullName[100]; 
      sprintf (fullName, "%s, %s", 
              students[i].last_name,
              students[i].first_name);

      printf("| %-6d | %-26s | %-8.2f |\n",
            students[i].id,
            fullName,
            students[i].grade);
    }
    printf("+========+============================+==========+\n");
    printf("Press Enter to Continue...\n");
    while(getchar() != '\n');
    getchar();
  }
  else if (choice == 2) {
    printCentered(" Sorting Student by Last Name... ", ' ');
    printf("+========+============================+==========+\n");
    printf("| %-6s | %-26s | %-8s |\n", "ID", "Name", "Grade");
    printf("+========+============================+==========+\n");
    for (int i = 0; i < count - 1; i++) {   
        for (int j = 0; j < count - 1 - i; j++) { 
          int cmp = strcasecmp_custom (students[j].last_name, // if the last name are the same, dont decide yet
                                      students[j + 1].last_name);
          if (cmp == 0){ // check the first name if the same
              cmp = strcasecmp_custom (students[j].first_name,
                                      students[j + 1].first_name); 
          }
          if (cmp > 0){ // -value > 0 = stay (false) otherwise, run this if statemet to swap 
              struct Student temp = students[j];
              students[j] = students[j + 1];
              students[j + 1] = temp;
          }
        }
      }

    for (int i = 0; i < count; i++) {
      char fullName[100]; 
      sprintf (fullName, "%s, %s",
              students[i].last_name,
              students[i].first_name);

      printf("| %-6d | %-26s | %-8.2f |\n",
            students[i].id,
            fullName,
            students[i].grade);
    }
    printf("+========+============================+==========+\n");
    printf("Press Enter to Continue...\n");
    while(getchar() != '\n');
    getchar();
  }
  else {
   printCentered(" Invalid Choice! Please Select 1 - 2 ", '=');
  }
} 
 
void studentReport (struct Student students[], int count) {

  system("cls");
  printCentered(" Student Report ", '=');
  
  if (count == 0) {
    printCentered(" There's no record of students! ", '=');
    return;
  }

  double sumofGrades = 0;
  // assuming the 1st student is the best until proven otherwise
  double bestGrade = students[0].grade;
  int bestStudent = 0;

  double worstGrade = students[0].grade;
  int worstStudent = 0;

  for (int i = 0; i < count; i++) {
      // GRADE AVERAGE
      sumofGrades += students[i].grade;

      // check if this student's grade is better (lower) than current best
      if (students[i].grade < bestGrade){
        bestGrade = students[i].grade;
        bestStudent = i; // to rmber who got this grade 
      }

      // check if this student's grade is worst (higher) than current 
      if (students[i].grade > worstGrade){
        worstGrade = students[i].grade;
        worstStudent = i; // to rmber who got this grade 
      } 
    }

    
    
    double average = sumofGrades / count; 

    char buffer[100];

    printf("+------------------------------------------------+\n");
    printBoxedCentered(" STATISTICS SUMMARY ");
    printf("+------------------------------------------------+\n");

    sprintf(buffer, "Total students: %d", count);
    printf("| %-46s |\n", buffer);

    sprintf(buffer, "Average Grade: %.2f", average);
    printf("| %-46s |\n", buffer);

    printf("+------------------------------------------------+\n");
    sprintf(buffer, "Top student: %s %s", students[bestStudent].first_name, students[bestStudent].last_name);
    printf("| %-46s |\n", buffer);

    sprintf(buffer, "grade: %.2f", students[bestStudent].grade);
    printf("| %-46s |\n", buffer);

    sprintf(buffer, "Lowest student: %s %s", students[worstStudent].first_name, students[worstStudent].last_name);
    printf("| %-46s |\n", buffer);

    sprintf(buffer, "grade: %.2f", students[worstStudent].grade);
    printf("| %-46s |\n", buffer);
    printf("+------------------------------------------------+\n");

    printf("Press enter to continue...\n");
      while (getchar() != '\n'); {
        getchar(); 
    }
 } 

int loadFromFile (struct Student students[]) {
  FILE *fp = fopen("students.txt", "r"); // open for reading
  if (fp == NULL) { 
    printf("No saved students found.\n");
    return 0; // no students loaded
  }

  int count = 0;
  while (fscanf(fp, "%d,%49[^,],%49[^,],%f\n", // ! comma separated values instead of spaces
                &students[count].id, 
                students[count].first_name, 
                students[count].last_name, 
                &students[count].grade) == 4) {
    count++;
    if (count >= 100) break; // this is to avoid overflow
  }

  fclose(fp);
  char buffer[100];
  sprintf(buffer, "%d student/s loaded from file!", count);
  printCentered(buffer, ' ');
  return count; // return number of students loaded
}
 
void saveToFile (struct Student students[], int count) {
  FILE *fp = fopen("students.txt", "w"); // open for writing
  if (fp == NULL) {
    printCentered("Error opening file for saving.", ' ');
    return;
  }

  for (int i = 0; i < count; i++) {
    fprintf(fp, "%d,%s,%s,%.2f\n", 
            students[i].id, 
            students[i].last_name, 
            students[i].first_name, 
            students[i].grade);
    }

    fclose(fp);
    printCentered("Students saved successfully!", ' ');
}