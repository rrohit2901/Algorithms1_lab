#include<bits/stdc++.h>
using namespace std;

// O(n) space and O(nlogn) time merge
void merge(int A[], int start, int end){
    int B[end-start+1];
    for(int i=start;i<=end;i++){
        B[i-start] = A[i];
    }
    int mid = (start+end)/2;
    int i = 0, j = mid+1-start, k = start;
    while(i<=mid-start && j<=end-start){
        if(B[i]<=B[j]){
            A[k++] = B[i];
            i++;
        }
        else{
            A[k++] = B[j];
            j++;
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

void m_sort(int A[], int start, int end){
    if(start==end){
        return;
    }
    int mid = (start+end)/2;
    m_sort(A, start, mid);
    m_sort(A, mid+1, end);
    merge(A, start, end);
    return;
}

// Quick sort
void q_sort(int A[], int start, int end){
    if(start >= end){
        return;
    }
    int pivot = start;
    int i = start, j = end;
    while(i<=j){
        while(i<=j && A[i]<=A[pivot]){
            i++;
        }
        while(i<=j && A[j]>A[pivot]){
            j--;
        }
        if(i<=j){
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    int temp = A[j];
    A[j] = A[pivot];
    A[pivot] = temp;
    q_sort(A, start, j-1);
    q_sort(A, i, end);
    return;
}


int main(){
    int n;
    cin>>n;
    int A[n];
    for(int i=0;i<n;i++){
        cin>>A[i];
    }
    q_sort(A, 0,n-1);
    for(int i=0;i<n;i++){
        cout<<A[i]<<" ";
    }
    cout<<"\n";
    return 0;
}