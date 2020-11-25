#include<bits/stdc++.h>
using namespace std;

struct time_slots{
    int start;
    int end;
    int index;
};

int check(struct time_slots A[], double l, int n){
    double curr = A[0].start;
    for(int i=1;i<n;i++){
        if(A[i].end < curr + l){
            return 0;
        }
        if(A[i].start >= curr + l){
            curr = A[i].start;
        }
        else{
            curr = curr + l;
        }
    }
    return 1;
}

double schedule_visits(struct time_slots A[], int n){
    double lo = 0, hi = 10000;
    for(int i=0;i<100;i++){
        double mid = (float)(lo + hi)/2.0;
        if(check(A, mid, n)){
            lo = mid;
        }
        else{
            hi = mid;
        }
    }
    return lo;
}

void swap1(time_slots *A, time_slots *B){
    time_slots *temp = A;
    B = A;
    A = temp;
    return;
}

void perma(time_slots A[], int curr, int n, int fin_order[], double *ans){
    if (curr == 1) {
        float temp_ans = schedule_visits(A, n);
        if(temp_ans > *ans){
            *ans = temp_ans;
            for(int i=0;i<n;i++){
                fin_order[i] = A[i].index;
            }
        }
        return;
    }
    for (int i = 0; i < curr; i++) {
        perma(A, curr - 1, n, fin_order, ans);
        if (curr % 2 == 1)
            swap(A[0], A[curr - 1]);
        else
            swap(A[i], A[curr - 1]);
    }
    return;
}

int main(){
    ifstream in;
    in.open("input1.txt");
    int n;
    in>>n;
    struct time_slots slots[n];
    for(int i=0;i<n;i++){
        int a, b;
        in>>a>>b;
        slots[i].start = a;
        slots[i].end = b;
        slots[i].index = i;
    }
    in.close();

    double ans = -1;
    int fin_order[n];
    perma(slots, n, n, fin_order, &ans);

    ofstream out;
    out.open("output.txt");
    
    out<<(int)ans<<":";
    int part = (ans - (int)ans)*60;
    if(part<10){
        out<<part<<"0\n";
    }
    else{
        out<<part<<"\n";
    }

    for(int i=0;i<n;i++){
        out<<fin_order[i]<<" ";
    }
    out<<"\n";

    return 0;
}