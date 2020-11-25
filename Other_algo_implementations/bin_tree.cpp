// BST implementation
#include<bits/stdc++.h>
using namespace std;

struct node{
    int data;
    node* parent;
    node *left;
    node *right;
};

void insert(int data, node **root){
    node *newnode = new node;
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    if(*root == NULL){
        *root = newnode;
        newnode->parent = NULL;
    }
    node *temp = *root;
    while(1){
        if(temp->data==data){
            break;
        }
        if(temp->data > data){
            if(temp->left == NULL){
                temp->left = newnode;
                newnode->parent = temp;
                break;
            }
            else{
                temp = temp->left;
            }
        }
        else{
            if(temp->right == NULL){
                temp->right = newnode;
                newnode->parent = temp;
                break;
            }
            else{
                temp = temp->right;
            }
        }
    }
    return;
}

node *search(int data, node *root){
    while(1){
        if(root->data==data){
            return root;
        }
        if(root->data > data && root->left!=NULL){
            root = root->left;
        }
        else if(root->data < data && root->right!=NULL){
            root = root->right;
        }
        else{
            return NULL;
        }
    }
}

void inorder(node *root){
    if(root==NULL){
        return;
    }
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}

node *find_max(node *root){
    while(root->right != NULL){
        root = root->right;
    }
    return root;
}

node *find_min(node *root){
    while(root->left!=NULL){
        root = root->left;
    }
    return root;
}

node *find_suc(int data, node *root){
    node *temp = search(data,root);
    if(temp==NULL){
        return NULL;
    }
    if(temp == find_max(root)){
        return NULL;
    }
    if(temp->right != NULL){
        temp = temp->right;
        return find_min(temp);
    }
    else{
        while(temp != (temp->parent)->left){
            temp = temp->parent;
        }
        temp = temp->parent;
        return temp;
    }
}

node *find_pre(int data, node *root){
    node *temp = search(data,root);
    if(temp==NULL){
        return NULL;
    }
    if(temp == find_min(root)){
        return NULL;
    }
    if(temp->left != NULL){
        temp = temp->left;
        return find_max(temp);
    }
    else{
        while(temp != (temp->parent)->right){
            temp = temp->parent;
        }
        temp = temp->parent;
        return temp;
    }
}

void del(int data, node **root){
    node *temp = search(data,*root);
    if(temp==NULL){
        return;
    }
    if(temp==*root){
        if(temp->left==NULL && temp->right==NULL){
            free(temp);
            *root = NULL;
            return;
        }
        else if(temp->left==NULL || temp->right==NULL){
            if(temp->left==NULL){
                *root = temp->right;
                free(temp);
            }
            else{
                *root = temp->left;
                free(temp);
            }
            return;
        }
        else{
            node *t1 = find_suc(data, *root);
            int data1 = t1->data;
            t1->data = temp->data;
            temp->data = data1;
            temp = t1;
        }
    }
    while(1){
        if(temp->left==NULL && temp->right==NULL){
            if(temp == (temp->parent)->left){
                (temp->parent)->left = NULL;
                return;
            }
            if(temp == (temp->parent)->right){
                (temp->parent)->right = NULL;
                return;
            }
        }
        else if(temp->left==NULL || temp->right==NULL){
            if(temp->left==NULL){
                if(temp == (temp->parent)->left){
                    (temp->parent)->left = temp->right;
                    (temp->right)->parent = temp->parent;
                    free(temp);
                }
                else{
                    (temp->parent)->right = temp->right;
                    (temp->right)->parent = temp->parent;
                    free(temp);
                }
            }
            else{
                if(temp == (temp->parent)->left){
                    (temp->parent)->left = temp->left;
                    (temp->left)->parent = temp->parent;
                    free(temp);
                }
                else{
                    (temp->parent)->right = temp->left;
                    (temp->left)->parent = temp->parent;
                    free(temp);
                }
            }
            return;
        }
        else{
            node *t1 = find_suc(data, *root);
            int data1 = t1->data;
            t1->data = temp->data;
            temp->data = data1;
            temp = t1;
        }
    }
    return;
}

int main(){
    int n;
    cin>>n;
    node *root = NULL;
    for(int i=0;i<n;i++){
        int a;
        cin>>a;
        insert(a, &root);
    }
    inorder(root);
    cout<<"\n";
    int q;
    cin>>q;
    for(int i=0;i<q;i++){
        int a;
        cin>>a;
        del(a, &root);
        inorder(root);
        cout<<"\n";
    }
    return 0;
}