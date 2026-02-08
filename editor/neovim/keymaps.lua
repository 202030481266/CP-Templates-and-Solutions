local keymap = vim.keymap

-- 设置 leader 键为空格
vim.g.mapleader = " "

-- 1. jj 映射为 Esc
keymap.set("i", "jj", "<Esc>", { desc = "退出插入模式" })

-- 2. jk 映射为 保存并返回命令模式
-- 这里使用 :w 保存，然后 <Esc>
keymap.set("i", "jk", "<Esc>:w<CR>", { desc = "保存并退出插入模式" })

-- 3. 可视模式下缩进保持选中状态
-- 默认 > 会取消选中，gv 会重新选中上次区域
keymap.set("v", "<", "<gv", { desc = "减少缩进并保持选中" })
keymap.set("v", ">", ">gv", { desc = "增加缩进并保持选中" })

-- 常用分屏跳转
keymap.set("n", "<C-h>", "<C-w>h")
keymap.set("n", "<C-j>", "<C-w>j")
keymap.set("n", "<C-k>", "<C-w>k")
keymap.set("n", "<C-l>", "<C-w>l")


-- 终端模式下用 Esc 退出到普通模式
vim.keymap.set('t', '<Esc>', '<C-\\><C-n>')
