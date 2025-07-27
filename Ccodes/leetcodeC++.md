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

### vector排序

降序排列：

```c++
#include <iostream>
#include <vector>
#include <algorithm> // 包含 sort 和 greater

int main() {
    std::vector<int> vec = {10, 2, 8, 5, 3};

    // 方法 1：Lambda 表达式
    std::sort(vec.begin(), vec.end(), [](int a, int b) { return a > b; });
    std::cout << "Lambda 降序结果: ";
    for (int num : vec) std::cout << num << " ";
    std::cout << std::endl;

    // 重新初始化 vector
    vec = {10, 2, 8, 5, 3};

    // 方法 2：std::greater
    std::sort(vec.begin(), vec.end(), std::greater<int>());
    std::cout << "std::greater 降序结果: ";
    for (int num : vec) std::cout << num << " ";
    std::cout << std::endl;

    return 0;
}
```

最后一项元素：back

```c++
return (nums.back() - 1) * (nums[nums.size() - 2] - 1);
```

### vector 中最大元素



### find

> 在 C++ 标准库中，不同容器或类的 `find` 方法的返回值和行为存在显著差异。用户提到的 **`npos`** 通常与字符串的 `find` 方法相关，而哈希表（如 `std::unordered_map` 或 `std::unordered_set`）的 `find` 方法返回的是迭代器，而非 `npos`。以下是详细对比：
>
> ---
>
> ### **1. `std::unordered_map`（哈希表）的 `find` 方法**
> - **功能**：在哈希表中查找键（key），返回指向该键的迭代器。
> - **返回值**：
>   - 如果找到键，返回指向该键-值对的迭代器（`iterator` 或 `const_iterator`）。
>   - **如果未找到**，返回哈希表的 `end()` 迭代器（`map.end()`）。
> - **示例**：
>   ```cpp
>   #include <unordered_map>
>   std::unordered_map<int, std::string> myMap;
>   // 假设 myMap 中没有键为 42 的元素
>   auto it = myMap.find(42);
>   if (it == myMap.end()) {
>       std::cout << "未找到键 42" << std::endl;
>   }
>   ```
>
> ---
>
> ### **2. `std::string` 的 `find` 方法**
> - **功能**：在字符串中查找子字符串或字符，返回第一个匹配的位置。
> - **返回值**：
>   - 如果找到子字符串/字符，返回其起始索引（`size_t` 类型）。
>   - **如果未找到**，返回 `std::string::npos`（一个特殊值，通常为 `-1` 或 `static_cast<size_t>(-1)`）。
> - **示例**：
>   ```cpp
>   std::string s = "Hello, World!";
>   size_t pos = s.find("Python"); // 未找到
>   if (pos == std::string::npos) {
>       std::cout << "未找到子字符串" << std::endl;
>   }
>   ```
>
> ---
>
> ### **3. 其他容器的 `find` 方法**
> #### **a. `std::vector` 或 `std::list` 的 `find`**
> - **注意**：这些容器本身没有 `find` 成员函数，而是通过 `<algorithm>` 头中的 `std::find` 算法实现。
> - **返回值**：
>   - 如果找到元素，返回指向该元素的迭代器。
>   - **如果未找到**，返回容器的 `end()` 迭代器。
> - **示例**：
>   ```cpp
>   #include <algorithm>
>   std::vector<int> vec = {1, 2, 3};
>   auto it = std::find(vec.begin(), vec.end(), 4);
>   if (it == vec.end()) {
>       std::cout << "未找到元素 4" << std::endl;
>   }
>   ```
>
> #### **b. `std::map` 的 `find`**
> - **功能**：在有序映射中查找键，返回迭代器。
> - **返回值**：
>   - 如果找到键，返回指向该键的迭代器。
>   - **未找到时返回 `map.end()`**，与 `unordered_map` 行为一致。
>
> ---
>
> ### **关键区别**
> | **方法**                   | **返回值类型**       | **未找到时的返回值** | **用途**                    |
> | -------------------------- | -------------------- | -------------------- | --------------------------- |
> | `std::unordered_map::find` | 迭代器（`iterator`） | `map.end()`          | 查找哈希表中的键            |
> | `std::string::find`        | `size_t`             | `std::string::npos`  | 查找字符串中的子字符串/字符 |
> | `std::find` (算法)         | 迭代器               | `end` 迭代器         | 查找容器中的元素            |
>
> ---
>
> ### **哪个会返回 `npos`？**
> - **只有 `std::string` 的 `find` 方法会返回 `npos`**。其他容器或算法的 `find` 方法均通过返回 `end()` 迭代器表示未找到。
>
> ---
>
> ### **常见错误与注意事项**
> 1. **混淆 `npos` 和 `end()`**：
>    - 如果误将 `unordered_map::find` 的返回值与 `npos` 比较，会导致逻辑错误。
>    ```cpp
>    // 错误示例（哈希表的 find 不会返回 npos）
>    if (myMap.find(key) == std::string::npos) { // 错误！类型不匹配
>        // ...
>    }
>    ```
>
> 2. **字符串的 `npos` 类型**：
>    - `std::string::npos` 是 `size_t` 类型，通常为 `-1` 的无符号值（如 `static_cast<size_t>(-1)`），需直接比较返回值是否等于它。
>
> 3. **其他容器的 `find`**：
>    - 对于 `std::vector`、`std::list` 等，需使用 `std::find` 算法，并检查是否等于 `end()` 迭代器。
>
> ---
>
> ### **总结**
> - **哈希表（`unordered_map`）的 `find`**：返回迭代器，未找到时返回 `end()`。
> - **字符串（`std::string`）的 `find`**：返回位置索引，未找到时返回 `npos`。
> - **其他容器的查找**：通过 `std::find` 算法实现，返回迭代器并检查 `end()`。
>
> 理解这些差异能避免常见的逻辑错误，确保代码的正确性。

![image-20250321181624194](assets/image-20250321181624194.png)

### vector 转化为 哈希集合

```c++
unordered_set<int> st(nums.begin(), nums.end()); // 把 nums 转成哈希集合
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



















































































































