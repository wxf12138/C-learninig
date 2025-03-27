/* 
深度遍历搜索迷宫路径，软件运行要求如下：

请输入迷宫的行数和列数：
请输入迷宫的路径信息，（0表示可以走，1表示不能走）
0 0 0 1 1 
1 0 0 0 1
1 1 0 1 1
1 1 0 0 1
1 1 1 0 0
左上角为入口 右下角为出口
输出路径用*表示
*/
//定义迷宫每个节点的四个不同的方向
#include <iostream>
#include <vector>
#include <stack>
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
        _stack.push(_pMaze[0][0]);
        while(!_stack.empty())
        {
            Node _top = _stack.top();
            int x = _top._x;
            int y = _top._y;

            if (x == _rows - 1 && y == _cols - 1)
            {
                return;
            }

            //往右寻找
            if (_pMaze[x][y]._state[RIGHT] == YES)
            {
                _pMaze[x][y]._state[RIGHT] = NO;
                _pMaze[x][y+1]._state[LEFT] = NO;
                _stack.push(_pMaze[x][y+1]);
                continue;
            }

            //往下寻找
            if (_pMaze[x][y]._state[DOWN] == YES)
            {
                _pMaze[x][y]._state[DOWN] = NO;
                _pMaze[x+1][y]._state[UP] = NO;
                _stack.push(_pMaze[x+1][y]);
                continue;
            }

            //向左寻找
            if (_pMaze[x][y]._state[LEFT] == YES)
            {
                _pMaze[x][y]._state[LEFT] = NO;
                _pMaze[x][y-1]._state[RIGHT] = NO;
                _stack.push(_pMaze[x][y-1]);
                continue;
            }

            //向上
            if (_pMaze[x][y]._state[UP] == YES)
            {
                _pMaze[x][y]._state[UP] = NO;
                _pMaze[x-1][y]._state[DOWN] = NO;
                _stack.push(_pMaze[x-1][y]);
                continue;
            }
            _stack.pop();
        }
    }

    void printMazePath()
    { 
        if (_stack.empty())
        {
            cout << "迷宫没有解" << endl;
            return;
        }
        else
        {
            while(!_stack.empty())
            {
                Node top = _stack.top();
                _pMaze[top._x][top._y]._data = '*';
                _stack.pop();
            }

            for(int i = 0; i < _rows; ++i)
            {
                for(int j = 0; j < _cols; ++j)
                {
                    if(_pMaze[i][j]._data == '*')
                        cout << "* ";
                    else
                        cout << _pMaze[i][j]._data << " ";
                }
                cout << endl;
            }
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
    stack<Node> _stack;
};

int main()
{
    cout << "请输入迷宫的行列数go" << endl;
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