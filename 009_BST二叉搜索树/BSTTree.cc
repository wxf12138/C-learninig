#include <iostream>
#include <functional>
#include <cmath>
#include <stack>
#include <queue>
#include <string>
#include <vector>
using namespace std;

template <typename T, typename Comp = less<T>>
class BSTTree
{
public:
    // 初始化根节点和函数对象 + lamda表达式
    BSTTree(Comp comp = Comp())
        : root_(nullptr)
        , comp(comp)
    {}
    ~BSTTree() 
    {
        if (root_ != nullptr)
        {
            queue<Node*> que;
            que.push(root_);
            while (!que.empty())
            {
                Node* front = que.front();

                if (front->left_ != nullptr)
                {
                    que.push(front->left_);
                }
                if (front->right_ != nullptr)
                {
                    que.push(front->right_);
                }
                delete front;
                que.pop();
            }
        }
    }

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
    // 递归删除
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
        if (child == nullptr) 
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

    // 递归遍历方法
    void preOrder()
    {
        cout << "[递归]前序遍历: ";
        preOrder(root_);
        cout << endl;
    }
    void inOrder()
    {
        cout << "[递归]中序遍历: ";
        inOrder(root_);
        cout << endl;
    }
    void postOrder()
    {
        cout << "[递归]后序遍历: ";
        postOrder(root_);
        cout << endl;
    }
    void levelOrder()
    {
        cout << "[递归]层序遍历: ";
        int h = level();

        for (int i = 0; i < h; ++i)
        {
            levelOrder(root_, i); //递归调用层数
        }
        cout << endl;
    }


    // 非递归遍历方法
    void n_preOrder()
    {
        cout << "[非递归]前序遍历: ";
        if (root_ == nullptr)
            return;
        stack<Node*> s;
        s.push(root_);
        while (!s.empty())
        {
            Node* top = s.top();
            s.pop();
            cout << top->data_ <<" ";

            if (top->right_ != nullptr)
            {
                s.push(top->right_);
            }
            
            if (top->left_ != nullptr)
            {
                s.push(top->left_);
            }
        }
        
        cout << endl;
    }

    void n_inorder() // LVR
    {
        cout << "[非递归]中序遍历: ";
        if (root_ == nullptr)   
        {
            return;
        }  
        stack<Node*> s;
        Node* cur = root_;

        while(!s.empty() || cur != nullptr)
        {
            if (cur != nullptr)// 找到最左边的叶子节点
            {
                s.push(cur);
                cur = cur->left_;
            }
            else // 找到最左边节点可以输出了，并且遍历右节点的左孩子
            {
                Node* top = s.top(); // 取栈顶元素 相当于回溯
                cout << top->data_ << " "; 
                s.pop(); // 出栈 开始寻找右节点
                cur = top->right_;
            }
        }
        cout << endl;
    }

    // 因为后序遍历LRV时L遍历后要出栈，如果右子树有数据，会无法访问，因此采用LRV -> VRL， 需要两个栈
    void n_postOrder()
    {
        cout << "[非递归]后序遍历: ";
        if (root_ == nullptr)   
        {
            return;
        }  
        stack<Node*> s1;
        stack<Node*> s2;
        s1.push(root_);
        while (!s1.empty())
        {
            Node* top = s1.top();
            s1.pop();

            s2.push(top);
            if (top->left_ != nullptr)
            {
                s1.push(top->left_);
            }

            if (top->right_ != nullptr)
            {
                s1.push(top->right_);
            }
        }
        
        while (!s2.empty())
        {
            cout << s2.top()->data_<< " ";
            s2.pop();
        }
        
        cout << endl;
    }

    void n_levelOrder()
    {
        cout << "[非递归]层序遍历:";
		if (root_ == nullptr)
		{
			return;
		}
		queue<Node*> que;
		que.push(root_);
        while (!que.empty())
        {
            Node* front = que.front();
            cout << front->data_ << " ";
            que.pop();
            if (front->left_ != nullptr)
            {
                que.push(front->left_);
            }
            if (front->right_ != nullptr)
            {
                que.push(front->right_);
            }
        }
        cout << endl;
    }
   
    // 求层数
    int level()
    {
        return level(root_);
    }

    // 求满足区间元素的值
    void findValues(vector<T> &vec, int i, int j)
    {
        findValues(root_, vec, i, j);
    }

    // 判断二叉树是否为BST树
    bool isBSTTree()
    {
        Node* pre = nullptr;
        return isBSTTree(root_, pre);
    }

    // 子树判断问题
    bool isChildTree(BSTTree<T, Comp>& child)
	{
		// 在当前二叉树上找child的根节点
		if (child.root_ == nullptr)
		{
			return true;
		}

		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->data_ == child.root_->data_)
			{
				break;
			}
			else if (comp(cur->data_, child.root_->data_))
			{
				cur = cur->right_;
			}
			else
			{
				cur = cur->left_;
			}
		}
		if (cur == nullptr)
		{
			return false;
		}
		return isChildTree(cur, child.root_);
	}

    // 最近公共祖先节点
	int getLCA(int val1, int val2)
	{
		Node* node = getLCA(root_, val1, val2);
		if (node == nullptr)
		{
			throw "no LCA!";
		}
		else
		{
			return node->data_;
		}
	}

    // 镜像翻转
	void mirror01()
	{
		mirror01(root_);
	}

    // 镜像对称
    bool mirror02()
	{
		if (root_ == nullptr)
			return true;
		return mirror02(root_->left_, root_->right_);
	}
