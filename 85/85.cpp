#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>

using namespace std;


/*
85. Стр 179
Задано n точек на плоскости.
Найти окружность наибольшего радиуса,
не содержащую внутри ни одной точки
этого множества, центр которого лежит
внутри выпуклой оболочки заданного
множества точек.
*/


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

double dist (point &a, point &b)
{
    return sqrt( 0.0 + (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// ориентированная площадь треугольника
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
  int start = 0;
  for (int i=1;i<n;i++)
  {
    if (arr[i].y < arr[start].y)
      start = i;
    else
      if (arr[i].y == arr[start].y &&
          arr[i].x <  arr[start].x)
          start = i;
  }
  // эта точка точно входит в выпуклую оболочку
  mvo.push_back(start);

  int first = start;
  int cur = start;
  int next, sign;

  do
  {
    next = (cur + 1) % n;
    for (int i=0;i<n;i++)
    {
      sign = OrientTriangl2(arr[cur], arr[next], arr[i]);

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


int main()
{
  freopen("/Users/danielgehrman/Documents/Programming/Uni/Sem-2-NSU/85/input.txt", "r", stdin);
  freopen("/Users/danielgehrman/Documents/Programming/Uni/Sem-2-NSU/85/output.txt", "w", stdout);


  //inputting
  cin >> n;
  arr.resize(n);
  for (int i = 0; i < n; i++)
  {
    scanf("%d %d", &arr[i].x, &arr[i].y);
  }

  // outlining the MVO
  Jarvis(arr, mvo);

  //outputting the MVO
  double P = 0;
  for (int i = 0; i < mvo.size() - 1; i++)
  {
    printf("%d:\t%d\t%d\n", mvo[i], arr[mvo[i]].x, arr[mvo[i]].y);
    P += dist(arr[mvo[i]], arr[mvo[i+1]]);
  }

  //outputting the perimeter
  printf("%0.1f", P);

  vector<int> isMvo;

  isMvo.resize(n);



  for (int i = 0; i < n; i++)
  {
    isMvo[i] = 0;
  }
  for (int i = 0; i < mvo.size(); i++)
  {
    isMvo[mvo[i]] = 1;
  }

  cout << endl;

  double maxRadius = 0, radius2;
  point o;
  for (int i = 0; i < n; i++)
  {
    if (isMvo[i] == 1) continue;
    
    for (int j = 0; j < n; j++)
    {
      if (i == j) continue;

      
      radius2 = pow((arr[i].x - arr[j].x), 2.0) + pow((arr[i].y - arr[j].y), 2.0);

      if (radius2 > maxRadius)
      {
        for (int k = 0; k < n; k++)
        {
          if (k == i || k == j) continue;

          if (radius2 > pow((arr[i].x - arr[k].x), 2.0) + pow((arr[i].y - arr[k].y), 2.0))
          {
            break;;
          }

          if (k == n - 1)
          {
            maxRadius = radius2;
            o = arr[i];
          }
        }
      }
    }
  }

  maxRadius = pow(maxRadius, 0.5);

  cout << "\nR: " << maxRadius << "\t" << o.x << "\t" << o.y << endl;

  return 0;
}