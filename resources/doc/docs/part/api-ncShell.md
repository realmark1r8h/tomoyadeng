# Shell
  shell为全局对象，页面通过include('shell')加载使用; 
  <link rel="stylesheet" type="text/css" href="docs/css/common.css" />
  <script src="docs/js/string.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/template.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/shell.js" type="text/javascript" charset="utf-8"></script>
  
## 接口说明
*    函数接口:

<table id="method" class="table" >
</table>
 
 
*    ShowCmd 参数可选值:

<table id="settings" class="table">
</table>
  
## Shell操作

```html
// 获取屏幕信息
var val = desktop.getScreenInfo();
console.dir(val);
```

<div class="row">
	<div class="col-xs-3">
		<button class="btn btn-outline-primary btn-block" class="btn btn-outline-primary" id="open">打开文件</button>
	</div>
	<div class="col-xs-3">
		 <button class="btn btn-outline-primary btn-block" id="print">打印文件</button>
	</div>
	<div class="col-xs-3">
		<button class="btn btn-outline-primary btn-block" id="exec">执行</button>
	</div>
	<div class="col-xs-3">
		<button class="btn btn-outline-primary btn-block" id="showItemInFolder">文件夹中显示文件</button>
	</div>
	<div class="col-xs-3">
		<button class="btn btn-outline-primary btn-block" id="location">定位文件</button>
	</div>
</div>

 
 
 