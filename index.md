# Welcome to OI-Beats

Build by NtscYrx(Github).

[Visit OI-Beats / 访问网站](https://ntsc-yrx.github.io/oi-beats/site/)


## Powered by MkDocs

For full documentation visit [mkdocs.org](https://www.mkdocs.org).

## Commands

* `mkdocs new [dir-name]` - Create a new project.
* `mkdocs serve` - Start the live-reloading docs server.
* `mkdocs build` - Build the documentation site.
* `mkdocs -h` - Print help message and exit.

## Project layout

    mkdocs.yml    # The configuration file.
    docs/
        index.md  # The documentation homepage.
        ...       # Other markdown pages, images and other files.

## 正则表达式

如果你想要匹配字符串中加号 “+” 后面的所有内容，可以使用以下正则表达式：

```
\+(.*)
\+[0-9a-z](.*)
```

## 重命名原则：

- 文件名末尾不能出现空格
- 主文件夹需要clear，子文件夹不得修改名称

## 更新原则

在更新时，先将原docs文件夹重命名为docsOld，然后复制入新版本docs

## 自定义 Theme

http://mkdoc-material.llango.com/customization/#_3