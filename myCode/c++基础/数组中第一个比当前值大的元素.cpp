#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution{
public:
    vector<int> findMax(vector<int> num){
        if(num.size() == 0){
            return num;
        }
        vector<int> res(num.size());
        int i = 0;
        stack<int> s;
        while(i < num.size()){
            if(s.empty()||num[s.top() >= num[i]]){
                s.push(i++);
            }
            else{
                res[s.top()] = num[i];
                s.pop();
            }
        }
        while(!s.empty()){
            res[s.top()] = INT_MAX;
            s.pop();
        }
        for (int i = 0; i < res.size(); i++){
            cout << res[i] << " ";
        }
        cout << endl;
        return res;
    }
};

int main(){
    Solution s1;
    vector<int> v;
    v.push_back(2);
    v.push_back(1);
    v.push_back(5);
    v.push_back(4);
    v.push_back(6);
    v.push_back(5);

    s1.findMax(v);
}