# yiming2022

# 安装EUPSystemTool
1、下载压缩包EUPSystemTool.tar.gz并解压

2、解压得到EUPSystemTool文件夹，该目录下有：
-        OSAppScript——脚本目录,该目录下是EUPSystemTool工具使用的所有脚本
-        startEUPSystemTool.sh——使用polikit提权启动EUPSystemTool工具的脚本
-        installEUPSystemTool.sh——安装EUPSystemTool的脚本，使用者只需要sudo ./installEUPSystemTool.sh即可
         安装EUPSystemTool
-        shortcut.sh和shortcut_old.sh——设置EUPSystemTool快捷方式的脚本，该脚本集成在installEUPSystemTool.sh
         脚本里（目前有些问题，sudo -u devel -i 有问题，还未解决）
-        EUPSystemTool.policy——polikit提权的策略文件
-        Library.txt——动态库基础知识，在CheckLibModule中的README按钮使用
-        EUPSystemTool——二进制可执行文件


# 开发版本迭代
## v0.1增加内容
errnomodule：显示errno，shell命令执行后输出的shell code，Linux的signal


## v0.2增加内容
2022-6-27至2022-6-30
checklib：检查动态库功能，目前实现检查缺少依赖的动态库、检查重复和存在多版本的动态库
存在问题：
-         1、对于堆区内存释放的问题，不太了解释放的时机（已修改为栈的成员变量,或者堆变量挂到对象树上）
-         2、对于QProcess中execute函数，会报错QIODevice::read (QProcess): device not open，
          并且readALL返回空串（使用QProcess中的start函数）
-         3、对于多版本动态库的脚本还存在一些问题（已完成）
-         4、还未实现保存QTreeView中的文本信息到文件（已完成）

        

## v0.3增加内容
CPUModule:CPU的基本信息

GPUModule：GPU的基本信息

MemoryModule：Memory的基本信息

DiskModule：Disk的基本信息

OsInfoModule：OS的基本信息

DeviceModule:外设的信息

存在问题：
-         1、对MVC模式不太熟悉，熟悉MVC模式，现先使用较为简单的QTreeWidget显示数据，后续考虑使用QTreeView
          配合MVC模式，model和view分离。
-         2、刚开始代码重复量大，几乎每个模块都会使用QProcess去执行脚本，抽象成一个单例模式的类，该类
          有公有函数execShell(QString cmd),用于执行shell命令或脚本文件。
-         3、有些旧脚本与i7-12th的CPU不兼容

        
## v0.4增加内容
CPUModule:CPU的动态调节的信息，调节Governor、频率上下限的水位差（待优化，目前实现的不是水位差）、是否启用睿频和超线程

GPUModule：调节GPU的Power Limit功能

DeviceModule：设置鼠标位置

CheckLibModule：优化脚本、增加解析完成的弹窗、增加查看Readme.md功能

存在问题：
-         1、cpu Module中调节频率的命令cpupower接收的参数为x.xG，后面的单位默认是Hz（已解决）
-         2、修复动态库检查中检验系统是否存在该动态库的脚本（原脚本未用locate命令检查，已解决）
-         3、QSlider的刻度与样式表冲突，有样式表刻度显示不出来，需重写QSlider的paintEvent（目前用QLabel显示最大最小值）
-         4、checklibModule中的检查动态库功能非常耗时，经排查发现是脚本问题（初步构思的解决措施：由于该任务的数据是互不相关的，可并行执行，脚本收集该目录的所有动态库，然后分割成多份，用QThread创建线程绑定CPU并行完成）
-         5、cpuModule中设置水位差功能，当min大于max或max小于min时弹出QMessage，多次点击划槽会出现死循环即划块会回退，然后又触发QMessage，又回退又触发。（待解决）

## v1.0增加内容
AppModule:完成App线程绑定CPU、调节进程优先级等功能

CheckLib：增加白名单功能，在whiteList.conf上添加某一动态库的绝对路径，在检查的时候会过滤掉

App：编写shell脚本，完成对EUPSystemTool程序的安装

存在问题：
-         1、在进程绑定CPU上，可以选择多个CPU，采用CheckBox，用循环建立cores数量个的CheckBox，如何返回选中的CheckBox（已完成，使用sender）。     



# Qt
