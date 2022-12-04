# splash

  启动画面.<br>工作线程：**UI线程**.
  
* **父类** 
<a href="#api/apiObject">Object</a>&nbsp;

## show &nbsp;<span class="label label-static">静态</span> 

  显示Splash.
  
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
	<td>JsonObject </td>
	<td></td>
	<td>可支持的参数见<a href="#settings/settingsSplashWindowSettings">启动画面</a>.</td>
</tr>
	</tbody>
</table>

* **返回值**
   无. 

* **参考** 
<a href="#api/apisplash/1">hide</a>

* **示例&nbsp;&nbsp;&nbsp;&nbsp;**

```html
include('splash');
splash.show({
   image: 'images/splash.jpg',
   duration: 5000
});

```


<div class="adoc" id="div_show"></div>


## hide &nbsp;<span class="label label-static">静态</span> 

  n毫秒后隐藏Splash，n由<a href="#api/apisplash/0">show</a>中设置的fadeout决定.
  
* **函数参数**  无

* **返回值**
   无. 

* **示例&nbsp;&nbsp;&nbsp;&nbsp;**

```html
include('splash');
splash.hide();

```
*****
  n毫秒后隐藏Splash.
  
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
	<td>Int </td>
	<td></td>
	<td>指定延时时间n (毫秒).</td>
</tr>
	</tbody>
</table>

* **返回值**
   无. 

* **示例&nbsp;&nbsp;&nbsp;&nbsp;**

```html
include('splash');
splash.hide(3000);

```


<div class="adoc" id="div_hide"></div>


## isVisible &nbsp;<span class="label label-static">静态</span> <span class="label label-sync">同步</span> 

  判断Splash是否可见.
  
* **函数参数**  无

* **返回值**
  Boolean . 

* **示例&nbsp;&nbsp;&nbsp;&nbsp;**

```html
include('splash');
console.assert(splash.isVisible() == false);

```


<div class="adoc" id="div_isVisible"></div>


