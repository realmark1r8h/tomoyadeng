# Frame

  CEF Frame 封装.<br>工作线程：**UI线程**.
  
* **父类** 
<a href="#api/apiObject">Object</a>&nbsp;

## injectSrcipt &nbsp;
  向页面注入JS代码.
  
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
	<td>String </td>
	<td></td>
	<td>JS代码.</td>
</tr>
	</tbody>
</table>

* **返回值**
  Boolean true成功/false失败. 



<div class="adoc" id="div_injectSrcipt"></div>


## injectCSS &nbsp;
  向页面注入CSS代码.
  
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
	<td>String </td>
	<td></td>
	<td>CSS代码.</td>
</tr>
	</tbody>
</table>

* **返回值**
  Boolean true成功/false失败. 



<div class="adoc" id="div_injectCSS"></div>


## IsValid &nbsp;
  当前页面是否有效.
  
* **函数参数**  无

* **返回值**
  Boolean true有效/false无效. 



<div class="adoc" id="div_IsValid"></div>


## Undo &nbsp;
  撤消.
  
* **函数参数**  无

* **返回值**
   无. 



<div class="adoc" id="div_Undo"></div>


## Redo &nbsp;
  重做.
  
* **函数参数**  无

* **返回值**
   无. 



<div class="adoc" id="div_Redo"></div>


## Cut &nbsp;
  剪切.
  
* **函数参数**  无

* **返回值**
   无. 



<div class="adoc" id="div_Cut"></div>


## Copy &nbsp;
  复制.
  
* **函数参数**  无

* **返回值**
   无. 



<div class="adoc" id="div_Copy"></div>


## Paste &nbsp;
  粘贴.
  
* **函数参数**  无

* **返回值**
   无. 



<div class="adoc" id="div_Paste"></div>


## Delete &nbsp;
  删除.
  
* **函数参数**  无

* **返回值**
   无. 



<div class="adoc" id="div_Delete"></div>


## SelectAll &nbsp;
  全选.
  
* **函数参数**  无

* **返回值**
   无. 



<div class="adoc" id="div_SelectAll"></div>


## ViewSource &nbsp;
  查看网页源代码.
  
* **函数参数**  无

* **返回值**
   无. 



<div class="adoc" id="div_ViewSource"></div>


## LoadURL &nbsp;
  加载URL.
  
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
	<td>String </td>
	<td></td>
	<td>URL.</td>
</tr>
	</tbody>
</table>

* **返回值**
   无. 



<div class="adoc" id="div_LoadURL"></div>


## IsMain &nbsp;
  当前页面是否为主页面.
  
* **函数参数**  无

* **返回值**
  Boolean . 



<div class="adoc" id="div_IsMain"></div>


## IsFocused &nbsp;
  当前页面是否获得焦点.
  
* **函数参数**  无

* **返回值**
  Boolean . 



<div class="adoc" id="div_IsFocused"></div>


## GetName &nbsp;
  获取当前页面的名称.
  
* **函数参数**  无

* **返回值**
  String 页面名称. 



<div class="adoc" id="div_GetName"></div>


## GetIdentifier &nbsp;
  获取当前页面的ID.
  
* **函数参数**  无

* **返回值**
  Int identifier. 



<div class="adoc" id="div_GetIdentifier"></div>


## GetParent &nbsp;
  获取当前页面的父页面.
  
* **函数参数**  无

* **返回值**
  Frame . 



<div class="adoc" id="div_GetParent"></div>


## GetURL &nbsp;
  获取当前页面的URL.
  
* **函数参数**  无

* **返回值**
  String url. 



<div class="adoc" id="div_GetURL"></div>


## GetBrowser &nbsp;
  获取当前页面所属的Browser对象.
  
* **函数参数**  无

* **返回值**
  Browser . 

