#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int id;
    char name[100];
    char designation[100];
    double salary;
    struct Employee *left;
    struct Employee *right;
};

struct Employee *createEmployee(int id, const char *name, const char *designation, double salary) {
    struct Employee *newEmployee = (struct Employee *)malloc(sizeof(struct Employee));
    newEmployee->id = id;
    strcpy(newEmployee->name, name);
    strcpy(newEmployee->designation, designation);
    newEmployee->salary = salary;
    newEmployee->left = NULL;
    newEmployee->right = NULL;
    return newEmployee;
}

struct Employee *insertEmployee(struct Employee *root, struct Employee *employee) {
    if (root == NULL) {
        return employee;
    }

    if (employee->id < root->id) {
        root->left = insertEmployee(root->left, employee);
    } else if (employee->id > root->id) {
        root->right = insertEmployee(root->right, employee);
    }

    return root;
}

struct Employee *findMin(struct Employee *node) {
    struct Employee *current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

struct Employee *deleteEmployee(struct Employee *root, int id) {
    if (root == NULL) {
        return root;
    }

    if (id < root->id) {
        root->left = deleteEmployee(root->left, id);
    } else if (id > root->id) {
        root->right = deleteEmployee(root->right, id);
    } else {
        if (root->left == NULL) {
            struct Employee *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Employee *temp = root->left;
            free(root);
            return temp;
        }
        struct Employee *temp = findMin(root->right);
        root->id = temp->id;
        root->right = deleteEmployee(root->right, temp->id);
    }
    return root;
}
void displayEmployee(struct Employee *employee) {
    if (employee == NULL) {
        printf("Employee not found.\n");
        return;
    }

    printf("ID: %d\n", employee->id);
    printf("Name: %s\n", employee->name);
    printf("Designation: %s\n", employee->designation);
    printf("Salary: %.2lf\n", employee->salary);
    printf("\n");
}

void inOrderTraversal(struct Employee *root) {
    if (root == NULL) {
        return;
    }
    inOrderTraversal(root->left);
    displayEmployee(root);
    inOrderTraversal(root->right);
}

void preOrderTraversal(struct Employee *root) {
    if (root == NULL) {
        return;
    }
    displayEmployee(root);
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}
void postOrderTraversal(struct Employee *root) {
    if (root == NULL) {
        return;
    }
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    displayEmployee(root);
}


struct Employee *searchEmployeeByID(struct Employee *root, int id) {
    if (root == NULL || id == root->id) {
        return root;
    }

    if (id < root->id) {
        return searchEmployeeByID(root->left, id);
    }

    return searchEmployeeByID(root->right, id);
}



int countEmployees(struct Employee *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countEmployees(root->left) + countEmployees(root->right);
}

void updateSalary(struct Employee *root, int id, double newSalary) {
    struct Employee *employee = searchEmployeeByID(root, id);
    if (employee != NULL) {
        employee->salary = newSalary;
        printf("Employee with ID %d: Salary updated to %.2lf\n", id, newSalary);
    } else {
        printf("Employee with ID %d not found.\n", id);
    }
}

void updateDesignation(struct Employee *root, int id, const char *newDesignation) {
    struct Employee *employee = searchEmployeeByID(root, id);
    if (employee != NULL) {
        strcpy(employee->designation, newDesignation);
        printf("Employee with ID %d: Designation updated to %s\n", id, newDesignation);
    } else {
        printf("Employee with ID %d not found.\n", id);
    }
}



int main() {
    struct Employee *root = NULL;
    int id;
    char name[100];
    char designation[100];
    double salary;
    int choice;

    do {
        printf("Employee Management System Menu:\n");
        printf("1. Insert Employee\n");
        printf("2. Delete Employee by ID\n");
        printf("3. Search Employee by ID\n");
        printf("4. Count Employees\n");
        printf("5. Display Employee Tree Structure\n");
        printf("6. Display Employee Tree Structure(post-order traversal\n");
        printf("7. Display Employee Tree Structure(pre-order traversal\n");
        printf("8. Update employee Designation and Salary\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                printf("Enter Employee ID: ");
                scanf("%d", &id);
                printf("Enter Employee Name: ");
                scanf("%s", name);
                printf("Enter Employee Designation: ");
                scanf("%s", designation);
                printf("Enter Employee Salary: ");
                scanf("%lf", &salary);

                struct Employee *employee = createEmployee(id, name, designation, salary);
                root = insertEmployee(root, employee);
                break;
            }
            case 2: {
                printf("Enter Employee ID to delete: ");
                scanf("%d", &id);
                root = deleteEmployee(root, id);
                break;
            }
            case 3: {
                printf("Enter Employee ID to search: ");
                scanf("%d", &id);
                struct Employee *foundEmployee = searchEmployeeByID(root, id);
                displayEmployee(foundEmployee);
                break;
            }
            case 4: {
                int count = countEmployees(root);
                printf("Total number of employees: %d\n", count);
                break;
            }
            case 5: {
                printf("Binary Tree Structure (In-order traversal):\n");
                inOrderTraversal(root);
                break;
            }
          case 6: {
                printf("Binary Tree Structure (pre-order traversal):\n");
                preOrderTraversal(root);
                break;
            }
          case 7: {
                printf("Binary Tree Structure (post-order traversal):\n");
                postOrderTraversal(root);
                break;
            }
          
        
        case 8: {
    int updateChoice;
    printf("Update Employee Information:\n");
    printf("1. Update Salary\n");
    printf("2. Update Designation\n");
    printf("Enter your update choice: ");
    scanf("%d", &updateChoice);

    switch (updateChoice) {
        case 1: {
            int id;
            double newSalary;
            printf("Enter Employee ID: ");
            scanf("%d", &id);
            printf("Enter New Salary: \n");
            scanf("%lf", &newSalary);
            updateSalary(root, id, newSalary);
            break;
        }
        case 2: {
            int id;
            char newDesignation[100];
            printf("Enter Employee ID: ");
            scanf("%d", &id);
            printf("Enter New Designation: ");
            scanf("%s", newDesignation);
            updateDesignation(root, id, newDesignation);
            break;
        }
      
    break;
    }
}
}
    } while (choice != 9);
}