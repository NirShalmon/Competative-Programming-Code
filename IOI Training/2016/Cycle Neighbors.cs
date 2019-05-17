/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace IOI
{
    class Program
    {
        static void Main(string[] args)
        {
            int N = int.Parse(Console.ReadLine());
            int[] first = new int[3];
            int[] second = new int[3];
            first[0] = int.Parse(Console.ReadLine());
            if (N == 1)
            {
                Console.WriteLine(first[0]);
                return;
            }
            second[1] = int.Parse(Console.ReadLine());
            if (N == 2)
            {
                Console.WriteLine(Math.Max(first[0],second[1]));
                return;
            }
            second[2] = int.Parse(Console.ReadLine());
            if (N == 3)
            {
                Console.WriteLine(Math.Max(second[2], Math.Max(first[0], second[1])));
                return;
            }
            first[2] = second[2] + first[0];
            for (int i = 3; i < N; i++)
            {
                int read = int.Parse(Console.ReadLine());
                int tempF = first[2];
                int tempS = second[2];
                if (i != N - 1)
                {
                    first[2] = read + Math.Max(first[0], first[1]);
                }
                second[2] = read + Math.Max(second[0], second[1]);
                second[0] = second[1];
                second[1] = tempS;
                first[0] = first[1];
                first[1] = tempF;
            }
            int ans = 0;
            for (int i = 0; i < 3; i++)
            {
                ans = Math.Max(first[i], ans);
                ans = Math.Max(second[i], ans);
            }
            Console.WriteLine(ans);
        }
    }
}
