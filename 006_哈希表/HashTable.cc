#include <iostream>
using namespace std;

// 桶的状态
enum State
{
    STATE_UNUSE,
    STATE_USING,
    STATE_DELETE,   
};

// 定义桶的类型
struct Bucket
{
    Bucket(int key = 0, State state = STATE_UNUSE)
    : key_(key)
    , state_(state)
    {}
    int key_;
    State state_;
};

// 线性探测哈希表类型
class HashTable
{
public:
    HashTable(int size = primes_[0], double loadFactor = 0.75)
    : useBucketNum_(0)
    , loadFactor_(loadFactor)
    , primeIdx_(0)
    {
        // 把用户传入的size调整到最近的比较大的素数上
        if (size != primes_[0])
        {
            for (; primeIdx_ < PRIME_SIZE; primeIdx_++)
            {
                if (primes_[primeIdx_] >= size)
                {
                    break;
                }
            }
            // 用户传入的size值过大，已经超过最后一个素数，调整到最后一个素数
			if (primeIdx_ == PRIME_SIZE)
			{
				primeIdx_--;
			}
        }
        tableSize_ = primes_[primeIdx_];
        table_ = new Bucket[tableSize_];
    }
    
	~HashTable()
	{
		delete[]table_;
		table_ = nullptr;
	}
public:
    bool insert(int key)
    {
        // 考虑扩容
        double factor = useBucketNum_*1.0 / tableSize_;
        cout << "factor: " << factor << endl;
        if (factor > loadFactor_)
        {
            expand();
            cout << "expand() is used" << endl;
        }

        int idx = key % tableSize_;
        int i = idx;
        // key空闲
        do
        {
            if (table_[i].state_ != STATE_USING)
            {
                table_[i].state_ = STATE_USING;
                table_[i].key_ = key;
                useBucketNum_++;
                return true;
            }
            i = (i + 1) % tableSize_;            
        }while(i != idx);

        return false;
    }

    bool erase(int key)
    {
        int idx = key % tableSize_;
        int i = idx;
        bool erased = false; // 标记是否成功删除过元素

        do
        {
            if (table_[i].key_ == key && table_[i].state_ == STATE_USING)
            {
                table_[i].state_ = STATE_DELETE;
                useBucketNum_--;
                erased = true; // 成功删除一个
            }
            i = (i + 1) % tableSize_;
        } while (table_[i].state_ != STATE_UNUSE && i != idx); // STATE_UNUSE代表后面都是空闲位置不需要继续判断 既判断所有
        return erased; // 最后根据有没有删除过元素返回
    }

    bool find(int key)
    {
        int idx = key % tableSize_;
        int i = idx;
        do
        {
            if (table_[i].state_ == STATE_USING && table_[i].key_ == key)
            {
                return true;
            }
            i = (i + 1) % tableSize_;
        } while (table_[i].state_ != STATE_UNUSE && i != idx);
        return false;
    }

private:
    void expand()
    {
        ++primeIdx_;
        if (primeIdx_ == PRIME_SIZE)
        {
			throw "HashTable is too large, can not expand anymore!";
        }

        Bucket* newTable = new Bucket[primes_[primeIdx_]];
        for (int i = 0; i < tableSize_; i++)
        {
            if (table_[i].state_ == STATE_USING)
            {
                int idx = table_[i].key_ % primes_[primeIdx_];// 旧表有效的数据，重新哈希放到扩容后的新表
                int k = idx;
                do
                {
                    if (newTable[k].state_ != STATE_USING)
                    {
                        newTable[k].state_ = STATE_USING;
                        newTable[k].key_ = table_[i].key_;
                        break;
                    }
                    k = (k + 1) % primes_[primeIdx_];   
                } while (k != idx);
            }
        }

        delete[] table_;
        table_ = newTable;
        tableSize_ = primes_[primeIdx_];
    }
private:
    Bucket* table_; // 指向动态开辟的哈希表
    int tableSize_; // 哈希表当前长度， 用于哈希取模运算
    int useBucketNum_; // 已经使用桶的个数
    double loadFactor_; // 哈希表装载因子 
    static const int PRIME_SIZE = 10; // 素数表的大小
	static int primes_[PRIME_SIZE];   // 素数表
	int primeIdx_; // 当前使用的素数下标
};

int HashTable::primes_[PRIME_SIZE] = { 3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773 };

int main()
{
    HashTable htable;
	htable.insert(21);
	htable.insert(32);
	htable.insert(14);
	htable.insert(15);

	htable.insert(22);

	cout << htable.find(14) << endl;
	htable.erase(14);
	cout << htable.find(14) << endl;
}