# VimForCpp
## 项目简介
本项目主要目标是帮助对vim配置方法不熟悉的新手封装的一键式vim环境安装包. 主要针对终端vim用户, 适合远程ssh连接Linux服务器进行开发的场景(例如使用阿里云服务器或者腾讯云服务器等). 

## 特点
>* 安装速度快(使用码云而不是github作为源). 网络畅通情况下, 几分钟内完成 vim 插件安装.
>* 无需编译直接使用 YouCompleteMe(直接下载预编译好的 ycm\_core.so). 
>* 一键式安装. 真正做到一键式安装. 不光能一键式安装 Vim 配置, 同时也会安装依赖的程序(包括 git, neovim, ctags等)

## 支持环境
目前只支持 Centos7 x86_64. 后面会考虑 Ubuntu 等发行版的支持.

## 安装方法

在 shell 中执行指令(想在哪个用户下让vim配置生效, 就在哪个用户下执行这个指令. 强烈 "不推荐" 直接在 root 下执行): 

  curl -sLf https://gitee.com/HGtz2222/VimForCpp/raw/master/install.sh -o ./install.sh && bash ./install.sh

需要按照提示输入 root 密码. 您的 root 密码不会被上传, 请放心输入.

## 卸载方法

在安装了 VimForCpp 的用户下执行:

  bash ~/.VimForCpp/uninstall.sh

## 功能演示
### 概览

![概览](https://gitee.com/HGtz2222/VimForCpp/raw/master/screenshot/%E6%A6%82%E8%A7%88.png)

### 自动补全(语义级别补全+模糊匹配)

![自动补全](https://gitee.com/HGtz2222/VimForCpp/raw/master/screenshot/%E8%87%AA%E5%8A%A8%E8%A1%A5%E5%85%A8.gif)

### 头文件补全

![头文件补全](https://gitee.com/HGtz2222/VimForCpp/raw/master/screenshot/%E5%A4%B4%E6%96%87%E4%BB%B6%E8%A1%A5%E5%85%A8.gif)

### 语法诊断

![语法诊断](https://gitee.com/HGtz2222/VimForCpp/raw/master/screenshot/%E8%AF%AD%E6%B3%95%E8%AF%8A%E6%96%AD.gif)

### 跳转到变量/函数定义, 跳转到头文件

![代码跳转](https://gitee.com/HGtz2222/VimForCpp/raw/master/screenshot/%E5%87%BD%E6%95%B0%E5%8F%98%E9%87%8F%E5%A4%B4%E6%96%87%E4%BB%B6%E8%B7%B3%E8%BD%AC.gif)

### 函数列表

![函数列表](https://gitee.com/HGtz2222/VimForCpp/raw/master/screenshot/%E5%87%BD%E6%95%B0%E5%88%97%E8%A1%A8.gif)

### 函数查找

![函数查找](https://gitee.com/HGtz2222/VimForCpp/raw/master/screenshot/%E5%BF%AB%E9%80%9F%E6%9F%A5%E6%89%BE%E5%87%BD%E6%95%B0.gif)

### 文件列表

![文件列表](https://gitee.com/HGtz2222/VimForCpp/raw/master/screenshot/%E6%96%87%E4%BB%B6%E5%88%97%E8%A1%A8.gif)

### 文件查找

![文件查找](https://gitee.com/HGtz2222/VimForCpp/raw/master/screenshot/%E5%BF%AB%E9%80%9F%E6%9F%A5%E6%89%BE%E6%96%87%E4%BB%B6.gif)

### 变量重命名
TODO

### 查找函数调用位置
TODO

### 快速查看函数声明
TODO

## 包含的插件列表
TODO

## 快速使用
TODO 需要重新整理

### 普通模式下快捷键

```
  <F5>        快速运行(仅限单个文件)
  <F6>        打开函数列表
  <F7>        打开文件管理器
  <F8>        文档注释
  <F11>       检查文件编译错误(仅限 c++)
  <ctrl+j>    尝试匹配代码片段
  <ctrl+k>    跳转到函数声明/定义
  <ctrl+l>    返回到之前的代码
  <;+m>       高亮/取消高亮光标下的文本
  <zz>        快速折叠/取消折叠代码
```

### 插入模式下快捷键

```
  jk          回到普通模式并保存
  H J K L     快速移动窗口
  <space>T    快速切换.c文件和.h文件
  <space>e    以标签页打开文件
```

### 可视模式下快捷键

```
  <           向左缩进
  >           向右缩进
  S+(         给选中文本外面加一层括号(带空格)
  S+)         给选中文本外面加一层括号(不带空格)
```

## 关于图标显示
基于 vim-devicons 展示图标. 
vim-devicons依赖 Nerd Font 

<a href="https://github.com/ryanoasis/nerd-fonts">nerd-fonts</a>

如果使用 xshell 登录 Linux, 需要在 Windows 上安装 nerd-fonts. 并且在 xshell 中设置字体为 nerd-fonts. 但是由于 xshell 只支持等宽字体, 因此 nerd-fonts 中大部分字体是不能被 xshell 识别的. 
此处我找到了几个可以使用的 nerd-fonts. 其他的没有进一步测试.

<a href="https://github.com/ryanoasis/nerd-fonts/blob/master/patched-fonts/DroidSansMono/complete/Droid%20Sans%20Mono%20Nerd%20Font%20Complete%20Mono%20Windows%20Compatible.otf">DroidSansMono</a>

其他字体可以参考文件  **xshell可用字体** 

注意: 为了避免字体兼容性的问题, 显示图标功能默认已经关闭. 如需打开, 修改 ~/.vimrc 中的

  
  " Plug 'ryanoasis/vim-devicons'

将行首的 " 去掉即可.
