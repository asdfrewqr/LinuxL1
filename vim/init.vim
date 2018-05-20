"""""""""""""""""""""""""" vim-plug 插件管理器
" PlugInstall 安装插件
" PlugUpgrade 更新 vim-plug 自身
call plug#begin('~/.vim/bundle')
Plug 'Valloric/YouCompleteMe'
Plug 'bling/vim-airline'
Plug 'vim-airline/vim-airline-themes'
Plug 'morhetz/gruvbox'
Plug 'octol/vim-cpp-enhanced-highlight'
Plug 'SirVer/ultisnips'
Plug 'tpope/vim-surround'
Plug 'flazz/vim-colorschemes'
Plug 'scrooloose/nerdtree'
Plug 'python-mode/python-mode'
Plug 'scrooloose/nerdcommenter'
Plug 'Yggdroot/LeaderF'
Plug 'cpiger/NeoDebug'
Plug 'cpiger/NeoDebug'
Plug 'ryanoasis/vim-devicons'
Plug 'autozimu/LanguageClient-neovim', {
    \ 'branch': 'next',
    \ 'do': 'bash install.sh',
    \ }
call plug#end()


"""""""""""""""""""""""""" 主题
" colorscheme atom
" colorscheme molokai
colorscheme luna-term

" 以下为 gruvbox 主题专用 
" colorscheme gruvbox
" let g:gruvbox_contrast_light="light"
" let g:gruvbox_contrast_dark="hard"
" let g:gruvbox_improved_warnings=1


"""""""""""""""""""""""""" 零碎配置
set hlsearch
let mapleader = ";" 
set nu
behave mswin
syntax on
set si
set ai
set nowritebackup
set backspace=indent,eol,start
set expandtab
set tabstop=2
set softtabstop=2
set shiftwidth=2
set fileencodings=utf-8,gbk,cp936,cp950,latin1
set encoding=utf-8
set ruler
set showcmd
set incsearch
set ruler
set foldmethod=marker
filetype plugin on
" 不吱吱叫
set noeb vb t_vb=
set cursorline
" 文件修改之后自动载入
set autoread
" 在上下移动光标时，光标的上方或下方至少会保留显示的行数
set scrolloff=5
" 左下角不显示当前vim模式
set noshowmode

if has("autocmd")
  au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif
endif


"""""""""""""""""""""""""" airline 彩色状态栏/标签页
" 这几个是挑选的还不错的几个 airline 主题
" let g:airline_theme="ravenpower"
" let g:airline_theme="minimalist"
" let g:airline_theme="kolor"
" let g:airline_theme="jellybeans"
" let g:airline_theme="distinguished"
" let g:airline_theme="base16_google"
let g:airline_theme="behelit"

set helplang=cn
set ambiwidth=double
let g:airline_powerline_fonts = 1
let g:airline#extensions#tabline#enabled = 1
let g:airline#extensions#tabline#buffer_nr_show = 1
" 关闭状态显示空白符号计数
let g:airline#extensions#whitespace#enabled = 0
let g:airline#extensions#whitespace#symbol = '!'
" 设置consolas字体
set guifont=Consolas\ for\ Powerline\ FixedD:h11
if !exists('g:airline_symbols')
  let g:airline_symbols = {}
endif
" unicode symbols
let g:airline_left_sep = '»'
let g:airline_left_sep = '▶'
let g:airline_right_sep = '«'
let g:airline_right_sep = '◀'
let g:airline_symbols.crypt = '🔒'
let g:airline_symbols.linenr = '☰'
let g:airline_symbols.linenr = '␊'
let g:airline_symbols.linenr = '␤'
let g:airline_symbols.linenr = '¶'
let g:airline_symbols.maxlinenr = ''
let g:airline_symbols.maxlinenr = '㏑'
let g:airline_symbols.branch = '⎇'
let g:airline_symbols.paste = 'ρ'
let g:airline_symbols.paste = 'Þ'
let g:airline_symbols.paste = '∥'
let g:airline_symbols.spell = 'Ꞩ'
let g:airline_symbols.notexists = '∄'
let g:airline_symbols.whitespace = 'Ξ'

