/**
 * @author 钟汉津 <scnuzhonghanjin@gmail.com>
 */

const main = require('./build/Release/main.node');
const args = process.argv.splice(2);

exports.init = function () {
  console.log(args.map(x => main.main(x)));
};

this.init();