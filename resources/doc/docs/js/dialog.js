(function() {
	methodArr = [];
	settingsArr = [];
	initApi('SS', 'runFileDialog', 'Array', '文件对话框操作', 'options, Object, 对话框参数', 'callback, Function, 结果回调函数');
	initApi('SS', 'alert', '', '代替原生alert');
	initApi('SS', 'confirm', '', '代替原生confirm');
	initApi('SS', 'prompt', '', '代替原生prompt');

	initSettings('FILE_DIALOG_OPEN', 'Integer', '单文件选择');
	initSettings('FILE_DIALOG_OPEN_MULTIPLE', 'Integer', '多文件选择');
	initSettings('FILE_DIALOG_OPEN_FOLDER', 'Integer', '文件夹选择');
	initSettings('FILE_DIALOG_SAVE', 'Integer', '文件保存对话框');
	initSettings('FILE_DIALOG_TYPE_MASK', 'Integer', ' General mask defining the bits used for the type values');
	initSettings('FILE_DIALOG_OVERWRITEPROMPT_FLAG', 'Integer', 'Prompt to overwrite if the user selects an existing file with the Save dialog');
	initSettings('FILE_DIALOG_HIDEREADONLY_FLAG', 'Integer', 'Do not display read-only files');

	$(function() {
		createApiTable($('#method'), methodArr);
		createSettingsTable($('#settings'), settingsArr);
		include('dialog');

		console.dir(dialog);

		$('#alert').on('click', function() {
			var val = dialog.alert('322中在有我有有');
			console.dir(val);
		});
		$('#confirm').on('click', function() {
			var val = dialog.confirm('322中在有我有有??????');
			console.dir(val);
		});
		$('#prompt').on('click', function() {
			var val = dialog.prompt('322中在有我有有', 'd g 在工在在在');
			console.dir(val);
		});
		$('#dialogOpen').on('click', function() {
			dialog.runFileDialog({
				title: 'baidu.com',
				model: dialog.FILE_DIALOG_OPEN,
				defaultFilePath: '',
				acceptFilters: ['image/*'],
				selectedAcceptFilter: 0
			}, function(arr) {
				console.dir(arr);
			});
		});
		
		$('#dialogOpenMultiple').on('click', function() {
			dialog.runFileDialog({
				title: 'baidu.com',
				model: dialog.FILE_DIALOG_OPEN_MULTIPLE,
				defaultFilePath: '',
				acceptFilters: ['image/*'],
				selectedAcceptFilter: 0
			}, function(arr) {
				console.dir(arr);
			});
		});
		
		$('#dialogOpenFolder').on('click', function() {
			dialog.runFileDialog({
				title: 'baidu.com',
				model: dialog.FILE_DIALOG_OPEN_FOLDER,
				defaultFilePath: '',
				acceptFilters: ['image/*'],
				selectedAcceptFilter: 0
			}, function(arr) {
				console.dir(arr);
			});
		});
		
		$('#dialogSave').on('click', function() {
			dialog.runFileDialog({
				title: 'baidu.com',
				model: dialog.FILE_DIALOG_SAVE,
				defaultFilePath: '',
				acceptFilters: ['image/*'],
				selectedAcceptFilter: 0
			}, function(arr) {
				console.dir(arr);
			});
		});
		 
	})
})();