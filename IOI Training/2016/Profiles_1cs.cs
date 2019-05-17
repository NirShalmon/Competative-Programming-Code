/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Profiles
{
    class Program
    {
        static void Main(string[] args)
        {
            int N = int.Parse(Console.ReadLine());
            int[] occ = new int[20001];
            int sum = 0;
            for (int i = 0; i < N; i++)
            {
                int t = int.Parse(Console.ReadLine());
                occ[t]++;
                sum += t;
            }
            for (int i = 0; i < N; i++)
            {
                int t = int.Parse(Console.ReadLine());
                if (occ[t] > 0)
                {
                    occ[t]--;
                }
                else
                {
                    sum += t;
                }
            }
            Console.WriteLine(sum);
        }
    }
}
