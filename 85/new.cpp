#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
 
using namespace std;
 
struct point
{
    int x,y;
    point(){}
    point(int X, int Y)
    {
        x = X;
        y = Y;
    }
};

int n;
vector<point> arr;
vector<int> mvo;        // Минимальная Выпуклая Оболочка. mvo — массив индексов вершин arr
double P;

double dist (point &a, point &b)
{
    return sqrt( 0.0 + (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void input()
{
    cin >> n;
    arr.resize(n);

    for (int i = 0; i < n; i++)
        scanf("%d %d", &arr[i].x, &arr[i].y);
}

int OrientTriangl2(const point &p1, const point &p2, const point &p3)
{
    return p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y);
}
 
bool isInside(const point &p1, const point &p, const point &p2)
{
    return ( p1.x <= p.x && p.x <= p2.x &&
             p1.y <= p.y && p.y <= p2.y);
}

void Jarvis(const vector<point> &arr, vector<int> &mvo)
{
    // находим самую левую из самых нижних
    int base = 0;
    for (int i=1;i<n;i++)
    {
        if (arr[i].y < arr[base].y)
            base = i;
        else
            if (arr[i].y == arr[base].y &&
                arr[i].x <  arr[base].x)
                base = i;
    }
    // эта точка точно входит в выпуклую оболочку
    mvo.push_back(base);
 
    int first = base;
    int cur = base;
    do
    {
        int next = (cur + 1) % n;
        for (int i=0;i<n;i++)
        {
            int sign = OrientTriangl2(arr[cur], arr[next], arr[i]);

            // точка arr[i] находится левее прямой ( arr[cur], arr[next] )
            if (sign < 0) // обход выпуклой оболочки против часовой стрелки
                next = i;

            // точка лежит на прямой, образованной точками  arr[cur], arr[next]
            else if (sign == 0)
            {
                // точка arr[i] находится дальше, чем arr[next] от точки arr[cur]
                if (isInside(arr[cur],arr[next],arr[i]))
                    next = i;
            }
        }
        cur = next;
        mvo.push_back(next);
    }
    while (cur != first);
}

void solve()
{
    Jarvis(arr, mvo);
   
    for (int i = 0; i < mvo.size() - 1; i++)
    {
        printf("%d:\t%d\t%d\n", mvo[i], arr[mvo[i]].x, arr[mvo[i]].y);
        P += dist(arr[mvo[i]], arr[mvo[i+1]]);
    }
}

void output()
{
    printf("%0.1f", P);
}

int main()
{
    freopen("/Users/danielgehrman/Documents/Programming/Uni/Sem-2-NSU/85/input.txt", "r", stdin);
    freopen("/Users/danielgehrman/Documents/Programming/Uni/Sem-2-NSU/85/output.txt", "w", stdout);
 
    input();
    solve();
    output();
 
    return 0;
}