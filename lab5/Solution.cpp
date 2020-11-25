#include<bits/stdc++.h>
using namespace std;

/*

Definition of sub problem used: -
    dp[i][j] = Success probability when only i catalysts are present and only j reactions are present

Recursive relation used: -
    dp[i][j] = max(a=1 to min(i,c))(dp[i][j], dp[i-a][j-1] * e[j-1][a-1]);

Final answer: -
    ans = dp[c][n];

Here, base cases are: -
    if(i==0){
        dp[i][j] = 0;
    }
    if(j==0){
        dp[i][j] = 1;
    }
    if(i<j){
        dp[i][j] = 0; for all j
        (As there is atleast one reaction whose probability of success is 0)
    }

*/

int main(){
    // Input file stream for reading input
    ifstream in;
    in.open("input.txt");
    int n,c;
    in>>n>>c;
    double e[10][30];
    for(int i=0;i<n;i++){
        for(int j=0;j<c;j++){
            in>>e[i][j];
        }
    }
    in.close();

    // Array for stroing value of sub problems
    double dp[31][11] = {0};
    // Array for storing value required for traversals
    int par[31][11];
    // DP part
    for(int i=0;i<=c;i++){
        for(int j=0;j<=n;j++){
            // Base cases
            if(j==0){
                dp[i][j] = 1;
                continue;
            }
            if(i==0){
                dp[i][j] = 0;
                continue;
            }
            if(i<j){
                dp[i][j] = 0;
                continue;
            }

            dp[i][j] = 0;
            for(int a = 1;a<=min(i,c);a++){
                if(dp[i-a][j-1] * e[j-1][a-1] > dp[i][j]){
                    dp[i][j] = dp[i-a][j-1] * e[j-1][a-1];
                    par[i][j] = a;
                }
            }
        }
    }
    // Writing output
    ofstream out;
    out.open("output.txt");
    double ans = dp[c][n];
    out<<"The maximum probability of success is = "<<ans<<endl;
    // Path retracing
    int reacn[n];
    int cat = c;
    for(int i=n;i>0;i--){
        reacn[i-1] = par[cat][i];
        cat -= par[cat][i];
    }
    for(int i=0;i<n;i++){
        out<<"Reaction "<<i+1<<" : "<<reacn[i]<<endl;
    }
    out.close();
    return 0;
}