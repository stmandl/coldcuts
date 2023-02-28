# # HalHello World
# # again and again

class Editor:

    def __init__(self) -> None:
        self.buf = ""
        self.pos = 0 # next insert position
    
    def insert(self, c):
        self.buf = self.buf[:self.pos] + c + self.buf[self.pos:]
        self.pos += 1

    def goto_line_start(self):
        while self.pos > 0:
            if self.buf[self.pos-1] == '\n':
                break
            self.pos -= 1

    def goto_line_end(self):
        while self.pos < len(self.buf)-1:
            if self.buf[self.pos] == '\n':
                break
            self.pos += 1
    
    def left(self):
        if self.pos > 0:
            self.pos -= 1
    
    def right(self):
        if self.pos < len(self.buf)-1:
            self.pos += 1

    def count_to_start(self):
        p = self.pos
        c = 0
        while p > 0:
            if self.buf[p-1] == '\n':
                break
            p -= 1
            c += 1
        return c

    def down(self):
        offs = self.count_to_start()        
        self.goto_line_end()
        self.right()
        for _ in range(offs):
            self.right()


    def up(self):
        offs = self.count_to_start()        
        self.goto_line_start()
        self.left()
        self.goto_line_start()
        for _ in range(offs):
            self.right()

    def show(self):
        print(self.buf)

ed = Editor()
for c in "Hello World":
    ed.insert(c)
ed.insert("\n")
for c in "you suckers":
    ed.insert(c)

ed.goto_line_start()
print(ed.pos)
ed.left()
print(ed.pos)
ed.goto_line_start()
print(ed.pos)
ed.right()
ed.right()
print(ed.pos)
ed.insert("-")
ed.left()
print('pos:',ed.pos)
ed.down()
ed.insert("-")
ed.right()
ed.insert("*")
ed.left()
ed.up()
ed.insert("*")
print(ed.pos)
# ed.insert("\n")
# for c in "again and again":
#     ed.insert(c)
# ed.up()
# ed.show()
# ed.insert("!")
# ed.show()
# ed.down()
# ed.insert("?")
ed.show()