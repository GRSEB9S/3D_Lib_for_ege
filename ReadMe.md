## Welcome to the 3D_Lib_for_ege wiki!

* [基本运算元](#基本运算元)
    * [矩阵](#矩阵)
        * [宏](#矩阵宏)
        * [声明](#矩阵声明)
        * [构造函数](#矩阵构造函数)
        * [操作符重载](#矩阵操作符重载)
        * [函数](#矩阵函数)
    * 向量
        * 基于线性变换的向量
        * 基于仿射变换与投影变换的向量
    * 点

# 基本运算元

## 矩阵

### 矩阵宏

**IDENTITY_MATRIX  1**
用于初始化单位矩阵，当且仅当矩阵为方阵

**D_TYPE  double**
矩阵默认使用的基元类型

### 矩阵声明

```c++
template < int l, int m, typename T = D_TYPE >
class matrix;
```

### 矩阵构造函数

默认构造函数会构造**零矩阵**，允许使用宏`IDENTITY_MATRIX`构造**单位矩阵**
```c++
matrix< l, m, T> ( const int opt = 0 );
```

* opt: 构造参数

***

初始化构造函数
```c++
matrix< l, m, T > ( const T src[l][m] );
```
* src: 包含矩阵所有元素的二位数组变量

***

拷贝构造函数
```c++
matrix< l, m, T > ( const matrix < l, m, T >& src );
```

* src: 同阶矩阵

***

初始化构造函数
```c++
matrix < l, m, T > ( const std::initializer_list< std::initializer_list< T > >& src )
```

* src: 二维初始化列表，利用C++11语法允许使用更简单的方式初始化矩阵。例如：

```c++
matrix< 3, 3 > item {
    { 1, 2, 4 },
    { 2, 4, 8 },
    { 4, 8, 16 },
};
```

### 矩阵操作符重载

重载下标运算符
```c++
T* operator [] ( const int opt ) const 
```

* opt: 下标

***

重载赋值运算符
```c++
matrix < l, m, T >& operator = ( const matrix < l, m, T >& opt ) 
```

* opt: 同阶矩阵

***

重载相等比较运算符（矩阵不存在顺序序列，故而未重载<、>、<=、>=）
```c++
bool operator == ( const matrix < l, m, T >& opt ) const
```

* opt: 同阶矩阵

***

重载加法运算符
```c++
matrix < l, m, T > operator + ( const matrix < l, m, T >& opt ) const
```

* opt: 同阶矩阵

***

重载减法运算符
```c++
matrix < l, m, T > operator - ( const matrix < l, m, T >& opt ) const 
```

* opt: 同阶矩阵

***

重载数乘运算运算符
```c++
matrix < l, m, T > operator * ( T opt ) const 
```

* opt: 矩阵单元

***

重载乘法运算符
```c++
template < int n >
matrix < l, n, T > operator * ( const matrix < m, n, T >& opt ) const 
```

* opt: 行数与源矩阵列数相等的矩阵

***

重载数除除法运算符
```c++
matrix < l, m, T > operator / ( T opt ) const 
```

* opt: 矩阵单元

***

重载幂运算符（**当 `opt == -1` 时进行矩阵求逆运算**）
```c++
matrix < l, m, T > operator ^ ( int opt ) const 
```

* opt: 幂次

### 矩阵函数

矩阵对应行列式求值（当且仅当矩阵为方阵）
```c++
T det() const 
```

***

矩阵转置
```c++
matrix< m, l > trans() const 
```

***

**静态方法** 矩阵对应行列式求值（当且仅当矩阵为方阵）
```c++
template < int o >
static T det ( const matrix < o, o, T >& opt);
```

opt: 求值矩阵

***

**静态方法** 矩阵余子式（当且仅当矩阵为方阵）
```c++
template < int o >
static matrix < o - 1, o - 1, T > cofactor ( const matrix < o, o, T >& opt, int r, int c )
```

* opt: 求值矩阵
* r: 余子式去行行号（从0开始）
* c: 余子式去列列号（从0开始）

***

**静态方法** 矩阵转置
```c++
template < int o, int p >
static matrix < p, o, T > trans ( const matrix < o, p, T >& opt ) 
```

* opt: 求值矩阵

***

**静态方法** 矩阵求逆
```c++
template < int o >
static matrix < o, o, T > inv ( const matrix < o, o, T >& opt ) 
```

* opt: 求值矩阵

***