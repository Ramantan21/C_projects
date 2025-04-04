#include<stdio.h>

#define STACK_SIZE 10 // μεγεθος πινακα στοιβας
#define FALSE 0
#define TRUE 1

typedef int elem; //τυπος δεδομενων στοιβας

struct stack{ 
   elem array[STACK_SIZE];// πινακας στοιχειων
   int top; // κορυφη της στοιβας
};
typedef struct stack STACK; // συνωνυμο της στοιβας

void ST_init(STACK *s){
   s->top=-1;
}

int ST_empty(STACK s){
   return s.top==-1;
}


int ST_full(STACK s){
   return s.top == STACK_SIZE-1;
}
//εισαγει το χ στην στοιβα s και επιστρεεφει TRUE σε περιπτωση
//επιτυχειας και FALSE σε περιπτωση αποτυχιας
int ST_push(STACK s*,elem x){
   if(ST_full(*s))
      return FALSE;
   else
   {
      s->top++;
      s->array[s->top]=x;
      return TRUE;   
   }
}

int ST_pop(STACK *s,elem *x){
   if(ST_empty(*s)){
      return FALSE;
   }else
      {
         *x = s->array[s->top];
         s->top--;
         return TRUE;
      }
}
