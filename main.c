#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Student {
    char *surname;
    char *name;
    char *sex;
    int age;
    int group;
    float mathMark;
    float physicsMark;
    float chemistryMark;
    void (*infoOutput)(void*);
};

struct Student* initstudent(char* surname, char* name, char* sex, int age, int group, float mathMark, float physickMark, float chemistryMark);
void infoOutput(void* student);
void push_stack(void* arg);
void* pop_stack(void* stack);


struct Node {
    struct Student data;
    struct Node* next;
};

struct Stack {
    struct Node* head;
    unsigned long int size;
};

struct Stack* init() {
    struct Stack* res = malloc(sizeof(struct Stack));
    res->head = NULL;
    res->size = 0;
    return res;
}
void addTwoToMarks(struct student* student) {
    struct Student* s = (struct Student*)student;
    s->mathMark += 2.0;
    s->physicsMark += 2.0;
    s->chemistryMark += 2.0;
}




int main() {
    struct Student* one = initstudent("Polyakova", "Olga", "f", 17, 207, 5.0, 4.0, 5.0);
    struct Student* two = initstudent("Dremuhina", "Anastsia", "f", 18, 208, 5.0, 5.0, 3.0);
    struct Student* three = initstudent("Adamov", "Adam", "m", 16, 209, 5.0, 5.0, 5.0);

    struct Stack* students = init();
    struct {
        struct Stack* stack;
        void* elem;
    } args;

    args.stack = students;
    args.elem = one;
    push_stack(&args);

    args.elem = two;
    push_stack(&args);

    args.elem = three;
    push_stack(&args);

    while (students->size > 0) {
        struct Student* q = (struct Student*)pop_stack(students);
        addTwoToMarks(q);
        if (q->mathMark >= 4.0 && q->chemistryMark >= 4.0 && q->physicsMark >= 4.0) {
            q->infoOutput(q);
            free(q);
        }
    }

    return 0;
}

void infoOutput(void* student) {
    struct Student* s = (struct Student*)student;
    printf("Surname: %s\n", s->surname);
    printf("Name: %s\n", s->name);
    printf("Gender %s\n", s->sex);
    printf("Age: %d\n", s->age);
    printf("Group: %d\n", s->group);
    printf("Math mark: %f\n", s->mathMark);
    printf("Phystcs mark: %f\n", s->physicsMark);
    printf("Chemistry mark: %f\n", s->chemistryMark);
}

struct Student* initstudent(char* surname, char* name, char* sex, int age, int group, float mathMark, float physickMark, float chemistryMark) {
    struct Student* result = malloc(sizeof(struct Student));
    result->surname = surname;
    result->name = name;
    result->sex = sex;
    result->age = age;
    result->group = group;
    result->mathMark = mathMark;
    result->physicsMark = physickMark;
    result->chemistryMark = chemistryMark;
    result->infoOutput = infoOutput;
    return result;
}
void push_stack(void* arg) {
    struct {
        struct Stack* stack;
        void* elem;
    } *args = arg;

    struct Node* new_head = malloc(sizeof(struct Node));
    new_head->data = *((struct Student*)args->elem);
    new_head->next = args->stack->head;
    args->stack->head = new_head;
    args->stack->size += 1;
}

void* pop_stack(void* stack) {
    struct Stack* s = (struct Stack*)stack;
    if (s->size == 0) {
        return NULL;
    }
    struct Node* elem = s->head;
    struct Student* result = malloc(sizeof(struct Student));
    *result = s->head->data;
    s->head = s->head->next;
    s->size -= 1;
    free(elem);
    return result;
}
