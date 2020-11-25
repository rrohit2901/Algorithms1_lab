#include<bits/stdc++.h>
#define max_size 100
using namespace std;

struct job{                                                         // Structure for jobs
    int jobId;
    int startTime;
    int jobLength;
    int remLength;
};

struct heap{                                                        // Structure for heap
    job list[max_size];
    int numjobs;
};

void initHeap(heap *H){                                             // Function for initialising heap
    H->numjobs = 0;
    return;
}

void insertJob(heap *H, job j){                                     // Function for inserting into heap
    (H->numjobs)++;
    H->list[H->numjobs] = j;
    int curr = H->numjobs;
    while(curr>1){
        if(H->list[curr].remLength < H->list[curr/2].remLength){
            job temp = H->list[curr];
            H->list[curr] = H->list[curr/2];
            H->list[curr/2] = temp;
            curr = curr/2;
        }
        else if(H->list[curr].remLength == H->list[curr/2].remLength && H->list[curr].jobId < H->list[curr/2].jobId){
            job temp = H->list[curr];
            H->list[curr] = H->list[curr/2];
            H->list[curr/2] = temp;
            curr = curr/2;
        }
        else{
            break;
        }
    }
    return;
}

job getMin(heap *H){                                            // Function for getting min element
    return H->list[1];
}

int extractMinJob(heap *H, job *j){                                // Function for removing min element from heap
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
            curr = idx;
        }
        else if(best.remLength == H->list[curr].remLength && best.jobId < H->list[curr].jobId){
            H->list[idx] = H->list[curr];
            H->list[curr] = best;
            curr = idx;
        }
        else{
            break;
        }
    }
    return 0;
}

void c_sort(job jobList[], int max_time, int n){                            // Function for counting sort
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

void scheduler(job jobList[], int n){                               // Job scheduler
    int systime = -1;
    heap pq;
    initHeap(&pq);
    int curr = 0;
    int jobs_start[n];
    for(int i=0;i<n;i++){
        jobs_start[i] = -1;
    }
    float sum = 0;
    int active = 0;
    job currjob;
    while(active || (curr!=n || pq.numjobs!=0)){
        systime++;
        while(curr<n && jobList[curr].startTime==systime){
            insertJob(&pq, jobList[curr]);
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
    cout<<"Jobs scheduled at each timestep are:"<<endl;
    scheduler(jobList, n);
    return 0;
}