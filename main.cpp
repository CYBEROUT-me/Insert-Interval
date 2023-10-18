#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    enum operations
    {
        two_intervals_nums_in_other_intervals,
        only_first_intervals_num_in_other_intervals,
        only_second_intervals_num_in_other_intervals,
        no_intervals_nums_in_other_intervals
    };
    int oper;

    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        cout << "\n INTERVALS: " << endl;
        for(int i = 0; i < intervals.size(); i++){
            cout << "[";
            for(auto item : intervals[i]){
                cout << item << " ";
            }
            cout << "]";
        }
        cout << "\n newINTERVALS: " << endl;
        cout << "[";
        for(auto item : newInterval){
            cout << item << ",";
        }
        cout << "]";
        int in1 = -2;
        int in2 = -2;
        int pos1 = -2;
        int pos2 = -2;
        vector<vector<int>> ans;
        if(intervals.size() == 0){
            ans.push_back(newInterval);
        }
        else{
            for(int i = 0; i < intervals.size(); i++){
                if(newInterval[0] - intervals[i][0] <= intervals[i][1]-intervals[i][0] && newInterval[0] - intervals[i][0] >= 0) {
                    pos1 = i;
                }
                if(newInterval[1] - intervals[i][0] <= intervals[i][1]-intervals[i][0] && newInterval[1] - intervals[i][0] >= 0) {
                    pos2 = i;
                }
                if(i != intervals.size() - 1){
                    if(newInterval[0] - intervals[i][1] < intervals[i+1][0]-intervals[i][1] && newInterval[0] - intervals[i][1] > 0) {
                        in1 = i;
                    }
                    if(newInterval[1] - intervals[i][1] < intervals[i+1][0]-intervals[i][1] && newInterval[1] - intervals[i][1] > 0) {
                        in2 = i;
                    }
                }
                else{
                    if(newInterval[0] - intervals[i][1] < INT_MAX-intervals[i][1] && newInterval[0] - intervals[i][1] > 0) {
                        in1 = i;
                    }
                    if(newInterval[1] - intervals[i][1] < INT_MAX-intervals[i][1] && newInterval[1] - intervals[i][1] > 0) {
                        in2 = i;
                    }
                }
            }
            if(pos1 != -2 && pos2 != -2){
                oper = two_intervals_nums_in_other_intervals;
            }
            if(pos1 != -2 && pos2 == -2){
                oper = only_first_intervals_num_in_other_intervals;
            }
            if(pos1 == -2 && pos2 != -2){
                oper = only_second_intervals_num_in_other_intervals;
            }
            if(pos1 == -2 && pos2 == -2){
                oper = no_intervals_nums_in_other_intervals;
            }
            switch(oper)
            {
                case two_intervals_nums_in_other_intervals:
                {
                    for(int i = 0; i < pos1; i++) {
                        ans.push_back(intervals[i]);
                    }
                    ans.push_back({intervals[pos1][0], intervals[pos2][1]});
                    for(int i = pos2 + 1; i < intervals.size(); i++) {
                        ans.push_back(intervals[i]);
                    }
                    break;
                }
                case only_first_intervals_num_in_other_intervals: {
                    for (int i = 0; i < pos1; i++) {
                        ans.push_back(intervals[i]);
                    }
                    ans.push_back({intervals[pos1][0], newInterval[1]});
                    for (int i = in2 + 1; i < intervals.size(); i++) {
                        ans.push_back(intervals[i]);
                    }
                    break;
                }
                case only_second_intervals_num_in_other_intervals:
                {
                    for(int i = 0; i <= in1; i++) {
                        ans.push_back(intervals[i]);
                    }
                    ans.push_back({newInterval[0], intervals[pos2][1]});
                    for(int i = pos2+1; i < intervals.size(); i++) {
                        ans.push_back(intervals[i]);
                    }
                }
                case no_intervals_nums_in_other_intervals:
                {
                    if(in1 != -2 && in2 != -2){
                        for(int i = 0; i <= in1; i++) {
                            ans.push_back(intervals[i]);
                        }
                        ans.push_back(newInterval);
                        for(int i = in2 + 1; i < intervals.size(); i++) {
                            ans.push_back(intervals[i]);
                        }
                    }
                    else {
                        if (newInterval[1] < intervals[0][0]) {
                            ans.push_back(newInterval);
                            for (int i = 0; i < intervals.size(); i++) ans.push_back(intervals[i]);
                        }
                        if(newInterval[0] < intervals[0][0] && newInterval[1] > intervals[intervals.size()-1][1]) {
                            ans.push_back(newInterval);
                        }
                    }
                    break;
                }
            }
        }
        cout << "\nin1: " << in1 << "\nin2: " << in2 << "\npos1: " << pos1 << "\npos2: " << pos2 << endl;
        cout << "\n ANS: " << endl;
        for(int i = 0; i < ans.size(); i++){
            cout << "[";
            for(auto item : ans[i]){
                cout << item << " ";
            }
            cout << "]";
        }
        return ans;
    }


    int getIndex(vector<int> v, int K)
    {
        auto it = find(v.begin(), v.end(), K);
        if (it != v.end())
        {
            int index = it - v.begin();
            return index;
        }
        else {
            return -1;
        }
    }

    vector<vector<int>> remove(vector<vector<int>>& intervals, vector<int>& remInterval) {
        cout << "INTERVALS: " << endl;
        for(int i = 0; i < intervals.size(); i++){
            cout << "[ ";
            for(auto item : intervals[i]){
                cout << item << " ";
            }
            cout << "]";
        }
        cout << "\nTO REMOVE INTERVAL: ";
        cout << "[ ";
        for(auto item : remInterval){
            cout << item << " ";
        }
        cout << "]";
        vector<vector<int>> ans;
        vector<int> temp;
        for(int i = 0; i < intervals.size(); i++){
            for(int j = intervals[i][0]; j <= intervals[i][1];j++){
                temp.push_back(j);
            }
        }
        for(int i = remInterval[0]; i <= remInterval[1]; i++){
            int k = getIndex(temp, i);
            if(k > -1){
                temp.erase(temp.begin()+k);
            }
        }
        sort(temp.begin(), temp.end());
        int lowest = 0;
        int highest = 0;
        for(int i = 0; i < temp.size()-1; i++){
            if(temp[i] != temp[i+1]-1){
                highest = i;
                ans.push_back({temp[lowest], temp[highest]});
                lowest = i + 1;
                if(i == temp.size() - 2) ans.push_back({temp[temp.size()-1], temp[temp.size()-1]});
            }
        }
        cout << "\nANSWER IS: " << endl;
        for(int i = 0; i < ans.size(); i++){
            cout << "[ ";
            for(auto item : ans[i]){
                cout << item << " ";
            }
            cout << "]";
        }
        return ans;
    }
};



int main() {
    Solution a;
    vector<vector<int>> v = {{1,2},{4,7},{9,10},{12,16}};
    vector<int> n = {9,13};
    vector<int> rem = {2,8};
    a.insert(v, n);
    a.remove(v, rem);
}
