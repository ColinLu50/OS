#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;


map<int, vector<int>> Max;
map<int, vector<int>> Need;
map<int, bool> finished;
vector<int> available_resources;
vector<int> max_resources;
int resource_kind_num;

bool banker(int pid, const vector<int> req)
{
    bool found = true;

    vector<int> available_resources_tmp(available_resources);
    // available_resources_tmp = ;
    map<int, vector<int>> Need_tmp(Need);
    // cout << "current resources: ";
    // for(int i = 0; i < resource_kind_num; i ++)
    // {
    //     cout << available_resources_tmp[i] << " ";
    // }
    // cout << endl;
    for(int i = 0; i < resource_kind_num; i ++)
    {
        
        available_resources_tmp[i] -= req[i];
        if(available_resources_tmp[i] < 0)
        {
            return false;
        }
        Need_tmp[pid][i] -= req[i];
    }

    // cout << "current resources after req:  ";
    // for(int i = 0; i < resource_kind_num; i ++)
    // {
    //     cout << available_resources_tmp[i] << " ";
    // }
    // cout << endl;
    
    
    while(found)
    {
        found = false;
        for(map<int, vector<int>>::iterator need_itr = Need_tmp.begin(); need_itr != Need_tmp.end(); need_itr ++)
        {
            int curr_pid = need_itr->first;
            bool this_process = true;
            if(!finished[curr_pid])
            {
                vector<int> curr_need = need_itr->second;
                // check if this process can be run 
                for(int i = 0; i < resource_kind_num; i ++)
                {
                    if(curr_need[i] > available_resources_tmp[i])
                    {
                        this_process = false;
                        break;
                    }
                }
                if(this_process)
                {
                    finished[curr_pid] = true;
                    
                    found = true;
                    for(int i = 0; i < resource_kind_num; i++)
                    {
                        available_resources_tmp[i] += Max[curr_pid][i] - Need_tmp[curr_pid][i];
                        
                    }
                    // cout<<endl << curr_pid << " need : ";

                    // for(int i = 0; i < resource_kind_num; i++)
                    // {
                    //     cout << Need_tmp[curr_pid][i] << " " ;
                    // }
                    // cout<<endl;
                    break;
                    // map<int,bool>::iterator it = finished.find(curr_pid);               
                    // it->second = true;
                }
                // else
                // {
                //     cout<< "not choose: " << curr_pid << " need : ";

                //     for(int i = 0; i < resource_kind_num; i++)
                //     {
                //         cout << Need_tmp[curr_pid][i] << " " ;
                //     }
                //     cout<<endl;
                // }
                
            }
        
        }


    }
    
    int unfinished_num = 0;
    for(map<int, bool>::iterator it = finished.begin(); it != finished.end(); it ++)
    {
        // cout << "pid : " << it->first << " state: " << it->second <<endl;
        if(it->second == false)
        {
            unfinished_num ++;
        }
        it->second = false;
    }
    // cout<<"unfinished num" << unfinished_num << endl;
    if(unfinished_num == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
    
    
}

int create_process(int pid)
{
    vector<int> v;
    for(int i = 0; i < resource_kind_num; i ++)
    {
        int tmp;
        cin >> tmp;
        v.push_back(tmp);
    }

    for(int i = 0; i < resource_kind_num; i ++)
    {
        if(v[i] > max_resources[i])
        {
            cout << "NOT OK" << endl;
            return 1;
        }
    }

    Max.insert(pair<int, vector<int>>(pid, v));
    Need.insert(pair<int, vector<int>>(pid, v));
    finished.insert(pair<int, bool>(pid, false));

    // for(map<int, vector<int>>::iterator mapitr= Max.begin(); mapitr != Max.end(); mapitr ++)
    // {
    //     cout << mapitr->first << ":";
    //     for(vector<int>::iterator vecitr = mapitr->second.begin(); vecitr != mapitr->second.end(); vecitr ++)
    //     {
    //         cout<< *vecitr << "  ";
    //     }
    //     cout << endl;
    // }
    cout << "OK" << endl;
    return 0;
}

void request(int pid)
{
    vector<int> req;
    for(int i = 0; i < resource_kind_num; i ++)
    {
        int tmp;
        cin >> tmp;
        req.push_back(tmp);
    }

    if(banker(pid, req))
    {
        for(int i = 0; i < resource_kind_num; i ++)
        {
            available_resources[i] -= req[i];
            Need[pid][i] -= req[i];
        }
        cout<<"OK"<<endl;
    }
    else
    {
        cout << "NOT OK" << endl;
    }
}

void terminate(int pid)
{
    map<int, vector<int>>::iterator it = Max.find(pid);
    if(it == Max.end())
    {
        cout<<"NOT OK"<<endl;
        return;
    }

    for(int i = 0; i < resource_kind_num; i ++)
    {
        available_resources[i] += Max[pid][i] - Need[pid][i];
    }


    Max.erase(pid);
    Need.erase(pid);
    finished.erase(pid);
    cout<<"OK"<<endl;

}


int main()
{
    int pid;
    string cmd;

    cin >> resource_kind_num;
    for(int i = 0; i < resource_kind_num; i ++)
    {
        int tmp;
        cin >> tmp;
        available_resources.push_back(tmp);
        max_resources.push_back(tmp);
    }
    while(cin >> pid >> cmd)
    {
        if(cmd == "new")
        {
            /* create a new process */
            // cout << "new" << endl;
            create_process(pid);
        }
        else if(cmd == "request")
        {
            // cout << "request" << endl;
            request(pid);
        }
        else if(cmd == "terminate")
        {
            // cout << "terminate" << endl;
            terminate(pid);
        }
        // vector<int> v;
        // for(int i = 0; i < resource_kind_num; i ++)
        // {
        //     int tmp;
        //     cin >> tmp;
        //     v.push_back(tmp);

        // }
        // max.insert(pair<string, vector<int>>(s, v));

        // for(vector<int>::iterator vecitr = v.begin(); vecitr != v.end(); vecitr ++)
        // {
        //     cout<< *vecitr << "\t";
        // }


    }

    // cout<<"end while"<<endl;

    // for(map<string, vector<int>>::iterator mapitr= m.begin(); mapitr != m.end(); mapitr ++)
    // {
    //     cout << mapitr->first << ":";
    //     for(vector<int>::iterator vecitr = mapitr->second.begin(); vecitr != mapitr->second.end(); vecitr ++)
    //     {
    //         cout<< *vecitr <<endl;
    //     }
    // }


    return 0;
}