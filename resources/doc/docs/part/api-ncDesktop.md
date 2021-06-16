# 屏幕
  desktop为全局对象，页面通过include('desktop')加载使用;<br>
     用于获取桌面的基本信息.
  <link rel="stylesheet" type="text/css" href="docs/css/common.css" />
  <script src="docs/js/string.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/template.js" type="text/javascript" charset="utf-8"></script>
	<script src="docs/js/desktop.js" type="text/javascript" charset="utf-8"></script>
  
## 接口说明
<ul><li class="param">函数接口:</li></ul>

<table id="method" class="table" >
</table>
 
  
## 屏幕信息

```html
// 获取屏幕信息
var info = desktop.getScreenInfo();
console.dir(info);
```

<div class="row">
	<div class="col-xs-3">
        <button class="btn btn-outline-primary btn-block" id="getScreenInfo">获取屏幕信息</button>
  </div>
</div>
 