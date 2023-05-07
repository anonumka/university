const app = require('express')();
const client = require('socket.io-client');
const server = require('http').createServer(app);
const io = require('socket.io')(server);

var text_output = '';

app.use(require("express").static(__dirname+ '/'));
app.get('/', function (request, response) 
{
	response.sendFile(__dirname + '/public/index.html');
});

io.on('connection', function (client) { 
	console.log("User was connected " + client.id);
	io.to(client.id).emit('load', { cur_text: text_output });
	client.on('clear', function()
	{
		text_output = '';
		client.broadcast.emit('clear', { cur_text: text_output });
	});
	client.on('text_edit', function(data)
	{
		console.log('text = ' + data.cur_text);
		text_output = data.cur_text;
		client.broadcast.emit('text_edit', { cur_text: text_output });
	});
});

server.listen(3000);
console.log("Сервер запущен по адресу http://127.0.0.1:3000/");