#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    void* Object;
    Node* PreviousNode;
    Node* NextNode;
} Node;

typedef struct DoublyLinkedList
{
    Node* Head;
    Node* Tail;
} DoublyLinkedList;

void LinkedList_AddBeg(struct DoublyLinkedList* list, void* object)
{
    Node* createdNode = (Node*)malloc(sizeof(Node));
    createdNode->Object = object;
    createdNode->PreviousNode = NULL;
    createdNode->NextNode = list->Head;
    list->Head = createdNode;
    
    if (list->Tail == NULL) // tek elemanli durumu
        list->Tail = createdNode;
    else
        createdNode->NextNode->PreviousNode = createdNode; // Update the previous pointer of the old head
};

void LinkedList_AddEnd(struct DoublyLinkedList* list, void* object)
{
    Node* createdNode = (Node*)malloc(sizeof(Node));
    createdNode->Object = object;
    createdNode->PreviousNode = list->Tail;
    createdNode->NextNode = NULL;
    
    if (list->Tail != NULL)
        list->Tail->NextNode = createdNode;

    list->Tail = createdNode;

    if (list->Head == NULL)
        list->Head = createdNode;
};

void LinkedList_Delete(struct DoublyLinkedList* list, void* object)
{
    Node* currentNode = list->Head;
    while (currentNode != NULL)
    {
        if (currentNode->Object == object)
        {
            if (currentNode->PreviousNode != NULL)
            {
                currentNode->PreviousNode->NextNode = currentNode->NextNode;

                if (currentNode->NextNode != NULL)
                    currentNode->NextNode->PreviousNode = currentNode->PreviousNode;
                else
                    list->Tail = currentNode->PreviousNode; // Update tail if we deleted the last node

                free(currentNode);
            }
            else
            {
                list->Head = currentNode->NextNode;
                free(currentNode);

                if (currentNode->NextNode != NULL)
                    currentNode->NextNode->PreviousNode = NULL;
                else
                    list->Tail = NULL; // Update tail if we deleted the only node
            }
        }
        currentNode = currentNode->NextNode;
    }
};

Car* SearchCar(struct DoublyLinkedList* list, int ModelNo)
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

void PrintCars(struct DoublyLinkedList* list)
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
    struct DoublyLinkedList carList;
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