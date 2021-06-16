# 快速开始

  <link rel="stylesheet" type="text/css" href="docs/css/common.css" />
  <script src="docs/js/string.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/template.js" type="text/javascript" charset="utf-8"></script>
  <script src="docs/js/start.js" type="text/javascript" charset="utf-8"></script>
 
  
## 配置文件

编辑manifest.json设置程序的启动方式。 manifest不是必须的，如果不存在，那么程序将使用默认配置，如果存在，那么mainfest.json所在目录必须与程序所在目录相同。
 
manifest支持AppSettings和BrowserWindowSettings两个类 ，详细情况可参照app和BrowserWindow两个模块。

如果不使用NodeJs,那么需要指定一个URL作为程序启动时的URL。
  
```html
// 一个简单的配置文件, 设置程序启时要打开的URL
{
	"browserWindowSettings":{
		"titleBar": true,
		"url": "http://www.oschina.net" 
	}
}
```


## 创建窗口

```html

```