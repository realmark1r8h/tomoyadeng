// API表格模板
var apiThead = `<thead>
      <tr>  
      	<th class="col-xs-1" style="width:50px;">类型</th>
        <th class="col-xs-3">函数名</th>
        <th class="col-xs-3">输入参数</th>
        <th class="col-xs-1">返回类型</th>
        <th>说明</th>
      </tr>
    </thead>
      <tbody>{0}
      </tbody>`;
var apiTr = `
      <tr>
      	<td>{type}</td>
        <td class="method">{name}({argsList})</td>
        <td>{params}</td>
        <td>{retval}</td>
        <td>{desc}</td>
      </tr>`;

var apiLi = `
    <li><span class="param">{paramName} </span> {paramType} {paramDesc}</li>`;

initApi = function() {
	var len = arguments.length;
	if(len < 4) return false;
	var item = {};
	item.type = arguments[0];
	item.name = arguments[1];
	item.argsList = '';
	item.retval = arguments[2];
	item.desc = arguments[3];
	item.params = [];
	// 解析参数
	for(var i = 4; i < arguments.length; ++i) {
		var arr = arguments[i].split(',');
		if(arr.length < 1) continue;
		if(arr.length < 2) continue;
		if(arr.length < 3) arr.push('');
		var paramItem = {};
		paramItem.paramName = arr[0];
		paramItem.paramType = arr[1];
		paramItem.paramDesc = arr[2];
		console.dir(paramItem);
		item.params.push(paramItem);
	}
	methodArr.push(item);
}

createApiTable = function($table, arr) {
	// 复制对象
	var newArr = jQuery.extend(true, [], arr);
	$table.empty();
	$table.addClass('table table-hover table-bordered table-striped');
	var trList = '';
	// 遍历数组
	for(var index = 0; index < newArr.length; ++index) {
		var item = newArr[index];
		var paramList = '';
		var argsList = ''
		for(var i = 0; i < item.params.length; ++i) {
			argsList += item.params[i].paramName;
			if(i < item.params.length - 1) {
				argsList += ', ';
			}
			paramList += apiLi.format2(item.params[i]);
		}
		item.argsList += argsList;
		item.params = paramList;
		trList += apiTr.format2(item);
	}
	var tableList = apiThead.format2([trList]);
	var trArr = [];
	trArr.push(tableList);
	$table.append(tableList);
	console.log(tableList);
}

// 配置选项模板

var settingsThead = `
    <thead>
      <tr>
        <th class="col-xs-2">名称</th>
        <th class="col-xs-1">类型</th>
        <th>说明</th>
      </tr>
    </thead>
    <tbody> {0}
    </tbody>`;

var settingsTr = `
      <tr>
        <td class="method">{name}</td>
        <td>{type}</td>
        <td>{desc}</td>
      </tr>`;

initSettingsByArr = function(arr, name, type, desc) {

	var item = {};
	item.name = name;
	item.type = type;
	item.desc = desc;
	arr.push(item);
}

initSettings = function(name, type, desc) {

	var len = arguments.length;
	if(len < 3) return false;
	return initSettingsByArr(settingsArr, name, type, desc);
}

initMenuItemSettings = function(name, type, desc) {

	var len = arguments.length;
	if(len < 3) return false;
	return initSettingsByArr(menuItemArr, name, type, desc);
}

createSettingsTable = function($table, arr) {
	// 复制对象
	var newArr = jQuery.extend(true, [], arr);
	$table.empty();
	$table.addClass('table table-hover table-bordered table-striped');
	var settingsList = '';
	// 遍历数组
	for(var index = 0; index < newArr.length; ++index) {
		var item = newArr[index];
		settingsList += settingsTr.format2(item);
	}
	var tableList = settingsThead.format2([settingsList]);
	$table.append(tableList);
	console.log(tableList);
}

// 事件模板

var eventThead = `
    <thead>
      <tr>
        <th class="col-xs-2">名称</th>
        <th class="col-xs-2">参数</th>
        <th>说明</th>
      </tr>
    </thead>
    <tbody> {0}
    </tbody>`;

var eventTr = `
      <tr>
        <td class="method">{name}</td>
        <td>{type}</td>
        <td>{desc}</td>
      </tr>`;

initEventByArr = function(arr, name, type, desc) {

	var item = {};
	item.name = name;
	item.type = type;
	item.desc = desc;
	arr.push(item);
}

initEvent = function(name, type, desc) {

	var len = arguments.length;
	if(len < 3) return false;
	return initEventByArr(eventArr, name, type, desc);
}

createEventTable = function($table, arr) {
	// 复制对象
	var newArr = jQuery.extend(true, [], arr);
	$table.empty();
	$table.addClass('table table-hover table-bordered table-striped');
	var eventList = '';
	// 遍历数组
	for(var index = 0; index < newArr.length; ++index) {
		var item = newArr[index];
		eventList += eventTr.format2(item);
	}
	var tableList = eventThead.format2([eventList]);
	$table.append(tableList);
	console.log(tableList);
}