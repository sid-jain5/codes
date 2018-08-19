#include<bits/stdc++.h>

#define d 256

using namespace std;

void naiveSearch(string s1, string s2)
{
    //this function will ignore overlapping patterns
    long j=0,l1 = s1.length(), l2 = s2.length();
    //cout << "String length is " << l1 << " and pattern length is " << l2 << "\n";
    for(long i=0; i<l1;i++)
    {
        if(j<l2 && s2[j] == s1[i])
            j++;
        else if(j == l2)
        {
            i=i-1;
            cout << " Pattern found starting at Index " << i-j+1 << "\n";
            j=0;
        }
        else if(j<l2 && s2[j] != s1[i])
            j=0;
    }
}
void betterNaive(string s1, string s2)
{
    cout << "\n\n Naive algorithm \n Main idea is to match pattern starting from each character of string\n Complexity is O(m(n-m+1)) in worst case\n";
    long l1 = s1.length(), l2 = s2.length();
    long j;
    //cout << "String length is " << l1 << " and pattern length is " << l2 << "\n";
    for(long i=0; i<=l1-l2;i++)
    {
        for(j=0; j<l2; j++)
        {
            if(s1[i+j] != s2[j])
                break;
        }
        if(j == l2)
            cout << " Pattern found at " << i<< "\n";
    }
}
//Improved Naive Search when all characters in s2 are diffrent
void improvedNaive(string s1, string s2)
{
    cout << "\n\n Improved Naive \n when all the characters of s2 are different\n";
    long l1 = s1.length(), l2 = s2.length();
    long j;

    for(long i=0; i<=l1-l2; i++)
    {
        for(j=0;j<l2;j++)
        {
            if(s1[i+j]!=s2[j])
                break;
        }

        if(j!=l2)
        {
            if(j)
                i +=j-1;
        }
        else
            cout << " Pattern found at " << i<< "\n";
    }

}
//Knuth Morris Pratt Algorithm for pattern searching
void computeLps(string s2, long l2, long* lps)
{
    long len=0;

    lps[0] = 0;

    long i=1;
    while(i!=l2)
    {
        if(s2[i] == s2[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if(len!=0)
            {
                len = lps[len-1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}
void kmp(string s1, string s2)
{
    cout << "\n\n KMP algorithm \n Main idea is to make an lps array of longest prefix that is also a suffix so that all characters need not be matched\n Complexity is O(n) in worst case\n";
    long l1 = s1.length();
    long l2 = s2.length();

    long *lps = new long[l2];
    computeLps(s2, l2, lps);

    long i=0,j=0;
    while(i!= l1)
    {
        if(s1[i] == s2[j])
        {
            i++;
            j++;
        }
        if(j == l2)
        {
            cout << " Pattern found at index " << i-j << "\n";
            j = lps[j-1];
        }
        else if(i!=l1 && s1[i]!=s2[j])
        {
            if(j!=0)
                j = lps[j-1];
            else
                i++;
        }
    }
}
//
void rabinKarp(string s1, string s2, long primeNum)
{
    cout << "\n\n Rabin Karp algorithm \n Main idea is to match only those substrings with pattern who have same hash values that implies same characters, hash value calculated efficiently in O(1) time by using previous windows hash value\n";
    cout << " Complexity is O(n+m) in best and average case\n O(mn) in worst case occurs when all characters are same s1 = AAAAAA s2 = AAA\n";
    cout << "d = number of characters or 256 and h = (d^M-1) mod primeNum\n";
    cout << "hash[nextWindow] = (d(hash[previousWindow]-(ExitChararcter or previousWindowStart)*h) + entryCharacter) mod PrimeNum\n";

    long l1 = s1.length();
    long l2 = s2.length();

    long i,j,p=0,q=0,h=1;

    // h = (d^M-1) mod primeNum
    for(i=0;i<l2-1;i++)
        h = (h*d)%primeNum;

    //Calculating first window of text
    for(i=0; i<l2;i++)
    {
        p = (d*p + s2[i])%primeNum;
        q = (d*q + s1[i])%primeNum;
    }

    //Sliding pattern for next
    for(i=0; i<= l1-l2;i++)
    {
        if(p==q)
        {
            for(j=0; j<l2;j++)
            {
                if(s1[i+j] != s2[j])
                    break;
            }

            if(j == l2)
                cout << " Pattern found at index " << i << "\n";
        }

        if(i<l1-l2)
        {
            q = (d*(q - s1[i]*h) + s1[i+l2])%primeNum;

            if(q<0)
                q+=primeNum;
        }
    }
}
//

void badHeuristic(string s2, long* lastOccurence)
{
    for(long i=0; i<256;i++)
        lastOccurence[i] = -1;

    for(long i=0; i<s2.length();i++)
        lastOccurence[(int)s2[i]] = i;
}
void boyerMoore(string s1,string s2)
{
    cout << "\n\n Boyer Moore Bad Heuristics Algo \n Idea of bad character heuristic is on mismatch we shift the pattern until mismatch becomes match(shifting to last occurrence of that character)\n";
    cout << " or if the character is not present in pattern that start from char next to mismatched character\n";
    long l1 = s1.length();
    long l2 = s2.length();

    long *lastOccurence = new long[256];
    badHeuristic(s2,lastOccurence);

   /* for(long i=65; i<=90;i++)
        cout << lastOccurence[i] << " ";*/

    long i=0;

    while(i <= l1-l2)
    {
        long j = l2-1;

        while(j>=0 && s2[j] == s1[i+j])
            j--;

        //If pattern found, value of j will be -1
        if(j<0)
        {
            cout << " Pattern found at index " << i << "\n";
            if(i+l2<l1)
                i = i+ l2-lastOccurence[s1[i+l2]];
            else
                i++;
        }
        else
        {
            long num = 1;
            i += max(num, j-lastOccurence[s1[i+j]]);
        }
    }
}
int main()
{
    string s1,s2;

    cout << " Enter the main String\n" ;
    fflush(stdin);
    getline(cin,s1);

    cout << " Enter pattern to be searched\n ";
    fflush(stdin);
    getline(cin,s2);

    //exactly same STL for tolower, just replace toupper with tolower
    transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
    transform(s2.begin(), s2.end(), s2.begin(), ::toupper);

    //cout << s1 << " ------ " << s2 << "\n";

    //naiveSearch(s1,s2);
    betterNaive(s1,s2);
    kmp(s1,s2);
    rabinKarp(s1,s2,101);
    improvedNaive(s1,s2);
    boyerMoore(s1,s2);
}
