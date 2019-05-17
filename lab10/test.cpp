#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

int main() {
    int start, track_num, request_num;



    cin >> start >> track_num >> request_num;
    int tmp;
    unordered_set<int> s;
    s.insert(start);
    for (int i = 1; i < request_num + 1; i ++) {
        cin>>tmp;
        s.insert(tmp);
    }

    printf("%lu\n", s.size());


}