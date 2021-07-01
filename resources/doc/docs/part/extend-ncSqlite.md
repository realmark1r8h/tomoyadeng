# Sqlite
  Sqlite为全局对象，页面通过include('Sqlite')加载使用;

  <link rel="stylesheet" type="text/css" href="docs/css/common.css" />
  <script src="docs/js/string.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/template.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/sqlite.js" type="text/javascript" charset="utf-8"></script>
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

## 插入数据

```html
// 插入数据
var str = new Date().toString();
var val = db.insert('insert into abc (a, b, c) values(\"' + str + '\", 1, 33.22);');
if(val == 1) {
		alert('插入成功');
}
```

<div class="row">
    <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="insert">插入数据</button>
    </div>
</div>

## 查询数据

```html
// 查询数据
var val = db.select('select * from abc');
console.dir(val);
```

<div class="row">
    <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="select">查询数据</button>
    </div>
</div>

## 删除数据

```html
// 查询数据
var val = db.select('select * from abc');
console.dir(val);
```

<div class="row">
    <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="select">查询数据</button>
    </div>
</div>

## 更新数据

```html
// 查询数据
var val = db.select('select * from abc');
console.dir(val);
```

<div class="row">
    <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="select">查询数据</button>
    </div>
</div>


## 关闭数据库
 
 