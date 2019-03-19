" dw's little .vimrc for Linux. Include by making 
" source /path/to/this/file 
" your only(?) line in $MYVIMRC. 
set vb t_vb=
set nobackup
set nowb
set noswapfile
set hidden
set ruler
set hlsearch
syntax enable
set encoding=utf-8
" Tabs and spaces
set tabstop=8
set shiftwidth=2
set softtabstop=2
set expandtab
" Visual tabs
set list
set listchars=tab:→·
if has("autocmd")
  filetype plugin indent on
endif
" special tab settings for golang
autocmd Filetype go setlocal nolist tabstop=2

set backspace=indent,eol,start         " let backspace delete everything, not just inserted text
set incsearch                          " jump to search result while typing
language messages en_US.utf8
:let mapleader = ","

if has("gui_running")
  set guifont=Courier\ New:h10:cANSI
endif

let g:netrw_banner = 0                 " avoid useless netrw banner
let g:netrw_liststyle = 1              " add size and file info
let g:netrw_altfile = 1                " no Ctrl-^ to netrw buffers

set wildmode=longest,list,full         " (almost) Bash-style tab-completion
set wildmenu
set wildignore=*.o,*.class,*.exe,*.a,*.so,*.dll,*.pyc

set path=.,,

" Find tags file in current buffer's directory or any dir up the tree.
set tags=./tags;

" Move line up/down
nnoremap j :m .+1<CR>==
nnoremap k :m .-2<CR>==
nnoremap <Leader>s :update<CR>
nnoremap <Leader>w :bd<CR>
nnoremap <Leader>a :Ack<Space>
" Find word under cursor
nnoremap <Leader>A :Ack<Space><C-R><C-W> 
nnoremap <Leader>m :make<CR>
nnoremap <Leader>b :ls<CR>:b<Space>
nnoremap <Leader>e :Explore<CR>
nnoremap <Leader>t :CtrlPTag<CR>
nnoremap <Leader>r :CtrlPMRUFiles<CR>

" Navigate through quickfix list
nnoremap <C-j> :cn<CR>
nnoremap <C-k> :cp<CR>
nnoremap <C-l> :nohlsearch<CR><C-l>
" Next/previous buffer
nnoremap [b :bprevious<CR>
nnoremap ]b :bnext<CR>
" Next/previous quickfix item
nnoremap [q :cprev<CR>
nnoremap ]q :cnext<CR>
" make * search for selected text in visual mode
vnoremap * y/\V<C-r>=escape(@",'/\')<CR><CR>


" set makeprg=mingw32-make.exe
if executable('ag')
  let g:ackprg = 'ag --vimgrep'
endif

execute pathogen#infect()

" let g:ctrlp_custom_ignore = 'node_modules/\|\.git/'

