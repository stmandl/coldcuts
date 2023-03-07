create table hackers(hacker_id integer, name varchar(200));
create table submissions(submission_date date, submission_id integer, hacker_id integer, score integer);
insert into hackers values (15758, 'Rose');
insert into hackers values (20703, 'Angela');
insert into hackers values (36396, 'Frank');
insert into hackers values (38289, 'Patrick');
insert into hackers values (44065, 'Lisa');
insert into hackers values (53473, 'Kimberly');
insert into hackers values (62529, 'Bonnie');
insert into hackers values (79722, 'Michael');

insert into submissions values ('2016-03-01',8494,20703,0);
insert into submissions values ('2016-03-01',22493,53473,15);
insert into submissions values ('2016-03-01',23965,79722,60);
insert into submissions values ('2016-03-01',30173,36396,70);

insert into submissions values ('2016-03-02',34928,20703,0);
insert into submissions values ('2016-03-02',38740,15758,60);
insert into submissions values ('2016-03-02',42769,79722,25);
insert into submissions values ('2016-03-02',44364,79722,60);

insert into submissions values ('2016-03-03',45440,20703,0);
insert into submissions values ('2016-03-03',49050,36396,70);
insert into submissions values ('2016-03-03',50273,79722,5);

insert into submissions values ('2016-03-04',50344,20703,0);
insert into submissions values ('2016-03-04',51360,44065,90);
insert into submissions values ('2016-03-04',54404,53473,65);
insert into submissions values ('2016-03-04',61533,79722,45);

insert into submissions values ('2016-03-05',72852,20703,0);
insert into submissions values ('2016-03-05',74546,38289,0);
insert into submissions values ('2016-03-05',76487,62529,10);
insert into submissions values ('2016-03-05',82439,36396,40);
insert into submissions values ('2016-03-05',90006,36396,0);

insert into submissions values ('2016-03-06',90404,20703,0);

/*

select lag(has_sub,1) over (partition by hacker_id order by submission_date)
from
(
select all_comb.submission_date, all_comb.hacker_id, s.submission_date is not null as has_sub from
(
select * from
(select distinct submission_date from submissions) as x1
cross join 
 (select distinct hacker_id from submissions) as x2
  ) as all_comb
  left join submissions as s
  on (all_comb.hacker_id = s.hacker_id and all_comb.submission_date = s.submission_date)
 ) as x3
 order by submission_date,hacker_id;


select all_comb.submission_date, all_comb.hacker_id, s.submission_date is not null as has_sub from
(
select * from
(select distinct submission_date from submissions) as x1
cross join 
 (select distinct hacker_id from submissions) as x2
  ) as all_comb
  left join submissions as s
  on (all_comb.hacker_id = s.hacker_id and all_comb.submission_date = s.submission_date)
 
 order by submission_date,hacker_id;

*/

/*
select submission_date, best.hacker_id, name
from
(
select max_submissions.submission_date,       
       min(hacker_id) as hacker_id
from 
(
   select submission_date,
   max(num_submissions) max_submissions from
      (
         select submission_date, hacker_id, count(*) num_submissions from submissions
         group by submission_date, hacker_id
       ) submissions_per_day1
     group by submission_date
   ) max_submissions
   join
   (
    select submission_date, hacker_id, count(*) num_submissions from submissions
      group by submission_date, hacker_id
   ) submissions_per_day2
   on (max_submissions.submission_date = 
       submissions_per_day2.submission_date
      and num_submissions = max_submissions)    
 group by max_submissions.submission_date
 )as  best
 join hackers on (best.hacker_id = hackers.hacker_id)
 order by submission_date
;
*/

/*
select 
submission_date, hacker_id,
cumsum(num_sub>0) over (partition by hacker_id order by submission_date)
from
(
select submission_date, hacker_id, count(*) num_sub from 
submissions
group by submission_date, hacker_id
  )
/*