#include<bits/stdc++.h>
#define row 200
#define col 200
#define MAX_QUEUE_SIZE 80000

using namespace std;


void print_grid(char grid[][200], int n, int m){
    cout<<"Grid of stones is:\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout<<grid[i][j];
        }
        cout<<"\n";
    }
    return;
}

// Queue implementation
struct POINT{
    int x,y;
};

struct QUEUE{
    POINT *Arr;
    int start_id, end_id;
    int queue_size;
};

void init(QUEUE *qP, int size){
    qP->queue_size = size;
    qP->start_id = -1;
    qP->end_id = -1;
    qP->Arr = new POINT[size];
    return;
}

int isempty(QUEUE qP){
    if(qP.end_id == -1 || qP.start_id == -1 || qP.start_id > qP.end_id){
        return 1;
    }
    return 0;
}

POINT dequeue(QUEUE *qP){
    if(isempty(*qP)){
        cout<<"Can not pop from empty stack"<<endl;
        exit(0);
    }
    POINT ans = qP->Arr[qP->start_id];
    (qP->start_id)++;
    if(qP->end_id < qP->start_id){
        qP->start_id = -1;
        qP->end_id = -1;
    }
    return ans;
}

void enqueue(QUEUE *qP, POINT p){
    if(qP->start_id==-1){
        qP->start_id = 0;
    }
    qP->end_id++;
    qP->Arr[qP->end_id] = p;
    return;
}

// Queue implementation ends

// Strategy 1 implementation

int strategy1(char grid[][200], int n, int m, int jx, int jy, int fx, int fy){
    QUEUE qP;
    init(&qP, MAX_QUEUE_SIZE);
    int vis[row][col] = {0};
    POINT curr;
    curr.x = jx;
    curr.y = jy;
    enqueue(&qP, curr);
    vis[curr.x][curr.y] = 1;
    while(!isempty(qP)){
        POINT curr = dequeue(&qP);
        if(curr.x>0 && vis[curr.x-1][curr.y]==0 && grid[curr.x-1][curr.y]=='*'){
            POINT temp = curr;
            temp.x--;
            enqueue(&qP, temp);
            vis[temp.x][temp.y] = 1;
        }
        if(curr.y>0 && vis[curr.x][curr.y-1]==0 && grid[curr.x][curr.y-1]=='*'){
            POINT temp = curr;
            temp.y--;
            enqueue(&qP, temp);
            vis[temp.x][temp.y] = 1;
        }
        if(curr.x<n && vis[curr.x+1][curr.y]==0 && grid[curr.x+1][curr.y]=='*'){
            POINT temp = curr;
            temp.x++;
            enqueue(&qP, temp);
            vis[temp.x][temp.y] = 1;
        }
        if(curr.y<m && vis[curr.x][curr.y+1]==0 && grid[curr.x][curr.y+1]=='*'){
            POINT temp = curr;
            temp.y++;
            enqueue(&qP, temp);
            vis[temp.x][temp.y] = 1;
        }
    }
    if(vis[fx][fy]){
        return 1;
    }
    else{
        return 0;
    }
}

// Strategy 1 implementation 
// stack implementation begins

struct STACK{
    POINT head;
    STACK *next;
};

void init(STACK *s){
    s->next = NULL;
    return;
}

int isempty(STACK s){
    if(s.next==NULL){
        return 1;
    }
    return 0;
}

void push(STACK *s, POINT p){
    STACK *newnode = new STACK;
    newnode->next = s;
    newnode->head = p;
    s->next = newnode;
    return;
}

POINT pop(STACK *s){
    if((s)->next == NULL){
        cout<<"STACK IS EMPTY"<<endl;
        exit(0);
    }
    STACK *prev = s;
    s = s->next;
    prev->next = NULL;
    return (prev->head);
}

// Stack implementation end
// Strategy2 implementation

void Strategy2(char grid[][200], int n, int m, int jx, int jy, int fx, int fy){
    STACK s;
    init(&s);
    int vis[row][col] = {0};
    POINT parent[row][col];
    POINT curr;
    curr.x = jx;
    curr.y = jy;
    push(&s, curr);
    parent[jx][jy].x = -1;
    parent[jx][jy].y = -1;
    vis[jx][jy] = 1;
    while(!isempty(s)){
        POINT curr = pop(&s);
        if(curr.x==fx && curr.y==fy){
            break;
        }
        if(curr.x>0 && vis[curr.x-1][curr.y]==0 && grid[curr.x-1][curr.y]=='*'){
            POINT temp = curr;
            temp.x--;
            push(&s, temp);
            vis[temp.x][temp.y] = 1;
            parent[temp.x][temp.y] = curr;
        }
        if(curr.y>0 && vis[curr.x][curr.y-1]==0 && grid[curr.x][curr.y-1]=='*'){
            POINT temp = curr;
            temp.y--;
            push(&s, temp);
            vis[temp.x][temp.y] = 1;
            parent[temp.x][temp.y] = curr;
        }
        if(curr.x<n && vis[curr.x+1][curr.y]==0 && grid[curr.x+1][curr.y]=='*'){
            POINT temp = curr;
            temp.x++;
            push(&s, temp);
            vis[temp.x][temp.y] = 1;
            parent[temp.x][temp.y] = curr;
        }
        if(curr.y<m && vis[curr.x][curr.y+1]==0 && grid[curr.x][curr.y+1]=='*'){
            POINT temp = curr;
            temp.y++;
            push(&s, temp);
            vis[temp.x][temp.y] = 1;
            parent[temp.x][temp.y] = curr;
        }
    }
    STACK s2;
    init(&s2);
    curr.x = fx;
    curr.y = fy;
    while(curr.x!=-1 && curr.y!=-1){
        push(&s2, curr);
        curr = parent[curr.x][curr.y];
    }
    POINT temp = pop(&s2);
    cout<<"("<<temp.x<<", "<<temp.y<<")";
    while(!isempty(s2)){
        temp = pop(&s2);
        cout<<", ("<<temp.x<<", "<<temp.y<<")";
    }
    cout<<"\n";
    return;
}

int main(){
    int n,m,k;
    cin>>n>>m>>k;
    char grid[row][col];
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            grid[i][j] = '*';
        }
    }
    int ux[k],uy[k];
    for(int i=0;i<k;i++){
        cin>>ux[i];
    }
    for(int i=0;i<k;i++){
        cin>>uy[i];
    }
    int jx,jy,fx,fy;
    cin>>jx>>jy>>fx>>fy;
    for(int i=0;i<k;i++){
        grid[ux[i]][uy[i]] = '-';
    }
    print_grid(grid, n, m);
    int ex = strategy1(grid, n,m,jx,jy,fx,fy);
    if(ex){
        cout<<"Path Exists"<<endl;
        Strategy2(grid,  n,m,jx,jy,fx,fy);
    }
    else{
        cout<<"No Path Exists"<<endl;
    }
    return 0;
}