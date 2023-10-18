#include <iostream>
#include <vector>


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
};



int main() {
    Solution a;
    vector<vector<int>> v = {{1,2},{3,5},{6,7},{8,10},{12,16}};
    vector<vector<int>> v2 = {{1,7}, {12,14}};
    if(v.size() < v2.size()) v.swap(v2);
    for(int i = 0; i < v2.size(); i++){
        v = a.insert(v,v2[i]);
    }
}
