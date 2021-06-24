# 下载
Downloader为全局对象，页面通过include('Downloader')加载使用;
  
文件下载类
  
  <link rel="stylesheet" type="text/css" href="docs/css/common.css" />
  <script src="docs/js/string.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/template.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/downloader.js" type="text/javascript" charset="utf-8"></script>
  
## 接口说明
*    函数接口:

<table id="method" class="table" >
</table>
 
 
*    new Downloader(options)参数:

<table id="settings" class="table">
</table>
  
*    可监听的事件:

<table id="event" class="table">
</table>

## 下载文件

```html
// 创建下载对象
var downloader = new Downloader({
    url: "https://dldir1.qq.com/qqfile/qq/TIM1.2.0/21645/TIM1.2.0.exe",
//  file:'d:/TIM1.2.0.exe'
});
downloader.on('start', function(obj) {
    console.dir(obj);
});
downloader.on('update', function(obj) {
    var html = $('#downloadInfo').html();
    html = html.format(obj);
    $('.info').empty().append(html);
});
downloader.on('complete', function(obj) {
    alert('下载完成');
});
downloader.on('canceled', function(obj) {
    alert('下载取消');
})
```

<div class="row">
    <div class="col-xs-3">
        <button class="btn btn-outline-primary btn-block"  id="autoDownload">自动下载</button>
    </div>
    <div class="col-xs-3">
        <button class="btn btn-outline-primary btn-block"  id="download2">手动下载</button>
    </div>
    <div class="col-xs-3">
        <button class="btn btn-outline-primary btn-block"  id="start">开始下载</button>
    </div>
    <div class="col-xs-3">
        <button class="btn btn-outline-primary btn-block"  id="pause">暂停下载</button>
    </div>
    <div class="col-xs-3">
        <button class="btn btn-outline-primary btn-block"  id="resume">恢复下载</button>
    </div>
    <div class="col-xs-3">
        <button class="btn btn-outline-primary btn-block"  id="cancel">取消下载</button>
    </div>
</div>
<div class="info" style="margin-top: 10px;"></div>

 
 
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