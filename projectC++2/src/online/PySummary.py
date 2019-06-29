#!/usr/bin/env python
# coding=utf-8

import xmnlp
xmnlp.set_stopword('/home/ubuntu/downloads/simhash/dict/stop_words.utf8')

def parse_string(str):
    res = ''
    for p in xmnlp.keyphrase(str):
        res = res+''.join(p)+','
    
    return (res)

