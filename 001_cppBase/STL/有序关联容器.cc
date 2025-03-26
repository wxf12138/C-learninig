/*
    一、 标准容器
    1. 顺序容器
    vector
    deque
    list
    2. 容器适配器
    stack
    queue
    priority_queue
    3. 关联容器
    无序关联容器 -》 链式哈希表 增删查 O(1)
    set: 集合 key  map： 映射表 key-value
    unordered_set 单重集合
    unordered_map 单重映射表
    undored_multiset 多重集合
    unordered_multimap 多重映射表

    有序关联容器 -》 二叉树（红黑树） 增删查 O(log2N)
    set
    multiset
    map
    multimap
 */

#include <iostream>
#include <vector>
#include <unordered_map>
// 使用有序关联容器包含的头文件
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdlib>
// 使用无需关联容器包含的头文件
#include <unordered_set>
#include <unordered_map>
#include <deque>
using namespace std;
/*
     关联容器：
     1. 各个容器底层的数据结构 O(1) O(logN)
     2. 常用增删查方法
     增加： insert（val）
     遍历： iterator自己搜索，调用find成员方法
     删除： erase(val) erase(iterator)
 */
class Student
{
    public:
    Student(int id, string name)
        :_id(id), _name(name)
    {}

    bool operator<(const Student& s) const
    {
        return this->_id < s._id;
    }
    private:
    int _id;
    string _name;
    friend ostream& operator<<(ostream& out, const Student& stu);
};
ostream& operator<<(ostream& out, const Student& stu)
{
    out << "id:" << stu._id << " name:" << stu._name;
    return out;
}

int main()
{

    set<Student> set1;
    set1.insert(Student(1005, "zhangsan"));
    set1.insert(Student(1001, "lisi"));
    for (auto it = set1.begin(); it != set1.end(); it++)
    {
        cout << *it << endl;
    }
    // map<int, Student> map1;
    // map1.insert({1000, Student(1000, "zhangsan")});
    // map1.insert({1001, Student(1001, "lisi")});
    // for (auto it = map1.begin(); it != map1.end(); it++)
    // {
    //     cout << it->first << ":" << it->second << endl;
    // }
    
    /* set<int> set1;
    for (size_t i = 0; i < 20; i++)
    {
        set1.insert(rand() % 20 + 1);
    }
    
    for (int v : set1)
    {
        cout << v << " ";
    }
    cout << endl;
    return 0; */
}