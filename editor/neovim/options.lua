local opt = vim.opt

-- 基础美化
opt.relativenumber = true -- 相对行号
opt.number = true         -- 显示当前行号
opt.termguicolors = true  -- 开启真彩色支持
opt.cursorline = true     -- 高亮当前行
opt.signcolumn = "yes"    -- 始终显示左侧边栏（防止闪烁）

-- 缩进设置
opt.tabstop = 4
opt.shiftwidth = 4
opt.expandtab = true
opt.autoindent = true

-- 搜索
opt.ignorecase = true
opt.smartcase = true

-- 编码
vim.scriptencoding = 'utf-8'
opt.encoding = 'utf-8'
opt.fileencoding = 'utf-8'

-- shell
vim.opt.shell = 'pwsh'
vim.opt.shellcmdflag = '-NoLogo -NoProfile -ExecutionPolicy RemoteSigned -Command'
vim.opt.shellquote = '"'
vim.opt.shellxquote = ''
