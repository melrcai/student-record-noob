#include <stdio.h> // DAY 5 MARCH 3-8-9-11 // DANG, IM TIRED ASF. NEEDED TO COMPLETE TOLOWER SHII
#include <string.h>
#include <ctype.h> // for tolower function and isspace()

struct Student { // a structure called Student → this is a data container
  int id;
  char first_name[50];
  char last_name[50];
  float grade;
};

int strcasecmp_custom (const char *s1, const char *s2); // FUNCTION PROTOTYPE (DECLARATION)
void addStudent(struct Student students[], int *count); 
int isValidName(char name[]); 
void getValidName(char name[], int size, const char *label); 
void viewStudents(struct Student students[], int count);
int searchStudent(struct Student students[], int count);
void deleteStudent(struct Student students[], int *count);
void bubbleSort (struct Student students[], int count);
int loadFromFile (struct Student students[]);
void saveToFile (struct Student students[], int count);



int main(void) {

    int choice = 0; 
    struct Student students [100]; // → array for many students
    //can i use size of ????? ////////
    int count = loadFromFile(students); // load students from the file first, then tell me how many were loaded
  //  int count = 0; // this keep track on how many students are stored (↑ updated to this ↑)
    /*  for (int i = 0; i < count; i++) { // count = 0 → first student goes into students[0]
        students[count].id; // → goes inside the “id” slot of that student
        students[count].first_name;
      students[count].grade;
      count++;
    }*/

    printf("======== STUDENT MANAGER ========\n");
    do {
      printf("\nSelect an option\n");
      printf("\n1. Add Student\n");
      printf("2. View Students\n");
      printf("3. Search Student\n");
      printf("4. Delete Student\n");
      printf("5. Sort Students\n");
      printf("6. Exit\n");
      printf("\nChoose: ");
      scanf("%d", &choice);

      switch (choice) {
        case 1:
          addStudent(students, &count);
          break;

        case 2:
          viewStudents(students, count);
          break;

        case 3:  
          searchStudent(students, count);
          break;
        
        case 4:
          deleteStudent(students, &count);
          break;

        case 5:
          bubbleSort(students, count);  // prev was .grade lol, it must be the wholo struct
          break;
        case 6:
          saveToFile(students, count);
          printf("\n======== Exiting... ========\n");
          break;
        default:
          printf("\n=== Invalid Choice! Please select 1 - 6 ===\n");
      }
    } while (choice != 6); // will repeat menu as long as the user's choice is not 6


    return 0;
  }

// HELPER FUNCTION FOR CASE INSENSITIVE
int strcasecmp_custom (const char *s1, const char *s2) {
  while (*s1 && *s2){ // this will decide when to stop. when the pointer reaches \0, for ex. while (0 && smth) → false, loop stops
    unsigned char c1 = tolower((unsigned char) *s1);
    unsigned char c2 = tolower((unsigned char) *s2);    
    if (c1 != c2){
     return c1 - c2; // if they are different, return the difference (positive or negative)
    }     
    s1++; // f thy match, move to the nxt ltter
    s2++;
  }
  // loop wll finished bcos alr hit \0
  return (tolower((unsigned char)*s1) - tolower((unsigned char)*s2)); // this still confused me mb *chck cmmnt (ans)
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
   int valid; // should be declare outside the do while loop coz this cannot be recognized by while loop
   
   do {
    valid = 1; // has input
    printf("%s", label);
    fgets(name, size, stdin); // fgets enter key too with \n after the first_name and last_name

    name[strcspn(name, "\n")] = 0; // again, this is to remove the \n from the end of the string that fgets adds. strcspn finds the index of \n n replaces it with \0 to terminate the string properly.
   
    if (!isValidName(name)){
     printf("This cannot be blank or spaces only!\n"); 
     valid = 0;
    }
   } while (!valid); // should continue as long as it's still not valid

}

