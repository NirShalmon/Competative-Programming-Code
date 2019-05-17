/*****************
Competative programming code written by Nir Shalmon
IMPORTANT NOTE: This code was written during a time limited competition or for use in competition. 
THIS CODE IS NOT AN INDICATION OF MY  USUAL CODE QUALITY!!
******************/
﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace three
{
    class Program
    {
        static void Main(string[] args)
        {
            int N = int.Parse(Console.ReadLine());
            int upperBound = int.MaxValue;
            int lowerBound = int.MinValue;
            int carry = 0;
            int prev = 0;
            int sign = 1;
            for (int i = 0; i < N; i++)
            {
                sign *= -1;
                int t = int.Parse(Console.ReadLine());
                carry = 2 * t - carry;
                if (sign == 1)
                {
                    lowerBound = Math.Max( (prev-carry) / 2, lowerBound);
                }
                else
                {
                   
                    upperBound = Math.Min((carry - prev) / 2,upperBound);
                }
                prev = carry;
            }
            Console.WriteLine(Math.Max(0, upperBound - lowerBound + 1));

            
        }
    }
}
