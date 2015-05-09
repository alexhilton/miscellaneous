var net = require('net');
var server = net.createServer(function (socket) {
    //  "2013-07-06 17:42"
    var today = new Date();
    var res = today.getFullYear() + '-' + padding(today.getMonth() + 1) + '-' + padding(today.getDate()) +
                ' ' + padding(today.getHours()) + ':' + padding(today.getMinutes());
    socket.write(res);
    socket.end('\n');
});
server.listen(process.argv[2]);

function padding(num) {
    if (num < 10) {
        return '0' + num;
    }
    return num;
}
