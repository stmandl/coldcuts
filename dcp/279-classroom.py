## A classroom consists of N students, whose friendship can be represnted in an adjacency list.
## For example, the following describes a situation where 0 is friends with 1 and 2,3 is friends
## with 6 and so on.

friends = {0: [1,2],
           1: [0,5],
           2: [0],
           3: [6],
           4: [],
           5: [1],
           6: [3]}

## Each student can be placed in a friend group, which can be defined as the transitive closure of
## that student's friendship relations. In other words, this is the smallest set such that no
## student in the group has any friends outside this group. For the example above,
## the friend groups would be:

friend_groups = [{0,1,2,5}, {3,6}, {4}]

## Given a friendship list such as the one above, determine the number of friend groups in the class



## Ok, first observation: The number is deterministic, per relation. It is the well defined transitive closure

def trans(rel):
    res = []

    def new_group(i):
        return set(rel[i]).union([i])

    for i in range(len(rel)):
        found = False
        for g in res:
            if i in g:
                g.update([i],rel[i])
                found = True
        if not found:
            new_group=set(rel[i]).union([i])
            res.append(new_group)

    return res

def flatten(l):
    res = []
    for ll in l:
        if type(ll) == 'list':
            res.extend(ll)
        else:
            res.append(ll)
    return res

print('flatten:',flatten([[1],4,5,[5,6,[7,8]]]))

def trans2(rel):
    done_list = [False]*len(rel)
    def rec(i):
        #print(i)
        if done_list[i] == True:
            #print('done .. return []')
            return []
        else:
            done_list[i] = True
            #print('rel['+str(i)+']:',rel[i])
            sub = flatten([rec(j) for j in rel[i]])
            #print('sub:', sub)
            #print('return ', [i]+sub)
            return ( [i] + sub)
    res=[]
    for i in range(len(rel)):
        if not done_list[i]:
            res.append(rec(i))
    return res
    

print(trans2(friends))
