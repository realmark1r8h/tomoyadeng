# Object

  所有JS扩展对象所对应的C++类基类；该类不能被直接使用,需要编写C++扩展时继承该类，并映射成JS类使用.
  
## CLASS &nbsp;<span class="label label-static">静态</span> <span class="label label-const">常量</span> <span class="label label-property">属性</span> <span class="label label-single">单线程</span> 

  获取当前类所对象的对象，调用该对象的函数将会作用到类上面去.
  
* **函数参数**  无

* **返回值**
  Object 类所对象的CLASS对象. 



<div class="adoc" id="div_CLASS"></div>


## fromObjectName &nbsp;<span class="label label-static">静态</span> <span class="label label-single">单线程</span> <span class="label label-sync">同步</span> 

  通过对象名称查找对象.
  
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
	<td>对象名称.</td>
</tr>
	</tbody>
</table>

* **返回值**
  Object 如果对象存在，返回该对象; 如果不存在，返回Undefined. 

* **参考** 
<a href="#api/apiObject/2">fromObjectID</a>



<div class="adoc" id="div_fromObjectName"></div>


## fromObjectID &nbsp;<span class="label label-static">静态</span> <span class="label label-single">单线程</span> <span class="label label-sync">同步</span> 

  通过对象ID查找对象.
  
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
	<td>对象ID.</td>
</tr>
	</tbody>
</table>

* **返回值**
  Object 如果对象存在，返回该对象; 如果不存在，返回Undefined. 

*****
  通过对象ID查找对象.
  
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
	<td>对象ID.</td>
</tr>
	</tbody>
</table>

* **返回值**
  Object 如果对象存在，返回该对象; 如果不存在，返回Undefined. 

* **参考** 
<a href="#api/apiObject/1">fromObjectName</a>



<div class="adoc" id="div_fromObjectID"></div>


## setObjectName &nbsp;<span class="label label-static">静态</span> 

  设置当前对象名称.
  
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
	<td>对象名称.</td>
</tr>
	</tbody>
</table>

* **返回值**
   无. 



<div class="adoc" id="div_setObjectName"></div>


## getObjectName &nbsp;<span class="label label-single">单线程</span> <span class="label label-sync">同步</span> 

  获取当前对象名称.
  
* **函数参数**  无

* **返回值**
  String 对象名称. 



<div class="adoc" id="div_getObjectName"></div>


## notify &nbsp;
  向自己发送一个通知，可以监听这个通知得到返回结果(当transfer在单独的线程上执行时，可以通过自己定义消息来监听执行进度).
  
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
	<td>任务Javascript所支持的基本类型（Int Double String JsonObject Array）.</td>
</tr>
	</tbody>
</table>

* **返回值**
   无. 



<div class="adoc" id="div_notify"></div>


## relase &nbsp;<span class="label label-single">单线程</span> 

  释放当前对象所对应的C++对象，该函数调用后页面上对应的对象将无法使用
  
* **函数参数**  无

* **返回值**
   无. 



<div class="adoc" id="div_relase"></div>


## getUserData &nbsp;<span class="label label-single">单线程</span> <span class="label label-sync">同步</span> 

  获取用户保存的自定义数据.
  
* **函数参数**  无

* **返回值**
  JsonObject 所有配置参数. 

*****
  根据输入字段返回用户保存的自定义数据.
  
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
	<td>需要获取的字段名称.</td>
</tr>
	</tbody>
</table>

* **返回值**
   返回字段名所对应的数据。返回类型视配置参数类型而定，为JS所支持的基本数据类型. 

* **参考** 
<a href="#api/apiObject/8">setUserData</a>



<div class="adoc" id="div_getUserData"></div>


## setUserData &nbsp;<span class="label label-single">单线程</span> 

  保存自定义数据.该函数并不要求一定要输入所支持的参数，你也可以设置自定义参数，并在getUserData里面获取所设置的值与<a href="#api/apiObject/7">getUserData</a>相对应.
  
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
	<td>需要设置的参数，该值为一个JSON对象.</td>
</tr>
	</tbody>
</table>

* **返回值**
   无. 

* **参考** 
<a href="#api/apiObject/7">getUserData</a>



<div class="adoc" id="div_setUserData"></div>


## All &nbsp;<span class="label label-static">静态</span> <span class="label label-single">单线程</span> <span class="label label-sync">同步</span> 

  获取当前类的所有对象.
  
* **函数参数**  无

* **返回值**
  Array 包含当前类的所有对象. 



<div class="adoc" id="div_All"></div>


