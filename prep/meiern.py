from collections import Counter
from typing import Tuple
from random import randint

def normalize(play: Tuple[int, int]) -> Tuple[int,int]:
    if play[0] < play[1]:
        return (play[1], play[0])
    else:
        return play


play_counts = Counter()

for d1 in range(0,6):
    for d2 in range(0,6):
        play = normalize((d1+1,d2+1))
        play_counts[play] += 1

print(play_counts.most_common())

total = sum(play_counts.values())

total_prob = 0
for play, count in play_counts.most_common():
    prob = count/total*100
    total_prob += prob
    print(play, prob)

print(total, total_prob)

gen = ( (u,j) for u in range(5) for j in range(5) )
print(gen)
print(list(gen))