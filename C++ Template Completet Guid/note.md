# <font face="楷体" size=8 color=rgb(23,13,73)>C++ 模板完全指南</font>
<font face="楷体" size=5 color=green>---笔记</font>

----------
## <font face="楷体">目录:</font>
[第一章: C++模板](#Chapter1)
[第二章: 类模板](#Chapter2)
[第三章: 非参数模板](#Chapter3)
[第四章: 可变参数模板](#Chapter4)

----------

<span id=Chapter1><!--第一章起始处--></span>

<font face="华文中宋">

## 回顾关于C++模板的使用规则

- __1.1 模板要解决的问题__ 
    <font face = "楷体">
    - 实现代码的 __可重用__, 提高代码可维护性
    - 实现 参数包(__paramter package__) , 参数化 行为(__behavior__), 对象(__object__) 等抽象概念
    - 实现元编程(__meta programming__)技术

    </font><!--楷体-->

- __1.2 C++ 模板的使用__

```cpp
// std::declval<> 可以适配不支持默认构造函数的对象
    template<typename T1, typename T2>
    decltype(std::declval<T1>() + std::declval<T2>()) 
        sum(T1&& t1, T2&& t2) {
            return t1 + t2;
        }
```

模板可以进行偏特化与全特化, 也可以根据具体参数自动推导, 但是如果有一个
参数无法正确推导，则需要提供左边所有参数的类型

```cpp
    template<typename T1, typename T2, typename Rt>
    Rt sum(T1&& t1, T2&& t2) {...} // sum<int, double, double>(1, 1.) 应该这样调用

```
- __1.3 auto的返回类型推导__
 
    - 可以使用`auto`关键字自动推导函数的返回类型 :
```cpp

    template<typename T1, typename T2>
    auto sum(T1&& t1, T2&& t2) { return t1 + t2; }

```

`auto`的推导法则有:
    <font face="楷体">

  - 1. 在不主动添加cv限定符的情况下, 按值初始化的变量将忽略cv限定符
  - 2. 根据规则1, 则使用auto声明变量初始化时, 如果目标对象是引用, 则会忽略引用
  - 3. 使用auto&& 声明时, 会应用引用折叠的规则
  - 4. 如果对象是一个函数或数组, 则auto会被推导为对应的指针类型
  - 5. 使用初始化列表时:
    * (1). 直接使用初始化列表时, 列表必须为单元素类型, 否则报错
    * (2). 使用等号时, 会被推到为`std::initializer_list<T>`类型
    

    </font><!--楷体-->

- 可以使用 *trailing return type syntax* 来推导返回类型
 
```cpp
    #include <type_traits> // std::decay<> 防止返回对象引用
    template<typename T1, typename T2>
    auto max(T1&& t1, t2&& t2) -> std::decay_t<decltype(t1 > t2 ? t1 : t2)>
    { return t1 > t2 ? t1 : t2; }

```

- __1.4 模板默认参数__
 
  模板支持默认参数 :

  ```cpp
      #include<type_traits>

      template<typename T1, typename T2, 
          typename Rt = std::decay_t<decltype(true ? std::declval<T1>() : std::declval<T2>())> >
      Rt max(T1&& t1, T2&& t2) 
      { return t1 > t2 ? t1 : t2; } 

  ```

  除了利用`decltype`防止将Rt推导为引用类型, 也可以使用`std::common_type<>`

  ```cpp
      #include<type_traits>

      template<typename T1, typename T2,
          typename Rt = std::common_type_t<T1, T2>>
      Rt max(T1&& t1, T2&& t2)
      { return t1 > t2 ? t1 : t2; }

  ```

- __1.5 模板重载__

    - 模板重载
        函数模板支持重载, 但是在重载过程中应注意最好不要进行超出必要的更改, 如按值传递却改成了按引用传递。
  以max模板为例, 在为 `const char *` 提供特化版本时有以下代码
  ```cpp
      template<typename T>
      const T& max(const T& a, const T& b) {
          return a > b ? a : b;
      }    

      const char * max(const char * a, const char * b) {
          return strcmp(a, b) >= 0 ? a : b;
      }

  ```

  注意重载版本的max返回的是一个右值, 即临时变量, 如果碰巧写出以下代码, 异常就会触发
  编译器甚至会警告这种暴行.

  ```cpp
      template<typename T>
      const T& max(const T& a, const T& b, const T& c) {
          return max(max(a, b), c);
      }
      
      int main(){ 
          max("a", "b", "c");
          return 0;
      }
      ...
  main.cpp: In instantiation of 'const T& max1(const T&, const T&, const T&) [with T = const char*]':
  main.cpp:33:22: required from here
  main.cpp:21:16: warning: returning reference to temporary [-Wreturn-local-addr]
       21 |     return max1(max1(a, b), c);
          |            ~~~~^~~~~~~~~~~~~~~

  ```
  - 模板函数的重载同普通重载匹配规则一致, 优先匹配相应类型否则进行隐式转换(如派生类->基类)
  


- __1.6 函数模板引发的思考__
    * 是按值传递还是按引用传递?
          <font face="楷体">
        按值传递的好处有:
        * 语法相对简单轻便
        * 编译器优化效果更好
        * 适配移动语义
        * 触发移动语义时几乎没有复制成本 

        相对于复杂类型, 一些廉价的类型(如内置类型或std::string_view)更推荐按值传递       
        </font>

    * 是否`inline`?
    * 是否`constexpr`? 
     
- __1.7 约束与概念__
    术语 __concept__ 是用来描述模板实例化时所需要支持的特定行为, 从C++20开始C++提供了`concept`关键字来描述这种
    行为。`requires` 来提供检测方法。  
     


<span id=Chapter2><!--第二章起始处--></span>

## 类模板

类模板与普通的类声明类似, 但仍然有不同之处, 比如类模板的定义与声明必须放在同意头文件, 
这是因为实例化是编译期的行为, 但多文件编译是链接时的行为。

- __2.1 类模板的实例化__
    类模板在实例化时, 会忽略未调用过的成员函数, 即不会给出定义, 只有一个简单的声明, 这使得类型
    实例化时如果模板中定义了不合适的方法, 编译过程并不会报错。 

- __2.2 类模板的友元__
    类模板允许有友元函数, 友元的声明有三种方式
    * 在类外定义 :
        ```cpp
            template<typename T>
            struct cls;
            template<typename T>
            void print_cls(const cls<T>& c);

            template<typename T>
            struct cls  {
                ...
                friend void print_cls<T>(const cls<T> & c) {
                    ...
                }
            };

        ```
    * 在类内定义
      ```cpp
            template<typename T>
            struct cls {
                ...
                friend void print_cls(const cls<T> & c) {
                    ...
                }
            };
      ``` 

    * 在类内声明
      ```cpp
        template<typename T>
        struct cls {
            ...
            template<typename U>
            friend void print_cls(const cls<U> & c);
        };

        template<typename U>
        friend void print_cls(const cls<U> & c) {
            ...
        }
      ``` 

- __2.3 使用using或typedef关键字简化类模板声明__
 
    `using`可以简化声明如
    ```cpp
        template<typename T1, typename T2>
        using P<T1,T2> = std::pair<T1, T2>;

        template<typename>
    ```  
    则模板`P<>`成为了`std::pair<>`的一个`alias`


- __2.4 C++17推导指引__
    为了满足特定类型的自动推导(如`const char *` -> `std::string`)
    C++ 17 添加了推导指引。可以通过对特定构造函数使用该语法来帮助模板参数的
    自动推导, 但注意不支持*copy initalization*。
    如对于自制stack类需要传入*string literal*时可以自动推导为`std::string`

    可以利用如下语法
    ```cpp 
        stack(const char *) -> stack<std::string>;
    ```

    通过构造函数推导类模板的参数可以更好的实现完美转发, 如要实现一个`scope_guard`类,
    它可以接受一些列可调用对象以及所需的参数, 在`scope_guard`作用域结束后被调用。利用
    推导指引可以实现参数的自动推导以及支持完美转发。
    下面是一个可能实现
    ```cpp
        template<typename Fn, typename...Args>
            requires std::invocable<Fn, Args...>
        struct scope_guard { 
            std::tuple<Args...> fn_args_list;
            Fn                  f;
            scope_guard(Fn fn, Args...args) : f{fn}, fn_args_list{args...}
            {}

            ~scope_guard() { std::apply(f, fn_args_list); }
            scope_guard(const scope_guard&)                  = delete;
            const scope_guard& operator=(consr scope_guard&) = delete;
        }
    ```
    使用上面方式会使得参数被多次复制, 效率显然会下降, 所以对于参数的存储需要完美转发, 但完美转
    发对于类模板的参数`Fn, Args...`来说, 使用`Fn&&, Args&&...`这种参数的构造函数只是单纯的右
    值引用而已, 并不是所谓的万能引用。为此需要单独提供一个模板参数。
    ```cpp
        template<typename Fn, typename...Args>
        scope_guard(Fn&& fn, Args&&...args) 
            : f{std::forward<Fn>(fn)}, fn_args_list{std::forward<Args>(args)...}
        {} 
    ```
    但是如果通过这种方式的声明C++17的模板自动推导就会无效, 需要自己提供模板参数。因此可以利用
    推导指引显示指明类模板参数。
    ```cpp
        template<typename Fn, typename...Args>
        scope_guard(Fn&& fn, Args&&...args) -> scope_guard<Fn&&, Args&&...>;
    ```
    这样编译器便可以自动推导相应类型并支持完美转发。
    推导指引对于聚合类的使用很有帮助。 
    聚合类(*aggregate class*)是指无保护或私有的非静态成员, 无虚函数, 虚拟或受保护, 私有的基类
    的这样一种对象。比如`std::array`便是一种聚合类, 对于`std::array`可以用如下声明方式。
    ```cpp
        std::array arr = {1, 0, 1, -1, 0, -1, 1};   // 自动推导为std::array<int>
    ```
    其实现方式也是利用C++17的推导指引。
    ```cpp
        template<typename T1, typename...Ts>
            requires (std::is_same_v<T1, TS> && ...)
        array(T1, Ts...) -> array<T1, 1 + sizeof(Ts)>; 
    ```


<span id=Capter3><!--第三章起始处--></span>

## 非参数模板

模板可以有固定参数, 但必须满足以下条件之一 :

<font face="楷体">

- 必须是恒定常量整型 
- 必须是类/变量/函数的指针或引用(对象必须具有静态存储周期)
- std::nullptr_t
  
</font> 

C++ 17以后支持利用`auto`声明非参数模板(__nontype template__)
```cpp
    template<auto a, typename T2>
        requires requires(a, T2) { a + T2(); }
    decltype(auto) add(T2&& t) 
    { return a + t; }
```

<span id=Chapter4><!--第四章--></span>

## 可变参数模板

- sizeof...()
  C++11以后支持使用符号`...`表示可变参数模板列表。
  同时提供了`sizeof...()`运算符, 用于在编译期求出参数包的模板参数数量。
  如我们要实现一个size_s_v模板, 它可以求出任意聚合类内的数据成员的数量, 便可以
  利用可变参数模板实现。 
  ```cpp
      struct Init_helper {
          template<typename T>
          operator T();  //  永远不会被调用
      };
      template<bool is_constructible, typename TS, typename...Init>
      struct size_impl { static constexpr int value = sizeof...(Init) - 2; }
      template<typename TS, typename...Init>
      struct size_impl<true, TS, Init...>
      { static constexpr int value = size_impl< requires { TS{ Init_helper{}... }; }, TS, Init..., Init_helper>::value; }
      template<typename TS>
          requires std::is_aggregate_v<TS>
      using size_s_v = size_impl< requires { TS{}; }, TS, Init_helper>::value;
  ```
  这里利用了模板特化进行递归增加成员数量, 并用sizeof...()运算符计算聚合对象总的数据成员数量, 是一个可变参数模板的
  应用例子。可变参数模板对于已经特化过的模板会优先匹配并不再自动生成。

- 折叠表达式(__Fold Experssion__)
   C++ 对于任何二元运算符支持折叠表达式。甚至是`->`运算符。
   ```cpp
        struct Node {
            int data;
            Node * left;
            Node * right;

            constexpr Node() : data {}, left {nullptr}, right {nullptr}
            {};
        };

        template<typename TNode, typename...TPath>
        void print_node_data(TNode * root, TPath...path) {
            auto node_data = &TNode::data;
            std::cout << ((root->* ... ->* path)->* node_data);
        }
   ```     
   这里利用了 *... op pack*的写法, 实际上折叠表达式有多种写法 :
    
    - *op*   : 操作符
    - *pack* : 参数包
    - *init* : 普通的对象

    | Fold Expression           | Evaluation                                       |
    |---------------------------|--------------------------------------------------|
    | *( ... op pack )*         | *((( pack1 op pack2 ) op pack3 ) ... op packN )* |
    | *( pack op ... )*         | *( pack1 op ( ... ( packN-1 op packN )))*        |
    | *( init op ... op pack )* | *((( init op pack1 ) op pack2 ) ... op packN )*  |
    | *( pack op ... op init )* | *( pack1 op ( ... ( packN op init )))*           |
    | *({(pack op init)...})*   | *( {pack1 op init, pack2 op init, ..., packN op init} )*|

   同时这种折叠还可以出现在编译期对于类型擦除后对象行为的推导判断中
   ```cpp
        if constexpr (std::is_same_v<T, int> && ...) // since c++17
        {...}
   ```
   对下标的访问中。
   ```cpp
    template<typename vec_type, std::size_t...N>
    void print_arr(std::vector<vec_type>& arr, TCG::range_index_sequence<N...>) // TCG::range_index_sequence 可以按顺序得到一组范围内的数
    { print_arr_impl(arr[N]...); }
   ```

- 可变参数模板与类
  类模板自然可以用可变参数, 如 `std::variant` 、 `std::tuple`
  


</font><!--全局华文中宋-->



