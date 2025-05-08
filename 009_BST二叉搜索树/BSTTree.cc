#include <iostream>
#include <functional>
#include <cmath>
using namespace std;

template <typename T, typename Comp = less<T>>
class BSTTree
{
public:
    BSTTree(Comp comp = Comp())
        : root_(nullptr)
        , comp(comp)
    {
    }
    ~BSTTree() {}
    // 非递归插入
    void n_insert(const T &val)
    {
        if (root_ == nullptr)
        {
            root_ = new Node(val);
            return;
        }
        Node *parent = nullptr;
        Node *cur = root_;
        while (cur != nullptr)
        {
            if (cur->data_ == val)
            {
                return;
            }
            if (!comp(cur->data_, val))
            {
                parent = cur;
                cur = cur->left_;
            }
            else if (comp(cur->data_, val))
            {
                parent = cur;
                cur = cur->right_;
            }
        }
        if (comp(val, parent->data_))
        {
            parent->left_ = new Node(val);
        }
        else
        {
            parent->right_ = new Node(val);
        }
    }

    // 递归插入操作用户接口
    void insert(const T &val)
    {
        root_ = insert(root_, val);
    }

    // 递归查询操作用户接口
    bool query(const T &val)
    {
        return nullptr != query(root_, val);
    }

    void remove(const T &val)
    {
        root_ = remove(root_, val);
    }
    // 非递归删除
    void n_delete(const T &val)
    {
        if (root_ == nullptr)
        {
            return;
        }

        Node *parent = nullptr;
        Node *cur = root_;
        while (cur != nullptr)
        {
            if (comp(val, cur->data_))
            {
                parent = cur;
                cur = cur->left_;
            }
            else if (comp(cur->data_, val))
            {
                parent = cur;
                cur = cur->right_;
            }
            else
            {
                break;
            }
        }
        // 未找到删除节点
        if (cur == nullptr)
        {
            return;
        }

        // 待删除节点有两个孩子
        if (cur->left_ != nullptr && cur->right_ != nullptr)
        {
            // 获取前驱节点
            parent = cur;
            Node *pre = cur->left_;
            while (pre->right_ != nullptr)
            {
                parent = pre;
                pre = pre->right_;
            }
            cur->data_ = pre->data_;
            cur = pre; // 转换为删除只有一个孩子节点的情况
        }
        // cur指向删除节点，parent指向其父节点，统一处理curr指向的节点
        Node *child = cur->left_;
        if (child == nullptr) // 统一转化为无子节点的情况 左右都为空
        {
            child = cur->right_;
        }

        if (parent == nullptr) // 删除的是根节点
        {
            root_ = child;
        }
        else
        {
            // 把待删除节点的孩子孩子节点写入其父节点(待删除)相应地址位
            if (parent->left_ == cur)
            {
                parent->left_ = child;
            }
            else
            {
                parent->right_ = child;
            }
        }
        delete cur;
    }

    // 非递归查询
    bool non_query(const T &val)
    {
        Node *cur = root_;
        while (cur != nullptr)
        {
            if (cur->data_ == val)  
            {
                return true;
            }
            else if (comp(cur->data_, val))
            {
                cur = cur->right_;
            }
            else
            {
                cur = cur->left_;
            }
        }
        return false;
    }

    void preOrder()
    {
        cout << "前序遍历: ";
        preOrder(root_);
        cout << endl;
    }
    void inOrder()
    {
        cout << "中序遍历: ";
        inOrder(root_);
        cout << endl;
    }
    void postOrder()
    {
        cout << "后序遍历: ";
        postOrder(root_);
        cout << endl;
    }

    void levelOrder()
    {
        cout << "层序遍历: ";
        int h = level();

        for (int i = 0; i < h; ++i)
        {
            levelOrder(root_, i); //递归调用层数
        }
        cout << endl;
    }

    int level()
    {
        return level(root_);
    }

private:
    struct Node
    {
        Node(T data = T())
            : data_(data), left_(nullptr), right_(nullptr)
        {
        }
        T data_;
        Node *left_;
        Node *right_;
    };
 
