## rotate a matrix
## Assume: M[n][m]: Stored as list of rows

m1 = [[11,12,13],[21,22,23],[31,32,33]]

def rotate(M,direction='transpose'):
    if M is None: return M
    m = len(M)
    if m == 0: return M
    n = len(M[0])
    if n == 0: return M
    S = [ ['x'] * m for _ in range(n) ]

    def indexer():
        def transpose_(i,j):
            return j,i
        def left_(i,j):
            return j,m-i-1
        def right_(i,j):
            return n-j-1,i
        
        if direction=='transpose':
            return transpose_
        elif direction=='left':
            return left_
        elif direction == 'right':
            return right_
        else:
            raise f'Unknown direct: "{direction}", only "left" or "right" allowed'
    iii = indexer()
    for i in range(n):
        for j in range(m):
            ni,nj = iii(i,j)
            S[i][j] = M[ni][nj]
        
            
    return S


def printM(m):
    for r in m:
        print(r)

printM(m1)
print("Transposed:")
printM(rotate(m1,"transpose"))
print("Left:")
printM(rotate(m1,"left"))
print("Right:")
printM(rotate(m1,"right"))


print("now doing the same stuff using numpy")
