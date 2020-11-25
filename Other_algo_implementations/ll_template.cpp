#include<bits/stdc++.h>
using namespace std;

struct node{
    char name[50];
    int roll;
    struct node *next;
};

node *create_list(){
    node *head = new node;
    return head;
}

void append_at_end(char name[], int roll, node **head_ptr){
    node *newnode = new node;
    strcpy(newnode->name, name);
    newnode->roll = roll;
    newnode->next =NULL;
    node *it = *head_ptr;
    while(it->next != NULL){
        it=it->next;
    }
    it->next =newnode;
    return;
}

void append_at_front(char name[], int roll, node **head_ptr){
    node *newnode = new node;
    strcpy(newnode->name, name);
    newnode->roll = roll;
    newnode->next =*head_ptr;
    *head_ptr = newnode;
    return;
}

void append_at_pos(char name[], int roll, node **head_ptr, int pos){
    node *newnode = new node;
    strcpy(newnode->name, name);
    newnode->roll = roll;
    int i = 1;
    node *it = *head_ptr;
    node *prev = it;
    while(i!=pos && it != NULL){
        i++;
        prev = it;
        it=it->next;
    }
    if(i!=pos){
        cout<<"Position does not exist"<<endl;
        return;
    }
    if(pos==1){
        newnode->next =*head_ptr;
        *head_ptr = newnode;
        return;
    }
    if(it->next == NULL){
        newnode->next = NULL;
        it->next = newnode;
        return;
    }
    prev->next = newnode;
    newnode->next = it;
    return;
}

void delete_from_pos(node **head_ptr, int pos){
    node *it = *head_ptr;
    node *prev = it;
    if(*head_ptr==NULL){
        cout<<"Empty list"<<endl;
        return;
    }
    if(pos==1){
        *head_ptr = it->next;
        free(it);
        return;
    }
    int i=1;
    while(i!=pos && it!=NULL){
        i++;
        prev= it;
        it=it->next;
    }   
    if(i!=pos){
        cout<<"Position does not exist"<<endl;
        return;
    }
    prev->next = it->next;
    free(it);
    return;
}

void print_list(node *head){
    node *it = head;
    while(it!=NULL){
        cout<<it->name<<" "<<it->roll<<endl;
        it=it->next;
    }
    return;
}

void swap(node **head_ptr, node *node1, node *node2){
    auto it = *head_ptr;
    if(it==node1){
        node1->next = node2->next;
        *head_ptr = node2;
        node2->next = node1;
        return;
    }
    while(it->next!=node1){
        it=it->next;
    }
    it->next = node2;
    node1->next = node2->next;
    node2->next = node1;
    return;
}

void bubble_sort(node **head_ptr){
    node *it = *head_ptr;
    while(it!=NULL){
        node *it1 = *head_ptr;
        node *nxt = it1->next;
        while(it1!=NULL){
            nxt = it1->next;
            if(nxt==NULL){
                break;
            }
            if(it1->roll > nxt->roll){
                swap(head_ptr, it1, nxt);
            }
            it1 = it1->next;
        }  
        it = it->next;
    }
    return;
}

int main(){
    int n;
    cout<<"Enter number of students :- "<<flush;
    cin>>n;
    node *head = create_list();
    for(int i=0;i<n;i++){
        char name[50];
        int roll;
        cout<<"Enter name of student "<<i+1<<" :- "<<flush;
        getchar();
        cin.getline(name,49);
        cout<<"Enter of roll of student :- "<<flush;
        cin>>roll;
        append_at_end(name, roll, &head);
    }
    delete_from_pos(&head, 1);
    print_list(head);
    bubble_sort(&head);
    print_list(head);
    return 0;
}