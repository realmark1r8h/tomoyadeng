(function(){
	$(function(){
		window.console.assert = function(condition, outstr){
			if(!condition){
				if(window.assertArr && window.assertArr.length >0){
					var str = window.assertArr.shift();
					str = str.replace('console.assert', '');
					str= str.replace(';', '');
					console.error('失败:[ ' + str +  ' ]');
					
				}
				else{
					console.error('失败:[ ]');
				}
				
			}else{
				if(window.assertArr && window.assertArr.length >0){
					var str = window.assertArr.shift();
					str = str.replace('console.assert', '');
					str= str.replace(';', '');
					console.info('通过:[ ' + str +  ' ]'); 
				}
				else{
					console.info('通过:[ ]');
				}
				 
			}
		}
	});
})();
