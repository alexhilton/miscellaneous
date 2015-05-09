var http = require('http');

function jug(url, callback) {
    http.get(url, function(resposne) {
        var stuff = '';
        resposne.setEncoding('utf-8');
        resposne.on('data', function(data) {
            stuff += data;
        });
        resposne.on('end', function(data) {
            callback(url, stuff);
        });
    });
}
var bundle = {};
var collect = function(url, data) {
    bundle[url] = data;
};
for (var i = 2; i < process.argv.length; i++) {
    jug(process.argv[i], collect);
}

var len = function(obj) {
    var size = 0;
    for (var key in obj) {
        if (obj.hasOwnProperty(key)) {
            size++;
        }
    }
    return size;
};
var check = function() {
    if (len(bundle) == process.argv.length - 2) {
        for (var i = 2; i < process.argv.length; i++) {
            console.log(bundle[process.argv[i]]);
        }
    } else {
        setTimeout(check, 100);
    }
};

setTimeout(check, 100);
