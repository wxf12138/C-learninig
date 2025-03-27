//深度优先遍历 -》 栈
//广度优先遍历 --》 层层扩张  --》 队列

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

const int RIGHT = 0;
const int DOWN = 1;
const int LEFT = 2;
const int UP = 3;

//每个结点的方向数量
const int WAY_NUM = 4;

//节点行走状态
const int YES = 4;
const int NO = 5;

class Maze
{
public:
    Maze(int row, int col)
        :_rows(row)
        ,_cols(col)
    {
        _pMaze = new Node*[_rows];//申请二维数组
        for (int i = 0; i < _rows; ++i)
        {
            _pMaze[i] = new Node[_cols];
        }
        _pPath.resize(_rows * _cols);
    }

    void initNode(int x, int y, int data)
    {
        _pMaze[x][y]._x = x;
        _pMaze[x][y]._y = y;
        _pMaze[x][y]._data = data;
        //节点四个方向默认初始化
        for (int i = 0; i < WAY_NUM; ++i)
        {
            _pMaze[x][y]._state[i] = NO;
        }
    }

    // 开始设置所有节点的四个方向的状态
    void setNodeState()
    {
        for (int i = 0; i < _rows; ++i)
        {
            for (int j = 0; j < _cols; ++j)
            {
                if (_pMaze[i][j]._data == 1)
                {
                    continue;
                }
                
                if (j < _cols - 1 && _pMaze[i][j + 1]._data == 0)
                {
                    _pMaze[i][j]._state[RIGHT] = YES;
                }
                if (i < _rows - 1 && _pMaze[i + 1][j]._data == 0)
                {
                    _pMaze[i][j]._state[DOWN] = YES;
                }
                if (j > 0 && _pMaze[i][j - 1]._data == 0)
                {
                    _pMaze[i][j]._state[LEFT] = YES;
                }
                if (i > 0 && _pMaze[i - 1][j]._data == 0)
                {
                    _pMaze[i][j]._state[UP] = YES;
                }
            }
        }
    }

    void searchMazePath()
    {
        if (_pMaze[0][0]._data == 1)
        {
            return;
        }
        _queue.push(_pMaze[0][0]);
        while(!_queue.empty())
        {
            Node fron = _queue.front();
            int x = fron._x;
            int y = fron._y; 

            //往右寻找
            if (_pMaze[x][y]._state[RIGHT] == YES)
            {
                _pMaze[x][y]._state[RIGHT] = NO;
                _pMaze[x][y+1]._state[LEFT] = NO;
                //在辅助数组中记录一下节点的行走信息（这个节点的上一个节点的路径）
                _pPath[x * _rows + y +1 ] = _pMaze[x][y];
                _queue.push(_pMaze[x][y+1]);
                if (check (_pMaze[x][y+1]))
                return;
            }

            //往下寻找
            if (_pMaze[x][y]._state[DOWN] == YES)
            {
                _pMaze[x][y]._state[DOWN] = NO;
                _pMaze[x+1][y]._state[UP] = NO;
                _pPath[(x + 1) * _rows + y] = _pMaze[x][y];
                _queue.push(_pMaze[x+1][y]);
                if (check (_pMaze[x+1][y]))
                return;
            }

            //向左寻找
            if (_pMaze[x][y]._state[LEFT] == YES)
            {
                _pMaze[x][y]._state[LEFT] = NO;
                _pMaze[x][y-1]._state[RIGHT] = NO;
                _pPath[x * _rows + y - 1] = _pMaze[x][y];
                _queue.push(_pMaze[x][y-1]);
                if (check (_pMaze[x][y-1]))
                return;
            }

            //向上
            if (_pMaze[x][y]._state[UP] == YES)
            {
                _pMaze[x][y]._state[UP] = NO;
                _pMaze[x-1][y]._state[DOWN] = NO;
                _pPath[(x - 1) * _rows + y] = _pMaze[x][y];
                _queue.push(_pMaze[x-1][y]);
                if (check (_pMaze[x-1][y]))
                return;
            }
            _queue.pop();
        }
    }

    void printMazePath()
    { 
        if (_queue.empty())
        {
            cout << "迷宫没有解" << endl;
            return;
        }
        else
        {
            //回溯寻找迷宫路径点
            int x = _rows - 1;
            int y = _cols - 1;
            for (;;)
            {
                _pMaze[x][y]._data = '*';
                if (x == 0 && y == 0)
                {
                    break;
                }
                Node node = _pPath[x * _rows + y];
                //从辅助数组中回溯
                x = node._x;
                y = node._y;
            }
        }
        for (int i = 0; i < _rows; ++i)
		{
			for (int j = 0; j < _cols; ++j)
			{
				if (_pMaze[i][j]._data == '*')
					std::cout << "* ";
				else
					std::cout << _pMaze[i][j]._data << " ";
			}
			std::cout << std::endl;
		}
    }
private:
    struct Node
    {
        int _x;
        int _y;
        int _data;
        int _state[WAY_NUM];
    };
    Node **_pMaze;
    int _rows;
    int _cols;
    std::queue<Node> _queue;
    std::vector<Node> _pPath;

    bool check(Node &node)
    {
        return node._x == _rows - 1 && node._y == _cols - 1;
    }
};

int main()
{
    cout << "请输入迷宫的行列数" << endl;
    int row, col, data;
    cin >> row >> col;
    Maze maze(row, col); //创建迷宫对象

    // 坐标和节点数据的初始化
    cout << "请输入迷宫的路径信息（0表示可以走，1表示不能走）" << endl;
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            cin >> data;
            maze.initNode(i, j, data);
        }
    }

    // 开始设置所有节点的四个方向的状态
    maze.setNodeState();

    // 开始从左上角搜索迷宫的路径信息
    maze.searchMazePath();

    // 输出迷宫路径信息
    maze.printMazePath();
}