set nu
set hlsearch
syntax on
set cursorline
set tabstop=4
set cindent
set shiftwidth=4
set path +=.,/usr/include
set fileencodings=utf-8,gb18030,gbk,gb2312
call plug#begin('~/.vim/plugged')
Plug 'Valloric/YouCompleteMe', { 'do': './install.py --clang-completer',  'for': ['c', 'cpp'] }
call plug#end()
let g:ycm_global_ycm_extra_conf='~/.vim/plugged/YouCompleteMe/third_party/ycmd/.ycm_extra_conf.py'
