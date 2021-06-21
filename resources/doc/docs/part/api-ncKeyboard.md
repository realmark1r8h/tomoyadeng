# 键盘
   keyboard为全局对象，页面通过include('keyboard')加载使用;
  <link rel="stylesheet" type="text/css" href="docs/css/common.css" />
  <script src="docs/js/string.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/template.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/keyboard.js" type="text/javascript" charset="utf-8"></script>
  
## 接口说明
<ul><li class="param">函数接口:</li></ul>

<table id="method" class="table" >
</table>
 
 
<ul><li class="param">特殊键盘码:</li></ul>

<table id="settings" class="table">
</table>
  
## 键盘操作

```html
// 移动鼠标
mouse.moveR(0, -60);
mouse.click();
// 发送一个字符串
keyboard.sayString(`msdn对此方式的说明为：input_keyboard支持非键盘的输入方式，
	例如手写识别或语音识别，通过KEYEVENTF_UNICODE标识，这些方式与键盘（文本）输入别无二致。
	如果指定了KEYEVENTF_UNICODE，SendInput发送一个WM_KEYDOWN或WM_KEYUP消息给活动窗口的线程消息队列，
	消息的wParam参数为VK_PACKET。GetMessage或PeedMessage一旦获得此消息，
	就把它传递给TranslateMessage，TranslateMessage根据wScan中指定的Unicode字符产生一个WM_CHAR消息。
	若窗口是ANSI窗口，则Unicode字符会自动转换为相应的ANSI字符。`); 
keyboard.keyPress(keyboard.VK_MENU, keyboard.VK_F4);
keyboard.keyDown('1');
keyboard.keyUp('1');
```

<div id="text" class="example code" contenteditable="true">
 
</div>

<div class="row">
	<div class="col-xs-3">
		<button class="btn btn-outline-primary btn-block"  id="sayString">发送字符串</button>
	</div>
	<div class="col-xs-3">
		<button class="btn btn-outline-primary btn-block"  id="keyPress">关闭窗口(ALT+F4)</button>
	</div>
	<div class="col-xs-3">
		<button class="btn btn-outline-primary btn-block"  id="keyDown">按下</button>
	</div>
	<div class="col-xs-3">
		<button class="btn btn-outline-primary btn-block" id="keyUp">弹起</button>
	</div>
</div>
	 


 
 
 