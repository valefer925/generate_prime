#include <iostream>
#include <random>
#include <math.h>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

int modMulti(int a, int b, int p)
{
    int res = 1;
    while (b)
    {
        if (b & 1)
        {
            res = int(res * 1ll * a % p);
            --b;
        }
        else
        {
            a = int(a * 1ll * a % p);
            b >>= 1;
        }
    }
    return res;
}

int random_int(int a, int b)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(a, b);

    return distr(gen);
}
//WITNESS
bool witness(int a, int n)
{
    int s = 1;
    int t = 0;
    int u = 1;
    bool f = false;
    while (s * 2 <= n - 1)
    {
        t++;
        s = s * 2;
        while (s * u <= n - 1)
        {
            if (s * u == n - 1 && u % 2 != 0)
            {
                f = true;
                break;
            }
            u++;
        }
        if (f)
            break;
        u = 0;
    }
    if (!f)
        return false;
    int p = modMulti(a, u, n);
    int x;
    if (p == 1 || p == n - 1)

        return false;
    for (int i = 1; i < t; i++)
    {
        x = modMulti(p, 2, n);
        if (x == n - 1)
            return false;
        p = x;
    }
    return true;
}

//MILLER-RABIN
bool miller_rabin(int n, int s)
{
    int a;
    for (int i = 1; i <= s; i++)
    {
        //Generar numero aleatorio entre 1 y n-1
        a = random_int(1, n - 1);
        if (witness(a, n))
            return true;
    }

    return false;
}
int generate_prime_candidate(int b)
{
    int n = random_int(0, pow(2, b));
    int m = pow(2, (b - 5)) + 1;
    n = n | m;

    return n;
}

int generate_prime(int b)
{
    int s = 32;
    int n = generate_prime_candidate(b);
    while (miller_rabin(n, s))
        n += 2;
    return n;
}




int main()
{
    int aux = 0;
    int n;
    std::vector<int> res;

    while (res.size() != 100)
    {
        n = generate_prime(10);
        if (n % 2 != 0)
        {
            if (!(std::find(res.begin(), res.end(), n) != res.end()))
            {
                res.push_back(n);
                aux++;
            }
        }
    }
    int j = 0;
    for (int i = 0; i < res.size(); i++)
    {
        if (j == 20)
        {
            std::cout << std::endl;
            j = 0;
        }
        j++;
        std::cout << res[i] << " - ";
    }
}




