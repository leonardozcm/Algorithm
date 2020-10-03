#pragma once
#include <vector>
#include<map>
#include <iostream>
using namespace std;

class Solution
{
public:
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        auto size = candidates.size();
        sort(candidates.begin(), candidates.end());
        vector<int> path;
        vector<vector<int>> res;
        combinationSumdfs(candidates, target, 0, size, path, res);
        return res;
    }
    bool combinationSumdfs(vector<int> &candidates, int target, int begin, int size, vector<int> path, vector<vector<int>> &res)
    {
        if (target < 0)
            return false;
        if (target == 0)
        {
            res.push_back(path);
            return false;
        }

        for (int i = begin; i < size; i++)
        {
            /* code */
            auto pathtmp = path;
            pathtmp.push_back(candidates[i]);
            if (!combinationSumdfs(candidates, target - candidates[i], i, size, pathtmp, res))
                break;
        }
        return true;
    }
    void testcombinationSum()
    {
        vector<int> example = {10, 1, 2, 7, 6, 1, 5};
        int target = 8;
        for (auto &&i : combinationSum2(example, target))
        {
            for (auto &&j : i)
            {
                cout << j << ",";
            }
            cout << endl;
        }
    }
    //res[target]=sum(res[target-arr[i]])//i>=begin
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
    {
        auto size = candidates.size();
        sort(candidates.begin(), candidates.end());
        vector<int> path;
        vector<vector<int>> res;
        combinationSum2dfs(candidates, target, 0, size, path, res);
        return res;
    }
    bool combinationSum2dfs(vector<int> &candidates, int target, int begin, int size, vector<int> path, vector<vector<int>> &res)
    {
        if (target < 0)
            return false;
        if (target == 0)
        {
            res.push_back(path);
            return false;
        }

        int selectone;
        for (int i = begin; i < size; i++)
        {
            /* code */
            vector<int> pathtmp = path;
            pathtmp.push_back(candidates[i]);
            if (selectone == candidates[i])
                continue;
            else
            {
                /* code */
                selectone = candidates[i];
            }

            if (!combinationSum2dfs(candidates, target - candidates[i], i + 1, size, pathtmp, res))
                break;
        }
        return true;
    }

    int firstMissingPositive(vector<int> &nums)
    {
        int patch = 1;
        if (!nums.size())
            return patch;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++)
        {
            /* code */
            if (nums[i] <= 0)
                continue;
            if (nums[i] != patch)
            {
                return patch;
            }
            else
            {
                while (i + 1 < nums.size() && nums[i + 1] == nums[i])
                {
                    /* code */
                    i++;
                }

                patch++;
            }
        }
        return patch;
    }

    void firstMissingPositiveTest()
    {
        vector<int> examples = {7, 8, 9, 11, 12};
        cout << firstMissingPositive(examples) << endl;
    }

    int trapOutoftime(vector<int> &height)
    {
        int start = 0;
        int res = 0;
        int tmp = 0;
        int flag = 0;
        while (start < height.size() && height[start] == 0)
        {
            /* code */
            start++;
        }

        for (int i = start; i < height.size(); i++)
        {
            /* code */
            if (height[i] == 0)
                tmp++;
            else
            {
                flag++;
                res += tmp;
                tmp = 0;
                height[i]--;
            }
        }
        if (flag < 2)
            return 0;
        res += trap(height);
        return res;
    }

    int trap(vector<int> &height)
    {
        int start = 0;
        int res = 0;
        int end = 0;

        while (start + 1 < height.size() && height[start] <= height[start + 1])
        {
            /* code */
            start++;
        }
        end = start + 1;

        while (end < height.size())
        {

            while (end + 1 < height.size() && height[end] >= height[end + 1])
            {
                /* code */
                end++;
            }

            /* code */
            int endmax = end;
            while (end < height.size())
            {
                /* code */
                if (height[end] >= height[endmax])
                {
                    endmax = end;
                    if (height[endmax] >= height[endmax - 1] && (endmax + 1 == height.size() || height[endmax] >= height[endmax + 1]) && height[endmax] >= height[start])
                        break;
                }

                end++;
            }

            if (endmax == start + 1)
                return res;
            res += slideWindow(height, start, endmax);
            start = end = endmax;

            end++;
        }
        return res;
    }
    int slideWindow(vector<int> &height, int start, int end)
    {
        int res = 0;
        int max = height[start] < height[end] ? height[start] : height[end];
        for (int i = start + 1; i < end; i++)
        {
            /* code */
            res += max > height[i] ? max - height[i] : 0;
        }
        return res;
    }
    void trapTest()
    {
        // vector<int> examples={0,1,0,2,1,0,1,3,2,1,2,1};

        vector<int> examples = {5, 4, 2, 1, 2};
        cout << trap(examples) << endl;
    }
    string multiply(string num1, string num2)
    {
        if (num1[0] == '0' || num2[0] == '0')
            return "0";
        int m = num1.size(), n = num2.size();
        vector<int> Ansarr(m + n);
        for (int i = m - 1; i >= 0; i--)
        {
            /* code */
            for (int j = n - 1; j >= 0; j--)
            {
                /* code */
                Ansarr[i + j + 1] += char2int(num1[i]) * char2int(num2[j]);
            }
        }

        for (int i = m + n - 1; i > 0; i--)
        {
            /* code */
            Ansarr[i - 1] += Ansarr[i] / 10;
            Ansarr[i] = Ansarr[i] % 10;
        }

        int startindex = Ansarr[0] ? 0 : 1;
        string ans;
        while (startindex < n + m)
        {
            /* code */
            ans.push_back(Ansarr[startindex]);
            startindex++;
        }
        for (auto &&i : ans)
        {
            i += '0';
        }
        return ans;
    }

    int char2int(char a)
    {
        return a - '0';
    }

    bool isMatch(string s, string p)
    {

        if (s.empty() && (p.empty() || (p.size()==1&&p.at(0)=='*')))
        {
            return true;
        }else if(s.empty()||p.empty())
        {
            /* code */
            return false;
        }
        string tmp;
        bool flag=true;
        for (int i = 0; i < p.size(); i++)
        {
            /* code */
            if(p.at(i)!='*'){
                tmp.push_back(p.at(i));
                flag=true;
            }else
            {
                if(flag){tmp.push_back('*');
            flag=false;
}
            }
            

        }
        p=tmp;
        
        vector<vector<int>> patch(p.size(), vector<int>(s.size()));
        patch[0][0] = isPatch(s.at(0), p.at(0));

        for (int i = 0; i < p.size(); i++)
        {
            char p_tmp = p.at(i);
            for (int j = 0; j < s.size(); j++)
            {
                if (i > 0 && j > 0 && p_tmp != '*')
                    patch[i][j] = patch[i - 1][j - 1] && isPatch(s.at(j), p_tmp);
                else if (i == 0 && j == 0 && p_tmp != '*')
                {
                    patch[i][j] = isPatch(s.at(0), p.at(0));
                }
                else if (p_tmp == '*')
                {
                    if (j == 0)
                    {
                        patch[i][j] = i == 0 ? true : patch[i - 1][j];
                        int tail=p.at(0)=='*'?2:1;
                        if(i<tail&&i+1<p.size())
                            patch[i+1][j]=patch[i][j]&&isPatch(s.at(j), p.at(i+1));
                    }

                    else
                        patch[i][j] = i == 0 ? patch[i][j - 1] : patch[i - 1][j - 1] || patch[i][j - 1] || patch[i-1][j ];
                }
            }
        }
        return patch[p.size() - 1][s.size() - 1];
    }

    bool isPatch(char s, char p)
    {
        if (p == '*' || p == '?' || p == s)
            return true;
        else
            return false;
    }

    void testisMatch()
    {
       string s = "b";
        string p = "*a*";
        // string s="mississippi";
        // string p="m??*ss*?i*pi";

        // string s="aab";
        // string p="c*a*b";
        // string s = "adceb";
        // string p = "*a*b";
        // string s="aa";
        // string p="*";

        cout << isMatch(s, p) << endl;
    }

 int jump(vector<int>& nums) {
            if(nums.size()==1)return 0;
            int step=0;
            int start=0;
            int end=0;
            while(end<nums.size()-1){
                int max=end;
                for (int i = start; i <= end; i++)
                {
                    /* code */
                    if(nums[i]+i>max){
                        max=nums[i]+i;
                    }
                }
                start=end+1;
                end=max;
                step++;
                
            }
            return step;
        }
    
    void testJump(){
        vector<int> examples={1,1,1,1};
        cout<<jump(examples)<<endl;
    }

    void backtrack(vector<int>& nums,vector<vector<int>> &res,int first,int length){
            if(first==length){
                res.emplace_back(nums);
                return;
            }
            vector<int> searched;
            for (int i = first; i < length; i++)
            {
                /* code */

                if(count(searched.begin(),searched.end(),nums[i])){
                    continue;
                }else
                {
                    searched.push_back(nums[i]);
                }
                
                swap(nums[first],nums[i]);
                backtrack(nums,res,first+1,length);
                swap(nums[first],nums[i]);
            }
            
    }

    vector<vector<int>> permute(vector<int>& nums) {
            vector<vector<int> > res;
        backtrack( nums,res, 0, (int)nums.size());
        return res;

    }
        void rotate(vector<vector<int>>& matrix) {
            int n=matrix.size();
            //up and down
            for (int i = 0; i < n/2; i++)
            {
                /* code */
                matrix[i].swap(matrix[n-1-i]);
            }
            for (int i = 0; i <n; i++)
            {
                /* code */
                for (int j = i; j < n; j++)
                {
                    /* code */
                    swap(matrix[i][j],matrix[j][i]);
                }
                
                
            }
    }

      vector<vector<string>> groupAnagrams(vector<string>& strs) {
            vector<vector<string>> res;
            map<string,vector<string>> strmap;
            for (auto &&i : strs)
            {
                string t=i;
                sort(t.begin(),t.end());
                strmap[t].push_back(i);
            }
            for (auto &&i : strmap)
            {
                res.push_back(i.second);
            }
            return res;
            
    }

        double myPow(double x, int n) {
            if(x==0)return 0;
          
            if(n<0)
                return 1/myPow(x,-n);
            else if (n==0||x==1)
            {
                /* code */
                return 1;
            }
            

            if(n%2==0){
                double tmp=myPow(x,n/2);
                return tmp*tmp;
            }else
            {
                 double tmp=myPow(x,(int)n/2);
                return tmp*tmp*x;
            }
            
    }                                                                   
    void testMypow(){
        cout <<myPow(1.00000,-2147483648)<<endl;
    }
};