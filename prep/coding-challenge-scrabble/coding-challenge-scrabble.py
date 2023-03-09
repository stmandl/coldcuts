from collections import defaultdict

with open("dict.txt") as f:
    words = f.readlines()
    for i, w in enumerate(words):
        words[i] = w.strip().upper()
    words = set(words)


class WordTree:

    class Node:
        def __init__(self, is_word: bool) -> None:            
            self.is_word = is_word
            self.next = {}
            
        def insert(self, word):
            if len(word) == 0:
                self.is_word = True                
                return
            c = word[0]
            rest = word[1:]
            if c not in self.next:
                self.next[c] = WordTree.Node(False)
            self.next[c].insert(rest)            

        def gather(self, characters, word, bag, given=[], constraints=[]):
            #print("Gather:",characters, word, bag, constraints, given)
            if self.is_word:
                #print("Result:", word)
                bag.append(word)
            if len(given)>0 and given[0] is not None:
                c = given[0]
                #print("c",c,"in self.next:",self.next)
                if c in self.next:
                    self.next[c].gather(characters, word+c, bag, given[1:], constraints[1:])
            else:
                for i in range(len(characters)):
                    c = characters[i]
                    if len(constraints) > 0 and c not in constraints[0]:
                        continue                
                    if c in self.next:
                        remaining = characters[:i]+characters[i+1:]
                        nword = word + c
                        self.next[c].gather(remaining, nword, bag, given[1:], constraints[1:])
                


    def __init__(self, words) -> None:
        self.root = WordTree.Node(False)
        for w in words:            
            self.root.insert(w)

    def lookup(self, word):
        current = self.root
        while len(word)>0:            
            c = word[0]
            if c in current.next:
                word = word[1:]
                current = current.next[c]
            else:
                return False, None
        return current.is_word, current
            

    def possibleWords(self, characters, prefix=""):
        if len(prefix) > 0:
            _, start_node = self.lookup(prefix)
            res = []
            if start_node is not None:
                start_node.gather(characters, "", res)
            res = [prefix+w for w in res]
        else:
            res = []
            res = self.root.gather(characters, "", res)        
        
        return list(set(res))


wt = WordTree(words)
print("indexed.")
#print(wt.lookup("PANEL"))
#print(wt.lookup("PAN"))
print(wt.possibleWords(list("panmelyy".upper()), "LAM"))



with open("coding-challenge-scrabble.inp2") as f:
    board = f.readlines()
    panel = list(board[-1].strip().upper())    
    board = board[:-1]
    for i, r in enumerate(board):
        board[i] = list(r.strip().upper())  # get rid of newline at end
    print(board)


from copy import deepcopy

