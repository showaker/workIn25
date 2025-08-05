## 连续字符段长度比较
```
#include <string>
#include <algorithm>
using namespace std;

bool checkZeroOnes(string s) {
    int m1 = 0, m0 = 0;
    int i = 0, n = s.length();
    
    while (i < n) {
        int st = i;
        char v = s[st];
        
        // 找到连续相同字符的结束位置
        while (i < n && s[i] == v) {
            i++;
        }
        
        // 更新最大连续长度
        if (v == '1') {
            m1 = max(m1, i - st);
        } else {
            m0 = max(m0, i - st);
        }
    }
    
    return m1 > m0;
}
```







