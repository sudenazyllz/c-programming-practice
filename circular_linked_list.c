#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    void* Object;
    Node* NextNode;
} Node;

typedef struct CircularLinkedList
{
    Node* Head;
    Node* Tail;
} CircularLinkedList;

void LinkedList_AddBeg(struct CircularLinkedList* list, void* object)
{
    Node* createdNode = (Node*)malloc(sizeof(Node));
    createdNode->Object = object;
    createdNode->NextNode = list->Head;
    list->Head = createdNode;

    if (list->Tail == NULL)
    {
        list->Tail = createdNode;
        list->Tail->NextNode = list->Head;
    }
};

void LinkedList_AddEnd(struct CircularLinkedList* list, void* object)
{
    Node* createdNode = (Node*)malloc(sizeof(Node));
    createdNode->Object = object;
    createdNode->NextNode = list->Head;
    
    if (list->Tail != NULL)
        list->Tail->NextNode = createdNode;

    list->Tail = createdNode;

    if (list->Head == NULL)
        list->Head = createdNode;
};

void LinkedList_Delete(struct CircularLinkedList* list, void* object)
{
    Node* previousNode = list->Tail;
    Node* currentNode = list->Head;
    int isFirstHead = 1; // Flag to check if we are at the first node
    while (isFirstHead && currentNode != NULL)
    {
        if (currentNode->Object == object)
        {
            if (previousNode != list->Tail)
            {
                previousNode->NextNode = currentNode->NextNode;
                free(currentNode);

                if (previousNode->NextNode == list->Head) // If we deleted the tail, update the tail
                {
                    list->Tail = previousNode;
                }
            }
            else
            {
                list->Head = currentNode->NextNode;
                free(currentNode);

                if (list->Head == list->Tail) // If we deleted the only node, update the tail
                {
                    list->Head = NULL;
                    list->Tail = NULL;
                }
            }
        }
        previousNode = currentNode;
        currentNode = currentNode->NextNode;

        if (currentNode == list->Head) // If we have looped back to the head, break the loop
        {
            isFirstHead = 0;
        }
    }
};

Car* SearchCar(struct CircularLinkedList* list, int ModelNo)
{
    Node* currentNode = list->Head;
    int isFirstHead = 1; // Flag to check if we are at the first node
    while (isFirstHead && currentNode != NULL)
    {
        Car* currentCar = (Car*)currentNode->Object;
        if (currentCar->Model == ModelNo)
        {
            return currentCar;
        }
        currentNode = currentNode->NextNode;   
        if (currentNode == list->Head) // If we have looped back to the head, break the loop
        {
            isFirstHead = 0;
        }
    }
    return NULL;
};

void PrintCars(struct CircularLinkedList* list)
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
    struct CircularLinkedList carList;
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