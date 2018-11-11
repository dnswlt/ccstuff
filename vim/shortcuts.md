# Some useful vim shortcuts and commands

## Inserting and analysing characters

* `ga` ("Get ASCII") Display ASCII code and other info about character under the cursor
* `<C-v>u{1234}`  Insert character by hexadecumal (Unicode) code
* `<C-k>{char1}{char2}` Insert character as digraph. Examples: `>>` (for `&raquo;`), `12` (for `1/2`), `u"` for ü, `ss` for ß.

## Special modes

* `R` Replace mode (overwrite characters)

## Find and replace

* `/{pattern}` search for `pattern`
* `/\v{pattern}` "very magic" pattern syntax (every non-alpha char is special, close to Perl syntax)
* `/\c{pattern}` Case-insensitive search
* `n` find next occurrence of previous pattern
* `N` find previous occurrence of pattern
* `:%s/{pattern}/{repl}/{flags}` (`{flags}` are `g` global, `c` confirm, `n` count only)
* `:%s//{repl}/{flags}` like above, but use previously searched `{pattern}` (also from `/` find)

## Selecting text

* `gv` Re-select the most recent selection from visual mode

## Moving around

* `gg` go to first line buffer
* `G` go to last line in buffer
* `{`, `}` go to previous/next paragraph (separated by empty line)
* `(`, `)`, go to previous/next sentence (separated by punctuation mark)
* `f{letter}` go to next occurrence of `{letter}` on current line
* `;` repeat last `f{letter}` command

* `m{letter}` mark current cursor position
* `'{letter}` move to mark `{letter}` in current buffer


* `<C-^>` Goto alternate buffer (toggle between two buffers)
* `<C-o>` Goto previous jump location
* `<C-i>` Goto next jump location
* `:jumps` List jump locations

* `g;` Goto previous edit location in current buffer
* `g,` Goto next edit location (inverse of `g;`)
* `gi` Switch to insert mode at last insert location in current buffer

Code motion

* `%` go to matching parenthesis/bracket
* `[{brk}` goto outer left bracket, where `{brk}` can be `{` or `(`
* `]{brk}` goto outer right bracket, where `{brk}` can be `}` or `)`

## Copy and paste

Normal mode

* `"{reg}p` put (paste) content of register `{reg}`
* `"{reg}y{motion}` yank (copy) `{motion}` characters into register `{reg}` (use `*` for system clipboard)`

Visual mode

* `<C-r>+` insert system clipboard contents (also in insert mode)
* `"+y` yank selected text to system clipboard
* `:reg` list register contents

# gVim

Start gVim with a fixed window size and position:

* Run `set sessionoptions+=resize,winpos` to include the relevant info in a vim session file
* Run `:mksession` to create a `Session.vim` file
* Copy the `lines`, `columns` and `winpos` settings into your `$MYGVIMRC` file

```vim
set lines=56 columns=145
winpos 602 0
```

