
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

```
#include <iostream>
#include <vector>
#include <algorithm>  // std::max_element
#include <iterator>   // std::begin, std::end

int main() {
    std::vector<int> vec = {3, 7, 2, 9, 1, 5};

    // 使用 std::max_element 找到最大元素的迭代器
    auto max_it = std::max_element(std::begin(vec), std::end(vec));

    if (max_it != std::end(vec)) {
        std::cout << "最大元素是: " << *max_it << std::endl;
    } else {
        std::cout << "vector为空" << std::endl;
    }

    return 0;
}
```


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