" powerline symbols
let g:airline_left_sep = ''
let g:airline_left_alt_sep = ''
let g:airline_right_sep = ''
let g:airline_right_alt_sep = ''
let g:airline_symbols.branch = ''
let g:airline_symbols.readonly = ''
let g:airline_symbols.linenr = '☰'
" let g:airline_symbols.maxlinenr = ''
let g:airline_symbols.maxlinenr = ''

" old vim-powerline symbols
let g:airline_left_sep = '⮀'
let g:airline_left_alt_sep = '⮁'
let g:airline_right_sep = '⮂'
let g:airline_right_alt_sep = '⮃'
let g:airline_symbols.branch = '⭠'
let g:airline_symbols.readonly = '⭤'
" let g:airline_symbols.linenr = '⭡'
let g:airline_symbols.linenr = ''


"""""""""""""""""""""""""" 代码折叠(按下 zz 快速折叠/展开函数)
set foldenable
" 折叠方法
" manual    手工折叠
" indent    使用缩进表示折叠
" expr      使用表达式定义折叠
" syntax    使用语法定义折叠
" diff      对没有更改的文本进行折叠
" marker    使用标记进行折叠, 默认标记是 {{{ 和 }}}
set foldmethod=indent
set foldlevel=99
" 代码折叠自定义快捷键 zz
let g:FoldMethod = 0
fun! ToggleFold()
    if g:FoldMethod == 0
        exe "normal! zM"
        let g:FoldMethod = 1
    else
        exe "normal! zR"
        let g:FoldMethod = 0
    endif
endfun


"""""""""""""""""""""""""" 快速运行(按下 F5 快速运行)
func! Compile()
    exec "w"
    if &filetype == 'c'
      exec "!gcc -g % -o %<"
      exec "!./%<"
    elseif &filetype == 'cpp'
      exec "!g++ -g % -o %<"
      exec "!./%<"
    elseif &filetype == 'cc'
      exec "!g++ -g % -o %<"
      exec "!./%<"
    elseif &filetype == 'python'
      exec "!python %"
    elseif &filetype == 'sh'
      exec "!sh %"
    endif
endfunc


"""""""""""""""""""""""""" YouCompleteMe
set completeopt=longest,menu
autocmd InsertLeave * if pumvisible() == 0|pclose|endif
inoremap <expr> <CR> pumvisible() ? "\<C-y>" : "\<CR>"

let g:ycm_global_ycm_extra_conf = '~/.ycm_extra_conf.py'
let g:ycm_confirm_extra_conf = 0
"let g:ycm_key_invoke_completion='<C-j>'
let g:ycm_error_symbol = 'E>'
let g:ycm_warning_symbol = 'W>'
" 使用 NerdFont 中的图标表示错误和警告
" let g:ycm_error_symbol = '﯇'
" let g:ycm_warning_symbol = '卵'
let g:ycm_enable_diagnostic_signs = 1
let g:ycm_enable_diagnostic_highlighting = 1
let g:ycm_collect_identifiers_from_comments_and_strings = 0
let g:ycm_complete_in_comments = 1
let g:ycm_complete_in_strings = 1
let g:ycm_min_num_of_chars_for_completion = 2
let g:ycm_python_binary_path = 'python'
let g:ycm_semantic_triggers =  {
      \ 'c,cpp,python,java,go,erlang,perl': ['re!\w{2}'],
      \ 'cs,lua,javascript': ['re!\w{2}'],
      \}


"""""""""""""""""""""""""" Tagbar(函数列表)
let g:tagbar_ctags_bin='/usr/bin/ctags'
let g:tagbar_width=20
let g:tagbar_left=1
let g:tagbar_sort = 0


"""""""""""""""""""""""""" NERDTree(文件列表)
let g:NERDTreeWinPos="right"
let g:NERDTreeWinSize=20


"""""""""""""""""""""""""" CtrlP(快速查找文件)
" let g:ctrlp_working_path_mode='a'


"""""""""""""""""""""""""" cpp-enhanced-highlight(c++ 语法高亮)
" 高亮类，成员函数，标准库和模板
let g:cpp_class_scope_highlight = 1
let g:cpp_member_variable_highlight = 1
let g:cpp_concepts_highlight = 1
let g:cpp_experimental_simple_template_highlight = 1
" 文件较大时使用下面的设置高亮模板速度较快，但会有一些小错误
let g:cpp_experimental_template_highlight = 1


