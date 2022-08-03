# Process

  子进程类.<br>工作线程**Renderer线程**
  
* **父类** 
<a href="#api/apiRunnable">Runnable</a>&nbsp;

## ProcessTransfer <span class="label label-constructor">构造</span> <span class="label label-sync">同步</span> 

  创建一个进程类.
  
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
	<td>进程路径 .</td>
</tr>
	</tbody>
</table>

* **返回值**
  Process 进程对象. 



<div class="adoc" id="div_ProcessTransfer"></div>


## findPIDByName <span class="label label-static">静态</span> <span class="label label-sync">同步</span> 

  通过程序名称查找进程.
  
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
	<td>程序名.</td>
</tr>
	</tbody>
</table>

* **返回值**
  Array 与程序名匹配的进程ID列表. 



<div class="adoc" id="div_findPIDByName"></div>


## terminateProcessByName 

  通过程序名称结束进程.
  
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
	<td>程序名.</td>
</tr>
	</tbody>
</table>

* **返回值**
  Boolean true成功/false失败. 



<div class="adoc" id="div_terminateProcessByName"></div>


## killProcessByName 

  通过程序名杀死进程.
  
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
	<td>程序名.</td>
</tr><tr>
	<td>Boolean</td>
	<td>true </td>
	<td>是否杀死子进程.</td>
</tr>
	</tbody>
</table>

* **返回值**
  Boolean true成功/false失败. 



<div class="adoc" id="div_killProcessByName"></div>


## start 

  运行子程序.
  
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
	<td>启动参数.</td>
</tr>
	</tbody>
</table>

* **返回值**
  Boolean true成功/false失败. 



<div class="adoc" id="div_start"></div>


## getResult 

  获取子进程执行结果，该函数应该放到线程里面去执行，不然会将渲染进程阻塞.
  
* **函数参数**  无

* **返回值**
   无. 

