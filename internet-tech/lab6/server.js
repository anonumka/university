const hostname = '127.0.0.1';
const port = 3000;

let http = require('http');
let fs = require('fs');
let url = require('url');
let qs = require('querystring');
let auth = false;

function authorization(request, response)
{
	let body = '';
	request.on('data', function (data) {
		body += data;
	});
	request.on('end', function () {
		let post = qs.parse(body);
			verify(post['login'], post['password'], response);
	});
};

function verify(login, pass, response)
{
	fs.readFile("users.json", function(err, file){
		let data = JSON.parse(file);
		for (let i = 0; i < data.users.length; i++) 
		{
			if (data.users[i].login == login && data.users[i].password == pass)
			{
				console.log("(Успех!)");
				auth = true;
				response.writeHead(200, {'Content-Type': 'text/html; charset=utf-8'});	

				fs.createReadStream(__dirname + '/succeful.html').pipe(response);
				return;
			}
		}
		
		// Если пользователь не найден
		console.log("(Ошибка входа!)");
		response.writeHead(200, {'Content-Type': 'text/html; charset=utf-8'});

		fs.createReadStream(__dirname + '/error.html').pipe(response);
	});
}

let server = http.createServer((request, response) => {
  switch (request.url) {
		case '/':
			response.writeHead(200, {'Content-Type': 'text/html; charset=utf-8'});
			fs.createReadStream(__dirname + '/index.html').pipe(response);
			break;
		case '/auth':
			if (auth == false) {
				if (request.method == 'POST')
					authorization(request, response);
				else
				{
					response.writeHead(200, {'Content-Type': 'text/html; charset=utf-8'});
					fs.createReadStream(__dirname + '/auth.html').pipe(response);
				}
			}
			else {
				response.writeHead(200, {'Content-Type': 'text/html; charset=utf-8'});
				auth = false;
				fs.createReadStream(__dirname + '/auth.html').pipe(response);
			}
			break;
		case '/text':
			response.writeHead(200, {'Content-Type': 'text/plain; charset=utf-8'});
			response.end("Hello World");
			break;
		case '/json':
			response.writeHead(200, {'Content-Type': 'application/json; charset=utf-8'});
			fs.createReadStream(__dirname + '/users.json').pipe(response);
			break;
		case '/image':
			response.writeHead(200, {'Content-Type': 'image/jpeg; charset=utf-8'});
			fs.readFile("./img.jpg", function(err, image){response.end(image);});
			break;
		default:
			response.writeHead(404, {'Content-Type': 'text/html; charset=utf-8'});
			fs.createReadStream(__dirname + '/404.html').pipe(response);
			break;
	}
});
server.listen(port, hostname);
console.log(`Server running at http://${hostname}:${port}/`);
