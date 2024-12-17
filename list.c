#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int value;
    struct ListNode *next;
} * List;

//1 is empty:grami15
//2 insert:grammi 30
//3 print:grammi 37
//4 lenght:grammi 45
//5 find:grammi 53
//6 delete:grammi 60

/*int is_empty(List list){
    return list == NULL;
}

int main(){
  struct ListNode node= {42,NULL};

  List list1 = &node;
  List list2 = NULL;
  printf("Is empty: %d\n", is_empty(list1));
  printf("is empty: %d\n", is_empty(list2));
  return 0;
}*/

void insert(List *list, int value){
    List current_head = *list;
    List new_head = malloc(sizeof(struct ListNode));
    new_head->value = value;
    new_head->next = current_head;
    *list = new_head;
}
void print(List list){
    printf("list: ");
    while(list){
        printf("-> %d",list->value);
        list = list->next;
    }
    printf("-> NULL\n");
}
int lenght(List list){
    int counter = 0;
    while(list){
        counter++;
        list = list->next;
    }
    return counter;
}

List find(List list, int value){
    while(list && list->value != value){
        list = list->next;
    }
    return list;
}
List delete(List *list,int value){
    List temp;
    while(*list && (*list)->value != value){
        list = &((*list)->next);//bres to shmeio
    }
    if(*list){
        temp=*list;
        *list = temp->next;
        free(temp);
    }
}



int main(){
    List list = NULL;
    insert(&list,42); insert(&list,43); insert(&list,44); insert(&list,45); insert(&list,55);
    lenght(list);
    printf("Lenght is: %d\n",lenght(list));
    printf("Found 43: %x\n", find(list,43));
    printf("found 34: %x\n",find(list,34));
    delete(&list,44);
    print(list);

    return 0;

}