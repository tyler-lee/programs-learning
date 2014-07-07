'''class Fib:

    def __init__(self, max):
        self.max = max

    def __iter__(self):
        self.a = 0
        self.b = 1
        return self

    def __next__(self):
        fib = self.a
        if fib > self.max:
            raise StopIteration
        self.a, self.b = self.b, self.a + self.b
        return fib
'''
def fib(n):
    if n in (0,1):
        return n
    else:
        return fib(n-1) + fib(n-2)
