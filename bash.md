## Loose notes on bash & scripting

### TODO

1. Poznać dokładnie podstawową składnię - if, for, while, do
2. Jak działa read? Po co to?
3. Czemu czytanie arraya jest takie dziwne?
4. Przekazywanie argumentów do metody - jak "zbiję" w jeden string to działa inaczej niż jak przekazuję array (przykład javy czy bonfire np.). Dlaczego?
5. Zwracanie z funkcji za pomocą echo vs return
6. Jak działa pipe?
7. Jak działają i co oznaczają różne redirecty: <, < <(), <<<

**Next: [here](http://mywiki.wooledge.org/BashGuide/CommandsAndArguments) links starting from "Have a good look at ".** 

### Articles

1. [Understanding arguments, Word Splitting, Quoting, Escaping and Parameter Expansion](mywiki.wooledge.org/Arguments)
2. 

### The standard input is something totally different than command arguments

Based on [this SO answer](https://unix.stackexchange.com/a/108797).

These are two very different types of inputs:

* Standard input (stdin)
* Command line arguments

These are different, and are useful for different purposes.
Some commands can take input in both ways, but they typically use them differently.

Take for example the `wc` command:

* Passing input by stdin `ls | wc -l` will count the lines in the output of `ls` (if the number of lines is strange, check the notice below).
* Passing input by command line arguments `wc -l $(ls)`, this acts like `wc -l file_1.txt file_2.txt` etc. This will count lines in the list of files printed by ls

**Completely different things.**

* The `ls | wc -l` command can produce strange results, because `ls` returns all items in single line **when the terminal is the output**.
Otherwise, it will return results in separate lines, which is why `wc -l` returns number bigger than 1, even if pure `ls` prints everything in a single line when you issue it just like that.
Check [here](https://unix.stackexchange.com/questions/10421/output-from-ls-has-newlines-but-displays-on-a-single-line-why)) for details.

### Nice sed example

Based on [this SO answer](https://unix.stackexchange.com/a/108797).

```bash
rate=$(command1 | sed -ne 's/^rate..\([0-9]*\)%.*/\1/p')
command2 -t "rate was $rate"
```

Explanation of the sed:

1. The `s/pattern/replacement/` command is to replace some pattern.
2. The pattern means: the line must start with "rate" `^rate` followed by any two characters `..`, followed by 0 or more digits `[0-9]*`, followed by a `%`, followed by the rest of the text `.*`.
3. `\1` in the replacement means the content of the first expression captured within `\(...\)`, so in this case the digits before the `%` sign.
4. The `-n` flag of the sed command means to not print lines by default.
5. The `p` at the end of the `s///` command means to print the line if there was a replacement. In short, the command will print something only if there was a match.

### The glob *

### The [

`[` is a command and it expects the last argument to be `]`.

This is why, this one does not work:
```bash
$ [-f file]
# output: bash: [-f: command not found
```

however this one will work:
```bash
$ [ -f file ]
```

* Note - the `[ ]` command returns return codes `0` if true, `non-0` if false. To see the return code of the last issued command, use `echo $?`.

### Command arguments

1. Word splitting
2. Quoting, difference between a *syntactic* and *literal* whitespace.
3. Parameter expansion

***Quoting* and *escaping* are considered *before* parameter expansion happens, while *Word Splitting* is performed *after*.

### Quotes

[From here](http://mywiki.wooledge.org/Quotes)

#### 1. Single quotes: '...'

* Removes the special meaning of every character between the quotes.
* Everything inside single quotes becomes a literal string.
* The only character that you can't safely enclose in single quotes is a single quote.

#### 2. Double quotes: "..."

* Prevents some substitutions but allows others.
* Every substitution that begins with a dollar sign $ is performed, as is the legacy `...` (backtick) command substitution.
* Backslash escaping is also performed.
* **No word splitting or filename expansion is performed.**

#### 3. Backticks `...`

* Legacy command substitution syntax; deprecated in favor of $(...) but still permitted for historical reasons.

#### 4. Backslash

* Putting \ in front of a metacharacter removes its special meaning.
* This works inside double quotes, or in the absence of quotes. It does not work inside single quotes.

#### 5. Dollar and single quotes $'...'

* Contents are a single word with interpretation of backslash escape sequences such as \n for newline, \t for tab, and \xnn for bytes specified in hexadecimal. These may be used to specify a text representation of arbitrary data. No current implementation supports a context where these are not interpreted as NUL-terminated C strings.

#### 6. Dollar and double quotes $"..."

* This is a Bash extension. It is used for localization support. 