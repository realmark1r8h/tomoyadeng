# md5

  MD5加密类.<br>工作线程**Renderer线程**
  
## encode &nbsp;<span class="label label-static">静态</span> <span class="label label-sync">同步</span> 

  MD5 加密.
  
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
	<td>需要加密的字符串.</td>
</tr>
	</tbody>
</table>

* **返回值**
  String 加密后的字符串. 

* **示例&nbsp;&nbsp;&nbsp;&nbsp;**

```html
include('md5');
var str  = md5.encode('NCUI');
console.log(str);

```


<div class="adoc" id="div_encode"></div>