void addStudent(struct Student students[], int *count) { // why void?? (ans)
   printf("\n======== Adding student... ========\n");
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
    return; // this still confused the fck out of me. again, this function will stop and go back where it was called
   }

   students[*count].id = newID;

   getchar(); // clears leftover newline from previous scanf

   getValidName(students[*count].first_name, 
                sizeof(students[*count].first_name),
                "Enter your first name: ");

   getValidName(students[*count].last_name, 
                sizeof(students[*count].last_name),
                "Enter your last name: ");

   printf("Enter your Grade: "); 
   scanf("%f", &students[*count].grade); // ← user input
  
   (*count)++; // *count → actual variable in main changes
   // pointers allow us to modify main’s variables directly, so no return value is needed.
   printf("Student added! Current count = %d\n", *count);
} // 😆😆 LOL I DEFINE THE addStudent BEFORE THE STRUCT. HOW PROGRAM WILL READ THAT IF IT DOESNT KNOW THE struct Student YET LMAO

void viewStudents(struct Student students[], int count) {
  printf("\n======== Viewing students... ========\n");
  printf("-------------------------------------------\n"); 
  printf("\nStored Student:\n");
  printf("-------------------------------------------\n"); 
    for (int i = 0; i < count; i++) {
      printf("ID: %d\n", students[i].id); // i prev use students[count] which always accesses the nxt empty slot
      printf("Name: %s %s\n", students[i].first_name, students[i].last_name); // → use this to access the stored students
      printf("Grade: %.2f\n", students[i].grade);
      printf("-------------------------------------------\n"); 
  }
}

int searchStudent(struct Student students[], int count){
  int choice = 0;
  int searchID;
  int found = 0;
  char searchFirst[100];
  char searchLast[100];


    printf("\n======== Searching student... ========\n\n");
    printf("1. Search student by ID\n");
    printf("2. Search student by name\n");
    printf("Choose: ");
    scanf("%d", &choice);

    if (choice == 1) {
      printf("Enter the ID of the student: "); // ⁉️⁉️ now the fckn problem is whenever i found the information of the student, the choices will appear againlol.
      scanf("%d", &searchID); //prev was on dowhile (ud)

     // found = 0; // not found yet // ig i dont need to reset found here
      for (int i = 0; i < count; i++) {
        if (students[i].id == searchID){
          found = 1;
          printf("\n======== Student Found ========\n");
          printf("\nStudent Information:\n");
          printf("ID: %d\n", students[i].id);
          printf("Name: %s %s\n", students[i].first_name, students[i].last_name);
          printf("Grade: %.2f\n", students[i].grade);

        break; // stop searching once found
     
      }
    }
    if (!found){
    printf("Error: Student with ID '%d' not found in records.\n", searchID); 
    }

    printf("Press Enter to Continue...\n");
    while(getchar() != '\n');
    getchar();
  }

  else if (choice == 2) { 
      while (getchar() != '\n'); // removes the \n from the input buffer from the prev scanf
      printf("Enter student's first name: ");
      fgets(searchFirst, sizeof(searchFirst), stdin); // this is for user input (name + \n)
      searchFirst[strcspn(searchFirst, "\n")] = 0; 
      
      printf("Enter student's last name: ");
      fgets(searchLast, sizeof(searchLast), stdin); // this is for user input (name + \n)
      searchLast[strcspn(searchLast, "\n")] = 0; 
  
      
   //  found = 0; // not found yet // same hir as well ig
    for (int i = 0; i < count; i++) {
        if (strcasecmp_custom(students[i].first_name, searchFirst) == 0 && 
            strcasecmp_custom(students[i].last_name, searchLast) == 0){
        found = 1;
        printf("\n======== Student Found ========\n");
        printf("\nStudent Information:\n");
        printf("ID: %d\n", students[i].id);
        printf("Name: %s %s\n", students[i].first_name, students[i].last_name);
        printf("Grade: %.2f\n", students[i].grade);

        break; // stop searching once found
      }
    }
    if (!found){
    printf("Error: Student '%s %s' not found in records.\n", searchFirst, searchLast); 
    }

    printf("Press Enter to Continue...\n");
    // while(getchar() != '\n'); ⁉️⁉️ why this made me to enter twice (ans)
    getchar();
    } 
    
    if (choice < 1 || choice > 2) {
    printf("\n=== Invalid Choice! Please select 1 - 2 ===\n");
    } 
  } 

   

