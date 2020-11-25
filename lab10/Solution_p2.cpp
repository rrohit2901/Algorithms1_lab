#include<bits/stdc++.h>
using namespace std;

struct node{
    int value;
    node *next;
};

struct hashf{
    int key;
    struct hashf* next;
    struct node **val_list;
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
        int key1 = counter_party%n;
        node *head = curr->val_list[key1];
        while(head!=NULL){
            if(head->value==counter_party){
                return;
            }
            head = head->next;
        }
        append_at_end(counter_party, &(curr->val_list[key1]));
    }
    else{
        curr->next = new hashf;
        curr = curr->next;
        curr->key = portfolio;
        curr->val_list = new node*[n];
        for(int i=0;i<n;i++){
            curr->val_list[i] = NULL;
        }
        curr->next = NULL;
        int key1 = counter_party%n;
        append_at_end(counter_party, &(curr->val_list[key1]));
    }
    
    key = counter_party%n;
    curr = &(hashf_by_counterparty[key]);
    while(curr->next!=NULL && curr->key != counter_party){
        curr = curr->next;
    }
    if(curr->key==counter_party){
        int key1 = portfolio%n;
        append_at_end(portfolio, &(curr->val_list[key1]));
    }
    else{
        curr->next = new hashf;
        curr = curr->next;
        curr->key = counter_party;
        curr->val_list = new node*[n];
        for(int i=0;i<n;i++){
            curr->val_list[i] = NULL;
        }
        curr->next = NULL;
        int key1 = portfolio%n;
        append_at_end(portfolio, &(curr->val_list[key1]));
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
    for(int i=0;i<n;i++){
        if(curr->val_list[i]==NULL){
            continue;
        }
        node *head = curr->val_list[i];
        while(head!=NULL){
            int port_num = head->value;
            int key1 = port_num%n;
            hashf *curr = hashf_by_portfolio[key1].next;
            hashf *prev = curr;
            while(curr!=NULL && curr->key != port_num){
                prev = curr;
                curr = curr->next;
            }
            int key2 = counter_party%n;
            delete_element(&(curr->val_list[key2]), counter_party);
            head = head->next;
        }
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
            continue;   
        }
        int flag = 0;
        hashf *curr = p[i].next;
        while(curr!=NULL){
            for(int j=0;j<n;j++){
                if(curr->val_list[j]==NULL){
                    continue;
                }
                node *temp = curr->val_list[j];
                while(temp!=NULL){
                    flag = 1;
                    out<<"p "<<i<<" "<<curr->key<<" "<<temp->value<<endl;
                    temp = temp->next;
                }
            }
            curr = curr->next;
        }
        if(!flag){
            out<<"p "<<i<<" -1 -1"<<endl;
            continue;
        }
    }
    for(int i=0;i<n;i++){
        if(c[i].next==NULL){
            out<<"c "<<i<<" -1 -1"<<endl;
            continue;   
        }
        int flag = 0;
        hashf *curr = c[i].next;
        while(curr!=NULL){
            for(int j=0;j<n;j++){
                if(curr->val_list[j]==NULL){
                    continue;
                }
                node *temp = curr->val_list[j];
                while(temp!=NULL){
                    flag = 1;
                    out<<"c "<<i<<" "<<curr->key<<" "<<temp->value<<endl;
                    temp = temp->next;
                }
            }
            curr = curr->next;
        }
        if(!flag){
            out<<"c "<<i<<" -1 -1"<<endl;
            continue;
        }
    }
    return 0;
}