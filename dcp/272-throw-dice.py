#272:throw_dice(N,face,total)

#testcase:


def throw_dice(N,face,total):
    '''
    This is a straightforward recursive version
    '''
    if N==1:
        if total <= face: return 1
        else: return 0
    else:
        sum = 0
        for f in range(1,face,1):
            ntotal = total-f
            if ntotal >= 1:
                sum += throw_dice(N-1,face,ntotal)
            else:
                break
        return sum

def throw_dice2(N,face,total,cache={}):
    '''
    This here add a cache for previously computed subproblems'
    '''
    if (N,face,total) in cache: return cache[(N,face,total)]
    result = 0
    if N==1:
        if total <= face: result = 1
    else:
        sum = 0
        for f in range(1,face,1):
            ntotal = total-f
            if ntotal >= 1:
                sum += throw_dice2(N-1,face,ntotal,cache)
            else:
                break
        result = sum
    cache[(N,face,total)] = result
    return result



def test():
    x = throw_dice(3,6,7)
    print(x)
    assert x == 15