void deleteStudent (struct Student students[], int *count) {
   printf("\n======== Delete Student ========\n");
   printf("Enter the ID of the student to delete: ");
   int searchID = 0;
   scanf("%d", &searchID);

   int found = 0; // not found yet // i removed the int coz i declare it alr from case 3??
     for (int i = 0; i < *count; i++) {
       if (students[i].id == searchID){
         found = 1;
         printf("\n======== Student Found ========\n");
         printf("\nStudent Information:\n");
         printf("ID: %d\n", students[i].id);
         printf("Name: %s %s\n", students[i].first_name, students[i].last_name);
         printf("Grade: %.2f\n", students[i].grade);

         char userChoice[4]; // for yes or no
         printf("\n\nAre you sure you want to delete this student? (yes/no) \n");
         scanf("%3s", userChoice); // %3s → reads up to 3 characters to avoid overflow. → userChoice is already an array, so no & needed here.

         for (i = 0; userChoice[i]; i++) {
           userChoice[i] = tolower(userChoice[i]);
         } // this converts all letters to lowercase before comparing.
        
         if (strcmp(userChoice, "yes") == 0) {  // this becomes true, then print. y == y ✔ , e == e ✔ , // s == s ✔ , // \0 == \0 ✔
             for (i = 0; i < *count; i++) { // → loops through every student in the array to find the one with searchID
               if (students[i].id == searchID){ // → checks if the current student matches the ID to delete
                 // ↓ shift all students after i left ↓ / take not of j = 1 /
                 for (int j = i; j < *count - 1; j++) { // → shifts all students after the deleted one one position to the left:
                   students[j] = students[j + 1];  // shift left, basically overwrite to delete
                 }
                 (*count)--;  // reduce total number of students
                 printf("Student deleted!\n"); 
                 break; // stop loop after deletion
               }                                    
             }
         } else if (strcmp(userChoice, "no") == 0) {                           
             printf("Deletion canceled.\n");                                   
         } else {
             printf("Invalid input!\n");
         }
                  
         break; // stop searching once found
       }
     }

   if (found == 0){
     printf("\n======== Student not found ========\n");
   }
}

void bubbleSort (struct Student students[], int count) { // 😆😆 prev was int lol. bubble sort usually doesn’t need to return anything, because it modifies the array in place

  int choice;
  
  printf("\n-------------------------------------------\n\n"); 
  printf("1. Sort by Grade: \n");
  printf("2. Sort by Last Name: \n");
  printf("Choose: ");
  scanf("%d", &choice);
  
  if (choice == 1){
    printf("\n======== Sorting Student by Grade ========\n\n");
    printf("-------------------------------------------\n"); 
    for (int i = 0; i < count - 1; i++) {     // ⁉️⁉️⁉️
        for (int j = 0; j < count - 1 - i; j++) { // CONFUSED ASF SA -1 N YAN (ans)
          if (students[j].grade > students[j + 1].grade) {
            struct Student temp = students[j];
            students[j] = students[j + 1];
            students[j + 1] = temp;
          }
        }
    }

    for (int i = 0; i < count; i++) { // ⁉️ printing i, i → used to traverse the final sorted list
      printf("ID: %d\n", students[i].id); // j → only exists inside bubbleSort for comparing neighbors
      printf("Name: %s %s\n", students[i].first_name, students[i].last_name); // j has NO meaning anymore once sorting is finished. ⁉️
      printf("Grade: %.2f\n", students[i].grade);
      printf("-------------------------------------------\n"); 
    }
  }
  else if (choice == 2) {
    printf("\n======== Sorting Student by Last Name ========\n\n");
    printf("-------------------------------------------\n");
    
    for (int i = 0; i < count - 1; i++) {     // ⁉️⁉️⁉️
        for (int j = 0; j < count - 1 - i; j++) { // CONFUSED ASF SA -1 N YAN (ans)
          int cmp = strcasecmp_custom (students[j].last_name,
                                      students[j + 1].last_name);
          if (cmp == 0){
              cmp = strcasecmp_custom (students[j].first_name,
                                      students[j + 1].first_name); 
          }
          if (cmp > 0){
              struct Student temp = students[j];
              students[j] = students[j + 1];
              students[j + 1] = temp;
          }
        }
      }

    for (int i = 0; i < count; i++) { // ⁉️ printing i, i → used to traverse the final sorted list
          printf("ID: %d\n", students[i].id); // j → only exists inside bubbleSort for comparing neighbors
          printf("Name: %s, %s\n", students[i].last_name, students[i].first_name); // j has NO meaning anymore once sorting is finished. ⁉️
          printf("Grade: %.2f\n", students[i].grade);
          printf("-------------------------------------------\n");
    }
  }
  else {
    printf("\n=== Invalid Choice! Please select 1 - 2 ===\n");
  }
} // ‼️‼️ I NEED TO SWAP THE WHOLE STRUCT LOL, NOT JUST THE GRADE
 
