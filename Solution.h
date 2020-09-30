#pragma once
#include <vector>

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
        if (num1[0]== '0' || num2[0]== '0')
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

        int startindex=Ansarr[0]?0:1;
        string ans;
        while (startindex<n+m)
        {
            /* code */
            ans.push_back(Ansarr[startindex]);
            startindex++;
        }
        for (auto &&i : ans)
        {
            i+='0';
        }
        return ans;
    }

    int char2int(char a)
    {
        return a - '0';
    }

    bool isMatch(string s, string p) {
        
    }
};