"""""""""""""""""""""""""" UltiSnips(代码模板)
let g:UltiSnipsExpandTrigger="<C-j>"
let g:UltiSnipsListSnippets="<C-e>"
let g:UltiSnipsJumpForwardTrigger="<C-j>"
let g:UltiSnipsJumpBackwardTrgger="<C-k>"


"""""""""""""""""""""""""" LeaderF
let g:Lf_WindowHeight = 0.30


"""""""""""""""""""""""""" cquery
let g:LanguageClient_serverCommands = {
  \ 'cpp': ['~/.VimForCpp/cquery/bin/cquery', '--log-file=/tmp/cquery/cq.log'],
  \ 'cxx': ['~/.VimForCpp/cquery/bin/cquery', '--log-file=/tmp/cquery/cq.log'],
  \ 'hpp': ['~/.VimForCpp/cquery/bin/cquery', '--log-file=/tmp/cquery/cq.log'],
  \ 'cc': ['~/.VimForCpp/cquery/bin/cquery', '--log-file=/tmp/cquery/cq.log'],
  \ 'c': ['~/.VimForCpp/cquery/bin/cquery', '--log-file=/tmp/cquery/cq.log'],
  \ 'h': ['~/.VimForCpp/cquery/bin/cquery', '--log-file=/tmp/cquery/cq.log'],
\ }

let g:LanguageClient_loadSettings = 1
let g:LanguageClient_settingsPath = '/tmp/cquery/settings.json'

" 关闭 cquery 的诊断信息, 使用 Ycm 的足矣
let g:LanguageClient_diagnosticsEnable=0

" 指定项目的根目录标记.
let g:LanguageClient_rootMarkers = ['.root', '.svn', '.git']


"""""""""""""""""""""""""" 按键映射(统一规划)

""" 窗口
" 切换 .h / .c
nnoremap <space>aa :AT<cr>
" 快速打开标签页
nnoremap <space>as :tabe 
" 打开函数列表
nnoremap <space>ad :TagbarToggle<CR>
" 打开文件列表
nnoremap <space>af :NERDTreeToggle<RETURN>

""" 查找
" 按MRU规则查找文件
nnoremap <space>sa :LeaderfMru<cr>
" 查找当前文件中的函数
nnoremap <space>ss :LeaderfFunction<cr>
" 在所有 buffer 中进行函数查找
nnoremap <space>sd :LeaderfBuffer<cr>
" 按文件名查找文件
" let g:Lf_ShortcutF = '<c-p>'
let g:Lf_ShortcutF = '<space>sf'

""" 调试
" 使用 cquery 能得到更好的跳转效果.
nnoremap <space>da :call Compile()<cr>

""" 语义
" 跳转到定义
nnoremap <c-k> :YcmCompleter GoToDefinitionElseDeclaration<CR>
" 返回到跳转前的位置
nnoremap <c-l> <c-o>
nnoremap <space>fa :call LanguageClient_textDocument_definition()<CR>
" 查找所有被调用的函数. 此处有点瑕疵. 由于cquery中的操作都是异步完成的, 可能调用列表还没生成就尝试 lopen, 导致没有得到任何结果
nnoremap <space>fs :call LanguageClient_textDocument_references()<CR>:lopen<CR>
nnoremap <space>fd :call LanguageClient_textDocument_rename()<CR>
" 修正光标处的代码错误
nnoremap <space>ff :YcmCompleter FixIt<CR>
" 查看光标处的函数信息
nnoremap <space>fg :call LanguageClient_textDocument_hover()<CR>
" 诊断错误
nnoremap <space>fq :YcmDiags<CR>

""" 格式
" 添加文档注释
nnoremap <space>ga :Dox<RETURN><ESC>
" 函数折叠
nnoremap <space>gs :call ToggleFold()<cr>

""" 其他
" 调整窗口移动
nnoremap H <C-w>h
nnoremap J <C-w>j
nnoremap K <C-w>k
nnoremap L <C-w>l
" 快速保存
inoremap jk <esc>:w<cr>
nnoremap <esc> :w<cr>
inoremap <esc> <esc>:w<cr>
" 快速缩进
vnoremap < <gv
vnoremap > >gv
