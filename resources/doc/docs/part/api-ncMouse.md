# 鼠标
  mouse为全局对象，页面通过include('mouse')加载使用;  Node自己包含
     程序会启动时创建一个隐藏的托盘图标
  <link rel="stylesheet" type="text/css" href="docs/css/common.css" />
  <script src="docs/js/string.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/template.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/mouse.js" type="text/javascript" charset="utf-8"></script>
  
## 接口说明
<ul><li class="param">函数接口:</li></ul>

<table id="method" class="table" >
     
</table>
 
 

## 鼠标操作


```html
//显示托盘
var x = 100;
var y = 200;
// 
mouse.leftClick(x, y);
mouse.leftDown(x, y);
mouse.leftUp(x, y);
mouse.leftDoubleClick(x, y);
mouse.rightClick(x, y);
mouse.rightDown(x, y);
mouse.rightUp(x, y);
mouse.middleClick(x, y);
mouse.moveTo(x, y);
mouse.moveR(x, y);
// 鼠标滚轮，向上滚动
mouse.click(x, y);
mouse.mouseWheel(120);
// 鼠标滚轮 ，向下滚动
mouse.click(x, y);
mouse.mouseWheel(-120);
// 
mouse.saveMousePos();
mouse.restoreMousePos();
mouse.lockMouse();
mouse.unlockMouse();
mouse.waitClick();
mouse.getLastClick();
var val =mouse.getCursorPos();
mouse.setCursorPos(100, 500);
mouse.click(300, 80);
// 屏幕转窗口
var val =mouse.screenToClient(BrowserWindow.currentWindow, 300, 80);
console.dir(val);
// 窗口转屏幕
var val =mouse.clientToScreen(BrowserWindow.currentWindow, 300, 80);
console.dir(val);
// 
mouse.hideCursor();
mouse.showCursor();
 
 
```
<div class="row">
    <div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="leftClick">单击左键</button>
    </div>
    <div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="leftDown">按下左键</button>
    </div>
  	<div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="leftUp">弹起左键</button>
    </div>
  	<div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="leftDoubleClick">双击左键</button>
    </div>
  	<div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="rightClick">单击右键</button>
    </div>
  	<div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="rightDown">按下右键</button>
    </div>
  	<div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="rightUp">弹起右键</button>
    </div>
  	<div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="middleClick">单击中键</button>
    </div>
  	<div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="moveTo">移动鼠标</button>
    </div>
  	<div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="moveR">移动鼠标（相对对当前位置）</button>
    </div>
  	<div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="mouseWheelUp">鼠标滚轮（向上）</button>
    </div>
    	<div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="mouseWheelDown">鼠标滚轮（向下）</button>
    </div>
  	<div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="saveMousePos">保存鼠标位置</button>
    </div>
  	<div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="restoreMousePos">还原鼠标位置</button>
    </div>
  	<div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="lockMouse">锁定鼠标</button>
    </div>
  	<div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="unlockMouse">解锁鼠标</button>
    </div>
  	<div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="waitClick">等待鼠标事件</button>
    </div>
  	<div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="getLastClick">获取上一次鼠标按键</button>
   </div> 
    <div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="getCursorPos">获取鼠标位置</button>
    </div>
    <div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="setCursorPos">设置鼠标位置</button>
    </div>
    <div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="sendClick">单击</button>
    </div>
    <div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="screenToClient">坐标在窗口中的位置</button>
    </div>
    <div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="clientToScreen">坐标在屏幕中的位置</button>
    </div>
     <div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="hideCursor">隐藏鼠标</button>
    </div>
     <div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="showCursor">显示鼠标</button>
    </div>
</div>