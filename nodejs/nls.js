var fs  = require('fs');
fs.readdir(process.argv[2], function(err, list) {
    if (err) {
        return;
    }
    var ext = '.' + process.argv[3];
    for (var idx in list) {
        var item = list[idx];
        if (item && item.indexOf(ext, item.length - ext.length) !== -1) {
            console.log(item);
        }
    }
});
