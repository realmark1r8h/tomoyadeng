# 菜单
  Menu为类，页面通过include('Menu')加载使用;  Node自己包含
  <link rel="stylesheet" type="text/css" href="docs/css/common.css" />
  <script src="docs/js/string.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/template.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/menu.js" type="text/javascript" charset="utf-8"></script>
  
## 接口说明
<ul><li class="param">函数接口:</li></ul>

<table id="method" class="table" >
</table>
 
<ul><li class="param">new Menu(options) MenuSettings 参数说明:</li></ul>

<table id="settings" class="table">
</table>
  
<ul><li class="param">MenuItem 参数说明:</li></ul>

<table id="menuItemSettings" class="table">
</table>

## 创建菜单


```html
include('Menu');
//创建一级菜单
var menu = new Menu({
                hasShadow: true,
                transparent: false,
                lineHeight: 32,
                backgroundColor: 0xFFFFFFFF,
                roundcorner: 3,
                menu: [
                    { id: '1', text: '中文', 'separator': true },
                    { id: '2', text: '英文' },
                    { id: '3', text: '法文' },
                    { id: '4', text: '德文' }
                ]
            });
// 创建多级菜单            
var menu = new Menu({
                transparent: false,
                separatorColor: '0xffff0000',
                menu: [{
                        id: '1',
                        text: '111',
                        'separator': true,
                        menu: [
                            { id: '1', text: '中就让这首歌', 'separator': true },
                            { id: '2', text: '222' },
                            { id: '3', text: '333', shortcut: 'd' },
                            {
                                id: '4',
                                text: '444',
                                menu: [
                                    { id: '1', text: '111', 'separator': true },
                                    { id: '2', text: '222' },
                                    { id: '3', text: '333' }
                                ]
                            }
                        ]
                    },
                    {
                        id: '2',
                        text: '222',
                        menu: [
                            { id: '1', text: '111' },
                            { id: '2', text: '222' },
                            { id: '3', text: '333' },
                            { id: '4', text: '444' }
                        ]
                    },
                    { id: '3', text: '333' },
                    { id: '4', text: '444' }
                ]
            });
            menu.on('select', function(obj) {
                alert(JSON.stringify(obj));
            })
// 创建右键菜单
var rightMenu = document.getElementById('rightMenu');
    rightMenu.oncontextmenu = function() {
        var menu = new Menu({
            menu: [
                { id: '1', text: '111' },
                { id: '2', text: '222' },
                { id: '3', text: '333' },
                {
                    id: '4',
                    text: '444',
                    menu: [
                        { id: '1', text: '111' },
                        { id: '2', text: '222' },
                        { id: '3', text: '333' },
                        { id: '4', text: '444' }
                    ]
                }
            ]
        });
        menu.on('click', function(str) {
            alert(str);
        })
        return false;
    }      
```
<div class="row">
     <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="createMenu">创建菜单</button>
    </div>
    <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="multiMenu">多级菜单</button>
    </div>
    <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="rightMenu">右键菜单</button>
    </div>
</div>
  
 
## 菜单项设置


  
```html
 var menu = new Menu({
        menu: [
            { id: '1', text: '撤消', action: 'undo', shortcut: 'U' },
            { id: '2', text: '重做', action: 'redo', shortcut: 'R', separator: true },
            { id: '3', text: '剪切', action: 'cut', shortcut: 'T', enabled: false },
            { id: '4', text: '复制', action: 'copy', shortcut: 'C', visible: false },
            { id: '5', text: '粘贴', action: 'paste', shortcut: 'P', visible: false },
            { id: '6', text: '删除', action: 'delete', shortcut: 'D', separator: true },
            { id: '7', text: '全选', action: 'selectAll', shortcut: 'A', separator: true },
            { id: '8', text: '放大', action: 'zoomOut', shortcut: 'Z' } ,
            { id: '9', text: '缩小', action: 'zoomIn' , shortcut: 'X'},
            { id: '10', text: '重置', action: 'resetZoom',  separator: true },
            { id: '11', text: '打印', action: 'print' },
        ]
   });
```

 <div id="text" class="example code" contenteditable="true">
  <h1 class="code">右键点我</h1>
</div>
  
## 事件监听
```html
include('app');
var menu = new Menu({
        menu: [
            { id: '1', text: '中文', 'separator': true },
            { id: '2', text: '英文' },
            { id: '3', text: '法文' },
            { id: '4', text: '德文' }
        ]
    });
menu.on('select', function(event){
    alert(JSON.stringify(event));
});
menu.on('close', function(){
    alert('菜单已关闭');
});
```
 
 <div class="row">
     <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="listenMenu">事件监听</button>
    </div>
    
</div>


## 关闭菜单
菜单被选中或菜单失去焦点后会自动关闭，你也可以手动关闭菜单

```html
include('Menu');
// 创建一个菜单
var menu = new Menu();
// 关闭菜单
menu.close();
```
  
 <div class="row">
     <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="closeMenu">关闭菜单</button>
    </div>
</div>