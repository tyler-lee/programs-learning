import re


def build_match_and_apply_functions(pattern, search, replace):
    def match_rule(noun):
        return re.search(pattern, noun)
    def apply_rule(noun):
        return re.sub(search, replace, noun)
    return (match_rule, apply_rule)


def rules_generator(rules_filename):
    rules = []
    with open(rules_filename, encoding='utf-8') as rules_file:
        for line in rules_file:
            pattern, search, replace = line.split(None, 3)
            rules.append(build_match_and_apply_functions(pattern,
                search, replace))
    return rules


rules = rules_generator('rules.txt')
def plural(noun):
    for match_rule, apply_rule in rules:
        if match_rule(noun):
            return apply_rule(noun)
    raise ValueError('no matching rule for {0}'.format(noun))

def plural(noun):
    for match_rule, apply_rule in rules:
        if match_rule(noun):
            return apply_rule(noun)
    raise ValueError('no matching rule for {0}'.format(noun))
