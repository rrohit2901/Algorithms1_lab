#include<bits/stdc++.h>
using namespace std;
#define maxn 100

struct point{
    int x;
    int y;
};

int vis[maxn][maxn];
point parent[maxn][maxn];

void dfs(int **grid, int n, int curr_x, int curr_y, int fx, int fy, int curr_time){
    vis[curr_x][curr_y] = 1;
    if(curr_y+1<n && !vis[curr_x][curr_y+1] && grid[curr_x][curr_y+1]<=curr_time && grid[curr_x][curr_y]<=curr_time){
        parent[curr_x][curr_y+1] = {curr_x, curr_y};
        dfs(grid, n, curr_x, curr_y+1, fx, fy, curr_time);
    }
    if(curr_x+1<n && !vis[curr_x+1][curr_y] && grid[curr_x+1][curr_y]<=curr_time && grid[curr_x][curr_y]<=curr_time){
        parent[curr_x+1][curr_y] = {curr_x, curr_y};
        dfs(grid, n, curr_x+1, curr_y, fx, fy, curr_time);
    }
    if(curr_y>0 && !vis[curr_x][curr_y-1] && grid[curr_x][curr_y-1]<=curr_time && grid[curr_x][curr_y]<=curr_time){
        parent[curr_x][curr_y-1] = {curr_x, curr_y};
        dfs(grid, n, curr_x, curr_y-1, fx, fy, curr_time);
    }
    if(curr_x>0 && !vis[curr_x-1][curr_y] && grid[curr_x-1][curr_y]<=curr_time && grid[curr_x][curr_y]<=curr_time){
        parent[curr_x-1][curr_y] = {curr_x, curr_y};
        dfs(grid, n, curr_x-1, curr_y, fx, fy, curr_time);
    }
    return;
}

struct edge{
    point u,v;
};

void leasttimedjikstra(int **grid, int n, int sx, int sy, int fx, int fy){
    point vnear;
    int min;

    int **dist = new int*[n];
    point **touch = new point*[n];
    for(int i=0;i<n;i++){
        dist[i] = new int[n];
        touch[i] = new point[n];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==sx && j==sy)
                dist[i][j] = -1;
            else if(sx+1<n && i==sx+1 && j==sy)
                dist[i][j] = grid[i][j];
            else if(sy+1<n && i==sx && j==sy+1)
                dist[i][j] = grid[i][j];
            else if(sx-1>=0 && i==sx-1 && j==sy)
                dist[i][j] = grid[i][j];
            else if(sy>0 && i==sx && j==sy-1)
                dist[i][j] = grid[i][j];
            else
                dist[i][j] = 1e6;
            touch[i][j] = {sx, sy};
        }
    }


    for(int i=0;i<n-1;i++){
        min = 1e6;
        point min_idx;
        
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(dist[i][j]!=-1 && min>dist[i][j]){
                    min = dist[i][j+1];
                    min_idx = {i, j+1};
                    vnear = touch[i][j+1];
                }
            }
        }

        dist[min_idx.x][min_idx.y] = -1;
        parent[min_idx.x][min_idx.y] = {vnear.x, vnear.y};

        int a = min_idx.x;
        int b = min_idx.y;

        if(a+1<n && dist[a+1][b]!=-1 && dist[a+1][b]>grid[a+1][b]){
            dist[a+1][b] = grid[a+1][b];
            touch[a+1][b] = {a,b};
        }
        if(b+1<n && dist[a][b+1]!=-1 && dist[a][b+1]>grid[a][b+1]){
            dist[a][b+1] = grid[a][b+1];
            touch[a][b+1] = {a,b};
        }
        if(a>0 && dist[a-1][b]!=-1 && dist[a-1][b]>grid[a-1][b]){
            dist[a-1][b] = grid[a-1][b];
            touch[a-1][b] = {a,b};
        }
        if(b>0 && dist[a][b-1]!=-1 && dist[a][b-1]>grid[a][b-1]){
            dist[a][b-1] = grid[a][b-1];
            touch[a][b-1] = {a,b};
        }

        
    }

    return;

}

int main(){
    int n;
    cin>>n;
    int **grid = new int*[n];
    for(int i=0;i<n;i++){
        grid[i] = new int[n];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>grid[i][j];
        }
    }
    int sx, sy, fx, fy;
    cin>>sx>>sy>>fx>>fy;
    
    int lo = 0, hi = 1e6;
    int ans = 0;
    while(lo<=hi){
        int mid = (lo+hi)/2;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                vis[i][j] = 0;
            }
        }
        dfs(grid, n, sx, sy, fx, fy, mid);
        if(vis[fx][fy]){
            hi = mid-1;
            ans = mid;
        }
        else{
            lo = mid+1;
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            vis[i][j] = 0;
        }
    }
    dfs(grid, n, sx, sy, fx, fy, ans);
    // Path retracing
    int curr_x = fx, curr_y = fy;
    int fin_len = 0;
    point fin_path[n*n];
    while(curr_x!=sx || curr_y!=sy){
        fin_path[fin_len++]={curr_x, curr_y};
        point temp = parent[curr_x][curr_y];
        curr_x = temp.x;
        curr_y = temp.y;
    }
    cout<<"Minimum time taken is = "<<ans<<endl;
    cout<<"The path to reach from ("<<sx<<","<<sy<<") to ("<<fx<<","<<fy<<") is : -"<<endl;
    cout<<"("<<sx<<","<<sy<<") ";
    for(int i=fin_len-1;i>=0;i--){
        cout<<",("<<fin_path[i].x<<","<<fin_path[i].y<<") ";
    }
    cout<<"\n";
    cout<<"Length of path is = "<<fin_len+1<<endl;

    // Using djikstra

    cout<<"Solving the ps using modified djikstra :- \n";

    leasttimedjikstra(grid, n, sx, sy, fx, fy);
    curr_x = fx, curr_y = fy;
    int new_ans = 0;
    fin_len = 0;
    while(curr_x!=sx || curr_y!=sy){
        new_ans = max(new_ans, grid[curr_x][curr_y]);
        fin_path[fin_len++]={curr_x, curr_y};
        point temp = parent[curr_x][curr_y];
        curr_x = temp.x;
        curr_y = temp.y;
    }
    new_ans = max(new_ans, grid[sx][sy]);
    cout<<"Minimum time calculated from djikstra is :- "<<new_ans<<endl;
    cout<<"Printing path using djikstra: -\n";
    cout<<"("<<sx<<","<<sy<<") ";
    for(int i=fin_len-1;i>=0;i--){
        cout<<",("<<fin_path[i].x<<","<<fin_path[i].y<<") ";
    }
    cout<<"\n";
    cout<<"Length of path is = "<<fin_len+1<<endl;
    return 0;
}