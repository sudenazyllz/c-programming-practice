#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    void* Object;
    Node* NextNode;
} Node;

typedef struct LinkedList
{
    Node* Head;
    Node* Tail;
} LinkedList;

void LinkedList_AddBeg(struct LinkedList* list, void* object)
{
    Node* createdNode = (Node*)malloc(sizeof(Node));
    createdNode->Object = object;
    createdNode->NextNode = list->Head;
    list->Head = createdNode;

    if (list->Tail == NULL)
        list->Tail = createdNode;
};

void LinkedList_AddEnd(struct LinkedList* list, void* object)
{
    Node* createdNode = (Node*)malloc(sizeof(Node));
    createdNode->Object = object;
    createdNode->NextNode = NULL;
    
    if (list->Tail != NULL)
        list->Tail->NextNode = createdNode;

    list->Tail = createdNode;

    if (list->Head == NULL)
        list->Head = createdNode;
};

void LinkedList_Delete(struct LinkedList* list, void* object)
{
    Node* previousNode = NULL;
    Node* currentNode = list->Head;
    while (currentNode != NULL)
    {
        if (currentNode->Object == object)
        {
            if (previousNode != NULL)
            {
                previousNode->NextNode = currentNode->NextNode;
                free(currentNode);

                if (previousNode->NextNode == NULL)
                {
                    list->Tail = previousNode;
                }
            }
            else
            {
                list->Head = currentNode->NextNode;
                free(currentNode);

                if (list->Head == NULL)
                {
                    list->Tail = NULL;
                }
            }
        }
        previousNode = currentNode;
        currentNode = currentNode->NextNode;
    }
};

Car* SearchCar(struct LinkedList* list, int ModelNo)
{
    Node* currentNode = list->Head;
    while (currentNode != NULL)
    {
        Car* currentCar = (Car*)currentNode->Object;
        if (currentCar->Model == ModelNo)
        {
            return currentCar;
        }
        currentNode = currentNode->NextNode;   
    }
    return NULL; // TODO return (Car*) currentNode->object;
};

void PrintCars(struct LinkedList* list)
{
    // while => Car* currentCar = (Car*) currentNode->object; print currentCar->color vs.
}

typedef struct Car
{
    int ColorCode;
    int Model;
} Car;

int main(void) 
{
    struct LinkedList carList;
    struct Car mercedes;
    struct Car bmw;
    struct Car skoda;

    carList.Head = NULL;
    carList.Tail = NULL;

    mercedes.ColorCode = 0;
    mercedes.Model = 1;

    bmw.ColorCode = 3;
    bmw.Model = 5;

    skoda.ColorCode = 9;
    skoda.Model = 3;

    LinkedList_AddEnd(&carList, &mercedes);
    LinkedList_AddEnd(&carList, &bmw);
    LinkedList_AddEnd(&carList, &skoda);

    // PrintCars // mercedes -> bmw -> skoda

    LinkedList_Delete(&carList, &skoda);
    // PrintCars // mercedes -> bmw
    LinkedList_AddEnd(&carList, &skoda);
    LinkedList_Delete(&carList, &bmw);
    // PrintCars // mercedes -> skoda
    LinkedList_Delete(&carList, &mercedes);
    // PrintCars // skoda
    LinkedList_AddBeg(&carList, &bmw);
    LinkedList_AddBeg(&carList, &mercedes);
    // PrintCars // mercedes -> bmw -> skoda

    // search modelNo 5, then print specs
}