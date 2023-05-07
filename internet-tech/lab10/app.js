const app = require('express')();
const server = require('http').createServer(app);

var text_output = '';

app.use(require("express").static(__dirname+ '/'));
app.get('/', function (request, response) 
{
	response.sendFile(__dirname + '/public/index.html');
});

server.listen(3000);
console.log("Сервер запущен по адресу http://127.0.0.1:3000/");