#  Good morning! Here's your coding interview problem for today.
#  
#  This problem was asked by Microsoft.
#  
#  Implement 3 stacks using a single list:
#  
#  class Stack:
#      def __init__(self):
#          self.list = []
#  
#      def pop(self, stack_number):
#          pass
#  
#      def push(self, item, stack_number):
#          pass
#  


# Solution 2:
# use every 3rd element for each stack

class Stack2:
    def __init__(self):
        self.list = []
        self.sizes = [0,0,0]

    def _validate_stack_number(self, n):
        assert 0 <= n < len(self.sizes)

    # keep the internal list tidy
    # only consider the last part of the internal list
    # needs to be called after every changing operation!
    def _consolidate_state(self):
        #print('>>>', self.sizes, self.list)
        # make sure the list is able to hold the maimum element for each stack
        max_size = max(self.sizes)
        needed_length = len(self.sizes) * max_size
        if len(self.list) < needed_length:
            self.list.extend([None] * len(self.sizes))
        if len(self.list) > needed_length:
            self.list = self.list[:needed_length]
        for i, s in enumerate(self.sizes):
            if s < max_size:
                self.list[len(self.list) - len(self.sizes) + i] = None
        #print('>>>>>>', self.sizes, self.list)


    def top_pos(self, stack_number):        
        res = stack_number + (self.sizes[stack_number] - 1) * len(self.sizes) 
        #print(f'... top_pos({stack_number})=', res)
        return res

    # we return None if the stack has no top element
    def pop(self, stack_number):
        self._validate_stack_number(stack_number)
        if self.sizes[stack_number] == 0:
            return None
        result = self.list[self.top_pos(stack_number)]
        self.sizes[stack_number] -= 1
        self._consolidate_state()
        return result

    def push(self, item, stack_number):
        self._validate_stack_number(stack_number)
        self.sizes[stack_number] += 1
        self._consolidate_state()
        self.list[self.top_pos(stack_number)] = item

def test_stack_21():
    s: Stack2 = Stack2()
    assert s.pop(0) is None
    assert s.pop(1) is None
    assert s.pop(2) is None

def test_stack_22():
    s: Stack2 = Stack2()
    s.push('a',0)
    s.push('b',1)
    s.push('c',2)
    assert s.pop(0) == 'a'
    assert s.pop(0) is None

# Solution 1:
# Put three stacks in the list :-)
class Stack:
    def __init__(self):
        self.list = []

    """
    Removes and returns the top item of stack number stack_number1
    Returns None is stack is empty.
    """
    def pop(self, stack_number):
        if len(self.list)-1 < stack_number:
            return None
        #print('>>>>>>>>',len(self.list))
        if len(self.list[stack_number]) > 0:
            return self.list[stack_number].pop()
        return None

    """Adds an item on top of the stack with number stack_number"""
    def push(self, item, stack_number):
        if len(self.list)-1 < stack_number:
            self.list.extend([[]] * (stack_number - len(self.list) + 1))
        self.list[stack_number].append(item)


def test_stack_1():
    s: Stack = Stack()
    assert s.pop(0) is None
    assert s.pop(1) is None
    assert s.pop(2) is None

def test_stack_2():
    s: Stack = Stack()
    s.push('a',0)
    assert s.pop(0) == 'a'
    assert s.pop(0) is None
