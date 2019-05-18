#!/bin/bash
tar cvf zsk_`date +%Y-%m-%d-%H`_beifen.tar 2019* baiduwangpan/ chat/ shell/ sort/
gzip zsk_`date +%Y-%m-%d-%H`_beifen.tar
