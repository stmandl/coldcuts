with open("dict.txt") as f:
    words = f.readlines()
    for i, w in enumerate(words):
        words[i] = w.strip().upper()
    words = set(words)

with open("coding-challenge-scrabble.inp1") as f:
    board = f.readlines()
    panel = list(board[-1].strip().upper())    
    board = board[:-1]
    for i, r in enumerate(board):
        board[i] = list(r.strip().upper())  # get rid of newline at end
    print(board)

scores_to_char = \
    {1:"EAIONRTLSU",
     2:"DG",
     3:"BCMP",
     4:"FHVWY",
     5:"K",
     8:"JX",
    10:"QZ"}

for k, v in scores_to_char.items():
    scores_to_char[k] = list(v)


char_to_score = {}
for k, v in scores_to_char.items():
    for c in v:
        char_to_score[c] = k

def score_single(v):
    s = 0
    if type(v) == list:
        v = "".join(v)
    for i in range(len(v)-1):
        for j in range(i, len(v)):            
            subw = "".join(v[i:j])
            if "-" in subw:  break
            if subw in words:
                #print(subw,"in words")
                s += sum([char_to_score[c] if c in char_to_score else 0 for c in subw])
    return s


def get_column(board,c):
    return [board[r][c]) for r in range(len(board))]

def score(board):
    s = 0
    for r in board:
        s += score_single(r)
    for c in range(len(board[0])):
        column = get_column(board,c)
        s += score_single(column)
    return s



#
# Idea: 
#

plays = {}

# def play_position(board,r,c,panel, base_score, played,direction):
#     if board[r][c] != '-': return
#     for i,v in enumerate(panel):        
#         board[r][c] = v
#         played.append(v)
#         panel.pop(i)
#         s = score(board)
#         if s>base_score:
#             plays[s-base_score] = (c-len(played) if direction=='right' else 0, r-len(played) if direction == 'down' else 0,"".join(reversed(played)), s-base_score)
#         play_position(board,r + 1 if direction == 'down' else 0,
#                       c + 1 if direction == 'right' else 0,panel, base_score, played, direction)
#         board[r][c] = '-'
#         played.pop()
#         panel.insert(i,v)

def play_column(board,r,c,panel):
    if len(panel) == 0: return
    column = get_column(board,c)
    base_score = score_single(column)
    
    


play_down(board,1,13,panel,score(board),[])
print(plays)

# # brute force
# def subsets(l):
#     #print(l)
#     if len(l) == 0: return [[]]    
#     s1 = subsets(l[1:])
#     res = []
#     for s in s1:
#         # with and without the first element
#         res.append(s)
#         res.append([l[0]] + s)
#     return res

# from copy import copy

# def permutations(l):
#     #print(l)
#     """
#     given a list of items, return a list of lists
#     with all orderings of the items
#     """
#     if len(l) == 0:
#         return [[]]
#     if len(l) == 1:
#         return [[l[0]]]
#     p1 = permutations(l[1:])
#     #print(p1)
#     res = []
#     for p in p1:        
#         for i in range(len(p1)+1):
#             np = copy(p)
#             np.insert(i,l[0])
#             res.append(np)
#     return res


# #print(subsets(panel), len(subsets(panel)))
# #print(score(board))
# plays = []
# for s in subsets(panel):
#     #print(s)
#     for p in permutations(s):
#         plays.append(p)

#print(plays,len(plays))