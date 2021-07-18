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

*    show 参数说明:
 <table id="settings" class="table" >
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
// 使用默认关闭时间
splash.hide(); 
// 自定义关闭时间
splash.hide(5000);
// 直接关闭
splash.hide(0); 
```

<div class="row">
    <div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="hide">关闭</button>
    </div>
    <div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="hideWithDelay">关闭（3秒动画）</button>
    </div>
</div>