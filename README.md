# Boggle Game - 命令行交互式棋盘游戏

## 简介
实现⼀个通过命令⾏交互的 Boggle 游戏。Boggle 是⼀个棋盘游戏。在 N×N 的棋盘上排列了 N×N 个英⽂⼤写字⺟。玩家通过连线的⽅式，将相邻的字⺟组成英⽂单词，获得分数。每个字⺟与其周围的八个字⺟都相邻。在连线过程中，棋盘上的每个格⼦只能经过一次。该游戏中有两名玩家，分别为 Player 1 和 Player 2，两名玩家分别输⼊⾃⼰找到的单词。当游戏结束后，由电脑计算出两名玩家的总分，并且给出棋盘上所有可能的单词。

## 游戏流程

### 1. 棋盘输入
棋盘上的字⺟排列由标准输入给出。  
在标准输入的第一行，为一个数字 **N**，此后的 **N** 行，每行为一个长度为 **N**，且只包含大写英文字母的字符串。  
棋盘字母排列读入完毕后，游戏自动开始，你的程序应进入玩家输入环节。

### 2. 玩家输入
游戏按玩家轮流输入的方式进行。对于每个玩家而言，程序应首先展示当前玩家的得分（如 `Player 1 Score: 0`），然后等待当前玩家输入。  
玩家可多次输入，每次可输入两种内容之一：
- **输入 `???`**：表示结束当前玩家的输入，程序应当切换到下一个玩家。如果已经是最后一位玩家（即 Player 2），则进入游戏总结环节。
- **其他字符串**：视为玩家尝试的单词，程序会检查其有效性并反馈结果，然后展示当前玩家得分。  
  一个有效的单词应满足以下条件（请按照此顺序进行检查）：
  - **长度 ≥ 4**：短于 4 个字母的单词无效（输出 `[单词] is too short.`）。
  - **词典中存在**：需是 `EnglishWords.txt` 中的合法英文单词（输出 `[单词] is not a word.`）。
  - **棋盘路径有效**：可通过相邻格子（8 方向）连接，且每个格子最多使用一次（输出 `[单词] is not on board.`）。
  - **未被当前玩家找到过**：同一玩家不能重复提交同一单词（输出 `[单词] is already found.`）。

### 3. 计分规则
- **单词得分** = 单词长度 - 3（例如：4 个字母的单词得 1 分，5 个字母得 2 分，以此类推）。
- 玩家总分累加有效单词得分，回合结束后显示最终排名。

### 4. 游戏总结
在玩家输入结束后，进入游戏总结环节：
- **输出两名玩家的得分**，并且给出游戏结果：
  - `Player 1 wins!`
  - `Player 2 wins!`
  - `It's a tie!`
- **输出棋盘上所有可能的有效单词**（全大写、字典序排列、一行显示）。

---

## 词典信息
在 Boggle 游戏中，共有 12 万多个单词被认为是合法的单词，包含在一个名为 **EnglishWords.txt** 的文件中。  
我们提供了一个辅助类 **Lexicon**，可以用于读取该文件，并提供了 **contains** 和 **containsPrefix** 两个函数帮助你在词典中进行单词查找。

---

## 游戏规则总结
1. **棋盘输入：**
   - 输入 N 和 N×N 的字母棋盘。
2. **玩家输入：**
   - 每个玩家交替输入，直到输入 `???` 表示结束当前回合。
   - 每个单词输入都要进行有效性校验（长度、词典、棋盘路径、去重）。
3. **计分：**
   - 4 个字母得 1 分，5 个字母得 2 分，以此类推。
4. **游戏总结：**
   - 输出玩家得分和胜负结果。
   - 输出所有可能的有效单词。

---

## 示例
```
> ./boggle
5
EEIRD
AGMRS
CIILN
DLOTE
FRWOT
Player 1 Score: 0
guess
guess is not on board.
Player 1 Score: 0
word
Correct.
Player 1 Score: 1
acid
Correct.
Player 1 Score: 2
woolens
Correct.
Player 1 Score: 6
lote
lote is not a word.
Player 1 Score: 6
woolens
woolens is already found.
Player 1 Score: 6
toE
toE is too short.
Player 1 Score: 6
???
Player 2 Score: 0
totel
totel is not a word.
Player 2 Score: 0
Woolen
Correct.
Player 2 Score: 3
???
Player 1 Score: 6
Player 2 Score: 3
Player 1 wins!
All possible words: ACID AGEE AGILE AGIO AIOLI CAGE CAID CLIME CLOOT CLOT DIGIT DIME DIOL
DIOLS DROIT EMIC EMIR EMIRS EMIT ENTOIL ENTOILS FLIC FLIT FLITE FLOW FROLIC FROW GILD GILT
GIMLET GIRD GIRDS GIRL GIRLS GIRN GIRNS ILIA ILIAC IMID IOLITE LENS LENT LENTIL LENTO LENTOID
LILT LIME LIMIT LITTEN LOOT LORD LOTI LOTTO MICA MILD MILE MILIA MILO MILORD MILS MILT MIRI
MIRS MITE MITT MITTEN MITTENS NETT OILS OLEO OOLITE OTTO RIGID RILE RIME RIOT RITE ROIL ROILS
ROLE ROOT ROOTLET ROTE ROTL ROTLS ROTO ROTTE ROTTEN SLIM SLIME SLIT SLOID SLOT SLOW TELOI
TELS TENS TENT TILE TILS TIME TIMID TIRL TIRLS TOIL TOILE TOILET TOILS TOLD TOLE TOOL TOOLS
TOOT TOOTLE TOTE WOLD WOLF WOOL WOOLEN WOOLENS WOOLS WORD WORLD WROTE
```
