#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

int start;
int track_num;
int request_num;
vector<int> requests;



void FCFS() {
    long long unsigned int result = 0;
    int curr_req;
    int last_req = start;
    printf("FCFS\n");

    for (int i = 0; i < request_num + 1; i ++) {
        curr_req = requests[i];
        result += abs(curr_req - last_req);
        printf("%d", curr_req);
        if (i != request_num ) {
            printf(" -> ");
        } else {
            printf("\n");
        }
        last_req = curr_req;
    }
    printf("%llu\n", result);
}

void SSTF() {
    int next_track;
    int curr_track = start;

    int curr_dist;


    long long unsigned int result = 0;
    unordered_set<int> visited;

    printf("SSTF\n");

    

    for (int i = 0; i < request_num; i ++) {
        if(i != 0)
            visited.insert(curr_track);
        printf("%d", curr_track);
        int min_dist = track_num;
        for (int j = 1; j < request_num + 1; j ++) {
            if (visited.find(requests[j]) == visited.end() && (curr_dist = abs(requests[j] - curr_track)) < min_dist) {
                next_track = requests[j];
                min_dist = curr_dist;
            }
        }

        printf(" -> ");

        result += min_dist;

        curr_track = next_track;
    }
    printf("%d\n", curr_track);

    printf("%llu\n", result);
}

void SCAN() {
    printf("SCAN\n");

    vector<int> tmp(requests);
    sort(tmp.begin(), tmp.end());
    long long unsigned int result = 0;
    int start_pos = 0;
    for ( int i = 0; i < request_num + 1; i ++) {
        if(tmp[i] == start) {
            start_pos = i;
        }
    }

    int curr;
    int last =  tmp[start_pos];

    for ( int i = start_pos; i > 0; i --) {
        curr = tmp[i];
        printf("%d -> ", tmp[i]);
        result += abs(curr - last);
        last = curr;
    }

    printf("%d", tmp[0]);

    if (start_pos == request_num) {
        curr = tmp[0];
        result += abs(curr - last);
        printf("\n%llu\n", result);
        return;
    }



    result += abs(0 - curr);


    if(tmp[0] != 0) {
        printf(" -> %d", 0);
    }

    last = 0;

    for ( int i = start_pos + 1; i < request_num + 1; i ++) {
        printf(" -> %d", tmp[i]);
        curr = tmp[i];
        result += abs(curr - last);
        last = curr;
    }

    printf("\n%llu\n", result);
}


void C_SCAN() {
    printf("C-SCAN\n");

    vector<int> tmp(requests);
    sort(tmp.begin(), tmp.end());
    long long unsigned int result = 0;
    int start_pos = 0;
    for (int i = 0; i < request_num + 1; i ++) {
        if(tmp[i] == start) {
            start_pos = i;
        }
    }

    int curr;
    int last =  tmp[start_pos];

    for ( int i = start_pos; i > 0; i --) {
        curr = tmp[i];
        printf("%d -> ", tmp[i]);
        result += abs(curr - last);
        last = curr;
    }

    printf("%d", tmp[0]);
    if (start_pos == request_num) {
        curr = tmp[0];
        result += abs(curr - last);
        printf("\n%llu\n", result);
        return;
    }


    result += abs(0 - curr);


    if(tmp[0] != 0) {
        printf(" -> %d", 0);
    }

    last = track_num - 1;

    if(tmp[request_num] != track_num - 1) {
        printf(" -> %d", track_num - 1);
    }

    for ( int i = request_num; i > start_pos; i --) {
        printf(" -> %d", tmp[i]);
        curr = tmp[i];
        result += abs(curr - last);
        last = curr;
    }

    printf("\n%llu\n", result);
}

void LOOK() {
    printf("LOOK\n");

    vector<int> tmp(requests);
    sort(tmp.begin(), tmp.end());
    long long unsigned int result = 0;
    int start_pos = 0;
    for (int i = 0; i < request_num + 1; i ++) {
        if(tmp[i] == start) {
            start_pos = i;
        }
    }

    int curr;
    int last =  tmp[start_pos];

    for ( int i = start_pos; i > 0; i --) {
        curr = tmp[i];
        printf("%d -> ", tmp[i]);
        result += abs(curr - last);
        last = curr;
    }

    printf("%d", tmp[0]);
    curr = tmp[0];
    result += abs(curr - last);
    last = curr;

    for ( int i = start_pos + 1; i < request_num + 1; i ++) {
        printf(" -> %d", tmp[i]);
        curr = tmp[i];
        result += abs(curr - last);
        last = curr;
    }

    printf("\n%llu\n", result);
}

void C_LOOK() {
    printf("C-LOOK\n");

    vector<int> tmp(requests);
    sort(tmp.begin(), tmp.end());
    long long unsigned int result = 0;
    int start_pos = 0;
    for (int i = 0; i < request_num + 1; i ++) {
        if(tmp[i] == start) {
            start_pos = i;
        }
    }

    int curr;
    int last =  tmp[start_pos];

    for ( int i = start_pos; i > 0; i --) {
        curr = tmp[i];
        printf("%d -> ", tmp[i]);
        result += abs(curr - last);
        last = curr;
    }

    printf("%d", tmp[0]);
    curr = tmp[0];
    result += abs(curr - last);
    last = tmp[request_num];

    for ( int i = request_num; i > start_pos; i --) {
        printf(" -> %d", tmp[i]);
        curr = tmp[i];
        result += abs(curr - last);
        last = curr;
    }

    printf("\n%llu\n", result);
}


int main() {
    cin >> start >> track_num >> request_num;
    requests.resize(request_num + 1);
    requests[0] = start;
    for (int i = 1; i < request_num + 1; i ++) {
       scanf("%d", &requests[i]);
    }

    FCFS();
    SSTF();
    SCAN();
    C_SCAN();
    LOOK();
    C_LOOK();


}