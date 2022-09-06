# FileStream

  文件读写类.
  
* **父类** 
<a href="#api/apiRunnable">Runnable</a>&nbsp;

## FileStream &nbsp;<span class="label label-constructor">构造</span> 

  创建或打开一个文件.
  
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
	<td>需要操作文件的路径.</td>
</tr><tr>
	<td>Int</td>
	<td>3	</td>
	<td>文件打开方式，可以选择以下值，组合使用.<br>&nbsp;&nbsp;&nbsp;&nbsp; 1 以只读方式打开，如果文件不存在，那么将打开失败<br>&nbsp;&nbsp;&nbsp;&nbsp; 2 以写方式打开，如果文件不存在则会创建文件<br>&nbsp;&nbsp;&nbsp;&nbsp; 8 以追加方式打开<br>&nbsp;&nbsp;&nbsp;&nbsp; 32 以二进制方式打开文件<br></td>
</tr>
	</tbody>
</table>

* **返回值**
  FileStream  



<div class="adoc" id="div_FileStream"></div>


## open &nbsp;<span class="label label-sync">同步</span> 

  打开文件，创建对象时会默认打开文件，不需要重复调用.如果你调用了<a href="#extend/extendFileStream/5">close</a>函数，那么可以调用该函数重新打开文件
  
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
	<td>int</td>
	<td>0 </td>
	<td>文件打开方式，参见<a href="#extend/extendFileStream/0">构造函数</a>的内容.如果不输入该参数，程序会使用创建该对象时指定的打开方式</td>
</tr>
	</tbody>
</table>

* **返回值**
  Boolean . 



<div class="adoc" id="div_open"></div>


## read &nbsp;<span class="label label-sync">同步</span> 

  读取所有文件内容.
  
* **函数参数**  无

* **返回值**
  String 读取到的字符串. 



<div class="adoc" id="div_read"></div>


## write &nbsp;<span class="label label-sync">同步</span> 

  向文件中写入字符串.
  
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
	<td>需要写入的数据.</td>
</tr>
	</tbody>
</table>

* **返回值**
  Boolean true 成功/false 失败. 



<div class="adoc" id="div_write"></div>


## append &nbsp;<span class="label label-sync">同步</span> 

  将一个文件的内容追加到当前文件中.
  
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
	<td>文件路径</td>
</tr>
	</tbody>
</table>

* **返回值**
  Boolean true 成功/false 失败. 



<div class="adoc" id="div_append"></div>


## close &nbsp;<span class="label label-sync">同步</span> 

  关闭文件，关闭后不能再调用其他API操作文件.
  
* **函数参数**  无

* **返回值**
   无. 

* **参考** 
<a href="#extend/extendFileStream/1">open</a>



<div class="adoc" id="div_close"></div>


## size &nbsp;<span class="label label-sync">同步</span> 

  获取文件大小.
  
* **函数参数**  无

* **返回值**
  Int . 



<div class="adoc" id="div_size"></div>


## Remove &nbsp;<span class="label label-static">静态</span> <span class="label label-sync">同步</span> 

  删除文件.
  
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
	<td>文件路径.</td>
</tr>
	</tbody>
</table>

* **返回值**
   无. 



<div class="adoc" id="div_Remove"></div>


## remove &nbsp;<span class="label label-sync">同步</span> 

  删除当前文件.
  
* **函数参数**  无

* **返回值**
   无. 



<div class="adoc" id="div_remove"></div>


