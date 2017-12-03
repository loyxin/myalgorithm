/*************************************************************************
	> File Name: kmp.cpp
	> Author: loyxin
	> Mail: rafrozenluoxin@gmail.com 
	> Created Time: 2017-12-03 20:49:31
 ************************************************************************/

#include<iostream>
using namespace std;
class Solution {
public:
	// 根据要匹配的字符串，分析该字符串，得到字符串是否有前缀
	// next 数值就是反应该特性
    void GetNext(string pattern) {
        next = new int[pattern.size()];
        next[0] = -1;
        int k = -1; 
        int j = 0;
        while (j < pattern.size()-1) {
            if (k == -1 || pattern[j] == pattern[k]) {
                ++j;
                ++k;
                if (pattern[j] != pattern[k]) {  
                    // 此时的 pattern[k] 即为 pattern[next[j] ]
                    next[j] =k; 
                } else {
                    // 如果 pattern[j] == pattern[next[j]]，则 k = next[k]
                    next[j] = next[k];
                }
            } else {
                k = next[k]; // 不匹配，向前找前缀，相当于用模式串匹配模式串
            }
        }
    }

    int KMPSearch(string str, string pattern) {
        if (str.size() == 0 || pattern.size() == 0)
            return -1;
        GetNext(pattern);
        int j = 0; // 待匹配串索引
        int k = 0; // 模式串索引
        while (j < str.size() && k < (int)pattern.size()) {  //注意，负数不能和 size_t 的无符号数作比较
            if (k == -1 || str[j] == pattern[k]) {
                ++k;
                ++j;
            } else {
                k = next[k]; // 不匹配，移动模式串
            }
        }
        if (k == pattern.size())
            return j-k;
        else
            return -1;
    }
    Solution() {
        next = NULL;
    }
    ~Solution() {
        if (next != NULL)
            delete []next;
        next = NULL;
    }
private:
    int *next;
};

int main()
{
    string str = "abacababc";
    string pattern = "abab";
    Solution sol;
    cout << sol.KMPSearch(str, pattern) << endl;
}
