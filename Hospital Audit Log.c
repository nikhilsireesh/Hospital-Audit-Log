#include <stdio.h>
#include <string.h>

struct patient {
    int  Ano;
    char pname[50];
    char disease[50];
    int age;
};

void addpatient(struct patient patient) {
    int l=1,h=100;  
    FILE *fp;
    fp = fopen("patient.txt", "a");
    fprintf(fp, "%d %s %s %d\n", (rand()%(h))+l,patient.pname,patient.disease,patient.age);
    fclose(fp);
    printf("patient added successfully!\n");
}

void searchpatient(int id) {
    FILE *fp;
    struct patient patient;
    fp = fopen("patient.txt", "r");
    int found = 0;
    while(fscanf(fp, "%d %s %s %d", &patient.Ano,&patient.pname,&patient.disease,&patient.age) != EOF) {
        if(patient.Ano == id) {
            found = 1;
            printf("patient Found\n");
            printf("Ano: %d\n", patient.Ano);
            printf("pname: %s\n", patient.pname);
            printf("disease: %s\n", patient.disease);
            printf("age: %d\n", patient.age);
            break;
        }
    }
    if(!found) {
        printf("patient not found\n");
    }
    fclose(fp);
}

void updatepatient(int id, int newage) {
    FILE *fp;
    struct patient patient;
    fp = fopen("patient.txt", "r");
    int found = 0;

    // Create a temporary file
    FILE *temp = fopen("temp.txt", "w");

    while(fscanf(fp, "%d %s %s %d",&patient.Ano,&patient.pname,&patient.disease,&patient.age ) != EOF) {
        if(patient.Ano == id) {
            found = 1;
            patient.age = newage;
            fprintf(temp, "%d %s %s %d\n", patient.Ano,patient.pname,patient.disease,newage);
        } else {
            fprintf(temp, "%d %s %s %d\n",patient.Ano,patient.pname,patient.disease,patient.age );
        }
    }
    fclose(fp);
    fclose(temp);

    if(found) {
        remove("patient.txt");
        rename("temp.txt", "patient.txt");
        printf("patient's age  updated successfully!\n");
    } else {
        remove("temp.txt");
        printf("patient not found\n");
    }
}
void deletepatient(int id) {
    FILE *fp, *temp;
    struct patient patient;
    int found = 0;

    fp = fopen("patient.txt", "r");
    temp = fopen("temp.txt", "w");

    while(fscanf(fp, "%d %s %s %d",&patient.Ano,&patient.pname,&patient.disease,&patient.age ) != EOF) {
        if(patient.Ano != id) {
            fprintf(temp, "%d %s %s %d\n", patient.Ano,patient.pname,patient.disease,patient.age);
        } else {
            found = 1;
        }
    }
    fclose(fp);
    fclose(temp);

    if(found) {
        remove("patient.txt");
        rename("temp.txt", "patient.txt");
        printf("patient deleted successfully!\n");
    } else {
        remove("temp.txt");
        printf("patient not found\n");
    }
}


int main() {
    int choice;
    do {
        printf("Menu:\n1. Add a patient\n2. Search a patient\n3. Update a patient\n4. delete the patient\n5. exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: {
                struct patient patient;
                printf("Enter patient.pname: ");
                scanf("%s",&patient.pname );
                printf("Enter patient.disease: ");
                scanf("%s",&patient.disease);
                printf("Enter patient.age: ");
                scanf("%d", &patient.age);
                addpatient(patient);
                break;
            }
            case 2: {
                int searchId;
                printf("Enter patient Ano to search: ");
                scanf("%d", &searchId);
                searchpatient(searchId);
                break;
            }
            case 3: {
                int updateId;
                int newage;
                printf("Enter patient Ano to update: ");
                scanf("%d", &updateId);
                printf("Enter new age: ");
                scanf("%d", &newage);
                updatepatient(updateId, newage);
                break;
            }
            case 4: {
                int deleteId;
                printf("Enter patient Ano to delete: ");
                scanf("%d", &deleteId);
                deletepatient(deleteId);
                break;
            }
            case 5:
                printf("Exiting hospital management system...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid choice.\n");
        }
    } while(choice != 5);

    return 0;
}