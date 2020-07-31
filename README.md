# woh

war of hearts! let's battle! （｀へ ´）

# build

## linux

```shell
mkdir build
cd build
cmake ..
make
```

## win(vs)

创建文件夹 `build` , 在其中运行 `cmake ..`.
然后打开生成的 vs 工程.

# player interface

## term

- 局(game)
  一局游戏，是指从 0 开始，不断进行游戏，直到有玩家达到 100 分而分出胜负.
- 回合(round)
  一个回合，指从发牌开始，到所有玩家出完手牌
- 圈(circle)
  指玩家按照顺时针顺序各出一张牌

## interface

> see [player.h](woh/player.h) and [minmon.cpp](ai/minmon.cpp)

```c++
// 一局游戏开始，为玩家分配座位
virtual void sit(int s) = 0;
// 一回合开始时，发给玩家手牌
virtual void set_cards(vector<Card> cards) = 0;
// 玩家提供num张牌用于交换
virtual vector<Card> swap(int num) = 0;
// 玩家收到来自其他玩家交换的牌
virtual void rcv_swap(const vector<Card>& cards) = 0;
// 玩家打出一张牌，参数deck为其他玩家已经打出的牌
virtual Card play_card(const vector<Card>& deck) = 0;
// 一圈结束后，sit座位玩家拿到cards，cards为此圈中打出的所有牌
virtual void circle_end(int sit, const vector<Card>& cards) = 0;

// 实现以提供玩家名字
virtual string name() const = 0;
```

# notice

代码最好提交到`ai/{yourname}`下,并且用自己的命名空间以避免冲突.
