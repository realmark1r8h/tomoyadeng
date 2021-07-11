# 进程通信
  ipc为全局对象，页面通过include('ipc')加载使用; 
  
  <link rel="stylesheet" type="text/css" href="docs/css/common.css" />
  <script src="docs/js/string.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/template.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/splash.js" type="text/javascript" charset="utf-8"></script>
  
## 接口说明
*    函数接口:

<table id="method" class="table" >
</table>
 
 
 
## 显示启动窗口

```html
// 显示启动画面
splash.show({
	image: 'skin/2.jpg'
});
// 5秒后自动关闭
splash.show({
	image: 'skin/2.jpg',
 	duration: 5000
});
```

<div class="row">
    <div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="show">显示</button>
    </div>
    <div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="showWithDelay">显示（延时5秒关闭）</button>
    </div>
</div>

## 隐藏启动窗口

```html
// 关闭启动画面
splash.hide(); 
```

<div class="row">
    <div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="hide">关闭</button>
    </div>
</div>