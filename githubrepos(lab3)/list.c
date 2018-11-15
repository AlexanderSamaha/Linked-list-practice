/* Code created by Alexander Samaha
started: Nov. 2nd, 2018 | Last edit: Nov. 13, 2018
for:
McMaster University 2S03 Principles of Programming.
Assignment 3.

Written in C.

This program takes a header file detailing a linked list structure.
Goal is to take the structure and create a linked list with each
node linking to a linked list with random size based upon initial
conditions specified in a main function.
Then it takes the list elements and "flattens" it into a singly
linked list in ascending order of key values.
It prints both structures and then frees them from memory to ensure
no leaks.
*/

#include "assignment3.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*definitions*/
#define N 8000
static SLnodePtr HBnodeFlatten(HBnodePtr headHB, SLnodePtr headSL, SLnodePtr P);
static SLnodePtr SLnodeFlatten(SLnodePtr vList, SLnodePtr headSL, SLnodePtr P);
static SLnodePtr SLnodeInsert(SLnodePtr vList, SLnodePtr headSL, SLnodePtr P);
static int cmpfunc(const void *a, const void *b);
static void sortList(int n, int array[]);
static HBnodePtr createHBnode(HBnodePtr J, int n, int array[], int m, int b[]);
static SLnodePtr createSLnode(SLnodePtr S, HBnodePtr L, int m, int array[]);
static SLnodePtr nodeCreater(int m);

/*function creates a linked list of nodes with each node containing a
single linked list attached*/

HBnodePtr createHBlist(int n, int m) {
  srand(time(NULL));
  int a[N], b[N];
  sortList(n, a);
  // sortList (m, b);
  HBnodePtr head = NULL;

  head = createHBnode(head, n - 1, a, m, b);
  // vHead = createSLnode(vHead, m-1, b)

  return head;
}

/*This flatten list takes an HBlist and sorts all keys in ascending order
in a singly linked list.*/
SLnodePtr flattenList(const HBnodePtr L) {
  HBnodePtr headHB = L;
  SLnodePtr headSL;

  SLnodePtr P = nodeCreater(headHB->key);

  headSL = P;
  while (headHB != NULL) {

    HBnodeFlatten(headHB, headSL, P);
    headHB = headHB->next;
  }
  headSL = P;
  P = P->next;
  free(headSL);
  return P;
}
/*Takes an HBnode with its list children and sorts it into our final singly
linked list.*/
static SLnodePtr HBnodeFlatten(HBnodePtr headHB, SLnodePtr headSL,
                               SLnodePtr P) {
  SLnodePtr tempNode;
  SLnodePtr vList = headHB->bottom;

  if (headSL->next == NULL) {

    headSL->next = nodeCreater(headHB->key);
    SLnodeFlatten(vList, headSL = P, P);
    return headSL;

  } else if (headHB->key <= headSL->next->key) {
    tempNode = nodeCreater(headHB->key);

    tempNode->next = headSL->next;
    headSL->next = tempNode;
    SLnodeFlatten(vList, headSL = P, P);
    return headSL;
  }
  HBnodeFlatten(headHB, headSL->next, P);
}
/*takes a singly linked list and its nodes, returns the pointer to sorted final
linked list*/
static SLnodePtr SLnodeFlatten(SLnodePtr vList, SLnodePtr headSL, SLnodePtr P) {

  while (vList != NULL) {

    headSL = headSL->next;
    SLnodeInsert(vList, headSL, P);

    vList = vList->next;
  }

  return headSL;
}
/*takes an individual node and checks to see where it fits into the final single
 * linked list.*/
static SLnodePtr SLnodeInsert(SLnodePtr vList, SLnodePtr headSL, SLnodePtr P) {
  SLnodePtr tempNode;

  if (headSL->next == NULL) {
    headSL->next = nodeCreater(vList->key);
    return headSL;

  } else if (vList->key <= headSL->next->key) {
    tempNode = nodeCreater(vList->key);
    tempNode->next = headSL->next;
    headSL->next = tempNode;
    return headSL;
  }
  SLnodeInsert(vList, headSL->next, P);
}

/*this is needed for the built in qsort function in stdlib*/
static int cmpfunc(const void *a, const void *b) {
  return (*(int *)a - *(int *)b);
}

/*function will take an array and number of elements required,
returns a sorted array*/
static void sortList(int n, int array[]) {

  int i = 0;

  for (i = 0; i < n; i++) {
    array[i] = rand() % 100 + 1;
  }

  qsort(array, n, sizeof(int), cmpfunc);

  return;
}

/*function will create nodes for a single linked list recursively*/
static HBnodePtr createHBnode(HBnodePtr J, int n, int array[], int m, int b[]) {
  if (n >= 0) {
    int randM;
    HBnodePtr child = malloc(sizeof(struct HBnode));
    child->key = array[n];
    child->next = J;
    J = child;
    SLnodePtr vHead = NULL;
    randM = rand() % (m + 1 - 0) - 0;
    sortList(m + 1, b);
    vHead = createSLnode(vHead, J, randM, b);

    J = createHBnode(J, n - 1, array, m, b);
  }
  return J;
}

/*Function creates a SLnode recursively to be added to a single HBnode*/
static SLnodePtr createSLnode(SLnodePtr S, HBnodePtr L, int m, int array[]) {
  if (m <= 0) {
    return S;
  } else if (m > 0) {
    SLnodePtr childV = malloc(sizeof(struct SLnode));
    L->bottom = childV;
    childV->key = (L->key + array[m]);
    childV->next = S;
    S = childV;

    createSLnode(S, L, m - 1, array);
    return S;
  }
}

/*This function takes an HBlist and frees all nodes within, including the
 * vertical lists*/
void freeHBlist(HBnodePtr P) {
  HBnodePtr current = P;
  HBnodePtr nextHBnode;

  while (current != NULL) {
    nextHBnode = current->next;
    freeSLlist(current->bottom);
    free(current);
    current = nextHBnode;
  }
  P = NULL;
}

/*Will delete all nodes in a single linked list*/
void freeSLlist(SLnodePtr P) {
  SLnodePtr current = P;
  SLnodePtr nextSLnode;

  while (current != NULL) {
    nextSLnode = current->next;
    free(current);
    current = nextSLnode;
  }
  P = NULL;
}
/*function prints the horizontal nodes recursively and initiates printing
of the vertical list attached to each horizontal node*/
void printHBlist(const HBnodePtr L) {
  if (!L) {
    return;
  }
  printf("%d -> ", L->key);

  printSLlist(L->bottom);

  printHBlist(L->next);
}
/*Function takes in a standard single linked list and prints all elements*/
void printSLlist(const SLnodePtr L) {
  if (!L) {
    printf("\n");
    return;
  }

  printf("%d ", L->key);
  printSLlist(L->next);
}

static SLnodePtr nodeCreater(int m) {
  SLnodePtr node = malloc(sizeof(struct SLnode));
  node->key = m;
  node->next = NULL;
  return node;
}