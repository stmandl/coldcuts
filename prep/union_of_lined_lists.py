#!/usr/bin/python3
# Here is an OA question, only partial information.
# If anyone has further information, please feel free to share with me.
# HackerRank, Must use C++. The algorithm part is a medium to hard leetcode question.
# 100 min. Given a csv file, each row being (start_job, time, next_job),
# Your job is to detect if the input data is an union of single linked list;
# then compute the total time to finish all jobs, the total number of jobs,
# average time per job. Read the csv file, run an algorithm, writing output.

import random

data = []

job_counter = 0

for _ in range(5):

    job_len = random.randint(5,40)

    for _ in range(job_len):

        job_time = random.randint(10,100)        
        data.append((job_counter,job_time,job_counter+1))
        job_counter += 1
    
    job_counter+=1
    
random.shuffle(data)
for (a,b,c) in data:
    print(f'{a},{b},{c}')