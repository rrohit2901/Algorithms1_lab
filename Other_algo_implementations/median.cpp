#include<bits/stdc++.h>
using namespace std;

int median(int A[], int n, int start){
    if(n<=5){
        sort(A+start,A+start+n);
        return (A[start + ceil((n+1)/2.0)] + A[start + (n+1)/2])/2;
    }
    int len = n%5?n/5+1:n/5;
    int mids[len];
    for(int i=0;i<n;i+=5){
        int len = min(n, i+5) - i;
        int temp[len];
        loop(j,0,len){
            temp[j] = A[i+start+j];
        }
        mids[i] = median(temp, len, 0);
    }
    int pivot = median(mids, len,0);
    int i=start,j=start + n-1;
    while(i<j){
        while(i<j && A[i] <= pivot){
            i++;
        }
        while(i<j && A[j] > pivot){
            j--;
        }
        if(i<j){
            int temp = A[j];
            A[j] = A[i];
            A[i] = temp;
            i++;
            j--;
        }
    }

    if(i>=start + (n+1)/2){
        return median(A, (n+1)/2, start);
    }
    return median(A, n - i +1, start);
}

int main(){
    int n;
    cin>>n;
    int A[n];
    for(int i=0;i<n;i++){
        cin>>A[i];
    }
    int ans = median(A,n);
    cout<<ans<<endl;
    return 0;
}