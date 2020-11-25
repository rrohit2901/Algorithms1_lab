#include<bits/stdc++.h>
using namespace std;

// Defining structure of node
struct node{
    int data;
    struct node *add;
};

// Defining function to traverse fron front to end
void traverse_from_front(node *head){
    node *prev = NULL;
    node *next = head;
    while(next!=NULL){
        cout<<next->data<<" ";
        node *temp = next;
        next = (node *)((unsigned long long)prev ^ (unsigned long long)(next->add));
        prev = temp;
    }
    cout<<"\n";
    return;
}

// Defining fuunction to traverse fron back to front
void traverse_from_end(node *tail){
    node *next = NULL;
    node *prev = tail;
    while(prev!=NULL){
        cout<<prev->data<<" ";
        node *temp = prev;
        prev = (node *)((unsigned long long)next ^ (unsigned long long)(prev->add));
        next = temp;
    }
    cout<<"\n";
    return;
}

// Function for reversing the list
void reverse(node **head, node **tail){
    node *curr_head = *head, *curr_tail = *tail;
    *head = curr_tail;
    *tail = curr_head;
    return;
}

// Function for makeing list in the alternate format
void alternate(struct node **head, struct node **tail){
    node *curr_head = *head, *curr_tail = *tail;
    node *prev_head = NULL, *prev_tail = NULL;
    node *next1 = NULL, *next2 = NULL;
    while(curr_head!=curr_tail){
        // Finding next possible node in forward and reverse direction respectively
        next1 = (node*)((unsigned long long)(curr_head->add) ^ (unsigned long long)(prev_head));
        next2 = (node*)((unsigned long long)(curr_tail->add) ^ (unsigned long long)(prev_tail));
        if(next2==curr_head){                                   // Termination condition
            break;
        }
        // Changing links in the list
        curr_head->add = (node *)((unsigned long long)(prev_head) ^ (unsigned long long)(curr_tail));
        curr_tail->add = (node *)((unsigned long long)(curr_head) ^ (unsigned long long)(next1));
        node *temp = (node *)((unsigned long long)(curr_head) ^ (unsigned long long)(next1->add));
        next1->add = (node *)((unsigned long long)(temp) ^ (unsigned long long)(curr_tail));
        temp = (node *)((unsigned long long)(curr_tail) ^ (unsigned long long)(next2->add));
        next2->add = (node *)((unsigned long long)(prev_tail) ^ (unsigned long long)(temp));
        prev_head = curr_tail;
        curr_head = next1;
        curr_tail = next2;
        prev_tail = NULL;
        // Changing the address stored in tail pointer
        *tail = next2;
    }
    return;
}

int main(){
    int n;
    cout<<"Enter number of data points :- "<<flush;
    cin>>n;
    node *head = NULL;                                                  // Declaring head of list
    node *tail = NULL;                                                  // Declaring tail of list
    node *prev = NULL;
    node *curr = new node;
    node *next = new node;
    cout<<"Enter "<<n<<" integers between -100 and 100 :- "<<flush;
    for(int i=0;i<n;i++){
        int data;
        cin>>data;                                                     // Taking input of data
        curr->data = data;
        if(head==NULL){
            head = curr;
        }
        tail = curr;
        if(i!=n-1){                                                    // Insertion of data in list  
            curr->add = (node *)((unsigned long long)prev ^ (unsigned long long)next);
            prev = curr;
            curr = next;
            next = new node;
        }
        else{
            curr->add = (node *)((unsigned long long)prev ^ (unsigned long long)NULL);
        }
    }
    cout<<"Doubly linked list traversed from front to end : "<<flush;
    traverse_from_front(head);                                                          // Printing list from front to end
    cout<<"Doubly linked list traversed from end to front : "<<flush;
    traverse_from_end(tail);                                                            // Printing list from end to front
    reverse(&head, &tail);                                                              // Revrsing the list
    cout<<"Reversed doubly linked list traversed from front to end: "<<flush;
    traverse_from_front(head);
    alternate(&head, &tail);                                                            // Alternating the list
    cout<<"Alternated doubly linked list traversed from front to end: "<<flush;
    traverse_from_front(head);
    return 0;
}