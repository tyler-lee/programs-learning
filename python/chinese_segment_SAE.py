import urllib.request
import urllib.parse

#chinese_text = """
#这里填上需要分词的文本
#"""
def chinese_segment(chinese_text):
    '''
    这个程序是新浪SAE上的例子，这里进行简单的测试。
    参考链接：http://sae.sina.com.cn/doc/python/segment.html
    '''

    _SEGMENT_BASE_URL = 'http://segment.sae.sina.com.cn/urlclient.php'
    values = { 'content': chinese_text,
                'word_tag': 1,
                'encoding': 'utf-8'
            }

    data = urllib.parse.urlencode(values)
    url = _SEGMENT_BASE_URL + '?' + data
    #request = urllib.request.Request(url, data)
    response = urllib.request.urlopen(url)
    result = response.read().decode('utf-8')

    #payload = urllib.parse.urlencode([('context', chinese_text),])
    #args = urllib.parse.urlencode([('word_tag', 1), ('encoding', 'UTF-8'),])
    #url = _SEGMENT_BASE_URL + '?' + args
    #result = urllib.request.urlopen(url, payload)

    return result



if __name__ == '__main__':
    import sys
    for chinese_text in sys.argv[1:]:
        print(chinese_text)
        solution = chinese_segment(chinese_text)
        if solution:
            print(solution)

