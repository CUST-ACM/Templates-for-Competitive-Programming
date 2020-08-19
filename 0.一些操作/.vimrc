syntax on
set nu
set smarttab
set tabstop=4
set shiftwidth=4
set cindent
set mouse=a
map <F9> :call CR()<CR>

func! CR()
    exec "w"
    if &filetype=='cpp'
        exec "!g++ -O2 -std=c++11 % -o %< && ./%<"
    elseif &filetype=='python'
        exec "!python3 %"
    endif
endfunc
