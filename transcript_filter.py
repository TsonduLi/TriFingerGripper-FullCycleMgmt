import re
import opencc
def transcript_filter_en(s):
    s = re.sub(r'[^A-Za-z0-9 ,.?!\'"-]+', '', s)
    if s.startswith("I'm going to go find a laundry") or s.startswith("If you enjoyed this video") or s.startswith("Thank you") or s.startswith("Silence") or s.startswith("Share this") or s.startswith("Bye") or len(s) < 6:
        return ""
    s = re.sub(r'thank you( so much)?', '', s, flags=re.IGNORECASE)
    return s

def transcript_filter_ch(s):
    s = re.sub(r'[^\u4e00-\u9fa5A-Za-z0-9 ,.?!\'"-]+', '', s)
        #繁体转换为简体
    converter = opencc.OpenCC('t2s')
    s = converter.convert(s)

    if '点赞订阅转发' in s or '明镜与点点' in s or s.startswith("I'm going to go find a laundry") or s.startswith("If you enjoyed this video") or s.startswith("Thank you") or s.startswith("Silence") or s.startswith("Share this") or s.startswith("Bye") or len(s) < 6:
        return ""
    
    s = re.sub(r'thank you( so much)?', '', s, flags=re.IGNORECASE)

    s = re.sub(r'thanks( so much)?', '', s, flags=re.IGNORECASE)
    #繁体转换为简体
    converter = opencc.OpenCC('t2s')
    s = converter.convert(s)
    return s

text = '你好，很高兴аa56awg,et'
if __name__ == '__main__':
    print(transcript_filter_ch(text))