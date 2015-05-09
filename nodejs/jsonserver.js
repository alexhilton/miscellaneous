var http = require('http');
var server = http.createServer(function (req, res) {
    if (req.method !== 'GET') {
        res.write('Send me an GET\n');
        res.end();
        return;
    }
    //console.log(req.url);
    var pathp = /^(https?:\/\/)?[a-zA-Z0-9\-.:]+(\/.+)$/;
    var um = pathp.exec(req.url);
    var path = um && um[2];
    if (!path && req.url[0] === '/') {
        path = req.url;
    }
    if (!path) {
        res.write('404 Not Found.\n');
        res.end();
        return;
    }
    var pqp = /^(.+)\?(.+)$/.exec(path);
    path = pqp[1];
    var query = pqp[2];
    //console.log(path);
    //console.log(query);
    if (path === '/api/unixtime') {
        var ump = /^iso=(.+)$/.exec(query);
        res.writeHead(200, {'Content-Type': 'application/json'});
        res.write(JSON.stringify({unixtime: new Date(ump[1].toLocaleString()).getTime()}));
        res.end();
    } else if (path === '/api/parsetime') {
        var uum = /^iso=(.+)$/.exec(query);
        var d = new Date(uum[1].toLocaleString());
        res.writeHead(200, {'Content-Type': 'application/json'});
        res.write(JSON.stringify({
            hour: d.getHours(),
            minute: d.getMinutes(),
            second: d.getSeconds()
        }));
        res.end();
    } else {
        res.write('400 Bad Request\n');
        res.end();
    }
});
server.listen(process.argv[2]);
