var arduinoSerialPort = '/dev/tty.SLAB_USBtoUART';

var serialport = require('serialport');
var serialPort = new serialport.SerialPort(arduinoSerialPort,
{        parser: serialport.parsers.readline('\n')
});




var http    =   require('http');
var fs      =   require('fs');

var app = http.createServer(function (req, res) {
	fs.readFile('./app.html', 'utf-8', function(error, content) {
		res.writeHead(200, {'Content-Type' : 'text/html'});
		res.end(content);
	});
});


//// SOCKET.IO ////

var io  =  require('socket.io');


io = io.listen(app); 


io.sockets.on('connection', function (socket) {

	socket.emit('connexion');
	socket.on('slide',function(data){
		
		serialPort.write('!'+data.pin+'-'+data.pos+':');
		
	});    
	
	serialPort.on('data', function (data)
		{
				try
				{
						/*socket.emit('arduino', data);*/
						/*serialPort.write("!12-100:", function(err, results) {
							console.log('err ' + err);
							console.log('results ' + results);
						  }); */
						console.log(data);
				}
				catch (ex)
				{
						console.warn(ex);
				}
		});        
});




app.listen(8080);
console.log('Arduino Server at http://localhost:8080/');