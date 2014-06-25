
base_digit = (1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1)
base_roman = ('M', 'CM', 'D', 'CD', 'C', 'XC', 'L', 'XL', 'X', 'IX', 'V', 'IV', 'I')
numeral_roman_map = tuple(zip(base_digit,base_roman))

#define max value that romans can stand for
MAX_ROMAN = 4000

############## roman.to_roman begin ###############
def to_roman(digit_numeral):
    '''
    convert the given numeral into roman format.
    the given numeral should be between 0 and MAX_ROMAN
    '''
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
    result = 0
    index = 0
    for num, rom in numeral_roman_map:
        while roman_numeral[index:index+len(rom)] == rom:
            result += num
            index += len(rom)
            #print('found', rom, 'of length', len(rom), ', add', num)

    return result
############## roman.from_roman end ###############

class OutOfRangeError(ValueError):
    pass

class NotIntergerError(Exception):
    pass
