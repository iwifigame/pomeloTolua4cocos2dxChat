coco_pomelo_base
================

provides some API binded to lua using libpomelo and cocos2dx-3.0 beta

1.cocos2dx3.0 beta创建新项目 coco_pomelo_base
2.用本项目替换相应文件（夹）
3.把（包含vs解决方案的）libpomelo放到cocos2d\external
编译，运行

只用lua实现了一点和chatofpomelo-websocket交互的功能，有人进入聊天室、离开、发言会在控制台打印，点button会发送一条消息
pomelo的api在lua里比较全了，具体用法参考lua代码
没仔细检查cpp中各接口，如发现bug如jansson用法不当导致内存泄露之类的，请小伙伴们修改提交或通知俺，3ks~
