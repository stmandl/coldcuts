from __future__ import annotations
from dataclasses import dataclass
from typing import Generator

@dataclass
class Pos:
    x: int
    y: int

    def __add__(self, other):
        return Pos(self.x + other.x, self.y + other.y)

class Board:

    def __init__(self, width, height) -> None:
        self.width = width
        self.height = height
        self.tiles = [[0 for _ in range(width)] for _ in range(height)]

    def is_empty(self, pos: Pos) -> bool:
        return self.tiles[pos.y][pos.x] == 0
    
    def set(self, pos: Pos, color: int) -> bool:
        assert self.is_empty(pos)
        assert color > 0
        self.tiles[pos.y][pos.x] = color
    
    def is_valid_position(self, pos: Pos) -> bool:
        return 0 <= pos.x < self.width and 0 <= pos.y < self.height
    
    def __str__(self) -> str:
        return '\n'.join(["|"+''.join(map(lambda c: str(c) if c >0 else ' ',line))+"|" for line in self.tiles])+'\n'+"".join(['-']*(self.width+2))

class Tetromino:

    def __init__(self, pixels, color) -> None:
        '''
        for example of pixels, see subclasses
        '''
        self.pixels = pixels 
        self.color = color
    
 
    def width(self) -> int:
        return len(self.pixels[0])

    def height(self) -> int:
        return len(self.pixels)  

    def fits(self, board: Board, position: Pos) -> bool:
        for local_pos in self.positions():
            board_pos = position + local_pos
            if not board.is_valid_position(board_pos):
                print("not a valid board position: ", board_pos)
            if not board.is_valid_position(board_pos) or \
                (not board.is_empty(board_pos) and not self.is_empty(local_pos)):
                return False
        return True
    
    def is_empty(self, pos: Pos):
        return self.pixel_value(pos) == 0

    def pixel_value(self, pos:Pos):
        return self.pixels[pos.y][pos.x]

    def rotated(self, board, position) -> Tetromino:
        pixels = [[self.pixels[y][len(self.pixels[0])-1-x] for y in range(len(self.pixels))] for x in range(len(self.pixels[0]))]
        return Tetromino(pixels,self.color)        

    
    def put(self, board: Board, position: Pos, erase=False):
       assert self.fits(board,position), f"no fit at position {position}"
       for local_pos in self.positions():
            board_pos = position + local_pos
            if not self.is_empty(local_pos):
                board.set(board_pos, self.color if not erase else 0)
    
    def erase(self, board: Board, position: Pos):
        self.put(board, position, erase=True)

    def positions(self) -> Generator[Pos, None, None]:
        for y in range(self.height()):
            for x in range(self.width()):
                yield Pos(x,y)

    def __str__(self) -> str:
        return '\n'.join([''.join(map(str,line)) for line in self.pixels])

#  y' -> w - x , x' <- y
# 
#  [1,0],
#  [1,0],
#  [1,1],
#
#  [0,0,1]
#  [1,1,1]

class L(Tetromino):
    def __init__(self) -> None:
        pixels = [
            [1,0],
            [1,0],
            [1,1],
        ]
        super().__init__(pixels,1)

class J(Tetromino):
    def __init__(self) -> None:
        pixels = [
            [0,1],
            [0,1],
            [1,1],
        ]
        super().__init__(pixels,2)

class I(Tetromino):
    def __init__(self) -> None:
        pixels = [
            [1,1,1,1],
        ]
        super().__init__(pixels,3)

class O(Tetromino):
    def __init__(self) -> None:
        pixels = [
            [1,1],
            [1,1],
        ]
        super().__init__(pixels,4)

class T(Tetromino):
    def __init__(self) -> None:
        pixels = [
            [1,1,1],
            [0,1,0],
        ]
        super().__init__(pixels,5)

class S(Tetromino):
    def __init__(self) -> None:
        pixels = [
            [0,1,1],
            [1,1,0],
        ]
        super().__init__(pixels,6)

class Z(Tetromino):
    def __init__(self) -> None:
        pixels = [
            [1,1,0],
            [0,1,1],
        ]
        super().__init__(pixels,7)


z = Z()
print(z)
print()
print(z.rotated(None,None))
print()
print(z.rotated(None,None).rotated(None,None))
print(list(z.positions()))

board = Board(15,15)
print(board)

z.put(board,Pos(10,10))
print(board)