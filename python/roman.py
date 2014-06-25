import re

# build a map between digit numerals and roman numerals
base_digit = (1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1)
base_roman = ('M', 'CM', 'D', 'CD', 'C', 'XC', 'L', 'XL', 'X', 'IX', 'V', 'IV', 'I')
numeral_roman_map = tuple(zip(base_digit,base_roman))

# define max value that romans can stand for
MAX_ROMAN = 5000

# valid roman numerals regular pattern
roman_numeral_pattern = re.compile('''
        ^                   # beginning of string
        M{0,4}              # thousands: 0-3 Ms
        (CM|CD|D?C{0,3})    # hundreds: 900(CM), 400(CD), 0/100/200/300(0-3 Cs)
                            #           500/600/700/800(D, followed by 0-3 Cs)
        (XC|XL|L?X{0,3})    # tens: 90(XC), 40(XL), 0/10/20/30(0-3 Xs)
                            #           50/60/70/80(L, followed by 0-3 Xs)
        (IX|IV|V?I{0,3})    # ones: 9(IX), 4(IV), 0/1/2/3(0-3 Is)
                            #           5/6/7/8(V, followed by 0-3 Is)
        $                   # end of string
        ''', re.VERBOSE)

############## roman.to_roman begin ###############
def to_roman(digit_numeral):
    '''
    convert the given numeral into roman format.
    the given numeral should be between 0 and MAX_ROMAN
    '''
    return to_roman_v2(digit_numeral)

# to_roman_v2: with static digit and roman numerals map table
def to_roman_v2(digit_numeral):
    if not (0 < digit_numeral < MAX_ROMAN):
        raise OutOfRangeError('number out of range (must be 1..{}'.format(MAX_ROMAN-1))
    if not isinstance(digit_numeral, int):
        raise NotIntergerError('non-intergers can not be converted')

    return to_roman_table[digit_numeral]

# to_roman_v1: regular process
def to_roman_v1(digit_numeral):
    result = ''
    if not (0 < digit_numeral < MAX_ROMAN):
        raise OutOfRangeError('number out of range (must be 1..{}'.format(MAX_ROMAN-1))
    if not isinstance(digit_numeral, int):
        raise NotIntergerError('non-intergers can not be converted')

    for num, rom in numeral_roman_map:
        while digit_numeral >= num:
            result += rom
            digit_numeral -= num

    return result
############## roman.to_roman end ###############

############## roman.from_roman begin ###############
def from_roman(roman_numeral):
    '''
    convert the given roman numeral into digit format.
    the given numeral should be an legal roman numeral expression
    '''
    return from_roman_v2(roman_numeral)

# from_roman_v2: with static digit and roman numerals map table
def from_roman_v2(roman_numeral):
    if not isinstance(roman_numeral, str):
        raise InvalidRomanNumeralError('input should be a string')
    if not roman_numeral:
        raise InvalidRomanNumeralError('input should not be blank')
    if roman_numeral not in from_roman_table:
        raise InvalidRomanNumeralError('invalid roman numeral: {}'.format(roman_numeral))

    return from_roman_table[roman_numeral]

# from_roman_v1: regular process
def from_roman_v1(roman_numeral):
    if not isinstance(roman_numeral, str):
        raise InvalidRomanNumeralError('input should be a string')
    if not roman_numeral_pattern.search(roman_numeral):
        raise InvalidRomanNumeralError('invaild roman numerals: {}'.format(roman_numeral))
    if not roman_numeral:
        raise InvalidRomanNumeralError('input should not be blank')

    result = 0
    index = 0
    for num, rom in numeral_roman_map:
        while roman_numeral[index:index+len(rom)] == rom:
            result += num
            index += len(rom)
            #print('found', rom, 'of length', len(rom), ', add', num)

    return result
############## roman.from_roman end ###############

############# build up map tables for version 2 ##############
# build up digit and roman map tables
to_roman_table = {}
#to_roman_table = [None]
from_roman_table = {}
def build_digit_roman_map_tables():
    def to_roman(digit_numeral):
        result = ''
        for num, rom in numeral_roman_map:
            if digit_numeral >= num:
                result = rom
                digit_numeral -= num
                break

        if digit_numeral > 0:
            result += to_roman_table[digit_numeral]

        return result

    for digit_numeral in range(1, MAX_ROMAN):
        roman_numeral = to_roman(digit_numeral)
        #to_roman_table.append(roman_numeral)
        to_roman_table[digit_numeral] = roman_numeral
        from_roman_table[roman_numeral] = digit_numeral

build_digit_roman_map_tables()
##########################################################

class OutOfRangeError(ValueError):
    pass

class NotIntergerError(Exception):
    pass
class InvalidRomanNumeralError(Exception):
    pass
