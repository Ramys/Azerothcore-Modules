# mod-LuaEngine
[english](README.md) | 中文

一个用于AzerothCore的ELUNA模块.

如何安装:

1. 下载或者克隆这个模块:  
>   [下载zip压缩包](https://github.com/azerothcore/mod-eluna-lua-engine/archive/master.zip)  
>   或者克隆 `git clone https://github.com/azerothcore/mod-eluna-lua-engine.git`  
2. 解压并放到Azerothcore源码的modules文件夹中.  
3. 下载或者克隆ELUNA的核心文件:  
>   [download zip file.](https://github.com/ElunaLuaEngine/Eluna/archive/master.zip)  
>   clone `git clone https://github.com/ElunaLuaEngine/Eluna.git`  
4. 解压并放置到模块的LuaEngine文件夹中:mod-LuaEngine/LuaEngine(如果下载了zip文件，你需要将`Eluna-master`文件夹中的所有文件移动到`mod-eluna-lua-engine/LuaEngine`文件夹中。`LuaEngine.h`需要直接位于目录:`mod-eluna-lua-engine/LuaEngine`之下，不要有任何的子文件夹。)
5. 重新cmake.  
6. 重新生成. 

Eluna API : [http://www.elunaengine.com/](http://www.elunaengine.com/)