int loadFromFile (struct Student students[]) {
  FILE *fp = fopen("students.txt", "r"); // open for reading
  if (fp == NULL) { // ⁉️⁉️ why not *fp?? i feel liek i alr know, i js forgot lol
    printf("No saved students found.\n");
    return 0; // no students loaded
  }

  int count = 0;
  while (fscanf(fp, "%d %49s %49s %f", &students[count].id, students[count].first_name, students[count].last_name, &students[count].grade) == 4) {
    count++;
    if (count >= 100) break; // this is to avoid overflow
  }

  fclose(fp);
  printf("%d students loaded from file!\n", count);
  return count; // return number of students loaded
}
 
void saveToFile (struct Student students[], int count) {
  FILE *fp = fopen("students.txt", "w"); // open for writing
  if (fp == NULL) {
    printf("Error opening file for saving.\n");
    return;
  }

  for (int i = 0; i < count; i++) {

    fprintf(fp, "ID NUMBER        NAME               GPA\n");
    fprintf(fp, "%d                %s, %s    %.2f\n", students[i].id, students[i].last_name, students[i].first_name, students[i].grade);
    }

    fclose(fp);
    printf("Students saved successfully!\n"); 
}
 
 
 
 
  /*
  TAKE NOTE::
  1. strcspn(s1.name, "\n")
  → Find the position of the first \n inside the string. (the index where \n is found)
  → s1.name[ index ] = accessing that position 
  → 0 == '\0' → replacing \n w \0 a null terminator

  2. struct Student s1; // stucture variable of Student called s1 → this is to access the structure
  → replacing that w this struct Student students [100];
  → coz that is for storing a single student 

  3. How count works? (inside the option 1)
  → count is the index of the next empty box on the shelf.
  → only after you store all three field, inrement count
  → to move to the next empty box
  
  CONCEPTUALLY:
              Shelf → students[100]

            Adding a student:
                pick the box at index count
                fill compartments: id, first_name, grade
                move count++ → next empty box

            Viewing students:
                for i = 0 to count-1:
                    print students[i].id
                    print students[i].name
                    print students[i].grade

  KEY IDEA:
  students = array of structs
  students[count] = current struct to fill // ana: notebook : page :: students[count] : .id, .name, .grade
  .id, .name, .grade = compartments inside that struct
  & = memory address needed for scanf to write numbers

  INTERPRETATION:
  Notebook → the array students[100] (holds many students)
  Page → one element of the array, students[count] (one student struct)
  Content of page → the fields inside the struct: .id, .name, .grade

  VISUALIZATION:
  students[0] ─> id: 101, first_name: "Alice", grade: 95.5
  students[1] ─> id: 102, first_name: "Bob", grade: 88.0
  students[2] ─> empty box
  ...
  count = 2 → next empty box is students[2]

  4. void addStudent(){
   We are passing a pointer to 'count' (int *count) to the function.
   This means we are sending the *address* of the variable in main, not a copy.
   Inside the function, using (*count)++ modifies the original variable in main.
   The function stack frame will disappear after execution, but the actual 'count' in main is updated.
   This way, addStudent can change the main program's count directly without returning it.
  }

  5. case 4 
→ Outer loop (i):
  Loops through every student in the array to find the one with searchID.
→ if (students[i].id == searchID):
  Checks if the current student matches the ID to delete.
→ Inner loop (j):
  Shifts all students after the deleted one one position to the left:
  students[i] = students[i+1]
  students[i+1] = students[i+2]
  ...
  This removes the “gap” in the array.
→ count--:
  Decreases the total number of students since one has been deleted
→ printf("Student deleted!\n");:
  Informs the user that deletion was successful.
  ✅ Inside the if ensures it only prints if a student was actually found.
→ break;:
  Stops the loop early because the student has been deleted — no need to continue scanning.

  ⁉️ Why this works without temp ⁉️
  don’t need a temporary variable because shifting is always forward.
  students[j] = students[j+1] safely overwrites the current slot with the next student.

  5. case 5 
  Function signature (sorting an array of structs)
  ⁉️ What does bubble sort need? ⁉️
  a. the array itself → students
  b. the number of students currently stored → count

  6. bubbleSort()
  Passing by value vs passing by reference
  count is an int in main() that tells us how many students are currently stored.
  When you call: bubbleSort(students, count);

  a. You are passing the value of count (like “3” or “10”) to the function.
  b. The function only needs to read that value to know how many elements to loop over.
  c. You are not modifying count inside bubbleSort, so you don’t need its address.
  ‼️‼️ for sorting, count is just read-only, so we pass it by value not unless if i'll increase
  or decrease count

  7. void bubbleSort (struct Student students[], int count) { // 😆😆 prev was int lol. bubble sort usually doesn’t need to return anything, because it modifies the array in place
        for (int i = 0; i < count; i++) {
          for (int j = i; j < count - 1; j++) {
            if (students[j].grade > students[j + 1].grade) {
              int temp = students[j].grade;
              students[j].grade = students[j + 1.grade];
              students[j + 1].grade = temp;

            }
          }
        }
      } ⚠️⚠️ THIS IS WRONG LOL. WHAT U DOIN BITCH

  i = 0 // OUTER LOOP (passes)
  Pass 1 → biggest grade moves to the end
  Pass 2 → second biggest moves near end
  Pass 3 → next one moves...
  ⁉️ why is the OUTER loop count - 1 ⁉️
  run sorting passes count-1 times
  bcos each pass places one element in its final position
  the last remaining element is automatically sorted

  for (int i = 0; i < count - 1; i++) {     
      i = number of passes
      each pass moves one largest grade to its correct position at the end

  for (int j = 0; j < count - 1 - i; j++) {
      j compares adjacent students (j and j+1)
      count - 1 → prevents going out of array bounds
      - i → ignore the last elements already sorted from previous passes

  8. void loadFromFile (struct Student students[]) { }
  ⁉️ What happens here: ⁉️
  fscanf → reads ID, name, grade from each line
  Loop until we reach the end of file or the array is full
  Return the number of students loaded (look in onenote for more info)

  9. int searchStudent(struct Student students[], int count){
  → while(getchar() != '\n'); 
   - this made me enter twice bcos of this.
   - this clears all leftover char, including the \n i just typed for the name.
  →  getchar();
   - so now this asks me to enter, which will lead to entering twice

  10. int strcasecmp_custom (const char *s1, const char *s2) {  
  → return (tolower((unsigned char)*s1) - tolower((unsigned char)*s2)); 
  A. matched
    - *s1 and *s2 are both 0 (ASCII)
    - 0 - 0 = 0
    - res: 0 (equal strings)

  B. prolly one is shorter 
    - s1 = Mel → s2 = Melie
    - the loop goes to m, e, l, and s1 hits the end '\0' but s2 is at the letter 'i' 
    - the loop stops 
    - 0 - 105 (ASCII)
    - res: -105 (not 0 so strings r not matched)
  */

/*





????

i wanted them to be in function

*/   