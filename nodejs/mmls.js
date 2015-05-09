var ls = require('./mls');

ls(process.argv[2], process.argv[3], function(err, items) {
    if (!err && items && items.length > 0) {
        items.forEach(function(item) {
            console.log(item);
        });
    }
});
