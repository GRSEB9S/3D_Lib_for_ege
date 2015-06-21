## Welcome to the 3D_Lib_for_ege wiki!

* [��������Ԫ](#��������Ԫ)
    * [����](#����)
        * [��](#�����)
        * [����](#��������)
        * [���캯��](#�����캯��)
        * [����������](#�������������)
        * [����](#������)
    * ����
        * �������Ա任������
        * ���ڷ���任��ͶӰ�任������
    * ��

# ��������Ԫ

## ����

### �����

**IDENTITY_MATRIX  1**
���ڳ�ʼ����λ���󣬵��ҽ�������Ϊ����

**D_TYPE  double**
����Ĭ��ʹ�õĻ�Ԫ����

### ��������

```c++
template < int l, int m, typename T = D_TYPE >
class matrix;
```

### �����캯��

Ĭ�Ϲ��캯���ṹ��**�����**������ʹ�ú�`IDENTITY_MATRIX`����**��λ����**
```c++
matrix< l, m, T> ( const int opt = 0 );
```

* opt: �������

***

��ʼ�����캯��
```c++
matrix< l, m, T > ( const T src[l][m] );
```
* src: ������������Ԫ�صĶ�λ�������

***

�������캯��
```c++
matrix< l, m, T > ( const matrix < l, m, T >& src );
```

* src: ͬ�׾���

***

��ʼ�����캯��
```c++
matrix < l, m, T > ( const std::initializer_list< std::initializer_list< T > >& src )
```

* src: ��ά��ʼ���б�����C++11�﷨����ʹ�ø��򵥵ķ�ʽ��ʼ���������磺

```c++
matrix< 3, 3 > item {
    { 1, 2, 4 },
    { 2, 4, 8 },
    { 4, 8, 16 },
};
```

### �������������

�����±������
```c++
T* operator [] ( const int opt ) const 
```

* opt: �±�

***

���ظ�ֵ�����
```c++
matrix < l, m, T >& operator = ( const matrix < l, m, T >& opt ) 
```

* opt: ͬ�׾���

***

������ȱȽ�����������󲻴���˳�����У��ʶ�δ����<��>��<=��>=��
```c++
bool operator == ( const matrix < l, m, T >& opt ) const
```

* opt: ͬ�׾���

***

���ؼӷ������
```c++
matrix < l, m, T > operator + ( const matrix < l, m, T >& opt ) const
```

* opt: ͬ�׾���

***

���ؼ��������
```c++
matrix < l, m, T > operator - ( const matrix < l, m, T >& opt ) const 
```

* opt: ͬ�׾���

***

�����������������
```c++
matrix < l, m, T > operator * ( T opt ) const 
```

* opt: ����Ԫ

***

���س˷������
```c++
template < int n >
matrix < l, n, T > operator * ( const matrix < m, n, T >& opt ) const 
```

* opt: ������Դ����������ȵľ���

***

�����������������
```c++
matrix < l, m, T > operator / ( T opt ) const 
```

* opt: ����Ԫ

***

�������������**�� `opt == -1` ʱ���о�����������**��
```c++
matrix < l, m, T > operator ^ ( int opt ) const 
```

* opt: �ݴ�

### ������

�����Ӧ����ʽ��ֵ�����ҽ�������Ϊ����
```c++
T det() const 
```

***

����ת��
```c++
matrix< m, l > trans() const 
```

***

**��̬����** �����Ӧ����ʽ��ֵ�����ҽ�������Ϊ����
```c++
template < int o >
static T det ( const matrix < o, o, T >& opt);
```

opt: ��ֵ����

***

**��̬����** ��������ʽ�����ҽ�������Ϊ����
```c++
template < int o >
static matrix < o - 1, o - 1, T > cofactor ( const matrix < o, o, T >& opt, int r, int c )
```

* opt: ��ֵ����
* r: ����ʽȥ���кţ���0��ʼ��
* c: ����ʽȥ���кţ���0��ʼ��

***

**��̬����** ����ת��
```c++
template < int o, int p >
static matrix < p, o, T > trans ( const matrix < o, p, T >& opt ) 
```

* opt: ��ֵ����

***

**��̬����** ��������
```c++
template < int o >
static matrix < o, o, T > inv ( const matrix < o, o, T >& opt ) 
```

* opt: ��ֵ����

***