# Clound_Programming
基于QT C++开发的支持云编译的代码编辑器，旨在利用云服务器，为代码编辑器提供环境一致、高效的、与平台无关的云编译功能

## 开发说明：  
* 客户端：
  * 开发环境：`Visual Stdio 2019 + Windows 10 + QT 5.11.1 + QScintilla 2.11.1`  
  * 开发语言：`C++`   
  * 配置文件：`文本文件`  
  
* 服务器：
  * 开发环境：`Pycharm + Ubuntu 18.04 + Python3.7`
  * 开发语言：`Python`
  
* 通信方式：`TCP`

* 开发团队：`余甜 何鹏举 赫靖涛 程恭正 (名字不分先后)`  

## 功能说明：
* 文件
  * 新建
  * 打开
  * 保存
  * 保存所有
  * 另存为
  * 打开命令行
  * 打开文件所在路径
  * 关闭文件
  * 结束程序

* 编辑
    * 撤销
    * 反撤销
    * 剪切
    * 复制
    * 粘贴
    * 全选
    * 大小写转化
    * 显示空格
    * 语法高亮
    * 自动补全
    
* 查看
    * 自动换行
    * 程序语言（支持中文、英文界面）

* 语言
    * Text
    * C
    * C++
    * Java
    * Python
    * Python3
    
* 工具
    * 网易词典快捷入口

* 运行
    * 云编译执行

* 帮助
    * 查看帮助
    * 关于我们
    
* 界面预留接口
    * 操作系统选择
    * 下载二进制
    
## 项目定位：
* 目前已经实现了在Windows上编写并执行Linux程序，但是由于客户端和服务器程序理论上都可以跨平台，所以未来应该可以支持主流平台随意搭配使用。
* 对于一个团队、群体而言，只需要在服务器上搭建环境即可，做到集中编译，共享环境
* 未来不仅仅做到执行，还可以支持调试功能

## 效果展示：
* 基本界面
![基本界面1](https://github.com/oneflyingfish/a_flying_fish/blob/master/Pictures/Clound_Programming/1.png)
![基本界面2](https://github.com/oneflyingfish/a_flying_fish/blob/master/Pictures/Clound_Programming/2.png)

* C 
![C](https://github.com/oneflyingfish/a_flying_fish/blob/master/Pictures/Clound_Programming/C.png) 

* C++ 
![C++](https://github.com/oneflyingfish/a_flying_fish/blob/master/Pictures/Clound_Programming/Cpp.png) 

* Java 
![Java](https://github.com/oneflyingfish/a_flying_fish/blob/master/Pictures/Clound_Programming/Java.png) 

* Python2 
![Python2](https://github.com/oneflyingfish/a_flying_fish/blob/master/Pictures/Clound_Programming/Python2.png) 

* Python3 
![Python3](https://github.com/oneflyingfish/a_flying_fish/blob/master/Pictures/Clound_Programming/Python3.png) 
