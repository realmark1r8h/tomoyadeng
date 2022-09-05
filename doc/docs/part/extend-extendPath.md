# Path

  路径库.<br>工作线程**Renderer线程**
  
* **父类** 
<a href="#api/apiRunnable">Runnable</a>&nbsp;

## getFullAppDir &nbsp;<span class="label label-static">静态</span> <span class="label label-sync">同步</span> 

  返回当前程序所在目录.
  
* **函数参数**  无

* **返回值**
  Path 返回一个Path对象. 



<div class="adoc" id="div_getFullAppDir"></div>


## getFullAppName &nbsp;<span class="label label-static">静态</span> <span class="label label-sync">同步</span> 

  获取当前程序的完整路径.
  
* **函数参数**  无

* **返回值**
  Path 返回一个Path对象. 



<div class="adoc" id="div_getFullAppName"></div>


## fileExsit &nbsp;<span class="label label-static">静态</span> <span class="label label-sync">同步</span> 

  判断文件或目录是否存在.
  
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
	<td>路径.</td>
</tr>
	</tbody>
</table>

* **返回值**
  Boolean true 存在/false 不存在. 



<div class="adoc" id="div_fileExsit"></div>


## Remove &nbsp;<span class="label label-static">静态</span> 

  删除一个文件，或空目录.
  
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
	<td>路径.</td>
</tr>
	</tbody>
</table>

* **返回值**
  Boolean true 成功/false 失败. 



<div class="adoc" id="div_Remove"></div>


## RemoveAll &nbsp;<span class="label label-static">静态</span> 

  删除一个文件或文件夹，文件目录可以不为空.
  
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
	<td>路径.</td>
</tr>
	</tbody>
</table>

* **返回值**
  Boolean true 成功/false 失败. 



<div class="adoc" id="div_RemoveAll"></div>


## toString &nbsp;<span class="label label-sync">同步</span> 

  将当前Path对象转换为String.
  
* **函数参数**  无

* **返回值**
  String . 



<div class="adoc" id="div_toString"></div>


## isExsit &nbsp;<span class="label label-sync">同步</span> 

  判断当前路径是否存在.
  
* **函数参数**  无

* **返回值**
  Boolean true 存在/ false 不存在. 



<div class="adoc" id="div_isExsit"></div>


## append &nbsp;<span class="label label-sync">同步</span> 

  往当前路径中追加子路径.
  
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
	<td>需要追加了路径.</td>
</tr>
	</tbody>
</table>

* **返回值**
  Path 当前对象. 



<div class="adoc" id="div_append"></div>


## removeFileSpec &nbsp;<span class="label label-sync">同步</span> 

  去除文件名，得到目录.
  
* **函数参数**  无

* **返回值**
  Path 当前对象. 



<div class="adoc" id="div_removeFileSpec"></div>


## copyTo &nbsp;<span class="label label-sync">同步</span> 

  复制文件到指定位置.
  
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
	<td>目标位置.</td>
</tr>
	</tbody>
</table>

* **返回值**
  Boolean true 存在/ false 不存在. 



<div class="adoc" id="div_copyTo"></div>


## moveTo &nbsp;<span class="label label-sync">同步</span> 

  移动文件到指定位置.
  
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
	<td>目标位置.</td>
</tr>
	</tbody>
</table>

* **返回值**
  Boolean true 存在/ false 不存在. 



<div class="adoc" id="div_moveTo"></div>


## remove &nbsp;
  删除当前路径，该路径只能是一个文件或空目录删除一个文件，或空目录.
  
* **函数参数**  无

* **返回值**
  Boolean true 成功/false 失败. 



<div class="adoc" id="div_remove"></div>


## removeAll &nbsp;
  删除当前路径，可以删除子目录，.
  
* **函数参数**  无

* **返回值**
  Boolean true 成功/false 失败. 



<div class="adoc" id="div_removeAll"></div>


