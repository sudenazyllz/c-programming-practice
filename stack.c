#include <stdio.h>
#include <stdlib.h>

typedef struct Stack
{
    void** Elements;
    int Capacity;
    int ElementCount; // New member to keep track of the number of elements
} Stack;

typedef struct Car
{
    int ColorCode;
    int Model;
} Car;

void Stack_Push(struct Stack* stack, void* object)
{
    // Check if the stack is full
    if (stack->ElementCount == stack->Capacity)
    {
        printf("Stack is full. Cannot push new element.\n");
        return;
    }

    // Add the new element to the top of the stack
    stack->Elements[stack->ElementCount] = object;
    stack->ElementCount++; // Increment the element count
}

void* Stack_Pop(struct Stack* stack)
{
    // Check if the stack is empty
    if (stack->ElementCount == 0)
    {
        printf("Stack is empty. Cannot pop element.\n");
        return NULL;
    }

    // Remove the top element from the stack
    stack->ElementCount--; // Decrement the element count
    return stack->Elements[stack->ElementCount];
}

void Stack_Print_Car(struct Stack* stack)
{
    printf("Stack elements (from top to bottom):\n");
    for (int i = stack->ElementCount - 1; i >= 0; i--)
    {
        Car* currentCar = (Car*)stack->Elements[i];
        printf("Car Model: %d, Color Code: %d\n", currentCar->Model, currentCar->ColorCode);
    }
}

int main()
{
    struct Stack stack;
    struct Car mercedes;
    struct Car bmw;
    struct Car skoda;

    stack.Capacity = 10;
    stack.Elements = (void**)malloc(stack.Capacity * sizeof(void*));
    stack.ElementCount = 0; // Initialize element count

    mercedes.ColorCode = 0;
    mercedes.Model = 1;

    bmw.ColorCode = 3;
    bmw.Model = 5;

    skoda.ColorCode = 9;
    skoda.Model = 3;

    stack.Push(&stack, &mercedes);
    stack.Push(&stack, &bmw);
    stack.Push(&stack, &skoda);

    Stack_Print_Car(&stack);
    struct Car* poppedCar = (struct Car*)stack.Pop(&stack);
    if (poppedCar != NULL)
    {
        printf("Popped Car Model: %d, Color Code: %d\n", poppedCar->Model, poppedCar->ColorCode);
    }

    return 0;
}
