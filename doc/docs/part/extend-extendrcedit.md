# rcedit

  资源编辑器，用来生成exe程序.
  
## loadDiskSettings <span class="label label-static">静态</span> <span class="label label-sync">同步</span> 

  从磁盘中加载配置文件.
  
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
	<td>配置文件路径，文件内容必须为JSON格式.</td>
</tr>
	</tbody>
</table>

* **返回值**
  Boolean . 



<div class="adoc" id="div_loadDiskSettings"></div>


## getDefaultFileSettings <span class="label label-static">静态</span> <span class="label label-sync">同步</span> 

  获取默认的文件参数.
  
* **函数参数**  无

* **返回值**
  JsonObject . 



<div class="adoc" id="div_getDefaultFileSettings"></div>


## getDefaultAppSettings <span class="label label-static">静态</span> <span class="label label-sync">同步</span> 

  获取默认的APP启动参数.
  
* **函数参数**  无

* **返回值**
  JsonObject . 



<div class="adoc" id="div_getDefaultAppSettings"></div>


## getDefaultBrowserSettings 

  获取默认的浏览器窗口启动参数.
  
* **函数参数**  无

* **返回值**
  JsonObject . 



<div class="adoc" id="div_getDefaultBrowserSettings"></div>


## getDefaultSplashSettings <span class="label label-static">静态</span> <span class="label label-sync">同步</span> 

  获取默认的启动画面.
  
* **函数参数**  无

* **返回值**
  JsonObject . 



<div class="adoc" id="div_getDefaultSplashSettings"></div>


## commit <span class="label label-static">静态</span> <span class="label label-sync">同步</span> 

  生成EXE文件，这个函数将把配置好的参数写入EXE文件中.
  
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
	<td>配置文件目录.</td>
</tr><tr>
	<td>String </td>
	<td></td>
	<td>启动参数,JSON字符串</td>
</tr><tr>
	<td>String </td>
	<td></td>
	<td>浏览器窗口参数,JSON字符串</td>
</tr><tr>
	<td>String </td>
	<td></td>
	<td>启动画面参数,JSON字符串</td>
</tr>
	</tbody>
</table>

* **返回值**
  Boolean . 

