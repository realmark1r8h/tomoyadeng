# 对话框
 dialog为全局对象，页面通过include('dialog')加载使用;
  
js自带的弹出框 会阻塞UI线程，UI线程与Render线程同步交互时同样会阻塞UI线程，CEF和NCUI进行同步的方式不同，所以当UI线程同步调用JS
 时如果JS执行的函数会阻塞UI线程，那么会造成死锁，本类的函数代替原生js函数解决部分死锁。
  
  <link rel="stylesheet" type="text/css" href="docs/css/common.css" />
  <script src="docs/js/string.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/template.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/dialog.js" type="text/javascript" charset="utf-8"></script>
  
## 接口说明
<ul><li class="param">函数接口:</li></ul>

<table id="method" class="table" >
</table>
 
 
<ul><li class="param">对话框模式:</li></ul>

<table id="settings" class="table">
</table>
  
## 文件对话框

```html
// 获取屏幕信息
var val = desktop.getScreenInfo();
console.dir(val);
```

<div class="row">
	 <div class="col-xs-3">
  	<button class="btn btn-outline-primary btn-block" id="dialogOpen">单文件选择</button>
	</div> 
	<div class="col-xs-3">
	  <button class="btn btn-outline-primary btn-block" id="dialogOpenMultiple">多文件选择</button>
	</div> 
	<div class="col-xs-3">
	  <button class="btn btn-outline-primary btn-block" id="dialogOpenFolder">文件夹选择</button>
	</div> 
	<div class="col-xs-3">
	  <button class="btn btn-outline-primary btn-block" id="dialogSave">文件保存</button>
	</div> 
</div>

## 弹出框

```html
// 获取屏幕信息
var val = desktop.getScreenInfo();
console.dir(val);
```

<div class="row">
	<div class="col-xs-3">
	  <button class="btn btn-outline-primary btn-block" id="alert">alert</button>
	</div> 
	<div class="col-xs-3">
	  <button class="btn btn-outline-primary btn-block" id="confirm">confirm</button>
	</div> 
	<div class="col-xs-3">
	  <button class="btn btn-outline-primary btn-block" id="prompt">prompt</button>
	</div> 
</div>

 
 
 