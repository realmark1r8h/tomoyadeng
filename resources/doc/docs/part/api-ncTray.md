# 托盘模块
  tray为全局对象，页面通过include('tray')加载使用; 

程序会启动时创建一个隐藏的托盘图标
  <link rel="stylesheet" type="text/css" href="docs/css/common.css" />
  <script src="docs/js/string.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/template.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/tray.js" type="text/javascript" charset="utf-8"></script>
  
## 接口说明
<ul><li class="param">函数接口:</li></ul>

<table id="method" class="table" >
     
</table>
 
<ul><li class="param">事件说明:</li></ul>

<table id="event" class="table" >
     
</table>  

## 托盘操作


```html
//显示托盘
tray.show();  
tray.hide();
tray.setIcon('skin/logo1.ico');
tray.setIcon('skin/logo2.ico');
tray.setTooltip(new Date().toString());
tray.blink(true);
tray.blink(false);
var bBlink = tray.isBlink(); 
 
```
<div class="row">
    <div class="col-xs-3">
         <button class ="btn btn-outline-primary btn-block" id="show">显示托盘</button>
    </div>
    <div class="col-xs-3">
         <button class ="btn btn-outline-primary btn-block" id="hide">隐藏托盘</button>
    </div>
    <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="setIcon">设置图标</button>
    </div>
    <div class="col-xs-3">
         <button class ="btn btn-outline-primary btn-block" id="setIcon1">设置图标1</button>
    </div>
    <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="setIcon2">设置图标2</button>
    </div>
    <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="setIcon3">设置图标3</button>
    </div>
    <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="startBlink">闪烁托盘</button>
    </div>
    <div class="col-xs-3">
         <button class ="btn btn-outline-primary btn-block" id="stopBlink">停止闪烁</button>
    </div>
    <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="isBlink">是否闪烁</button>
    </div>
    <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="setTooltip">设置提示文本</button>
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