var http = require('http');
var url = process.argv[2];
http.get(url, function(response) {
    response.setEncoding('utf-8');
    response.on('data', function(data) {
        console.log(data);
    });
    response.on('error', function(error) {
        console.log(error);
    });
    response.on('end', function(end) {
    });
});
