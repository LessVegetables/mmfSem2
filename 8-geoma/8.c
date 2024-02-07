#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct cel
{
    double x, y, z;
    struct cel *next;
}nodes;

typedef struct arr
{
    nodes *root;
}list;


int main()
{

    H = ConvexHull(P); // МВО списка P точек

    nh = H.Count();

    G = P\H;

    for (i = 0; i < w * nh; i++)
    {

        im = IndexMaxSide(H);  // индекс в H начальной точки наибольшей стороны

        pb = H[im]; pe = H[(im + 1) % H.Count()];

        jpt = -1;

        qd0 = qDist(pb, pe); // квадрат расстояния pb, pe
        
        Sqmax = 0;

        foreach (pt in G)
        {
            qd1 = qDist(pb, pt);  qd2 = qDist(pe, pt);

            if (qd0 > Abs(qd1 - qd2))
            {
                Sqt = Sq(pb, pt, pe);

                if (Sqt < Sqmax) continue;

                if (NotEmptyTreangle(pb, pe, pt, G)) continue;

                if (IsCrossHull(pb, pe, pt, H)) continue;

                jpt = G.IndexOf(pt);
                Sqmax = Sqt;
            }
        }

        if (jpt >= 0)
        {
            H.Insert(im + 1, G[jpt]);
            G.RemoveAt(jpt);
        }
        else break;
    }


    return 0;
}