let color = "#00FF00";
let drawing = false;

function changeColorOnGreen() {
	color = "#00FF00";
}

function changeColorOnBlue() {
	color = "#0000FF";
}

function changeColorOnRed() {
	color = "#FF0000";
}

window.onload = function ()
{
	window.canvas = document.getElementById("box");
	let ctx = canvas.getContext("2d");

	document.getElementById("clear_btn").addEventListener('click', clear_context);
	socket = io.connect("http://127.0.0.1:3000");

	canvas.onmousedown = function (coord)
	{
		drawing = true;
		doTrail(coord);
	};

	canvas.onmousemove = function (coord)
	{
		if (!drawing)
			return false;
		doTrail(coord);
	};

	canvas.onmouseup = function (coord)
	{
		drawing = false;
	}

	function doTrail(coord)
	{
		let x = coord.pageX - canvas.offsetLeft - 15;
		let y = coord.pageY - canvas.offsetTop - 15;
		draw(x, y, color);
		socket.emit('draw', { x: x, y: y, color: color });
	}

	function draw(x, y, color)
	{
		ctx.beginPath();
		ctx.rect(x, y, 5, 5);
		ctx.fillStyle = color;
		ctx.fill();
		ctx.closePath();
	}
	
	function clear()
	{
		ctx.beginPath();
		ctx.clearRect(0, 0, canvas.width, canvas.height);
		ctx.closePath();
	}
	
	function clear_context() {
		clear();
		socket.emit('clear', {});
	}
	
	socket.on('load', function (data)
	{
		//create a new canvas
		var newCanvas = document.createElement('canvas');
		var context = newCanvas.getContext('2d');

		//set dimensions
		newCanvas.width = 1200;
		newCanvas.height = 800;

		//apply the old canvas to the new one
		context.drawImage(data.global_context, 0, 0);
	});

	socket.on('draw', function (data)
	{
		draw(data.x, data.y, data.color);
	});

	socket.on('clear', function (data)
	{
		clear();
	});
}







