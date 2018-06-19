#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct enterprise
{
    unsigned long long ID;
    char name[50];
    char branch[30];
    double income;
    double debt;
    unsigned int employees;
}t_Enterprise;

typedef struct node
{
    t_Enterprise enterprise;
    struct node *next;
}t_Node;

int menu();
void loadFile(t_Node **head);
void saveFile(t_Node* head);
char *getFilePath();
void addNode(t_Node **head, t_Enterprise tempEnterprise);
t_Enterprise getEnterprise(t_Node *head);
void deleteList(t_Node **head);
void deleteNodeAtPoss(t_Node **head, int poss);
void deleteEnterprises(t_Node **head);
int isUniqueID(t_Node *head, unsigned long long ID);
void printNode(t_Node *head);
int nodesCounter(t_Node *head);
void swap(t_Node **A, t_Node **B);
void bubbleSort(t_Node **head);
void bubbleSortExtra(t_Node **head, char *branch);
void printSortedNodes(t_Node **head);
void printEnterprise(t_Enterprise tempEnterprise);

int main()
{
    t_Node *head = NULL;

    while(1)
    {
        system("cls");
        switch (menu())
        {
            case 1:
                loadFile(&head);
                break;
            case 2:
                saveFile(head);
                break;
            case 3:
                addNode(&head, getEnterprise(head));
                break;
            case 4:
                printNode(head);
                break;
            case 5:
                printSortedNodes(&head);
                break;
            case 6:
                deleteEnterprises(&head);
                break;
            default:
                deleteList(&head);
                return 0;
                break;
        }
        system("PAUSE");
    }
}

int menu()
{
    int input;

    printf("MENU\n\n");
    printf("1. Load file\n");
    printf("2. Save file\n");
    printf("3. Add an enterprise\n");
    printf("4. Print data by enterprise ID\n");
    printf("5. List enterprises by branch\n");
    printf("6. Delete enterprises by debt\n");
    printf("0. Exit\n");
    do
    {
        printf("\nSelect option: ");
        fflush(stdin);
        scanf("%d", &input);
        printf("\n");
    }while(input < 0 || input > 6);

    return input;
}

void printNode(t_Node *head)
{
    unsigned long long ID;

    if(!(head))
    {
		printf("List is empty!\n");
		return;
	}
	printf("\nEnter ID: ");
    fflush(stdin);
    scanf("%llu", &ID);
	while(head->next != NULL)
	{
	    if(ID == head->enterprise.ID)
        {
            printEnterprise(head->enterprise);
            return;
        }
        head = head->next;
	}
	printf("Enterprise not found!\n");
}

int isUniqueID(t_Node *head, unsigned long long ID)
{
	while(head)
        {
		if(head->enterprise.ID == ID)
		{
			printf("ID already exist!\n");
			return 0;
		}
		head = head->next;
	}

	return 1;
}

t_Enterprise getEnterprise(t_Node *head)
{
    t_Enterprise newEnterprise;

    do
    {
		printf("Enter ID: ");
		fflush(stdin);
		scanf("%llu", &newEnterprise.ID);
	}while(!(isUniqueID(head, newEnterprise.ID)) || !newEnterprise.ID || newEnterprise.ID > 999999999999);
	do
	{
		printf("\nEnter name: ");
		fflush(stdin);
		gets(newEnterprise.name);
	}while(!strlen(newEnterprise.name));
	do
	{
		printf("\nEnter branch: ");
		gets(newEnterprise.branch);
		newEnterprise.branch[0] = toupper(newEnterprise.branch[0]);
	}while (!strlen(newEnterprise.branch));
	do
	{
		printf("\nEnter income: ");
		fflush(stdin);
		scanf("%lf", &newEnterprise.income);
	}while (newEnterprise.income < 0);
	do
	{
		printf("\nEnter debt: ");
		fflush(stdin);
		scanf("%lf", &newEnterprise.debt);
	}while (newEnterprise.debt < 0);
	do
	{
		printf("\nEnter employees count: ");
		fflush(stdin);
		scanf("%u", &newEnterprise.employees);
		printf("\n");
	}while (newEnterprise.employees < 0);

	return newEnterprise;
}

void printEnterprise(t_Enterprise tempEnterprise)
{
	printf("\nID: %llu\n", tempEnterprise.ID);
	printf("Name: %s\n", tempEnterprise.name);
    printf("Branch: %s\n", tempEnterprise.branch);
	printf("Income: %.2lf\n", tempEnterprise.income);
	printf("Debt: %.2lf\n", tempEnterprise.debt);
	printf("Workers: %u\n", tempEnterprise.employees);
}

void addNode(t_Node **head, t_Enterprise tempEnterprise)
{
    t_Node *tempNode = (t_Node*)malloc(sizeof(t_Node));
    t_Node *tempNode2 = *head;
    tempNode->enterprise = tempEnterprise;
    tempNode->next = NULL;

    if(!(*head))
    {
		*head = tempNode;
        printf("First Enterprise added successfully!\n");
		return;
	}
    while(tempNode2->next)
		tempNode2 = tempNode2->next;
	tempNode2->next = tempNode;
    printf("New Enterprise added successfully!\n");
}

int nodesCounter(t_Node *head)
{
	int n = 0;

	while(head)
    {
		n++;
		head = head->next;
	}

	return n;
}

