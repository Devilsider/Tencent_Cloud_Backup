#!/usr/bin/env python
# coding=utf-8
import xmnlp
xmnlp.set_stopword('/home/ubuntu/downloads/simhash/dict/stop_words.utf8')
doc = """自然语言处理: 是人工智能和语言学领域的分支学科。
在这此领域中探讨如何处理及运用自然语言；自然语言认知则是指让电脑“懂”人类的语言。 
自然语言生成系统把计算机数据转化为自然语言。自然语言理解系统把自然语言转化为计算机程序更易于处理的形式。"""

res='' 
for p in xmnlp.keyphrase(doc):
    res=res+''.join(p)+','
    print(''.join(p))

print(res)

#f = open('./test.txt','w')
#f.write(xmnlp.keyphrase(doc))
