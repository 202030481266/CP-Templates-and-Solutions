## 1. VS Code (VSCode Neovim 插件)

VSCode Neovim 的最大优势是它运行着一个真实的 Neovim 实例。

### 基础映射

你可以直接在 VS Code 设置中指定使用你现有的 `init.lua`。但由于 VS Code 的分屏逻辑与原生 Vim 不同，建议在你的 `keymaps.lua` 中加入条件判断，或在 `settings.json` 中配置：

**在 `settings.json` 中添加：**

```json
{
    "vscode-neovim.neovimInitPath": "C:/Users/你的用户名/AppData/Local/nvim/init.lua", // 指向你的配置
    "extensions.experimental.affance": true,
    
    // 针对 VS Code 分屏跳转的优化（写在 settings.json 而非 lua）
    "vim.handleKeys": {
        "<C-h>": false,
        "<C-j>": false,
        "<C-k>": false,
        "<C-l>": false
    }
}

```

**针对分屏跳转（在 VS Code 的 `keybindings.json` 中）：**

```json
[
    { "command": "workbench.action.focusLeftGroup", "key": "ctrl+h", "when": "editorTextFocus && vim.active" },
    { "command": "workbench.action.focusRightGroup", "key": "ctrl+l", "when": "editorTextFocus && vim.active" },
    { "command": "workbench.action.focusAboveGroup", "key": "ctrl+k", "when": "editorTextFocus && vim.active" },
    { "command": "workbench.action.focusBelowGroup", "key": "ctrl+j", "when": "editorTextFocus && vim.active" }
]

```

---

## 2. JetBrains IDEs (IdeaVim 插件)

IdeaVim 使用 `~/.ideavimrc` 文件（Windows 下通常在 `C:\Users\用户名\.ideavimrc`）。它不支持 Lua，需要转译为 Vimscript。

**配置内容 (`.ideavimrc`):**

```vim
" 设置 Leader 键
let mapleader = " "

" 1. 映射 jj 为 Esc
inoremap jj <Esc>

" 2. 映射 jk 为 保存并返回 (IdeaVim 中 :w 对应 IDE 的 Save All)
inoremap jk <Esc>:w<CR>

" 3. 可视模式缩进保持选中
vnoremap < <gv
vnoremap > >gv

" 常用分屏跳转 (调用 IDE 原生 Action 体验更佳)
nnoremap <C-h> <Action>(EditorLeft)
nnoremap <C-j> <Action>(EditorDown)
nnoremap <C-k> <Action>(EditorUp)
nnoremap <C-l> <Action>(EditorRight)

" 基础设置
set relativenumber
set number
set cursorline
set ignorecase
set smartcase
set ideajoin " 增强型行合并

" 缩进设置 (通常 IDE 会覆盖这些，但写上以防万一)
set tabstop=4
set shiftwidth=4
set expandtab

```

---

## 3. Visual Studio (VsVim 插件)

VsVim 同样使用 Vimscript 风格，读取 `_vsvimrc` 文件。

**配置内容 (`_vsvimrc`):**

```vim
let mapleader = " "

" 插入模式映射
inoremap jj <Esc>
inoremap jk <Esc>:w<CR>

" 缩进保持
vnoremap < <gv
vnoremap > >gv

" 分屏跳转 (VS 默认使用 Ctrl+Tab 或特定的窗口快捷键)
" 下面映射尝试模拟原生 Vim 行为
nnoremap <C-h> <C-w>h
nnoremap <C-j> <C-w>j
nnoremap <C-k> <C-w>k
nnoremap <C-l> <C-w>l

" 基础设置
set relativenumber
set number
set ignorecase
set smartcase
" 注意：VS 的 UI 设置（如 Tab 大小、颜色）通常由 VS 菜单中的 '选项' 决定，vsvimrc 的优先级较低

```

---

## 总结与建议

| 功能 | 建议实现方式 |
| --- | --- |
| **`jj` / `jk**` | 在所有环境中效果一致，直接映射。 |
| **分屏跳转** | **VSCode/IntelliJ** 建议调用 IDE 的 `Action`（如上文代码），因为 IDE 的分屏不完全等同于 Vim 的 Buffer 窗口。 |
| **UI 设置** | `relativenumber` 和 `cursorline` 在 IDE 中建议通过 IDE 自带的设置界面开启，这样更稳定。 |
| **Shell (pwsh)** | 仅在 VS Code 的 `settings.json` 中配置 `terminal.integrated.defaultProfile.windows` 为 `PowerShell` 即可。 |
