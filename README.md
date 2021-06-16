# NCUI
基于Duilib+CEF++NodeJs的类似electron的桌面UI框架，适用于Windows XP 及以上系统，整体框架已完成，还有一些功能未实现，BUG未修改，C++用户已经可以修改使用，具有以下特性：

*   **单进程模式**： 可以选择程序以单进程还是多进程方式执行。
*   **离屏渲染**： 通过离屏渲染实现窗口透明。
*   **进程同步**： 可以在各进程间同步发送接收数据。
*   **请求拦截**： 拦截网络请求。
*   **C++扩展**： 只需包含头文件及可编写扩展，而且写法也很简单。
*   **差量更新**： 热更新。
*   **NODEJS**： 支持NodeJs控制程序。
*   **无版本限制**： 不限制CEF或Nodejs版本。

## 编译
* [下载CEF和NODE库](https://gitee.com/amoylel/NCUI/attach_files/download?i=95744&u=http%3A%2F%2Ffiles.git.oschina.net%2Fgroup1%2FM00%2F01%2FEC%2FPaAvDFm_w36ALMokBIafhng4_Zc6163.7z%3Ftoken%3D4839d493c3094bd59c257c16e29e6584%26ts%3D1505740719%26attname%3DNCUI-Library.7z) 解压到解决方案同级目录
* 运行config_debug.bat或config_release.bat初始化项目文件(需要python)
* 项目依赖boost，如果没有安装boost需要自行下载编译，编译命令见[boost编译说明.bat](https://gitee.com/amoylel/NCUI/blob/master/boost%20%E7%BC%96%E8%AF%91%E5%91%BD%E4%BB%A4.txt)
* 修改Microsoft.Cpp.Common.user.props设置boost目录
* 使用VS2015编译

## 下载
* [下载编译好的NCUI](https://gitee.com/amoylel/NCUI/attach_files/download?i=95746&u=http%3A%2F%2Ffiles.git.oschina.net%2Fgroup1%2FM00%2F01%2FEC%2FPaAvDFm_xy6AEkhlAnK3Bjkn9ns2266.7z%3Ftoken%3Dd1751bc694e355a51a2f139f858bfabb%26ts%3D1505740719%26attname%3DNCUI-0.0.0.1.7z)