# 高级用法

  NCUI进阶教程.
  
## 使用Node.js &nbsp;
  NCUI支持使用Node.js控制程序，但目前只针对4.7.3进行过开发，更高或更低的版本可能并不支持.你可以在Node.js中使用文档api部分所提供的绝大部分接口，其他类型的接口不被支持.<br>你可以编辑manifest.json文件(useNode=true)来获取Node.js支持.默认情况下Node.js会注入到NCUI中，并在单独的线程中运行.<br>你可以编辑manifest.json文件(useNodeProcess=true)使Node.js在单独的进程中执行,该模式下Node.js会以调试模式启动，你可以使用node-inspector或其他调试工作调试Node.js代码.
  
* **示例**

```html
// 直接在NCUI中使用Node.js
{
    "appSettings":{
        useNode: true,
        useNodeProcess: false
    }
}

// 在单独的进程中使用Node.js
{
    "appSettings":{
        useNode: true,
        useNodeProcess: true
    }
}

```


<div class="adoc" id="div_使用Node.js"></div>


## 生成应用 &nbsp;
  可以使用<a href="#extend/extendrcedit">资源编辑模块</a>生成自己的应用.
  


<div class="adoc" id="div_生成应用"></div>


## local协议 &nbsp;
  NCUI注册了自定义协议local://file来支持本地文件的访问.具体为"local://file/文件路径",文件路径如果为相对路径的话，将以%webDir%所在目录进行查找.
  
* **示例**

```html
includes('BrowserWindow', 'app');

var win = new BrowserWindow({
    titleBar: true,
    url: 'local://file/example/localfile.html'
})

var url = app.toAbsolutePath("%webDir%example/FramelessWindow.html");
console.log(url);

new BrowserWindow({
    titleBar: false,
    url: url
})

```


<div class="adoc" id="div_local协议"></div>


## @file协议 &nbsp;
  NCUI支持自定义协议@file:///来支持本地文件的访问.具体为"@file:///文件路径",文件路径如果为相对路径的话，将以%webDir%所在目录进行查找.<br>@file协议更加强大,你可以在任意url中注入@file协议将url指向本地文件，且不存在跨域等问题.
  
* **示例**

```html
includes('BrowserWindow', 'app');

var win = new BrowserWindow({
    titleBar: true,
    url: 'localhost/@file:///example/localfile.html'
})

var url = app.toAbsolutePath("%webDir%example/FramelessWindow.html");
console.log(url);

new BrowserWindow({
    titleBar: false,
    url: 'http://www.baidu.com/ananana/@file:///'+url
})

```


<div class="adoc" id="div_@file协议"></div>


## 地址映射 &nbsp;
  该功能可以将一个URL映射到本地文件.目前支持的映射方式有文件、目录、ZIP格式压缩文件、DLL动态库、SQLITE数据库文件、RES资源文件<br>可以编辑manifest.json指定映射路径，也可以在程序运行后<a href="#api/apiapp/5">手动指定</a>映射路径.<br>当前程序就是采用URL到文件夹的方式访问页面的.
  
* **参考** 
<a href="#api/apiapp/5">app.addUrlMapping</a>



<div class="adoc" id="div_地址映射"></div>


## 源代码管理 &nbsp;
  NCUI支持读取本地文件、ZIP格式压缩文件、DLL动态库中的HTML源代码，你可以通过这些方式为NCUI提供源代码.<br>1. **从本地目录中读取HTML:**<br>2. **从ZIP文件中读取HTML:**<br>3. **从DLL中读取HTML:**<br>4. **从SQLITE数据库中读取HTML:**<br>5. **从程序的资源文件中读取HTML:**<br>NCUI不直接提供源代码加密功能，但支持读取加密的ZIP文件、加载的SQLITE数据库，你可以通过修改源代码的方式提供对应的加密文件密码供程序使用.
  


<div class="adoc" id="div_源代码管理"></div>


## C++扩展 &nbsp;
  NCUI提供更加简单的扩展编写方式，只需要将扩展项目生成的动态库文件放到renderer_modules或者browser_modules目录即可在页面中调用.<br>如果你是C++程序员，请参考libDemo项目的源代码.
  


<div class="adoc" id="div_C++扩展"></div>


## 外部渲染层 &nbsp;
  仅离屏模式下支持使用外部数据渲染界面.
  
* **参考** 
<a href="#api/apiBrowserWindow/63">BrowserWindow.addOverlap</a>



<div class="adoc" id="div_外部渲染层"></div>


## DLL调用 &nbsp;
  NCUI直接调用C导出的DLL接口,但限制比较多，还不如直接写C++扩展快，暂未开放.
  
