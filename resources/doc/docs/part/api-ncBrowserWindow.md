# BrowserWindow

BrowserWindow为全局对象，页面通过include('BrowserWindow')加载使用;  Node自己包含


  <link rel="stylesheet" type="text/css" href="docs/css/common.css" />
  <script src="docs/js/string.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/template.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/BrowserWindow.js" type="text/javascript" charset="utf-8"></script>
  
## 接口说明
<ul><li class="param">函数接口:</li></ul>

<table id="method" class="table" >
     
</table>
 
<ul><li class="param">new BorwserWindow(options) BrowserWindowSettings 参数说明:</li></ul>

<table id="settings" class="table">
</table>

<ul><li class="param">事件说明:</li></ul>

<table id="event" class="table" >
     
</table>  

## 创建浏览器窗口


```html
//创建普通窗口
var normalWindow = new BrowserWindow({ 
    roundcorner: 3,
    name: 'www.baidu.com', 
    title:'百度一下，你就知道'
    titleBar: true,
    width: 960,
    height: 650,
    minWidth: 471,
    minHeight: 520,
    url: "http://www.baidu.com/more"
});

// 创建离屏窗口
var offscreenWindow = new BrowserWindow({ 
    roundcorner: 3,
    name: 'www.baidu.com', 
    title:'百度一下，你就知道'
    titleBar: true,
    width: 960,
    height: 650,
    minWidth: 471,
    minHeight: 520,
    url: "http://www.baidu.com/more",
    offscreen: true,
    transparent: false
});

// 创建透明窗口
var transparentWindow = new BrowserWindow({ 
    roundcorner: 3,
    name: 'www.baidu.com', 
    title:'百度一下，你就知道'
    titleBar: true,
    width: 960,
    height: 650,
    minWidth: 471,
    minHeight: 520,
    url: "https://www.baidu.com/more",
    offscreen: true,
    transparent: true
});
 
```
<div class="row">
    <div class="col-xs-3">
         <button class ="btn btn-outline-primary btn-block" id="normalWindow">普通窗口</button>
    </div>
     <div class="col-xs-3">
         <button class ="btn btn-outline-primary btn-block" id="offscreenWindow">离屏窗口</button>
    </div>
     <div class="col-xs-3">
         <button class ="btn btn-outline-primary btn-block" id="transparentWindow">透明窗口</button>
    </div>
</div>

## 无边框窗口

无边框窗口没有标题栏，无法通过标题栏移动窗口，可以给html元素添加class="drag"给窗口增加移动功能

```html

<!--设置鼠标在当前div上时可以拖动窗口-->
<div class="drag"> 
    <!--设置按钮不能被拖动-->
    <button class="no-drag"></button>
</div>

// 创建一个无边框窗口
var framelessWindow = new BrowserWindow({
    titleBar: false,
    url: 'http://127.0.0.1:8020/amoylel/doc/example/FramelessWindow.html'
});
```

<div class="row">
    <div class="col-xs-3">
         <button class ="btn btn-outline-primary btn-block" id="framelessWindow">无边框窗口</button>
    </div>
</div>

## 窗口默认参数
  
```html
 
// 添加窗口默认参数
BrowserWindow.addBrowserWindowSettings('http://www.oschina.net', {
    titleBar: true,
    alwaysOnTop: true,
    
}); 
// 移除窗口默认参数
BrowserWindow.removeBrowserWindowSettings('http://www.oschina.net');
```

<div class="row">
    <div class="col-xs-3">
         <button class ="btn btn-outline-primary btn-block" id="addBrowserWindowSettings">添加默认参数</button>
    </div>
     <div class="col-xs-3">
         <button class ="btn btn-outline-primary btn-block" id="removeBrowserWindowSettings">移除默认参数</button>
    </div>
    <div class="col-xs-3">
         <a class ="btn btn-outline-primary btn-block" href="http://www.oschina.net" target="blank">查看效果</a>
    </div>
</div>


## 调试工具

可以手动打开调试工具，当浏览器窗口关闭时，调试窗口会自动关闭

