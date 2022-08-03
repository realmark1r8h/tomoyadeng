# Browser

  CEF提供的浏览器类封装.<br>工作线程：**UI线程**.
  
## GetHost 

  获取浏览器的Host对象.
  
* **函数参数**  无

* **返回值**
  BrowserHost . 



<div class="adoc" id="div_GetHost"></div>


## CanGoBack 

  判断当前浏览器是否可以后退.
  
* **函数参数**  无

* **返回值**
  Boolean true可以后退/false不能回退. 



<div class="adoc" id="div_CanGoBack"></div>


## GoBack 

  后退.
  
* **函数参数**  无

* **返回值**
   无. 



<div class="adoc" id="div_GoBack"></div>


## CanGoForward 

  判断当前浏览器是否可以前进.
  
* **函数参数**  无

* **返回值**
  Boolean true可以前进false不能前进. 



<div class="adoc" id="div_CanGoForward"></div>


## GoForward 

  前进.
  
* **函数参数**  无

* **返回值**
   无. 



<div class="adoc" id="div_GoForward"></div>


## IsLoading 

  是否正在加载页面.
  
* **函数参数**  无

* **返回值**
  Boolean true是/false否. 



<div class="adoc" id="div_IsLoading"></div>


## Reload 

  重新加载页面.
  
* **函数参数**  无

* **返回值**
   无. 



<div class="adoc" id="div_Reload"></div>


## ReloadIgnoreCache 

  重新加载页面，无视任何缓存数据.
  
* **函数参数**  无

* **返回值**
   无. 



<div class="adoc" id="div_ReloadIgnoreCache"></div>


## StopLoad 

  停止加载页面.
  
* **函数参数**  无

* **返回值**
   无. 



<div class="adoc" id="div_StopLoad"></div>


## GetIdentifier 

  获取浏览器ID.
  
* **函数参数**  无

* **返回值**
  Int 浏览器ID. 



<div class="adoc" id="div_GetIdentifier"></div>


## IsSame 

  与另一个Borwser对象比较是否相等.
  
* **函数参数**

<table class="table table-hover table-bordered ">
	<thead>
		<tr>
			<th class="col-xs-1">类型</th>
			<th class="col-xs-1">默认值</th>
			<th>说明</th>
		</tr>
	</thead>
	<tbody>
		<tr>
	<td>Object </td>
	<td></td>
	<td>Browser 对象.</td>
</tr>
	</tbody>
</table>

* **返回值**
  Boolean true相同/false失败. 



<div class="adoc" id="div_IsSame"></div>


## IsPopup 

  是否为一个弹出窗口.
  
* **函数参数**  无

* **返回值**
  Boolean true弹出窗口/false非弹出窗口. 



<div class="adoc" id="div_IsPopup"></div>


## HasDocument 

  是否在浏览器中加载了文档.
  
* **函数参数**  无

* **返回值**
  Boolean true有document/false 无document. 



<div class="adoc" id="div_HasDocument"></div>


## GetMainFrame 

  返回浏览器窗口的主（顶层）框架Frame.
  
* **函数参数**  无

* **返回值**
  Frame Frame 对象. 



<div class="adoc" id="div_GetMainFrame"></div>


## GetFocusedFrame 

  返回浏览器窗口的焦点框架Frame.
  
* **函数参数**  无

* **返回值**
  Frame Frame 对象. 



<div class="adoc" id="div_GetFocusedFrame"></div>


## GetFrame 

  通过名称或ID获取Frame.
  
* **函数参数**

<table class="table table-hover table-bordered ">
	<thead>
		<tr>
			<th class="col-xs-1">类型</th>
			<th class="col-xs-1">默认值</th>
			<th>说明</th>
		</tr>
	</thead>
	<tbody>
		<tr>
	<td>Int/String </td>
	<td></td>
	<td>Frame ID 或Frame 名称.</td>
</tr>
	</tbody>
</table>

* **返回值**
  Frame Frame 对象. 



<div class="adoc" id="div_GetFrame"></div>


## GetFrameCount 

  获取Frame个数.
  
* **函数参数**  无

* **返回值**
  Int Frame个数. 



<div class="adoc" id="div_GetFrameCount"></div>


## GetFrameIdentifiers 

  获取所有Frame的ID，返回一个数组[].
  
* **函数参数**  无

* **返回值**
  Array . 



<div class="adoc" id="div_GetFrameIdentifiers"></div>


## GetFrameNames 

  获取所有Frame的名称，返回一个数组[].
  
* **函数参数**  无

* **返回值**
  Array . 



<div class="adoc" id="div_GetFrameNames"></div>


## currentFrame 

  获取当前Frame.
  
* **函数参数**  无

* **返回值**
  Frame Frame 对象. 

