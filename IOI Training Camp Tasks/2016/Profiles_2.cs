/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Profile_2
{
    class Program
    {
        static void Main(string[] args)
        {
            int N = int.Parse(Console.ReadLine());
            int[] s = new int[20001];
            int[] sw = new int[20001];
            int[] w = new int[20001];
            int[] ww = new int[20001];
            int sum = 0;
            for (int i = 0; i < N; i++)
            {
                int t = int.Parse(Console.ReadLine());
                s[t]++;
            }
            for (int i = 0; i < N; i++)
            {
                int t = int.Parse(Console.ReadLine());
                w[t]++;
            }
            for (int i = 0; i < 20001; i++)
            {
                sw[i] += (i == 0 ? 0 : sw[i -1]) + s[i];
                ww[i] += (i == 0 ? 0 : ww[i -1]) + w[i];
                int t = (s[i] * (N - ww[i]) + w[i] * (N - sw[i]) + s[i] * w[i]) * i;
                sum += t;
            }
            Console.WriteLine(sum);
        }
    }
}
