#pragma on
#include<vector>
#include<iostream>
using namespace std;
class Solution {
    public:
        vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
            auto size=candidates.size();
            vector<int> path;
            vector<vector<int>> res;
            combinationSumdfs(candidates,target,0,size,path,res);
        }   

        void combinationSumdfs(vector<int>& candidates, int target,int begin,int size,vector<int> path,vector<vector<int>> &res) {
            if(target<0)
                return;
            if(target==0)
            {
                res.push_back(path);
                return;
            }
           
            for (int i = begin; i < size; i++)
            {
                /* code */
                 auto pathtmp=path;
                 pathtmp.push_back(candidates[i]);
                 combinationSumdfs(candidates,target-candidates[i],i,size,pathtmp,res);
                
            }
            

        }

        void testcombinationSum(){
            vector<int> example={2,3,6,7};
            int target=7;
            for (auto &&i : combinationSum(example,target))
            {
                for (auto &&j : i)
                {
                    cout<<j<<",";
                }
                cout<<endl;
            }
            
        }
};