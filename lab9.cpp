#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <list>

using namespace std;

int cache_size;
int alg;
int page_num;

int hit_num = 0;


struct CircularNode {
    int valid;
    int data;
    CircularNode *next;
};

struct CircularNode* hand = NULL;

CircularNode* init_circle_list (int length) {

//    struct CircularNode* head;
    struct CircularNode* curr;
    struct CircularNode* next;

    struct CircularNode* head = new CircularNode();
    head->valid= 0;
    head->data = -1;
    head->next = NULL;

    hand = head;
    curr = head;
    CircularNode* tmp;
    for (int i = 1; i < length; i ++) {
         tmp = new CircularNode();
        tmp->valid = 0;
        tmp->data = -1;
        tmp->next = NULL;

        curr->next = tmp;
        curr = curr->next;
    }

    curr->next = head;

}

void display() {
    struct CircularNode* ptr;
    ptr = hand;
    cout << "circle list: ";
    do {
        cout<<ptr->data <<" (" << ptr->valid << ") ";
        ptr = ptr->next;
    } while(ptr != hand);
    cout << endl;
}



int clock() {

    init_circle_list(cache_size);
    map<int, CircularNode*> in_cache_page;
    int curr;
    for(int i = 0; i < page_num; i ++) {
        cin >> curr;

        //check hit
        if (in_cache_page.find(curr) != in_cache_page.end()) {
            hit_num ++;
            in_cache_page[curr]->valid = 1;
        }
        // miss : insert & replace
        else {

            // find fist valid = 0
            struct CircularNode* ptr;
            int replace_page;
            ptr = hand;
            do {
                if (ptr->valid == 0) {
                    ptr->valid = 1;
                    replace_page = ptr->data;
                    ptr->data = curr;
                    hand = ptr->next;
                    break;
                } else {
                    ptr->valid = 0;
                }
                ptr = ptr->next;
            } while(1);
            if (replace_page != -1) {
                in_cache_page.erase(replace_page);
//                cout << i+1 << " : replace value is " << replace_page << endl;
            }
            in_cache_page[curr] = ptr;


        }
//        cout << i+1 << " : ";
//        display();
    }

    return 0;
}







int FIFO() {
    map<int, int> used_pages;
    queue<int> q;
    int curr;
    for(int i = 0; i < page_num; i ++) {
        cin >> curr;

        //check hit
        if(used_pages.find(curr) != used_pages.end()) {
            hit_num ++;
//            cout << i+1 << " : hit value is " << curr << endl;
            continue;
        }

        // insert & replace
        if(q.size() == cache_size) {
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

        }
        // insert & replace
        else if(use.size() == cache_size) {
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

int second_chance() {
    int FIFO_zise = cache_size / 2;
    int LRU_zise = cache_size - FIFO_zise;

    list<int> LRU_list;
    map<int, list<int>::iterator> in_LRU_to_list_pos;
    map<int, int> in_FIFO;
    queue<int> q;

    int curr;
    for(int i = 0; i < page_num; i ++) {
        cin >> curr;

        //check hit
        // hit in FIFO
        if (in_FIFO.find(curr) != in_FIFO.end()) {
            hit_num ++;
            continue;
        }
        // hit in LRU
        else if (in_LRU_to_list_pos.find(curr) != in_LRU_to_list_pos.end()) {
            hit_num ++;

            // remove from LRU list
            LRU_list.erase(in_LRU_to_list_pos[curr]);
            in_LRU_to_list_pos.erase(curr);

//            // put it into FIFO list
//            in_FIFO[curr] = 1;
//            q.push(curr);
//
//            // remove the front from FIFO queue
//            int FIFO_delete_page = q.front();
//            q.pop();
//            in_FIFO.erase(FIFO_delete_page);
//
//            // put the FIFO delete page into LRU list
//
//
//
//
//            LRU_list.push_front(curr);
//            in_LRU_to_list_pos[curr] = LRU_list.begin();
//            continue;
        }

        // miss: insert & replace
        // first add to FIFO queue
        if(q.size() < FIFO_zise) {
            // cache is not full
            in_FIFO[curr] = 1;
            q.push(curr);
        } else {
            // queue is full
            // first remove from FIFO list
            int FIFO_delete_page = q.front();
            q.pop();
            in_FIFO.erase(FIFO_delete_page);

            // push the new page into FIFO list
            in_FIFO[curr] = 1;
            q.push(curr);

            // push the FIFO delete page into LRU list
            // check if LRU list is full
            if (LRU_list.size() == LRU_zise) {
                // if full, remove the LRU page
                int LRU_delete_page = LRU_list.back();
                LRU_list.pop_back();
                in_LRU_to_list_pos.erase(LRU_delete_page);
            }
            // add the FIFO delete page
            LRU_list.push_front(FIFO_delete_page);
            in_LRU_to_list_pos[FIFO_delete_page] = LRU_list.begin();


//            cout << i+1 << " : pop value is " << FIFO_delete_page << endl;
        }
//        printf("");
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
        if(in_cache_num == cache_size) {
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
    cin >> cache_size >> alg >> page_num;

//    FIFO();
//    min();
//    LRU();
//    clock();
    second_chance();
    printf("Hit ratio = %2.2f\%", 100*hit_num/(double)page_num);

    return 0;
}