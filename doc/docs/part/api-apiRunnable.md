# Runnable

  如果一个类想要在线程中运行的话，需要继承自Runable.<br>工作线程：**UI线程** 或 **Renderer线程**.
  
* **父类** 
<a href="#api/apiObject">Object</a>&nbsp;

## attach &nbsp;
  将当前对象附加到一个线程中.
  
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
	<td>需要附加的线程</td>
</tr>
	</tbody>
</table>

* **返回值**
  Boolean true成功/false失败. 



<div class="adoc" id="div_attach"></div>


## detach &nbsp;
  将当前对象从一个线程中分离.
  
* **函数参数**  无

* **返回值**
   无. 



<div class="adoc" id="div_detach"></div>


## weakup &nbsp;<span class="label label-single">单线程</span> 

  唤醒当前对象所附加的线程.
  
* **函数参数**  无

* **返回值**
   无. 



<div class="adoc" id="div_weakup"></div>


## suspend &nbsp;
  挂起所附加线程，不能在浏览器线程（UI/Renderer）上执行.
  
* **函数参数**  无

* **返回值**
   无. 

