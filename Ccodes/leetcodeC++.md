## STL

### 哈希表遍历

```c++
for (const auto& pair : myMap) {
        if (pair.first == pair.second) {
            std::cout << "Found a pair where key and value are equal: Key: " << pair.first
                      << ", Value: " << pair.second << std::endl;
            found = true;
        }
    }
```

或者直接用pair结构

```c++
for (auto [key, value]: m) {
            if (key == value) {
                ans = max(ans, key);
            }
        }
```


### 集合方法

```cpp
f (st.contains(x - 1)) 
```

contains是C++20新特性，在这之前可以用count方法，返回0或1.

在 C++ 的 `unordered_set` 中，删除某个元素可以通过其成员函数 `erase` 实现。`erase` 提供了多种重载形式，可以根据不同的需求选择合适的方式

### push_back和emplace_back

- **`emplace_back` 更高效** ：对于复杂对象，它避免了临时对象的创建和移动。
- **`push_back` 更通用** ：适用于已构造好的对象，语法更简单。
- **选择依据** ：根据具体场景权衡性能和代码可读性。

**为什么 `emplace_back` 报错？**

在这段代码中：

ans.emplace_back({x, nums[j], nums[k]});

`ans` 是一个 `vector<vector<int>>` 类型的容器，`emplace_back` 需要推断如何将 `{x, nums[j], nums[k]}` 转换为 `vector<int>` 类型的对象。虽然 `{x, nums[j], nums[k]}` 看起来像是一个合法的初始化列表，但由于 C++ 的模板推导规则，编译器可能无法正确推断出 `vector<int>` 的构造函数可以接受这种形式的参数。

具体来说：

- `emplace_back` 需要明确知道它正在构造的目标类型。
- 在某些编译器实现中，`emplace_back` 对初始化列表的支持可能不够完善，导致推断失败。

因此，编译器会报错，提示无法匹配合适的重载函数。

**为什么 `push_back` 不报错？**

相比之下，`push_back` 的行为更为简单。它的作用是将一个已经构造好的对象添加到容器中。当我们写：

ans.push_back({x, nums[j], nums[k]});

编译器会自动将 `{x, nums[j], nums[k]}` 解释为一个 `vector<int>` 类型的临时对象，并将其传递给 `push_back`。这种方式更符合 C++ 的语法规则，因此不会报错。

换句话说，`push_back` 更加通用，因为它总是处理完整的对象，而不是依赖模板推导来构造对象。

------

**如何解决这个问题？**

如果你希望继续使用 `emplace_back`，可以通过显式指定目标类型来帮助编译器推断。例如：

ans.emplace_back(vector<int>{x, nums[j], nums[k]});

这里，我们显式地将 `{x, nums[j], nums[k]}` 包装为一个 `vector<int>` 类型的对象，从而避免了模板推导的问题。



### unordered_map方法

contains

```c++
unordered_map<int, int> cnt;
for (int sj : s) {
    // 注意不要直接 += cnt[sj-k]，如果 sj-k 不存在，会插入 sj-k
    ans += cnt.contains(sj - k) ? cnt[sj - k] : 0;
    cnt[sj]++;
}

```

声明

```cpp
unordered_map<int, int> cnt{{0, 1}}; // s[0]=0 单独统计
```

### 双端队列deque

deque

```c++
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> ans;
        deque<int> q; // 双端队列
        for (int i = 0; i < nums.size(); i++) {
            // 1. 入
            while (!q.empty() && nums[q.back()] <= nums[i]) {
                q.pop_back(); // 维护 q 的单调性
            }
            q.push_back(i); // 入队
            // 2. 出
            if (i - q.front() >= k) { // 队首已经离开窗口了
                q.pop_front();
            }
            // 3. 记录答案
            if (i >= k - 1) {
                // 由于队首到队尾单调递减，所以窗口最大值就是队首
                ans.push_back(nums[q.front()]);
            }
        }
        return ans;
    }
};
```

### reduce

C++17及之后，通过` <numeric>`头文件引入了一个名为` std::reduce`的函数。

```c++
#include <iostream>
#include <vector>
#include <numeric> // 包含 std::reduce

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 使用默认的加法操作
    int sum = std::reduce(numbers.begin(), numbers.end());

    std::cout << "Sum: " << sum << std::endl; // 输出: Sum: 15
    return 0;
}
```









## 全局变量

### 移动记录数组



## 引用

避免操作变量的副本。

如果我们不使用引用，而是写成 `for (int x : nums)`，代码的行为会发生以下变化：

- `x` 是 `nums` 中每个元素的副本。
- 在循环体中，`swap(x, nums[ptr0])` 只会交换 `x`（副本）和 `nums[ptr0]` 的值，而不会影响 `nums` 中的实际元素。
- 因此，`nums` 的内容不会被正确修改，最终结果将是错误的。

## 定长滑窗模板

![image-20250327231854444](assets/image-20250327231854444.png)

```c++
class Solution {
public:
    int maxVowels(string s, int k) {
        int ans = 0, vowel = 0;
        for (int i = 0; i < s.length(); i++) {
            // 1. 进入窗口
            if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') {
                vowel++;
            }
            if (i < k - 1) { // 窗口大小不足 k
                continue;
            }
            // 2. 更新答案
            ans = max(ans, vowel);
            // 3. 离开窗口
            char out = s[i - k + 1];
            if (out == 'a' || out == 'e' || out == 'i' || out == 'o' || out == 'u') {
                vowel--;
            }
        }
        return ans;
    }
};
```



## C++新特性相关

### constexpr

表示方向的数组：

```c++
static constexpr int DIRS[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
```

### move

**为什么使用 `move`？**

在这段代码中，`move` 的使用有以下几个优点：

1. **性能优化** ：
   - 如果不使用 `move`，`ans = t;` 会触发拷贝赋值操作，这会导致额外的内存分配和数据复制。
   - 使用 `move` 后，资源直接转移，避免了这些开销，尤其是在处理大字符串时效果显著。
2. **减少不必要的资源管理** ：
   - `t` 在赋值给 `ans` 后不再需要保留其原始内容，因此可以直接将其资源转移给 `ans`。
3. **代码清晰性** ：
   - 使用 `move` 明确表达了开发者的意图，即“我只需要转移资源，不需要保留原对象”。

## 题目涉及定理相关/模板题

### 顺时针90°旋转图像

上下翻转然后沿主对角线翻转，得到顺时针90°的图像。





















































































































