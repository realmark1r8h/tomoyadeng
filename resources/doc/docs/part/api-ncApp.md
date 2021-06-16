# app模块
  app为全局对象，页面通过include('app')加载使用;  Node自己包含
  <link rel="stylesheet" type="text/css" href="docs/css/common.css" />
  <script src="docs/js/string.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/template.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/app.js" type="text/javascript" charset="utf-8"></script>
  
## 接口说明
<ul><li class="param">函数接口:</li></ul>

<table id="method" class="table" >
    <thead>
      <tr>
        <th class="col-xs-3">函数名</th>
        <th class="col-xs-4">输入参数</th>
        <th class="col-xs-1">返回类型</th>
        <th>说明</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td class="method">getConfig([key])</td>
        <td>
          <li><span class="param">[key] </span> String(可选) 配置项</li>
        </td>
        <td>Object</td>
        <td>获取程序配置信息</td>
      </tr>
      <tr>
        <td class="method">setConfig(options)</td>
        <td>
          <li><span class="param">options </span> Object 需要更新的键值</li>
        </td>
        <td></td>
        <td>更新程序配置信息</td>
      </tr>
      <tr>
        <td class="method">toAbsolutePath(path)</td>
        <td>
          <li><span class="param">path </span> String 路径</li>
        </td>
        <td>String</td>
        <td>获取程序配置信息</td>
      </tr>
      <tr>
        <td class="method">addUrlMapping(url, path)</td>
        <td>
          <li><span class="param">url </span> String 网络路径</li>
          <li><span class="param">path </span> String 本地路径</li>
        </td>
        <td>Boolean</td>
        <td>将一个网络路径映射为本地路径，URL必须是一个完整的绝对路径(以网络协议开头， 如：http://、file:///)， 本地路径可以是一个目录，也可以是一个文件</td>
      </tr>
      <tr>
        <td class="method">removeUrlMapping(url)</td>
        <td>
          <li><span class="param">url </span> String 网络路径</li>
        </td>
        <td>Boolean</td>
        <td>取消URL的本地路径映射</td>
      </tr>
      <tr>
        <td class="method">urlToNativeFile(url, [needExist])</td>
        <td>
          <li><span class="param">url </span> String 网络路径</li>
          <li><span class="param">[needExist] </span> Boolean 是否要求文件存在</li>
        </td>
        <td></td>
        <td>将URL转换为本地路径</td>
      </tr>
      <tr>
        <td class="method">quit()</td>
        <td></td>
        <td></td>
        <td>正常退出程序，页面可以阻止程序退出</td>
      </tr>
      <tr>
        <td class="method">exit()</td>
        <td></td>
        <td></td>
        <td>强制退出程序</td>
      </tr>
    </tbody>
</table>
 
 
<ul><li class="param">setConfig 参数说明:</li></ul>

<table id="settings" class="table">
    <thead>
      <tr>
        <th class="col-xs-2">名称</th>
        <th class="col-xs-1">类型</th>
        <th>说明</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td class="method">single_process</td>
        <td>Boolean</td>
        <td>是否在单进程中使用CEF, 默认true</td>
      </tr>
      <tr>
        <td class="method">locale</td>
        <td>String</td>
        <td>CEF语言环境, 默认中文"zh-CN"</td>
      </tr>
      <tr>
        <td class="method">useNode</td>
        <td>Boolean</td>
        <td>是否使用NodeJS, 默认false</td>
      </tr>
      <tr>
        <td class="method">useNodeProcess</td>
        <td>Boolean</td>
        <td>是否在单独的进程中使用NodeJS, 默认false</td>
      </tr>
      <tr>
        <td class="method">debugNode</td>
        <td>Boolean</td>
        <td>是否允许调试NodeJs, 默认false, 如果需要调试NodeJs需要在控制台模式下进行</td>
      </tr>
      <tr>
        <td class="method">appPath</td>
        <td>String</td>
        <td>程序所在磁盘的完整路径</td>
      </tr>
      <tr>
        <td class="method">appDir</td>
        <td>String</td>
        <td>程序所在磁盘目录</td>
      </tr>
      <tr>
        <td class="method">appName</td>
        <td>String</td>
        <td>程序名称</td>
      </tr>
      <tr>
        <td class="method">skinDir</td>
        <td>String</td>
        <td>资源文件所在目录,默认%appDir%skin</td>
      </tr>
      <tr>
        <td class="method">workDir</td>
        <td>String</td>
        <td>程序工作目录，默认%appDir%</td>
      </tr>
      <tr>
        <td class="method">webDir</td>
        <td>String</td>
        <td>Web代码所在目录，默认%appDir%web</td>
      </tr>
      <tr>
        <td class="method">homeDir</td>
        <td>String</td>
        <td>用户数据根目录，默认%appDataDir%appName</td>
      </tr>
      <tr>
        <td class="method">downloadsDir</td>
        <td>String</td>
        <td>文件下载目录，默认%homeDir%downloads</td>
      </tr>
      <tr>
        <td class="method">musicsDir</td>
        <td>String</td>
        <td>音乐目录，默认%homeDir%musics</td>
      </tr>
      <tr>
        <td class="method">picturesDir</td>
        <td>String</td>
        <td>图片目录，默认%homeDir%pictures</td>
      </tr>
      <tr>
        <td class="method">videosDir</td>
        <td>String</td>
        <td>视频目录，默认%homeDir%videos</td>
      </tr>
      <tr>
        <td class="method">dragClassName</td>
        <td>String</td>
        <td>允许拖拽移动窗口的元素类名，默认"drag"。（&lt;div class="drag"&gt;&lt;/div&gt;,如果鼠标在当前元素或其子元素上，按下左键可以移动整个窗口）</td>
      </tr>
      <tr>
        <td class="method">noDragClassName</td>
        <td>String</td>
        <td>不允许拖拽移动窗口的元素类名，默认"no-drag"</td>
      </tr>
    </tbody>
</table>
  
## 获取配置信息


```html
include('app');
//获取所有配置信息
var config = app.getConfig();  
// 获取单项配置信息
var appDir = app.getConfig('appDir'); 
```
<div class="row">
     <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="getConfig">获取全部</button>
    </div>
    <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="getOne">单项获取</button>
    </div>
</div>

## 设置配置信息


  
```html
include('app');
// 设置一项
app.setConfig({skin:'%appDir%res'}); 

// 同时设置多项
app.setConfig({
    skin:'%appDir%res',
    web:'%appDir%webDir'
}); 
```
 
 <div class="row">
     <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="setConfig">设置</button>
    </div>
    
</div>


## 获取绝对路径
```html
include('app');
 
app.toAbsolutePath('%appDir%download'); 
```
 
 
 <div class="row">
     <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="toAbsolutePath">路径转换</button>
    </div>
    
</div>


## URL映射
将http file 等其他协议映射为本地文件

```html
include('app');
 
 // 添加一个URL映射, http://aaa/  (/cccc/d,
app.addUrlMapping('http://wwww.baidu.com', '%webDir%baidu'); 
// 重置添加会覆盖之间的路径
app.addUrlMapping('http://wwww.baidu.com', '%webDir%'); 
// 移除URL映射
app.removeUrlMapping('http://wwww.baidu.com');
// 将一个URL转投为本地文件路径
var path = app.urlToNativePath('http://wwww.baidu.com/test.html');
var path2 = app.urlToNativePath('http://wwww.baidu.com');

```
 
 
 <div class="row">
     <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="addUrlMapping">添加映射</button>
    </div>
    <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="removeUrlMapping">移除映射</button>
    </div>
    <div class="col-xs-3">
        <a class ="btn btn-outline-primary btn-block" href="http://wwww.baidu.com/test.html" target="blank">查看效果</a>
    </div>
    <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="urlToNativePath">URL转换</button>
    </div>
</div>


 ## 退出程序
 
```html
// 正常退出程序
app.quit();
// 强制退出程序
app.exit();
```
 
 <div class="row">
     <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="quit">正常退出</button>
    </div>
    <div class="col-xs-3">
        <button class ="btn btn-outline-primary btn-block" id="exit">强制退出</button>
    </div>
</div>