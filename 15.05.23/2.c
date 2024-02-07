/*

фамилия: 10 букв, однофамильцев нет
номер группы
оценки пол за последнюю сессию: три экзамена

1. все данные занести в бинарное дерево: ключь — фамилия
2. сначала напечатать тех, кто круглые отличники
3. затем круглые двоишники
4. 

*/

#include <stdio.h>
#include <string.h>  
#include <stdlib.h>


typedef struct nodes
{
    char* data;
    int group;
    int* grades;
    struct nodes *left;
    struct nodes *right;
}branch;


typedef struct tree
{
    branch *root;
}Tree;

typedef struct cel
{
    branch *node;
    struct cel *next;
}cell;

typedef struct stacks
{
    cell *root;
}stack;


void makenullTree(branch *t)
{
    if (t == NULL)
    {
        free(t);
        return;
    }
    else
    {
        makenullTree(t -> left);
        makenullTree(t -> right);
    }
}


Tree *createTree()
{
    Tree *t;
    t = (Tree*) malloc(sizeof(Tree));

    t -> root = NULL;
    return t;
}

void grow(branch *b, branch *d)
{
    printf("added: %s\n", d -> data);
    int comp = strcmp(b -> data, d -> data);

    if (comp == 0)
    {
        free(d);
        return;
    }
    else if (comp < 0)
    {
        if (b -> left != NULL)
        {
            grow(b -> left, d);
        }
        else
        {
            b -> left = d;
        }
    }
    else if (comp > 0)
    {
        if (b -> right != NULL)
        {
            grow(b -> right, d);
        }
        else
        {
            b -> right = d;
        }
    }
}

void add(Tree *t, branch *d)
{
    if (t -> root == NULL)
    {
        t -> root = d;
    }
    else
    {
        grow(t -> root, d);
    }
}


void printInner(branch *b) //внутренний обход
{
    if (b -> left != NULL)
    {
        printInner(b -> left);
    }
    puts(b -> data);
    if (b -> right != NULL)
    {
        printInner(b -> right);
    }
}


void printTree(Tree *F)
{
    printInner(F -> root);
}




// char getInner(branch *b) //внутренний обход
// {
//     if (b -> left != NULL)
//     {
//         return getInner(b -> left);
//     }
//     return (b -> data);
//     if (b -> right != NULL)
//     {
//         return getInner(b -> right);
//     }
// }

// char getTree(Tree *F)
// {
//     return getInner(F -> root);
// }

// void makenullStack(cell *s)
// {
//     if (s == NULL)
//     {
//         free(s);
//         return;
//     }
//     else
//     {
//         makenullStack(s -> next);
//     }
// }

// stack *createStack()
// {
//     stack *s;
//     s = (stack*)malloc(sizeof(stack));

//     s -> root = NULL;
//     return s;
// }

// void push(stack *s, branch *a)
// {
//     cell *c;
//     c = (cell*)malloc(sizeof(cell));
//     c -> node = a;
//     c -> next = s -> root;

//     s -> root = c;
//     return;
// }

// void pop(stack *s)
// {
//     if (s == NULL)
//     {
//         printf("Stack already empty\n");
//         return;
//     }
//     else
//     {
//         cell* temp;

//         temp = s -> root;
//         s -> root = s -> root -> next;
//         free(temp);
//         return;
//     }
// }

// int top(stack *s)
// {
//     return s -> root -> node -> data;
// }

// int isEmpty(stack *s)
// {
//     if (s == NULL) return 1;
//     else return 0;
// }

// int size(stack *s)
// {
//     int counter = 0;

//     cell *runner = s -> root;

//     while (runner != NULL)
//     {
//         counter++;
//         runner = runner -> next;
//     }
//     return counter;
// }

// void printStack(stack *s)
// {
//     cell *runner = s -> root;

//     while (runner != NULL)
//     {
//         printf("%c\t", runner -> node -> data);
//         runner = runner -> next;
//     }
//     printf("\n");
//     return;
// }

int main()
{
    Tree *students = createTree();

    FILE *in = fopen("/Users/danielgehrman/Documents/Programming/Uni/Sem-1-NSU/15.05.23/input.txt", "r");

    char last[10];
    char temp[10];
    int g, grds[3];

    branch* b;

    while (!feof(in))
    {
        fscanf(in, "%s%d%d%d%d", last, &g, &grds[0], &grds[1], &grds[2]);

        b = (branch*)malloc(sizeof(branch));
        b -> data = (char*)malloc(sizeof(last));
        b -> data = last;

        b -> group = g;

        b -> grades =(int*)malloc(sizeof(grds));
        b -> grades = grds;

        b -> left = NULL;
        b -> right = NULL;

        add(students, b);
    }
    
    fclose(in);

    printTree(students);

    printf("%s\n %d  %d", students -> root -> data);

    printf("done\n");

    makenullTree(students -> root);
    free(students);

    return 0;
}