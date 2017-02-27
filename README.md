# 贪吃蛇游戏（SDL2 + C++开发）

---

## 开发环境与依赖

 - IDE: Virtual Studio 2012
 - 依赖库: SDL2（下载地址: https://www.libsdl.org/download-2.0.php）
 - 开发语言: C++

## 实现效果图
![俄罗斯方块游戏实现效果图](https://github.com/SmallHedgehog/Games-Snake/blob/master/res/4.png)

## 公共引用文件描述
- res/目录下是程序中使用的资源文件，比如背景图片等；
- Defines.h文件中定义的是const values，比如游戏区域的位置等信息；
- Enums.h文件中定义的是enum const values，比如定义方向等；

## 类文件描述

**Square类**

Square类的对象表示蛇每次吃到食物会增加的部分，此外Square类的对象也可以表示游戏中的食物。

**Snake类**

Snake类表示游戏中的蛇，它包含了vector<Square*>的集合。

**Game类**

Game类管理着我们的游戏对象，并且做碰撞检测等。

**Window类**

Window主要负责我们窗口的绘制、资源文件的加载、初始化我们的游戏对象以及进入消息循环等。
