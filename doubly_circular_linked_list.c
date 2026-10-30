#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    void* Object;
    Node* PreviousNode;
    Node* NextNode;
} Node;

typedef struct DoublyCircularLinkedList
{
    Node* Head;
    Node* Tail;
    int ElementCount; // New member to keep track of the number of elements
} DoublyCircularLinkedList;

void LinkedList_AddBeg(struct DoublyCircularLinkedList* list, void* object)
{
    Node* createdNode = (Node*)malloc(sizeof(Node));
    createdNode->Object = object;
    createdNode->PreviousNode = list->Tail;
    createdNode->NextNode = list->Head;
    list->Head = createdNode;

    if (list->ElementCount == 0)
    {
        list->Tail = createdNode;
        list->Tail->PreviousNode = list->Head;
        list->Tail->NextNode = list->Head;
    }
    else
        createdNode->NextNode->PreviousNode = createdNode; // Update the previous pointer of the old head

    list->ElementCount++; // Increment the element count
};

void LinkedList_AddEnd(struct DoublyCircularLinkedList* list, void* object)
{
    Node* createdNode = (Node*)malloc(sizeof(Node));
    createdNode->Object = object;
    createdNode->PreviousNode = list->Tail;
    createdNode->NextNode = list->Head;
    
    if (list->ElementCount != 0)
        list->Tail->NextNode = createdNode;

    list->Tail = createdNode;

    if (list->ElementCount == 0)
        list->Head = createdNode;
    else
        list->Head->PreviousNode = createdNode; // Update the previous pointer of

    list->ElementCount++; // Increment the element count
};

void LinkedList_Delete(struct DoublyCircularLinkedList* list, void* object)
{
    Node* currentNode = list->Head;
    int isFirstHead = 1; // Flag to check if we are at the first node
    while (isFirstHead && list->ElementCount != 0)
    {
        if (currentNode->Object == object)
        {
            if (list->Head == list->Tail) // If we are deleting the only node
            {
                free(currentNode);
            }
            else 
            {
                currentNode->PreviousNode->NextNode = currentNode->NextNode;
                currentNode->NextNode->PreviousNode = currentNode->PreviousNode;

                if (currentNode == list->Head)
                    list->Head = currentNode->NextNode; // Update head if we deleted the head
                else if (currentNode == list->Tail)
                    list->Tail = currentNode->PreviousNode; // Update tail if we deleted the tail

                free(currentNode);
            }
            list->ElementCount--; // Decrement the element count
            return; // Exit after deleting the node
        }
        currentNode = currentNode->NextNode;

        if (currentNode == list->Head) // If we have looped back to the head, break the loop
        {
            isFirstHead = 0;
        }
    }
};

Car* SearchCar(struct DoublyCircularLinkedList* list, int ModelNo)
{
    Node* currentNode = list->Head;
    int isFirstHead = 1; // Flag to check if we are at the first node
    while (isFirstHead && list->ElementCount != 0)
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

void PrintCars(struct DoublyCircularLinkedList* list)
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
    struct DoublyCircularLinkedList carList;
    struct Car mercedes;
    struct Car bmw;
    struct Car skoda;

    carList.Head = NULL;
    carList.Tail = NULL;
    carList.ElementCount = 0; // Initialize element count

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