#include<bits/stdc++.h>
using namespace std;

struct node{
    int data;
    node *next;
};

node **graph;

void push(int s, int d){
    node *temp = graph[s];
    node *newnode = new node;
    newnode->data = d;
    newnode->next = NULL;
    if(temp==NULL){
        graph[s] = newnode;
        return;
    }
    while(temp->next!=NULL){
        temp = temp->next;
    }
    temp->next = newnode;
    return;
}

void pprint(int n){
    for(int i=0;i<n;i++){
        node *temp = graph[i];
        cout<<i+1;
        while(temp!=NULL){
            cout<<" -> "<<temp->data+1;
            temp = temp->next;
        }
        cout<<"\n";
    }
    return;
}

void dfs_visit(int u, int *t, int vis[], int parent[], int dis[], int leave[]){
    vis[u] = 1;
    (*t)++;
    dis[u] = *t;
    for(node *temp = graph[u]; temp != NULL;){
        if(!vis[temp->data]){
            parent[temp->data] = u;
            dfs_visit(temp->data, t, vis, parent, dis, leave);
        }
        temp = temp->next;
    }
    (*t)++;
    leave[u] = *t;
    vis[u] = 2;
    return;
}

void dfs(int n, int *t, int vis[], int parent[], int dis[], int leave[]){           // General graph
    for(int i = 0;i<n;i++){
        if(!vis[i]){
            dfs_visit(i, t, vis, parent, dis, leave);
            parent[i] = -1;
        }
    }
    return;
}


int cycle(int n){             // For directed graph
    int ans = 0;
    int vis[n] = {0};
    for(int i=0;i<n;i++){
        if(vis[i]){
            continue;;
        }
        stack<int>s;
        s.push(i);
        while(!s.empty()){
            int temp = s.top();
            s.pop();
            vis[temp] = 1;
            for(node *x = graph[temp]; x!=NULL;){
                if(!vis[x->data]){
                    s.push(x->data);
                }
                else{
                    ans++;
                }
                x = x->next;
            }
            vis[temp] = 2;
        }
    }
    return ans;
}


int main(){
    int n;                  // Number of nodes
    cin>>n;
    graph = new node*[n];
    for(int i = 0;i<n;i++){
        graph[i] = NULL;
    }
    int m;                  // Number of edges
    cin>>m;
    for(int i=0;i<m;i++){   // Adding edges
        int a,b;
        cin>>a>>b;
        push(a,b);
        // push(b,a);
    }
    pprint(n);              // Printing graph
    int vis[n] = {0};
    int parent[n];
    int dis[n];
    int leave[n];
    int t = 0;
    dfs(n,&t, vis, parent, dis, leave);  // dfs
    for(int i=0;i<n;i++){
        cout<<vis[i]<<" ";
    }
    cout<<"\n";
    for(int i=0;i<n;i++){
        cout<<parent[i]<<" ";
    }
    cout<<"\n";
    for(int i=0;i<n;i++){
        cout<<dis[i]<<" ";
    }
    cout<<"\n";
    for(int i=0;i<n;i++){
        cout<<leave[i]<<" ";
    }
    cout<<"\n";
    cout<<"Cycle count is "<<cycle(n)<<endl;
    return 0;
}