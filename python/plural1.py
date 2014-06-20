import re

def plural(noun):
    '''
    如果某个单词以 S 、X 或 Z 结尾，添加 ES 。Bass 变成 basses， fax 变成 faxes，而 waltz 变成 waltzes。
    如果某个单词以发音的 H 结尾，加 ES；如果以不发音的 H 结尾，只需加上 S 。什么是发音的 H ？指的是它和其它字母组合在一起发出能够听到的声音。因此 coach 变成 coaches 而 rash 变成 rashes，因为在说这两个单词的时候，能够听到 CH 和 SH 的发音。但是 cheetah 变成 cheetahs，因为 H 不发音。
    如果某个单词以发 I 音的字母 Y 结尾，将 Y 改成 IES；如果 Y 与某个原因字母组合发其它音的话，只需加上 S 。因此 vacancy 变成 vacancies，但 day 变成 days 。
    如果所有这些规则都不适用，只需加上 S 并作最好的打算。
    '''

    if re.search('[sxz]$', noun):
        return re.sub('$', 'es', noun)
    elif re.search('[^aeioudgkprt]h$', noun):
        return re.sub('$', 'es', noun)
    elif re.search('[^aeiou]y$', noun):
        return re.sub('y$', 'ies', noun)
    else:
        return noun + 's'


