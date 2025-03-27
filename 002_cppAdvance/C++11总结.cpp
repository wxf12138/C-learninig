/* 
    C++11总结
    一、关键字和语法
    auto：可以根据右值，推出左边变量类型
    nullptr：指针专用，空指针，可以和整型进行区别
    foreach：可以遍历数组、容器等
    右值引用：move移动语义函数和forward类型完美转发函数 
    模板新特性：typename...A 可变参
    二、函数对象和绑定器
    function： 函数对象 
    bind：绑定器 bind1st 和 bind2nd 二元对象函数 —》 一元函数对象
    lambda表达式
    三、智能指针
    shared_ptr：共享指针，可以多个对象共享一个指针，析构时自动释放
    weak_ptr：弱指针，不能被自动释放，只能通过shared_ptr获取
    四、容器
    unordered_map：无序map，可以快速查找，但是不能保证顺序
    unordered_set：无序set，可以快速查找，但是不能保证顺序
    ordered_map：有序map，可以快速查找，并且保证顺序
    ordered_set：有序set，可以快速查找，并且保证顺序
    array
    forward_list：前向链表，可以快速插入和删除
    五、语言级别支持的多线程
    win: createThread
    linux: pthread_create
    clone
*/