#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <list>

using namespace std;

int cache_num;
int alg;
int page_num;

int hit_num = 0;

int FIFO() {
    map<int, int> used_pages;
    queue<int> q;
    int curr;
    for(int i = 0; i < page_num; i ++) {
        cin >> curr;

        //check hit
        if(used_pages[curr] == 1) {
            hit_num ++;
//            cout << i+1 << " : hit value is " << curr << endl;
            continue;
        }

        // insert & replace
        if(q.size() == cache_num) {
            // cache is full
            int delete_page = q.front();
            q.pop();
            used_pages.erase(delete_page);
//            cout << i+1 << " : pop value is " << delete_page << endl;
        }

        used_pages[curr] = 1;
        q.push(curr);
    }

    return 0;
}

int LRU() {
    list<int> use;
    map<int, list<int>::iterator> in_cache_page_to_list_pos;

    int curr;
    for(int i = 0; i < page_num; i ++) {
        cin >> curr;

        //check hit
        if (in_cache_page_to_list_pos.find(curr) != in_cache_page_to_list_pos.end()) {
            hit_num ++;
            use.erase(in_cache_page_to_list_pos[curr]);
            continue;
        }

        // insert & replace
        if(use.size() == cache_num) {
            // cache is full
            int delete_page = use.back();
            use.pop_back();
            in_cache_page_to_list_pos.erase(delete_page);
//            cout << i+1 << " : pop value is " << delete_page << endl;
        }

        use.push_front(curr);
        in_cache_page_to_list_pos[curr] = use.begin();
    }

    return 0;
}

int min() {
    map<int, queue<int>> use;
    map<int, int> in_cache;
    int in_cache_num = 0;
    vector<int> page_list(page_num);

    int curr;
    for(int i = 0; i < page_num; i ++) {
        cin >> curr;
        page_list[i] = curr;
        use[curr].push(i + 1);
    }
    for(int i = 0; i < page_num; i ++) {
        //check hit
        curr = page_list[i];
        use[curr].pop();
        if(in_cache.count(curr) == 1) {
            hit_num ++;
//            cout << i+1 << " : hit value is " << curr << endl;
            continue;
        }

        // insert & replace
        if(in_cache_num == cache_num) {
            // cache is full, replace

            int replace_page = -1;
            int furthest_use = -1;

            map<int, int>::iterator it;
            for (it = in_cache.begin(); it != in_cache.end(); it ++) {
                int cur_page = (*it).first;
//                cout << "curr page: " << cur_page << endl;



                if (use[cur_page].empty()) {
                    replace_page = cur_page;
                    break;
                } else {

                    int cur_use = use[cur_page].front();

                    if (cur_use > furthest_use) {
                        replace_page = cur_page;
                        furthest_use = cur_use;
                    }
                }
            }

            in_cache.erase(replace_page);
            in_cache_num --;
//            cout << i+1 << " : replace value is " << replace_page << endl;
        }

        // insert
        in_cache[curr] = 1;
        in_cache_num ++;
    }



    return 0;
}

int main() {

    // read the input
    cin >> cache_num >> alg >> page_num;

//    FIFO();
//    min();
    LRU();
    printf("Hit ratio = %2.2f\%", 100*hit_num/(double)page_num);
    return 0;
}