public:
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
    
    // 求满足区间的元素值[i, j] 实现
    void findValues(Node* node,vector<T> &vec, int i, int j)
    {
        if (node != nullptr)
		{
			// 在当前节点的左子树中搜索
			if (node->data_ > i)
			{
				findValues(node->left_, vec, i, j); // L
			}

			if (node->data_ >= i && node->data_ <= j)// V
			{
				vec.push_back(node->data_); // 存储满足区间元素的值
			}

			// 在当前节点的右子树中搜索
			if (node->data_ < j)
			{
				findValues(node->right_, vec, i, j); // R
			}
		}
    }
    
    // 判断二叉树是否是BST树的实现 利用BST树中序遍历是一个升序的特点
    bool isBSTTree(Node* node, Node*& pre)
    {
        if (node == nullptr)
        {
            return true;
        }

        if(!isBSTTree(node->left_, pre)) // L
        {
            return false;
        }
        // V
        if (pre != nullptr)
        {
            if(comp(node->data_, pre->data_))
            {
                return false;
            }
        }
        pre = node; // 更新中序遍历的前驱节点
        return isBSTTree(node->right_, pre); // R
    }

    // 判断子树问题实现
	bool isChildTree(Node* father, Node* child)
	{
		if (father == nullptr && child == nullptr)
		{
			return true;
		}

		if (father == nullptr) // 子树里面有的节点，当前二叉树没有
		{
			return false;
		}

		if (child == nullptr)
		{
			return true;
		}

		// 判断值不相同
		if (father->data_ != child->data_)  // V
		{
			return false;
		}

		return isChildTree(father->left_, child->left_) // L
			&& isChildTree(father->right_, child->right_); // R
	}

    // 最近公共祖先节点实现
	Node* getLCA(Node* node, int val1, int val2)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		if (comp(node->data_, val1) && comp(node->data_, val2))
		{
			return getLCA(node->right_, val1, val2);
		}
		else if (comp(val1, node->data_) && comp(val2, node->data_))
		{
			return getLCA(node->left_, val1, val2);
		}
		else
		{
			return node;
		}
	}
    // 镜像翻转
	void mirror01(Node* node)
	{
		if (node == nullptr)
			return;

		// V
		Node* tmp = node->left_;
		node->left_ = node->right_;
		node->right_ = tmp;

		mirror01(node->left_);  // L
		mirror01(node->right_); // R
	}

    // 镜像对称
	bool mirror02(Node* node1, Node* node2)
	{
		if (node1 == nullptr && node2 == nullptr)
		{
			return true;
		}
		if (node1 == nullptr || node2 == nullptr)
		{
			return false;
		}
		if (node1->data_ != node2->data_)
		{
			return false;
		}
		return mirror02(node1->left_, node2->right_)
			&& mirror02(node1->right_, node2->left_);
	}
    Node *root_;
    Comp comp;
};
 
void test01() // 测试是否是BST树
{
    using Node = BSTTree<int>::Node;
    BSTTree<int> bst;
	bst.root_ = new Node(40);
	Node* node1 = new Node(20);
	Node* node2 = new Node(60);
	Node* node3 = new Node(30);
	Node* node4 = new Node(80);

	bst.root_->left_ = node1;
	bst.root_->right_ = node2;
	node2->left_ = node3;
	node2->right_ = node4;

    cout << bst.isBSTTree() << endl;
}

void test02() // 测试子树判断问题
{
	int ar[] = { 58,24,67,0,34,62,69,5,41,64,78 };
	BSTTree<int> bst;
	for (int v : ar)
	{
		bst.insert(v);
	}

	using Node = BSTTree<int>::Node;
	BSTTree<int> bst1;
	bst1.root_ = new Node(67);
	Node* node1 = new Node(62);
	Node* node2 = new Node(69);
	Node* node3 = new Node(60);
	bst1.root_->left_ = node1;
	bst1.root_->right_ = node2;
	node1->left_ = node3;

	cout << bst.isChildTree(bst1) << endl;
}

void test03() // 测试LCA问题
{
	int ar[] = { 58,24,67,0,34,62,69,5,41,64,78 };
	BSTTree<int> bst;
	for (int v : ar)
	{
		bst.insert(v);
	}

	cout << bst.getLCA(64, 41) << endl;
}

void test04() // 测试镜像对称
{
	using Node = BSTTree<int>::Node;
	BSTTree<int> bst;
	bst.root_ = new Node(40);
	Node* node1 = new Node(20);
	Node* node2 = new Node(20);
	Node* node3 = new Node(10);
	Node* node4 = new Node(15);
	Node* node5 = new Node(15);
	Node* node6 = new Node(10);

	bst.root_->left_ = node1;
	bst.root_->right_ = node2;
	node1->left_ = node3;
	node1->right_ = node4;
	node2->left_ = node5;
	//node2->right_ = node6;

	cout << bst.mirror02() << endl;
}

int main()
{
    test04();
    // using Elm = pair<int, string>;
    // using Functor = function<bool(Elm, Elm)>;
    // BSTTree<Elm, Functor> bst([](Elm p1, Elm p2)->bool{
    //     return p1.first > p2.first;
    // });
    // int arr[] = {58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78};
    // BSTTree<int> bst;
    // for (int v : arr)
    // {
    //     bst.insert(v);
    // }

    // bst.inOrder();
	// bst.mirror01();
	// bst.inOrder();

    // vector<int> vec;
    // bst.findValues(vec, 10, 60);
	// for (int v : vec)
	// {
	// 	cout << v << " ";
	// }
	// cout << endl;
// //    cout <<  bst.non_query(58) << endl;
// //    cout <<  bst.non_query(27) << endl;

//     cout << bst.query(58) << endl;
//     bst.remove(34);

//     bst.preOrder();
//     bst.n_preOrder();
//     bst.inOrder();
//     bst.n_inorder();
//     bst.postOrder();
//     bst.n_postOrder();

//     bst.levelOrder();
//     bst.n_levelOrder();
}