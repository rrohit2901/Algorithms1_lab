#include<bits/stdc++.h>
#define max_size 100
using namespace std;

struct job{
    int jobId;
    int startTime;
    int jobLength;
    int remLength;
};

struct newheap{
    job list[max_size];
    int pos[max_size];
    int numjobs;
};

struct jobpair{
    int jobid_from;
    int jobid_to;
};

void initheap(newheap *H){
    H->numjobs = 0;
    return;
}

void insertJob(newheap *H, job j){
    (H->numjobs)++;
    H->list[H->numjobs] = j;
    H->pos[j.jobId] = H->numjobs;
    int curr = H->numjobs;
    while(curr>1){
        if(H->list[curr].remLength < H->list[curr/2].remLength){
            job temp = H->list[curr];
            H->list[curr] = H->list[curr/2];
            H->list[curr/2] = temp;
            H->pos[H->list[curr].jobId] = curr;
            H->pos[H->list[curr/2].jobId] = curr/2;
            curr = curr/2;
        }
        else if(H->list[curr].remLength == H->list[curr/2].remLength && H->list[curr].jobId < H->list[curr/2].jobId){
            job temp = H->list[curr];
            H->list[curr] = H->list[curr/2];
            H->list[curr/2] = temp;
            H->pos[H->list[curr].jobId] = curr;
            H->pos[H->list[curr/2].jobId] = curr/2;
            curr = curr/2;
        }
        else{
            break;
        }
    }
    return;
}

job getMin(newheap *H){
    return H->list[1];
}

int extractMinJob(newheap *H, job *j){
    if(H->numjobs == 0){
        return -1;
    }
    *j = H->list[1];
    job temp = H->list[1];
    H->list[1] = H->list[H->numjobs];
    H->list[H->numjobs] = temp;
    (H->numjobs)--;
    int curr = 1;
    while(2*curr <= H->numjobs){
        int idx = 2*curr;
        job best = H->list[2*curr];
        if(2*curr+1 <= H->numjobs && (best.remLength > H->list[2*curr+1].remLength || (best.remLength == H->list[2*curr+1].remLength && best.jobId > H->list[2*curr+1].jobId))){
            idx = 2*curr+1;
            best = H->list[2*curr+1];
        }
        if(best.remLength < H->list[curr].remLength){
            H->list[idx] = H->list[curr];
            H->list[curr] = best;
            H->pos[H->list[curr].jobId] = curr;
            H->pos[H->list[idx].jobId] = idx;
            curr = idx;
        }
        else if(best.remLength == H->list[curr].remLength && best.jobId < H->list[curr].jobId){
            H->list[idx] = H->list[curr];
            H->list[curr] = best;
            H->pos[H->list[curr].jobId] = curr;
            H->pos[H->list[idx].jobId] = idx;
            curr = idx;
        }
        else{
            break;
        }
    }
    return 0;
}

void c_sort(job jobList[], int max_time, int n){
    job **mat;
    mat = new job*[max_time+1];
    for(int i=0;i<=max_time;i++){
        mat[i] = new job[n];
    }
    int count[max_time+1]={0};
    for(int i=0;i<n;i++){
        count[jobList[i].startTime]++;
        mat[jobList[i].startTime][count[jobList[i].startTime]-1] = jobList[i];
    }
    int curr=0;
    for(int i=0;i<=max_time;i++){
        if(count[i]==0){
            continue;
        }
        for(int j=0;j<count[i];j++){
            jobList[curr++] = mat[i][j];
        }
    }
    return;
}

void decreaseKey(newheap *H, int jid){
    jid++;
    int curr = H->pos[jid];
    H->list[curr].remLength = (H->list[curr].remLength)/2;
    while(curr>1){
        if(H->list[curr].remLength < H->list[curr/2].remLength){
            job temp = H->list[curr];
            H->list[curr] = H->list[curr/2];
            H->list[curr/2] = temp;
            H->pos[H->list[curr].jobId] = curr;
            H->pos[H->list[curr/2].jobId] = curr/2;
            curr = curr/2;
        }
        else if(H->list[curr].remLength == H->list[curr/2].remLength && H->list[curr].jobId < H->list[curr/2].jobId){
            job temp = H->list[curr];
            H->list[curr] = H->list[curr/2];
            H->list[curr/2] = temp;
            H->pos[H->list[curr].jobId] = curr;
            H->pos[H->list[curr/2].jobId] = curr/2;
            curr = curr/2;
        }
        else{
            break;
        }
    }
    return;
}

