#include <iostream>

using namespace std;

class CComplex
{
    private:
        double re, im;
        friend CComplex operator+(const CComplex &d, const CComplex &c);//定义友元函数来调用private变量
        friend ostream &operator<<(ostream &out, const CComplex &c);
        friend istream &operator>>(istream &in, CComplex &c);
    public:
        CComplex(double re = 0, double im = 0) : re(re), im(im) {}
        
        // 重载加号运算符
        /* CComplex operator+(const CComplex &c) const
        {
            return CComplex(re + c.re, im + c.im);
        } */
        CComplex operator-(const CComplex &c) const
        {
            return CComplex(re - c.re, im - c.im);
        }

        CComplex& operator++ ()
        {
            re++;
            im++;
            return *this;
        } // 前置

        CComplex operator++ (int)
        {
            //CComplex temp = *this; // 先保存当前对象
            //re++;
            //im++;
            //return temp; // 返回保存的对象
            return CComplex(re++, im++);
        }// 后置

        void operator+= (const CComplex& c)
        {
            re += c.re;
            im += c.im;
        }

        void show (){
            cout << re << " + " << im << "i" << endl;
        }
};

CComplex operator+(const CComplex &d, const CComplex &c)//全局运算符重载
{
    return CComplex(d.re + c.re, d.im + c.im );
}

ostream &operator<<(ostream &out, const CComplex &c)
{
    out << c.re << " + " << c.im << "i " ;
    return out;
}

istream &operator>>(istream &in, CComplex &c)
{
    in >> c.re >> c.im;
    return in;
}

int main()
{
    CComplex c1(1, 2), c2(3, 4);
    CComplex c3 = c1 + c2;
    CComplex c4 = 20 + c1;//全局运算符重载
    c3.show();
    c4.show();
    CComplex c5 = c4++;
    c5.show();
    CComplex c6 = ++c5;
    c6.show(); 
    c1 += c2;

    cout << c1 << c3 << c4 << c5 << c6 << endl;

}