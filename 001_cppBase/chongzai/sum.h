//只要是c++编译器，都内置了__cplusplus 这个宏

#ifdef __cplusplus
extern "C" {
#endif

// C语言函数声明
int sum(int a, int b);

#ifdef __cplusplus
}
#endif
