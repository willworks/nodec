/**
 * @author 钟汉津 <scnuzhonghanjin@gmail.com>
 */

const main = require('./build/Release/main.node');
const args = process.argv.splice(2);

exports.init = function () {
  // 基本数据类型
  console.log(args.map(x => main.var(x)));
  // 数组传递
  console.log(main.arr([111,222,333]));
  // 对象传递
  console.log(main.obj({key:1,key_a:2,c:"sdf",test:[1,2,3]}));
  // 方法传递
  const fn = main.func(fn_param);
  console.log(fn);
}

function fn_param(){
  console.log("call fn fn_param by sync!");
}

this.init();