# desktop

  用于获取桌面的基本信息.<br>工作线程：**UI线程**.
  
* **父类** 
<a href="#api/apiObject">Object</a>&nbsp;

## getScreenInfo &nbsp;<span class="label label-static">静态</span> <span class="label label-sync">同步</span> 

  获取屏幕信息,包括屏幕大小和工作区域大小.
  
* **函数参数**  无

* **返回值**
  JsonObject .
	* **Int** width   桌面宽度
	* **Int** height  桌面高度
	* **JsonObject** rcWork  桌面工作区域信息
		* **Int** left  工作区域左上角坐标X
		* **Int** top  工作区域左上角坐标Y
		* **Int** right  工作区域右下角坐标X
		* **Int** bottom  工作区域右下角坐标Y
		* **Int** width  工作区域宽度
		* **Int** height  工作区域高度
 

* **示例**

```html
include('desktop');
var desktopInfo = desktop.getScreenInfo();
console.log(desktopInfo);

```
