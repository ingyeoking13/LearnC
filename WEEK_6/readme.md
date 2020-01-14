# 6주차 발표 20200114

## 백준 16437 양구출작전

### eovh1962

[문제링크](https://www.acmicpc.net/problem/16437)  
[정답소스](../Study/16437_eovh1962.c)

소스에서 realloc과 관련된 이야기  
c++ vector push_back 을 n 개 하였을 때 시간복잡도가 O(n)인 이유  
[computer science stack 링크](https://cs.stackexchange.com/questions/9380/why-is-push-back-in-c-vectors-constant-amortized)

## 백준 15983 순간이동 발판

### djm03178

소프트콘 E 번 문제

[문제링크](https://www.acmicpc.net/problem/15983)  
[문제해설지](https://docs.google.com/presentation/d/1h6-FNqXeA-c8_ol_2p9SBcW1kse5LOvyyw9wXnGbwbk/edit?usp=sharing)  
[정답소스](../Study/15983_djm03178.cc)  

## cf Hello 2020 C. New Year and Permutation

### djm03178

[문제링크](https://codeforces.com/contest/1284/problem/C)  
[정답소스](../Study/codeforces_Hello2020D_gaelim.cc)  

**문제해설**

```
(자리 n개) * (그 자리에 고정시킬 수 n개) * (고정시킨 수들의 순열의 수 1!개) * (그 자리를 제외한 나머지 자리들의 순열의 수 (n-1)!개)
(자리 n-1개) * (그 자리에 고정시킬 수 n-1개) * (고정시킨 수들의 순열의 수 2!개) * (그 자리를 제외한 ~ (n-2)!개)
...
..
.
(자리 1개) * (그 자리에 고정시킬 수 1개) * (고정시킨 수들의 순열의 수 n!개) * (그 자리를 제외한 ~ 0!개)
```

_풀어볼만한_  
양구출작전    
순간이동발판 subtask1

_도전적인_  
순간이동발판 subtask2   
New Year and Permutation

_어려운_    
순간이동발판 subtask3
