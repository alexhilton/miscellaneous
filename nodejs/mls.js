var fs  = require('fs');
module.exports = function(path, ext, callback) {
    fs.readdir(path, function(err, list) {
        if (err) {
            callback(err);
            return;
        }
        var results = [];
        ext = '.' + ext;
        for (var idx in list) {
            var item = list[idx];
            if (item && item.indexOf(ext, item.length - ext.length) !== -1) {
                results.push(item);
            }
        }
        callback(err, results);
    });
};
