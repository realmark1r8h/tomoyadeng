# action

  内置事件.
  
## execute <span class="label label-static">静态</span> 

  执行一个内置动作，可以支持.
  
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
	<td>动作.</td>
</tr>
	</tbody>
</table>

* **返回值**
   无. 

* **示例**

```html
include('action');
// 最小化当前窗口
action.execute('minimize');
// 最大化当前窗口
action.execute('maximize');

```
