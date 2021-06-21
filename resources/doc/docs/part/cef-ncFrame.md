# Frame
  Frame为全局对象，不能创建，只能获取
  js自带的弹出框 会阻塞UI线程，UI线程与Render线程同步交互时同样会阻塞UI线程，CEF和NCUI进行同步的方式不同，所以当UI线程同步调用JS
  时如果JS执行的函数会阻塞UI线程，那么会造成死锁，本类的函数代替原生js函数解决部分死锁。
  <link rel="stylesheet" type="text/css" href="docs/css/common.css" />
  <script src="docs/js/string.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/template.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/Frame.js" type="text/javascript" charset="utf-8"></script>
  
## 接口说明
<ul><li class="param">函数接口:</li></ul>

<table id="method" class="table" >
</table>
 
 
 
 
 
 