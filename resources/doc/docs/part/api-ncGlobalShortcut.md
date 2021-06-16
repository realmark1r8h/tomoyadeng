# 对话框
  dialog为全局对象，页面通过include('dialog')加载使用;  Node自己包含
  js自带的弹出框 会阻塞UI线程，UI线程与Render线程同步交互时同样会阻塞UI线程，CEF和NCUI进行同步的方式不同，所以当UI线程同步调用JS
  时如果JS执行的函数会阻塞UI线程，那么会造成死锁，本类的函数代替原生js函数解决部分死锁。
  <link rel="stylesheet" type="text/css" href="docs/css/common.css" />
  <script src="docs/js/string.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/template.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/globalShortcut.js" type="text/javascript" charset="utf-8"></script>
  
## 接口说明
<ul><li class="param">函数接口:</li></ul>

<table id="method" class="table" >
</table>
 
 
<ul><li class="param">registerShortcut参数:</li></ul>

<table id="settings" class="table">
</table>

<ul><li class="param">可监听事件:</li></ul>

<table id="eventSettings" class="table">
</table>
  
  
## 操作说明

```html
// 注册快捷键
var id = globalShortcut.registerShortcut({ ctrl: true, alt: true, key: 'O', action: 'toggleVisible' });
 // 也可以直接使用字符串注册
// globalShortcut.registerShortcut('MOD_CONTROL+MOD_ALT+O');
// 使用id判断快捷键是否注册
var bRegisted = globalShortcut.isRegistered(id);
// 使用字符串判断快捷键是否注册
var bRegisted = globalShortcut.isRegistered('MOD_CONTROL+MOD_ALT+O');
// 反注册
globalShortcut.unregisterShortcut(id);
globalShortcut.unregisterShortcut('MOD_CONTROL+MOD_ALT+O');
// 反注册所有热键
globalShortcut.unregisterAll(); 
```

<div class="row">
		<div class="col-xs-3">
			<button class ="btn btn-outline-primary btn-block" id="registerShortcut">注册热键</button>
		</div>
		<div class="col-xs-3">
			<button class ="btn btn-outline-primary btn-block" id="isRegistered">判断是否注册</button>
		</div>
		<div class="col-xs-3">
			<button class ="btn btn-outline-primary btn-block" id="unregisterShortcut">销毁热键</button>
		</div>
		<div class="col-xs-3">
			<button class ="btn btn-outline-primary btn-block" id="unregisterAll">销毁所有热键</button>
		</div>
</div> 

## 事件监听
```html
// 注册快捷键
globalShortcut.registerShortcut('MOD_CONTROL+MOD_ALT+P');
// 监听事件
globalShotcut.on('hotkeydown', function(target){
		console.dir(target);
});
```
<div class="row">
		<div class="col-xs-3">
			<button class ="btn btn-outline-primary btn-block" id="registerShortcutForEvent">监听</button>
		</div>
</div> 
