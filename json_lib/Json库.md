## 编译环境

- cmake

  - ```shell
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Debug ..
    # cmake -DCMAKE_BUILD_TYPE=Release ..
    make
    ```

  - ```shell
    cmake -G Xcode..
    open leptjson_test.xcodeproj
    ```

## 单元测试

- 常见的单元测试框架有xUint系列，如[C++的Google Test](https://github.com/google/googletest), [C#的Nunit](https://nunit.org/)
- 功能驱动开发（Feature - Driven Development, FDD)
- 测试驱动开发（Test - Driven Develo pment, TDD)
  - 重构：在不改变代码外在行为的情况下，对代码进行修改，以改进程序的内部结构

## 宏的编写

- 反斜杠代表该行未结束，会串接下一行
- 如果宏里有多过一个语句，就需要用do{/*...*/}while(0)包裹成单个语句

## 断言

- 当程序以release配置编译时（定义了NDEBUG宏），assert（）不会做检测；而当在debug配置时（没有定义NDEBUG宏），则会在运行时检测assert(cond)中的条件是否为真，断言失败会直接令程序崩溃
- **断言中不能改动变量的值**

## JSON

- Json是树状结构，包含六种数据类型

  - null, boolean, number, string, array, object

- Json 库

  - 把Json文本解析为一个树状数据结构（parse）
  - 提供接口访问该数据结构 （access）
  - 把数据结构转换成Json文本 （stringify）

- **Json 数字语法**

  - ```C++
    JSON-text = ws value ws 
    ws = *(%x20 / %x09 / %x0D)
    # xhh 表示以16进制表示的字符，/是多选一，*是零或多个，（）用于分组
    value = null / false / true
    null = "null"
    false = "false"
    true = "true"
    ```

  - ```C++
    number = ["-"] int [frac] [exp]
    int = "0" / digit 1-9 
    frac = "."
    exp = "e" / "E" ["-" / "+"] [*[1-9]]
    # 负号 + 整数 + 小数 + 指数
    # C语言中，数组长度，索引值最好使用size_t类型，而不是int或unsigned.
    ```

  - <img src="https://pic1.zhimg.com/80/v2-de5a6e279cbac2071284bfa7bb1e5730_1440w.png" alt="v2-de5a6e279cbac2071284bfa7bb1e5730_1440w" style="zoom:50%;" />

- **Json 字符串语法**

  - ```
    JSON 字符串语法, 转义字符（escape character)
    string = quotation-mark *char quotation-mark
    char = unescaped / 
    	escape (
    	%x22 " quotation 引用
    	%x5C \ reverse solidus 反斜线
    	%x2F / solidus 斜线
    	%x62 b backspace 空格
    	%x66 f form feed 换页符
    	%x6E n line feed 换行符
    	%x72 r carriage return 回车
    	%x74 t tab	制表符
    	%x75 u XXXX )
    escape = %x5C \
    quotation-mark = %x22 "
    unescaped = %x20-21 / %x23-5B / %x5D-10FFFF
    ```

  - 当解析字符串时`lept_parse_string()`，把解析的结果先储存在一个临时的缓冲区，**在完成解析前，这个缓冲区的大小是无法预知的**；解析完成后`lept_set_string()`把缓冲区的结果记值；可通过重用动态堆栈来避免每次解析 JSON 时需要重新创建动态数据结构，节省时间；

  - Json输入字符串`"a\tb"`,C / C++对其理解为 为`\"a\\tb\"`；

  - Unicode编码（多语言的统一编码系统）

    - 多个机构成立了Unicode联盟，并于1991年释出Unicode 1.0，收录了24种语言共7161个字符。在2016年，Unicode 9.0 共收录135种语言，共128237个字符；
    - 这些字符被收录为统一字符集（Universal Coded Character Set, UCS），每个字符映射至一个整数码点（code point），码点的范围是 0 至 0x10FFFF，码点又通常记作 U+XXXX，当中 XXXX 为 16 进位数字。例如 劲 → U+52B2、峰 → U+5CF0。很明显，UCS 中的字符无法像 ASCII 般以一个字节存储；
    - Unicode &rarr; UTF-8（会将一个码点储存为一至多个编码单元, code unit）；
    - [C++ 11 新特性--Unicode支持](https://www.jianshu.com/p/8b87a05c23b1)
    - [Unicode解码 + UTF-8编码](https://zhuanlan.zhihu.com/p/45695434)

- **JSON 数组**

  - ```
    JSON 数组 语法
    array = %x5B ws [value * (ws %x2C ws value)] ws %x5D
    %x5B 左中括号；ws 空白字符; %x2C 逗号; %x5D 右中括号;
    一个数组可以包含零至多个值，以逗号分隔，例如 []、[1,2,true]、[[1,2],[3,4],"abc"] 都是合法的数组，且不接受末端额外的逗号，如[1,2,]是不合法的;
    // 实现难点不在于语法，而在于内存管理；
    ```

  - 存储 JSON 数组类型的数据结构

    - **数组**：优点是能以 *O(1)* 用索引访问任何元素，次要优点是内存布局紧凑，省内存之余还有高缓存一致性（cache coherence）；但缺点是不能快速插入元素，且在解析 JSON 数组时无法提前预知应该分配的数组大小;
    - **链表**：优点是可快速地插入元素（开端、末端或中间），但是查询的时间复杂度为 *O(n)* ；另一个缺点是相对于数组而言，链表在存储每个元素时有额外的内存开销（存储下一节点的指针），而且遍历时元素所在的内存可能不连续，令缓存不命中（cache miss）的机会上升；

- **JSON 对象**

  - ```
    member = string ws %x3A ws value
    object = %x7B ws [ member *( ws %x2C ws member ) ] ws %x7D
    %x3A,逗号; %x7B,左花括号; %x7D,右花括号; %x2C,逗号;
    {"one": 1, "two":2}
    [{"name": "zhang san"}, {"name": "li si"}]
    ```

  - 可表示键值对的数据结构

    - 动态数组：可扩展容量的数组，如 C++ 的 `std::vector`；
    - 有序动态数组：和动态数组相同，但保证元素已排序，可用二分搜寻查询成员；
    - 平衡树：平衡二叉树可有序地遍历成员，如红黑树和`std::map(std::multi_map支持重复键)`;
    - 哈希表：通过哈希函数实现平均 *O(1)* 查询，如 C++11 的`std::unordered_map (unordered_multimap 支持重复键）`;

    <img src="https://pic4.zhimg.com/80/v2-d21b818cfeaa1932d89e049836c47ebb_1440w.png" alt="v2-d21b818cfeaa1932d89e049836c47ebb_1440w" style="zoom: 33%;" />

- **JSON 生成器**

  - 把树形数据转换成 JSON 文本，这个过程又称为**字符串化 (stringify)**；为了简单期间，不做换行、缩进等美化处理，因此生成的 **JSON 文本**会是单行、无空白字符的最紧凑形式；
  - <img src="https://pic4.zhimg.com/80/v2-fb04f1beaccd5690a1ba4c99403eb4a7_1440w.png" alt="v2-fb04f1beaccd5690a1ba4c99403eb4a7_1440w" style="zoom: 67%;" />
  - 对于浮点型number，`to_string(int / float / double)`使用正则匹配去除末尾多余的0.
  - Array 和 Object 相关函数的互相调用需要对其函数进行提前声明,`.h 或 .cpp`中均可；