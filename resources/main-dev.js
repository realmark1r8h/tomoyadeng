'use strict';


// 重定向stdout, 不行
//const fs = require('fs');
//const process = require('process');
//var access = fs.createWriteStream('e:/api.access.log');
//process.stdout.write = process.stderr.write = access.write.bind(access);
//process.on('uncaughtException', function(err) {
//console.error((err && err.stack) ? err.stack : err);
//});

var console = {};
console.log = function(){}
console.info = function(){}
console.warn = function(){}
console.error = function(){}
console.dir = function(){}
console.time = function(){}
console.timeEnd = function(){}
console.trace = function(){}
console.assert = function(){}
   

//require('node-monkey').start();
//const xnode = require('E:/amoylel-Out/Binary.UD32/x_node');     
//const xnode = require('./build/Release/x_node');
//const xnode1 = require('E:/amoylel-Out/Binary.UD32/addons/hello-world/build/Release/binding');
//const xnode = require('E:/amoylel/Native/x-node/build/Release/x_node');
const xnode = require(process.cwd() + '/ncui');

app.addUrlMapping('http://127.0.0.1:8020/', 'doc/'); 
 tray.show(true);
 
console.log('rcef');

function fooo() {
    var sb = JSON.stringify(cc);
    return sb;
}

console.log(shell.SW_HIDE);
console.log(shell.SW_RESTORE);
//shell.open("www.baidu.com");
 
 
const win = new BrowserWindow({
    show:true,
    hasShadow: true,
    titleBar: false,
    offscreen: false,
    transparent: false,
    width: 1280,
    height: 720,
    roundcorner: 5,
    sizebox: "4,4,6,6",
//  url: "http://127.0.0.1:8020/amoylel/web/index.html" ,
//   url:"http://127.0.0.1:8020/amoylel/doc/index.html?debug=1"
 url:"http://127.0.0.1:8020/index.html?debug=1"
});

win.on('maximize', function() {
    tray.blink(true);
    console.log(333); 
});
win.on('OnAfterCreated', function(browser) {
    //  tray.blink(true);
    var bc = browser.CanGoBack();
});

tray.on('rbuttondown', function() {
    console.log('rbuttondown');
    
    var menu = new Menu({
        lineHeight: 32,
        roundcorner: 0,
        menu: [
            { id: '1', text: '全屏', action: 'fullscreen', separator: true },
            { id: '2', text: '退出全屏', action: 'nonFullscreen' },
            { id: '3', text: '全选', action: 'selectAll' },
            { id: '3', text: '重新加载', action: 'forceReload' },
            { id: '4', text: '调试', action: 'showDevtools' },
            { id: '5', text: '退出程序', action: 'quit' }
        ]
    });
    menu.on('close', function(){
//      dialog.alert(333);
    });
    menu.on('click', function(){
//      dialog.alert(0904);
    });
    menu.prop2;
    tray.blink(!tray.isBlink());
    console.log(1);
    //  console.log(menu);
    console.log(2);
});

//console.log(33);
//tray.blink(true);
//globalShortcut.on('hotkeydown', function(id, str){
////          alert(id +', ' + str);  
//      });
//       globalShortcut.registerShortcut('MOD_CONTROL+MOD_ALT+O');
//      $('#registerShortcut').on('click', function() {
//         
//      });
//
//      $('#unregisterShortcut').on('click', function() {
//         globalShortcut.unregisterShortcut('MOD_CONTROL+MOD_ALT+O');
//      });
//shell.open('http://www.baidu.com');
//win.maximize();

var urlRequest = new URLRequest();
urlRequest.on('RequestComplete', function() {
    //              shell.open('http://www.baidu.com');
})

win.on('OnLoadEnd', function() {
    win.send('abcd', 66);
    
})


// ipc
ipc.on('message', function() {
    tray.blink(!tray.isBlink());
    return 3;
})


// system
console.dir(system.screen);
console.dir(system.mouse);

//mouse.moveTo(100, 100);