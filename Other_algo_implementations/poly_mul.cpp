#include<bits/stdc++.h>
using namespace std;
#define loop(i,a,b) for(int i=a;i<b;i++)
#define ll long long

void poly_mul(ll A[], ll B[], ll C[], ll n){
    if(n==2){
        C[0] = A[0] * B[0];
        C[1] = A[0] * B[1] + B[0] * A[1];
        C[2] = A[1] * B[1];
        return;
    }
    ll size = n/2;
    ll flag = 0;
    if(size%2){
        size++;
        flag = 1;
    }
    ll Ah[size], Al[size], Bh[size], Bl[size];
    ll pro_h[2*size-1], pro_l[2*size-1];
    loop(i,0,n){
        if(i<n/2){
            Al[i] = A[i];
        }
        else{
            Ah[i-n/2] = A[i];
        }
    }
    loop(i,0,n){
        if(i<n/2){
            Bl[i] = B[i];
        }
        else{
            Bh[i-n/2] = B[i];
        }
    }
    if(flag){
        Ah[size-1] = 0;
        Al[size-1] = 0;
        Bh[size-1] = 0;
        Bl[size-1] = 0;
    }


    poly_mul(Ah, Bh, pro_h, size);
    poly_mul(Al, Bl, pro_l, size);


    loop(i,0,size){
        Ah[i] += Al[i];
        Bh[i] += Bl[i];
    }
    ll pro_mid[2*size-1];
    poly_mul(Ah, Bh, pro_mid, size);
    loop(i,0,2*size-1){
        pro_mid[i] -= (pro_h[i] + pro_l[i]);
    }
    loop(i,0,2*n-1){
        C[i] = 0;
        if(i<n-1){
            C[i] = pro_l[i];
        }
        else if(i>=n){
            C[i] = pro_h[i-n];
        }
        if(i>=n/2 && i<3*n/2-1){
            C[i] += pro_mid[i-n/2];
        }
    }
    return;
}

int main(){
    ll n;
    cin>>n;
    ll size = n+1;
    if(n%2==0){
        size++;
    }
    ll A[size], B[size];
    loop(i,0,n+1){
        cin>>A[i];
    }
    loop(i,0,n+1){
        cin>>B[i];
    }
    if(n%2==0){
        A[size-1] = 0;
        B[size-1] = 0;
    }
    ll C[2*n+1];
    poly_mul(A, B, C, size);
    cout<<C[0];
    loop(i,1,2*n+1){
        cout<<" + "<<C[i]<<"x^("<<i<<")";
    }
    cout<<"\n";
    return 0;
}
