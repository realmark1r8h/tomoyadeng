# 快速开始

  开始使用NCUI.
  
## 配置文件 &nbsp;
  编辑程序所在目录下的manifest.json文件可以自定义设置程序的启动方式。<br>完整的manifest包含三个段，分别为 appSettings， browserWindowSettings， splashWindowSettings;<br>对应可以设置<a href="#settings/settingsAppSettings">启动参数</a>，<a href="#settings/settingsBrowserWindowSettings">启动浏览器窗口参数</a>，<a href="#settings/settingsSplashWindowSettings">程序启动画面</a><br>manifest不是必须的，如果不存在，那么程序将使用默认配置.
  
* **示例**

```html
// 一个简单的配置文件,只包含启动窗口的参数配置段， 设置程序启时要打开的URL
{
    "browserWindowSettings":{
    "titleBar": true,
    "url": "http://www.oschina.net"
    }
}

```
* **示例**

```html
// 一个包含所有段的的配置文件
{
   "appSettings":{
       "single_process": true
   },
   "browserWindowSettings":{
        "titleBar": true,
        "url": "http://www.oschina.net"
    },
    "splashWindowSettings":{
       "images":"%webDir%images/splash.png"
    },
}

```


<div class="adoc" id="div_配置文件"></div>


## 创建浏览器窗口 &nbsp;
  程序启动时会创建一个默认的浏览器窗口，该窗口的参数可以通过编辑manifest.json文件进行配置.<br>如果需要在页面上创建窗口，可以通过<a href="#api/apiBrowserWindow">BrowserWindow</a>提供的接口创建一个新的浏览器窗口。<br>除此之外，浏览器默认的窗口创建动作（如：**a标签**、**window.open**等）出来的窗口将使用默认的{@ling 浏览器窗口参数},这可能会影响你的正常使用（比如没有标题栏，不能拖动窗口），可以<a href="#api/apiBrowserWindow/65">预设置浏览器窗口参数</a>来避免该问题
  
* **参考** 
<a href="#api/apiBrowserWindow/65">BrowserWindow.addBrowserWindowSettings</a>



<div class="adoc" id="div_创建浏览器窗口"></div>


## 导入模块 &nbsp;
  如果要使用NCUI提供的模块，那么必须在使用之间前将需要的模块导入到页面中，你可以通过以下两个接口导入需要的模块。<br>使用**include**导入单个模块，模块会被注入到页面的全局变量中.<br>使用**includes**导入多个模块，所有模块都会被注入到页面的全局变量中.<br>如果内置模块不存在，将会导入renderer_modules文件夹下模块，如果还是不存在会导入browser_modules文件夹下模块.renderer_modules文件夹下的扩展在Renderer线程上运行，browser_modules文件夹下的扩展在UI线程上运行.
  
* **示例**

```html
// 导入单个模块
include('BrowserWindow');
BrowserWindow.current.maximize();

```
* **示例**

```html
// 导入多个个模块
include('BrowserWindow', 'app');
BrowserWindow.current.maximize();
BrowserWindow.current.restore();
// 尝试退出程序
app.quit();

```