void newScheduler(job jobList[], int n, jobpair pairList[], int m){
    int systime = -1;
    newheap pq;
    initheap(&pq);
    int curr = 0;
    int jobs_start[n];
    int pos[n];
    int dep_size[n] = {0};
    int ins[n] = {0};
    int **dependencies;
    dependencies = new int*[n];
    for(int i=0;i<n;i++){
        jobs_start[i] = -1;
        pos[jobList[i].jobId-1] = i;
        dependencies[i] = new int[n];
    }
    for(int i=0;i<m;i++){
        dependencies[pairList[i].jobid_from-1][dep_size[pairList[i].jobid_from-1]] = pairList[i].jobid_to-1;
        dep_size[pairList[i].jobid_from-1]++;
    }
    float sum = 0;
    int active = 0;
    job currjob;
    while(active || (curr!=n || pq.numjobs!=0)){
        systime++;
        while(curr<n && jobList[curr].startTime==systime){
            insertJob(&pq, jobList[curr]);
            ins[jobList[curr].jobId-1] = 1;
            curr++;
        }
        int nxt = 0;
        job nxtjob;        
        if(pq.numjobs!=0){
            nxtjob = getMin(&pq);
            nxt = 1;
        }
        if(active && nxt){
            if(nxtjob.remLength<currjob.remLength || (nxtjob.remLength==currjob.remLength && nxtjob.jobId<currjob.jobId)){
                extractMinJob(&pq, &nxtjob);
                insertJob(&pq, currjob);
                currjob = nxtjob;
            }
        }
        if(!active && nxt){
            active = 1;
            extractMinJob(&pq, &currjob);
        }
        if(active){
            cout<<currjob.jobId<<" ";
            if(jobs_start[currjob.jobId-1]==-1){
                jobs_start[currjob.jobId-1]=systime;
                sum += systime - currjob.startTime;
            }
            currjob.remLength--;
            if(currjob.remLength==0){
                active = 0;
                for(int i=0;i<dep_size[currjob.jobId-1];i++){
                    int cuid = dependencies[currjob.jobId-1][i];
                    if(!ins[cuid]){
                        jobList[pos[cuid]].remLength /= 2;
                    }
                    else if(jobs_start[cuid]==-1){
                        decreaseKey(&pq, cuid);
                    }
                }
            }
        }
        else{
            cout<<"-1 ";
        }
    } 
    cout<<"\n";
    cout<<"Average Turnaround Time is ";
    float avg = (float)sum/n;
    cout<<fixed<<setprecision(6)<<avg<<endl;
    return;
}

int main(){
    cout<<"Enter no. of jobs (n): "<<flush;
    int n;
    cin>>n;
    cout<<"Enter the jobs:\n";
    job jobList[n];
    int max_start_time = -1;
    for(int i=0;i<n;i++){
        cin>>jobList[i].jobId>>jobList[i].startTime>>jobList[i].jobLength;
        jobList[i].remLength = jobList[i].jobLength;
        max_start_time = max(max_start_time, jobList[i].startTime);
    }
    c_sort(jobList, max_start_time, n);
    int m;
    cout<<"Enter the number of dependency pairs: "<<flush;
    cin>>m;
    jobpair pairList[m];
    cout<<"Enter the dependency pairs"<<endl;
    for(int i=0;i<m;i++){
        cin>>pairList[i].jobid_from>>pairList[i].jobid_to;
    }
    cout<<"Jobs scheduled at each timestep are:"<<endl;
    newScheduler(jobList, n, pairList, m);
    return 0;
}