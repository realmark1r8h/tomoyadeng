# 对话框
 ipc为全局对象，页面通过include('ipc')加载使用;  Node自己包含
  js自带的弹出框 会阻塞UI线程，UI线程与Render线程同步交互时同样会阻塞UI线程，CEF和NCUI进行同步的方式不同，所以当UI线程同步调用JS
  时如果JS执行的函数会阻塞UI线程，那么会造成死锁，本类的函数代替原生js函数解决部分死锁。
  <link rel="stylesheet" type="text/css" href="docs/css/common.css" />
  <script src="docs/js/string.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/template.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/ipc.js" type="text/javascript" charset="utf-8"></script>
  
## 接口说明
<ul><li class="param">函数接口:</li></ul>

<table id="method" class="table" >
</table>
 
 
 
## 发送消息

```html
// 发送普通消息，没有执行结果
var val = ipc.exec('message', 123);
// 发送同步消息
var val = ipc.sync('message', 123);
// 发送异步消息
ipc.async('message', 123, function(val) {
        console.dir(val);
});
```

<div class="row">
    <div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="exec">普通IPC</button>
    </div>
    <div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="sync">同步IPC</button>
    </div>
    <div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="async">异步IPC</button>
    </div>
    <div class="col-xs-3">
      <a class="btn btn-outline-primary btn-block"  href="docs/partial/ipcTest.html" target="blank">查看效果</a>
    </div>
</div>

## 监听消息

```html
// 监听消息
var val = ipc.on('message', function(){
    return 344;
});
```

<div class="row">
    <div class="col-xs-3">
      <button class="btn btn-outline-primary btn-block"  id="exec">监听消息</button>
    </div>
</div>