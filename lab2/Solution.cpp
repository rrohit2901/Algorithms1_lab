// Name - Rohit Raj; Roll-19CS10049//
#include "assign2.h"
using namespace std;


// Merge sorting routing -> Merge function
void merge1(Box A[], int start, int end, int x){
    Box B[end-start+1];
    for(int i=start;i<=end;i++){
        B[i-start] = A[i];
    }
    int mid = (start+end)/2;
    int i = 0, j = mid+1-start, k = start;
    while(i<=mid-start && j<=end-start){
        if(x==1){
            if(B[i].left<=B[j].left){
                A[k++] = B[i];
                i++;
            }
            else{
                A[k++] = B[j];
                j++;
            }
        }
        else{
            if(B[i].right<=B[j].right){
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

// Merge sort main function
void m_sort(Box A[], int start, int end, int x){
    if(start==end){
        return;
    }
    int mid = (start+end)/2;
    m_sort(A, start, mid,x);
    m_sort(A, mid+1, end,x);
    merge1(A, start, end,x);
    return;
}

// Function for combining step in divide and conquer
Point* merge(Point A[], int len_a, Point B[], int len_b, int* size){
    int m_size = 2*(len_a + len_b);
    Point *ans = new Point[m_size];
    int outputsize = 0;
    int i=0, j=0;
    int h_a = 0, h_b = 0, curr_h = 0;
    // Inserting one with lower x coordinate
    while(i<len_a && j<len_b){
        if(A[i].x < B[j].x){
            h_a = A[i].y;
            curr_h = (h_a>=h_b)?h_a:h_b;
            if(outputsize>0 && ans[outputsize-1].y == curr_h){
                i++;
            }
            else if(outputsize>0 && ans[outputsize-1].x == A[i].x){
                ans[outputsize-1].y = (curr_h >=ans[outputsize-1].y)?curr_h:ans[outputsize-1].y;
                i++;
            }
            else{
                ans[outputsize].x = A[i].x;
                ans[outputsize].y = curr_h;
                outputsize++;
                i++;
            }   
        }
        else{
            h_b = B[j].y;
            curr_h = (h_a>=h_b)?h_a:h_b;
            if(outputsize>0 && ans[outputsize-1].y == curr_h){
                j++;
            }
            else if(outputsize>0 && ans[outputsize-1].x == B[j].x){
                ans[outputsize-1].y = (curr_h >=ans[outputsize-1].y)?curr_h:ans[outputsize-1].y;
                j++;
            }
            else{
                ans[outputsize].x = B[j].x;
                ans[outputsize].y = curr_h;
                outputsize++;
                j++;
            } 
        }
    }
    // Inserting remaining elements of array A
    while(i<len_a){
        h_a = A[i].y;
        if(outputsize>0 && ans[outputsize-1].y == h_a){
            i++;
        }
        else if(outputsize>0 && ans[outputsize-1].x == A[i].x){
            ans[outputsize-1].y = (h_a >=ans[outputsize-1].y)?h_a:ans[outputsize-1].y;
            i++;
        }
        else{
            ans[outputsize].x = A[i].x;
            ans[outputsize].y = h_a;
            outputsize++;
            i++;
        } 
    }
    // Inserting remaining elements of array B
    while(j<len_b){
        h_b = B[j].y;
        if(outputsize>0 && ans[outputsize-1].y == h_b){
            j++;
        }
        else if(outputsize>0 && ans[outputsize-1].x == B[j].x){
            ans[outputsize-1].y = (h_b >=ans[outputsize-1].y)?h_b:ans[outputsize-1].y;
            j++;
        }
        else{
            ans[outputsize].x = B[j].x;
            ans[outputsize].y = h_b;
            outputsize++;
            j++;
        } 
    }
    // Updating the size
    *size = outputsize;
    // Returning the required array
    return ans;
}

// Auxiliary function for division of problem into subproblems
Point *find_line(Box boxes[], int start, int end, int* outputsize){
    // Base case
    if(start==end){
        Point *ans = new Point[2];
        ans[0].x = boxes[start].left;
        ans[0].y = boxes[start].ht;
        ans[1].x = boxes[start].right;
        ans[1].y = 0;
        *outputsize = 2;
        return ans;
    }
    int mid = (start+end)/2;
    // Solving sub problems
    int s1 = 0;
    Point *ans1 = find_line(boxes, start, mid, &s1);
    int s2 = 0;
    Point *ans2 = find_line(boxes, mid+1, end, &s2);
    // Merging the sub problems
    Point *ans = merge(ans1, s1, ans2, s2, outputsize);
    ans[*outputsize-1].y = 0;
    // Return required array
    return ans;
}

Point* findOutLine(Box boxes[], int size, int* outputsize){
    Point* point_array;
    m_sort(boxes, 0, size-1, 1);
    point_array = find_line(boxes, 0, size-1, outputsize);
    return point_array;
}

int main(){
    process();
    return 0;
}