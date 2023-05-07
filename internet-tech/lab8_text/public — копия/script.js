window.onload = function ()
{
	const ta = document.getElementById('input_area');
	socket = io.connect("http://127.0.0.1:3000");
	
	ta.addEventListener('input', event => {
		console.log(event.target.value);
		socket.emit('text_edit', { cur_text: event.target.value });
	});
	
	socket.on('text_edit', function (data)
	{
		ta.value = data.cur_text;
	});
	socket.on('load', function (data)
	{
		ta.value = data.cur_text;
	});
}







