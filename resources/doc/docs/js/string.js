Overload = function(fn_objs){
//	"use strict";
    var is_match = function(x,y){
        if(x==y)return true;
        if(x.indexOf("*")==-1)return false;
     
        var x_arr = x.split(","),y_arr = y.split(",");
        if(x_arr.length != y_arr.length)return false;
     
        while(x_arr.length){
            var x_first =  x_arr.shift(),y_first = y_arr.shift();
            if(x_first!="*" && x_first!=y_first)return false;
        }
        return true;
    };
    var ret = function(){
        var args = arguments
        ,args_len = args.length
        ,args_types=[]
        ,args_type
        ,fn_objs = args.callee._fn_objs
        ,match_fn = function(){};
         
        for(var i=0;i<args_len;i++){
            var type = typeof args[i];
            type=="object" && (args[i].length>-1) && (type="array");
            args_types.push(type);
        }
        args_type = args_types.join(",");
        for(var k in fn_objs){
            if(is_match(k,args_type)){
                match_fn = fn_objs[k];
                break;
            }
        }
        return match_fn.apply(this,args);
    };
    ret._fn_objs = fn_objs;
    return ret;
};
 
// 字符串格式化
String.prototype.format2 = Overload({
    "array" : function(params){
        var reg = /{(\d+)}/gm;
        return this.replace(reg,function(match,name){
            return params[~~name];
        });
    }
    ,"object" : function(param){
        var reg = /{([^{}]+)}/gm;
        return this.replace(reg,function(match,name){
            return param[name];
        });
    }
});

// 
////删除左右两端的空格
//String.prototype.trim = function(){
//	 return this.replace(/(^\s*)|(\s*$)/g, "");
//}
////删除左边的空格
//String.prototype.ltrim = function(){
//	return this.replace(/(^\s*)/g,"");
//}
////删除右边的空格
//String.prototype.rtrim = function(){
//	return this.replace(/(^\s*)/g,"");
//}
//
//String.prototype.isNull = function(){
//	
//	var str = this;
//	str.trim();
//	if(str == '') return true;
//}
//
//// 合并多个空白为一个空白 
//String.prototype.resetBlank = function() { 
//var regEx = /\s+/g; 
//return this.replace(regEx, ' '); 
//}; 
// 
//// 保留数字 
//String.prototype.getNum = function() { 
//var regEx = /[^\d]/g; 
//return this.replace(regEx, ''); 
//}; 
// 
//// 保留中文 
//String.prototype.getCN = function() { 
//var regEx = /[^\u4e00-\u9fa5\uf900-\ufa2d]/g; 
//return this.replace(regEx, ''); 
//}; 
// 
//// String转化为Number 
//String.prototype.toInt = function() { 
//return isNaN(parseInt(this)) ? this.toString() : parseInt(this); 
//}; 
// 
//// 得到字节长度 
//String.prototype.getLen = function() { 
//var regEx = /^[\u4e00-\u9fa5\uf900-\ufa2d]+$/; 
//if (regEx.test(this)) { 
//  return this.length * 2; 
//} else { 
//  var oMatches = this.match(/[\x00-\xff]/g); 
//  var oLength = this.length * 2 - oMatches.length; 
//  return oLength; 
//} 
//}; 
// 
//// 获取文件全名 
//String.prototype.getFileName = function() { 
//var regEx = /^.*\/([^\/\?]*).*$/; 
//return this.replace(regEx, '$1'); 
//}; 
// 
//// 获取文件扩展名 
//String.prototype.getExtensionName = function() { 
//var regEx = /^.*\/[^\/]*(\.[^\.\?]*).*$/; 
//return this.replace(regEx, '$1'); 
//}; 
// 
////替换所有
//String.prototype.replaceAll = function(reallyDo, replaceWith, ignoreCase) { 
//if (!RegExp.prototype.isPrototypeOf(reallyDo)) { 
//  return this.replace(new RegExp(reallyDo, (ignoreCase ? "gi" : "g")), replaceWith); 
//} else { 
//  return this.replace(reallyDo, replaceWith); 
//} 
//};
