const app = require('express')();
const client = require('socket.io-client');
const server = require('http').createServer(app);
const io = require('socket.io')(server);

const canvas = createCanvas(1200, 800);
const context = canvas.getContext("2d");

app.use(require("express").static(__dirname+ '/'));
app.get('/', function (request, response) 
{
	response.sendFile(__dirname + '/index.html');
});

io.on('connection', function (client) { 
	console.log('User was connected to socket!');
	client.on('load', function()
	{
		client.broadcast.emit('load', { global_context: ctx });
	});
	client.on('draw', function(data)
	{
		draw(data.x, data.y, data.color);
		client.broadcast.emit('draw', data);
	});
	client.on('clear', function(data)
	{
		clear();
		client.broadcast.emit('clear', data);
	});
});

function draw(x, y, color)
{
	context.beginPath();
	context.arc(x, y, 5, 0, 2 * Math.PI, false);
	context.fillStyle = color;
	context.fill();
	context.closePath();
}

function clear()
{
	ctx.beginPath();
	ctx.clearRect(0, 0, canvas.width, canvas.height);
	ctx.closePath();
}

server.listen(3000);
console.log("Сервер запущен по адресу http://127.0.0.1:3000/");