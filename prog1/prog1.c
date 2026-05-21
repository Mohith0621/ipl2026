#include <stdio.h>
#include <stdlib.h>

struct Student {
    int id;
    char name[30];
    float marks;
};

// Function to display mth record using fseek
void getRecord(char filename[], int m)
{
    FILE *fp;
    struct Student s;

    fp = fopen(filename, "rb");

    if(fp == NULL)
    {
        printf("File not found\n");
        return;
    }

    // Move to mth record
    fseek(fp, (m-1)*sizeof(struct Student), SEEK_SET);

    if(fread(&s, sizeof(struct Student), 1, fp)==1)
    {
        printf("\nRecord %d:\n",m);
        printf("ID = %d\n",s.id);
        printf("Name = %s\n",s.name);
        printf("Marks = %.2f\n",s.marks);
    }
    else
    {
        printf("Record does not exist\n");
    }

    fclose(fp);
}


// Delete record by ID
void deleteRecord(char filename[], int deleteID)
{
    FILE *fp, *temp;
    struct Student s;
    int found=0;

    fp = fopen(filename,"rb");
    temp = fopen("temp.dat","wb");

    if(fp==NULL)
    {
        printf("File not found\n");
        return;
    }

    while(fread(&s,sizeof(struct Student),1,fp))
    {
        if(s.id != deleteID)
        {
            fwrite(&s,sizeof(struct Student),1,temp);
        }
        else
        {
            found=1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(filename);
    rename("temp.dat",filename);

    if(found)
        printf("Record deleted successfully\n");
    else
        printf("Record not found\n");
}


void displayAll(char filename[])
{
    FILE *fp;
    struct Student s;

    fp=fopen(filename,"rb");

    printf("\nAll Records:\n");

    while(fread(&s,sizeof(struct Student),1,fp))
    {
        printf("%d %s %.2f\n",
                s.id,
                s.name,
                s.marks);
    }

    fclose(fp);
}



int main()
{
    int n,i,m,deleteID;
    struct Student s;

    FILE *fp=fopen("student.dat","wb");

    printf("Enter number of records: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("\nEnter ID Name Marks:\n");

        scanf("%d",&s.id);
        scanf("%s",s.name);
        scanf("%f",&s.marks);

        fwrite(&s,sizeof(struct Student),1,fp);
    }

    fclose(fp);

    displayAll("student.dat");


    printf("\nEnter m to get mth record: ");
    scanf("%d",&m);

    getRecord("student.dat",m);


    printf("\nEnter ID to delete: ");
    scanf("%d",&deleteID);

    deleteRecord("student.dat",deleteID);

    displayAll("student.dat");

    return 0;
}