```html
// 打开当前页面的调试工具
win.showDevTools();
// 关闭调试
win.closeDevTools();
```

<div class="row">
    <div class="col-xs-3">
         <button class ="btn btn-outline-primary btn-block" id="showDevTools">打开调试</button>
    </div>
     <div class="col-xs-3">
         <button class ="btn btn-outline-primary btn-block" id="closeDevTools">关闭调试</button>
    </div>
</div>

## 事件监听
  
```html
include('app');
// 设置一项
app.setConfig({skin:'%appDir%res'}); 

// 同时设置多项
app.setConfig({
    skin:'%appDir%res',
    web:'%appDir%webDir'
}); 
```

<div id="text" class="example code" contenteditable="true">
  <h3 id="output">移动鼠标到托盘上试试</h3>
</div>

## 窗口函数
 
  
```html
// win. 

```

<div class="row">
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="addBrowserWindowSettings">addBrowserWindowSettings</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="removeBrowserWindowSettings">removeBrowserWindowSettings</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="getBrowserWindowSettings">getBrowserWindowSettings</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="currentWindow">currentWindow</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="getAllWindows">getAllWindows</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="getFocusedWindow">getFocusedWindow</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="fromWebContents">fromWebContents</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="fromId">fromId</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="getName">getName</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="setName">setName</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="id">id</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="close">close</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="isFocused">isFocused</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="show">show</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="showInactive">showInactive</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="hide">hide</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="isVisible">isVisible</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="maximize">maximize</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="unmaximize">unmaximize</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="isMaximized">isMaximized</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="minimize">minimize</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="restore">restore</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="isMinimized">isMinimized</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="setFullScreen">setFullScreen</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="isFullScreen">isFullScreen</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="setBounds">setBounds</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="getBounds">getBounds</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="setSize">setSize</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="getSize">getSize</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="setMinimumSize">setMinimumSize</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="getMinimumSize">getMinimumSize</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="setMaximumSize">setMaximumSize</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="getMaximumSize">getMaximumSize</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="setResizable">setResizable</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="isResizable">isResizable</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="setMovable">setMovable</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="isMovable">isMovable</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="setMinimizable">setMinimizable</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="isMinimizable">isMinimizable</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="setMaximizable">setMaximizable</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="isMaximizable">isMaximizable</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="setFullScreenable">setFullScreenable</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="isFullScreenable">isFullScreenable</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="setClosable">setClosable</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="isClosable">isClosable</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="setAlwaysOnTop">setAlwaysOnTop</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="isAlwaysOnTop">isAlwaysOnTop</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="center">center</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="setPosition">setPosition</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="getPosition">getPosition</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="setTitle">setTitle</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="getTitle">getTitle</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="flashFrame">flashFrame</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="topmost">topmost</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="isTopmost">isTopmost</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="setSkipTaskbar">setSkipTaskbar</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="getNativeWindowHandle">getNativeWindowHandle</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="hookWindowMessage">hookWindowMessage</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="isWindowMessageHooked">isWindowMessageHooked</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="unhookWindowMessage">unhookWindowMessage</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="unhookAllWindowMessages">unhookAllWindowMessages</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="focusOnWebView">focusOnWebView</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="blurWebView">blurWebView</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="capturePage">capturePage</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="loadURL">loadURL</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="reload">reload</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="setMenu">setMenu</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="setProgressBar">setProgressBar</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="setOverlayIcon">setOverlayIcon</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="setHasShadow">setHasShadow</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="hasShadow">hasShadow</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="showDevTools">showDevTools</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="closeDevTools">closeDevTools</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="exec">exec</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="sync">sync</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="async">async</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="enableDrag">enableDrag</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="disableDrag">disableDrag</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="getBrowser">getBrowser</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="toggleFullScreen">toggleFullScreen</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="toggleVisible">toggleVisible</button>  </div> 
    <div class="col-xs-3"><button class="btn btn-outline-primary btn-block" id="setIcon ">setIcon</button>  </div> 
</div>