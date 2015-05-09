var fs = require('fs');
var stuff = fs.readFileSync(process.argv[2]).toString();
var lines = stuff.split('\n');
console.log(lines.length - 1);