void swap(t_Node **A, t_Node **B)
{
	t_Enterprise tempEnterprise = (*A)->enterprise;

	(*A)->enterprise = (*B)->enterprise;
	(*B)->enterprise = tempEnterprise;
}

void bubbleSort(t_Node **head)
{
	t_Node *tempNode = *head;
	int i, j, n = nodesCounter(*head);

	if(!n || n == 1)
		return;
	for(i = 0; i < n - 1; i++, tempNode = (*head))
        {
		for(j = 0; j < n - i - 1; j++)
		{
			if(strcmp(tempNode->enterprise.branch, tempNode->next->enterprise.branch) > 0)
			{
				swap(&tempNode, &tempNode->next);
			}
			tempNode = tempNode->next;
		}
	}
}

void bubbleSortExtra(t_Node **head, char *branch)
{
	t_Node *tempNode = *head;
	int i, j, n = nodesCounter(*head);

	if(!n || n == 1)
		return;
	for(i = 0; i < n - 1; i++, tempNode = (*head))
        {
		for(j = 0; j < n - i - 1; j++)
		{
			if((strcmp(tempNode->enterprise.name, tempNode->next->enterprise.name) > 0) && (strcmp(branch, tempNode->enterprise.branch) == 0) && (strcmp(branch, tempNode->next->enterprise.branch) == 0))
			{
				swap(&tempNode, &tempNode->next);
			}
			tempNode = tempNode->next;
		}
	}
}

void deleteList(t_Node **head)
{
    t_Node* temp;

	while(*head)
    {
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
}

void printSortedNodes(t_Node **head)
{
	int i = 1, flag = 1;
	t_Node *tempNode = *head;

	if(!(*head)){
		printf("List is empty!\n");
		return;
	}
	bubbleSort(head);
	while(tempNode)
    {
		if(flag)
		{
			printf("\nBranch: %s\n", tempNode->enterprise.branch);
            bubbleSortExtra(head, tempNode->enterprise.branch);
			flag = 0;
		}
		printEnterprise(tempNode->enterprise);
		if(tempNode->next)
			if(strcmp(tempNode->enterprise.branch, tempNode->next->enterprise.branch))
				flag = 1;
		tempNode = tempNode->next;
	}
}

void deleteNodeAtPoss(t_Node **head, int poss)
{
	int i;
	t_Node *tempNode1 = (*head), *tempNode2;

	if(poss == 1)
    {
		(*head) = tempNode1->next;
		free(tempNode1);
		return;
	}
	for(i = 0; i < poss - 2; i++)
		tempNode1 = tempNode1->next;
		//temp1 pointst to (n-1)th possition;
	tempNode2 = tempNode1->next;//temp2 points to n-th poss Node;
	tempNode1->next = tempNode2->next;
	free(tempNode2);
}

void deleteEnterprises(t_Node **head)
{
    int flag = 0, poss = 1;
	double debt;
	t_Node *tempNode = *head;

    if(!(*head))
    {
		printf("List is empty!\n");
		return;
	}
	printf("Enter debt: ");
    fflush(stdin);
    scanf("%lf", &debt);
    while(tempNode)
    {
        if(tempNode->enterprise.debt >= debt)
        {
            flag = 1;
            tempNode = tempNode->next;
            deleteNodeAtPoss(head, poss);
        }else{
            poss++;
            tempNode = tempNode->next;
        }
	}
	if(!flag)
        printf("No enterprises with debt higher than %.2lf found!\n", debt);
	else
		printf("All enterprises(debt over %.2lf) deleted!\n", debt);
}

char *getFilePath()
{
    char *filePath = (char*)malloc(sizeof(char) * 50);

    printf("Enter file path: \n");
    fflush(stdin);
    gets(filePath);
    if(!strchr(filePath, '.'))
		strcat(filePath, ".bin");

    return filePath;
}

void loadFile(t_Node **head)
{
    FILE *fp;
    char *filePath;
    t_Enterprise tempEnterprise;

    filePath = getFilePath();

    if((fp = fopen(filePath, "rb")) == NULL)
    {
        printf("Error: File could not be opened!\n");
        free(filePath);
        return;
    }
    if(*head)
        deleteList(head);
    while(1)
    {
		if(fread(&tempEnterprise, sizeof(t_Enterprise), 1, fp) != 1)
			break;
		addNode(head, tempEnterprise);
        printEnterprise(tempEnterprise);
	}
    if(fclose(fp) != 0)
    {
        printf("Error: File could not be closed!\n");
        free(filePath);
        return;
    }
    if (!(*head))
		printf("No data loaded from \"%s\"\n", filePath);
	else
		printf("Info loaded successfully from \"%s\"\n", filePath);
    free(filePath);
}

void saveFile(t_Node* head)
{
	FILE* fp;
	char *filePath;

	if(!head){
		printf("List is empty!\n");
		printf("Add some new firms first!\n");
		return;
	}

	filePath = getFilePath();

    if((fp = fopen(filePath, "wb")) == NULL)
    {
        printf("Error: File could not be opened!\n");
        exit(1);
    }
	while(head)
    {
		if(fwrite(&head->enterprise, sizeof(t_Enterprise), 1, fp) != 1)
		{
			printf("Error occured while writing in file\n");
			exit(1);
		}
		head = head->next;
	}
	if(fclose(fp) != 0)
    {
        printf("Error: File could not be closed!\n");
        exit(1);
    }
	printf("Info saved successfully to \"%s\"\n", filePath);
	free(filePath);
}
