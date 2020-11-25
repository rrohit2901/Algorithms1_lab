#include<bits/stdc++.h>
using namespace std;

struct node{
    int value;
    node *next;
};

struct hashf{
    int key;
    struct hashf* next;
    struct node *val_list;
};

void append_at_end(int value, node **head_ptr){
    node *newnode = new node;
    newnode->value = value;
    newnode->next =NULL;
    if(*head_ptr == NULL){
        *head_ptr = newnode;
        return;
    }
    node *it = *head_ptr;
    while(it->next != NULL){
        it=it->next;
    }
    it->next = newnode;
    return;
}

void delete_element(node **head_ptr, int num){
    node *it = *head_ptr;
    node *prev = it;
    if(*head_ptr==NULL){
        cout<<"Empty list"<<endl;
        return;
    }
    if(it->value == num){
        *head_ptr = it->next;
        free(it);
        return;
    }
    while(it->value != num){
        prev = it;
        it = it->next;
    }
    prev->next = it->next;
    free(it);
    return;
}

void insert(hashf hashf_by_portfolio[], hashf hashf_by_counterparty[], int counter_party, int portfolio, int n){
    int key = portfolio%n;
    hashf *curr = &(hashf_by_portfolio[key]);
    while(curr->next!=NULL && curr->key != portfolio){
        curr = curr->next;
    }
    if(curr->key==portfolio){
        node *head = curr->val_list;
        while(head!=NULL){
            if(head->value==counter_party){
                return;
            }
            head = head->next;
        }
        append_at_end(counter_party, &(curr->val_list));
    }
    else{
        curr->next = new hashf;
        curr = curr->next;
        curr->key = portfolio;
        curr->val_list = NULL;
        curr->next = NULL;
        append_at_end(counter_party, &(curr->val_list));
    }
    
    key = counter_party%n;
    curr = &(hashf_by_counterparty[key]);
    while(curr->next!=NULL && curr->key != counter_party){
        curr = curr->next;
    }
    if(curr->key==counter_party){
        append_at_end(portfolio, &(curr->val_list));
    }
    else{
        curr->next = new hashf;
        curr = curr->next;
        curr->key = counter_party;
        curr->val_list = NULL;
        curr->next = NULL;
        append_at_end(portfolio, &(curr->val_list));
    }
    return;
}

void remove(hashf hashf_by_portfolio[], hashf hashf_by_counterparty[], int counter_party, int n){
    int key = counter_party%n;
    hashf *curr = hashf_by_counterparty[key].next;
    hashf *prev = curr;
    while(curr!=NULL && curr->key != counter_party){
        prev = curr;
        curr = curr->next;
    }
    node *temp = curr->val_list;
    while(temp!=NULL){
        int key1 = (temp->value)%n;
        int port_num = temp->value;
        hashf *curr = &(hashf_by_portfolio[key1]);
        hashf *prev = curr;
        while(curr->key != port_num){
            prev = curr;
            curr = curr->next;
        }
        delete_element(&(curr->val_list), counter_party);
        if(curr->val_list == NULL){
            if(prev==curr){
                hashf_by_counterparty[key].next = curr->next;
            }
            else{
                prev->next = curr->next;
            }
            free(curr);
        }
        temp = temp->next;
    }
    if(prev==curr){
        hashf_by_counterparty[key].next = curr->next;
    }
    else{
        prev->next = curr->next;
    }
    free(curr);
    return;
}

int main(){
    ifstream in;
    in.open("input.txt");
    int n;
    in>>n;
    int t;
    in>>t;
    hashf p[n];
    hashf c[n];
    for(int i=0;i<n;i++){
        p[i].next = NULL;
        p[i].key = -1;
        c[i].next = NULL;
        c[i].key = -1;
    }
    for(int i=0;i<t;i++){
        char a;
        in>>a;
        if(a=='+'){
            int x,y;
            in>>x>>y;
            insert(p, c, x, y, n);
        }
        else{
            int x;
            in>>x;
            remove(p, c, x, n);
        }
    }
    in.close();
    ofstream out;
    out.open("Output.txt");
    for(int i=0;i<n;i++){
        if(p[i].next==NULL){
            out<<"p "<<i<<" -1 -1"<<endl;
        }
        else{
            hashf *curr = p[i].next;
            while(curr!=NULL){
                node *temp = curr->val_list;
                while(temp!=NULL){
                    out<<"p "<<i<<" "<<curr->key<<" "<<temp->value<<endl;
                    temp = temp->next;
                }
                curr = curr->next;
            }
        }
    }
    for(int i=0;i<n;i++){
        if(c[i].next==NULL){
            out<<"c "<<i<<" -1 -1"<<endl;
        }
        else{
            hashf *curr = c[i].next;
            while(curr!=NULL){
                node *temp = curr->val_list;
                while(temp!=NULL){
                    out<<"c "<<i<<" "<<curr->key<<" "<<temp->value<<endl;
                    temp = temp->next;
                }
                curr = curr->next;
            }
        }
    }
    return 0;
}