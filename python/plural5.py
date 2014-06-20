import re


def build_match_and_apply_functions(pattern, search, replace):
    def match_rule(noun):
        return re.search(pattern, noun)
    def apply_rule(noun):
        return re.sub(search, replace, noun)
    return (match_rule, apply_rule)


def rules(rules_filename):
    with open(rules_filename, encoding='utf-8') as rules_file:
        for line in rules_file:
            pattern, search, replace = line.split(None, 3)
            yield build_match_and_apply_functions(pattern, search, replace)


def plural(noun, rules_filename = 'rules.txt'):
    for match_rule, apply_rule in rules(rules_filename):
        if match_rule(noun):
            return apply_rule(noun)
    raise ValueError('no matching rule for {0}'.format(noun))