class Solver:
    """
    Given a board, a panel (list of chars), and a dictionary, suggest possible plays
    """
    def __init__(self, board, panel, wt: WordTree):
        self.board = board
        self.panel = panel
        self.wt = wt
        self.analyzed = False

    def analyze(self):
        print("Analyzing board")
        self.positions = set()
        for r in range(len(self.board[0])):
            for c in range((len(self.board))):
                self.positions.add((r,c))

        self.attach_positions = set()
        for p in self.positions:
            if self.is_empty(p) and (not self.is_empty(self.left(p)) or \
                                     not self.is_empty(self.right(p)) or \
                                     not self.is_empty(self.up(p)) or \
                                     not self.is_empty(self.down(p))):
                self.attach_positions.add(p)

        self.possible_chars = {} # per position record what characters are possible
        for p in self.positions:
            if not self.is_empty(p):
                self.possible_chars[p] = set(self.content(p))
            elif p not in self.attach_positions: # we are free to choose anything from the panel
                self.possible_chars[p] = set(self.panel)
            else:
                # check downwards:
                downwards_constraints = set()
                np = self.down(p)
                if np in self.positions:
                    if not self.is_empty(np):
                        word = self.read_downwards(np)
                        for c in self.panel:
                            if self.wt.lookup(c+word)[0]:
                                downwards_constraints.add(c)

                # check upwards:
                upwards_constraints = set()
                np = self.up(p)
                if np in self.positions:
                    if not self.is_empty(np):
                        word = self.read_upwards(np)
                        for c in self.panel:
                            if self.wt.lookup(c+word)[0]:
                                upwards_constraints.add(c)
                
                if len(downwards_constraints)>0 and len(upwards_constraints) > 0:
                    self.possible_chars[p] = downwards_constraints.intersection(upwards_constraints)
                elif len(downwards_constraints)>0 and len(upwards_constraints) == 0:
                    self.possible_chars[p] = downwards_constraints
                elif len(downwards_constraints)==0 and len(upwards_constraints) > 0:
                    self.possible_chars[p] = upwards_constraints
                else:
                    self.possible_chars[p] = set(self.panel)

        self.analyzed = True
        print("... done")

    def copy(self):
        assert self.analyzed
        res = Solver(self.board, self.panel, wt)
        res.possible_chars = self.possible_chars
        res.attach_positions = self.attach_positions
        res.positions = self.positions
        res.analyzed = True
        return res
    
    def solve_in_position(self, pos, results):
        if not self.analyzed:
            self.analyze()
        # move left to the first character in the row left to pos
        while not self.is_empty(self.left(pos)):
            pos = self.left(pos)        
        while pos is not None:
            self.fit(pos, results)
            pos = self.left(pos)
        return results

    
    def fit(self, pos, results):
        #print("fitting at pos:",pos)
        #print("Board:", self.board)
        prefix = ""
        while not self.is_empty(pos):
            prefix += self.content(pos)
            pos = self.right(pos)
        _, node = self.wt.lookup(prefix)
        #print("prefix",prefix,"pos",pos)
        pointer = pos
        constraints = []
        given = []
        while pointer in self.positions:
            constraints.append(self.possible_chars[pointer])
            given.append(self.content(pointer) if not self.is_empty(pointer) else None)
            pointer = self.right(pointer)
        #print("constratints", constraints)
        #print("panel", panel)
        #print("node==root", node==self.wt.root)
        suffixes = []
        node.gather(self.panel, "", suffixes, given, constraints)
        for s in suffixes:
            results[pos].add(prefix+s)
        return results


    def solutions(self):
        if not self.analyzed:
            self.analyze()
        results = defaultdict(set)
        for p in self.attach_positions:
            c = self.copy()
            c.solve_in_position(p, results)        
        return results

    def read_downwards(self, pos):
        word = []
        while pos in self.positions and not self.is_empty(pos):
            word.append(self.content(pos))
            pos = self.down(pos)
        return "".join(word)

    def read_upwards(self, pos):
        word = []
        while pos in self.positions and not self.is_empty(pos):
            word.append(self.content(pos))
            pos = self.up(pos)
        return "".join(word)

    def is_empty(self, position):
        if position not in self.positions: return True
        return self.content(position) == "-"
    
    def content(self,position):
        assert position in self.positions
        return self.board[position[0]][position[1]]

    def left(self, pos):
        p = (pos[0], pos[1]-1)
        return p if p in self.positions else None

    def right(self, pos):
        p = (pos[0], pos[1]+1)
        return p if p in self.positions else None

    def up(self, pos):
        p = (pos[0]-1, pos[1])
        return p if p in self.positions else None

    def down(self, pos):
        p = (pos[0]+1, pos[1])
        return p if p in self.positions else None


s = Solver(board, panel, wt)
print("solve in 2,0:", s.solve_in_position(pos=(2,0),results=defaultdict(set)))
print("All solutions", s.solutions())
print("exiting")
import sys
sys.exit(0)


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


# def get_column(board,c):
#     return [board[r][c]) for r in range(len(board))]

# def score(board):
#     s = 0
#     for r in board:
#         s += score_single(r)
#     for c in range(len(board[0])):
#         column = get_column(board,c)
#         s += score_single(column)
#     return s



# #
# # Idea: 
# #

# plays = {}

# # def play_position(board,r,c,panel, base_score, played,direction):
# #     if board[r][c] != '-': return
# #     for i,v in enumerate(panel):        
# #         board[r][c] = v
# #         played.append(v)
# #         panel.pop(i)
# #         s = score(board)
# #         if s>base_score:
# #             plays[s-base_score] = (c-len(played) if direction=='right' else 0, r-len(played) if direction == 'down' else 0,"".join(reversed(played)), s-base_score)
# #         play_position(board,r + 1 if direction == 'down' else 0,
# #                       c + 1 if direction == 'right' else 0,panel, base_score, played, direction)
# #         board[r][c] = '-'
# #         played.pop()
# #         panel.insert(i,v)

# def play_column(board,r,c,panel):
#     if len(panel) == 0: return
#     column = get_column(board,c)
#     base_score = score_single(column)
    
    


# play_down(board,1,13,panel,score(board),[])
# print(plays)

# # # brute force
# # def subsets(l):
# #     #print(l)
# #     if len(l) == 0: return [[]]    
# #     s1 = subsets(l[1:])
# #     res = []
# #     for s in s1:
# #         # with and without the first element
# #         res.append(s)
# #         res.append([l[0]] + s)
# #     return res

# # from copy import copy

# # def permutations(l):
# #     #print(l)
# #     """
# #     given a list of items, return a list of lists
# #     with all orderings of the items
# #     """
# #     if len(l) == 0:
# #         return [[]]
# #     if len(l) == 1:
# #         return [[l[0]]]
# #     p1 = permutations(l[1:])
# #     #print(p1)
# #     res = []
# #     for p in p1:        
# #         for i in range(len(p1)+1):
# #             np = copy(p)
# #             np.insert(i,l[0])
# #             res.append(np)
# #     return res


# # #print(subsets(panel), len(subsets(panel)))
# # #print(score(board))
# # plays = []
# # for s in subsets(panel):
# #     #print(s)
# #     for p in permutations(s):
# #         plays.append(p)

# #print(plays,len(plays))