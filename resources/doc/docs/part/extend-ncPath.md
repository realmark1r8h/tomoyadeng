# Path
  Path为全局对象，页面通过include('Path')加载使用;

  <link rel="stylesheet" type="text/css" href="docs/css/common.css" />
  <script src="docs/js/string.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/template.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/extend/Path.js" type="text/javascript" charset="utf-8"></script>
## 接口说明
*    函数接口:

<table id="method" class="table" >
</table>
 
## 打开数据库
```html
// 打开数据库
db = new Sqlite('E:/amoylel/test.db');
```
<div class="row">
    <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="open">打开数据库</button>
    </div>
</div>

## 执行SQL

```html
// 插入数据
var str = new Date().toString();
var val = db.execute(`insert into abc (a, b, c) values('{0}', {1}, {2});`, [str, 1, 33.22]);
if(val == 1) {
		alert('插入成功');
}
// 删除数据
var val = db.execute(`DELETE FROM abc where b='{0}'`,[1]);
alert('删除' + val + '条数据');
// 更新数据
var val = db.execute(`UPDATE abc SET a='{0}' where b = {1}`, [new Date().toString(), 2]);
alert('更新' + val + '条数据');
```

<div class="row">
    <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="insert">插入数据</button>
    </div>
    <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="remove">删除数据</button>
    </div>
     <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="update">更新数据</button>
    </div>
</div>

## 查询数据

```html
// 查询数据
var val = db.query('select * from abc where b={0}', [1], {rows:2, page:1});
console.dir(val);
```

<div class="row">
    <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="query">查询数据</button>
    </div>
</div>
 


## 备份数据库
 
 ```html
// 备份数据库
var val = db.backup('test2.db'); 
```

<div class="row">
    <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="backup">备份数据库</button>
    </div>
</div>