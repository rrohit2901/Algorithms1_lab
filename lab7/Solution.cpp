#include<bits/stdc++.h>
using namespace std;

typedef struct _node{                                       // Declaring structure of DSU
    int rank = 0;
    _node *parent;
}node;

node*** makeset(int n,int m){                               // Function of making DSU
    node ***addr = new node**[n];
    for(int i=0;i<n;i++){
        addr[i] = new node*[m];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            addr[i][j] = new node;
            addr[i][j]->rank = 0;
            addr[i][j]->parent = addr[i][j];
        }
    }
    return addr;
}

node* findset(node *curr){                              // Finding root of tree whose current is part of.
    node *temp = curr;
    while(temp->parent != temp){
        temp = temp->parent;
    }
    node *z = curr;
    while(z->parent != z){                            // Implementing path compression
        node *w = z;
        z = z->parent;
        w->parent = temp;
    }
    return temp;
}

void mergeset(node *a, node *b){                    // Function for merging two trees with differenct roots
    node* t1 = findset(a);
    node* t2 = findset(b);
    if(t1==t2){
        return;
    }
    if(t1->rank < t2->rank){                        // Union by rank 
        t1->parent = t2;
    }
    else if(t2->rank < t1->rank){
        t2->parent = t1;
    }
    else{
        t2->parent = t1;
        (t1->rank)++;
    }
    return;
}

int isconnected(node ***addr, int n, int m){            // Function for checking if the complete matrix is connected
    node* p = findset(addr[0][0]);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(findset(addr[i][j])!=p){
                return 0;
            }
        }
    }
    return 1;
}

void findtreasure(node ***addr, int n, int m, int **horiz, int **vert){             // Function for making all vertices connected
    while(!isconnected(addr,n,m)){
        int ch1 = rand()%2;
        if(ch1==0 && m!=1){                                                                 // Vertical edge removal
            int i1 = rand()%n;
            int j1 = rand()%(m-1);
            if(vert[i1][j1]){
                continue;
            }
            int x1 = i1;
            int x2 = i1;
            int y1 = j1;
            int y2 = j1+1;
            if(findset(addr[x1][y1])==findset(addr[x2][y2])){
                vert[i1][j1]=-1;
                continue;
            }
            else{
                mergeset(addr[x1][y1], addr[x2][y2]);
                vert[i1][j1] = 1;
            }
        }
        else if(ch1==1 && n!=1){                                                                 // Horizontal edge removal
            int i1 = rand()%(n-1);
            int j1 = rand()%(m);
            if(horiz[i1][j1]){
                continue;
            }
            int x1 = i1;
            int x2 = i1+1;
            int y1 = j1;
            int y2 = j1;
            if(findset(addr[x1][y1])==findset(addr[x2][y2])){
                horiz[i1][j1] = -1;
                continue;
            }
            else{
                horiz[i1][j1] = 1;
                mergeset(addr[x1][y1], addr[x2][y2]);
            }
        }
    }
    return;
}

void printgrid(int **horiz, int **vert, int n, int m, int cond){                    // Function for printing grid

    // Here cond is type of printing to be done
    // cond==0 means printing initial state grid
    // cond==1 means printing final state grid

    if(cond==0){    
        for(int i=0;i<n+1;i++){
            for(int j=0;j<m;j++){
                if(i==0 && j==0){
                    cout<<"+   ";
                    continue;
                }
                cout<<"+---";
            }
            cout<<"+"<<endl;
            int j=0;
            if(i==n){
                continue;
            }
            for(j=0;j<m;j++){
                cout<<"|   ";
            }
            if(i==n-1 && j==m){
                cout<<"\n";
                continue;
            }
            cout<<"|"<<endl;
        }
    }
    else{
        for(int i=0;i<n+1;i++){
            for(int j=0;j<m;j++){
                if(i==0 && j==0){
                    cout<<"+   ";
                    continue;
                }
                if(i>0 && i<n && horiz[i-1][j]==1){
                    cout<<"+   ";
                    continue;
                }
                cout<<"+---";
            }
            cout<<"+"<<endl;
            int j=0;
            if(i==n){
                continue;
            }
            for(j=0;j<m;j++){
                if(i<n && j>0 && vert[i][j-1]==1){
                    cout<<"    ";
                    continue;
                }
                cout<<"|   ";
            }
            if(i==n-1 && j==m){
                cout<<"\n";
                continue;
            }
            cout<<"|"<<endl;
        }
    }
    return;
}

int main(int argc, char *argv[]){
    srand((unsigned  int)time(NULL));
    int n,m;
    if(argc==1){                                                        // Processing input from command line
        cout<<"NO INPUT GIVEN...Taking default case."<<endl;
        n=10;
        m=10;
    }
    else if(argc==3){
        n=atoi(argv[1]);
        m=atoi(argv[2]);
    }
    cout<<n<<" "<<m<<endl;
    node ***addr = makeset(n,m);
    int** horiz = new int*[n-1];
    int** vert = new int*[n];
    for(int i=0;i<n-1;i++){
        horiz[i] = new int[m];
    }
    for(int i=0;i<n && m>1;i++){
        vert[i] = new int[m-1];
    }
    for(int i=0;i<n-1;i++){
        for(int j=0;j<m;j++){
            horiz[i][j] = 0;
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m-1;j++){
            vert[i][j] = 0;
        }
    }
    findtreasure(addr, n, m, horiz, vert);
    node *p1 = findset(addr[0][0]);
    node *p2 = findset(addr[n-1][m-1]);
    if(p1==p2){
        cout<<"The final chamber can be reached from the start chamber."<<endl;
    }
    else{
        cout<<"The final chamber can not be reached from the start chamber."<<endl;
    }    
    cout<<"Initial Grid"<<endl;
    printgrid(horiz, vert, n, m, 0);
    cout<<"\n";
    cout<<"Final Grid"<<endl;
    printgrid(horiz, vert, n, m, 1);
    cout<<"\n";
    return 0;
}