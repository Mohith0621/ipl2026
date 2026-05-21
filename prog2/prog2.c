#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Student
{
    int roll;
    char name[30];
    float marks;
};

// Function to create array of seek positions
int createIndex(FILE *fp, long pos[])
{
    struct Student s;
    int count = 0;

    rewind(fp);

    while (1)
    {
        pos[count] = ftell(fp);

        if (fscanf(fp, "%d %s %f",
                   &s.roll,
                   s.name,
                   &s.marks) != 3)
        {
            break;
        }

        count++;
    }

    return count;
}

// Function to display record using seek position
void displayRecord(FILE *fp, long position)
{
    struct Student s;

    fseek(fp, position, SEEK_SET);

    fscanf(fp, "%d %s %f",
           &s.roll,
           s.name,
           &s.marks);

    printf("\nRecord Details:\n");
    printf("Roll Number : %d\n", s.roll);
    printf("Name        : %s\n", s.name);
    printf("Marks       : %.2f\n", s.marks);
}

int main()
{
    struct Student s[MAX];
    long positions[MAX];
    FILE *fp;
    int n, i, choice, total;

    printf("Enter number of records: ");
    scanf("%d", &n);

    // Input records from user
    for(i = 0; i < n; i++)
    {
        printf("\nEnter details for student %d\n", i+1);

        printf("Roll Number: ");
        scanf("%d", &s[i].roll);

        printf("Name: ");
        scanf("%s", s[i].name);

        printf("Marks: ");
        scanf("%f", &s[i].marks);
    }

    // Store records in ASCII file
    fp = fopen("students.txt", "w");

    if(fp == NULL)
    {
        printf("File opening error\n");
        return 1;
    }

    for(i = 0; i < n; i++)
    {
        fprintf(fp, "%d %s %.2f\n",
                s[i].roll,
                s[i].name,
                s[i].marks);
    }

    fclose(fp);

    // Open file for reading
    fp = fopen("students.txt", "r");

    if(fp == NULL)
    {
        printf("File opening error\n");
        return 1;
    }

    // Create seek positions
    total = createIndex(fp, positions);

    printf("\nSeek Positions:\n");
    for(i = 0; i < total; i++)
    {
        printf("Record %d -> Byte Position %ld\n",
               i + 1,
               positions[i]);
    }

    // Ask user which record to display
    printf("\nEnter record number to display (1-%d): ", total);
    scanf("%d", &choice);

    if(choice >= 1 && choice <= total)
    {
        displayRecord(fp, positions[choice - 1]);
    }
    else
    {
        printf("Invalid record number\n");
    }

    fclose(fp);

    return 0;
}