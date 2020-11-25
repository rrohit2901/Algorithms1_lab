#include<bits/stdc++.h>
using namespace std;
#define loop(i,a,b) for(int i=a;i<b;i++)
#define ll long long

struct point{
    int x;
    int y;
};

struct p_point{
    point a,b;
    double dis;
};

void merge(point A[], int start, int end, int x){
    point B[end-start+1];
    for(int i=start;i<=end;i++){
        B[i-start] = A[i];
    }
    int mid = (start+end)/2;
    int i = 0, j = mid+1-start, k = start;
    while(i<=mid-start && j<=end-start){
        if(x==1){
            if(B[i].x<=B[j].x){
                A[k++] = B[i];
                i++;
            }
            else{
                A[k++] = B[j];
                j++;
            }
        }
        else{
            if(B[i].y<=B[j].y){
                A[k++] = B[i];
                i++;
            }
            else{
                A[k++] = B[j];
                j++;
            }
        }
    }
    while(i<=mid-start){
        A[k++] = B[i++];
    }
    while(j<=end-start){
        A[k++] = B[j++];
    }
    return;
}

void m_sort(point A[], int start, int end, int x){
    if(start==end){
        return;
    }
    int mid = (start+end)/2;
    m_sort(A, start, mid,x);
    m_sort(A, mid+1, end,x);
    merge(A, start, end,x);
    return;
}

p_point find_closest(point p[], ll start, ll end){
    // Base case
    if(end-start+1 < 5){
        p_point ans;
        ans.dis = 5000;
        for(int i=start;i<end+1;i++){
            for(int j=start;j<end+1;j++){
                if(i==j){
                    continue;
                }
                double dis1 = sqrt((p[i].x-p[j].x)*(p[i].x-p[j].x) + (p[i].y-p[j].y)*(p[i].y-p[j].y));
                if(dis1 < ans.dis){
                    ans.a = p[i];
                    ans.b = p[j];
                    ans.dis = dis1;
                }
            }
        }
        return ans;
    }
    // Divide
    int mid = (start+end)/2;
    p_point a1 = find_closest(p, start, mid);
    p_point a2 = find_closest(p, mid+1, end);
    // Merge
    double d = min(a1.dis, a2.dis);
    int x = p[mid].x;
    point strip[end-start+1];
    ll len = 0;
    for(int i=start;i<end+1;i++){
        if(p[i].x >= x-d && p[i].x <= x+d){
            strip[len++] = p[i];
        }
    }
    p_point ans = a1;
    if(a2.dis < ans.dis){
        ans = a2;
    }
    m_sort(strip,0,len-1,0);
    for(int i=0;i<len;i++){
        for(int j=i+1;j<len && p[j].y - p[i].y <d;j++){
            double dis1 = sqrt((p[i].x-p[j].x)*(p[i].x-p[j].x) + (p[i].y-p[j].y)*(p[i].y-p[j].y));
            if(dis1 < ans.dis){
                ans.dis = dis1;
                ans.a = p[i];
                ans.b = p[j];
            }
        }
    }
    return ans;
}

int main(){
    ll n;
    cin>>n;
    point p[n];
    loop(i,0,n){
        cin>>p[i].x>>p[i].y;
    }
    m_sort(p, 0, n-1,1);
    p_point ans = find_closest(p,0,n-1);
    cout<<ans.dis<<endl;
    cout<<ans.a.x<<" "<<ans.a.y<<endl;
    cout<<ans.b.x<<" "<<ans.b.y<<endl;
    return 0;
}