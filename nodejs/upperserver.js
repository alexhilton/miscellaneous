var http = require('http');
var server = http.createServer(function (req, res) {
    if (req.method === 'POST') {
        req.setEncoding('utf-8');
        req.on('data', function (data) {
            res.write(data.toUpperCase());
        });
        req.on('end', function(end) {
            res.end();
        });
    }
});
server.listen(process.argv[2]);
