'''
这个文档是为了说明getattr函数的使用，可以用在动态构建函数调用上
有点类似于C++类中的动态函数
'''
class Father:
    '''
    这个是父类
    '''
    def callback(self, prefix, name, *args):
        func = getattr(self, prefix + name, None);
        if callable(func):
            return func(*args)

    def start(self, name):
        self.callback('start_', name)
    def end(self, name):
        self.callback('end_', name)


class Child:
    '''
    这个是子类
    '''
    def action(self, father):
        father.start(self.type)
        father.end(self.type)
        return True

class Child_1(Child):
    type = 'child_1'
class Child_2(Child):
    type = 'child_2'
class Child_3(Child):
    type = 'child_3'

class Main(Father):
    def start_child_1(args):
        print('start_child_1')
    def end_child_1(args):
        print('end_child_1')
    def start_child_2(args):
        print('start_child_2')
    def end_child_2(args):
        print('end_child_2')
    def start_child_3(args):
        print('start_child_3')
    def end_child_3(args):
        print('end_child_3')


father = Main()
child_1 = Child_1()
child_2 = Child_2()
child_3 = Child_3()

print('Test Begin')
child_1.action(father)
child_3.action(father)
child_2.action(father)
print('Test End')

