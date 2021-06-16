;
(function() {

	methodArr = [];
	settingsArr = [];
	menuItemArr = [];

	initApi('CS', 'new Menu', 'Object', '创建一个菜单', 'options, Object, 菜单参数');
	initApi('MN', 'close', '', '关闭菜单');

	initSettings('lineHeight', 'Integer', '菜单项行高,默认32');
	initSettings('separatorColor', 'String', '分隔条颜色，默认"0xffe8e8e8"');
	initSettings('menu', 'Array', '所有菜单项,具体内容参考MenuItem');

	initMenuItemSettings('id', 'String', '当前菜单项ID');
	initMenuItemSettings('text', 'String', '当前菜单项显示文本');
	initMenuItemSettings('action', 'String', '当前菜单项的预定义动作，如果有效则执且不会向页面返回菜单选择事件');
	initMenuItemSettings('separator', 'Boolean', '是否显示分隔符，默认false');
	initMenuItemSettings('visible', 'Boolean', '当前菜单项是否可用，默认true');
	initMenuItemSettings('enabled', 'Boolean', '当前菜单项是否可用，默认true');
	initMenuItemSettings('shortcut', 'String', '当前菜单项快捷键，默认无快捷键');

	initMenuItemSettings('menu', 'Object', '子菜单， 参考MenuSettings');

	$(function() {
		createApiTable($('#method'), methodArr);
		createSettingsTable($('#settings'), settingsArr);
		createSettingsTable($('#menuItemSettings'), menuItemArr);
		include('Menu');
		console.dir(Menu);

		$('#createMenu').on('click', function() {
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
			menu.on('select', function(obj) {
				alert(JSON.stringify(obj));
			})

		});

		$('#multiMenu').on('click', function() {
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
		});

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
			menu.on('select', function(str) {
				alert(str);
			})
			return false;
		};

		var text = document.getElementById('text');
		text.oncontextmenu = function() {
			var menu = new Menu({
				menu: [
					{ id: '1', text: '撤消', action: 'undo', shortcut: 'U' },
					{ id: '2', text: '重做', action: 'redo', shortcut: 'R', separator: true },
					{ id: '3', text: '剪切', action: 'cut', shortcut: 'T', enabled: false },
					{ id: '4', text: '复制', action: 'copy', shortcut: 'C', visible: false },
					{ id: '5', text: '粘贴', action: 'paste', shortcut: 'P', visible: false },
					{ id: '6', text: '删除', action: 'delete', shortcut: 'D', separator: true },
					{ id: '7', text: '全选', action: 'selectAll', shortcut: 'A', separator: true },
					{ id: '8', text: '放大', action: 'zoomOut', shortcut: 'Z' },
					{ id: '9', text: '缩小', action: 'zoomIn', shortcut: 'X' },
					{ id: '10', text: '重置', action: 'resetZoom', separator: true },
					{ id: '11', text: '打印', action: 'print' },
				]
			});
			menu.on('select', function(str) {
				alert(str);
			})
			return false;
		}

		$('#listenMenu').on('click', function() {
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
			menu.on('select', function(obj) {
				alert(JSON.stringify(obj));
			});
			menu.on('close', function(){
			    alert('菜单已关闭');
			});
			 
		});
		
		$('#closeMenu').on('click', function() {
            var menu2 = new Menu({
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
            menu2.close();
            
            window.setTimeout(function(){ 
                
            }, 1000);

        });
	});
})();