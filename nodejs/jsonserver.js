var http = require('http');
var url = require('url');
var server = http.createServer(function (req, res) {
    if (req.method !== 'GET') {
        res.write('Send me an GET\n');
        res.end();
        return;
    }
    //console.log(req.url);
    var theUrl = url.parse(req.url, true);

    if (!theUrl.pathname) {
        res.write('404 Not Found.\n');
        res.end();
        return;
    }
    if (theUrl.pathname === '/api/unixtime') {
        var ump = theUrl.query['iso'];
        res.writeHead(200, {'Content-Type': 'application/json'});
        res.write(JSON.stringify({unixtime: new Date(ump.toLocaleString()).getTime()}));
        res.end();
    } else if (theUrl.pathname === '/api/parsetime') {
        var uum = theUrl.query['iso'];
        var d = new Date(uum.toLocaleString());
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
