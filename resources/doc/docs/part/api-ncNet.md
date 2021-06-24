# 网络
  net为全局对象，页面通过include('net')加载使用; 
   
  <link rel="stylesheet" type="text/css" href="docs/css/common.css" />
  <script src="docs/js/string.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/template.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/net.js" type="text/javascript" charset="utf-8"></script>
  
## 接口说明
*    函数接口:

<table id="method" class="table" >
</table>
  
## 下载文件

```html
// 下载文件，返回一个Downloader对象
var downloader = net.download({url: "https://dldir1.qq.com/qqfile/qq/TIM1.2.0/21645/TIM1.2.0.exe"});
console.dir(downloader);
```

<div class="row">
	 <div class="col-xs-3">
  	<button class="btn btn-outline-primary btn-block" id="downloader">下载文件</button>
	</div> 
	<div class="col-xs-3">
	  <button class="btn btn-outline-primary btn-block" id="requests">加载文件</button>
	</div> 
</div>

 
 
 
 <script type="text/html" id="downloadInfo">
  <div class="row">
    <div class="col-xs-3">
        <label>文件名：</label>
    </div>
    <div class="col-xs-9">
        <label>{fullPath}</label>
    </div>
    <div class="col-xs-3">
        <label>文件原始地址：</label>
    </div>
    <div class="col-xs-9">
        <label>{originalUrl}</label>
    </div>

    <div class="col-xs-3">
        <label>文件地址：</label>
    </div>
    <div class="col-xs-9">
        <label>{url}</label>
    </div>

    <div class="col-xs-3">
        <label>开始时间：</label>
    </div>
    <div class="col-xs-9">
        <label>{startTime}</label>
    </div>

    <div class="col-xs-3">
        <label>当前速度：</label>
    </div>
    <div class="col-xs-9">
        <label>{currentSpeed}</label>
    </div>

    <div class="col-xs-3">
        <label>当前进度：</label>
    </div>
    <div class="col-xs-9">
        <label>{percentComplete}</label>
    </div>

    <div class="col-xs-3">
        <label>已下载：</label>
    </div>
    <div class="col-xs-9">
        <label>{receivedBytes}</label>
    </div>
    <div class="col-xs-3">
        <label>总大小：</label>
    </div>
    <div class="col-xs-9">
        <label>{totalBytes}</label>
    </div>
  </div>
</script>