采用了多文件编程，Room为对房间的定义，geneRoom为生成地图的部分，myAdeventure为游戏主体部分。

运行方法：
在命令行中使用
g++ -o adventure myAdventure.cpp geneRoom.cpp Room.cpp
然后运行 adventure.exe文件

开始会让你输入需要生成的房间数量，生成完成后会输出地图详情。
当出现"Game Start"的字样时，代表游戏开始，可以正常开始游戏。