    // 递归前序遍历实现 VLR
    void preOrder(Node* node)
    {
        if (node != nullptr)
        {
            cout << node->data_ << " ";
            preOrder(node->left_);
            preOrder(node->right_);
        }
    }

    // 递归中序遍历实现 LVR
    void inOrder(Node* node)
    {
        if (node != nullptr)
        {
            inOrder(node->left_);
            cout << node->data_ << " ";
            inOrder(node->right_);
        }
    }

    // 递归后序遍历实现 RLV
    void postOrder(Node* node)
    {
        if (node != nullptr)
        {
            postOrder(node->left_);
            postOrder(node->right_);
            cout << node->data_ << " ";
        }
    }

    // 求高度， 以node为根节点的子树的高度
    int level(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        int left = level(node->left_);
        int right = level(node->right_);
        return left > right ? left + 1 : right + 1; 
    }

    // 求树的节点数实现接口
    int number(Node* node)
    {
        if (node == nullptr)   
            return 0;
        int left = number(node->left_);
        int right = number(node->right_);
        return left + right + 1;
    }

    // 递归层序遍历的实现
    void levelOrder(Node* node , int i)
    {
        if (node == nullptr)
            return;
        if (i == 0)
        {
            cout << node->data_ << " ";
            return;
        }
        levelOrder(node->left_, i - 1);
        levelOrder(node->right_, i - 1);
    }

    // 递归插入实现接口
    Node* insert(Node* node, const T &val)
    {
        if(node == nullptr)
        {
            // 递归结束，找到val的位置，生成新节点并返回其节点
            return new Node(val);
        }
        if (node->data_ == val)
        {
            return node;
        }
        else if(comp(node->data_, val))
        {
            node->right_ = insert(node->right_, val);
            return node;
        }
        else
        {
            node->left_ = insert(node->left_, val);
            return node;
        }
    }

    // 递归查询功能的实现
    Node* query(Node* node, int val)
    {
        if (node == nullptr)
            return nullptr;
        if (node->data_ == val)
        {
            return node;
        }
        else if (comp(node->data_, val))
        {
            node->right_ = query(node->right_, val);
        }
        else
        {
            node->left_ = query(node->left_, val);
        }
    }

    // 递归删除操作的实现
    Node* remove(Node *node, const T &val)
    {
        if (node == nullptr)
            return nullptr;
        if (node->data_ == val)
        {
            // 要删除节点有两个孩子
            if (node->left_ != nullptr && node->right_ != nullptr) 
            {
                // 找前驱节点
                Node* pre = node->left_;
                while (pre->right_ != nullptr)
                {
                    pre = pre->right_;
                }
                node->data_ = pre->data_;
                // 通过递归直接删除前驱节点
                node->left_ = remove(node->left_, pre->data_);
            }
            else // 要删除节点有一个孩子
            {
                if (node->left_ != nullptr)
                {
                    Node* left = node->left_;
                    delete node;
                    return left;
                }
                else if (node->right_ != nullptr)
                {
                    Node* right = node->right_;
                    delete node;
                    return right;
                }
                else // 没孩子
                {
                    delete node;
                    return nullptr;
                }
            }
        }
        else if (comp(node->data_, val))
        {
            node->right_ = remove(node->right_, val);
        }
        else
        {
            node->left_ = remove(node->left_, val);
        }
        return node; // 把当前节点返回给父节点， 更新父节点相应的地址域
    }
    
    Node *root_;
    Comp comp;
};

int main()
{
    int arr[] = {58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78};
    BSTTree<int> bst;
    for (int v : arr)
    {
        bst.insert(v);
    }

//    cout <<  bst.non_query(58) << endl;
//    cout <<  bst.non_query(27) << endl;

    cout << bst.query(58) << endl;
    bst.remove(34);

    bst.preOrder();
    bst.inOrder();
    bst.postOrder();

    bst.levelOrder();
}