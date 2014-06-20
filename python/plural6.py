import re



class LazyRules:
    rules_filename = 'rules.txt'

    def __init__(self):
        self.pattern_file = open(self.rules_filename, encoding='utf-8')
        self.cache = []

    def __iter__(self):
        self.cache_index = 0
        return self

    def __next__(self):
        self.cache_index += 1
        if len(self.cache) >= self.cache_index:
            return self.cache[self.cache_index - 1]

        if self.pattern_file.closed:
            raise StopIteration

        line = self.pattern_file.readline()
        if not line:
            self.pattern_file.close()
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

