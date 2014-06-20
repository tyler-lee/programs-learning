import re



class LazyRules:
    '''
    这个版本的plural实现时，如果现有规则匹配则不需要从文件读取更新的规则，否则重新打开文件并定位到上次打开的位置，接着再读取一条规则，这个的问题在于可能出现需要反复打开文件的情况，耗费系统资源
    或者可以考虑另一种实现：即打开文件后一次性缓存所有的规则，后续则不再需要读取文件，当然这个的开销就是占用较多的内存
    '''
    rules_filename = 'rules.txt'

    def __init__(self):
        # define a cache for rules
        self.cache = []
        # initiate the position in rules_filename file
        self.position = 0

    def __iter__(self):
        self.cache_index = 0
        return self

    def __next__(self):
        self.cache_index += 1
        if len(self.cache) >= self.cache_index:
            return self.cache[self.cache_index - 1]

        with open(self.rules_filename, encoding='utf-8') as pattern_file:
            # turn to last position in rules_filename before last close
            pattern_file.seek(self.position)
            line = pattern_file.readline()
            # remember current position in rules_filename
            self.position = pattern_file.tell()
            if not line:
                raise StopIteration

            pattern, search, replace = line.split(None, 3)
            func = build_match_and_apply_functions(pattern, search, replace)
            self.cache.append(func)
            return func

def build_match_and_apply_functions(pattern, search, replace):
    def match_rule(noun):
        return re.search(pattern, noun)
    def apply_rule(noun):
        return re.sub(search, replace, noun)
    return (match_rule, apply_rule)


rules = LazyRules()


def plural(noun):
    for match_rule, apply_rule in rules:
        if match_rule(noun):
            return apply_rule(noun)
    raise ValueError('no matching rule for {0}'.format(noun))

